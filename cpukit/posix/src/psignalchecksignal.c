/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: psignalchecksignal.c,v 1.9 2009/06/29 23:19:28 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(RTEMS_DEBUG)
  #include <assert.h>
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
 *  _POSIX_signals_Check_signal
 */

bool    _POSIX_signals_Check_signal(
  POSIX_API_Control  *api,
  int                 signo,
  bool                is_global
)
{
  siginfo_t                   siginfo_struct;
  sigset_t                    saved_signals_blocked;

  if ( ! _POSIX_signals_Clear_signals( api, signo, &siginfo_struct,
                                       is_global, true ) )
    return false;

  /*
   *  Since we made a union of these, only one test is necessary but this is
   *  safer.
   */
  #if defined(RTEMS_DEBUG)
    assert( _POSIX_signals_Vectors[ signo ].sa_handler ||
            _POSIX_signals_Vectors[ signo ].sa_sigaction );
  #endif

  /*
   *  Just to prevent sending a signal which is currently being ignored.
   */
  if ( _POSIX_signals_Vectors[ signo ].sa_handler == SIG_IGN )
    return false;

  /*
   *  Block the signals requested in sa_mask
   */
  saved_signals_blocked = api->signals_blocked;
  api->signals_blocked |= _POSIX_signals_Vectors[ signo ].sa_mask;

  /*
   *  Here, the signal handler function executes
   */
  switch ( _POSIX_signals_Vectors[ signo ].sa_flags ) {
    case SA_SIGINFO:
      (*_POSIX_signals_Vectors[ signo ].sa_sigaction)(
        signo,
        &siginfo_struct,
        NULL        /* context is undefined per 1003.1b-1993, p. 66 */
      );
      break;
    default:
      (*_POSIX_signals_Vectors[ signo ].sa_handler)( signo );
      break;
  }

  /*
   *  Restore the previous set of blocked signals
   */
  api->signals_blocked = saved_signals_blocked;

  return true;
}
