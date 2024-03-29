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
 *  $Id: system.h,v 1.1 2007/12/13 16:56:21 joel Exp $
 */

/* functions */

#include <pmacros.h>
#include <unistd.h>
#include <errno.h>

void *POSIX_Init(
  void *argument
);

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_POSIX_THREADS     2

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#include <rtems/confdefs.h>

/* global variables */

/* end of include file */
