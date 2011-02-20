/*
 * Atmel AT91SAM9G20 Register definitions, used in AT91SAM9G20EK
 *
 * Copyright (c) 2011 by Liu Xing Hua <xhl.physics@gmail.com>
 * 
 * Copyright (c) 2003 by Cogent Computer Systems
 * Written by Mike Kelly <mike@cogcomp.com>
 *
 * Modified by Fernando Nicodemos <fgnicodemos@terra.com.br>
 * from NCB - Sistemas Embarcados Ltda. (Brazil)
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 *
*/


#ifndef __AT91SAM9G20_H__
#define __AT91SAM9G20_H__

#include "bits.h"

typedef volatile unsigned long vulong;

/* Source Mode Register - 32 of them */
#define AIC_SMR_BASE            0xFFFFF000
#define AIC_SMR_REG(_x_)        *(vulong *)(AIC_SMR_BASE + (_x_ & 0x7c))

/* Source Vector Register - 32 of them */
#define AIC_SVR_BASE            0xFFFFF080
#define AIC_SVR_REG(_x_)        *(vulong *)(AIC_SVR_BASE + (_x_ & 0x7c))

/* Control Register - 32 of them */
#define AIC_CTL_BASE            0xFFFFF100
#define AIC_CTL_REG(_x_)        *(vulong *)(AIC_CTL_BASE + (_x_ & 0x7f))

/* Register Offsets */
/* offsets from AIC_SMR_BASE and AIC_SVR_BASE */
#define AIC_SMR_FIQ             0x00    /* Advanced Interrupt Controller FIQ */
#define AIC_SMR_SYSIRQ          0x04    /* Advanced Interrupt Controller SYSIRQ */
#define AIC_SMR_PIOA            0x08    /* Parallel I/O Controller A */
#define AIC_SMR_PIOB            0x0c    /* Parallel I/O Controller B */
#define AIC_SMR_PIOC            0x10    /* Parallel I/O Controller C */
#define AIC_SMR_ADC             0x14    /* Analog to Digital Converter */
#define AIC_SMR_US0             0x18    /* USART 0 */
#define AIC_SMR_US1             0x1c    /* USART 1 */
#define AIC_SMR_US2             0x20    /* USART 2 */
#define AIC_SMR_MCI             0x24    /* Multimedia Card Interface */
#define AIC_SMR_UDP             0x28    /* USB Device Port */
#define AIC_SMR_TWI             0x2C    /* Two-wire Interface */
#define AIC_SMR_SPI0            0x30    /* Serial Peripheral Interface 0 */
#define AIC_SMR_SPI1            0x34    /* Serial Peripheral Interface 1 */
#define AIC_SMR_SSC0            0x38    /* Synchronous Serial Controller 0 */
#define AIC_SMR_RES0            0x3c    /* Reserved 0 */
#define AIC_SMR_RES1            0x40    /* Reserved 1 */
#define AIC_SMR_TC0             0x44    /* Timer/Counter 0 */
#define AIC_SMR_TC1             0x48    /* Timer/Counter 1 */
#define AIC_SMR_TC2             0x4c    /* Timer/Counter 2 */
#define AIC_SMR_UHP             0x50    /* USB Host Port */
#define AIC_SMR_EMAC            0x54    /* Ethernet MAC */
#define AIC_SMR_ISI             0x58    /* Image Sensor Interface */
#define AIC_SMR_US3             0x5c    /* USART 3 */
#define AIC_SMR_US4             0x60    /* USART 4 */
#define AIC_SMR_US5             0x64    /* USART 5 */
#define AIC_SMR_TC3             0x68    /* Timer/Counter 3 */
#define AIC_SMR_TC4             0x6c    /* Timer/Counter 4 */
#define AIC_SMR_TC5             0x70    /* Timer/Counter 5 */
#define AIC_SMR_IRQ0            0x74    /* Advanced Interrupt Controller IRQ0 */
#define AIC_SMR_IRQ1            0x78    /* Advanced Interrupt Controller IRQ1 */
#define AIC_SMR_IRQ2            0x7c    /* Advanced Interrupt Controller IRQ2 */


/* from AIC_CTL_BASE */
#define AIC_IVR                 0x00    /* IRQ Vector Register */
#define AIC_FVR                 0x04    /* FIQ Vector Register */
#define AIC_ISR                 0x08    /* Interrupt Status Register */
#define AIC_IPR                 0x0C    /* Interrupt Pending Register */
#define AIC_IMR                 0x10    /* Interrupt Mask Register */
#define AIC_CISR                0x14    /* Core Interrupt Status Register */
#define AIC_IECR                0x20    /* Interrupt Enable Command Register */
#define AIC_IDCR                0x24    /* Interrupt Disable Command Register */
#define AIC_ICCR                0x28    /* Interrupt Clear Command Register */
#define AIC_ISCR                0x2C    /* Interrupt Set Command Register */
#define AIC_EOICR               0x30    /* End of Interrupt Command Register */
#define AIC_SPU                 0x34    /* Spurious Vector Register */
#define AIC_DCR                 0x38    /* Debug Control Register (Protect) */
#define AIC_FFER                0x40    /* Fast Forcing Enable Register */
#define AIC_FFDR                0x44    /* Fast Forcing Disable Register */
#define AIC_FFSR                0x48    /* Fast Forcing Status Register */

/* Bit Defines */
/* AIC_ISR - Interrupt Status Register */
#define AIC_ISR_IRQID_MASK      0x1f    /* current interrupt ID          */

/* AIC_CISR - Core Interrupt Status Register */
#define AIC_CISR_IRQ            BIT1    /* 1 = Core IRQ is active */
#define AIC_CISR_FIQ            BIT0    /* 1 = Core FIQ is active */

/* AIC_DCR - Debug Control Register (Protect) */
#define AIC_DCR_GMSK            BIT1    /* 0 = AIC controls IRQ and FIQ */
#define AIC_DCR_PROT            BIT0    /* 1 = enable protection mode */

/* AIC_SMR */
#define AIC_SMR_PRIOR(_x_)      ((_x_ & 0x07) << 0)
#define AIC_SMR_SRC_LVL_LOW     (0 << 5)        /* Are these right? docs don't say which is high/low     */
#define AIC_SMR_SRC_EDGE_LOW    (1 << 5)
#define AIC_SMR_SRC_LVL_HI      (2 << 5)
#define AIC_SMR_SRC_EDGE_HI     (3 << 5)

/**************************************************************************/
/* Debug Unit		                                                  */
/**************************************************************************/
#define DBGU_BASE               0xFFFFF200
#define DBGU_REG(_x_)   *(vulong *)(DBGU_BASE + _x_)

/* Register Offsets */
#define DBGU_CR                 0x00    /* Control Register */
#define DBGU_MR                 0x04    /* Mode Register */
#define DBGU_IER                0x08    /* Interrupt Enable Register */
#define DBGU_IDR                0x0C    /* Interrupt Disable Register */
#define DBGU_IMR                0x10    /* Interrupt Mask Register */
#define DBGU_CSR                0x14    /* Channel Status Register */
#define DBGU_RHR                0x18    /* Receiver Holding Register */
#define DBGU_THR                0x1C    /* Transmitter Holding Register */
#define DBGU_BRGR               0x20    /* Baud Rate Generator Register */
#define DBGU_C1R                0x40    /* Chip ID1 Register */
#define DBGU_C2R                0x44    /* Chip ID2 Register */
#define DBGU_FNTR               0x48    /* Force NTRST Register */

/**************************************************************************/
/* USART 0-3  							          */
/**************************************************************************/
#define USART0_BASE             0xFFFB0000
#define USART1_BASE             0xFFFB4000
#define USART2_BASE             0xFFFB8000
#define USART3_BASE             0xFFFD0000
#define USART4_BASE             0xFFFD4000
#define USART5_BASE             0xFFFD8000


/**************************************************************************
 * Peripheral Data Control (DMA)
 * Note that each of the following peripherals has it's own
 * set of these registers starting at offset 0x100 from it's
 * base address: DBGU, SPI, USART and SSC
 * To access the DMA for a peripheral, use the macro for that
 * peripheral but with these register offsets
 **************************************************************************/
/* Register Offsets */
#define PDC_RPR         0x100   /* Receive Pointer Register */
#define PDC_RCR         0x104   /* Receive Counter Register */
#define PDC_TPR         0x108   /* Transmit Pointer Register */
#define PDC_TCR         0x10c   /* Transmit Counter Register */
#define PDC_RNPR        0x110   /* Receive Next Pointer Register */
#define PDC_RNCR        0x114   /* Receive Next Counter Register */
#define PDC_TNPR        0x118   /* Transmit Next Pointer Register */
#define PDC_TNCR        0x11c   /* Transmit Next Counter Register */
#define PDC_PTCR        0x120   /* PDC Transfer Control Register */
#define PDC_PTSR        0x124   /* PDC Transfer Status Register */

/**************************************************************************
 * Parallel I/O Unit
 * There are four PIO blocks - A, B, C.  They all have the
 * same register set, but different base addresses
 **************************************************************************/
/* Port A */
#define PIOA_BASE               0xFFFFF400
#define PIOA_REG(_x_)   *(vulong *)(PIOA_BASE + _x_)

/* Port B */
#define PIOB_BASE               0xFFFFF600
#define PIOB_REG(_x_)   *(vulong *)(PIOB_BASE + _x_)

/* Port C */
#define PIOC_BASE               0xFFFFF800
#define PIOC_REG(_x_)   *(vulong *)(PIOC_BASE + _x_)

/**************************************************************************
 * Power Management and Clock Control
 *************************************************************************/
#define PMC_BASE                0xFFFFFC00
#define PMC_REG(_x_)    *(vulong *)(PMC_BASE + _x_)

/**************************************************************************
 * MAC Unit
 *************************************************************************/
#define EMAC_BASE               0xFFFC4000
#define EMAC_REG(_x_)   *(vulong *)(EMAC_BASE + _x_)

/**************************************************************************
 * Watchdog Timer  Unit
 **************************************************************************/
#define WDT_BASE	0xFFFFFD40
#define WDT_REG(_x_)	*(vulong *)(WDT_BASE + _x_)

#define WDT_CR	(0x00)		/* WDT Control Register */
#define WDT_MR	(0x04)		/* Mode Register */
#define WDT_SR	(0x08)		/* Status Register */

#define WDT_DIS	(1 << 15) 	/* 1 = Disables the Watchdog Timer. */
#define WDT_EN	(0 << 15)	/* 0 = Enables the Watchdog Timer */

/**************************************************************************
 * Periodic Interval Timer (PIT) Unit
 **************************************************************************/
#define PITC_BASE	0xFFFFFD30
#define PITC_REG(_x_)   *(vulong *)(PITC_BASE + _x_)
#define PIT_MR	(0x00)
#define PIT_SR	(0x04)
#define PIT_PIVR	(0x08)
#define PIT_PIIR	(0x0c)

/* PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register */
#define PITC_PIV        (0xFFFFF <<  0) /* (PITC) Periodic Interval Value */
#define PITC_PITEN      (0x1 << 24) /* (PITC) Periodic Interval Timer Enabled */
#define PITC_PITIEN     (0x1 << 25) /* (PITC) Periodic Interval Timer Interrupt Enable */
#define PITC_PITIDIS     (0x0 << 25) /* (PITC) Periodic Interval Timer Interrupt disable */

/* PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register */
#define PITC_PITS       (0x1 <<  0) /* (PITC) Periodic Interval Timer Status */

/* PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register */
#define PITC_CPIV       (0xFFFFF <<  0) /* (PITC) Current Periodic Interval Value */
#define PITC_PICNT      (0xFFF << 20) /* (PITC) Periodic Interval Counter */
/* PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register */

/**************************************************************************
 * Timer/Counter Unit
 **************************************************************************/
#define TC_BASE         0xFFFA0000
#define TC_REG(_x_)     *(vulong *)(TC_BASE + 0x00 + _x_)
#define TC_TC0_REG(_x_) *(vulong *)(TC_BASE + 0x00 + _x_)
#define TC_TC1_REG(_x_) *(vulong *)(TC_BASE + 0x40 + _x_)
#define TC_TC2_REG(_x_) *(vulong *)(TC_BASE + 0x80 + _x_)

/* Offsets from TC_TC?_REG  */
#define TC_CCR      0x00    /* Channel Control Register  */
#define TC_CMR      0x04    /* Channel Mode Register  */
#define TC_CV       0x10    /* Counter Value  */
#define TC_RA       0x14    /* Register A  */
#define TC_RB       0x18    /* Register B  */
#define TC_RC       0x1C    /* Register C  */
#define TC_SR       0x20    /* Status Register  */
#define TC_IER      0x24    /* Interrupt Enable Register  */
#define TC_IDR      0x28    /* Interrupt Disable Register  */
#define TC_IMR      0x2C    /* Interrupt Mask Register  */

/* Offsets from TC_BASE */
#define TC_BCR      0xc0    /* Channel Control Register  */
#define TC_BMR      0xc4    /* Channel Control Register  */

/* Block control register */
#define TC_BCR_SYNC    BIT0       /* Set to syncronize channels */

/* Block mode register */
#define TC_BMR_TC0(_x_)    ((_x_ & 0x3) << 0)   /* TC0 clock source */
#define TC_BMR_TC1(_x_)    ((_x_ & 0x3) << 2)   /* TC1 clock source */
#define TC_BMR_TC2(_x_)    ((_x_ & 0x3) << 4)   /* TC2 clock source */

/* Channel Control register */
#define TC_CCR_CLKEN     BIT0       /* Enable clock */
#define TC_CCR_CLKDIS    BIT1       /* Disable clock */
#define TC_CCR_SWTRG     BIT2       /* Software trigger command */

/* Channel mode register */
#define TC_CMR_TCCLKS(_x_)   ((_x_ & 0x7) << 0)  /* Clock source */
#define TC_CMR_CLKI          BIT3                /* Clock invert */
#define TC_BURST(_x_)        ((_x_ & 0x3 << 4)   /* Burst signal selection */
#define TC_WAVE              BIT15               /* 0 for catpure, 1 for wave */

/* Channel mode register - capture mode (TC_WAVE = 0) */
#define TC_CMR_LDBSTOP       BIT6                /* Set to stop clock when RB loads */
#define TC_CMR_LDBDIS        BIT7                /* Set to disable clock when RB loads */
#define TC_CMR_ETRGEDG(_x_)  ((_x_ & 0x3) << 8)  /* Select edge triggering mode */
#define TC_CMR_ABETRG        BIT10               /* Select ext trigger source */
#define TC_CMR_CPCTRG        BIT14               /* RC Compare trigger enable */
#define TC_CMR_WAVE          BIT15               /* 1 = Capture Mode is disabled (Waveform Mode is enabled).*/
#define TC_CMR_LDRA(_x_)     ((_x_ & 0x3) << 16) /* RA loading selection */
#define TC_CMR_LDRB(_x_)     ((_x_ & 0x3) << 18) /* RB loading selection */

/* Channel mode register - wave mode (TC_WAVE = 1) */
#define TC_CMR_CPCSTOP       BIT6                 /* Clock stopped w/ RC compare */
#define TC_CMR_CPCDIS        BIT7                 /* Clock disabled w/ RC compare */
#define TC_CMR_EEVTEDG(_x_)  ((_x_ & 0x3) << 8)   /* Ext event edge selection */
#define TC_CMR_EEVT(_x_)     ((_x_ & 0x3) << 10)  /* Ext event selection */
#define TC_CMR_ENETRG        BIT12                /* Ext event trigger enable */
#define TC_CMR_WAVESEL(_x_)  ((_x_ & 0x3) << 13)  /* Waveform selection */
#define TC_CMR_ACPA(_x_)     ((_x_ & 0x3) << 16)  /* RA compare effect on TIOA */
#define TC_CMR_ACPC(_x_)     ((_x_ & 0x3) << 18)  /* RC compare effect on TIOA */
#define TC_CMR_AEEVT(_x_)    ((_x_ & 0x3) << 20)  /* Ext event effect on TIOA */
#define TC_CMR_ASWTRG(_x_)   ((_x_ & 0x3) << 22)  /* SW trigger effect on TIOA */
#define TC_CMR_BCPB(_x_)     ((_x_ & 0x3) << 24)  /* RB compare effect on TIOB */
#define TC_CMR_BCPC(_x_)     ((_x_ & 0x3) << 26)  /* RC compare effect on TIOB */
#define TC_CMR_BEEVT(_x_)    ((_x_ & 0x3) << 28)  /* Ext event effect on TIOB */
#define TC_CMR_BSWTRG(_x_)   ((_x_ & 0x3) << 30)  /* SW trigger effect on TIOB */

/* Counter value */
#define TC_CV_MASK            0xffff              /* Timer counter mask */

/* Status, Interrupt enable, Interrupt disable, and Interrupt mask registers */
#define TC_SR_COVFS     BIT0        /* Counter overflow status */
#define TC_SR_LOVRS     BIT1        /* Load overrun status */
#define TC_SR_CPAS      BIT2        /* RA compare status */
#define TC_SR_CPBS      BIT3        /* RB compare status */
#define TC_SR_CPCS      BIT4        /* RC compare status */
#define TC_SR_LDRAS     BIT5        /* RA loading status */
#define TC_SR_LDRBS     BIT6        /* RB loading  status */
#define TC_SR_ETRGS     BIT7        /* External trigger status */
#define TC_SR_CLKSTA    BIT16       /* Clock enabling status */
#define TC_SR_MTIOA     BIT17       /* TIOA Mirror */
#define TC_SR_MTIOB     BIT18       /* TIOB Mirror */

/***************************************************************************
 * External Bus Interface Unit
 **************************************************************************/
#define EBI_BASE                        0xFFFFEA00
#define EBI_REG(_x_)            *(vulong *)(EBI_BASE + _x_)

/***************************************************************************
 * Static Memory Interface Unit
 ***************************************************************************/
#define SMC_REG(_x_)            *(vulong *)(0xFFFFEC00 + _x_)

/**************************************************************************
 * SDRAM Memory Interface Unit
 **************************************************************************/
#define SDRC_REG(_x_)           *(vulong *)(0xFFFFEA00 + _x_)

#endif /* __AT91RSAM9G20_H__ */

