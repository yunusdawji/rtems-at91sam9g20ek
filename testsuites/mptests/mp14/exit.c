/*  Exit_test
 *
 *  This routine safely stops the test and prints some information
 *
 *  Input parameters:   NONE
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
 *  $Id: exit.c,v 1.10 2004/04/20 07:09:30 ralf Exp $
 */

#include "system.h"

void Exit_test( void )
{
  rtems_status_code status;
  rtems_mode        old_mode;

  /*
   * Wait a bit before shutting down so we don't screw up the other node
   * when our MPCI shuts down
   */

  rtems_task_wake_after(20);

  status = rtems_task_mode( RTEMS_NO_PREEMPT, RTEMS_PREEMPT_MASK, &old_mode );
  directive_failed( status, "rtems_task_mode" );

  MPCI_Print_statistics();

  rtems_shutdown_executive( 0 );
}
