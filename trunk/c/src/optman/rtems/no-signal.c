/*
 *  Signal Manager
 *
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: no-signal.c,v 1.13 2008/12/17 20:25:43 joel Exp $
 */

#include <rtems/system.h>
#include <rtems/rtems/status.h>
#include <rtems/score/isr.h>
#include <rtems/score/thread.h>
#include <rtems/score/interr.h>

#include <rtems/rtems/asr.h>
#include <rtems/rtems/modes.h>
#include <rtems/rtems/signal.h>

void _Signal_Manager_initialization(void)
{
}
 
