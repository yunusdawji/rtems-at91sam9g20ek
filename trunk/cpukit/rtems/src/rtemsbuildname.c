/*
 *  RTEMS Object Helper -- Build an Object Name
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: rtemsbuildname.c,v 1.2 2009/11/30 15:59:55 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/rtems/types.h>

#undef rtems_build_name
rtems_name rtems_build_name(
  char C1,
  char C2,
  char C3,
  char C4
)
{
  return _Objects_Build_name( C1, C2, C3, C4 );
}
