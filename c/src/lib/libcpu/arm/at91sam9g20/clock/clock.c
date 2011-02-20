/*
 *  AT91SAM9G20 clock specific using the PIT Timer
 *
 *  Copyright (c) 2011 by Liu Xing Hua <xhl.physics@gmail.com>
 *
 *  Copyright (c) 2003 by Cogent Computer Systems
 *  Written by Mike Kelly <mike@cogcomp.com>
 *         and Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 *
 *
 *  $Id: clock.c,v 1.12 2010/04/30 13:15:48 sh Exp $
 */
#include <rtems.h>
#include <rtems/clockdrv.h>
#include <rtems/libio.h>

#include <stdlib.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <at91sam9g20.h>
#include <at91sam9g20_pmc.h>


static unsigned long pit_piv_reload;

/**
 * Enables clock interrupt.
 *
 * If the interrupt is always on, this can be a NOP.
 */
static void clock_isr_on(const rtems_irq_connect_data *unused)
{
    /* enable timer interrupt */
    PITC_REG(PIT_MR) = PITC_PITIEN;
}

/**
 * Disables clock interrupts
 *
 * If the interrupt is always on, this can be a NOP.
 */
static void clock_isr_off(const rtems_irq_connect_data *unused)
{
    /* disable timer interrupt */
    PITC_REG(PIT_MR) = PITC_PITIDIS;
    return;
}

/**
 * Tests to see if clock interrupt is enabled, and returns 1 if so.
 * If interrupt is not enabled, returns 0.
 *
 * If the interrupt is always on, this always returns 1.
 */
static int clock_isr_is_on(const rtems_irq_connect_data *irq)
{
    /* check timer interrupt */
    return PITC_REG(PIT_MR) & PITC_PITIEN;
}

rtems_isr Clock_isr(rtems_vector_number vector);

/* Replace the first value with the clock's interrupt name. */
rtems_irq_connect_data clock_isr_data = {AT91SAM9G20_INT_SYSIRQ,
                                         (rtems_irq_hdl)Clock_isr,
					 NULL,
                                         clock_isr_on,
                                         clock_isr_off,
                                         clock_isr_is_on};


#define Clock_driver_support_install_isr( _new, _old ) \
  do {                                                 \
      (_old) = NULL;                                   \
      BSP_install_rtems_irq_handler(&clock_isr_data);  \
  } while(0)

uint16_t pit_piv_value;
void Clock_driver_support_initialize_hardware(void)
{
  uint32_t pit_str;
  int mck;

  /* the PIT timer is driven from MCK/16 */
  mck = at91sam9g20_get_mck();
  pit_piv_value = 
   (((rtems_configuration_get_microseconds_per_tick() * (mck/16)) + (1000000/2))/ 1000000);
 
  pit_piv_reload = pit_piv_value;

  /* read the status to clear the int */
  pit_str = PITC_REG(PIT_SR);

  /* set priority */
  AIC_SMR_REG(AIC_SMR_SYSIRQ) = AIC_SMR_PRIOR(0x7);

  /* set the timer value */
  PITC_REG(PIT_MR) = pit_piv_reload;
}

uint32_t bsp_clock_nanoseconds_since_last_tick(void)
{
  uint16_t mck_counts;

  mck_counts = pit_piv_value - pit_piv_reload;
  return (rtems_configuration_get_microseconds_per_tick() * mck_counts * 1000)
     / pit_piv_value;
}

#define Clock_driver_nanoseconds_since_last_tick \
  bsp_clock_nanoseconds_since_last_tick

#define CLOCK_VECTOR 0

#define Clock_driver_support_at_tick() \
  do { \
    uint32_t pit_str; \
    \
    /* read the status to clear the int */ \
    pit_str = PITC_REG(PIT_SR); \
  } while (0)

void Clock_driver_support_shutdown_hardware( void )
{
    BSP_remove_rtems_irq_handler(&clock_isr_data);
}

#include "../../../../libbsp/shared/clockdrv_shell.h"
