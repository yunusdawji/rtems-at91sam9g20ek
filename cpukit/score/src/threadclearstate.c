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
 *  $Id: threadclearstate.c,v 1.10 2009/11/29 13:51:52 ralf Exp $
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
 *  _Thread_Clear_state
 *
 *  This kernel routine clears the appropriate states in the
 *  requested thread.  The thread ready chain is adjusted if
 *  necessary and the Heir thread is set accordingly.
 *
 *  Input parameters:
 *    the_thread - pointer to thread control block
 *    state      - state set to clear
 *
 *  Output parameters:  NONE
 *
 *  INTERRUPT LATENCY:
 *    priority map
 *    select heir
 */


void _Thread_Clear_state(
  Thread_Control *the_thread,
  States_Control  state
)
{
  ISR_Level       level;
  States_Control  current_state;

  _ISR_Disable( level );
    current_state = the_thread->current_state;

    if ( current_state & state ) {
      current_state =
      the_thread->current_state = _States_Clear( state, current_state );

      if ( _States_Is_ready( current_state ) ) {

        _Priority_Add_to_bit_map( &the_thread->Priority_map );

        _Chain_Append_unprotected(the_thread->ready, &the_thread->Object.Node);

        _ISR_Flash( level );

        /*
         *  If the thread that was unblocked is more important than the heir,
         *  then we have a new heir.  This may or may not result in a
         *  context switch.
         *
         *  Normal case:
         *    If the current thread is preemptible, then we need to do
         *    a context switch.
         *  Pseudo-ISR case:
         *    Even if the thread isn't preemptible, if the new heir is
         *    a pseudo-ISR system task, we need to do a context switch.
         */
        if ( the_thread->current_priority < _Thread_Heir->current_priority ) {
          _Thread_Heir = the_thread;
          if ( _Thread_Executing->is_preemptible ||
               the_thread->current_priority == 0 )
            _Context_Switch_necessary = true;
        }
      }
  }
  _ISR_Enable( level );
}
