/*
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: preq_sem.c,v 1.6 2004/04/15 04:00:25 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/itron/semaphore.h>
#include <rtems/itron/task.h>
#include <rtems/score/tod.h>

/*
 *  preq_sem - Poll and Request Semaphore
 *
 *  This function implements the ITRON 3.0 preq_sem() service.
 */

ER preq_sem(
  ID semid
)
{
  return twai_sem( semid, TMO_POL );
}
