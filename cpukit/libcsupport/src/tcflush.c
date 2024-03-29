/*
 *  tcflush() - POSIX 1003.1b 7.2.2 - Line Control Functions
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: tcflush.c,v 1.6 2009/09/15 09:42:46 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#if defined(RTEMS_NEWLIB)

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <termios.h>
/* #include <sys/ioctl.h> */

#include <rtems/libio.h>

int tcflush (
  int fd __attribute__((unused)),
  int queue __attribute__((unused)) )
{
  return 0;
}

#endif
