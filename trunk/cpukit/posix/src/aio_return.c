/*
 *  6.7.6 Retrieve Return Status of Asynchronous I/O Operation,
 *        P1003.1b-1993, p. 162
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: aio_return.c,v 1.2.2.1 2010/08/09 07:37:18 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <aio.h>
#include <errno.h>

#include <rtems/system.h>
#include <rtems/seterr.h>

ssize_t aio_return(
  const struct aiocb  *aiocbp __attribute__((unused))
)
{
  rtems_set_errno_and_return_minus_one( ENOSYS );
}
