/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 * $Id: init.c,v 1.9 2009/10/26 17:04:39 ralf Exp $
 */

#include <tmacros.h>  /* includes bsp.h, stdio, etc... */

rtems_task Init(
    rtems_task_argument ignored
) {
  rtems_status_code  status;
  rtems_interval     timestamps[6],
                     wantintervals[5] = { 1, 50, 200, 25, 3 };
  rtems_name         period_name = rtems_build_name('P','E','R','a');
  rtems_id           period_id;
  int                loopy;

  printf("\n\n*** TEST 32 ***\n");

  /* create period */
  status = rtems_rate_monotonic_create(
      period_name,
      &period_id
  );
  directive_failed(status, "rate_monotonic_create");

  /* start period with initial value */
  status = rtems_rate_monotonic_period( period_id, wantintervals[0] );
  directive_failed(status, "rate_monotonic_period #1");

  /* get our first timestamp */
  status = rtems_clock_get( RTEMS_CLOCK_GET_TICKS_SINCE_BOOT, &timestamps[0] );
  directive_failed(status, "clock_get");

  /* loop through and gather more timestamps */
  for (loopy = 1; loopy < 5; loopy++) {

    status = rtems_rate_monotonic_period( period_id, wantintervals[loopy] );
    directive_failed(status, "rate_monotonic_period #2");

    status = rtems_clock_get(
        RTEMS_CLOCK_GET_TICKS_SINCE_BOOT,
        &timestamps[loopy]
    );
    directive_failed(status, "clock_get");
  }

  /* block one last time */
  status = rtems_rate_monotonic_period( period_id, 1 );
  directive_failed(status, "rate_monotonic_period #3");

  /* get one last timestamp */
  status = rtems_clock_get(
      RTEMS_CLOCK_GET_TICKS_SINCE_BOOT,
      &timestamps[loopy]
  );
  directive_failed(status, "clock_get");

  /* cancel the period */
  status = rtems_rate_monotonic_cancel(period_id);
  directive_failed(status, "rate_monotonic_cancel");

  /* delete it */
  status = rtems_rate_monotonic_delete(period_id);
  directive_failed(status, "rate_monotonic_delete");

  /* tabulate and print results */
  for (loopy = 0; loopy < 5; loopy++) {
    printf(
        "period %d: measured %" PRIdrtems_interval " tick(s), wanted %" PRIdrtems_interval "\n",
        loopy, timestamps[loopy+1] - timestamps[loopy],
        wantintervals[loopy]
    );
  }

  /* the end */
  puts("*** END OF TEST 32 ***");
  rtems_test_exit(0);
}

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_MAXIMUM_TASKS        1
#define CONFIGURE_MAXIMUM_PERIODS      1

#define CONFIGURE_MICROSECONDS_PER_TICK 100000

#define CONFIGURE_INIT

#include <rtems/confdefs.h>

