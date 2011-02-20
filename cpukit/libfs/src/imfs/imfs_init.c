/*
 *  IMFS Initialization
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_init.c,v 1.17 2010/05/31 13:56:36 ccj Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>         /* for mkdir */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <assert.h>

#include "imfs.h"
#include <rtems/libio_.h>

#if defined(IMFS_DEBUG)
#include <stdio.h>
#endif

/*
 *  IMFS file system operations table
 */

const rtems_filesystem_operations_table  IMFS_ops = {
  IMFS_eval_path,
  IMFS_evaluate_for_make,
  IMFS_link,
  IMFS_unlink,
  IMFS_node_type,
  IMFS_mknod,
  IMFS_chown,
  IMFS_freenodinfo,
  IMFS_mount,
  IMFS_initialize,
  IMFS_unmount,
  IMFS_fsunmount,
  IMFS_utime,
  IMFS_evaluate_link,
  IMFS_symlink,
  IMFS_readlink,
  IMFS_rename,
  NULL
};

/*
 *  IMFS_initialize
 */

int IMFS_initialize(
  rtems_filesystem_mount_table_entry_t *temp_mt_entry,
  const void                           *data
)
{
   return IMFS_initialize_support(
     temp_mt_entry,
     &IMFS_ops,
     &IMFS_memfile_handlers,
     &IMFS_directory_handlers
   );
}
