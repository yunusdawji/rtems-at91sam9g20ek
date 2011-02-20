/*
 *  write() - POSIX 1003.1b 6.4.2 - Write to a File
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: write.c,v 1.16 2007/09/20 22:25:14 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/libio_.h>
#include <rtems/seterr.h>

/*
 * write
 *
 * This routine writes count bytes from from buffer pointed to by buffer
 * to the file associated with the open file descriptor, fildes.
 */

ssize_t write(
  int         fd,
  const void *buffer,
  size_t      count
)
{
  ssize_t  rc;
  rtems_libio_t     *iop;

  rtems_libio_check_fd( fd );
  iop = rtems_libio_iop( fd );
  rtems_libio_check_is_open( iop );
  rtems_libio_check_buffer( buffer );
  rtems_libio_check_count( count );
  rtems_libio_check_permissions( iop, LIBIO_FLAGS_WRITE );

  /*
   *  Now process the write() request.
   */

  if ( !iop->handlers->write_h )
    rtems_set_errno_and_return_minus_one( ENOTSUP );

  rc = (*iop->handlers->write_h)( iop, buffer, count );

  if ( rc > 0 )
    iop->offset += rc;

  return rc;
}
