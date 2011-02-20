/*
 *  RTEMS "Broken" __sbrk Implementation
 *
 *  NOTE: sbrk is provided by the BSP.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: __sbrk.c,v 1.6 2009/09/30 05:51:18 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(RTEMS_NEWLIB) && !defined(HAVE___SBRK)

#include <errno.h>

void * __sbrk(
  int incr __attribute__((unused))
)
{
  errno = EINVAL;
  return (void *)0;
}
#endif
