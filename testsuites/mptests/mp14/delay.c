/*  Delayed_send_event
 *
 *  This routine is a timer service routine which sends an event to a task.
 *
 *  Input parameters:  NONE
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: delay.c,v 1.11 2008/09/05 21:30:17 joel Exp $
 */

#include "system.h"

rtems_timer_service_routine Delayed_send_event(
  rtems_id  timer_id,
  void     *id_ptr
)
{
  rtems_status_code status;
  rtems_id          id = *(rtems_id *)id_ptr;

  status = rtems_event_send( id, RTEMS_EVENT_16 );
  fatal_directive_check_status_only(
    status, RTEMS_SUCCESSFUL, "rtems_event_send" );
}
