/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: bspgetcpuclockspeed.c,v 1.2 2009/11/29 14:59:41 ralf Exp $
 */

#include <bsp.h>

uint32_t bsp_get_CPU_clock_speed(void)
{
  return 60000000;
}
