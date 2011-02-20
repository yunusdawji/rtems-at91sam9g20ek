/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: def_int.c,v 1.2 2009/01/01 15:13:07 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/itron/intr.h>

/*
 *  def_int - Define Interrupt Handler
 */

ER def_int(
  UINT    dintno __attribute__((unused)),
  T_DINT *pk_dint __attribute__((unused))
)
{
  return E_OK;
}
