/*
 *  RTEMS Object Helper -- Extract API From Id
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: rtemsobjectidgetapi.c,v 1.3 2009/11/30 15:59:56 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/rtems/types.h>

#undef rtems_object_id_get_api
int rtems_object_id_get_api(
  rtems_id id
)
{
  return _Objects_Get_API( id );
}
