/**
 * @file rtems/itron/config.h
 */

/*  config.h
 *
 *  This include file contains the table of user defined configuration
 *  parameters specific for the ITRON API.
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: config.h,v 1.6 2008/12/17 22:12:23 joel Exp $
 */

#ifndef _RTEMS_ITRON_CONFIG_H
#define _RTEMS_ITRON_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  XXX
 *
 *  The following records define the Configuration Table.  The
 *  information contained in this table is required in all
 *  RTEMS systems, whether single or multiprocessor.  This
 *  table primarily defines the following:
 *
 *     + required number of each object type
 */

/*
 *  For now, we are only allowing the user to specify the entry point
 *  and stack size for ITRON initialization threads.
 */

typedef struct {
  ID          id;
  T_CTSK      attributes;
} itron_initialization_tasks_table;

typedef struct {
  int                                 maximum_tasks;
  int                                 maximum_semaphores;
  int                                 maximum_eventflags;
  int                                 maximum_mailboxes;
  int                                 maximum_message_buffers;
  int                                 maximum_ports;
  int                                 maximum_memory_pools;
  int                                 maximum_fixed_memory_pools;
  int                                 number_of_initialization_tasks;
  itron_initialization_tasks_table   *User_initialization_tasks_table;
} itron_api_configuration_table;

/**
 *  @brief ITRON API Configuration Table
 *
 *  This is the ITRON API Configuration Table expected to be generated
 *  by confdefs.h.
 */
extern itron_api_configuration_table Configuration_ITRON_API;

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
