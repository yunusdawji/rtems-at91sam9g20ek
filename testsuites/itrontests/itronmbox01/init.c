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
 *  $Id: init.c,v 1.7 2008/02/01 00:45:01 joel Exp $
 */

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <time.h>

void ITRON_Init( void )
{
  printf( "\n\n*** ITRON MBOX TEST 01 ***\n" );
  printf( "ITRON Mailboxes are implemented but there is currently no test.\n" );
  printf( "*** END OF ITRON MBOX TEST 01 ***\n" );
  rtems_test_exit( 0 );
}
