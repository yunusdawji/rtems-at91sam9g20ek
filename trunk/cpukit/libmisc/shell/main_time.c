/*
 *  Time Shell Command Implmentation
 *
 *  Author: Chris Johns <chrisj@rtems.org>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: main_time.c,v 1.2 2009/11/29 12:12:39 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <rtems.h>
#include <rtems/shell.h>
#include "internal.h"

int rtems_shell_main_time(
  int   argc,
  char *argv[]
)
{
  rtems_shell_cmd_t* shell_cmd;
  int                errorlevel = 0;
  struct timespec    start;
  struct timespec    end;
  struct timespec    period;
  rtems_status_code  sc;

  argc--;

  sc = rtems_clock_get_uptime(&start);
  if (sc != RTEMS_SUCCESSFUL)
    printf("error: cannot read time\n");

  if (argc) {
    shell_cmd = rtems_shell_lookup_cmd(argv[1]);
    if ( argv[1] == NULL ) {
      errorlevel = -1;
    } else if ( shell_cmd == NULL ) {
      errorlevel = rtems_shell_script_file(argc, &argv[1]);
    } else {
      errorlevel = shell_cmd->command(argc, &argv[1]);
    }
  }

  sc = rtems_clock_get_uptime(&end);
  if (sc != RTEMS_SUCCESSFUL)
    printf("error: cannot read time\n");

  period.tv_sec = end.tv_sec - start.tv_sec;
  period.tv_nsec = end.tv_nsec - start.tv_nsec;
  if (period.tv_nsec < 0)
  {
    --period.tv_sec;
    period.tv_nsec += 1000000000UL;
  }

  printf("time: %li:%02li:%02li.%03li\n",
         period.tv_sec / 3600,
         period.tv_sec / 60, period.tv_sec % 60,
         period.tv_nsec / 1000000);

  return errorlevel;
}

rtems_shell_cmd_t rtems_shell_TIME_Command = {
  "time",                                     /* name */
  "time command [arguments...]",              /* usage */
  "misc",                                     /* topic */
  rtems_shell_main_time,                      /* command */
  NULL,                                       /* alias */
  NULL                                        /* next */
};
