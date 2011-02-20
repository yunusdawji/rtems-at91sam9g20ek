/**
 * @file rtems/posix/mqueue.inl
 */

/*  rtems/posix/mqueue.inl
 *
 *  This include file contains the static inline implementation of the private 
 *  inlined routines for POSIX Message Queue.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: mqueue.inl,v 1.17 2009/01/05 20:26:01 joel Exp $
 */
 
#ifndef _RTEMS_POSIX_MQUEUE_H
# error "Never use <rtems/posix/mqueue.inl> directly; include <rtems/posix/mqueue.h> instead."
#endif

#ifndef _RTEMS_POSIX_MQUEUE_INL
#define _RTEMS_POSIX_MQUEUE_INL
 
/*PAGE
 *
 *  _POSIX_Message_queue_Allocate
 */
 
RTEMS_INLINE_ROUTINE
  POSIX_Message_queue_Control *_POSIX_Message_queue_Allocate( void )
{
  return (POSIX_Message_queue_Control *)
    _Objects_Allocate( &_POSIX_Message_queue_Information );
}
 
/*PAGE
 *
 *  _POSIX_Message_queue_Allocate_fd
 */
 
RTEMS_INLINE_ROUTINE POSIX_Message_queue_Control_fd *
  _POSIX_Message_queue_Allocate_fd( void )
{
  return (POSIX_Message_queue_Control_fd *)
    _Objects_Allocate( &_POSIX_Message_queue_Information_fds );
}
 
/*PAGE
 *
 *  _POSIX_Message_queue_Free
 */
 
RTEMS_INLINE_ROUTINE void _POSIX_Message_queue_Free (
  POSIX_Message_queue_Control *the_mq
)
{
  _Objects_Free( &_POSIX_Message_queue_Information, &the_mq->Object );
}

/*PAGE
 *
 *  _POSIX_Message_queue_Free_fd
 */
 
RTEMS_INLINE_ROUTINE void _POSIX_Message_queue_Free_fd (
  POSIX_Message_queue_Control_fd *the_mq_fd
)
{
  _Objects_Free( &_POSIX_Message_queue_Information_fds, &the_mq_fd->Object );
}

/*PAGE
 *
 *  _POSIX_Message_queue_Namespace_remove
 */
 
RTEMS_INLINE_ROUTINE void _POSIX_Message_queue_Namespace_remove (
  POSIX_Message_queue_Control *the_mq
)
{
  _Objects_Namespace_remove( 
    &_POSIX_Message_queue_Information, &the_mq->Object );
}
 
/*PAGE
 *
 *  _POSIX_Message_queue_Get
 */
 
RTEMS_INLINE_ROUTINE POSIX_Message_queue_Control *_POSIX_Message_queue_Get (
  Objects_Id         id,
  Objects_Locations *location
)
{
  return (POSIX_Message_queue_Control *)
    _Objects_Get( &_POSIX_Message_queue_Information, id, location );
}
 
/*PAGE
 *
 *  _POSIX_Message_queue_Get_fd
 */
 
RTEMS_INLINE_ROUTINE POSIX_Message_queue_Control_fd *_POSIX_Message_queue_Get_fd (
  mqd_t              id,
  Objects_Locations *location
)
{
  return (POSIX_Message_queue_Control_fd *) _Objects_Get(
    &_POSIX_Message_queue_Information_fds,
    (Objects_Id)id,
    location
  );
}
 
/*PAGE
 *
 *  _POSIX_Message_queue_Is_null
 */
 
RTEMS_INLINE_ROUTINE bool _POSIX_Message_queue_Is_null (
  POSIX_Message_queue_Control *the_mq
)
{
  return !the_mq;
}

/*PAGE
 *
 *  _POSIX_Message_queue_Priority_to_core
 */
 
RTEMS_INLINE_ROUTINE CORE_message_queue_Submit_types _POSIX_Message_queue_Priority_to_core(
  unsigned int priority
)
{
  return priority * -1;
}

/*
 *  _POSIX_Message_queue_Priority_from_core
 * 
 *  DESCRIPTION:
 *
 *  XXX
 */
 
RTEMS_INLINE_ROUTINE unsigned int _POSIX_Message_queue_Priority_from_core(
  CORE_message_queue_Submit_types priority
)
{
  /* absolute value without a library dependency */
  return ((priority >= 0) ? priority : -priority);
}

#endif
/*  end of include file */
