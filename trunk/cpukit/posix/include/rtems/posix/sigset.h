/**
 * @file rtems/posix/sigset.h
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: sigset.h,v 1.1 2009/12/04 15:24:21 ralf Exp $
 */

#ifndef _RTEMS_POSIX_SIGSET_H
#define _RTEMS_POSIX_SIGSET_H

#include <signal.h> // sigset_t

/*
 *  Currently 32 signals numbered 1-32 are defined
 */

#define SIGNAL_EMPTY_MASK  0x00000000L
#define SIGNAL_ALL_MASK    0xffffffffL

static inline sigset_t signo_to_mask(
  uint32_t sig
)
{
  return 1u << (sig - 1);
}

static inline bool is_valid_signo(
  int signo
)
{
  return ((signo) >= 1 && (signo) <= 32 );
}

#endif
