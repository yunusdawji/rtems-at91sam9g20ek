/*  Task_2
 *
 *  This routine serves as a test task.
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
 *  $Id: task2.c,v 1.9 2009/12/08 17:52:53 joel Exp $
 */

#include "system.h"

void *Task_2(
  void *argument
)
{
  int  status;

  Task_id = pthread_self();
  printf( "Task_2: ID is 0x%08" PRIxpthread_t "\n", Task_id );

  status = pthread_mutex_lock( &Mutex_id );
  rtems_test_assert(  !status );

  puts( "Task_2: pthread_cond_wait" );
  status = pthread_cond_wait( &Cond1_id, &Mutex_id );
  rtems_test_assert(  !status );

  puts( "Task_2: back from pthread_cond_wait release mutex" );
  status = pthread_mutex_unlock( &Mutex_id );
  rtems_test_assert(  !status );

  puts( "Task_2: task exit" );
  pthread_exit( NULL );

  return NULL; /* just so the compiler thinks we returned something */
}
