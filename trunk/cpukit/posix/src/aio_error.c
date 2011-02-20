/*
 *  6.7.5 Retrieve Error of Asynchronous I/O Operation, P1003.1b-1993, p. 161
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: aio_error.c,v 1.2 2009/01/02 10:04:23 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <aio.h>
#include <errno.h>

#include <rtems/system.h>
#include <rtems/seterr.h>

int aio_error(
  const struct aiocb  *aiocbp __attribute__((unused))
)
{
  rtems_set_errno_and_return_minus_one( ENOSYS );
}
