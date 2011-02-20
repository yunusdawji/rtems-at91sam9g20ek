/*
 *  Free IMFS Node Support Routines
 *
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_free.c,v 1.8 2004/04/17 08:34:41 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>

#include <rtems/libio_.h>
#include "imfs.h"

/*
 *  IMFS_freenodinfo
 *
 *  This routine is the IMFS free node handler for the file system
 *  operations table.
 *
 *  The In Memory File System keeps its nodes in memory.  This routine
 *  is for file sytems that do not.
 */

int IMFS_freenodinfo(
 rtems_filesystem_location_info_t      *pathloc       /* IN */
)
{
  return 0;
}
