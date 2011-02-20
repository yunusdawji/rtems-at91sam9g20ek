/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: system.h,v 1.7 2009/12/08 17:52:47 joel Exp $
 */

#include <tmacros.h>
#include <rtems/itron.h>

/* functions */

void ITRON_Init( void );

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_ITRON_TASKS       1
#define CONFIGURE_MAXIMUM_ITRON_SEMAPHORES  10

#define CONFIGURE_ITRON_INIT_TASK_TABLE

#include <rtems/confdefs.h>

/* global variables */

TEST_EXTERN rtems_id Global_variable;   /* example global variable     */

/* end of include file */
