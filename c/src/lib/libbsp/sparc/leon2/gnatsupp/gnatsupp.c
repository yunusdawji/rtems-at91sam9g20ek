/*
 *
 * Support for gnat/rtems interrupts and exception handling.
 * Jiri Gaisler, ESA/ESTEC, 17-02-1999.
 *
 *  $Id: gnatsupp.c,v 1.3 2008/08/18 11:53:53 ralf Exp $
 */

void __gnat_install_handler_common (int t1, int t2);

/*
 *  Avoid trap 0x18 which is used by the clock tick, and
 *  0x12 (UART B interrupt) which is used by the stub.
 */

void
__gnat_install_handler (void)
{
  __gnat_install_handler_common (0x18, 0x12);
}
