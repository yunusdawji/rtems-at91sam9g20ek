/*
 *  Input/Output Manager - Open Device
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ioopen.c,v 1.1 2007/05/29 19:56:35 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/io.h>

/*
 *  rtems_io_open
 *
 *  This routine is the open directive of the IO manager.
 *
 *  Input Paramters:
 *    major        - device driver number
 *    minor        - device number
 *    argument     - pointer to argument(s)
 *
 *  Output Parameters:
 *    returns       - return code
 */

rtems_status_code rtems_io_open(
  rtems_device_major_number  major,
  rtems_device_minor_number  minor,
  void                      *argument
)
{
  rtems_device_driver_entry callout;

  if ( major >= _IO_Number_of_drivers )
    return RTEMS_INVALID_NUMBER;

  callout = _IO_Driver_address_table[major].open_entry;
  return callout ? callout(major, minor, argument) : RTEMS_SUCCESSFUL;
}
