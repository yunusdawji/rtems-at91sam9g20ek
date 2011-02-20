/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: psignalsetprocesssignals.c,v 1.6 2007/12/17 16:19:14 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <pthread.h>
#include <signal.h>

#include <rtems/system.h>
#include <rtems/score/isr.h>
#include <rtems/score/thread.h>
#include <rtems/score/tqdata.h>
#include <rtems/score/wkspace.h>
#include <rtems/seterr.h>
#include <rtems/posix/threadsup.h>
#include <rtems/posix/psignal.h>
#include <rtems/posix/pthread.h>
#include <rtems/posix/time.h>
#include <stdio.h>

/*PAGE
 *
 *  _POSIX_signals_Set_process_signals
 */

void _POSIX_signals_Set_process_signals(
  sigset_t   mask
)
{
  ISR_Level  level;

  _ISR_Disable( level );
    if ( !_POSIX_signals_Pending )
      _Thread_Do_post_task_switch_extension++;
    _POSIX_signals_Pending |= mask;
  _ISR_Enable( level );
}
