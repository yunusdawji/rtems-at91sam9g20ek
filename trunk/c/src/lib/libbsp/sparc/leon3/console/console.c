/*
 *  This file contains the TTY driver for the serial ports on the LEON.
 *
 *  This driver uses the termios pseudo driver.
 *
 *  COPYRIGHT (c) 1989-1998.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  Modified for LEON3 BSP.
 *  COPYRIGHT (c) 2004.
 *  Gaisler Research.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: console.c,v 1.14 2010/05/24 15:05:19 joel Exp $
 */

#include <bsp.h>
#include <rtems/libio.h>
#include <stdlib.h>
#include <assert.h>
#include <rtems/bspIo.h>
#include <amba.h>

/*
 *  Should we use a polled or interrupt drived console?
 *
 *  NOTE: This is defined in the custom/leon.cfg file.
 */

/*
 *  console_outbyte_polled
 *
 *  This routine transmits a character using polling.
 */

void console_outbyte_polled(
  int  port,
  char ch
);

/* body is in debugputs.c */

/*
 *  console_inbyte_nonblocking
 *
 *  This routine polls for a character.
 */

int console_inbyte_nonblocking( int port );

/* body is in debugputs.c */


/*
 *  Console Termios Support Entry Points
 *
 */

ssize_t console_write_support (int minor, const char *buf, size_t len)
{
  int nwrite = 0;

  while (nwrite < len) {
    console_outbyte_polled( minor, *buf++ );
    nwrite++;
  }
  return nwrite;
}


/*
 *  Console Device Driver Entry Points
 *
 */
int uarts = 0;
volatile LEON3_UART_Regs_Map *LEON3_Console_Uart[LEON3_APBUARTS];

rtems_device_driver console_initialize(
  rtems_device_major_number  major,
  rtems_device_minor_number  minor,
  void                      *arg
)
{
  rtems_status_code status;
  int i, uart0;
  char console_name[16];

  rtems_termios_initialize();

  /* default console to zero and override if multiprocessing */
  uart0 = 0;
  #if defined(RTEMS_MULTIPROCESSING)
    if (rtems_configuration_get_user_multiprocessing_table() != NULL)
      uart0 =  LEON3_Cpu_Index;
  #endif

  /*  Register Device Names */
  if (uarts && (uart0 < uarts)) {
    status = rtems_io_register_name( "/dev/console", major, 0 );
    if (status != RTEMS_SUCCESSFUL)
      rtems_fatal_error_occurred(status);

    strcpy(console_name,"/dev/console_a");
    for (i = uart0+1; i < uarts; i++) {
      console_name[13]++;
      status = rtems_io_register_name( console_name, major, i);
    }
  }

  /*
   *  Initialize Hardware if ONLY CPU or first CPU in MP system
   */

  #if defined(RTEMS_MULTIPROCESSING)
    if (rtems_configuration_get_user_multiprocessing_table()->node == 1)
  #endif
  {
    for (i = uart0; i < uarts; i++)
    {
      LEON3_Console_Uart[i]->ctrl |=
        LEON_REG_UART_CTRL_RE | LEON_REG_UART_CTRL_TE;
      LEON3_Console_Uart[i]->status = 0;
    }
  }

  return RTEMS_SUCCESSFUL;
}

rtems_device_driver console_open(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  rtems_status_code sc;

  static const rtems_termios_callbacks pollCallbacks = {
    NULL,                        /* firstOpen */
    NULL,                        /* lastClose */
    console_inbyte_nonblocking,  /* pollRead */
    console_write_support,       /* write */
    NULL,                        /* setAttributes */
    NULL,                        /* stopRemoteTx */
    NULL,                        /* startRemoteTx */
    0                            /* outputUsesInterrupts */
  };


  assert( minor <= LEON3_APBUARTS );
  if ( minor > LEON3_APBUARTS )
    return RTEMS_INVALID_NUMBER;

  sc = rtems_termios_open (major, minor, arg, &pollCallbacks);


  return RTEMS_SUCCESSFUL;
}

rtems_device_driver console_close(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  return rtems_termios_close (arg);
}

rtems_device_driver console_read(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  return rtems_termios_read (arg);
}

rtems_device_driver console_write(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  return rtems_termios_write (arg);
}

rtems_device_driver console_control(
  rtems_device_major_number major,
  rtems_device_minor_number minor,
  void                    * arg
)
{
  return rtems_termios_ioctl (arg);
}

