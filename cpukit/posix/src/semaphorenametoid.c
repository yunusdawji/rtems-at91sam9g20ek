/*
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: semaphorenametoid.c,v 1.13 2009/01/05 20:26:01 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdarg.h>

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/posix/semaphore.h>
#include <rtems/posix/time.h>
#include <rtems/seterr.h>

/*PAGE
 *
 *  _POSIX_Semaphore_Name_to_id
 *
 *  Look up the specified name and attempt to locate the id
 *  for the associated semaphore.
 */

int _POSIX_Semaphore_Name_to_id(
  const char     *name,
  sem_t          *id
)
{
  Objects_Name_or_id_lookup_errors  status;
  Objects_Id                        the_id;

   if ( !name )
     return EINVAL;

  if ( !name[0] )
    return EINVAL;

  status = _Objects_Name_to_id_string(
    &_POSIX_Semaphore_Information,
    name,
    &the_id
  );
  *id = the_id;

  if ( status == OBJECTS_NAME_OR_ID_LOOKUP_SUCCESSFUL )
    return 0;

  return ENOENT;
}
