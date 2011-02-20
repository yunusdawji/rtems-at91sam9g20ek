/*
 *  A test support function which extends the file to the specified
 *  length.  This handles the implied open(), lseek(), write(), and close()
 *  operations.
 *
 *  The defined behavior is a seek() followed by a write() extends the file
 *  and zero fills the new length part.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: test_extend.c,v 1.4 2009/12/08 17:52:53 joel Exp $
 */

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include <pmacros.h>

/*
 *  test_extend routine
 */

void test_extend(
  char   *file,
  off_t  offset
)
{
  int   fd;
  int   status;
  char  c = 0;

  fd = open( file, O_WRONLY );
  if ( fd == -1 ) {
    printf( "test_extend: open( %s ) failed : %s\n", file, strerror( errno ) );
    rtems_test_exit( 0 );
  }

  status = lseek( fd, offset - 1, SEEK_SET );
  rtems_test_assert( status != -1 );

  status = write( fd, &c, 1 );
  if ( status == -1 ) {
    printf( "test_extend: write( %s ) failed : %s\n", file, strerror( errno ) );
    rtems_test_exit( 0 );
  }

  if ( status != 1 ) {
    printf( "test_extend: write( %s ) only wrote %d of %d bytes\n",
            file, status, 1 );
    rtems_test_exit( 0 );
  }

  status = close( fd );
  rtems_test_assert( !status );
}
