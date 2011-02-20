/*
 *  IMFS Node Removal Handler
 *
 *  This file contains the handler used to remove a node when a file type
 *  does not require special actions.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_rmnod.c,v 1.16 2009/06/12 01:53:33 ccj Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#include <rtems.h>
#include <rtems/libio.h>
#include <rtems/libio_.h>

#include "imfs.h"

/*
 *  IMFS_rmnod
 */

int IMFS_rmnod(
  rtems_filesystem_location_info_t  *parent_pathloc, /* IN */
  rtems_filesystem_location_info_t  *pathloc         /* IN */
)
{
  IMFS_jnode_t *the_jnode;

  the_jnode = (IMFS_jnode_t *) pathloc->node_access;

  /*
   * Take the node out of the parent's chain that contains this node
   */

  if ( the_jnode->Parent != NULL ) {
    rtems_chain_extract( (rtems_chain_node *) the_jnode );
    the_jnode->Parent = NULL;
  }

  /*
   * Decrement the link counter and see if we can free the space.
   */

  the_jnode->st_nlink--;
  IMFS_update_ctime( the_jnode );

  /*
   * The file cannot be open and the link must be less than 1 to free.
   */

  if ( !rtems_libio_is_file_open( the_jnode ) && (the_jnode->st_nlink < 1) ) {

    /*
     * Is rtems_filesystem_current this node?
     */

    if ( rtems_filesystem_current.node_access == pathloc->node_access )
       rtems_filesystem_current.node_access = NULL;

    /*
     * Free memory associated with a memory file.
     */

    if ( the_jnode->type == IMFS_SYM_LINK ) {
      if ( the_jnode->info.sym_link.name )
        free( (void*) the_jnode->info.sym_link.name );
    }
    free( the_jnode );
  }

  return 0;

}
