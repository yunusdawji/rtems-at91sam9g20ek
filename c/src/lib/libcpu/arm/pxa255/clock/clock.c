/*
 *  By Yang Xi <hiyangxi@gmail.com>
 *  PXA255 clock specific using the System Timer
 *
 *  RTEMS uses IRQ 26 as Clock Source
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: clock.c,v 1.7 2010/04/30 13:15:49 sh Exp $
 */

#include <rtems.h>
#include <rtems/clockdrv.h>
#include <rtems/libio.h>

#include <stdlib.h>
#include <bsp.h>
#include <bspopts.h>
#include <bsp/irq.h>
#include <pxa255.h>

#if ON_SKYEYE==1
  #define CLOCK_DRIVER_USE_FAST_IDLE
#endif

static unsigned long period_num;

/**
 *  Return the nanoseconds since last tick
 */
uint32_t clock_driver_get_nanoseconds_since_last_tick(void)
{
  return 0;
}

#define Clock_driver_nanoseconds_since_last_tick \
  clock_driver_get_nanoseconds_since_last_tick

/**
 * Enables clock interrupt.
 *
 * If the interrupt is always on, this can be a NOP.
 */
static void clock_isr_on(const rtems_irq_connect_data *unused)
{
  /*Clear the interrupt bit */
  XSCALE_OS_TIMER_TSR = 0x1;

  /* enable timer interrupt */
  XSCALE_OS_TIMER_IER |= 0x1;

#if ON_SKYEYE==1
  period_num = (TIMER_RATE* Configuration.microseconds_per_tick)/100000;
#else
  period_num = (TIMER_RATE* Configuration.microseconds_per_tick)/10000;
#endif

  XSCALE_OS_TIMER_MR0 = XSCALE_OS_TIMER_TCR + period_num;
}

/**
 * Disables clock interrupts
 *
 * If the interrupt is always on, this can be a NOP.
 */
static void clock_isr_off(const rtems_irq_connect_data *unused)
{
  /*Clear the interrupt bit */
  XSCALE_OS_TIMER_TSR = 0x1;
  /* disable timer interrupt*/
  XSCALE_OS_TIMER_IER &= ~0x1;
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
  return XSCALE_OS_TIMER_IER & 0x1;
}

rtems_isr Clock_isr(rtems_vector_number vector);

/* Replace the first value with the clock's interrupt name. */
rtems_irq_connect_data clock_isr_data = {
  XSCALE_IRQ_OS_TIMER,
  (rtems_irq_hdl)Clock_isr,
  NULL,
  clock_isr_on,
  clock_isr_off,
  clock_isr_is_on
};


#define Clock_driver_support_install_isr( _new, _old ) \
  do {						       \
    _old = NULL;				       \
    BSP_install_rtems_irq_handler(&clock_isr_data);    \
  } while (0)

void Clock_driver_support_initialize_hardware(void)
{
#if ON_SKYEYE==1
  period_num = (TIMER_RATE* Configuration.microseconds_per_tick)/100000;
#else
  period_num = (TIMER_RATE* Configuration.microseconds_per_tick)/10000;
#endif
}


#define CLOCK_VECTOR 0

#define Clock_driver_support_at_tick() \
  do { \
    /* read the status to clear the int */ \
    XSCALE_OS_TIMER_TSR = 0x1; \
    \
    /*Add the match register*/ \
    XSCALE_OS_TIMER_MR0 = XSCALE_OS_TIMER_TCR + period_num; \
  } while (0)

void Clock_driver_support_shutdown_hardware( void )
{
  BSP_remove_rtems_irq_handler(&clock_isr_data);
}

#include "../../../../libbsp/shared/clockdrv_shell.h"
