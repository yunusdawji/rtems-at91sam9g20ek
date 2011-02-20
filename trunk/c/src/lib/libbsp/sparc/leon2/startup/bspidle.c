/*
 *  LEON2 Idle Thread with power-down function
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  Ported to LEON implementation of the SPARC by On-Line Applications
 *  Research Corporation (OAR) under contract to the European Space
 *  Agency (ESA).
 *
 *  LEON modifications of respective RTEMS file: COPYRIGHT (c) 1995.
 *  European Space Agency.
 *
 *  $Id: bspidle.c,v 1.2 2009/11/29 15:33:26 ralf Exp $
 */

#include <bsp.h>

void *bsp_idle_thread( uintptr_t ignored )
{
  while (1) {
    /* make sure on load follows store to power-down reg */
    LEON_REG.Power_Down = LEON_REG.Power_Down;
  }
  return NULL;
}

