/*
 *  $Id: condtimedwait.c,v 1.8 2009/05/03 23:10:02 joel Exp $
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: condtimedwait.c,v 1.8 2009/05/03 23:10:02 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <pthread.h>
#include <errno.h>

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/score/states.h>
#include <rtems/score/watchdog.h>
#include <rtems/posix/cond.h>
#include <rtems/posix/time.h>
#include <rtems/posix/mutex.h>

/*PAGE
 *
 *  11.4.4 Waiting on a Condition, P1003.1c/Draft 10, p. 105
 */

int pthread_cond_timedwait(
  pthread_cond_t        *cond,
  pthread_mutex_t       *mutex,
  const struct timespec *abstime
)
{
  Watchdog_Interval ticks;
  bool              already_timedout;

  /*
   *  POSIX requires that blocking calls with timeouts that take
   *  an absolute timeout must ignore issues with the absolute
   *  time provided if the operation would otherwise succeed.
   *  So we check the abstime provided, and hold on to whether it
   *  is valid or not.  If it isn't correct and in the future,
   *  then we do a polling operation and convert the UNSATISFIED
   *  status into the appropriate error.
   */
  switch ( _POSIX_Absolute_timeout_to_ticks(abstime, &ticks) ) {
    case POSIX_ABSOLUTE_TIMEOUT_INVALID:
      return EINVAL;
    case POSIX_ABSOLUTE_TIMEOUT_IS_IN_PAST:
    case POSIX_ABSOLUTE_TIMEOUT_IS_NOW:
      already_timedout = true;
      break;
    case POSIX_ABSOLUTE_TIMEOUT_IS_IN_FUTURE:
    default:  /* only to silence warnings */
      already_timedout = false;
      break;
  }

  return _POSIX_Condition_variables_Wait_support(
    cond,
    mutex,
    ticks,
    already_timedout
  );
}
