/*
 *  IMFS_mknod
 *
 *  Routine to create a node in the IMFS file system.
 *
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_mknod.c,v 1.14 2010/01/19 19:31:00 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "imfs.h"
#include <rtems/libio_.h>
#include <rtems/seterr.h>

int IMFS_mknod(
  const char                        *token,      /* IN */
  mode_t                             mode,       /* IN */
  dev_t                              dev,        /* IN */
  rtems_filesystem_location_info_t  *pathloc     /* IN/OUT */
)
{
  IMFS_token_types   type = 0;
  IMFS_jnode_t      *new_node;
  int                result;
  char               new_name[ IMFS_NAME_MAX + 1 ];
  IMFS_types_union   info;

  IMFS_get_token( token, strlen( token ), new_name, &result );

  /*
   *  Figure out what type of IMFS node this is.
   */
  if ( S_ISDIR(mode) )
    type = IMFS_DIRECTORY;
  else if ( S_ISREG(mode) )
    type = IMFS_MEMORY_FILE;
  else if ( S_ISBLK(mode) || S_ISCHR(mode) ) {
    type = IMFS_DEVICE;
    rtems_filesystem_split_dev_t( dev, info.device.major, info.device.minor );
  }
  else if (S_ISFIFO(mode))
    type = IMFS_FIFO;
  else  {
    rtems_set_errno_and_return_minus_one( EINVAL );
  }

  /*
   *  Allocate and fill in an IMFS jnode
   *
   *  NOTE: Coverity Id 21 reports this as a leak.
   *        While technically not a leak, it indicated that IMFS_create_node
   *        was ONLY passed a NULL when we created the root node.  We
   *        added a new IMFS_create_root_node() so this path no longer
   *        existed.  The result was simpler code which should not have
   *        this path. 
   */
  new_node = IMFS_create_node(
    pathloc,
    type,
    new_name,
    mode,
    &info
  );

  if ( !new_node )
    rtems_set_errno_and_return_minus_one( ENOMEM );

  return 0;
}
