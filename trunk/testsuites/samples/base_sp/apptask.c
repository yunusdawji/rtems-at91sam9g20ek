/*  Application_task
 *
 *  This routine is as an example of an application task which
 *  prints a message including its RTEMS task id.  This task
 *  then invokes exit to return to the monitor.
 *
 *  Input parameters:  NONE
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
 *  $Id: apptask.c,v 1.14 2009/10/27 06:59:20 ralf Exp $
 */

#include "system.h"
#include "tmacros.h"

#include <stdio.h>
#include <stdlib.h>

rtems_task Application_task(
  rtems_task_argument argument
)
{
  rtems_id          tid;
  rtems_status_code status;

  status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );

  printf( "Application task was invoked with argument (%" PRIdrtems_task_argument ") "
          "and has id of 0x%" PRIxrtems_id "\n", argument, tid );

  printf( "*** END OF SAMPLE SINGLE PROCESSOR APPLICATION ***\n" );
  exit( 0 );
}
