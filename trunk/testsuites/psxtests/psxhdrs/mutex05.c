/*
 *  This test file is used to verify that the header files associated with
 *  invoking this function are correct.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: mutex05.c,v 1.10 2009/05/10 20:15:55 joel Exp $
 */

#include <pthread.h>

#ifndef _POSIX_THREADS
#error "rtems is supposed to have pthread_mutex_lock"
#endif

void test( void );

void test( void )
{
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  int result;

  result = pthread_mutex_lock( &mutex );
}
