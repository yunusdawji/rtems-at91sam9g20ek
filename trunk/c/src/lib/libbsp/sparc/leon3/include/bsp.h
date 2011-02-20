/*  bsp.h
 *
 *  This include file contains all SPARC simulator definitions.
 *
 *  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  Ported to ERC32 implementation of the SPARC by On-Line Applications
 *  Research Corporation (OAR) under contract to the European Space
 *  Agency (ESA).
 *
 *  ERC32 modifications of respective RTEMS file: COPYRIGHT (c) 1995.
 *  European Space Agency.
 *
 *  $Id: bsp.h,v 1.13 2009/11/29 15:33:27 ralf Exp $
 */

#ifndef _BSP_H
#define _BSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bspopts.h>

#include <rtems.h>
#include <leon.h>
#include <rtems/clockdrv.h>
#include <rtems/console.h>

/* SPARC CPU variant: LEON3 */
#define LEON3 1

/*
 *  BSP provides its own Idle thread body
 */
void *bsp_idle_thread( uintptr_t ignored );
#define BSP_IDLE_TASK_BODY bsp_idle_thread

/*
 * Network driver configuration
 */
struct rtems_bsdnet_ifconfig;
extern int rtems_leon_open_eth_driver_attach(
  struct rtems_bsdnet_ifconfig *config,
  int attach
);
extern int rtems_smc91111_driver_attach_leon3(
  struct rtems_bsdnet_ifconfig *config,
  int attach
);
extern int rtems_leon_greth_driver_attach(
  struct rtems_bsdnet_ifconfig *config,
  int attach
);

#define RTEMS_BSP_NETWORK_DRIVER_NAME_OPENETH	"open_eth1"
#define RTEMS_BSP_NETWORK_DRIVER_ATTACH_OPENETH	 rtems_leon_open_eth_driver_attach
#define RTEMS_BSP_NETWORK_DRIVER_NAME_SMC91111	"smc_eth1"
#define RTEMS_BSP_NETWORK_DRIVER_ATTACH_SMC91111 rtems_smc91111_driver_attach_leon3
#define RTEMS_BSP_NETWORK_DRIVER_NAME_GRETH	 "gr_eth1"
#define RTEMS_BSP_NETWORK_DRIVER_ATTACH_GRETH    rtems_leon_greth_driver_attach

#ifndef RTEMS_BSP_NETWORK_DRIVER_NAME
#define RTEMS_BSP_NETWORK_DRIVER_NAME   RTEMS_BSP_NETWORK_DRIVER_NAME_GRETH
#define RTEMS_BSP_NETWORK_DRIVER_ATTACH RTEMS_BSP_NETWORK_DRIVER_ATTACH_GRETH
#endif

/*
 *  Simple spin delay in microsecond units for device drivers.
 *  This is very dependent on the clock speed of the target.
 */

extern void Clock_delay(uint32_t microseconds);

#define delay( microseconds ) Clock_delay(microseconds)
extern int   CPU_SPARC_HAS_SNOOPING;


/* Constants */

/*
 *  Information placed in the linkcmds file.
 */

extern int   RAM_START;
extern int   RAM_END;
extern int   RAM_SIZE;

extern int   PROM_START;
extern int   PROM_END;
extern int   PROM_SIZE;

extern int   CLOCK_SPEED;

extern int   end;        /* last address in the program */

/* miscellaneous stuff assumed to exist */

rtems_isr_entry set_vector(                     /* returns old vector */
    rtems_isr_entry     handler,                /* isr routine        */
    rtems_vector_number vector,                 /* vector number      */
    int                 type                    /* RTEMS or RAW intr  */
);

void BSP_fatal_return( void );

void bsp_spurious_initialize( void );

#ifdef __cplusplus
}
#endif

#endif


