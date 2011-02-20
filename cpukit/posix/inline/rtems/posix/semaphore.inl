/**
 * @file rtems/posix/semaphore.inl
 */

/*  rtems/posix/semaphore.inl
 *
 *  This include file contains the static inline implementation of the private 
 *  inlined routines for POSIX Semaphores.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: semaphore.inl,v 1.16 2009/01/05 20:26:01 joel Exp $
 */
 
#ifndef _RTEMS_POSIX_SEMAPHORE_H
# error "Never use <rtems/posix/semaphore.inl> directly; include <rtems/posix/semaphore.h> instead."
#endif

#ifndef _RTEMS_POSIX_SEMAPHORE_INL
#define _RTEMS_POSIX_SEMAPHORE_INL
 
/*PAGE
 *
 *  _POSIX_Semaphore_Allocate
 */
 
RTEMS_INLINE_ROUTINE POSIX_Semaphore_Control *_POSIX_Semaphore_Allocate( void )
{
  return (POSIX_Semaphore_Control *)
    _Objects_Allocate( &_POSIX_Semaphore_Information );
}
 
/*PAGE
 *
 *  _POSIX_Semaphore_Free
 */
 
RTEMS_INLINE_ROUTINE void _POSIX_Semaphore_Free (
  POSIX_Semaphore_Control *the_semaphore
)
{
  _Objects_Free( &_POSIX_Semaphore_Information, &the_semaphore->Object );
}
 
/*PAGE
 *
 *  _POSIX_Semaphore_Namespace_remove
 */
 
RTEMS_INLINE_ROUTINE void _POSIX_Semaphore_Namespace_remove (
  POSIX_Semaphore_Control *the_semaphore
)
{
  _Objects_Namespace_remove( 
    &_POSIX_Semaphore_Information, &the_semaphore->Object );
}
 


/*PAGE
 *
 *  _POSIX_Semaphore_Get
 */
RTEMS_INLINE_ROUTINE POSIX_Semaphore_Control *_POSIX_Semaphore_Get (
  sem_t             *id,
  Objects_Locations *location
)
{
  return (POSIX_Semaphore_Control *)
    _Objects_Get( &_POSIX_Semaphore_Information, (Objects_Id)*id, location );
}
 
/*PAGE
 *
 *  _POSIX_Semaphore_Is_null
 */
 
RTEMS_INLINE_ROUTINE bool _POSIX_Semaphore_Is_null (
  POSIX_Semaphore_Control *the_semaphore
)
{
  return !the_semaphore;
}

#endif
/*  end of include file */

