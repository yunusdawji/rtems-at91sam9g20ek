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
 *  $Id: time03.c,v 1.9 2009/05/10 20:15:56 joel Exp $
 */

#include <time.h>

void test( void );

void test( void )
{
  struct tm timestruct;
  time_t    time_encoded;

  timestruct.tm_sec = 0;
  timestruct.tm_min = 0;
  timestruct.tm_hour = 0;
  timestruct.tm_mday = 1;
  timestruct.tm_mon = 0;
  timestruct.tm_year = 0;
  timestruct.tm_wday = 0;
  timestruct.tm_yday = 0;
  timestruct.tm_isdst = 0;

  time_encoded = mktime( &timestruct );
}
