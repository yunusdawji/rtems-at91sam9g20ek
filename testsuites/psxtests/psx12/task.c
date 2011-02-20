/*  Task_1
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
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
 *  $Id: task.c,v 1.6 2003/09/04 18:53:38 joel Exp $
 */

#include "system.h"
#include <time.h>
#include <sched.h>

void *Task_1(
  void *argument
)
{
  puts( "Task_1: exitting" );
  pthread_exit( NULL );

  return NULL; /* just so the compiler thinks we returned something */
}
