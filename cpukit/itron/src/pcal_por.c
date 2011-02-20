/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: pcal_por.c,v 1.2 2009/01/01 15:13:07 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/itron/port.h>

/*
 *  pcal_por - Poll and Call Port for Rendezvous
 */

ER pcal_por(
  VP   msg __attribute__((unused)),
  INT *p_rmsgsz __attribute__((unused)),
  ID   porid __attribute__((unused)),
  UINT calptn __attribute__((unused)),
  INT  cmsgsz __attribute__((unused))
)
{
  return E_OK;
}
