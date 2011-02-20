/*
 *  COPYRIGHT (c) 2010 Chris Johns <chrisj@rtems.org>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: rtems-rfs-rtems-file.c,v 1.4.2.2 2010/10/18 22:48:55 ccj Exp $
 */
/**
 * @file
 *
 * @ingroup rtems-rfs
 *
 * RTEMS RFS File Handlers
 *
 * This file contains the set of handlers used to process operations on
 * RFS file nodes.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <inttypes.h>

#include <rtems/rfs/rtems-rfs-file.h>
#include "rtems-rfs-rtems.h"

/**
 * This routine processes the open() system call.  Note that there is nothing
 * special to be done at open() time.
 *
 * @param iop
 * @param pathname
 * @param flag
 * @param mode
 * @return int
 */

static int
rtems_rfs_rtems_file_open (rtems_libio_t* iop,
                           const char*    pathname,
                           uint32_t       flag,
                           uint32_t       mode)
{
  rtems_rfs_file_system* fs = rtems_rfs_rtems_pathloc_dev (&iop->pathinfo);
  rtems_rfs_ino          ino;
  rtems_rfs_file_handle* file;
  uint32_t               flags;
  int                    rc;

  flags = 0;

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_FILE_OPEN))
    printf("rtems-rfs: file-open: path:%s ino:%" PRId32 " flags:%04" PRIx32 " mode:%04" PRIx32 "\n",
           pathname, ino, flags, mode);

  rtems_rfs_rtems_lock (fs);
  
  ino = rtems_rfs_rtems_get_iop_ino (iop);
  
  rc = rtems_rfs_file_open (fs, ino, flags, &file);
  if (rc > 0)
  {
    rtems_rfs_rtems_unlock (fs);
    return rtems_rfs_rtems_error ("file-open: open", rc);
  }

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_FILE_OPEN))
    printf("rtems-rfs: file-open: handle:%p\n", file);
  
  iop->file_info = file;
  
  rtems_rfs_rtems_unlock (fs);
  return 0;
}

/**
 * This routine processes the close() system call.  Note that there is nothing
 * to flush at this point.
 *
 * @param iop
 * @return int
 */
static int
rtems_rfs_rtems_file_close (rtems_libio_t* iop)
{
  rtems_rfs_file_handle* file = iop->file_info;
  rtems_rfs_file_system* fs = rtems_rfs_file_fs (file);
  int                    rc;

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_FILE_CLOSE))
    printf("rtems-rfs: file-close: handle:%p\n", file);

  rtems_rfs_rtems_lock (fs);
  
  rc = rtems_rfs_file_close (fs, file);
  if (rc > 0)
    rc = rtems_rfs_rtems_error ("file-close: file close", rc);
  
  rtems_rfs_rtems_unlock (fs);
  return rc;
}

/**
 * This routine processes the read() system call.
 *
 * @param iop
 * @param buffer
 * @param count
 * @return int
 */
ssize_t
rtems_rfs_rtems_file_read (rtems_libio_t* iop,
                           void*          buffer,
                           size_t         count)
{
  rtems_rfs_file_handle* file = iop->file_info;
  rtems_rfs_pos          pos;
  uint8_t*               data = buffer;
  ssize_t                read = 0;
  int                    rc;

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_FILE_READ))
    printf("rtems-rfs: file-read: handle:%p count:%zd\n", file, count);

  rtems_rfs_rtems_lock (rtems_rfs_file_fs (file));

  pos = iop->offset;
  
  if (pos < rtems_rfs_file_size (file))
  {
    while (count)
    {
      size_t size;

      rc = rtems_rfs_file_io_start (file, &size, true);
      if (rc > 0)
      {
        read = rtems_rfs_rtems_error ("file-read: read: io-start", rc);
        break;
      }

      if (size == 0)
        break;
    
      if (size > count)
        size = count;
    
      memcpy (data, rtems_rfs_file_data (file), size);

      data  += size;
      count -= size;
      read  += size;

      rc = rtems_rfs_file_io_end (file, size, true);
      if (rc > 0)
      {
        read = rtems_rfs_rtems_error ("file-read: read: io-end", rc);
        break;
      }
    }
  }
  
  rtems_rfs_rtems_unlock (rtems_rfs_file_fs (file));
  
  return read;
}

/**
 * This routine processes the write() system call.
 *
 * @param iop
 * @param buffer
 * @param count
 * @return ssize_t
 */
ssize_t
rtems_rfs_rtems_file_write (rtems_libio_t* iop,
                            const void*    buffer,
                            size_t         count)
{
  rtems_rfs_file_handle* file = iop->file_info;
  rtems_rfs_pos          pos;
  const uint8_t*         data = buffer;
  ssize_t                write = 0;
  int                    rc;

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_FILE_WRITE))
    printf("rtems-rfs: file-write: handle:%p count:%zd\n", file, count);

  rtems_rfs_rtems_lock (rtems_rfs_file_fs (file));

  pos = iop->offset;
  
  /*
   * If the iop position is past the physical end of the file we need to set the
   * file size to the new length before writing.
   */
  
  if (pos > rtems_rfs_file_size (file))
  {
    rc = rtems_rfs_file_set_size (file, pos);
    if (rc)
    {
      rtems_rfs_rtems_unlock (rtems_rfs_file_fs (file));
      return rtems_rfs_rtems_error ("file-write: write extend", rc);
    }
    rtems_rfs_file_set_bpos (file, pos);
  }
  
  while (count)
  {
    size_t size = count;
    
    rc = rtems_rfs_file_io_start (file, &size, false);
    if (rc)
    {
      write = rtems_rfs_rtems_error ("file-write: write open", rc);
      break;
    }
    
    if (size > count)
      size = count;

    memcpy (rtems_rfs_file_data (file), data, size);

    data  += size;
    count -= size;
    write  += size;
    
    rc = rtems_rfs_file_io_end (file, size, false);
    if (rc)
    {
      write = rtems_rfs_rtems_error ("file-write: write close", rc);
      break;
    }
  }
  
  iop->size = rtems_rfs_file_size (file);
  
  rtems_rfs_rtems_unlock (rtems_rfs_file_fs (file));
  
  return write;
}

/**
 * This routine processes the ioctl() system call.
 *
 * @note  No ioctl()'s are currently supported for RFS files.
 *
 * @param iop
 * @param command
 * @param buffer
 */

int
rtems_rfs_rtems_file_ioctl (rtems_libio_t* iop, uint32_t command, void* buffer)
{
  return 0;
}

/**
 * This routine processes the lseek() system call.
 *
 * @param iop
 * @param offset
 * @param whence
 * @return rtems_off64_t
 */
rtems_off64_t
rtems_rfs_rtems_file_lseek (rtems_libio_t* iop,
                            rtems_off64_t  offset,
                            int            whence)
{
  rtems_rfs_file_handle* file = iop->file_info;
  rtems_rfs_pos          pos;
  int                    rc;

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_FILE_LSEEK))
    printf("rtems-rfs: file-lseek: handle:%p offset:%Ld\n", file, offset);

  rtems_rfs_rtems_lock (rtems_rfs_file_fs (file));
  
  pos = iop->offset;
  
  rc = rtems_rfs_file_seek (file, pos, &pos);
  if (rc)
  {
    rtems_rfs_rtems_unlock (rtems_rfs_file_fs (file));
    return rtems_rfs_rtems_error ("file_lseek: lseek", rc);
  }
  
  rtems_rfs_rtems_unlock (rtems_rfs_file_fs (file));
  
  return iop->offset;
}

/**
 * This routine processes the ftruncate() system call.
 *
 * @param iop
 * @param length
 * @return int
 */
int
rtems_rfs_rtems_file_ftruncate (rtems_libio_t* iop,
                                rtems_off64_t  length)
{
  rtems_rfs_file_handle* file = iop->file_info;
  int                    rc;

  if (rtems_rfs_rtems_trace (RTEMS_RFS_RTEMS_DEBUG_FILE_FTRUNC))
    printf("rtems-rfs: file-ftrunc: handle:%p length:%Ld\n", file, length);
  
  rtems_rfs_rtems_lock (rtems_rfs_file_fs (file));
  
  rc = rtems_rfs_file_set_size (file, length);
  if (rc)
    rc = rtems_rfs_rtems_error ("file_ftruncate: set size", rc);

  iop->size = rtems_rfs_file_size (file);
  
  rtems_rfs_rtems_unlock (rtems_rfs_file_fs (file));

  return rc;
}

/*
 *  Set of operations handlers for operations on RFS files.
 */

const rtems_filesystem_file_handlers_r rtems_rfs_rtems_file_handlers = {
  .open_h      = rtems_rfs_rtems_file_open,
  .close_h     = rtems_rfs_rtems_file_close,
  .read_h      = rtems_rfs_rtems_file_read,
  .write_h     = rtems_rfs_rtems_file_write,
  .ioctl_h     = rtems_rfs_rtems_file_ioctl,
  .lseek_h     = rtems_rfs_rtems_file_lseek,
  .fstat_h     = rtems_rfs_rtems_stat,
  .fchmod_h    = rtems_rfs_rtems_fchmod,
  .ftruncate_h = rtems_rfs_rtems_file_ftruncate,
  .fpathconf_h = NULL,
  .fsync_h     = rtems_rfs_rtems_fdatasync,
  .fdatasync_h = rtems_rfs_rtems_fdatasync,
  .fcntl_h     = rtems_rfs_rtems_fcntl,
  .rmnod_h     = rtems_rfs_rtems_rmnod
};
