/*
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: devfs_eval.c,v 1.6.2.1 2010/08/27 17:33:11 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/seterr.h>
#include <fcntl.h>
#include <assert.h>
#include "devfs.h"

/**
 *  The following defines the device-only filesystem operating
 *  handlers.
 */

extern rtems_filesystem_operations_table devFS_ops;

/**
 *  The following defines the device-only filesystem operating
 *  handlers.
 */

extern rtems_filesystem_file_handlers_r  devFS_file_handlers;

int devFS_evaluate_path(
  const char                        *pathname,
  size_t                             pathnamelen,
  int                                flags,
  rtems_filesystem_location_info_t  *pathloc
)
{
  int                   i;
  rtems_device_name_t  *device_name_table;

  /* see if 'flags' is valid */
  if ( !rtems_libio_is_valid_perms( flags ) )
    rtems_set_errno_and_return_minus_one( EPERM );

  /* get the device name table */
  device_name_table = (rtems_device_name_t *)pathloc->node_access;
  if (!device_name_table)
    rtems_set_errno_and_return_minus_one( EFAULT );

  for (i = 0; i < rtems_device_table_size; i++) {
    if (!device_name_table[i].device_name)
      continue;

    if (strncmp(pathname, device_name_table[i].device_name, pathnamelen) != 0)
      continue;

    if (device_name_table[i].device_name[pathnamelen] != '\0')
      continue;

    /* find the device, set proper values */
    pathloc->node_access = (void *)&device_name_table[i];
    pathloc->handlers = &devFS_file_handlers;
    pathloc->ops = &devFS_ops;
    pathloc->mt_entry = rtems_filesystem_root.mt_entry;
    return 0;
  }

  /* no such file or directory */
  rtems_set_errno_and_return_minus_one( ENOENT );
}



int devFS_evaluate_for_make(
   const char                         *path,
   rtems_filesystem_location_info_t   *pathloc,
   const char                        **name
)
{
    /* we do nothing, just set name to path */
   *name = path;
    return 0;
}

