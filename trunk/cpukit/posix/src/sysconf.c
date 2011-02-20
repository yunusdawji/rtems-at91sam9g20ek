/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: sysconf.c,v 1.16 2009/11/30 15:44:21 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>
#include <unistd.h>
#include <errno.h>

#include <rtems/system.h>
#include <rtems/seterr.h>
#include <rtems/score/tod.h>
#include <rtems/libio_.h>

#include <sys/param.h>

/*PAGE
 *
 *  4.8.1 Get Configurable System Variables, P1003.1b-1993, p. 95
 */

long sysconf(
  int name
)
{
  if ( name == _SC_CLK_TCK )
    return (TOD_MICROSECONDS_PER_SECOND /
      rtems_configuration_get_microseconds_per_tick());

  if ( name == _SC_OPEN_MAX )
    return rtems_libio_number_iops;

  if ( name == _SC_GETPW_R_SIZE_MAX )
    return 1024;

  if ( name == _SC_PAGESIZE )
    return PAGE_SIZE;

#if defined(__sparc__)
  if ( name == 515 ) /* Solaris _SC_STACK_PROT */
   return 0;
#endif

  rtems_set_errno_and_return_minus_one( EINVAL );
}
