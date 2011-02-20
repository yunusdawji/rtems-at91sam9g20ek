/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2009/10/26 05:46:46 ralf Exp $
 */

#include <tmacros.h>
#include <rtems/stackchk.h>

rtems_task Init(
  rtems_task_argument argument
)
{
  bool              blown;

  puts( "\n\n*** TEST STACK CHECKER 01 ***" );

  puts( "stack_checker_is_blown - NOT BLOWN" );
  blown = rtems_stack_checker_is_blown();
  rtems_test_assert(!blown);

  puts( "*** END OF TEST STACK CHECKER 01 ***" );
  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS 1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_STACK_CHECKER_ENABLED

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

