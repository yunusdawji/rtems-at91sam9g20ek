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
 *  $Id: test.c,v 1.15 2010/06/02 00:50:37 ccj Exp $
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <rtems.h>
#include <rtems/libio.h>
#include <pmacros.h>

extern rtems_filesystem_location_info_t rtems_filesystem_current;

DIR *directory;
DIR *directory2;
DIR *directory3;
DIR *directory_not;

char *dnames[] = {
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"c/y",
	"c/z",
	"c/x",
	"c/y/a3333",
	"c/y/j123",
        "c/y/my_mount_point",
        "c/y/my_mount_point/my_dir",
        "c/z/my_mount_point",
        "END"
};

char *fnames[] = {
	"a",
	"b",
	"c",
	"d",
	"e",
	"f",
	"c/y",
	"c/z",
	"c/x",
	"c/y/a3333",
	"c/y/j123",
        "c/y/my_mount_point",
        "c/y/my_mount_point/my_dir",
        "c/y/my_mount_point/my_dir/d",
        "c/z/my_mount_point",
	"/c/z/my_mount_point/a/../../my_mount_point/a/g",
        "END"
};

#if defined(__rtems__)
int test_main(void)
#else
int main(
  int argc,
  char **argv
)
#endif
{
  int i;
  int fd;
  int status;
  struct stat statbuf;
  static char mount_point_string[25] = { "/c/z/my_mount_point" };


  printf( "\n\n*** MOUNT/UNMOUNT TEST ***\n" );

  /*
   * Change directory to the root and create files under
   * the base file system.
   */

  printf( "\nchdir to the root directory\n" );
  status = chdir( "/" );
  printf( "chdir() status : %d\n\n", status );

  printf( "\nCreating a series of directories under /\n" );
  i=0;
  while ( strcmp(dnames[i], "END") != 0 )
  {
     status = mkdir( dnames[i], 0777 );
     printf("Creating : %25s  %d %d   ", dnames[i], status, errno );
     if ( status == 0 )
        printf(" Success\n");
     else
        printf(" Failure\n");

     i++;
  }

  /*
   * Create a Files with all rwx for others group and user.  Verify
   * the created file.
   */

  printf("create /b/my_file\n");
  fd = open ("/b/my_file", O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
  rtems_test_assert(  fd != 0 );
  close (fd);

  printf("Verify /b/my_file\n");
  fd = open("/b/my_file", S_IRWXU|S_IRWXG|S_IRWXO);
  rtems_test_assert(  fd != 0 );
  close( fd );


  printf("create c/y/my_mount_point/my_dir/d\n");
  fd = open ("c/y/my_mount_point/my_dir/d", O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
  rtems_test_assert(  fd != 0 );
  close (fd);

  printf("Verify c/y/my_mount_point/my_dir/d\n");
  fd = open("c/y/my_mount_point/my_dir/d", S_IRWXU|S_IRWXG|S_IRWXO);
  rtems_test_assert(  fd != 0 );
  close( fd );

  /*
   *  Mount an the IMFS file system on the base file system.
   */

  printf("Attempting to mount IMFS file system at /c/z/my_mount_point \n");
  status = mount(
    "null",
    mount_point_string,
    "imfs",
    RTEMS_FILESYSTEM_READ_WRITE,
    NULL );
  rtems_test_assert(  status == 0 );
  printf("2nd file system successfully mounted at /c/z/my_mount_point \n");

  /*
   * Change directory to the mount point and create a group of files under
   * the mounted file system.
   */

  printf( "\nchdir to /c/z/my_mount_point.\n" );
  status = chdir( "/c/z/my_mount_point" );
  printf( "chdir() status : %d\n\n", status );

  printf( "\nCreating a series of directories under /c/z/my_mount_point\n" );
  i=0;
  while ( strcmp(fnames[i], "END") != 0 )
  {
     status = mkdir( fnames[i], 0777 );
     printf("Creating: %46s   %d %d   ", fnames[i], status, errno );
     if ( status == 0 )
        printf(" Success\n");
     else {
        printf(" Failure\n");
        perror("errno");
     }

     status = stat( fnames[i], &statbuf );
     if ( status == -1 )
       printf( ": %s\n", strerror( errno ) );

     i++;
  }

  printf( "\nchdir to /\n" );
  status = chdir( "/" );
  printf( "chdir() status : %d\n\n", status );

  /*
   * Unmount the first file system we mounted
   */

  printf( "Unmount status:");
  status = unmount( "/c/z/my_mount_point" );
  printf( " %d\n", status );


  /*
   * Mount a NULL filesystem and verify it fails.
   */

  printf("Mount a NULL file system and verify EINVAL\n");
  status = mount(
    "null",
    mount_point_string,
    "nofound",
    RTEMS_FILESYSTEM_READ_WRITE,
    NULL );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EINVAL );

  /*
   * Verify mount with option of -62 fails with EINVAL
   */

  printf("mount with option of -62 should fail with EINVAL\n");
  status = mount(
    "null",
    "/c/y/my_mount_point",
    "imfs",
    -62,
    NULL );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EINVAL );

  /*
   * Mount a Read Only File system.
   */

  printf("Mount a Read Only filesystem at /c/y/my_mount_point \n");
  status = mount(
    "null",
    "/c/y/my_mount_point",
    "imfs",
    RTEMS_FILESYSTEM_READ_ONLY,
    NULL );
  rtems_test_assert(  status == 0 );
  printf("Read only file system successfully mounted at /c/y/my_mount_point \n");

  /*
   * Create a directory that passes through the read only file system.
   */

  printf("create c/y/my_mount_point/../../y/my_mount_point/new_dir\n");
  status = mkdir("c/y/my_mount_point/../../y/my_mount_point/new_dir",S_IRWXU );
  rtems_test_assert(  status == 0 );
  status = stat("c/y/my_mount_point/../../y/my_mount_point/new_dir",&statbuf );
  rtems_test_assert(  status == 0 );
  status = stat("c/y/my_mount_point/new_dir/..", &statbuf );
  rtems_test_assert(  status == 0 );

  /*
   * Attempt to mount a second file system at a used mount point.
   */

  printf("Verify a mount point returns EBUSY for another mount\n");
  status = mount(
    "null",
    "/c/y/my_mount_point",
    "imfs",
     RTEMS_FILESYSTEM_READ_ONLY,
     NULL );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EBUSY);

  /*
   * Attempt to mount at a file.
   */

  printf("Mount on a file should fail with ENOTDIR\n");
  status = mount(
    "null",
    "/b/my_file",
    "imfs",
    RTEMS_FILESYSTEM_READ_ONLY,
    NULL );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == ENOTDIR );


  /*
   * Verify we cannot unmount a file system while we are in it.
   */

  printf("Create and chdir to /c/y/my_mount_point/mydir\n");
  status = mkdir( "/c/y/my_mount_point/mydir", 0777);
  rtems_test_assert(  status == 0 );

  status = chdir( "/c/y/my_mount_point/mydir" );
  rtems_test_assert(  status == 0 );

  printf("unmount of /c/y/my_mount_point should fail with EBUSY\n");
  status = unmount( "/c/y/my_mount_point" );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EBUSY );

  /*
   * Chdir to root and verify we can unmount the file system now.
   */

  printf("chdir to / and verify we can unmount /c/y/my_mount_point\n");
  status = chdir( "/" );
  rtems_test_assert(  status == 0 );

  printf("unmount /c/y/my_mount_point \n");
  status = unmount( "/c/y/my_mount_point" );
  rtems_test_assert(  status == 0 );

  /*
   * Attempt to unmount a directory that does not exist.
   */

  printf("unmount /b/mount_point should fail with EINVAL\n");
  status = unmount( "/b/mount_point" );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == ENOENT );

  /*
   * Remount the filesystem.
   */

  printf("Mount /c/y/my_mount_point\n");
  status = mount(
    "null",
    "/c/y/my_mount_point",
    "imfs",
    RTEMS_FILESYSTEM_READ_ONLY,
    NULL );
  rtems_test_assert(  status == 0 );

  /*
   * Create a file and directory then open the directory.
   * Verify unmount will return EBUSY while directory is open.
   */

  printf("Create and open /c/y/my_mount_point/my_file\n");
  fd = open( "/c/y/my_mount_point/my_file", O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
  rtems_test_assert(  fd != -1 );
  status = close( fd );
  rtems_test_assert(  status == 0 );

  printf("\nmkdir /c/y/my_mount_point/my_dir\n");
  status = mkdir( "/c/y/my_mount_point/my_dir", 0x1c0 );
  printf("Open /c/y/my_mount_point/my_dir\n");
  directory = opendir( "/c/y/my_mount_point/my_dir" );
  rtems_test_assert(  directory );

  printf("Unmount /c/y/my_mount_point should fail with EBUSY\n");
  status = unmount( "/c/y/my_mount_point" );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EBUSY );

  printf("Close /c/y/my_mount_point/my_dir\n");
  status = closedir( directory );
  rtems_test_assert(  status == 0 );

  /*
   * Attempt to unmount a directory that is not a mount point.
   */

  printf("Unmount /c/y/my_mount_point/my_dir should fail with EACCES\n");
  status = unmount( "/c/y/my_mount_point/my_dir" );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EACCES );

  /*
   * Verify a file system can not be unmounted with a mounted file system
   * in it.
   */

  printf("Mount a file system at /c/y/my_mount_point/my_dir\n");
  status = mount(
     "null",
     "/c/y/my_mount_point/my_dir",
     "imfs",
     RTEMS_FILESYSTEM_READ_WRITE,
     NULL );
  rtems_test_assert(  status == 0 );

  printf("unmount /c/y/my_mount_point should fail with EBUSY\n");
  status = unmount( "/c/y/my_mount_point" );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EBUSY );

  /*
   * Verify you cannot create a hard link across mounted file systems.
   */

  printf("Verify a hard link across filesystems fails with EXDEV\n");
  status = mkdir( "/c/y/my_mount_point/my_dir2", S_IRWXU  );
  rtems_test_assert(  status == 0 );

  status = link( "/c/y/my_mount_point/my_dir2", "/c/y/my_mount_point/my_dir/my_link" );
  rtems_test_assert(  status == -1 );
  rtems_test_assert(  errno == EXDEV );

  /*
   * Create a symbolic link across mountpoints.
   */

  printf("Verify a symbolic link across file systems works\n");
  status = symlink( "/c/y/my_mount_point/my_dir2", "/c/y/my_mount_point/my_dir/my_link" );
  rtems_test_assert(  status == 0 );
  status = stat( "/c/y/my_mount_point/my_dir/my_link", &statbuf );
  rtems_test_assert(  status == 0 );

  printf("unmount /c/y/my_mount_point/my_dir\n");
  status = unmount( "/c/y/my_mount_point/my_dir" );
  rtems_test_assert(  status == 0 );

  /*
   * Verify symblic link no longer works.
   */

  printf("Verify the symbolic link now fails\n");
  status = stat( "/c/y/my_mount_point/my_dir/my_link", &statbuf );
  rtems_test_assert(  status != 0 );

  printf("unmount /c/y/my_mount_point\n");
  status = unmount( "/c/y/my_mount_point" );
  rtems_test_assert(  status == 0 );

  printf( "\n\n*** END OF MOUNT/UNMOUNT TEST ***\n" );
  rtems_test_exit(0);
}
