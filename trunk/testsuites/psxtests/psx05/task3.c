/*  Task_3
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
 *  $Id: task3.c,v 1.7 2009/12/08 17:52:53 joel Exp $
 */

#include "system.h"
#include <errno.h>

void *Task_3(
  void *argument
)
{
  int                 status;
  struct sched_param  param;
  int                 policy;

  printf( "Task 3: pthread_mutex_lock unavailable (inherit case)\n" );
  status = pthread_mutex_lock( &Mutex2_id );
  printf( "Task 3: mutex acquired\n" );
  rtems_test_assert(  !status );

  printf( "Task 3: unlock Mutex 2\n" );
  status = pthread_mutex_unlock( &Mutex2_id );
  rtems_test_assert(  !status );

  status = pthread_getschedparam( pthread_self(), &policy, &param );
  rtems_test_assert(  !status );
  printf( "Task 3: pthread_getschedparam priority = %d\n", param.sched_priority );

  printf( "Task 3: exit\n" );
  pthread_exit( NULL );

     /* switch to Init */

  return NULL; /* just so the compiler thinks we returned something */
}
