/*
 *  By Yang Xi <hiyangxi@gmail.com>.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: pmc.c,v 1.2 2009/07/10 15:34:12 joel Exp $
 */

#include <rtems.h>
#include <bsp.h>
#include <pxa255.h>

unsigned int xscale_read_pmc(int reg)
{
  unsigned int val = 0;
  switch(reg){
  case PMC_PMNC:
    asm volatile("mrc p14,0,%0,c0,c1,0\n":"=r"(val):);
    break;
  case PMC_CCNT:
    asm volatile("mrc p14,0,%0,c1,c1,0\n":"=r"(val):);
    break;
  case PMC_INTEN:
    asm volatile("mrc p14,0,%0,c4,c1,0\n":"=r"(val):);
    break;
  case PMC_FLAG:
    asm volatile("mrc p14,0,%0,c5,c1,0\n":"=r"(val):);
    break;
  case PMC_EVTSEL:
    asm volatile("mrc p14,0,%0,c8,c1,0\n":"=r"(val):);
    break;
  case PMC_PMN0:
    asm volatile("mrc p14,0,%0,c0,c2,0\n":"=r"(val):);
    break;
  case PMC_PMN1:
    asm volatile("mrc p14,0,%0,c1,c2,0\n":"=r"(val):);
    break;
  case PMC_PMN2:
    asm volatile("mrc p14,0,%0,c2,c2,0\n":"=r"(val):);
    break;
  case PMC_PMN3:
    asm volatile("mrc p14,0,%0,c3,c2,0\n":"=r"(val):);
    break;
  default:
    val = 0;
    break;
  }
  return val;
}

void xscale_write_pmc(int reg, unsigned int val)
{
  switch(reg){
  case PMC_PMNC:
    asm volatile("mcr p14,0,%0,c0,c1,0\n"::"r"(val));
    break;
  case PMC_CCNT:
    asm volatile("mcr p14,0,%0,c1,c1,0\n"::"r"(val));
    break;
  case PMC_INTEN:
    asm volatile("mcr p14,0,%0,c4,c1,0\n"::"r"(val));
    break;
  case PMC_FLAG:
    asm volatile("mcr p14,0,%0,c5,c1,0\n"::"r"(val));
    break;
  case PMC_EVTSEL:
    asm volatile("mcr p14,0,%0,c8,c1,0\n"::"r"(val));
    break;
  case PMC_PMN0:
    asm volatile("mcr p14,0,%0,c0,c2,0\n"::"r"(val));
    break;
  case PMC_PMN1:
    asm volatile("mcr p14,0,%0,c1,c2,0\n"::"r"(val));
    break;
  case PMC_PMN2:
    asm volatile("mcr p14,0,%0,c2,c2,0\n"::"r"(val));
    break;
  case PMC_PMN3:
    asm volatile("mcr p14,0,%0,c3,c2,0\n"::"r"(val));
    break;
  default:
    break;
  }
}

void xscale_pmc_enable_pmc(void)
{
  unsigned int val;
  val = xscale_read_pmc(PMC_PMNC);
  val = (val | PMC_PMNC_E)&(~PMC_PMNC_PCD);
  xscale_write_pmc(PMC_PMNC,val);
}
void xscale_pmc_disable_pmc(void)
{
  unsigned int val;
  val = xscale_read_pmc(PMC_PMNC);
  val = val & (~PMC_PMNC_E);
  xscale_write_pmc(PMC_PMNC,val);
}

void xscale_pmc_reset_pmc(void)
{
  unsigned int val;
  val = xscale_read_pmc(PMC_PMNC);
  val = val | PMC_PMNC_PCR;
  xscale_write_pmc(PMC_PMNC,val);
}

void xscale_pmc_reset_ccnt(void)
{
  unsigned int val;
  val = xscale_read_pmc(PMC_PMNC);
  val = val | PMC_PMNC_CCR;
  xscale_write_pmc(PMC_PMNC,val);
}

void xscale_pmc_setevent(int reg, unsigned char evt)
{
  unsigned int val;
  val = xscale_read_pmc(PMC_EVTSEL);
  if((reg >= PMC_PMN0) && (reg <= PMC_PMN3)){
    val &= ~(0xff<<(reg-PMC_PMN0)*8);
    val |= evt << (reg-PMC_PMN0)*8;
    xscale_write_pmc(PMC_EVTSEL,val);
  }
}
