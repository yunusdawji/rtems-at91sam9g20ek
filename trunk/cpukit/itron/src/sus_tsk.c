/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: sus_tsk.c,v 1.11 2007/10/26 20:19:00 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <limits.h>
#include <rtems/itron.h>

#include <rtems/score/thread.h>
#include <rtems/score/userext.h>
#include <rtems/score/wkspace.h>
#include <rtems/score/apiext.h>
#include <rtems/score/sysstate.h>

#include <rtems/itron/task.h>


/*
 *  Task-Dependent Synchronization Functions
 */

/*
 *  sus_tsk - Suspend Other Task
 */

ER sus_tsk(
  ID tskid
)
{
  register Thread_Control *the_thread;
  Objects_Locations        location;

  the_thread = _ITRON_Task_Get( tskid, &location );
  switch ( location ) {
#if defined(RTEMS_MULTIPROCESSING)
    case OBJECTS_REMOTE:
#endif
    case OBJECTS_ERROR:
      return _ITRON_Task_Clarify_get_id_error( tskid );

    case OBJECTS_LOCAL:

      if ( _Thread_Is_executing( the_thread ) )
        _ITRON_return_errorno( E_OBJ );

      if (the_thread->suspend_count == INT_MAX )
        _ITRON_return_errorno( E_QOVR );

      _Thread_Suspend( the_thread );
      break;
  }

  _ITRON_return_errorno( E_OK );
}
