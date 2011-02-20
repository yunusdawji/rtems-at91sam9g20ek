/*
 *  This file contains the hardware specific portions of the TTY driver
 *  for the simulators stdin/out.
 *
 *  Logic based on newlib-1.8.2/newlib/libc/sys/sh/syscalls.c
 *
 *  COPYRIGHT (c) 1989-2000.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: console-io.c,v 1.7 2008/09/30 16:12:37 joel Exp $
 */

#include <bsp.h>
#include <rtems/libio.h>
#include <stdlib.h>
#include <assert.h>

#include <syscall.h>

int errno;

extern int __trap34(int, int, void*, int );

/*
 *  console_initialize_hardware
 *
 *  This routine initializes the console hardware.
 *
 */

void console_initialize_hardware(void)
{
  return;
}

/*
 *  console_outbyte_polled
 *
 *  This routine transmits a character using polling.
 */

void console_outbyte_polled(
  int  port,
  char ch
)
{
  __trap34 (SYS_write, 1, &ch, 1);
  return;
}

/*
 *  console_inbyte_nonblocking
 *
 *  This routine polls for a character.
 */

int console_inbyte_nonblocking(
  int port
)
{
  unsigned char c;

  return __trap34 (SYS_read, 0, &c, 1);
}

/* XXX wrong place for this */
int _sys_exit (int n)
{
  return __trap34 (SYS_exit, n, 0, 0);
}
