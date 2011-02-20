/**
 *  @file  rtems/score/priority.h
 *
 *  This include file contains all thread priority manipulation routines.
 *  This Handler provides mechanisms which can be used to
 *  initialize and manipulate thread priorities.
 */

/*
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: priority.h,v 1.25.2.1 2010/06/14 06:09:11 ralf Exp $
 */

#ifndef _RTEMS_SCORE_PRIORITY_H
#define _RTEMS_SCORE_PRIORITY_H

/**
 *  @defgroup ScorePriority Priority Handler
 *
 *  This handler encapsulates functionality which is used to manage
 *  thread priorities.  At the SuperCore level 256 priority levels
 *  are supported with lower numbers representing logically more important
 *  threads.  The priority level 0 is reserved for internal RTEMS use.
 *  Typically it is assigned to threads which defer internal RTEMS
 *  actions from an interrupt to thread level to improve interrupt response.
 *  Priority level 255 is assigned to the IDLE thread and really should not
 *  be used by application threads.  The default IDLE thread implementation
 *  is an infinite "branch to self" loop which never yields to other threads
 *  at the same priority.
 */
/**@{*/

/*
 * Processor specific information.
 */
#include <rtems/score/cpu.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  The following type defines the control block used to manage
 *  thread priorities.
 *
 *  @note Priority 0 is reserved for internal threads only.
 */
typedef uint32_t   Priority_Control;

/** This defines the highest (most important) thread priority. */
#define PRIORITY_MINIMUM      0

/** This defines the default lowest (least important) thread priority. */
#if defined (CPU_PRIORITY_MAXIMUM)
  #define PRIORITY_DEFAULT_MAXIMUM      CPU_PRIORITY_MAXIMUM
#else
  #define PRIORITY_DEFAULT_MAXIMUM      255
#endif

/** This defines the lowest (least important) thread priority. */
#define PRIORITY_MAXIMUM      rtems_maximum_priority

/**
 *  The following record defines the information associated with
 *  each thread to manage its interaction with the priority bit maps.
 */
typedef struct {
  /** This is the address of minor bit map slot. */
  Priority_Bit_map_control *minor;
  /** This is the priority bit map ready mask. */
  Priority_Bit_map_control  ready_major;
  /** This is the priority bit map ready mask. */
  Priority_Bit_map_control  ready_minor;
  /** This is the priority bit map block mask. */
  Priority_Bit_map_control  block_major;
  /** This is the priority bit map block mask. */
  Priority_Bit_map_control  block_minor;
}   Priority_Information;

/**
 *  This variable contains the configured number of priorities
 */
extern uint8_t rtems_maximum_priority;

/**
 *  Each sixteen bit entry in this array is associated with one of
 *  the sixteen entries in the Priority Bit map.
 */
SCORE_EXTERN volatile Priority_Bit_map_control _Priority_Major_bit_map;

/** Each bit in the Priority Bitmap indicates whether or not there are
 *  threads ready at a particular priority.  The mapping of
 *  individual priority levels to particular bits is processor
 *  dependent as is the value of each bit used to indicate that
 *  threads are ready at that priority.
 */
SCORE_EXTERN Priority_Bit_map_control
               _Priority_Bit_map[16] CPU_STRUCTURE_ALIGNMENT;

/*
 *  The definition of the Priority_Bit_map_control type is CPU dependent.
 *
 */

#if ( CPU_USE_GENERIC_BITFIELD_CODE == FALSE )
/**
 *  This method returns the priority bit mask for the specified major
 *  or minor bit number.
 *
 *  @param[in] _bit_number is the bit number for which we need a mask
 *
 *  @return the priority bit mask
 *
 *  @note This may simply be a pass through to a CPU dependent implementation.
 */
#define _Priority_Mask( _bit_number ) \
  _CPU_Priority_Mask( _bit_number )
#endif

#if ( CPU_USE_GENERIC_BITFIELD_CODE == FALSE )
/**
 *  This method returns the bit index position for the specified priority.
 *
 *  @param[in] _priority is the priority for which we need the index.
 *
 *  @return This method returns the array index into the priority bit map.
 *
 *  @note This may simply be a pass through to a CPU dependent implementation.
 */
#define _Priority_Bits_index( _priority ) \
  _CPU_Priority_bits_index( _priority )
#endif

#ifndef __RTEMS_APPLICATION__
#include <rtems/score/priority.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
