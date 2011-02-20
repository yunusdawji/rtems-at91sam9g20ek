/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: test_support.c,v 1.6 2009/12/08 21:39:21 humph Exp $
 */

#include <fcntl.h>
#include <tmacros.h>
#include "test_support.h"

static char  Too_Long_Name[PATH_MAX + 2];
static char  Longest_Name[PATH_MAX + 1];

const char *Get_Too_Long_Name(void)
{
  int i;

  for ( i=0; i <= PATH_MAX; i++ )
    Too_Long_Name[i] = 'E';
  Too_Long_Name[i] = '\0';
  return Too_Long_Name;
}

const char *Get_Longest_Name(void)
{
  int i;

  for ( i=0; i < PATH_MAX-1; i++ )
    Longest_Name[i] = 'L';
  Longest_Name[i] = '\0';
  return Longest_Name;
}

void Allocate_majority_of_workspace( int smallest )
{
  bool                   result;
  Heap_Information_block info;
  void                   *temp;

  puts("Allocate_majority_of_workspace: ");
  result = rtems_workspace_get_information( &info );
  if ( result != TRUE )
    perror("==> Error Getting workspace information");

  do {
    result = rtems_workspace_allocate(
      info.Free.largest-16,
      &temp
    );
    if ((!result) || (!temp))
      perror("Unable to allocate from workspace");
    result = rtems_workspace_get_information( &info );
  } while ( info.Free.largest >= smallest );

}
