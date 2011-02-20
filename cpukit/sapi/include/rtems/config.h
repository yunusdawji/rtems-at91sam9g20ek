/**
 * @file rtems/config.h
 */

/*
 *  This include file contains the table of user defined configuration
 *  parameters.
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: config.h,v 1.51 2009/11/29 13:51:51 ralf Exp $
 */

#ifndef _RTEMS_CONFIG_H
#define _RTEMS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Unlimited object support. Changes the configuration table entry for POSIX
 *  or RTEMS APIs to bounded only by the memory of the work-space.
 *
 *  Use the macro to define the resource unlimited before placing in
 *  the configuration table.
 */

#include <rtems/score/object.h>
#define RTEMS_UNLIMITED_OBJECTS OBJECTS_UNLIMITED_OBJECTS

#define rtems_resource_unlimited(resource) \
  ( resource | RTEMS_UNLIMITED_OBJECTS )

/*
 *  This is kind of kludgy but it allows targets to totally ignore the
 *  optional APIs like POSIX and ITRON safely.
 */

#ifdef RTEMS_POSIX_API
#include <rtems/posix/config.h>
#else
typedef void *posix_api_configuration_table;
#endif

#ifdef RTEMS_ITRON_API
#include <rtems/itron.h>
#include <rtems/itron/config.h>
#else
typedef void *itron_api_configuration_table;
#endif

#include <rtems/rtems/config.h>

#include <rtems/extension.h>
#include <rtems/io.h>
#if defined(RTEMS_MULTIPROCESSING)
#include <rtems/score/mpci.h>
#endif

#if defined(RTEMS_MULTIPROCESSING)
/*
 *  The following records define the Multiprocessor Configuration
 *  Table.  This table defines the multiprocessor system
 *  characteristics which must be known by RTEMS in a multiprocessor
 *  system.
 */
typedef struct {
  /** This is the local node number. */
  uint32_t            node;
  /** This is the maximum number of nodes in system. */
  uint32_t            maximum_nodes;
  /** This is the maximum number of global objects. */
  uint32_t            maximum_global_objects;
  /** This is the maximum number of proxies. */
  uint32_t            maximum_proxies;

  /** The MPCI Receive server is assumed to have a stack of at least
   *  minimum stack size.  This field specifies the amount of extra
   *  stack this task will be given in bytes.
   */
  uint32_t            extra_mpci_receive_server_stack;

  /** This is a pointer to User/BSP provided MPCI Table. */
  rtems_mpci_table   *User_mpci_table;
} rtems_multiprocessing_table;
#endif

/*
 *  The following records define the Configuration Table.  The
 *  information contained in this table is required in all
 *  RTEMS systems, whether single or multiprocessor.  This
 *  table primarily defines the following:
 *
 *     + location and size of the RTEMS Workspace
 *     + microseconds per clock tick
 *     + clock ticks per task timeslice
 *     + required number of each object type for each API configured
 */
typedef struct {
  /** This field specifies the base address of the RTEMS Workspace.
   */
  void                          *work_space_start;

  /** This field specifies the size in bytes of the RTEMS Workspace.
   */
  uintptr_t                      work_space_size;

  /** This field specifies the maximum number of dynamically installed
   *  used extensions.
   */
  uint32_t                       maximum_extensions;

  /** This field specifies the number of microseconds which elapse
   *  between clock ticks.  This is the basis for RTEMS timing.
   */
  uint32_t                       microseconds_per_tick;

  /** This field specifies the number of ticks in each task's timeslice.
   */
  uint32_t                       ticks_per_timeslice;

  /** This element points to the BSP's optional idle task which may override
   *  the default one provided with RTEMS.
   */
  Thread                       (*idle_task)( uintptr_t );

  /** This field specifies the size of the IDLE task's stack.  If less than or
   *  equal to the minimum stack size, then the IDLE task will have the minimum
   *  stack size.
   */
  uint32_t                       idle_task_stack_size;

  /** This field specifies the size of the interrupt stack.  If less than or
   *  equal to the minimum stack size, then the interrupt stack will be of
   *  minimum stack size.
   */
  uint32_t                       interrupt_stack_size;

  /** The BSP may want to provide it's own stack allocation routines.
   *  In this case, the BSP will provide this stack allocation hook.
   */
  void *                       (*stack_allocate_hook)( size_t );

  /** The BSP may want to provide it's own stack free routines.
   *  In this case, the BSP will provide this stack free hook.
   */
  void                         (*stack_free_hook)( void *);

  /** If this element is TRUE, then RTEMS will zero the Executive Workspace.
   *  When this element is FALSE, it is assumed that the BSP or invoking
   *  environment has ensured that memory was cleared before RTEMS was
   *  invoked.
   */
  bool                           do_zero_of_workspace;

  uint32_t                       maximum_drivers;
  uint32_t                       number_of_device_drivers;
  rtems_driver_address_table    *Device_driver_table;
  uint32_t                       number_of_initial_extensions;
  rtems_extensions_table        *User_extension_table;
  #if defined(RTEMS_MULTIPROCESSING)
    rtems_multiprocessing_table   *User_multiprocessing_table;
  #endif
} rtems_configuration_table;

/**
 *   This is the configuration table generated by confdefs.h.
 */
extern rtems_configuration_table  Configuration;

#if defined(RTEMS_MULTIPROCESSING)
  /**
   *   This points to the multiprocessing configuration table.
   */
  SAPI_EXTERN rtems_multiprocessing_table  *_Configuration_MP_table;
#endif

#if defined(RTEMS_MULTIPROCESSING)
  /**
   *  @brief RTEMS Multiprocessing Configuration Table
   *
   *  This is the RTEMS Multiprocessing Configuration Table expected to
   *  be generated by confdefs.h.
   */
  extern rtems_multiprocessing_table  Multiprocessing_configuration;
#endif


/*
 *  Some handy macros to avoid dependencies on either the BSP
 *  or the exact format of the configuration table.
 */

#define rtems_configuration_get_table() \
        (&Configuration)

#define rtems_configuration_get_work_space_start() \
        (Configuration.work_space_start)

#define rtems_configuration_get_work_space_size() \
        (Configuration.work_space_size)

#define rtems_configuration_get_maximum_extensions() \
        (Configuration.maximum_extensions)

#define rtems_configuration_get_microseconds_per_tick() \
        (Configuration.microseconds_per_tick)
#define rtems_configuration_get_milliseconds_per_tick() \
        (Configuration.microseconds_per_tick / 1000)
#define rtems_configuration_get_nanoseconds_per_tick() \
      (Configuration.microseconds_per_tick * 1000)

#define rtems_configuration_get_ticks_per_timeslice() \
        (Configuration.ticks_per_timeslice)

#define rtems_configuration_get_idle_task() \
        (Configuration.idle_task)

#define rtems_configuration_get_idle_task_stack_size() \
        (Configuration.idle_task_stack_size)

/* XXX We need to get this from the generated table
 *     since BSPs need it before the pointer is set.
 *     Eventually all should be done this way.
 */
extern rtems_configuration_table    Configuration;

#define rtems_configuration_get_interrupt_stack_size() \
        (Configuration.interrupt_stack_size)

#define rtems_configuration_get_stack_allocate_hook() \
        (Configuration.stack_allocate_hook)

#define rtems_configuration_get_stack_free_hook() \
        (Configuration.stack_free_hook)

/**
  * This macro assists in accessing the field which indicates whether
  * RTEMS is responsible for zeroing the Executive Workspace.
  */
#define rtems_configuration_get_do_zero_of_workspace() \
   (Configuration.do_zero_of_workspace)

#define rtems_configuration_get_number_of_device_drivers() \
        (Configuration.number_of_device_drivers)

#define rtems_configuration_get_device_driver_table() \
        (Configuration.Device_driver_table)

#define rtems_configuration_get_number_of_initial_extensions() \
        (Configuration.number_of_initial_extensions)

#define rtems_configuration_get_user_extension_table() \
        (Configuration.User_extension_table)

#if defined(RTEMS_MULTIPROCESSING)
  #define rtems_configuration_get_user_multiprocessing_table() \
	  (Configuration.User_multiprocessing_table)
#else
  #define rtems_configuration_get_user_multiprocessing_table() NULL
#endif

#define rtems_configuration_get_rtems_api_configuration() \
        (&Configuration_RTEMS_API)

#define rtems_configuration_get_posix_api_configuration() \
        (&Configuration_POSIX_API)

#define rtems_configuration_get_itron_api_configuration() \
        (&Configuration_ITRON_API)

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
