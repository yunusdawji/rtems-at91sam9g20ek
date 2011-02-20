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
 *  $Id: proc02.c,v 1.10 2010/04/02 07:28:41 ralf Exp $
 */

#include <sys/types.h>
#include <unistd.h>

void test( void );

void test( void )
{
  pid_t pid;

  pid = getppid();
}
