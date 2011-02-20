/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: act_cyc.c,v 1.2 2009/01/01 15:13:07 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/score/thread.h>
#include <rtems/score/tod.h>

#include <rtems/itron/time.h>

/*
 *  act_cyc - Activate Cyclic Handler
 */

ER act_cyc(
  HNO   cycno __attribute__((unused)),
  UINT  cycact
)
{
  Watchdog_Control *object;

  if(cycact != TCY_OFF || cycact != TCY_ON)
     return E_PAR;

#if 0
  if( object->Object_ID != cycno)
     return E_NOEXS;
#endif

  _Watchdog_Activate(object);

  return E_OK;
}
