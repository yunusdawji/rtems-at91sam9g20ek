/*  Task_3
 *
 *  This routine serves as a test task.  It simply sleeps for 5 seconds
 *  and then deletes itself.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: task3.c,v 1.4 2009/08/12 20:50:24 joel Exp $
 */

#include "system.h"

void Task_3()
{
  rtems_status_code status;

  /*
   * XXX - Convert Later.
   */

  puts( "TA3 - rtems_task_wake_after - sleep 5 seconds" );
  status = rtems_task_wake_after( 5*rtems_clock_get_ticks_per_second() );
  directive_failed( status, "rtems_task_wake_after in TA3" );


  puts( "TA3 - exd_tsk - exit and delete self" );
  exd_tsk();
  directive_failed( 0, "exd_tsk" );
}
