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
 *  $Id: signal07.c,v 1.10 2009/05/10 20:15:56 joel Exp $
 */

#include <signal.h>

#ifndef _POSIX_THREADS
#error "rtems is supposed to have pthread_kill"
#endif

void test( void );

void test( void )
{
  pthread_t  thread;
  int        signal_number;
  int        result;

  thread = 0;
  signal_number = SIGALRM;

  result = pthread_kill( thread, signal_number );
}
