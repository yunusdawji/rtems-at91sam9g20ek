##
## $Id: Makefile.am,v 1.10 2005/10/16 07:30:12 ralf Exp $
##

ACLOCAL_AMFLAGS = -I ../../../aclocal

# Descend into the @RTEMS_BSP_FAMILY@ directory
SUBDIRS = @RTEMS_BSP_FAMILY@

EXTRA_DIST =
EXTRA_DIST += shared/console.c
EXTRA_DIST += shared/setvec.c

include $(top_srcdir)/../../../automake/subdirs.am
include $(top_srcdir)/../../../automake/local.am
