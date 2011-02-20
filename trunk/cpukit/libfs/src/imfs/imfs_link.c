/*
 *  IMFS_link
 *
 *  The following rouine creates a new link node under parent with the
 *  name given in name.  The link node is set to point to the node at
 *  to_loc.
 *
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_link.c,v 1.13 2010/01/19 19:31:00 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include "imfs.h"
#include <rtems/libio_.h>
#include <rtems/seterr.h>

int IMFS_link(
  rtems_filesystem_location_info_t  *to_loc,      /* IN */
  rtems_filesystem_location_info_t  *parent_loc,  /* IN */
  const char                        *token        /* IN */
)
{
  IMFS_types_union   info;
  IMFS_jnode_t      *new_node;
  char               new_name[ IMFS_NAME_MAX + 1 ];
  int                i;

  /*
   *  Verify this node can be linked to.
   */
  info.hard_link.link_node = to_loc->node_access;
  if ( info.hard_link.link_node->st_nlink >= LINK_MAX )
    rtems_set_errno_and_return_minus_one( EMLINK );

  /*
   * Remove any separators at the end of the string.
   */
  IMFS_get_token( token, strlen( token ), new_name, &i );

  /*
   *  Create a new link node.
   *
   *  NOTE: Coverity Id 19 reports this as a leak
   *        While technically not a leak, it indicated that IMFS_create_node
   *        was ONLY passed a NULL when we created the root node.  We
   *        added a new IMFS_create_root_node() so this path no longer
   *        existed.  The result was simpler code which should not have
   *        this path. 
   */
  new_node = IMFS_create_node(
    parent_loc,
    IMFS_HARD_LINK,
    new_name,
    ( S_IFLNK | ( S_IRWXU | S_IRWXG | S_IRWXO )),
    &info
  );

  if ( !new_node )
    rtems_set_errno_and_return_minus_one( ENOMEM );

  /*
   * Increment the link count of the node being pointed to.
   */
  info.hard_link.link_node->st_nlink++;
  IMFS_update_ctime( info.hard_link.link_node );

  return 0;
}
