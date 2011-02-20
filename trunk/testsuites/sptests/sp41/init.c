/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.9 2009/07/24 20:43:06 joel Exp $
 */

#define __RTEMS_VIOLATE_KERNEL_VISIBILITY__
#include <tmacros.h>

void iterator(
  Thread_Control *thread
)
{
}

rtems_task Init(
  rtems_task_argument ignored
)
{
  void *tmp;

  puts( "\n\n*** TEST 41 ***" );

  puts( "Init - overwrite internal value to trip case" );
  tmp = _Objects_Information_table[ OBJECTS_CLASSIC_API ][ 1 ];
  _Objects_Information_table[ OBJECTS_CLASSIC_API ][ 1 ] = NULL;

  puts( "Init - rtems_iterate_over_all_threads" );
  rtems_iterate_over_all_threads(iterator);
  _Objects_Information_table[ OBJECTS_CLASSIC_API ][ 1 ] = tmp;

  puts( "*** END OF TEST 41 ***" );
  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS         1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/* global variables */
