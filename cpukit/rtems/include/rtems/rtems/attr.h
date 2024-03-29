/**
 * @file rtems/rtems/attr.h
 *
 *  This include file contains all information about the Object Attributes
 *  Handler.
 */

/*  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: attr.h,v 1.26 2009/11/29 11:55:14 ralf Exp $
 */

#ifndef _RTEMS_RTEMS_ATTR_H
#define _RTEMS_RTEMS_ATTR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @defgroup ClassicAttributes Attributes
 *
 *  @ingroup ClassicRTEMS
 *
 *  This encapsulates functionality which defines and manages the
 *  set of Classic API object attributes.
 */
/**@{*/

/**
 *  This defines the type used to contain Classic API attributes.  These
 *  are primarily used when creating objects.
 */
typedef uint32_t   rtems_attribute;

/** This is the default value for an attribute set. */

#define RTEMS_DEFAULT_ATTRIBUTES  0x00000000

/**
 *  This is the attribute constant to indicate local resource.
 */
#define RTEMS_LOCAL               0x00000000

/**
 *  This is the attribute constant to indicate global resource.
 */
#define RTEMS_GLOBAL              0x00000002

/**
 *  This is the attribute constant which reflects that blocking
 *  tasks will be managed using FIFO discipline.
 */
#define RTEMS_FIFO                0x00000000

/**
 *  This is the attribute constant which reflects that blocking
 *  tasks will be managed using task priority discipline.
 */
#define RTEMS_PRIORITY            0x00000004

/******************** RTEMS Task Specific Attributes *********************/

/**
 *  This attribute constant indicates that the task will not use the
 *  floating point hardware.  If the architecture permits it, then
 *  the FPU will be disabled when the task is executing.
 */
#define RTEMS_NO_FLOATING_POINT   0x00000000

/**
 *  This attribute constant indicates that the task will use the
 *  floating point hardware.  There will be a floating point
 *  context associated with this task.
 */
#define RTEMS_FLOATING_POINT      0x00000001

/***************** RTEMS Semaphore Specific Attributes ********************/

/**
 *  This is the mask for the attribute bits associated with the
 *  Classic API Semaphore Manager.
 */
#define RTEMS_SEMAPHORE_CLASS         0x00000030

/**
 *  This attribute constant indicates that the Classic API Semaphore
 *  instance created will be a counting semaphore.
 */
#define RTEMS_COUNTING_SEMAPHORE      0x00000000

/**
 *  This attribute constant indicates that the Classic API Semaphore
 *  instance created will be a proper binary semaphore or mutex.
 */
#define RTEMS_BINARY_SEMAPHORE        0x00000010

/**
 *  This attribute constant indicates that the Classic API Semaphore
 *  instance created will be a simple binary semaphore.
 */
#define RTEMS_SIMPLE_BINARY_SEMAPHORE 0x00000020

/**
 *  This attribute constant indicates that the Classic API Semaphore
 *  instance created will NOT use the Priority Inheritance Protocol.
 */
#define RTEMS_NO_INHERIT_PRIORITY     0x00000000

/**
 *  This attribute constant indicates that the Classic API Semaphore
 *  instance created will use the Priority Inheritance Protocol.
 *
 *  @note The semaphore instance must be a binary semaphore.
 */
#define RTEMS_INHERIT_PRIORITY        0x00000040

/**
 *  This attribute constant indicates that the Classic API Semaphore
 *  instance created will NOT use the Priority Ceiling Protocol.
 */
#define RTEMS_NO_PRIORITY_CEILING     0x00000000

/**
 *  This attribute constant indicates that the Classic API Semaphore
 *  instance created will use the Priority Ceiling Protocol.
 *
 *  @note The semaphore instance must be a binary semaphore.
 */
#define RTEMS_PRIORITY_CEILING        0x00000080

/******************** RTEMS Barrier Specific Attributes ********************/

/**
 *  This attribute constant indicates that the Classic API Barrier
 *  instance created will use an automatic release protocol.
 */
#define RTEMS_BARRIER_AUTOMATIC_RELEASE 0x00000010

/**
 *  This attribute constant indicates that the Classic API Barrier
 *  instance created will use the manual release protocol.
 */
#define RTEMS_BARRIER_MANUAL_RELEASE    0x00000000

/**************** RTEMS Internal Task Specific Attributes ****************/

/**
 *  This attribute constant indicates that the task was created
 *  by the application using normal Classic API methods.
 */
#define RTEMS_APPLICATION_TASK        0x00000000

/**
 *  This attribute constant indicates that the task was created
 *  by RTEMS as a support task.
 */
#define RTEMS_SYSTEM_TASK             0x00008000

/****************** Forced Attributes in Configuration ****************/

/**
 *  This attribute constant indicates the attributes that are not
 *  supportable given the hardware configuration.
 */
#if ( CPU_HARDWARE_FP == TRUE ) || ( CPU_SOFTWARE_FP == TRUE )
#define ATTRIBUTES_NOT_SUPPORTED       0
#else
#define ATTRIBUTES_NOT_SUPPORTED       RTEMS_FLOATING_POINT
#endif

/**
 *  This attribute constant indicates the attributes that are
 *  required given the hardware configuration.
 */
#if ( CPU_ALL_TASKS_ARE_FP == TRUE )
#define ATTRIBUTES_REQUIRED            RTEMS_FLOATING_POINT
#else
#define ATTRIBUTES_REQUIRED            0
#endif

#ifndef __RTEMS_APPLICATION__
#include <rtems/rtems/attr.inl>
#endif

#ifdef __cplusplus
}
#endif

/**@}*/

#endif
/* end of include file */
