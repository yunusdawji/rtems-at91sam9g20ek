/*
 *  $Id: setpgid.c,v 1.3 2009/09/30 04:42:18 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <unistd.h>
#include <errno.h>
#include <rtems/seterr.h>

/*PAGE
 *
 *  4.3.3 Set Process Group ID for Job Control, P1003.1b-1993, p. 89
 */

int setpgid(
  pid_t  pid __attribute__((unused)),
  pid_t  pgid __attribute__((unused))
)
{
  rtems_set_errno_and_return_minus_one( ENOSYS );
}
