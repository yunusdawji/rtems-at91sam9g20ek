/*
 * Atmel AT91SAM9G20 PMC functions
 *
 * Copyright (c) 2004 by Jay Monkman <jtm@lopingdog.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: pmc.c,v 1.4 2009/11/30 04:58:24 ralf Exp $
 */

#include <rtems.h>
#include <bsp.h>
#include <at91sam9g20.h>
#include <at91sam9g20_pmc.h>

int at91sam9g20_get_mainclk(void)
{
    return BSP_MAIN_FREQ;
}

int at91sam9g20_get_slck(void)
{
    return BSP_SLCK_FREQ;
}

int at91sam9g20_get_mck(void)
{
    uint32_t mck_reg;
    uint32_t mck_freq = 0;  /* to avoid warnings */
    uint32_t pll_reg;
    int prescaler = 0;  /* to avoid warnings */

    mck_reg = PMC_REG(PMC_MCKR);

    switch(mck_reg & PMC_MCKR_PRES_MASK) {
    case PMC_MCKR_PRES_1:
	prescaler = 1;
	break;
    case PMC_MCKR_PRES_2:
        prescaler = 2;
        break;
    case PMC_MCKR_PRES_4:
        prescaler = 4;
        break;
    case PMC_MCKR_PRES_8:
        prescaler = 8;
        break;
    case PMC_MCKR_PRES_16:
        prescaler = 16;
        break;
    case PMC_MCKR_PRES_32:
        prescaler = 32;
        break;
    case PMC_MCKR_PRES_64:
        prescaler = 64;
        break;
    }

    /* Let's find out what MCK's source is */
    switch (mck_reg & PMC_MCKR_CSS_MASK) {
    case PMC_MCKR_CSS_SLOW:
        /* I'm assuming the slow clock is 32.768 KHz */
        mck_freq = at91sam9g20_get_slck() / prescaler;
        break;

    case PMC_MCKR_CSS_MAIN:
        mck_freq = at91sam9g20_get_mainclk() / prescaler;
        break;

    case PMC_MCKR_CSS_PLLA:
        pll_reg = PMC_REG(PMC_PLLAR);
        mck_freq = at91sam9g20_get_mainclk() / prescaler;
        mck_freq = mck_freq / (pll_reg & PMC_PLLAR_DIV_MASK);
        mck_freq = mck_freq * (((pll_reg & PMC_PLLAR_MUL_MASK) >> 16) + 1);
        break;

    case PMC_MCKR_CSS_PLLB:
        pll_reg = PMC_REG(PMC_PLLBR);
        mck_freq = at91sam9g20_get_mainclk() / prescaler;
        mck_freq = mck_freq / (pll_reg & PMC_PLLBR_DIV_MASK);
        mck_freq = mck_freq * (((pll_reg & PMC_PLLBR_MUL_MASK) >> 16) + 1);
        break;
    }

    if ((mck_reg & PMC_MCKR_MDIV_MASK) == PMC_MCKR_MDIV_1) {
	mck_freq = mck_freq / 1;
    } else if ((mck_reg & PMC_MCKR_MDIV_MASK) == PMC_MCKR_MDIV_2) {
        mck_freq = mck_freq / 2;
    } else if ((mck_reg & PMC_MCKR_MDIV_MASK) == PMC_MCKR_MDIV_4) {
        mck_freq = mck_freq / 4;
    } else if ((mck_reg & PMC_MCKR_MDIV_MASK) == PMC_MCKR_MDIV_6) {
	mck_freq = mck_freq / 6;
    }

    return mck_freq;
}

int at91sam9g20_get_pck(void)
{
    uint32_t pck_reg;
    uint32_t pck_freq = 0;  /* to avoid warnings */

    pck_reg = PMC_REG(PMC_MCKR);

    if ((pck_reg & PMC_MCKR_PDIV_MASK) == PMC_MCKR_PDIV_1) {
	pck_freq = pck_freq / 1;
    } else if ((pck_reg & PMC_MCKR_PDIV_MASK) == PMC_MCKR_PDIV_2) {
     	pck_freq = pck_freq / 2; 
     }
    
    return pck_freq;
}
