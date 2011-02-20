/*
 *  $Id: tftp.h,v 1.7.2.1 2010/07/01 15:01:11 sh Exp $
 */

/*
 * Trivial File Transfer Protocol (TFTP)
 *
 * Transfer file to/from remote host
 *
 * W. Eric Norum
 * Saskatchewan Accelerator Laboratory
 * University of Saskatchewan
 * Saskatoon, Saskatchewan, CANADA
 * eric@skatter.usask.ca
 */

/*
 * Usage:
 *
 * To open `/bootfiles/image' on `hostname' for reading:
 *         fd = open ("/TFTP/hostname/bootfiles/image", O_RDONLY);
 *
 * The 'TFTP' is the mount path and the `hostname' must be four dot-separated
 * decimal values.
 */

#ifndef _RTEMS_TFTP_H
#define _RTEMS_TFTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtems/libio.h>

/*
 * Filesystem Mount table entry.
 */
int rtems_tftpfs_initialize(rtems_filesystem_mount_table_entry_t *temp_mt_entry);

#ifdef __cplusplus
}
#endif

#endif
