/*
 * AT91SAM9G20 Memory Controller definitions
 * 
 * Copyright (c) 2011 by Liu Xing Hua <xhl.physics@gmail.com>
 *
 * Copyright (c) 2002 by Cogent Computer Systems
 * Written by Mike Kelly <mike@cogcomp.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 *
 */
#ifndef AT91SAM9G20_MEM_H
#define AT91SAM9G20_MEM_H

/**********************************************************************
 *       External Bus Interface Unit
 **********************************************************************/
#define EBI_CSA             0x11C    /* Chip Select Assignment Register */

/* Bit Defines */
/* EBI_CSA - Chip Select Assignment Register */
#define EBI_CSA_CS17_IOSR		BIT17		/*I/O Slew Rate Selection */
#define EBI_CSA_CS16_VDDIOMSEL   BIT16    /* 1 = Memories are 3.3V powered  */
#define EBI_CSA_CS8_DBPUC	     BIT8    /* 1= CS8 D0 - D15 Data Bus bits are not internally pulled-up. */
#define EBI_CSA_CS5_CF1       BIT5    /* Static Memory Controller and the CompactFlash Logic (second slot) */
#define EBI_CSA_CS4_CF        BIT4    /* 1 = CS4-6 are assigned to Compact Flash, 0 = Chip Selects */
#define EBI_CSA_CS3_SMM       BIT3    /* 1 = CS3 is assigned to SmartMedia, 0 = Chip Select */
#define EBI_CSA_CS1_SDRAM     BIT1    /* 1 = CS1 is assigned to SDRAM, 0 = Chip Select */


/***************************************************************************
 * Static Memory Interface Unit
 ***************************************************************************/
/* Bit Defines */

#define SMC_SETUP(_x_)	    (0x10*_x_ + 0x00) /* SMC Setup Register */
#define SMC_PULSE(_x_)	    (0x10*_x_ + 0x04) /* SMC Pulse Register */
#define SMC_CYCLE(_x_)	    (0x10*_x_ + 0x08) /* SMC Cycle Register */
#define SMC_MODE(_X_)	    (0x10*_x_ + 0x0c) /* SMC Mode Register */

/* SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x */
#define SMC_NWESETUP    (0x3F <<  0) /* (SMC) NWE Setup Length */
#define SMC_NCSSETUPWR  (0x3F <<  8) /* (SMC) NCS Setup Length in WRite Access */
#define SMC_NRDSETUP    (0x3F << 16) /* (SMC) NRD Setup Length */
#define SMC_NCSSETUPRD  (0x3F << 24) /* (SMC) NCS Setup Length in ReaD Access */

/* SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x */
#define SMC_NWEPULSE    (0x7F <<  0) /* (SMC) NWE Pulse Length */
#define SMC_NCSPULSEWR  (0x7F <<  8) /* (SMC) NCS Pulse Length in WRite Access */
#define SMC_NRDPULSE    (0x7F << 16) /* (SMC) NRD Pulse Length */
#define SMC_NCSPULSERD  (0x7F << 24) /* (SMC) NCS Pulse Length in ReaD Access */

/* SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x */
#define SMC_NWECYCLE    (0x1FF <<  0) /* (SMC) Total Write Cycle Length */
#define SMC_NRDCYCLE    (0x1FF << 16) /* (SMC) Total Read Cycle Length */

/* SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x */
#define SMC_READMODE    (0x1 <<  0) /* (SMC) Read Mode */
#define SMC_WRITEMODE   (0x1 <<  1) /* (SMC) Write Mode */
#define SMC_NWAITM      (0x3 <<  4) /* (SMC) NWAIT Mode */
#define SMC_NWAITM_NWAIT_DISABLE        (0x0 <<  4) /* (SMC) External NWAIT disabled */
#define SMC_NWAITM_NWAIT_ENABLE_FROZEN  (0x2 <<  4) /* (SMC) External NWAIT enabled in frozen mode */
#define SMC_NWAITM_NWAIT_ENABLE_READY   (0x3 <<  4) /* (SMC) External NWAIT enabled in ready mode */
#define SMC_BAT         (0x1 <<  8) /* (SMC) Byte Access Type */
#define SMC_BAT_BYTE_SELECT          (0x0 <<  8) /* (SMC) Write controled by ncs, nbs0, nbs1, nbs2, nbs3. Read controled by ncs, nrd, nbs0, nbs1, nbs2, nbs3. */
#define SMC_BAT_BYTE_WRITE           (0x1 <<  8) /* (SMC) Write controled by ncs, nwe0, nwe1, nwe2, nwe3. Read controled by ncs and nrd */
#define SMC_DBW         (0x3 << 12) /* (SMC) Data Bus Width */
#define SMC_DBW_WIDTH_EIGTH_BITS     (0x0 << 12) /* (SMC) 8 bits */
#define SMC_DBW_WIDTH_SIXTEEN_BITS   (0x1 << 12) /* (SMC) 16 bits */
#define SMC_DBW_WIDTH_THIRTY_TWO_BITS (0x2 << 12) /* (SMC) 32 bits */
#define SMC_TDF         (0xF << 16) /* (SMC) Data Float Time */
#define SMC_TDFEN       (0x1 << 20) /* (SMC) TDF Enabled */
#define SMC_PMEN        (0x1 << 24) /* (SMC) Page Mode Enabled */
#define SMC_PS          (0x3 << 28) /* (SMC) Page Size */
#define SMC_PS_SIZE_FOUR_BYTES      (0x0 << 28) /* (SMC) 4 bytes */
#define SMC_PS_SIZE_EIGHT_BYTES     (0x1 << 28) /* (SMC) 8 bytes */
#define SMC_PS_SIZE_SIXTEEN_BYTES   (0x2 << 28) /* (SMC) 16 bytes */
#define SMC_PS_SIZE_THIRTY_TWO_BYTES (0x3 << 28) /* (SMC) 32 bytes */

/* ***************************************************************************** */
/* SDRAM Memory Interface Unit */
/* ***************************************************************************** */
#define SDRC_MR             0x00       /* Mode Register */
#define SDRC_TR             0x04       /* Refresh Timer Register */
#define SDRC_CR             0x08       /* Configuration Register */
#define SDRC_LPR            0x10       /* Low Power Register */
#define SDRC_IER            0x14       /* Interrupt Enable Register */
#define SDRC_IDR            0x18       /* Interrupt Disable Register */
#define SDRC_IMR            0x1C       /* Interrupt Mask Register */
#define SDRC_ISR            0x20       /* Interrupt Status Register */
#define SDRC_MDR		  0x24		 /*  SDRAMC Memory Device Register */

/* Bit Defines */
/* SDRC_MR - Mode Register */
#define SDRC_MR_NORM          (0 << 0)   /* Normal Mode - All accesses to SDRAM are decoded normally */
#define SDRC_MR_NOP         (1 << 0)   /* NOP Command is sent to SDRAM */
#define SDRC_MR_PRE         (2 << 0)   /* Precharge All Command is sent to SDRAM */
#define SDRC_MR_MRS         (3 << 0)   /* Mode Register Set Command is sent to SDRAM */
#define SDRC_MR_REF         (4 << 0)   /* Refresh Command is sent to SDRAM */
#define SDRC_MR_LMR         (5 << 0)   /* (SDRAMC) Issue an Extended Load Mode Register */
#define SDRC_MR_DEEP        (6 << 0)   /* (SDRAMC) Enter Deep Power Mode */

/* SDRC_TR - Refresh Timer Register */
#define SDRC_TR_COUNT(_x_)    ((_x_ & 0xfff) << 0)

/* SDRC_CR - Configuration Register */
#define SDRC_CR_TXSR(_x_)     ((_x_ & 0xf) << 27)     /* CKE to ACT Time */
#define SDRC_CR_TRAS(_x_)     ((_x_ & 0xf) << 23)     /* ACT to PRE Time */
#define SDRC_CR_TRCD(_x_)     ((_x_ & 0xf) << 19)     /* RAS to CAS Time */
#define SDRC_CR_TRP(_x_)      ((_x_ & 0xf) << 15)     /* PRE to ACT Time */
#define SDRC_CR_TRC(_x_)      ((_x_ & 0xf) << 11)     /* REF to ACT Time */
#define SDRC_CR_TWR(_x_)      ((_x_ & 0xf) << 7)      /* Write Recovery Time */
#define SDRAMC_DBW     	    (0x1 <<  7) /* (SDRAMC) Data Bus Width */
#define SDRAMC_DBW_32	    (0x0 <<  7) /* (SDRAMC) 32 Bits datas bus */
#define SDRAMC_DBW_16	    (0x1 <<  7) /* (SDRAMC) 16 Bits datas bus */
#define SDRC_CR_CAS_1         (1 << 5)   /* Cas Delay = 1, this is the only supported value */
#define SDRC_CR_CAS_2         (2 << 5)   /* Cas Delay = 2, this is the only supported value */
#define SDRC_CR_CAS_3         (3 << 5)   /* Cas Delay = 3, this is the only supported value */
#define SDRC_CR_NB_4          BIT4       /* 4 Banks per device */
#define SDRC_CR_NR_11         (0 << 2)   /* Number of rows = 11 */
#define SDRC_CR_NR_12         (1 << 2)   /* Number of rows = 12 */
#define SDRC_CR_NR_13         (2 << 2)   /* Number of rows = 13 */
#define SDRC_CR_NC_8          (0 << 0)   /* Number of columns = 8 */
#define SDRC_CR_NC_9          (1 << 0)   /* Number of columns = 9 */
#define SDRC_CR_NC_10         (2 << 0)   /* Number of columns = 10 */
#define SDRC_CR_NC_11         (3 << 0)   /* Number of columns = 11 */


/* SDRC_LPR - Low Power Register */
#define SDRC_LPR_LPCB         BIT0       /* 1 = De-assert CKE between accesses */
#define SDRAMC_LPCB     (0x3 <<  0) /* (SDRAMC) Low-power Configurations */
#define SDRAMC_LPCB_DISABLE              (0x0) /* (SDRAMC) Disable Low Power Features */
#define SDRAMC_LPCB_SELF_REFRESH         (0x1) /* (SDRAMC) Enable SELF_REFRESH */
#define SDRAMC_LPCB_POWER_DOWN           (0x2) /* (SDRAMC) Enable POWER_DOWN */
#define SDRAMC_LPCB_DEEP_POWER_DOWN      (0x3) /* (SDRAMC) Enable DEEP_POWER_DOWN */
#define SDRAMC_PASR     (0x7 <<  4) /* (SDRAMC) Partial Array Self Refresh (only for Low Power SDRAM) */
#define SDRAMC_TCSR     (0x3 <<  8) /* (SDRAMC) Temperature Compensated Self Refresh (only for Low Power SDRAM) */
#define SDRAMC_DS       (0x3 << 10) /* (SDRAMC) Drive Strenght (only for Low Power SDRAM) */
#define SDRAMC_TIMEOUT  (0x3 << 12) /* (SDRAMC) Time to define when Low Power Mode is enabled */
#define SDRAMC_TIMEOUT_0_CLK_CYCLES         (0x0 << 12) /* (SDRAMC) Activate SDRAM Low Power Mode Immediately */
#define SDRAMC_TIMEOUT_64_CLK_CYCLES        (0x1 << 12) /* (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer */
#define SDRAMC_TIMEOUT_128_CLK_CYCLES       (0x2 << 12) /* (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer */

/* SDRC_IER - Interrupt Enable Register */
/* SDRC_IDR - Interrupt Disable Register */
/* SDRC_ISR - Interrupt Mask Register */
/* SDRC_IMR - Interrupt Mask Register */
#define SDRC_INT_RES          BIT0       /* Refresh Error Status */

#endif
