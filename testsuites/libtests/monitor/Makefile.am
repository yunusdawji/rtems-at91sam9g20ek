##
## $Id: Makefile.am,v 1.22 2009/04/03 12:46:19 ralf Exp $
##

MANAGERS = dpmem event io msg mp part region sem signal timer rate_monotonic \
    ext

rtems_tests_PROGRAMS = monitor
monitor_SOURCES = init.c system.h

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

monitor_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(monitor_OBJECTS) $(monitor_LDADD)
LINK_LIBS = $(monitor_LDLIBS)

monitor$(EXEEXT): $(monitor_OBJECTS) $(monitor_DEPENDENCIES)
	@rm -f monitor$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
