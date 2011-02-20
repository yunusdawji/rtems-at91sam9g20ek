/*  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: coretodmsecstoticks.c,v 1.1 2008/12/16 20:53:33 joel Exp $
 */


#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/config.h>
#include <rtems/score/tod.h>

uint32_t TOD_MILLISECONDS_TO_TICKS(
  uint32_t milliseconds
)
{
  return (milliseconds / rtems_configuration_get_milliseconds_per_tick());
}
