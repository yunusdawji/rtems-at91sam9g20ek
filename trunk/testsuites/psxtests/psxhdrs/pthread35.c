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
 *  $Id: pthread35.c,v 1.10 2009/10/27 05:02:34 ralf Exp $
 */

#include <pthread.h>

#if !HAVE_DECL_PTHREAD_ATTR_SETCPUTIME
extern int pthread_attr_setcputime(
  pthread_attr_t  *attr,
  int             clock_allowed);
#endif

#ifndef _POSIX_THREAD_CPUTIME
#error "rtems is supposed to have pthread_attr_setcputime"
#endif

void test( void );

void test( void )
{
  pthread_attr_t  attr;
  int             clock_allowed;
  int             result;

  clock_allowed = CLOCK_ALLOWED;
  clock_allowed = CLOCK_DISALLOWED;

  result = pthread_attr_setcputime( &attr, clock_allowed );
}
