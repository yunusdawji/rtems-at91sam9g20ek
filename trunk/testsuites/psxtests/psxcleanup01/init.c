/*
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2009/11/30 03:33:23 ralf Exp $
 */

#include <rtems.h>
#include "pmacros.h"
#include <pthread.h>  /* thread facilities */

void cleaner(void *arg)
{
  puts( "clean was not supposed to run" );
  rtems_test_exit(0);
}

void *POSIX_Init(
  void *argument
)
{
  puts( "\n\n*** POSIX CLEANUP TEST 01 ***" );

  puts( "Init - pthread_cleanup_push - a routine we will not execute" );
  pthread_cleanup_push(cleaner, NULL);

  puts( "Init - pthread_cleanup_pop - do not execute" );
  pthread_cleanup_pop(0);

  puts( "*** END OF POSIX CLEANUP TEST 01 ***\n" );
  rtems_test_exit(0);
}


/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_MAXIMUM_POSIX_THREADS 1

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
