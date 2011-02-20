/*
 *  $Id: rtems_bootp.c,v 1.6 2010/02/18 00:24:25 ccj Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <rtems/error.h>
#include <sys/types.h>
#include <rtems/rtems_bsdnet.h>
#include <rtems/rtems_bsdnet_internal.h>

/*
 * Perform a BOOTP request
 */
void
rtems_bsdnet_do_bootp (void)
{
  bool ok;
	rtems_bsdnet_semaphore_obtain ();
	ok = bootpc_init (false, true);
	rtems_bsdnet_semaphore_release ();
  if (!ok)
    panic ("rtems_bsdnet_do_bootp: bootp failed");
}

/*
 * Perform a BOOTP request and update "standard" files in /etc
 * with the results.
 */
void
rtems_bsdnet_do_bootp_and_rootfs (void)
{
  bool ok;
	rtems_bsdnet_semaphore_obtain ();
	ok = bootpc_init (true, true);
	rtems_bsdnet_semaphore_release ();
  if (!ok)
    panic ("rtems_bsdnet_do_bootp_and_rootfs: bootp failed");
}
