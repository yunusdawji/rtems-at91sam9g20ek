/**
 * @file
 *
 * @ingroup ScoreProtHeap
 *
 * @brief Protected Heap Handler implementation.
 */

/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: pheapextend.c,v 1.4 2009/09/06 15:24:07 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/protectedheap.h>

bool _Protected_heap_Extend(
  Heap_Control *the_heap,
  void         *starting_address,
  uintptr_t     size
)
{
  Heap_Extend_status status;
  uintptr_t           amount_extended;

  _RTEMS_Lock_allocator();
    status = _Heap_Extend(the_heap, starting_address, size, &amount_extended);
  _RTEMS_Unlock_allocator();
  return (status == HEAP_EXTEND_SUCCESSFUL);
}

