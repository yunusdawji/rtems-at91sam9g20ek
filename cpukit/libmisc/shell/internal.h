/*
 *  Shell Internal Information
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: internal.h,v 1.7 2009/06/12 01:53:33 ccj Exp $
 */

#ifndef _RTEMS_SHELL_INTERNAL_H
#define _RTEMS_SHELL_INTERNAL_H

struct rtems_shell_topic_tt;
typedef struct rtems_shell_topic_tt rtems_shell_topic_t;

struct rtems_shell_topic_tt {
  const char          *topic;
  rtems_shell_topic_t *next;
};


extern rtems_shell_cmd_t   * rtems_shell_first_cmd;
extern rtems_shell_topic_t * rtems_shell_first_topic;

rtems_shell_topic_t * rtems_shell_lookup_topic(const char *topic);


void rtems_shell_register_monitor_commands(void);
void rtems_shell_initialize_command_set(void);

void rtems_shell_print_heap_info(
  const char       *c,
  Heap_Information *h
);

#endif
