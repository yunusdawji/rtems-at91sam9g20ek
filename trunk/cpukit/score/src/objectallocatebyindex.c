/*
 *  Object Handler
 *
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: objectallocatebyindex.c,v 1.13 2009/01/05 20:09:02 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/address.h>
#include <rtems/score/chain.h>
#include <rtems/score/object.h>
#if defined(RTEMS_MULTIPROCESSING)
#include <rtems/score/objectmp.h>
#endif
#include <rtems/score/thread.h>
#include <rtems/score/wkspace.h>
#include <rtems/score/sysstate.h>
#include <rtems/score/isr.h>

/*PAGE
 *
 *  _Objects_Allocate_by_index
 *
 *  DESCRIPTION:
 *
 *  This function allocates the object control block
 *  specified by the index from the inactive chain of
 *  free object control blocks.
 */

Objects_Control *_Objects_Allocate_by_index(
  Objects_Information *information,
  int                  the_index,
  uint16_t             sizeof_control
)
{
  Objects_Control *the_object;

  if ( the_index > 0 && information->maximum >= the_index ) {
    the_object = information->local_table[ the_index ];
    if ( the_object )
      return NULL;

    /* XXX
     *  This whole section of code needs to be evaluated for unlimited objects.
     *    +  The 0 should be dealt with more properly so we can autoextend.
     *    +  The pointer arithmetic is probably too expensive but is likely
     *       necessary especially on targets with 16 bit offset limits.
     *    +  etc.
     */

    the_object = (Objects_Control *) _Addresses_Add_offset(
      information->object_blocks[ 0 ],
      (sizeof_control * (the_index - 1))
    );
    _Chain_Extract( &the_object->Node );

    return the_object;
  }

  /*
   *  Autoextend will have to be thought out as it applies
   *  to user assigned indices.
   */

  return NULL;
}
