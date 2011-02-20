/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2009/11/30 03:33:23 ralf Exp $
 */

#include "tmacros.h"
#include <pthread.h>
#include <errno.h>

void *POSIX_Init(
  void *argument
)
{
  int            sc;
  pthread_cond_t cond1;
  pthread_cond_t cond2;

  puts( "\n\n*** POSIX TEST -- AUTOMATIC INITIALIZAITON 02 ***" );

  cond1 = PTHREAD_COND_INITIALIZER;
  cond2 = PTHREAD_COND_INITIALIZER;
  puts( "Init - pthread_cond_broadcast - auto initialize - OK" );
  sc = pthread_cond_broadcast( &cond1 );
  fatal_posix_service_status( sc, 0, "cond broadcast OK" );

  puts( "Init - pthread_cond_broadcast - auto initialize - EINVAL" );
  sc = pthread_cond_broadcast( &cond2 );
  fatal_posix_service_status( sc, EINVAL, "cond lock EINVAL" );

  puts( "Init - pthread_cond_destroy - OK" );
  sc = pthread_cond_destroy( &cond1 );
  fatal_posix_service_status( sc, 0, "cond destroy OK" );

  puts( "*** END OF POSIX TEST AUTOMATIC INITIALIZATION 02 ***" );
  rtems_test_exit( 0 );

  return NULL; /* just so the compiler thinks we returned something */
}

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_POSIX_THREADS 1
#define CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES 1

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
