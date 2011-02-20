/*
 * AT91SAM9G20EK BSP header file
 *
 * Copyright (c) 2004 by Cogent Computer Systems
 * Writtent by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 *
 *
 *  $Id: bsp.h,v 1.9 2010/04/30 14:44:17 sh Exp $
 */
#ifndef _BSP_H
#define _BSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bspopts.h>

#include <rtems.h>
#include <rtems/console.h>
#include <rtems/clockdrv.h>
#include <libchip/serial.h>

#define BSP_FEATURE_IRQ_EXTENSION

/* What is the input clock freq in hertz? */
#define BSP_MAIN_FREQ 18432000     /* 18.432 MHz */
#define BSP_SLCK_FREQ   32768      /* 32.768 KHz */
#define BSP_MCK		 ((18432000 * 43) / 6)  /* Master clock frequency  */

/* What is the last interrupt? */
#define BSP_MAX_INT AT91SAM9G20_MAX_INT

console_tbl *BSP_get_uart_from_minor(int minor);
static inline int32_t BSP_get_baud(void) {return 115200;}


/*
 * Network driver configuration
 */
extern struct rtems_bsdnet_ifconfig *config;

/* Change these to match your board */
int rtems_at91sam9g20_emac_attach(struct rtems_bsdnet_ifconfig *config, int attaching);
#define RTEMS_BSP_NETWORK_DRIVER_NAME	"eth0"
#define RTEMS_BSP_NETWORK_DRIVER_ATTACH	rtems_at91sam9g20_emac_attach

#ifdef __cplusplus
}
#endif

#endif /* _BSP_H */

