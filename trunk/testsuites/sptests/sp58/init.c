/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2009/11/30 03:33:25 ralf Exp $
 */

#include <tmacros.h>

#include <sys/types.h>
#include <rtems/score/timespec.h>
#include <rtems/score/threadq.h>

void timespec_divide_by_zero(void)
{
  struct timespec      t1;
  struct timespec      zero;
  uint32_t             ival_percentage;
  uint32_t             fval_percentage;

  t1.tv_sec  = 1;
  t1.tv_nsec = 0;

  zero.tv_sec  = 0;
  zero.tv_nsec = 0;

  ival_percentage = 1234;
  fval_percentage = 5678;

  puts( "Init - _Timespec_Divide - by zero" );
  _Timespec_Divide( &t1, &zero, &ival_percentage, &fval_percentage );
  rtems_test_assert( ival_percentage == 0 );
  rtems_test_assert( fval_percentage == 0 );

}

rtems_task Init(
  rtems_task_argument ignored
)
{
  puts( "\n\n*** TEST 58 ***" );

  timespec_divide_by_zero();

  puts( "*** END OF TEST 58 ***" );
  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS  1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>

/* global variables */
