/*
 *  Thread Handler
 *
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: threadevaluatemode.c,v 1.6 2008/12/22 05:52:32 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/apiext.h>
#include <rtems/score/context.h>
#include <rtems/score/interr.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/score/priority.h>
#include <rtems/score/states.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/thread.h>
#include <rtems/score/threadq.h>
#include <rtems/score/userext.h>
#include <rtems/score/wkspace.h>

/*PAGE
 *
 *  _Thread_Evaluate_mode
 *
 *  XXX
 */

bool _Thread_Evaluate_mode( void )
{
  Thread_Control     *executing;

  executing = _Thread_Executing;

  if ( !_States_Is_ready( executing->current_state ) ||
       ( !_Thread_Is_heir( executing ) && executing->is_preemptible ) ) {
    _Context_Switch_necessary = true;
    return true;
  }

  return false;
}
