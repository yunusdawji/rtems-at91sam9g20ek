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
 *  $Id: signal20.c,v 1.10 2010/04/02 07:28:41 ralf Exp $
 */

#include <unistd.h>

void test( void );

void test( void )
{
  unsigned int seconds;
  unsigned int result;

  seconds = 10;

  result = alarm( seconds );
}
