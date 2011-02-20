/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: twai_sem.c,v 1.10 2008/09/04 16:04:00 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/itron/semaphore.h>
#include <rtems/itron/task.h>
#include <rtems/score/tod.h>

/*
 *  twai_sem - Wait on Semaphore with Timeout
 *
 *  This function implements the ITRON 3.0 twai_sem() service.
 */

ER twai_sem(
  ID semid,
  TMO tmout
)
{
  ITRON_Semaphore_Control  *the_semaphore;
  Objects_Locations         location;
  Watchdog_Interval         interval;
  bool                      blocking;

  interval = 0;
  if ( tmout == TMO_POL ) {
    blocking = false;
  } else {
    blocking = true;

    if ( tmout != TMO_FEVR )
      interval = TOD_MILLISECONDS_TO_TICKS(tmout);

    if ( _ITRON_Is_in_non_task_state() )
      return E_CTX;
  }

  the_semaphore = _ITRON_Semaphore_Get( semid, &location );
  switch ( location ) {
#if defined(RTEMS_MULTIPROCESSING)
    case OBJECTS_REMOTE:               /* Multiprocessing not supported */
#endif
    case OBJECTS_ERROR:
      return _ITRON_Semaphore_Clarify_get_id_error( semid );

    case OBJECTS_LOCAL:
      _CORE_semaphore_Seize(
        &the_semaphore->semaphore,
        the_semaphore->Object.id,
        blocking,                       /* wait for a timeout */
        interval                        /* timeout value */
      );
      _Thread_Enable_dispatch();
      return _ITRON_Semaphore_Translate_core_semaphore_return_code(
               _Thread_Executing->Wait.return_code
             );
  }
  return E_OK;
}
