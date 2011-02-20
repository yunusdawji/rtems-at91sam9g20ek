/*  Task_2
 *
 *  This routine serves as a test task.  It sleeps for 1 minute but
 *  does not expect to wake up.  Task 1 should suspend then delete it
 *  so that it appears to never wake up.
 *
 *  Input parameters:
 *    argument - task argument
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
 *  $Id: task2.c,v 1.3 2003/09/04 18:53:25 joel Exp $
 */

#include "system.h"

/*
 * XXX - This test requires tasks to suspend self, yet ITRON defines
 *       this as an error.
 */

void Task_2()
{
  rtems_status_code status;

  while (1) {

    puts( "TA2 - rtems_task_suspend RTEMS_SELF" );
    status = rtems_task_suspend( RTEMS_SELF );
    directive_failed( status, "TA2 rtems_task_suspend RTEMS_SELF" );

  }
}
