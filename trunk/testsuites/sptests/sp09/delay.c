/*  Delayed_routine
 *
 *  This routine is used as the timer routine for Timer Manager tests.
 *
 *  Input parameters:
 *    ignored - this parameter is ignored
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: delay.c,v 1.8 2003/09/04 18:53:47 joel Exp $
 */

#include "system.h"

rtems_timer_service_routine Delayed_routine(
  rtems_id  ignored_id,
  void     *ignored_address
)
{
}
