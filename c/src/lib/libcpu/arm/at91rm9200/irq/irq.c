/*
 * Atmel AT91RM9200 Interrupt handler
 *
 * Copyright (c) 2010 embedded brains GmbH.
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: irq.c,v 1.6 2010/04/30 13:15:49 sh Exp $
 */

#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/irq-generic.h>

#include <at91rm9200.h>

void bsp_interrupt_dispatch(void)
{
  rtems_vector_number vector = AIC_CTL_REG(AIC_ISR);

  bsp_interrupt_handler_dispatch(vector);

  AIC_CTL_REG(AIC_EOICR) = 0;
}

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
  AIC_CTL_REG(AIC_IECR) = 1 << vector;

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  AIC_CTL_REG(AIC_IDCR) = 1 << vector;

  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_facility_initialize(void)
{
  /* disable all interrupts */
  AIC_CTL_REG(AIC_IDCR) = 0xffffffff;

  _CPU_ISR_install_vector(ARM_EXCEPTION_IRQ, arm_exc_interrupt, NULL);

  return RTEMS_SUCCESSFUL;
}

void bsp_interrupt_handler_default(rtems_vector_number vector)
{
  printk("spurious interrupt: %u\n", vector);
}
