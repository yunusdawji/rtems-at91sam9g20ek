/**
 * @file
 *
 * @ingroup bsp_bootcard
 *
 * @brief Standard system startup.
 */

/*
 * Copyright (c) 2008
 * Embedded Brains GmbH
 * Obere Lagerstr. 30
 * D-82178 Puchheim
 * Germany
 * rtems@embedded-brains.de
 *
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rtems.com/license/LICENSE.
 *
 * $Id: bootcard.h,v 1.9 2010/04/30 11:17:49 sh Exp $
 */

/**
 * @defgroup bsp_kit Board Support Package
 *
 * @brief Board support package dependent code.
 */

/**
 * @defgroup bsp_bootcard Bootcard
 *
 * @ingroup bsp_kit
 *
 * @brief Standard system startup.
 *
 * @{
 */

#ifndef LIBBSP_SHARED_BOOTCARD_H
#define LIBBSP_SHARED_BOOTCARD_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include <bspopts.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Global pointer to the command line of boot_card().
 */
extern const char *bsp_boot_cmdline;

void bsp_start(void);

void bsp_pretasking_hook(void);

void bsp_predriver_hook(void);

void bsp_postdriver_hook(void);

void bsp_cleanup(void);

void bsp_reset(void);

/**
 * @brief Should be used as the heap begin address in bsp_get_work_area() if
 * the heap area is contained in the work area.
 */
#define BSP_BOOTCARD_HEAP_USES_WORK_AREA NULL

/**
 * @brief Should be used to request the default heap size in bsp_get_work_area().
 *
 * In case that the heap area is contained in the work area this heap size
 * value indicates that the area outside the work space should be used as heap
 * space.
 */
#define BSP_BOOTCARD_HEAP_SIZE_DEFAULT 0

void bsp_get_work_area(
  void      **work_area_begin,
  uintptr_t  *work_area_size,
  void      **heap_begin,
  uintptr_t  *heap_size
);

/**
 * @brief Standard system initialization procedure.
 *
 * You may pass a command line in @a cmdline.  It is later available via the
 * global @ref bsp_boot_cmdline variable.
 *
 * This is the C entry point for ALL RTEMS BSPs.  It is invoked from the
 * assembly language initialization file usually called @c start.S which does
 * the basic CPU setup (stack, C runtime environment, zero BSS, load other
 * sections) and calls afterwards boot_card().  The boot card function provides
 * the framework for the BSP initialization sequence.  The basic flow of
 * initialization is:
 *
 * - disable interrupts, interrupts will be enabled during the first context switch
 * - bsp_start() - more advanced initialization
 * - obtain information on BSP memory via bsp_get_work_area() and allocate RTEMS Workspace
 * - rtems_initialize_data_structures()
 * - allocate memory for C Program Heap
 * - initialize C Library and C Program Heap
 * - bsp_pretasking_hook()
 * - if defined( RTEMS_DEBUG )
 *   - rtems_debug_enable( RTEMS_DEBUG_ALL_MASK )
 * - rtems_initialize_before_drivers()
 * - bsp_predriver_hook()
 * - rtems_initialize_device_drivers()
 *   - initialization of all device drivers
 * - bsp_postdriver_hook()
 * - rtems_initialize_start_multitasking()
 *   - 1st task executes C++ global constructors
 *   - .... application runs ...
 *   - exit
 * - back to here eventually
 * - bsp_cleanup()
 *
 * If something goes wrong bsp_cleanup() will be called out of order.
 *
 * This style of initialization ensures that the C++ global constructors are
 * executed after RTEMS is initialized.
 */
int boot_card(const char *cmdline);

/** @} */

void bsp_libc_init(void *heap_begin, uintptr_t heap_size, size_t sbrk_amount);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_SHARED_BOOTCARD_H */
