/*
 * ATMEL AT91SAM9G20EK - AT91SAM9G20 Startup Code
 *
 *  Copyright (c) 2011 by Liu Xing Hua <xhl.physics@gmail.com>
 *
 *  Copyright (c) 2004 by Cogent Computer Systems
 *  Written by Jay Monkman <jtm@lopingdog.com>
 *
 *  Modified by Joel Sherill 
 *  from OAR Corporation and 
 *  Fernando Nicodemos <fgnicodemos@terra.com.br>
 *  from NCB - Sistemas Embarcados Ltda. (Brazil)
 * 
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: bspstart.c,v 1.20 2010/04/30 14:44:17 sh Exp $
 */

#include <bsp.h>
#include <bsp/irq-generic.h>
#include <at91sam9g20.h>
#include <at91sam9g20_pmc.h>
#include <at91sam9g20_emac.h>
#include <at91sam9g20_gpio.h>
#include <at91sam9g20_usart.h>

/* Function prototypes */
extern void rtems_exception_init_mngt(void);
void bsp_libc_init( void *, uint32_t, int );
static void fix_mac_addr(void);
void bsp_usart_init(void);

/*
 * bsp_start_default - BSP initialization function
 *
 * This function is called before RTEMS is initialized and used
 * adjust the kernel's configuration.
 *
 * This function also configures the CPU's memory protection unit.
 *
 * RESTRICTIONS/LIMITATIONS:
 *   Since RTEMS is not configured, no RTEMS functions can be called.
 */
void bsp_start_default( void )
{
  /* disable interrupts */
  AIC_CTL_REG(AIC_IDCR) = 0xffffffff;

  /*
   * Some versions of the bootloader have the MAC address
   * reversed. This fixes it, if necessary.
   */
  fix_mac_addr();

  /*
   * Init rtems PIO configuration for USARTs
   */
  bsp_usart_init(); 

  /*
   * Init rtems exceptions management
   */
  rtems_exception_init_mngt();

  /*
   * Init rtems interrupt management
   */
  if (bsp_interrupt_initialize() != RTEMS_SUCCESSFUL) {
    _CPU_Fatal_halt(0xe);
  }

} /* bsp_start */

/*
 * Some versions of the bootloader shipped with the CSB337
 * reverse the MAC address. This function tests for that,
 * and fixes the MAC address.
 */
/*
 * May be not needed on at91sam9g20ek
 */
static void fix_mac_addr(void)
{
  uint8_t addr[6];

  /* Read the MAC address */
  addr[0] = (EMAC_REG(EMAC_SA1L) >>  0) & 0xff;
  addr[1] = (EMAC_REG(EMAC_SA1L) >>  8) & 0xff;
  addr[2] = (EMAC_REG(EMAC_SA1L) >> 16) & 0xff;
  addr[3] = (EMAC_REG(EMAC_SA1L) >> 24) & 0xff;
  addr[4] = (EMAC_REG(EMAC_SA1H) >>  0) & 0xff;
  addr[5] = (EMAC_REG(EMAC_SA1H) >>  8) & 0xff;

  /* Check which 3 bytes have Cogent's OUI */
  if ((addr[5] == 0x00) && (addr[4] == 0x23) && (addr[3] == 0x31)) {
      EMAC_REG(EMAC_SA1L) = ((addr[5] <<  0) |
                             (addr[4] <<  8) |
                             (addr[3] << 16) |
                             (addr[2] << 24));

      EMAC_REG(EMAC_SA1H) = ((addr[1] <<  0) |
                             (addr[0] <<  8));
  }
}

/*
 *
 * NAME: bsp_usart_init - Function to setup the PIO in USART mode
 *       before startup
 *
 * DESCRIPTION:
 *   This function is called before usart driver is initialized and is
 *   used to setup the proper mode of PIO operation for USART.
 *
 * NOTES:
 *   The initialization could be done smarter by programming only the
 *   bits you need to program for each USART when the port is ENABLED.
 *
 */
void bsp_usart_init(void)
{
  /*
   * Configure shared pins for USARTs.
   * Disables the PIO from controlling the corresponding pin.
   */
  /*
   * Our AT91SAM9G20EK board does not use these usarts
   */
#if 0
  PIOB_REG(PIO_PDR) |= ( BIT4 |   /* USART0 TXD0  */
                         BIT5 |   /* USART0 RXD0  */
                         BIT6 |   /* USART1 TXD1  */
                         BIT7 |   /* USART1 RXD1  */
                         BIT8 |   /* USART2 TXD2  */
                         BIT9 );   /* USART2 RXD2  */

  /**** PIO Controller B - Pins you want in mode A ****/
  PIOB_REG(PIO_ASR) |=  ( BIT4 |   /* USART0 TXD0  */
                          BIT5 |   /* USART0 RXD0  */
                          BIT6 |   /* USART1 TXD1  */
                          BIT7 |   /* USART1 RXD1  */
                          BIT8 |   /* USART2 TXD2  */
                          BIT9 );  /* USART2 RXD2  */

  /**** PIO Controller B - Pins you want in mode B ****/
  /**** none ****/

  /* Enable the clock to the USARTs */
  PMC_REG(PMC_PCER) |= ( PMC_PCR_PID_US0 |   /* USART 0 Peripheral Clock */
                         PMC_PCR_PID_US1 |   /* USART 1 Peripheral Clock */
                         PMC_PCR_PID_US2 );  /* USART 2 Peripheral Clock */ 
#endif
;
} 

/*
 *  By making this a weak alias for bsp_start_default, a brave soul
 *  can override the actual bsp_start routine used.
 */
void bsp_start (void) __attribute__ ((weak, alias("bsp_start_default")));
