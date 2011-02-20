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
 *  $Id: signal23.c,v 1.4 2009/05/10 20:15:56 joel Exp $
 */

#include <signal.h>

useconds_t _EXFUN(ualarm, (useconds_t __useconds, useconds_t __interval));
void test( void );

void test( void )
{
  useconds_t useconds;
  useconds_t interval;
  useconds_t result;

  useconds = 10;
  interval = 10;

  result = ualarm( useconds, interval );
}
