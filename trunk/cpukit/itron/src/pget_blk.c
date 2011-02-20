/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: pget_blk.c,v 1.2 2009/01/01 15:13:07 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>

#include <rtems/itron/vmempool.h>

/*
 *  pget_blk - Poll and Get Variable-Size Memory Block
 */

ER pget_blk(
  VP  *p_blk __attribute__((unused)),
  ID   mplid __attribute__((unused)),
  INT  blksz __attribute__((unused))
)
{
  return E_OK;
}
