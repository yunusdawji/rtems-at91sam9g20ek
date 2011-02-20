/*
 * AT91SAM9G20EK Memory map
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 * File from the old CSB337 RTEMS BSP
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
 *  $Id: memmap.c,v 1.5 2009/12/04 18:24:52 joel Exp $
 */

#include <rtems.h>
#include <libcpu/mmu.h>

#include <bspopts.h>

/* Remember, the ARM926 has 64 TLBs. If you have more 1MB sections than
 * that, you'll have TLB lookups, which could hurt performance.
 */
mmu_sect_map_t mem_map[] = {
/*  <phys addr>  <virt addr> <size> <flags> */
    {0x00200000, 0x00000000,   1,    MMU_CACHE_NONE},     /* SRAM */
    {0x00200000, 0x00200000,   1,    MMU_CACHE_NONE},     /* SRAM 0 */
    {0x00300000, 0x00300000,   1,    MMU_CACHE_NONE},     /* SRAM 1 */
    {0x10000000, 0x10000000,   1,    MMU_CACHE_NONE},     /* FLASH */
    {0x20000000, 0x20000000,  64,    MMU_CACHE_WTHROUGH}, /* SDRAM */
    {0x30000000, 0x30000000,   1,    MMU_CACHE_NONE},     /* Video buffer - 8MB */
    {0x40000000, 0x40000000,   256,  MMU_CACHE_NONE},     /* NAND FLASH EBI_CS3 */
    {0x50000000, 0x50000000,   1,    MMU_CACHE_NONE},     /* CF CE 1 */
    {0x60000000, 0x60000000,   1,    MMU_CACHE_NONE},     /* CF CE 1 */
    {0x70000000, 0x70000000,   1,    MMU_CACHE_NONE},     /* CF CE 2 */
    {0x80000000, 0x80000000,   1,    MMU_CACHE_NONE},     /* Expansion CS0 */
    {0xfff00000, 0xfff00000,   1,    MMU_CACHE_NONE},     /* Internal regs */
    {0x00000000, 0x00000000,   0,    0}                   /* The end */
};

