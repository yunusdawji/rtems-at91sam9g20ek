/**
 * @file rtems/itron/semaphore.h
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: semaphore.h,v 1.9 2008/12/17 22:12:23 joel Exp $
 */

#ifndef _RTEMS_ITRON_SEMAPHORE_H
#define _RTEMS_ITRON_SEMAPHORE_H

#include <rtems/itron/object.h>
#include <rtems/score/coresem.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  The following defines the control block used to manage each semaphore.
 */

typedef struct {
  ITRON_Objects_Control   Object;
  bool                    is_priority_blocking;
  CORE_semaphore_Control  semaphore;
}   ITRON_Semaphore_Control;

/*
 *  The following defines the information control block used to manage
 *  this class of objects.
 */

ITRON_EXTERN Objects_Information  _ITRON_Semaphore_Information;

/*
 *  _ITRON_Semaphore_Manager_initialization
 *
 *  DESCRIPTION:
 *
 *  This routine performs the initialization necessary for this manager.
 */

void _ITRON_Semaphore_Manager_initialization(void);

#include <rtems/itron/semaphore.inl>

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
