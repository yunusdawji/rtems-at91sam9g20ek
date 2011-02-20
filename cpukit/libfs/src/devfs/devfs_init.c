/*
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: devfs_init.c,v 1.5 2010/05/31 13:56:36 ccj Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <rtems.h>
#include <rtems/seterr.h>
#include <rtems/score/wkspace.h>
#include "devfs.h"

rtems_filesystem_operations_table devFS_ops =
{
    devFS_evaluate_path,
    devFS_evaluate_for_make,
    NULL,
    NULL,
    devFS_node_type,
    devFS_mknod,
    NULL,
    NULL,
    NULL,
    devFS_initialize,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};


rtems_filesystem_file_handlers_r devFS_file_handlers =
{
    devFS_open,
    devFS_close,
    devFS_read,
    devFS_write,
    devFS_ioctl,
    NULL,
    devFS_stat,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};



int devFS_initialize(
  rtems_filesystem_mount_table_entry_t *temp_mt_entry,
  const void                           *data
)
{
  rtems_device_name_t  *device_name_table;

  /* allocate device only filesystem name table */
  device_name_table = (rtems_device_name_t *)_Workspace_Allocate(
        sizeof( rtems_device_name_t ) * ( rtems_device_table_size )
        );

  /* no memory for device filesystem */
  if (!device_name_table)
      rtems_set_errno_and_return_minus_one( ENOMEM );

  memset(
    device_name_table, 0,
    sizeof( rtems_device_name_t ) * ( rtems_device_table_size )
    );

  /* set file handlers */
  temp_mt_entry->mt_fs_root.handlers     = &devFS_file_handlers;
  temp_mt_entry->mt_fs_root.ops          = &devFS_ops;

  /* Set the node_access to device name table */
  temp_mt_entry->mt_fs_root.node_access = (void *)device_name_table;

  return 0;
}

