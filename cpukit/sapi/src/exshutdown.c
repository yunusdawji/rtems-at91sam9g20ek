/*
 *  Initialization Manager
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: exshutdown.c,v 1.3 2009/09/04 13:09:48 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/thread.h>

/*
 *  rtems_shutdown_executive
 *
 *  This kernel routine shutdowns the executive.  It halts multitasking
 *  and returns control to the application execution "thread" which
 *  initialially invoked the rtems_initialize_executive directive.
 *
 *  Input parameters:   NONE
 *
 *  Output parameters:  NONE
 */

void rtems_shutdown_executive(
   uint32_t   result
)
{
  if ( !_System_state_Is_shutdown( _System_state_Get() ) ) {
    _System_state_Set( SYSTEM_STATE_SHUTDOWN );
    _Thread_Stop_multitasking();
  }
}
