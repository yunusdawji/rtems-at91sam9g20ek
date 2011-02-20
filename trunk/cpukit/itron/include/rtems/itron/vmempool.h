/**
 * @file rtems/itron/vmempool.h
 */

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: vmempool.h,v 1.8 2008/12/17 22:12:23 joel Exp $
 */

#ifndef _RTEMS_ITRON_VMEMPOOL_H
#define _RTEMS_ITRON_VMEMPOOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/itron/object.h>

/*
 *  The following defines the control block used to manage each variable
 *  memory pool.
 */

typedef struct {
  ITRON_Objects_Control   Object;
  uint32_t                XXX_more_stuff_goes_here;
}   ITRON_Variable_memory_pool_Control;

/*
 *  The following defines the information control block used to manage
 *  this class of objects.
 */

ITRON_EXTERN Objects_Information  _ITRON_Variable_memory_pool_Information;

/*
 *  _ITRON_Variable_memory_pool_Manager_initialization
 *
 *  DESCRIPTION:
 *
 *  This routine performs the initialization necessary for this manager.
 */

void _ITRON_Variable_memory_pool_Manager_initialization(void);

/*
 *  XXX insert private stuff here
 */

#include <rtems/itron/vmempool.inl>

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
