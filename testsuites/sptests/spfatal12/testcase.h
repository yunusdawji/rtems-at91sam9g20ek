/*  Test __assert_func with NULL function name
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: testcase.h,v 1.1 2009/09/04 21:28:56 joel Exp $
 */

#define FATAL_ERROR_TEST_NAME            "12"
#define FATAL_ERROR_DESCRIPTION  \
        "_Heap_Initialize fails during RTEMS initialization"
#define FATAL_ERROR_EXPECTED_SOURCE      INTERNAL_ERROR_CORE
#define FATAL_ERROR_EXPECTED_IS_INTERNAL TRUE
#define FATAL_ERROR_EXPECTED_ERROR       INTERNAL_ERROR_TOO_LITTLE_WORKSPACE

void force_error()
{
  Configuration.work_space_size  = sizeof(void *);
  rtems_initialize_data_structures();

  /* we will not run this far */
}
