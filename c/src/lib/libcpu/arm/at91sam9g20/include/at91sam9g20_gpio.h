/*
 * AT91SAM9G20 GPIO definitions
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
#ifndef AT91SAM9G20_GPIO_H
#define AT91SAM9G20_GPIO_H

#include <bits.h>

/* Register Offsets */
#define PIO_PER         0x00    /* PIO Enable Register */
#define PIO_PDR         0x04    /* PIO Disable Register */
#define PIO_PSR         0x08    /* PIO Status Register */
#define PIO_OER         0x10    /* Output Enable Register */
#define PIO_ODR         0x14    /* Output Disable Registerr */
#define PIO_OSR         0x18    /* Output Status Register */
#define PIO_IFER        0x20    /* Input Filter Enable Register */
#define PIO_IFDR        0x24    /* Input Filter Disable Register */
#define PIO_IFSR        0x28    /* Input Filter Status Register */
#define PIO_SODR        0x30    /* Set Output Data Register */
#define PIO_CODR        0x34    /* Clear Output Data Register */
#define PIO_ODSR        0x38    /* Output Data Status Register */
#define PIO_PDSR        0x3c    /* Pin Data Status Register */
#define PIO_IER         0x40    /* Interrupt Enable Register */
#define PIO_IDR         0x44    /* Interrupt Disable Register */
#define PIO_IMR         0x48    /* Interrupt Mask Register */
#define PIO_ISR         0x4c    /* Interrupt Status Register */
#define PIO_MDER        0x50    /* Multi-driver Enable Register */
#define PIO_MDDR        0x54    /* Multi-driver Disable Register */
#define PIO_MDSR        0x58    /* Multi-driver Status Register */
#define PIO_PUDR        0x60    /* Pull-up Disable Register */
#define PIO_PUER        0x64    /* Pull-up Enable Register */
#define PIO_PUSR        0x68    /* Pad Pull-up Status Register */
#define PIO_ASR         0x70    /* Select A Register */
#define PIO_BSR         0x74    /* Select B Register */
#define PIO_ABSR        0x78    /* AB Select Status Register */
#define PIO_OWER        0xA0    /* Output Write Enable Register */
#define PIO_OWDR        0xA4    /* Output Write Disable Register */
#define PIO_OWSR        0xA8    /* Output Write Status Register */


/*
 * The AT91SAM9G20 GPIO's are spread across three 32-bit ports A-C.
 * To make it easier to interface with them and to eliminate the need
 * to track which GPIO is in which port, we     convert the Port x, Bit y
 * into a single GPIO number 0 - 95.
 *
 * Board specific defines will assign the board level signal to a
 * virutal GPIO.
 *
 * PORT A
 */
#define GPIO_0          BIT0
#define GPIO_1          BIT1
#define GPIO_2          BIT2
#define GPIO_3          BIT3
#define GPIO_4          BIT4
#define GPIO_5          BIT5
#define GPIO_6          BIT6
#define GPIO_7          BIT7
#define GPIO_8          BIT8
#define GPIO_9          BIT9
#define GPIO_10         BIT10
#define GPIO_11         BIT11
#define GPIO_12         BIT12
#define GPIO_13         BIT13
#define GPIO_14         BIT14
#define GPIO_15         BIT15
#define GPIO_16         BIT16
#define GPIO_17         BIT17
#define GPIO_18         BIT18
#define GPIO_19         BIT19
#define GPIO_20         BIT20
#define GPIO_21         BIT21
#define GPIO_22         BIT22
#define GPIO_23         BIT23
#define GPIO_24         BIT24
#define GPIO_25         BIT25
#define GPIO_26         BIT26
#define GPIO_27         BIT27
#define GPIO_28         BIT28
#define GPIO_29         BIT29
#define GPIO_30         BIT30
#define GPIO_31         BIT31
/* PORT B */
#define GPIO_32         BIT0
#define GPIO_33         BIT1
#define GPIO_34         BIT2
#define GPIO_35         BIT3
#define GPIO_36         BIT4
#define GPIO_37         BIT5
#define GPIO_38         BIT6
#define GPIO_39         BIT7
#define GPIO_40         BIT8
#define GPIO_41         BIT9
#define GPIO_42         BIT10
#define GPIO_43         BIT11
#define GPIO_44         BIT12
#define GPIO_45         BIT13
#define GPIO_46         BIT14
#define GPIO_47         BIT15
#define GPIO_48         BIT16
#define GPIO_49         BIT17
#define GPIO_50         BIT18
#define GPIO_51         BIT19
#define GPIO_52         BIT20
#define GPIO_53         BIT21
#define GPIO_54         BIT22
#define GPIO_55         BIT23
#define GPIO_56         BIT24
#define GPIO_57         BIT25
#define GPIO_58         BIT26
#define GPIO_59         BIT27
#define GPIO_60         BIT28
#define GPIO_61         BIT29
#define GPIO_62         BIT30
#define GPIO_63         BIT31
/* PORT C */
#define GPIO_64         BIT0
#define GPIO_65         BIT1
#define GPIO_66         BIT2
#define GPIO_67         BIT3
#define GPIO_68         BIT4
#define GPIO_69         BIT5
#define GPIO_70         BIT6
#define GPIO_71         BIT7
#define GPIO_72         BIT8
#define GPIO_73         BIT9
#define GPIO_74         BIT10
#define GPIO_75         BIT11
#define GPIO_76         BIT12
#define GPIO_77         BIT13
#define GPIO_78         BIT14
#define GPIO_79         BIT15
#define GPIO_80         BIT16
#define GPIO_81         BIT17
#define GPIO_82         BIT18
#define GPIO_83         BIT19
#define GPIO_84         BIT20
#define GPIO_85         BIT21
#define GPIO_86         BIT22
#define GPIO_87         BIT23
#define GPIO_88         BIT24
#define GPIO_89         BIT25
#define GPIO_90         BIT26
#define GPIO_91         BIT27
#define GPIO_92         BIT28
#define GPIO_93         BIT29
#define GPIO_94         BIT30
#define GPIO_95         BIT31

/*
 * Most of the GPIO pins can have one of two alternate functions
 * in addition to being GPIO
 *
 * Port A, Alternate Function A
 */
#define PIOA_ASR_MISO   BIT0    /* SPI Master In (RX), Slave out */
#define PIOA_ASR_MOSI   BIT1    /* SPI Master Out (TX), Slave In */
#define PIOA_ASR_SPCK   BIT2    /* SPI Clock */
#define PIOA_ASR_NPCS0  BIT3    /* SPI Chip Select 0 */
#define PIOA_ASR_RTS2   BIT4    /* USART RTS2 */
#define PIOA_ASR_CTS2   BIT5    /* USART CTS2 */
#define PIOA_ASR_MCDA0  BIT6    /*  */
#define PIOA_ASR_MCCDA  BIT7    /*  */
#define PIOA_ASR_MCCK   BIT8    /*  */
#define PIOA_ASR_MCDA1  BIT9    /*  */
#define PIOA_ASR_MCDA2  BIT10   /*  */
#define PIOA_ASR_MCDA3  BIT11   /*  */
#define PIOA_ASR_ETX0   BIT12   /* EMAC TXD0 */
#define PIOA_ASR_ETX1   BIT13   /* EMAC TXD1 */
#define PIOA_ASR_ERX0   BIT14   /* EMAC RX0 */
#define PIOA_ASR_ERX1   BIT15   /* EMAC RX1 */
#define PIOA_ASR_ETXEN  BIT16   /* EMAC TXEN */
#define PIOA_ASR_ERXDV  BIT17   /* EMAC RXDV */
#define PIOA_ASR_ERXER  BIT18   /* EMAC RXER */
#define PIOA_ASR_ETXCK  BIT19   /* EMAC TXCK */
#define PIOA_ASR_EMDC   BIT20   /* EMAC MDC */
#define PIOA_ASR_EMDIO  BIT21   /* EMAC MDIO */
#define PIOA_ASR_ADTRG  BIT22   /*  */
#define PIOA_ASR_TWD    BIT23   /* Two-Wire (I2C) Data */
#define PIOA_ASR_TWCK   BIT24   /* Two-Wire (I2C) Clock */
#define PIOA_ASR_TCLK0  BIT25   /*  */
#define PIOA_ASR_TIOA0  BIT26   /*  */
#define PIOA_ASR_TIOA1  BIT27   /*  */
#define PIOA_ASR_TIOA2  BIT28   /*  */
#define PIOA_ASR_SCK1   BIT29   /*  */
#define PIOA_ASR_SCK2   BIT30   /*  */
#define PIOA_ASR_SCK0   BIT31   /*  */

/* Port A, Alternate Function B */
#define PIOA_BSR_MCDB0  BIT0    /* MMC/SD Card B, Data 0 */
#define PIOA_BSR_MCCDB  BIT1    /*  */
#define PIOA_BSR_MCDB3  BIT3    /* MMC/SD Card B, Data 3 */
#define PIOA_BSR_MCDB2  BIT4    /* MMC/SD Card B, Data 2 */
#define PIOA_BSR_MCDB1  BIT5    /* MMC/SD Card B, Data 1 */
#define PIOA_BSR_EXT2   BIT10   /*  */
#define PIOA_BSR_EXT3   BIT11   /*  */
#define PIOA_BSR_ETXER  BIT22   /*  */
#define PIOA_BSR_ETX2   BIT23   /* ETX2?? */
#define PIOA_BSR_ETX3   BIT24   /*     */
#define PIOA_BSR_ERX2   BIT25   /*  */
#define PIOA_BSR_ERX3   BIT26   /*  */
#define PIOA_BSR_ERXCK  BIT27   /*  */
#define PIOA_BSR_ECRS   BIT28   /*  */
#define PIOA_BSR_ECOL   BIT29   /*  */
#define PIOA_BSR_RXD4   BIT30   /*  */
#define PIOA_BSR_TXD4   BIT31   /*  */

/* Port B, Function A */
#define PIOB_ASR_MISO   BIT0    /* SPI Master In (RX), Slave out  */
#define PIOB_ASR_MOSI   BIT1    /* SPI Master Out (TX), Slave In  */
#define PIOB_ASR_SPCK   BIT2    /* SPI Clock */
#define PIOB_ASR_RNPCS0 BIT3    /* SPI Chip Select 0 */
#define PIOB_ASR_TXD0   BIT4    /* USART 0 TXD */
#define PIOB_ASR_RXD0   BIT5    /* USART 0 RXD */
#define PIOB_ASR_TXD1   BIT6    /* USART 1 TXD */
#define PIOB_ASR_RXD1   BIT7    /* USART 1 RXD */
#define PIOB_ASR_TXD2   BIT8    /* USART 2 TXD */
#define PIOB_ASR_RXD2   BIT9    /* USART 2 RXD */
#define PIOB_ASR_TXD3   BIT10   /* USART 3 TXD */
#define PIOB_ASR_RXD3   BIT11   /* USART 3 RXD */
#define PIOB_ASR_TXD5   BIT12   /* USART 3 TXD */
#define PIOB_ASR_RXD5   BIT13   /* USART 5 RXD */
#define PIOB_ASR_DRXD   BIT14   /* DBUGU RXD   */
#define PIOB_ASR_DTXD   BIT15   /* DBUGU TXD   */
#define PIOB_ASR_TK0    BIT16   /*    */
#define PIOB_ASR_TF0    BIT17   /*    */
#define PIOB_ASR_TD0    BIT18   /*    */
#define PIOB_ASR_RD0    BIT19   /*    */
#define PIOB_ASR_RK0    BIT20   /*    */
#define PIOB_ASR_RF0    BIT21   /*    */
#define PIOB_ASR_DSR0   BIT22   /*    */
#define PIOB_ASR_DCD0   BIT23   /* USART  DCD */
#define PIOB_ASR_DTR0   BIT24   /* USART  DTR */
#define PIOB_ASR_RI0    BIT25   /* USART  RI  */
#define PIOB_ASR_RTS0   BIT26   /* USART 0 RTS */
#define PIOB_ASR_CTS0   BIT27   /*   */
#define PIOB_ASR_RTS1   BIT28   /*   */
#define PIOB_ASR_CTS1   BIT29   /*   */
#define PIOB_ASR_PCK0   BIT30   /*   */
#define PIOB_ASR_PCK1   BIT31   /*   */


/* Port B, Function B */
#define PIOB_BSR_TIOA3  BIT0    /* Timer 3 IO A  */
#define PIOB_BSR_TIOB3  BIT1    /* Timer 3 IO B  */
#define PIOB_BSR_TIOA4  BIT2    /* Timer 4 IO A  */
#define PIOB_BSR_TIOA5  BIT3    /* Timer 5 IO A  */
#define PIOB_BSR_TCLK1  BIT6    /* */
#define PIOB_BSR_TCLK2  BIT7    /*  */
#define PIOB_BSR_D8     BIT10   /* ISI_D8 */
#define PIOB_BSR_D9     BIT11   /* ISI_D9 */
#define PIOB_BSR_D10    BIT12   /* ISI_D10 */
#define PIOB_BSR_D11    BIT13   /* ISI_D11 */
#define PIOB_BSR_TCLK3  BIT16   /*  */
#define PIOB_BSR_TCLK4  BIT17   /*  */
#define PIOB_BSR_TIOB4  BIT18   /*  */
#define PIOB_BSR_TIOB5  BIT19   /*  */
#define PIOB_BSR_D0	     BIT20   /* ISI_D0 */
#define PIOB_BSR_D1	     BIT21   /* ISI_D1 */
#define PIOB_BSR_D2     BIT22   /* ISI_D2 */
#define PIOB_BSR_D3     BIT23   /* ISI_D3 */
#define PIOB_BSR_D4     BIT24   /* ISI_D4 */
#define PIOB_BSR_D5     BIT25   /* ISI_D5 */
#define PIOB_BSR_D6     BIT26   /* ISI_D6 */
#define PIOB_BSR_D7     BIT27   /* ISI_D7 */
#define PIOB_BSR_PCK    BIT28   /* ISI_PCK */
#define PIOB_BSR_VSYNC  BIT29   /* ISI_VSYNC */
#define PIOB_BSR_HSYNC  BIT30   /* ISI_HSYNC */
#define PIOB_BSR_MCK    BIT31   /* ISI_MCK */

/* Port C, Alternate Function A */
#define PIOC_ASR_A23    BIT4    /* A23 */
#define PIOC_ASR_A24    BIT5    /* A24 */
#define PIOC_ASR_TIOB2  BIT6    /*  */
#define PIOC_ASR_TIOB1  BIT7    /*   */
#define PIOC_ASR_NCS4   BIT8    /* CS4 or Compact Flash CS */
#define PIOC_ASR_NCS5   BIT9    /* CS5 or Compact Flash CE1 */
#define PIOC_ASR_A25    BIT10   /* A25 or CS5 or Compact Flash */
#define PIOC_ASR_NCS2   BIT11   /*  */
#define PIOC_ASR_IRQ0   BIT12   /* IRQ0 */
#define PIOC_ASR_FIQ    BIT13   /* FIQ */
#define PIOC_ASR_NCS3   BIT14   /* CS3 or NAND Flash CS */
#define PIOC_ASR_NWAIT  BIT15   /* WAIT */
#define PIOC_ASR_D16    BIT16   /* Databus Bit 16 */
#define PIOC_ASR_D17    BIT17   /* Databus Bit 17 */
#define PIOC_ASR_D18    BIT18   /* Databus Bit 18 */
#define PIOC_ASR_D19    BIT19   /* Databus Bit 19 */
#define PIOC_ASR_D20    BIT20   /* Databus Bit 20 */
#define PIOC_ASR_D21    BIT21   /* Databus Bit 21 */
#define PIOC_ASR_D22    BIT22   /* Databus Bit 22 */
#define PIOC_ASR_D23    BIT23   /* Databus Bit 23 */
#define PIOC_ASR_D24    BIT24   /* Databus Bit 24 */
#define PIOC_ASR_D25    BIT25   /* Databus Bit 25 */
#define PIOC_ASR_D26    BIT26   /* Databus Bit 26 */
#define PIOC_ASR_D27    BIT27   /* Databus Bit 27 */
#define PIOC_ASR_D28    BIT28   /* Databus Bit 28 */
#define PIOC_ASR_D29    BIT29   /* Databus Bit 29 */
#define PIOC_ASR_D30    BIT30   /* Databus Bit 30 */
#define PIOC_ASR_D31    BIT31   /* Databus Bit 31 */

/* Port C, Alternate Function B  */
#define PIOC_BSR_SCK3   BIT0    /*	*/
#define PIOC_BSR_PCK0   BIT1 	/*	*/
#define PIOC_BSR_PCK1   BIT2 	/*	*/
#define PIOC_BSR_NPCS3  BIT3	/*	*/
#define PIOC_BSR_NPCS2  BIT4 	/*	*/
#define PIOC_BSR_NPCS1  BIT5	/*	*/
#define PIOC_BSR_CFCE1  BIT6	/*	*/
#define PIOC_BSR_CFCE2  BIT7    /*	*/
#define PIOC_BSR_RTS3   BIT8 	/*	*/
#define PIOC_BSR_TIOB0  BIT9	/*	*/
#define PIOC_BSR_CTS3   BIT10	/*	*/
#define PIOC_BSR_NPCS1  BIT11 	/*	*/
#define PIOC_BSR_NCS7   BIT12	/*	*/
#define PIOC_BSR_NCS6   BIT13	/*	*/
#define PIOC_BSR_IRQ2   BIT14	/*	*/
#define PIOC_BSR_IRQ1   BIT15	/*	*/
#define PIOC_BSR_NPCS2  BIT16  	/*	*/
#define PIOC_BSR_NPCS3  BIT17	/*	*/
#define PIOC_BSR_NPCS1  BIT18	/*	*/
#define PIOC_BSR_NPCS2  BIT19	/*	*/
#define PIOC_BSR_NPCS3  BIT20	/*	*/
#define PIOC_BSR_TCLK5  BIT22 	/*	*/

#endif /* AT91SAM9G20_GPIO_H */
