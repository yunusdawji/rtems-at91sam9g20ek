/*  Put_buffer
 *
 *  This test routine prints the given buffer.
 *  buffer.
 *
 *  Input parameters:
 *    buffer - pointer to message buffer to be printer
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: putbuff.c,v 1.12 2009/05/10 14:39:46 joel Exp $
 */

#include "system.h"

void Put_buffer(
  void *buffer
)
{
  int i, j;
  char c;
  long *b = buffer;

  for ( i = 0; i < (int) (MESSAGE_SIZE / sizeof(long)); i++ ) {
    for ( j = sizeof(long) - 1; j >= 0; j-- ) {
      if ( (c = (char)(b[i] >> (8 * j)) & 0xFF) == 0 )
        return;
      printf( "%c", c );
    }
  }
}
