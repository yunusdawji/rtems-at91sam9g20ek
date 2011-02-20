/*
 *  IMFS_fcntl
 *
 *  The following routine does a fcntl on an IMFS node.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_fcntl.c,v 1.5 2004/04/17 08:34:41 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "imfs.h"

int IMFS_fcntl(
  int            cmd,
  rtems_libio_t *iop
)
{
  return 0;
}
