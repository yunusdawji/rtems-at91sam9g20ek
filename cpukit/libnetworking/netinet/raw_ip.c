/*
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)raw_ip.c	8.7 (Berkeley) 5/15/95
 * $FreeBSD: src/sys/netinet/raw_ip.c,v 1.147 2005/01/07 01:45:45 imp Exp $
 */

/*
 *	$Id: raw_ip.c,v 1.10 2010/05/29 04:33:42 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
 
#include "opt_inet6.h"
#include "opt_ipsec.h"
#include "opt_mac.h"

#include <sys/param.h>
#include <rtems/bsd/sys/queue.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <errno.h>
#include <sys/systm.h>

#include <net/if.h>
#include <net/route.h>

#define _IP_VHL
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_pcb.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_mroute.h>

#include <netinet/ip_fw.h>

#if !defined(COMPAT_IPFW) || COMPAT_IPFW == 1
#undef COMPAT_IPFW
#define COMPAT_IPFW 1
#else
#undef COMPAT_IPFW
#endif

static struct inpcbhead ripcb;
static struct inpcbinfo ripcbinfo;

/*
 * Nominal space allocated to a raw ip socket.
 */
#define	RIPSNDQ		8192
#define	RIPRCVQ		8192

/*
 * Raw interface to IP protocol.
 */

/*
 * Initialize raw connection block q.
 */
void
rip_init(void)
{
	LIST_INIT(&ripcb);
	ripcbinfo.listhead = &ripcb;
	/*
	 * XXX We don't use the hash list for raw IP, but it's easier
	 * to allocate a one entry hash list than it is to check all
	 * over the place for hashbase == NULL.
	 */
	ripcbinfo.hashbase = hashinit(1, M_PCB, &ripcbinfo.hashmask);
}

static struct	sockaddr_in ripsrc = { sizeof(ripsrc), AF_INET, 0, {0}, {0} };
/*
 * Setup generic address and protocol structures
 * for raw_input routine, then pass them along with
 * mbuf chain.
 */
void
rip_input(struct mbuf *m, int iphlen)
{
	struct ip *ip = mtod(m, struct ip *);
	register struct inpcb *inp;
	struct inpcb *last = 0;
	struct mbuf *opts = 0;

	ripsrc.sin_addr = ip->ip_src;
	for (inp = ripcb.lh_first; inp != NULL; inp = inp->inp_list.le_next) {
		if (inp->inp_ip_p && inp->inp_ip_p != ip->ip_p)
			continue;
		if (inp->inp_laddr.s_addr &&
                  inp->inp_laddr.s_addr != ip->ip_dst.s_addr)
			continue;
		if (inp->inp_faddr.s_addr &&
                  inp->inp_faddr.s_addr != ip->ip_src.s_addr)
			continue;
		if (last) {
			struct mbuf *n = m_copy(m, 0, (int)M_COPYALL);
			if (n) {
				if (last->inp_flags & INP_CONTROLOPTS ||
				    last->inp_socket->so_options & SO_TIMESTAMP)
				    ip_savecontrol(last, &opts, ip, n);
				if (sbappendaddr(&last->inp_socket->so_rcv,
				    (struct sockaddr *)&ripsrc, n,
				    opts) == 0) {
					/* should notify about lost packet */
					m_freem(n);
					if (opts)
					    m_freem(opts);
				} else
					sorwakeup(last->inp_socket);
				opts = 0;
			}
		}
		last = inp;
	}
	if (last) {
		if (last->inp_flags & INP_CONTROLOPTS ||
		    last->inp_socket->so_options & SO_TIMESTAMP)
			ip_savecontrol(last, &opts, ip, m);
		if (sbappendaddr(&last->inp_socket->so_rcv,
		    (struct sockaddr *)&ripsrc, m, opts) == 0) {
			m_freem(m);
			if (opts)
			    m_freem(opts);
		} else
			sorwakeup(last->inp_socket);
	} else {
		m_freem(m);
              ipstat.ips_noproto++;
              ipstat.ips_delivered--;
      }
}

/*
 * Generate IP header and pass packet to ip_output.
 * Tack on options user may have setup with control call.
 */
int
rip_output(struct mbuf *m, struct socket *so, u_long dst)
{
	struct ip *ip;
	struct inpcb *inp = sotoinpcb(so);
	int flags = ((so->so_options & SO_DONTROUTE) ? IP_ROUTETOIF : 0) |
	    IP_ALLOWBROADCAST;

	/*
	 * If the user handed us a complete IP packet, use it.
	 * Otherwise, allocate an mbuf for a header and fill it in.
	 */
	if ((inp->inp_flags & INP_HDRINCL) == 0) {
		if (m->m_pkthdr.len + sizeof(struct ip) > IP_MAXPACKET) {
			m_freem(m);
			return(EMSGSIZE);
		}
		M_PREPEND(m, sizeof(struct ip), M_WAIT);
		ip = mtod(m, struct ip *);
		ip->ip_tos = 0;
		ip->ip_off = 0;
		ip->ip_p = inp->inp_ip_p;
		ip->ip_len = m->m_pkthdr.len;
		ip->ip_src = inp->inp_laddr;
		ip->ip_dst.s_addr = dst;
		ip->ip_ttl = MAXTTL;
	} else {
		if (m->m_pkthdr.len > IP_MAXPACKET) {
			m_freem(m);
			return(EMSGSIZE);
		}
		ip = mtod(m, struct ip *);
		/* don't allow both user specified and setsockopt options,
		   and don't allow packet length sizes that will crash */
#ifdef _IP_VHL
		if (((IP_VHL_HL(ip->ip_vhl) != (sizeof (*ip) >> 2)) 
		     && inp->inp_options)
		    || (ip->ip_len > m->m_pkthdr.len)
		    || (ip->ip_len < (IP_VHL_HL(ip->ip_vhl) << 2))) {
#else
		if (((ip->ip_hl != (sizeof (*ip) >> 2))
		     && inp->inp_options)
		    || (ip->ip_len > m->m_pkthdr.len)
		    || (ip->ip_len < (ip->ip_hl << 2))) {
#endif
			m_freem(m);
			return EINVAL;
		}
		if (ip->ip_id == 0)
			ip->ip_id = htons(ip_id++);
		/* XXX prevent ip_output from overwriting header fields */
		flags |= IP_RAWOUTPUT;
		ipstat.ips_rawout++;
	}
	return (ip_output(m, inp->inp_options, &inp->inp_route, flags,
			  inp->inp_moptions));
}

/*
 * Raw IP socket option processing.
 */
int
rip_ctloutput(int op, struct socket *so, int level, int optname,
	struct mbuf **m)
{
	struct inpcb *inp = sotoinpcb(so);
	int error;

	if (level != IPPROTO_IP) {
		if (op == PRCO_SETOPT && *m)
			(void)m_free(*m);
		return (EINVAL);
	}

	switch (optname) {

	case IP_HDRINCL:
		error = 0;
		if (op == PRCO_SETOPT) {
			if (m == 0 || *m == 0 || (*m)->m_len < sizeof (int))
				error = EINVAL;
			else if (*mtod(*m, int *))
				inp->inp_flags |= INP_HDRINCL;
			else
				inp->inp_flags &= ~INP_HDRINCL;
			if (*m)
				(void)m_free(*m);
		} else {
			*m = m_get(M_WAIT, MT_SOOPTS);
			(*m)->m_len = sizeof (int);
			*mtod(*m, int *) = inp->inp_flags & INP_HDRINCL;
		}
		return (error);

#ifdef COMPAT_IPFW
	case IP_FW_GET:
		if (ip_fw_ctl_ptr == NULL || op == PRCO_SETOPT) {
			if (*m) (void)m_free(*m);
			return(EINVAL);
		}
		return (*ip_fw_ctl_ptr)(optname, m); 

	case IP_FW_ADD:
	case IP_FW_DEL:
	case IP_FW_FLUSH:
	case IP_FW_ZERO:
		if (ip_fw_ctl_ptr == NULL || op != PRCO_SETOPT) {
			if (*m) (void)m_free(*m);
			return(EINVAL);
		}
		return (*ip_fw_ctl_ptr)(optname, m); 

	case IP_NAT:
		if (ip_nat_ctl_ptr == NULL) {
			if (*m) (void)m_free(*m);
			return(EINVAL);
		}
		return (*ip_nat_ctl_ptr)(op, m); 

#endif
	case IP_RSVP_ON:
		return ip_rsvp_init(so);
		break;

	case IP_RSVP_OFF:
		return ip_rsvp_done();
		break;

	case IP_RSVP_VIF_ON:
		return ip_rsvp_vif_init(so, *m);

	case IP_RSVP_VIF_OFF:
		return ip_rsvp_vif_done(so, *m);

	case MRT_INIT:
	case MRT_DONE:
	case MRT_ADD_VIF:
	case MRT_DEL_VIF:
	case MRT_ADD_MFC:
	case MRT_DEL_MFC:
	case MRT_VERSION:
	case MRT_ASSERT:
		if (op == PRCO_SETOPT) {
			error = ip_mrouter_set(optname, so, *m);
			if (*m)
				(void)m_free(*m);
		} else if (op == PRCO_GETOPT) {
			error = ip_mrouter_get(optname, so, m);
		} else
			error = EINVAL;
		return (error);
	}
	return (ip_ctloutput(op, so, level, optname, m));
}

static u_long	rip_sendspace = RIPSNDQ; /* XXX sysctl ? */
static u_long	rip_recvspace = RIPRCVQ; /* XXX sysctl ? */

/*ARGSUSED*/
int
rip_usrreq(struct socket *so, int req, struct mbuf *m, struct mbuf *nam,
	struct mbuf *control)
{
	register int error = 0;
	register struct inpcb *inp = sotoinpcb(so);
	int s;

	if (req == PRU_CONTROL)
		return (in_control(so, (uintptr_t)m, (caddr_t)nam,
			(struct ifnet *)control));

	switch (req) {

	case PRU_ATTACH:
		if (inp)
			panic("rip_attach");
		if ((so->so_state & SS_PRIV) == 0) {
			error = EACCES;
			break;
		}
		s = splnet();
		error = in_pcballoc(so, &ripcbinfo);
		splx(s);
		if (error)
			break;
		error = soreserve(so, rip_sendspace, rip_recvspace);
		if (error)
			break;
		inp = (struct inpcb *)so->so_pcb;
		inp->inp_ip_p = (uintptr_t)nam;
		break;

	case PRU_DISCONNECT:
		if ((so->so_state & SS_ISCONNECTED) == 0) {
			error = ENOTCONN;
			break;
		}
		/* FALLTHROUGH */
	case PRU_ABORT:
		soisdisconnected(so);
		/* FALLTHROUGH */
	case PRU_DETACH:
		if (inp == 0)
			panic("rip_detach");
		if (so == ip_mrouter)
			ip_mrouter_done();
		ip_rsvp_force_done(so);
		if (so == ip_rsvpd)
			ip_rsvp_done();
		in_pcbdetach(inp);
		break;

	case PRU_BIND:
	    {
		struct sockaddr_in *addr = mtod(nam, struct sockaddr_in *);

		if (nam->m_len != sizeof(*addr)) {
			error = EINVAL;
			break;
		}
		if ((ifnet == 0) ||
		    ((addr->sin_family != AF_INET) &&
		     (addr->sin_family != AF_IMPLINK)) ||
		    (addr->sin_addr.s_addr &&
		     ifa_ifwithaddr((struct sockaddr *)addr) == 0)) {
			error = EADDRNOTAVAIL;
			break;
		}
		inp->inp_laddr = addr->sin_addr;
		break;
	    }
	case PRU_CONNECT:
	    {
		struct sockaddr_in *addr = mtod(nam, struct sockaddr_in *);

		if (nam->m_len != sizeof(*addr)) {
			error = EINVAL;
			break;
		}
		if (ifnet == 0) {
			error = EADDRNOTAVAIL;
			break;
		}
		if ((addr->sin_family != AF_INET) &&
		     (addr->sin_family != AF_IMPLINK)) {
			error = EAFNOSUPPORT;
			break;
		}
		inp->inp_faddr = addr->sin_addr;
		soisconnected(so);
		break;
	    }

	case PRU_CONNECT2:
		error = EOPNOTSUPP;
		break;

	/*
	 * Mark the connection as being incapable of further input.
	 */
	case PRU_SHUTDOWN:
		socantsendmore(so);
		break;

	/*
	 * Ship a packet out.  The appropriate raw output
	 * routine handles any massaging necessary.
	 */
	case PRU_SEND:
	    {
		register u_long dst;

		if (so->so_state & SS_ISCONNECTED) {
			if (nam) {
				error = EISCONN;
				break;
			}
			dst = inp->inp_faddr.s_addr;
		} else {
			if (nam == NULL) {
				error = ENOTCONN;
				break;
			}
			dst = mtod(nam, struct sockaddr_in *)->sin_addr.s_addr;
		}
		error = rip_output(m, so, dst);
		m = NULL;
		break;
	    }

	case PRU_SENSE:
		/*
		 * stat: don't bother with a blocksize.
		 */
		return (0);

	/*
	 * Not supported.
	 */
	case PRU_RCVOOB:
	case PRU_RCVD:
	case PRU_LISTEN:
	case PRU_ACCEPT:
	case PRU_SENDOOB:
		error = EOPNOTSUPP;
		break;

	case PRU_SOCKADDR:
		in_setsockaddr(inp, nam);
		break;

	case PRU_PEERADDR:
		in_setpeeraddr(inp, nam);
		break;

	default:
		panic("rip_usrreq");
	}
	if (m != NULL)
		m_freem(m);
	return (error);
}
