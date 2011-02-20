/** 
 *  @file  rtems/score/corespinlock.inl
 *
 *  This include file contains all of the inlined routines associated
 *  with the SuperCore spinlock.
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: corespinlock.inl,v 1.5 2008/12/22 09:22:17 ralf Exp $
 */

#ifndef _RTEMS_SCORE_CORESPINLOCK_H
# error "Never use <rtems/score/corespinlock.inl> directly; include <rtems/score/corespinlock.h> instead."
#endif

#ifndef _RTEMS_SCORE_CORESPINLOCK_INL
#define _RTEMS_SCORE_CORESPINLOCK_INL

/**
 *  @addtogroup ScoreSpinlock 
 *  @{
 */

/**
 *
 *  This method is used to determine if the spinlock is available or not.
 *
 *  @param[in] the_spinlock will be checked
 *
 *  @return This method will return true if the spinlock is busy
 *          and false otherwise.
 */
RTEMS_INLINE_ROUTINE bool _CORE_spinlock_Is_busy(
  CORE_spinlock_Control  *the_spinlock
)
{
  return (the_spinlock->users != 0);
}

/**@}*/

#endif
/* end of include file */
