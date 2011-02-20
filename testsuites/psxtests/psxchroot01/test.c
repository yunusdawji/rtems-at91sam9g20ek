/*
 *  This is a native test to explore how the readdir() family works.
 *  Newlib supports the following readdir() family members:
 *
 *    closedir()   -
 *    readdir()    -
 *    scandir()    -
 *    opendir()    -
 *    rewinddir()  -
 *    telldir()    - BSD not in POSIX
 *    seekdir()    - BSD not in POSIX
 *
 *
 *  seekdir() takes an offset which is a byte offset.  The Linux
 *  implementation of this appears to seek to the ((off/DIRENT_SIZE) + 1)
 *  record where DIRENT_SIZE seems to be 12 bytes.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: test.c,v 1.8 2009/12/08 17:52:53 joel Exp $
 */

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <rtems/libio.h>
#include <rtems/userenv.h>
#include <pmacros.h>

void touch( char *file )
{
  int fd;

  rtems_test_assert(  file );

  fd = open( file, O_RDWR|O_CREAT, 0777 );
  rtems_test_assert(  fd != -1 );
  close( fd );
}

int fileexists( char *file )
{
  int         status;
  struct stat statbuf;

  rtems_test_assert(  file );

  status = stat( file, &statbuf );

  if ( status == -1 ) {
    /* printf( ": %s\n", strerror( errno ) ); */
    return 0;
  }
  return 1;
}

#if defined(__rtems__)
int test_main(void)
#else
int main(
  int argc,
  char **argv
)
#endif
{
  int status;

/*
 *  This test is the C equivalent of this sequence.
#mkdir /one
#mkdir /one/one
#touch /one/one.test
#touch /one/two/two.test
#chroot /one
#if !fileexists(/one/one.test) echo "SUCCESSFUL"
#if fileexists(/two/two.test) echo "SUCCESSFUL"
#rtems_set_private_env() ! reset at the global environment
#if fileexists(/one/one.test) echo "SUCESSFUL"
#if !fileexists(/two/two.test) echo "SUCCESSFUL"
*/

  printf( "\n\n*** CHROOT01 TEST ***\n" );

  status = mkdir( "/one", 0777);
  rtems_test_assert(  status == 0 );

  status = mkdir( "/one/one", 0777);
  rtems_test_assert(  status == 0 );

  status = mkdir( "/one/two", 0777);
  rtems_test_assert(  status == 0 );

  touch( "/one/one.test" );
  touch( "/one/two/two.test" );

  status = chroot( "/one" );
  rtems_test_assert(  status == 0 );

  status = fileexists( "/one/one.test" );
  printf( "%s on /one/one.test\n", (!status) ? "SUCCESS" : "FAILURE" );

  status = fileexists( "/two/two.test" );
  printf( "%s on /two/two.test\n", (status) ? "SUCCESS" : "FAILURE" );

  puts( "Reset the private environment" );
  rtems_libio_set_private_env();

  status = fileexists( "/one/one.test" );
  printf( "%s on /one/one.test\n", ( status) ? "SUCCESS" : "FAILURE" );

  status = fileexists( "/two/two.test" );
  printf( "%s on /two/two.test\n", (!status) ? "SUCCESS" : "FAILURE" );

  printf( "*** END OF CHROOT01 TEST ***\n" );
  rtems_test_exit(0);
}
