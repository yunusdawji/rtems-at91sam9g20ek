/**
 * @file
 *
 * @ingroup rtems_ramdisk
 *
 * @brief RAM disk block device implementation.
 */

/*
 * Copyright (c) 2009
 * embedded brains GmbH
 * Obere Lagerstr. 30
 * D-82178 Puchheim
 * Germany
 * <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 *
 * $Id: ramdisk-init.c,v 1.3 2010/03/28 03:11:05 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#include <rtems.h>
#include <rtems/ramdisk.h>

const rtems_driver_address_table ramdisk_ops = {
  .initialization_entry = NULL,
  RTEMS_GENERIC_BLOCK_DEVICE_DRIVER_ENTRIES
};

ramdisk *ramdisk_allocate(
  void *area_begin,
  uint32_t block_size,
  rtems_blkdev_bnum block_count,
  bool trace
)
{
  struct ramdisk *rd = malloc(sizeof(struct ramdisk));

  if (rd == NULL) {
    return NULL;
  }

  if (area_begin == NULL) {
    area_begin = calloc(block_count, block_size);
    if (area_begin == NULL) {
      free(rd);

      return NULL;
    }
    rd->malloced = true;
  } else {
    rd->malloced = false;
  }
  rd->block_size = block_size;
  rd->block_num = block_count;
  rd->area = area_begin;
  rd->trace = trace;
  rd->initialized = true;

  return rd;
}

void ramdisk_free(ramdisk *rd)
{
  if (rd != NULL) {
    if (rd->malloced) {
      free(rd->area);
    }
    free(rd);
  }
}

rtems_status_code ramdisk_register(
  uint32_t block_size,
  rtems_blkdev_bnum block_count,
  bool trace,
  const char *disk,
  dev_t *dev_ptr
)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  rtems_device_major_number major = 0;
  ramdisk *rd = NULL;
  dev_t dev = 0;

  sc = rtems_io_register_driver(0, &ramdisk_ops, &major);
  if (sc != RTEMS_SUCCESSFUL) {
    return RTEMS_UNSATISFIED;
  }

  rd = ramdisk_allocate(NULL, block_size, block_count, trace);
  if (rd == NULL) {
    rtems_io_unregister_driver(major);

    return RTEMS_UNSATISFIED;
  }

  dev = rtems_filesystem_make_dev_t(major, 0);

  sc = rtems_disk_create_phys(
    dev,
    block_size,
    block_count,
    ramdisk_ioctl,
    rd,
    disk
  );
  if (sc != RTEMS_SUCCESSFUL) {
    ramdisk_free(rd);
    rtems_io_unregister_driver(major);

    return RTEMS_UNSATISFIED;
  }

  *dev_ptr = dev;

  return RTEMS_SUCCESSFUL;
}
