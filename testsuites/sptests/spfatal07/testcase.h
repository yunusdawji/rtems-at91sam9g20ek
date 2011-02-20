/*
 * Classic API Init task create failure
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: testcase.h,v 1.6 2009/11/30 03:33:25 ralf Exp $
 */

/*
 *  Way too much stack space.  Should generate a fatal error
 *  on the init task create.
 */
#define CONFIGURE_HAS_OWN_INIT_TASK_TABLE
#define CONFIGURE_INIT_TASK_STACK_SIZE   RTEMS_MINIMUM_STACK_SIZE
rtems_initialization_tasks_table Initialization_tasks[] = {
  { rtems_build_name('I', 'N', 'I', ' '),
    RTEMS_MINIMUM_STACK_SIZE,
    1,
    RTEMS_DEFAULT_ATTRIBUTES,
    Init,
    RTEMS_DEFAULT_MODES,
    0
  }
};
#define CONFIGURE_INIT_TASK_TABLE Initialization_tasks
#define CONFIGURE_INIT_TASK_TABLE_SIZE \
  sizeof(CONFIGURE_INIT_TASK_TABLE) / sizeof(rtems_initialization_tasks_table)

#define FATAL_ERROR_TEST_NAME            "7"
#define FATAL_ERROR_DESCRIPTION \
        "Core Configuration Invalid ISR stack size"
#define FATAL_ERROR_EXPECTED_SOURCE      INTERNAL_ERROR_CORE
#define FATAL_ERROR_EXPECTED_IS_INTERNAL TRUE
#define FATAL_ERROR_EXPECTED_ERROR       INTERNAL_ERROR_INTERRUPT_STACK_TOO_SMALL

void force_error()
{
  #if (CPU_ALLOCATE_INTERRUPT_STACK == TRUE)
    Configuration.interrupt_stack_size = (STACK_MINIMUM_SIZE-1);
    rtems_initialize_data_structures();
  #else
    puts(
      "WARNING - Test not applicable on this target architecture.\n"
      "WARNING - Only applicable when CPU_ALLOCATE_INTERRUPT_STACK == TRUE."
    );
    rtems_test_exit(0);
  #endif

  /* we will not run this far */
}
