/*  Init
 *
 *  This routine is the initialization task for this test program.
 *  It is called from init_exec and has the responsibility for creating
 *  and starting the tasks that make up the test.  If the time of day
 *  clock is required for the test, it should also be set to a known
 *  value by this function.
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
 *  $Id: init.c,v 1.3 2003/09/04 18:51:28 joel Exp $
 */

#define TEST_INIT
#include "system.h"

extern void debug_test(void);

rtems_task Init(
  rtems_task_argument ignored
)
{
  printf( "\n\n*** C DEBUG TEST ***\n" );

  debug_test();

  printf( "\n*** END OF C DEBUG TEST ***\n" );

  exit( 0 );
}
