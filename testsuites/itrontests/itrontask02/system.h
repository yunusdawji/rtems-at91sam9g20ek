/*  system.h
 *
 *  This include file contains information that is included in every
 *  function in the test set.
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: system.h,v 1.11 2009/10/30 11:08:15 ralf Exp $
 */

#include <tmacros.h>
#include <rtems/itron.h>

/* functions */

void ITRON_Init( void );
void Dormant_task(void);
void Non_Dormant_task(void);

/* configuration information */

/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_ITRON_TASKS      5

#define CONFIGURE_ITRON_INIT_TASK_TABLE

#include <rtems/confdefs.h>

/* global variables */

#define DORMANT_TASK_ID         2
#define NON_DORMANT_TASK_ID     3

TEST_EXTERN rtems_id Global_variable;   /* example global variable     */

/* end of include file */
