/*  Test_task
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
 *
 *  Input parameters:  NONE
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: tasks.c,v 1.14 2009/08/12 20:50:38 joel Exp $
 */

#include "system.h"
#include <bsp.h>
#include <bsp/irq-generic.h>
#include <at91sam9g20.h>
#include <at91sam9g20_pmc.h>
#include <at91sam9g20_gpio.h>

rtems_task Test_task(
  rtems_task_argument unused
)
{
  rtems_id          tid;
  uint32_t    task_index;
  rtems_status_code status;
  
  PIOB_REG(PIO_PER) |= (BIT0); /* Enable PB0 */
  PIOB_REG(PIO_OER) |= (BIT0); /* Output enable */

  status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &tid );
  task_index = task_number( tid );
  for ( ; ; ) {
 	
	PIOB_REG(PIO_SODR) |= (BIT0); /* Set 1 */
	
	uint32_t tmp = 100000;
	while(tmp--);
        
      PIOB_REG(PIO_CODR) |= (BIT0); /* Set 1 */

   
     // rtems_test_exit( 0 );
    }
    put_name( Task_name[ task_index ], FALSE );
    status = rtems_task_wake_after(
      task_index * 5 * rtems_clock_get_ticks_per_second() );
}
