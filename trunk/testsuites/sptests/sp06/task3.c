/*  Task_3
 *
 *  This routine serves as a test task.  It is started, has its priority
 *  changed, and when it runs it deletes itself.
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
 *  $Id: task3.c,v 1.8 2003/09/04 18:53:47 joel Exp $
 */

#include "system.h"

rtems_task Task_3(
  rtems_task_argument argument
)
{
  rtems_status_code status;

  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_SELF" );
}
