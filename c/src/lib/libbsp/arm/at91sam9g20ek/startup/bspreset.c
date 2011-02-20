/*
 * ATMEL AT91SAM9G20EK - AT91SAM9G20 Startup code
 *
 * Copyright (c) 2011 by Liu Xing Hua <xhl.physics@gmail.com>
 * 
 * Copyright (c) 2004 by Cogent Computer Systems
 * Written by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *
 *  $Id: bspreset.c,v 1.2 2009/11/29 14:53:00 ralf Exp $
*/
#include <bsp.h>
#include <at91sam9g20.h>
#include <at91sam9g20_pmc.h>
#include <at91sam9g20_emac.h>

void bsp_reset(void)
{
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);

  /* Enable the watchdog timer, then wait for the world to end. */
  WDT_REG(WDT_MR) = WDT_EN;

  while(1);
}
