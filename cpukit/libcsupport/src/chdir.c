/*
 *  chdir() - POSIX 1003.1b - 5.2.1 - Change Current Working Directory
 *
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: chdir.c,v 1.14 2010/04/28 15:01:31 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>

#include <unistd.h>
#include <errno.h>

#include <rtems/libio_.h>
#include <rtems/seterr.h>

int chdir(
  const char *pathname
)
{
  rtems_filesystem_location_info_t  loc;
  int                               result;

  if ( !pathname )
    rtems_set_errno_and_return_minus_one( EFAULT );

  /*
   *  Get the node where we wish to go.
   */
  result = rtems_filesystem_evaluate_path(
    pathname, strlen( pathname ), RTEMS_LIBIO_PERMS_SEARCH, &loc, true );
  if ( result != 0 )
     return -1;

  /*
   * Verify you can change directory into this node.
   */
  if ( !loc.ops->node_type_h ) {
    rtems_filesystem_freenode( &loc );
    rtems_set_errno_and_return_minus_one( ENOTSUP );
  }

  if (  (*loc.ops->node_type_h)( &loc ) != RTEMS_FILESYSTEM_DIRECTORY ) {
    rtems_filesystem_freenode( &loc );
    rtems_set_errno_and_return_minus_one( ENOTDIR );
  }

  rtems_filesystem_freenode( &rtems_filesystem_current );

  rtems_filesystem_current = loc;

  return 0;
}
