/**
 *  @file  rtems/score/isr.h
 *
 *  This include file contains all the constants and structures associated
 *  with the management of processor interrupt levels.  This handler
 *  supports interrupt critical sections, vectoring of user interrupt
 *  handlers, nesting of interrupts, and manipulating interrupt levels.
 */

/*
 *  COPYRIGHT (c) 1989-2006.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: isr.h,v 1.31 2009/11/28 05:58:54 ralf Exp $
 */

#ifndef _RTEMS_SCORE_ISR_H
#define _RTEMS_SCORE_ISR_H

/**
 *  @defgroup ScoreISR ISR Handler
 *
 *  This handler encapsulates functionality which provides the foundation
 *  ISR services used in all of the APIs supported by RTEMS.
 */
/**@{*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  The following type defines the control block used to manage
 *  the interrupt level portion of the status register.
 */
typedef uint32_t   ISR_Level;

/**
 *  The following type defines the type used to manage the vectors.
 */
typedef uint32_t   ISR_Vector_number;

/**
 *  Return type for ISR Handler
 */
typedef void ISR_Handler;

/**
 *  Pointer to an ISR Handler
 */
#if (CPU_ISR_PASSES_FRAME_POINTER == 1)
typedef ISR_Handler ( *ISR_Handler_entry )(
                 ISR_Vector_number,
                 CPU_Interrupt_frame *
             );
#else
typedef ISR_Handler ( *ISR_Handler_entry )(
                 ISR_Vector_number
             );
#endif

/**
 *  This constant promotes out the number of vectors truly supported by
 *  the current CPU being used.  This is usually the number of distinct vectors
 *  the cpu can vector.
 */
#define ISR_NUMBER_OF_VECTORS                CPU_INTERRUPT_NUMBER_OF_VECTORS

/**
 *  This constant promotes out the highest valid interrupt vector number.
 */
#define ISR_INTERRUPT_MAXIMUM_VECTOR_NUMBER  CPU_INTERRUPT_MAXIMUM_VECTOR_NUMBER

/**
 *  The following is true if signals have been sent to the currently
 *  executing thread by an ISR handler.
 */
SCORE_EXTERN bool       _ISR_Signals_to_thread_executing;

/**
 *  The following contains the interrupt service routine nest level.
 *  When this variable is zero, a thread is executing.
 */
SCORE_EXTERN volatile uint32_t   _ISR_Nest_level;

#if (CPU_SIMPLE_VECTORED_INTERRUPTS == TRUE)
/**
 *  The following declares the Vector Table.  Application
 *  interrupt service routines are vectored by the ISR Handler via this table.
 */
SCORE_EXTERN ISR_Handler_entry *_ISR_Vector_table;
#endif

/**
 *  This routine performs the initialization necessary for this handler.
 */
void _ISR_Handler_initialization ( void );

/**
 *  This routine disables all interrupts so that a critical section
 *  of code can be executing without being interrupted.  Upon return,
 *  the argument _level will contain the previous interrupt mask level.
 */
#define _ISR_Disable( _level ) \
  do { \
    _CPU_ISR_Disable( _level ); \
    RTEMS_COMPILER_MEMORY_BARRIER(); \
  } while (0)

/**
 *  This routine enables interrupts to the previous interrupt mask
 *  LEVEL.  It is used at the end of a critical section of code to
 *  enable interrupts so they can be processed again.
 */
#define _ISR_Enable( _level ) \
  do { \
    RTEMS_COMPILER_MEMORY_BARRIER(); \
    _CPU_ISR_Enable( _level ); \
  } while (0)

/**
 *  This routine temporarily enables interrupts to the previous
 *  interrupt mask level and then disables all interrupts so that
 *  the caller can continue into the second part of a critical
 *  section.  This routine is used to temporarily enable interrupts
 *  during a long critical section.  It is used in long sections of
 *  critical code when a point is reached at which interrupts can
 *  be temporarily enabled.  Deciding where to flash interrupts
 *  in a long critical section is often difficult and the point
 *  must be selected with care to ensure that the critical section
 *  properly protects itself.
 */
#define _ISR_Flash( _level ) \
  do { \
    RTEMS_COMPILER_MEMORY_BARRIER(); \
    _CPU_ISR_Flash( _level ); \
    RTEMS_COMPILER_MEMORY_BARRIER(); \
  } while (0)

/**
 *  This routine installs new_handler as the interrupt service routine
 *  for the specified vector.  The previous interrupt service routine is
 *  returned as old_handler.
 */
#define _ISR_Install_vector( _vector, _new_handler, _old_handler ) \
  _CPU_ISR_install_vector( _vector, _new_handler, _old_handler )

/**
 *  This routine returns the current interrupt level.
 */
#define _ISR_Get_level() \
        _CPU_ISR_Get_level()

/**
 *  This routine sets the current interrupt level to that specified
 *  by new_level.  The new interrupt level is effective when the
 *  routine exits.
 */
#define _ISR_Set_level( _new_level ) \
	  do { \
		RTEMS_COMPILER_MEMORY_BARRIER();  \
		_CPU_ISR_Set_level( _new_level ); \
		RTEMS_COMPILER_MEMORY_BARRIER();  \
	} while (0)


/**
 *  This routine is the interrupt dispatcher.  ALL interrupts
 *  are vectored to this routine so that minimal context can be saved
 *  and setup performed before the application's high-level language
 *  interrupt service routine is invoked.   After the application's
 *  interrupt service routine returns control to this routine, it
 *  will determine if a thread dispatch is necessary.  If so, it will
 *  ensure that the necessary thread scheduling operations are
 *  performed when the outermost interrupt service routine exits.
 *
 *  @note  Implemented in assembly language.
 */
void _ISR_Handler( void );

/**
 *  This routine provides a wrapper so that the routine
 *  @ref _Thread_Dispatch can be invoked when a reschedule is necessary
 *  at the end of the outermost interrupt service routine.  This
 *  wrapper is necessary to establish the processor context needed
 *  by _Thread_Dispatch and to save the processor context which is
 *  corrupted by _Thread_Dispatch.  This context typically consists
 *  of registers which are not preserved across routine invocations.
 *
 *  @note  Implemented in assembly language.
 */
void _ISR_Dispatch( void );

/**
 *  Invokes the thread dispatcher or signal extension if necessary.
 *
 *  It should be called at the end of interrupt processing.  The interrupt nest
 *  level must be zero before calling this routine.
 *
 *  This is a high level replacement of _ISR_Dispatch().  It must be invoked
 *  within an environment such that a call to _Thread_Dispatch() is allowed.
 */
void _ISR_Thread_dispatch( void );

/**
 *  This function returns true if the processor is currently servicing
 *  and interrupt and false otherwise.   A return value of true indicates
 *  that the caller is an interrupt service routine, NOT a thread.  The
 */
#if (CPU_PROVIDES_ISR_IS_IN_PROGRESS == TRUE)
bool _ISR_Is_in_progress( void );
#else
#define _ISR_Is_in_progress() \
        (_ISR_Nest_level != 0)
#endif

#include <rtems/score/isr.inl>

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
