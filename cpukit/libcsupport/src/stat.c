/*
 *  stat() - POSIX 1003.1b 5.6.2 - Get File Status
 *
 *  Reused from lstat().
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: stat.c,v 1.16 2009/10/14 16:19:47 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

/*
 *  lstat() and stat() share the same implementation with a minor
 *  difference on how links are evaluated.
 */

#ifndef _STAT_NAME
#define _STAT_NAME         stat
#define _STAT_R_NAME       _stat_r
#define _STAT_FOLLOW_LINKS true
#endif


#include <rtems.h>

#include <rtems/libio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <rtems/libio_.h>
#include <rtems/seterr.h>

int _STAT_NAME(
  const char  *path,
  struct stat *buf
)
{
  int                              status;
  rtems_filesystem_location_info_t loc;

  /*
   *  Check to see if we were passed a valid pointer.
   */

  if ( !buf )
    rtems_set_errno_and_return_minus_one( EFAULT );

  status = rtems_filesystem_evaluate_path( path, strlen( path ),
                                           0, &loc, _STAT_FOLLOW_LINKS );
  if ( status != 0 )
    return -1;

  if ( !loc.handlers->fstat_h ){
    rtems_filesystem_freenode( &loc );
    rtems_set_errno_and_return_minus_one( ENOTSUP );
  }

  /*
   *  Zero out the stat structure so the various support
   *  versions of stat don't have to.
   */

  memset( buf, 0, sizeof(struct stat) );

  status =  (*loc.handlers->fstat_h)( &loc, buf );

  rtems_filesystem_freenode( &loc );

  return status;
}

/*
 *  _stat_r, _lstat_r
 *
 *  This is the Newlib dependent reentrant version of stat() and lstat().
 */

#if defined(RTEMS_NEWLIB)

#include <reent.h>

int _STAT_R_NAME(
  struct _reent *ptr __attribute__((unused)),
  const char    *path,
  struct stat   *buf
)
{
  return _STAT_NAME( path, buf );
}
#endif
