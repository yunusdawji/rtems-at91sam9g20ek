/*
 *  ITRON Message Buffer Manager
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: msgbuffer.c,v 1.14 2009/11/03 05:23:05 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/itron.h>
#include <rtems/config.h>
#include <rtems/itron/msgbuffer.h>
#include <rtems/itron/task.h>

/*
 *  _ITRON_Message_buffer_Manager_initialization
 *
 *  This routine initializes all message buffer manager related data
 *  structures.
 *
 *  Input parameters:   NONE
 *
 *  Output parameters:  NONE
 */

void _ITRON_Message_buffer_Manager_initialization(void)
{
  _Objects_Initialize_information(
    &_ITRON_Message_buffer_Information, /* object information table */
    OBJECTS_ITRON_API,                  /* object API */
    OBJECTS_ITRON_MESSAGE_BUFFERS,      /* object class */
    Configuration_ITRON_API.maximum_message_buffers,
                               /* maximum objects of this class */
    sizeof( ITRON_Message_buffer_Control ),
                               /* size of this object's control block */
    false,                     /* true if names for this object are strings */
    ITRON_MAXIMUM_NAME_LENGTH  /* maximum length of each object's name */
#if defined(RTEMS_MULTIPROCESSING)
    ,
    false,                     /* true if this is a global object class */
    NULL                       /* Proxy extraction support callout */
#endif
  );

  /*
   *  Register the MP Process Packet routine.
   *
   *  NOTE: No MP Support YET in RTEMS ITRON implementation.
   */
}
