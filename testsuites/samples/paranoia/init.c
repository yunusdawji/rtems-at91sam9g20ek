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
 *  $Id: init.c,v 1.14 2010/03/29 11:30:48 thomas Exp $
 */

#define CONFIGURE_INIT
#include "system.h"
#include <stdio.h>
#include <stdlib.h> /* exit */

extern int paranoia(int, char **);

char *args[2] = { "paranoia", 0 };

rtems_task Init(
  rtems_task_argument ignored
)
{
  /*
   *  Install whatever optional floating point assistance package
   *  is required by this CPU.
   */

#if BSP_SMALL_MEMORY
  printf("NO Paranoia Test. MEMORY TOO SMALL");
#else

#if (defined (m68040))
  M68KFPSPInstallExceptionHandlers ();
#endif

  printf( "\n\n*** PARANOIA TEST ***\n" );
  paranoia(1, args);
  printf( "*** END OF PARANOIA TEST ***\n" );
#endif /* BSP_SMALL_MEMORY */
  exit( 0 );
}
