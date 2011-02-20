/**
 * @file
 *
 * @ingroup rtems_disk
 *
 * @brief Block device disk management API.
 */

/*
 * Copyright (C) 2001 OKTET Ltd., St.-Petersburg, Russia
 * Author: Victor V. Vengerov <vvv@oktet.ru>
 *
 * @(#) $Id: diskdevs.h,v 1.19 2010/05/17 08:08:30 sh Exp $
 */

#ifndef _RTEMS_DISKDEVS_H
#define _RTEMS_DISKDEVS_H

#include <rtems.h>
#include <rtems/libio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rtems_disk_device rtems_disk_device;

/**
 * @defgroup rtems_disk Block Device Disk Management
 *
 * @ingroup rtems_libblock
 *
 * @brief This module provides functions to manage disk devices.
 *
 * A disk is a set of blocks which are identified by a consecutive set of
 * non-negative integers starting at zero.  There are also logical disks which
 * contain a subset of consecutive disk blocks.  The logical disks are used to
 * represent the partitions of a disk.  The disk devices are accessed via the
 * @ref rtems_bdbuf "block device buffer module".
 *
 * @{
 */

/**
 * @brief Block device block index type.
 */
typedef uint32_t rtems_blkdev_bnum;

/**
 * @brief Block device IO control handler type.
 */
typedef int (*rtems_block_device_ioctl)(
  rtems_disk_device *dd,
  uint32_t req,
  void *argp
);

/**
 * @brief Description of a disk device (logical and physical disks).
 *
 * An array of pointer tables to rtems_disk_device structures is maintained.
 * The first table will be indexed by the major number and the second table
 * will be indexed by the minor number.  This allows quick lookup using a data
 * structure of moderated size.
 */
struct rtems_disk_device {
  /**
   * @brief Device identifier (concatenation of major and minor number).
   */
  dev_t dev;

  /**
   * @brief Physical device identifier (equals the @c dev entry if it specifies a
   * physical device).
   */
  rtems_disk_device *phys_dev;

  /**
   * @brief Driver capabilities.
   */
  uint32_t capabilities;

  /**
   * @brief Disk device name.
   */
  char *name;

  /**
   * @brief Usage counter.
   *
   * Devices cannot be deleted if they are in use.
   */
  unsigned uses;

  /**
   * @brief Start block number.
   *
   * Equals zero for physical devices.  It is a block offset to the related
   * physical device for logical device.
   */
  rtems_blkdev_bnum start;

  /**
   * @brief Size of the physical or logical disk in blocks.
   */
  rtems_blkdev_bnum size;

  /**
   * @brief Device block size in bytes.
   *
   * This is the minimum transfer unit. It can be any size.
   */
  uint32_t block_size;

  /**
   * @brief Device media block size in bytes.
   *
   * This is the media transfer unit the hardware defaults to.
   */
  uint32_t media_block_size;

  /**
   * @brief IO control handler for this disk.
   */
  rtems_block_device_ioctl ioctl;

  /**
   * @brief Private data for the disk driver.
   */
  void *driver_data;

  /**
   * @brief Indicates that this disk should be deleted as soon as the last user
   * releases this disk.
   */
  bool deleted;
};

/**
 * @name Disk Device Data
 *
 * @{
 */

static inline dev_t rtems_disk_get_device_identifier(
  const rtems_disk_device *dd
)
{
  return dd->dev;
}

static inline rtems_device_major_number rtems_disk_get_major_number(
  const rtems_disk_device *dd
)
{
  return rtems_filesystem_dev_major_t(dd->dev);
}

static inline rtems_device_minor_number rtems_disk_get_minor_number(
  const rtems_disk_device *dd
)
{
  return rtems_filesystem_dev_minor_t(dd->dev);
}

static inline void *rtems_disk_get_driver_data(
  const rtems_disk_device *dd
)
{
  return dd->driver_data;
}

static inline uint32_t rtems_disk_get_media_block_size(
  const rtems_disk_device *dd
)
{
  return dd->media_block_size;
}

/** @} */

/**
 * @name Disk Device Maintainance
 *
 * @{
 */

/**
 * @brief Creates a physical disk with device identifier @a dev.
 *
 * The block size @a block_size must be positive.  The disk will have
 * @a block_count blocks.  The block index starts with zero.  The associated disk
 * device driver will be invoked via the IO control handler @a handler.  A
 * device node will be registered in the file system with absolute path @a
 * name, if @a name is not @c NULL.  This function is usually invoked from a
 * block device driver during initialization when a physical device is detected
 * in the system.  The device driver provides an IO control handler to allow
 * block device operations.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_NOT_CONFIGURED Cannot lock disk device operation mutex.
 * @retval RTEMS_INVALID_ADDRESS IO control handler is @c NULL.
 * @retval RTEMS_INVALID_NUMBER Block size is zero.
 * @retval RTEMS_NO_MEMORY Not enough memory.
 * @retval RTEMS_RESOURCE_IN_USE Disk device descriptor is already in use.
 * @retval RTEMS_UNSATISFIED Cannot create device node.
 */
rtems_status_code rtems_disk_create_phys(
  dev_t dev,
  uint32_t block_size,
  rtems_blkdev_bnum block_count,
  rtems_block_device_ioctl handler,
  void *driver_data,
  const char *name
);

/**
 * @brief Creates a logical disk with device identifier @a dev.
 *
 * A logical disk manages a subset of consecutive blocks contained in the
 * physical disk with identifier @a phys.  The start block index of the logical
 * disk device is @a begin_block.  The block count of the logcal disk will be
 * @a block_count.  The blocks must be within the range of blocks managed by
 * the associated physical disk device.  A device node will be registered in
 * the file system with absolute path @a name, if @a name is not @c NULL.  The
 * block size and IO control handler are inherited by the physical disk.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_NOT_CONFIGURED Cannot lock disk device operation mutex.
 * @retval RTEMS_INVALID_ID Specified physical disk identifier does not
 * correspond to a physical disk.
 * @retval RTEMS_INVALID_NUMBER Begin block or block count are out of range.
 * @retval RTEMS_NO_MEMORY Not enough memory.
 * @retval RTEMS_RESOURCE_IN_USE Disk device descriptor for logical disk
 * identifier is already in use.
 * @retval RTEMS_UNSATISFIED Cannot create device node.
 */
rtems_status_code rtems_disk_create_log(
  dev_t dev,
  dev_t phys,
  rtems_blkdev_bnum begin_block,
  rtems_blkdev_bnum block_count,
  const char *name
);

/**
 * @brief Deletes a physical or logical disk device with identifier @a dev.
 *
 * Marks the disk device as deleted.  When a physical disk device is deleted,
 * all corresponding logical disk devices will marked as deleted too.  Disks
 * that are marked as deleted and have a usage counter of zero will be deleted.
 * The corresponding device nodes will be removed from the file system.  In
 * case of a physical disk deletion the IO control handler will be invoked with
 * a RTEMS_BLKIO_DELETED request.  Disks that are still in use will be deleted
 * upon release.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_NOT_CONFIGURED Cannot lock disk device operation mutex.
 * @retval RTEMS_INVALID_ID No disk for specified device identifier.
 */
rtems_status_code rtems_disk_delete(dev_t dev);

/**
 * @brief Returns the disk device descriptor for the device identifier @a dev.
 *
 * Increments usage counter by one.  You should release the disk device
 * descriptor with rtems_disk_release().
 *
 * @return Pointer to the disk device descriptor or @c NULL if no corresponding
 * disk exists.
 */
rtems_disk_device *rtems_disk_obtain(dev_t dev);

/**
 * @brief Releases the disk device descriptor @a dd.
 *
 * Decrements usage counter by one.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 */
rtems_status_code rtems_disk_release(rtems_disk_device *dd);

/** @} */

/**
 * @name Disk Management
 *
 * @{
 */

/**
 * @brief Initializes the disk device management.
 *
 * This functions returns successful if the disk device management is already
 * initialized.  There is no protection against concurrent access.
 *
 * @retval RTEMS_SUCCESSFUL Successful initialization.
 * @retval RTEMS_NO_MEMORY Not enough memory or no semaphore available.
 * @retval RTEMS_UNSATISFIED Block device buffer initialization failed.
 */
rtems_status_code rtems_disk_io_initialize(void);

/**
 * @brief Releases all resources allocated for disk device management.
 *
 * There is no protection against concurrent access.  If parts of the system
 * are still in use the behaviour is undefined.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 */
rtems_status_code rtems_disk_io_done(void);

/** @} */

/** @} */

/**
 * @brief Disk device iterator.
 *
 * Returns the next disk device descriptor with a device identifier larger than
 * @a dev.  If there is no such device, @c NULL will be returned.  Use minus
 * one to start the search.
 *
 * @code
 * rtems_status_code sc = RTEMS_SUCCESSFUL;
 * rtems_disk_device *dd = (dev_t) -1;
 *
 * while (sc == RTEMS_SUCCESSFUL && (dd = rtems_disk_next(dev)) != NULL) {
 *   dev = rtems_disk_get_device_identifier(dd);
 *   sc = rtems_disk_release(dd);
 * }
 * @endcode
 */
rtems_disk_device *rtems_disk_next(dev_t dev);

#ifdef __cplusplus
}
#endif

#endif
