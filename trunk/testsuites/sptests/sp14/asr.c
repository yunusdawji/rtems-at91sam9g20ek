/*  Process_asr
 *
 *  This is the asynchronous signal routine (asr) for task 1.
 *  It demonstrates that ASRs can block execute and block.
 *
 *  Input parameters:
 *    the_signal_set - signal set
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: asr.c,v 1.11 2009/10/30 13:23:47 ralf Exp $
 */

#include "system.h"
#include "tmacros.h"

rtems_asr Process_asr(
  rtems_signal_set the_signal_set
)
{
  rtems_status_code status;

  printf( "ASR - ENTRY - signal => %08" PRIxrtems_signal_set "\n", the_signal_set );
  switch( the_signal_set ) {
    case RTEMS_SIGNAL_16:
    case RTEMS_SIGNAL_17:
    case RTEMS_SIGNAL_18 | RTEMS_SIGNAL_19:
      break;
    case RTEMS_SIGNAL_0:
    case RTEMS_SIGNAL_1:
      puts( "ASR - rtems_task_wake_after - yield processor" );
      FLUSH_OUTPUT();
      status = rtems_task_wake_after( RTEMS_YIELD_PROCESSOR );
      directive_failed( status, "rtems_task_wake_after yield" );
      break;
    case RTEMS_SIGNAL_3:
      Asr_fired = TRUE;
      break;
  }
  printf( "ASR - EXIT  - signal => %08" PRIxrtems_signal_set "\n", the_signal_set );
  FLUSH_OUTPUT();
}
