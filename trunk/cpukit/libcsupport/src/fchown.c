/*
 *  fchown() - POSIX 1003.1b 5.6.5 - Change Owner and Group of a File
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: fchown.c,v 1.1 2008/04/11 22:57:54 ccj Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/stat.h>
#include <errno.h>

#include <rtems.h>
#include <rtems/libio.h>

#include <rtems/libio_.h>
#include <rtems/seterr.h>

int fchown(
  int   fd,
  uid_t owner,
  gid_t group
)
{
  rtems_libio_t *iop;

  rtems_libio_check_fd( fd );
  iop = rtems_libio_iop( fd );
  rtems_libio_check_is_open(iop);

  rtems_libio_check_permissions( iop, LIBIO_FLAGS_WRITE );

  if ( !iop->pathinfo.ops->chown_h )
    rtems_set_errno_and_return_minus_one( ENOTSUP );

  return (*iop->pathinfo.ops->chown_h)( &iop->pathinfo, owner, group );
}
