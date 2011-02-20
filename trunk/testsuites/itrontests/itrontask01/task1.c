/*  Task_1_through_3
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
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
 *  $Id: task1.c,v 1.10 2009/10/30 11:06:18 ralf Exp $
 */

#include "system.h"

void Task_2_through_4(void)
{
  ID                tid;
  int               tid_index;
  rtems_time_of_day time;
  ER                status;
  char              name[30];

  status = get_tid( &tid );
  directive_failed( status, "get_tid");

  tid_index = tid - 1;  /* account for init tasks */

  sprintf(name, "TA%d", tid_index);

  while( FOREVER ) {
    status = rtems_clock_get_tod( &time );
    directive_failed( status, "rtems_clock_get_tod" );

    if ( time.second >= 35 ) {
      puts( "*** END OF ITRON TASK TEST 1 ***" );
      rtems_test_exit( 0 );
    }

    printf(name);
    print_time( " - rtems_clock_get_tod - ", &time, "\n" );

    status = rtems_task_wake_after(
      tid_index * 5 * rtems_clock_get_ticks_per_second() );
    directive_failed( status, "rtems_task_wake_after" );
  }
}
