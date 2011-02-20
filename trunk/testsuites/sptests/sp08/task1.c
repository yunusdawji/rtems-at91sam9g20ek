/*  Task_1
 *
 *  This routine serves as a test task.  It verifies all combinations of
 *  task mode changes.
 *
 *  Input parameters:
 *    argument - task argument
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
 *  $Id: task1.c,v 1.9 2003/09/04 18:53:47 joel Exp $
 */

#include "system.h"

rtems_task Task_1(
  rtems_task_argument argument
)
{
  rtems_mode        previous_mode;
  rtems_status_code status;

/* BEGINNING OF RTEMS_ASR */

  status = rtems_task_mode( RTEMS_ASR, RTEMS_ASR_MASK, &previous_mode );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_ASR                  - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_NO_ASR,
    RTEMS_ASR_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_NO_ASR               - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_NO_ASR,
    RTEMS_ASR_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_NO_ASR               - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_ASR,
    RTEMS_ASR_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_ASR                  - previous mode: ",
    previous_mode
  );

/* END OF RTEMS_ASR */

/* BEGINNING OF RTEMS_TIMESLICE */

  status = rtems_task_mode(
    RTEMS_NO_TIMESLICE,
    RTEMS_TIMESLICE_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_NO_TIMESLICE         - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_TIMESLICE,
    RTEMS_TIMESLICE_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_TIMESLICE            - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_TIMESLICE,
    RTEMS_TIMESLICE_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_TIMESLICE            - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_NO_TIMESLICE,
    RTEMS_TIMESLICE_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_NO_TIMESLICE         - previous mode: ",
    previous_mode
  );

/* END OF RTEMS_TIMESLICE */

/* BEGINNING OF RTEMS_PREEMPT */

  status = rtems_task_mode(
    RTEMS_PREEMPT,
    RTEMS_PREEMPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_PREEMPT              - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_NO_PREEMPT,
    RTEMS_PREEMPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_NO_PREEMPT           - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_NO_PREEMPT,
    RTEMS_PREEMPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_NO_PREEMPT           - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_PREEMPT,
    RTEMS_PREEMPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_PREEMPT              - previous mode: ",
    previous_mode
  );

/* END OF RTEMS_PREEMPT */

/* BEGINNING OF RTEMS_INTERRUPT_LEVEL */

  status = rtems_task_mode(
    RTEMS_INTERRUPT_LEVEL(3),
    RTEMS_INTERRUPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_INTERRUPT_LEVEL( 3 ) - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_INTERRUPT_LEVEL(5),
    RTEMS_INTERRUPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - RTEMS_INTERRUPT_LEVEL( 5 ) - previous mode: ",
    previous_mode
  );

/* END OF RTEMS_INTERRUPT_LEVEL */

/* BEGINNING OF COMBINATIONS */

  status = rtems_task_mode(
    RTEMS_INTERRUPT_LEVEL(3) | RTEMS_NO_ASR |
      RTEMS_TIMESLICE | RTEMS_NO_PREEMPT,
    RTEMS_INTERRUPT_MASK | RTEMS_ASR_MASK |
      RTEMS_TIMESLICE_MASK | RTEMS_PREEMPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - set all modes        - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_INTERRUPT_LEVEL(3) | RTEMS_NO_ASR |
      RTEMS_TIMESLICE | RTEMS_NO_PREEMPT,
    RTEMS_INTERRUPT_MASK | RTEMS_ASR_MASK |
      RTEMS_TIMESLICE_MASK | RTEMS_PREEMPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - set all modes        - previous mode: ",
    previous_mode
  );

  status = rtems_task_mode(
    RTEMS_INTERRUPT_LEVEL(0) | RTEMS_ASR | RTEMS_NO_TIMESLICE | RTEMS_PREEMPT,
    RTEMS_INTERRUPT_MASK | RTEMS_ASR_MASK |
    RTEMS_TIMESLICE_MASK | RTEMS_PREEMPT_MASK,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - clear all modes      - previous mode: ",
    previous_mode
  );

/* END OF COMBINATIONS */

/* BEGINNING OF CURRENT MODE */

  status = rtems_task_mode(
    RTEMS_CURRENT_MODE,
    RTEMS_CURRENT_MODE,
    &previous_mode
  );
  directive_failed( status, "rtems_task_mode" );
  put_mode(
    "TA1 - rtems_task_mode - get current mode     - previous mode: ",
    previous_mode
  );

/* END OF CURRENT MODE */

  puts( "*** END OF TEST 8 ***" );
  rtems_test_exit( 0 );
}
