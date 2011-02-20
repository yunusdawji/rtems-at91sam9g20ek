/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: sig_sem.c,v 1.6 2007/10/26 20:19:00 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/itron/semaphore.h>
#include <rtems/itron/task.h>
#include <rtems/score/tod.h>

/*
 *  sig_sem - Signal Semaphore
 *
 *  This function implements the ITRON 3.0 sig_sem() service.
 */

ER sig_sem(
  ID semid
)
{
  ITRON_Semaphore_Control *the_semaphore;
  Objects_Locations        location;
  CORE_semaphore_Status    status;

  the_semaphore = _ITRON_Semaphore_Get( semid, &location );
  switch ( location ) {
#if defined(RTEMS_MULTIPROCESSING)
    case OBJECTS_REMOTE:               /* Multiprocessing not supported */
#endif
    case OBJECTS_ERROR:
      return _ITRON_Semaphore_Clarify_get_id_error( semid );

    case OBJECTS_LOCAL:
      /*
       *  XXX maxsemcnt
       */

      status = _CORE_semaphore_Surrender(
        &the_semaphore->semaphore,
        the_semaphore->Object.id,
        NULL                       /* Multiprocessing not supported */
      );
      _Thread_Enable_dispatch();
      return _ITRON_Semaphore_Translate_core_semaphore_return_code( status );
  }
  return E_OK;
}
