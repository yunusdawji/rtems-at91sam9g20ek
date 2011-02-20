/*
 *  FTP Server Information
 *
 *  $Id: ftpd.h,v 1.9 2009/03/12 15:34:29 joel Exp $
 */

#ifndef _RTEMS_FTPD_H
#define _RTEMS_FTPD_H

#ifdef __cplusplus
extern "C" {
#endif

#define FTPD_CONTROL_PORT   21

/* FTPD access control flags */
enum
{
  FTPD_NO_WRITE = 0x1,
  FTPD_NO_READ  = 0x2,
  FTPD_NO_RW    = FTPD_NO_WRITE | FTPD_NO_READ
};

typedef int (*rtems_ftpd_hookfunction)(char *, size_t);

struct rtems_ftpd_hook
{
   char                    *filename;
   rtems_ftpd_hookfunction hook_function;
};

struct rtems_ftpd_configuration
{
   rtems_task_priority     priority;           /* FTPD task priority  */
   unsigned long           max_hook_filesize;  /* Maximum buffersize  */
                                               /*    for hooks        */
   int                     port;               /* Well-known port     */
   struct rtems_ftpd_hook  *hooks;             /* List of hooks       */
   char const              *root;              /* Root for FTPD or 0 for / */
   int                     tasks_count;        /* Max. connections    */
   int                     idle;               /* Idle timeout in seoconds
                                                  or 0 for no (inf) timeout */
   int                     access;             /* 0 - r/w, 1 - read-only,
                                                  2 - write-only,
                                                  3 - browse-only */
};

/*
 * Reply codes.
 */
#define PRELIM          1       /* positive preliminary */
#define COMPLETE        2       /* positive completion */
#define CONTINUE        3       /* positive intermediate */
#define TRANSIENT       4       /* transient negative completion */
#define ERROR           5       /* permanent negative completion */

int rtems_initialize_ftpd(void);

#ifdef __cplusplus
}
#endif

#endif  /* _RTEMS_FTPD_H */
