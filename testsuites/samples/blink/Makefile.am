##
##  $Id: Makefile.am,v 1.26 2009/04/03 12:42:12 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = blink
blink_SOURCES = init.c tasks.c system.h

dist_rtems_tests_DATA = blink.scn
dist_rtems_tests_DATA += blink.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

blink_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

LINK_OBJS = $(blink_OBJECTS) $(blink_LDADD)
LINK_LIBS = $(blink_LDLIBS)

blink$(EXEEXT): $(blink_OBJECTS) $(blink_DEPENDENCIES)
	@rm -f blink$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
