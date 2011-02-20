/*
 *  COPYRIGHT (c) 2010 Chris Johns <chrisj@rtems.org>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: rtems-rfs-rtems-dir.c,v 1.3.2.2 2010/10/11 21:12:48 ccj Exp $
 */
/**
 * @file
 *
 * @ingroup rtems-rfs
 *
 * RTEMS RFS Directory Access Routines
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <inttypes.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <rtems/rfs/rtems-rfs-dir.h>
#include <rtems/rfs/rtems-rfs-link.h>
#include "rtems-rfs-rtems.h"

/**
 * This rountine will verify that the node being opened as a directory is in
 * fact a directory node. If it is then the offset into the directory will be
 * set to 0 to position to the first directory entry.
 *
 * @param iop
 * @param pathname
 * @param flag
 * @param mode
 * @@return int
 */
static int
rtems_rfs_rtems_dir_open (rtems_libio_t* iop,
                          const char*    pathname,
                          uint32_t       flag,
                          uint32_t       mode)
{
  rtems_rfs_file_system* fs = rtems_rfs_rtems_pathloc_dev (&iop->pathinfo);
  rtems_rfs_ino          ino = rtems_rfs_rtems_get_iop_ino (iop);
  rtems_rfs_inode_handle inode;
  int                    rc;

  rtems_rfs_rtems_lock (fs);
  
  rc = rtems_rfs_inode_open (fs, ino, &inode, true);
  if (rc)
  {
    rtems_rfs_rtems_unlock (fs);
    return rtems_rfs_rtems_error ("dir_open: opening inode", rc);
  }
  
  if (!RTEMS_RFS_S_ISDIR (rtems_rfs_inode_get_mode (&inode)))
  {
    rtems_rfs_inode_close (fs, &inode);
    rtems_rfs_rtems_unlock (fs);
    return rtems_rfs_rtems_error ("dir_open: not dir", ENOTDIR);
  }
    
  iop->offset = 0;

  rtems_rfs_inode_close (fs, &inode);
  rtems_rfs_rtems_unlock (fs);
  return 0;
}

/**
 * This routine will be called by the generic close routine to cleanup any
 * resources that have been allocated for the management of the file
 *
 * @param iop
 * @retval 0 Always no error.
 */
static int
rtems_rfs_rtems_dir_close (rtems_libio_t* iop)
{
  /*
   * The RFS does not hold any resources. Nothing to do.
   */
  return 0;
}

/**
 * This routine will read the next directory entry based on the directory
 * offset. The offset should be equal to -n- time the size of an individual
 * dirent structure. If n is not an integer multiple of the sizeof a dirent
 * structure, an integer division will be performed to determine directory
 * entry that will be returned in the buffer. Count should reflect -m- times
 * the sizeof dirent bytes to be placed in the buffer.  If there are not -m-
 * dirent elements from the current directory position to the end of the
 * exisiting file, the remaining entries will be placed in the buffer and the
 * returned value will be equal to -m actual- times the size of a directory
 * entry.
 */
static ssize_t
rtems_rfs_rtems_dir_read (rtems_libio_t* iop,
                          void*          buffer,
                          size_t         count)
{
  rtems_rfs_file_system* fs = rtems_rfs_rtems_pathloc_dev (&iop->pathinfo);
  rtems_rfs_ino          ino = rtems_rfs_rtems_get_iop_ino (iop);
  rtems_rfs_inode_handle inode;
  struct dirent*         dirent;
  ssize_t                bytes_transferred;
  int                    d;
  int                    rc;

  count  = count / sizeof (struct dirent);
  dirent = buffer;
  
  rtems_rfs_rtems_lock (fs);
  
  rc = rtems_rfs_inode_open (fs, ino, &inode, true);
  if (rc)
  {
    rtems_rfs_rtems_unlock (fs);
    return rtems_rfs_rtems_error ("dir_read: read inode", rc);
  }

  bytes_transferred = 0;
  
  for (d = 0; d < count; d++, dirent++)
  {
    size_t size;
    rc = rtems_rfs_dir_read (fs, &inode, iop->offset, dirent, &size);
    if (rc == ENOENT)
    {
      rc = 0;
      break;
    }
    if (rc > 0)
    {
      bytes_transferred = rtems_rfs_rtems_error ("dir_read: dir read", rc);
      break;
    }
    iop->offset += size;
    bytes_transferred += sizeof (struct dirent);
  }

  rtems_rfs_inode_close (fs, &inode);
  rtems_rfs_rtems_unlock (fs);
  
  return bytes_transferred;
}

/**
 * This routine will behave in one of three ways based on the state of argument
 * whence. Based on the state of its value the offset argument will be
 * interpreted using one of the following methods:
 *
 *   SEEK_SET - offset is the absolute byte offset from the start of the
 *              logical start of the dirent sequence that represents the
 *              directory
 *   SEEK_CUR - offset is used as the relative byte offset from the current
 *              directory position index held in the iop structure
 *   SEEK_END - N/A --> This will cause an assert.
 *
 * @param iop
 * @param offset
 * @param whence
 * return rtems_off64_t
 */
static rtems_off64_t
rtems_rfs_rtems_dir_lseek (rtems_libio_t* iop,
                           rtems_off64_t  offset,
                           int            whence)
{
  switch (whence)
  {
    case SEEK_SET:   /* absolute move from the start of the file */
    case SEEK_CUR:   /* relative move */
      break;

     case SEEK_END:   /* Movement past the end of the directory via lseek */
                      /* is not a permitted operation                     */
    default:
      return rtems_rfs_rtems_error ("dir_lseek: bad whence", EINVAL);
      break;
  }
  return 0;
}

static int
rtems_rfs_rtems_dir_rmnod (rtems_filesystem_location_info_t* parent_pathloc,
                           rtems_filesystem_location_info_t* pathloc)
{
  rtems_rfs_file_system* fs = rtems_rfs_rtems_pathloc_dev (pathloc);
  rtems_rfs_ino          parent = rtems_rfs_rtems_get_pathloc_ino (parent_pathloc);
  rtems_rfs_ino          ino = rtems_rfs_rtems_get_pathloc_ino (pathloc);
  uint32_t               doff = rtems_rfs_rtems_get_pathloc_doff (pathloc);
  int                    rc;

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_DIR_RMNOD))
    printf ("rtems-rfs: dir-rmnod: parent:%" PRId32 " doff:%" PRIu32 ", ino:%" PRId32 "\n",
            parent, doff, ino);

  if (ino == RTEMS_RFS_ROOT_INO)
    return rtems_rfs_rtems_error ("dir_rmnod: root inode", EBUSY);

  rtems_rfs_rtems_lock (fs);
  
  rc = rtems_rfs_unlink (fs, parent, ino, doff, rtems_rfs_unlink_dir_if_empty);
  if (rc)
  {
    rtems_rfs_rtems_unlock (fs);
    return rtems_rfs_rtems_error ("dir_rmnod: unlinking", rc);
  }

  rtems_rfs_rtems_unlock (fs);
  return 0;
}

/*
 *  Set of operations handlers for operations on directories.
 */

const rtems_filesystem_file_handlers_r rtems_rfs_rtems_dir_handlers = {
  .open_h      = rtems_rfs_rtems_dir_open,
  .close_h     = rtems_rfs_rtems_dir_close,
  .read_h      = rtems_rfs_rtems_dir_read,
  .write_h     = NULL,
  .ioctl_h     = NULL,
  .lseek_h     = rtems_rfs_rtems_dir_lseek,
  .fstat_h     = rtems_rfs_rtems_stat,
  .fchmod_h    = rtems_rfs_rtems_fchmod,
  .ftruncate_h = NULL,
  .fpathconf_h = NULL,
  .fsync_h     = NULL,
  .fdatasync_h = rtems_rfs_rtems_fdatasync,
  .fcntl_h     = rtems_rfs_rtems_fcntl,
  .rmnod_h     = rtems_rfs_rtems_dir_rmnod
};
