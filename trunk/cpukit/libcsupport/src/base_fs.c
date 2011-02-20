/*
 *  Base file system initialization
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: base_fs.c,v 1.22 2010/05/31 13:56:36 ccj Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <rtems/libio.h>
#include <rtems/libio_.h>

/*
 *  Default mode for created files.
 */


/*
 *  rtems_filesystem_initialize
 *
 *  Initialize the foundation of the file system.  This is specified
 *  by the structure rtems_filesystem_mount_table.  The usual
 *  configuration is a single instantiation of the IMFS or miniIMFS with
 *  a single "/dev" directory in it.
 */

void rtems_filesystem_initialize( void )
{
  int                                   status;
  const rtems_filesystem_mount_table_t *mt;
  rtems_filesystem_location_info_t      loc;

  /*
   *  Set the default umask to "022".
   */

  rtems_filesystem_umask = 022;

  /*
   *  mount the first filesystem.
   */

  if ( rtems_filesystem_mount_table_size == 0 )
    rtems_fatal_error_occurred( 0xABCD0001 );

  mt = &rtems_filesystem_mount_table[0];

  status = mount( mt->device, mt->mount_point, mt->type, mt->fsoptions, NULL );

  if ( status == -1 )
    rtems_fatal_error_occurred( 0xABCD0002 );

  rtems_filesystem_link_counts = 0;

  /* setup the 'current' and 'root' directories
   *
   * NOTE: cloning the pathlocs is not strictly
   *       necessary. Since we implicitely let
   *       all threads that don't call
   *       libio_set_private_env() share the same
   *       (initial) 'root' and 'current' locs,
   *       we (also implicitely) assume that the
   *       root filesystem doesn't care about
   *       reference counts.
   *       I just inserted the code snippet below
   *       to remind everybody of the fact by
   *       making it more explicit...
   *       Ideally, every thread would have to
   *       call either share_private_env() or
   *       set_private_env() - but then: that's
   *       gonna hit performance.
   *
   *       Till Straumann, 10/25/2002
   */
  /* Clone the root pathloc */
  rtems_filesystem_evaluate_path("/", 1, 0, &loc, 0);
  rtems_filesystem_root        = loc;
  /* One more clone for the current node */
  rtems_filesystem_evaluate_path("/", 1, 0, &loc, 0);
  rtems_filesystem_current     = loc;

  /* Note: the global_env's refcnt doesn't matter
   * as the global env is never released
   */


  /*
   *  Traditionally RTEMS devices are under "/dev" so install this directory.
   *
   *  If the mkdir() fails, we can't print anything so just fatal error.
   *
   *  NOTE: UNIX root is 755 and owned by root/root (0/0).  It is actually
   *        created that way by the IMFS.
   */

  status = mkdir( "/dev", 0777);
  if ( status != 0 )
    rtems_fatal_error_occurred( 0xABCD0003 );

  /*
   *  You can't mount another filesystem properly until the mount point
   *  it will be mounted onto is created.  Moreover, if it is going to
   *  use a device, then it is REALLY unfair to attempt this
   *  before device drivers are initialized.  So we return via a base
   *  filesystem image and nothing auto-mounted at this point.
   */
}
