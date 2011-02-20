/*  Fill_buffer
 *
 *  This test routine copies a given source string to a given destination
 *  buffer.
 *
 *  Input parameters:
 *    source - pointer to string to be copied
 *    buffer - pointer to message buffer to be filled
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: fillbuff.c,v 1.9 2004/03/30 19:46:38 joel Exp $
 */

#include "system.h"

void Fill_buffer(
  char *source,
  long *buffer
)
{
  char *p;
  int i, j;

  p = source;
  for ( i = 0 ; i < MESSAGE_SIZE / sizeof(long) ; i++ ) {
    buffer[i] = 0;
    for ( j = sizeof(long) - 1; j >= 0; j-- ) {
      buffer[i] |= *p++ << (8 * j);
    }
  }
}
