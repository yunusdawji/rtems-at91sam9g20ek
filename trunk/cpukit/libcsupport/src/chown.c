/*
 *  chown() - POSIX 1003.1b 5.6.5 - Change Owner and Group of a File
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: chown.c,v 1.12 2009/06/12 01:53:32 ccj Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/stat.h>
#include <errno.h>

#include <rtems.h>
#include <rtems/libio.h>

#include <rtems/libio_.h>
#include <rtems/seterr.h>

int chown(
  const char *path,
  uid_t       owner,
  gid_t       group
)
{
  rtems_filesystem_location_info_t   loc;
  int                                result;

  if ( rtems_filesystem_evaluate_path( path, strlen( path ), 0x00, &loc, true ) )
    return -1;

  if ( !loc.ops->chown_h ) {
    rtems_filesystem_freenode( &loc );
    rtems_set_errno_and_return_minus_one( ENOTSUP );
  }

  result = (*loc.ops->chown_h)( &loc, owner, group );

  rtems_filesystem_freenode( &loc );

  return result;
}
