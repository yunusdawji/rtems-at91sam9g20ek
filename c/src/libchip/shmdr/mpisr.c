/*  _Shm_isr()
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: mpisr.c,v 1.10 2008/09/05 14:48:37 joel Exp $
 */

#include <rtems.h>
#include "shm_driver.h"

void Shm_isr(void)
{
  Shm_Interrupt_count += 1;
  rtems_multiprocessing_announce();
}
