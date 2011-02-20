/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: keydelete.c,v 1.11 2009/07/22 00:09:31 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <string.h>

#include <rtems/system.h>
#include <rtems/score/thread.h>
#include <rtems/score/wkspace.h>
#include <rtems/posix/key.h>

/*PAGE
 *
 *  17.1.3 Thread-Specific Data Key Deletion, P1003.1c/Draft 10, p. 167
 */

int pthread_key_delete(
  pthread_key_t  key
)
{
  register POSIX_Keys_Control *the_key;
  Objects_Locations            location;
  uint32_t                     the_api;

  the_key = _POSIX_Keys_Get( key, &location );
  switch ( location ) {

    case OBJECTS_LOCAL:
      _Objects_Close( &_POSIX_Keys_Information, &the_key->Object );

      for ( the_api = 1; the_api <= OBJECTS_APIS_LAST; the_api++ )
        if ( the_key->Values[ the_api ] )
          _Workspace_Free( the_key->Values[ the_api ] );

      /*
       *  NOTE:  The destructor is not called and it is the responsibility
       *         of the application to free the memory.
       */

      _POSIX_Keys_Free( the_key );
      _Thread_Enable_dispatch();
      return 0;

#if defined(RTEMS_MULTIPROCESSING)
    case OBJECTS_REMOTE:   /* should never happen */
#endif
    case OBJECTS_ERROR:
      break;
  }

  return EINVAL;
}
