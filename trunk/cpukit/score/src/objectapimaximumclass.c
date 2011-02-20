/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: objectapimaximumclass.c,v 1.2 2009/07/07 23:33:17 joel Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/score/object.h>

unsigned int _Objects_API_maximum_class(
  uint32_t api
)
{
  switch (api) {
    case OBJECTS_INTERNAL_API:
      return OBJECTS_INTERNAL_CLASSES_LAST;
    case OBJECTS_CLASSIC_API:
      return OBJECTS_RTEMS_CLASSES_LAST;
    case OBJECTS_POSIX_API:
      return OBJECTS_POSIX_CLASSES_LAST;
    case OBJECTS_ITRON_API:
      return OBJECTS_ITRON_CLASSES_LAST;
    case OBJECTS_NO_API:
    default:
      break;
  }
  return 0;
}

