/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: system.h,v 1.11 2009/10/30 11:05:24 ralf Exp $
 */

#include <tmacros.h>
#include <rtems/itron.h>

/* functions */

void ITRON_Init( void );
void Task_2_through_4(void);

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_ITRON_TASKS      4
#define CONFIGURE_EXTRA_TASK_STACKS (RTEMS_MINIMUM_STACK_SIZE * 4)


#define CONFIGURE_ITRON_INIT_TASK_TABLE

#include <rtems/confdefs.h>

/* global variables */

/* end of include file */
