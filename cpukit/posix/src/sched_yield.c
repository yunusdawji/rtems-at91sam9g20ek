/*
 *  13.3.5 Yield Processor, P1003.1b-1993, p. 257
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: sched_yield.c,v 1.1 2007/12/13 16:52:21 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sched.h>
#include <errno.h>

#include <rtems/system.h>
#include <rtems/score/tod.h>
#include <rtems/score/thread.h>
#include <rtems/seterr.h>
#include <rtems/posix/priority.h>
#include <rtems/posix/time.h>

int sched_yield( void )
{
  _Thread_Disable_dispatch();
    _Thread_Yield_processor();
  _Thread_Enable_dispatch();
  return 0;
}
