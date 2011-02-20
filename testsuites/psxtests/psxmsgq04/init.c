/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.8 2009/12/08 17:52:53 joel Exp $
 */

#include <pmacros.h>
#include <unistd.h>
#include <errno.h>
#include <tmacros.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>

#include "test_support.h"

void *POSIX_Init(
  void *argument
)
{
  struct mq_attr          attr;
  mqd_t                   Queue, second_Queue;
  int                     sc;
  Heap_Information_block  start;
  Heap_Information_block  info;
  size_t                  to_alloc;
  void                   *alloced;
  bool                    sb;
  const char             *name;

  puts( "\n\n*** POSIX MESSAGE QUEUE TEST 4 ***" );

  attr.mq_maxmsg = 1;
  attr.mq_msgsize = sizeof(int);

  puts( "Init - Open message queue instance 1" );
  Queue = mq_open( "Queue", O_CREAT | O_RDWR, 0x777, &attr );
  if ( Queue == (-1) )
    perror( "mq_open failed" );
  rtems_test_assert(  Queue != (-1) );

  puts( "Init - Open message queue instance 2 - FAIL - ENFILE " );
  second_Queue = mq_open( "Queue2", O_CREAT | O_RDWR, 0x777, &attr );
  if ( second_Queue != (-1) )
    puts( "mq_open did not failed" );
  rtems_test_assert(  second_Queue == (-1) );
  rtems_test_assert(  errno == ENFILE );

  puts( "Init - Unlink message queue instance 1" );
  sc = mq_unlink( "Queue" );
  if ( sc != 0 )
    perror( "mq_unlink failed" );
  rtems_test_assert(  sc == 0 );

  puts( "Init - Close message queue instance 1" );
  sc = mq_close( Queue );
  if ( sc != 0 )
    perror( "mq_close failed" );
  rtems_test_assert(  sc == 0 );

  sb = rtems_workspace_get_information( &start );
  rtems_test_assert(  start.Free.number == 1 );
  to_alloc = start.Free.largest;

  /* find the largest we can actually allocate */
  while ( 1 ) {
    sb = rtems_workspace_allocate( to_alloc, &alloced );
    if ( sb )
      break;
    to_alloc -= 4;
  }

  rtems_workspace_free( alloced );

  /*
   * Now do the test
   */
  puts( "Init - Memory allocation error test" );

  sb = rtems_workspace_get_information( &info );

  attr.mq_maxmsg = 1;
  attr.mq_msgsize = 200;

  name = Get_Longest_Name();
  while ( attr.mq_msgsize > 0 ) {
    sb = rtems_workspace_allocate( to_alloc, &alloced );
    rtems_test_assert(  sb );

    second_Queue = mq_open(name,O_CREAT | O_RDWR, 0x777, &attr );

    /* free the memory we snagged, then check the status */
    rtems_workspace_free( alloced );

    if ( second_Queue != (-1) )
      break;

    /* attr.mq_msgsize -= 48; */
    to_alloc -= 4;
  }

  if ( second_Queue == -1 )
    rtems_test_exit(0);

  puts( "Init - Message Queue created" );

  puts( "Init - Unlink message queue" );
    sc = mq_unlink( name );
    if ( sc != 0 )
      perror( "mq_unlink failed" );
    rtems_test_assert(  sc == 0 );

  puts( "Init - Close message queue" );
    sc = mq_close( second_Queue );
    if ( sc != 0 )
      perror( "mq_close failed" );
    rtems_test_assert(  sc == 0 );

  puts( "*** END OF POSIX MESSAGE QUEUE TEST 4 ***" );
  rtems_test_exit( 0 );

  return NULL; /* just so the compiler thinks we returned something */
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

/* account for message buffers and string names */
#define CONFIGURE_MESSAGE_BUFFER_MEMORY \
    CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(1, sizeof(int))

#define CONFIGURE_MAXIMUM_POSIX_THREADS                   1
#define CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES            1
#define CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUE_DESCRIPTORS 2

#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
