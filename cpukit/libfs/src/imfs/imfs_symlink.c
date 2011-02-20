/*
 *  IMFS_symlink
 *
 *  The following rouine creates a new symbolic link node under parent
 *  with the name given in name.  The node is set to point to the node at
 *  to_loc.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_symlink.c,v 1.14 2010/01/19 19:31:00 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "imfs.h"
#include <rtems/libio_.h>
#include <rtems/seterr.h>

int IMFS_symlink(
  rtems_filesystem_location_info_t  *parent_loc,
  const char                        *link_name,
  const char                        *node_name
)
{
  IMFS_types_union   info;
  IMFS_jnode_t      *new_node;
  char               new_name[ IMFS_NAME_MAX + 1 ];
  int                i;

  /*
   * Remove any separators at the end of the string.
   */
  IMFS_get_token( node_name, strlen( node_name ), new_name, &i );

  /*
   * Duplicate link name
   */
  info.sym_link.name = strdup(link_name);
  if (info.sym_link.name == NULL) {
    rtems_set_errno_and_return_minus_one(ENOMEM);
  }

  /*
   *  Create a new link node.
   *
   *  NOTE: Coverity CID 22 notes this as a resource leak.
   *        While technically not a leak, it indicated that IMFS_create_node
   *        was ONLY passed a NULL when we created the root node.  We
   *        added a new IMFS_create_root_node() so this path no longer
   *        existed.  The result was simpler code which should not have
   *        this path. 
   */
  new_node = IMFS_create_node(
    parent_loc,
    IMFS_SYM_LINK,
    new_name,
    ( S_IFLNK | ( S_IRWXU | S_IRWXG | S_IRWXO )),
    &info
  );

  if (new_node == NULL) {
    free(info.sym_link.name);
    rtems_set_errno_and_return_minus_one(ENOMEM);
  }

  return 0;
}
