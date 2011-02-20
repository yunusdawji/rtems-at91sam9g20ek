/*
 *  rtems_iterate_over_all_threads
 *
 *  This function operates by as follows:
 *    for all threads
 *         invoke specified function
 *
 *  COPYRIGHT (c) 1989-2003.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: iterateoverthreads.c,v 1.7 2009/07/23 15:46:48 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/thread.h>

void rtems_iterate_over_all_threads(rtems_per_thread_routine routine)
{
  uint32_t             i;
  uint32_t             api_index;
  Thread_Control      *the_thread;
  Objects_Information *information;

  if ( !routine )
    return;

  for ( api_index = 1 ; api_index <= OBJECTS_APIS_LAST ; api_index++ ) {
    if ( !_Objects_Information_table[ api_index ] )
      continue;

    information = _Objects_Information_table[ api_index ][ 1 ];
    if ( !information )
      continue;

    for ( i=1 ; i <= information->maximum ; i++ ) {
      the_thread = (Thread_Control *)information->local_table[ i ];

      if ( !the_thread )
	continue;

      (*routine)(the_thread);
    }
  }

}
