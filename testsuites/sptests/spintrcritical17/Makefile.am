##
## $Id: Makefile.am,v 1.1 2009/11/30 09:08:35 thomas Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spintrcritical17
spintrcritical17_SOURCES = init.c \
    ../spintrcritical_support/intrcritical.c

dist_rtems_tests_DATA = spintrcritical17.scn
dist_rtems_tests_DATA += spintrcritical17.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spintrcritical17_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include
AM_CPPFLAGS += -I$(top_srcdir)/spintrcritical_support

LINK_OBJS = $(spintrcritical17_OBJECTS) $(spintrcritical17_LDADD)
LINK_LIBS = $(spintrcritical17_LDLIBS)

spintrcritical17$(EXEEXT): $(spintrcritical17_OBJECTS) $(spintrcritical17_DEPENDENCIES)
	@rm -f spintrcritical17$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
