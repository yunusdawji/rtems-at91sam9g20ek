##
## $Id: Makefile.am,v 1.1 2009/07/28 19:23:49 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spintrcritical16
spintrcritical16_SOURCES = init.c \
    ../spintrcritical_support/intrcritical.c

dist_rtems_tests_DATA = spintrcritical16.scn
dist_rtems_tests_DATA += spintrcritical16.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spintrcritical16_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include
AM_CPPFLAGS += -I$(top_srcdir)/spintrcritical_support

LINK_OBJS = $(spintrcritical16_OBJECTS) $(spintrcritical16_LDADD)
LINK_LIBS = $(spintrcritical16_LDLIBS)

spintrcritical16$(EXEEXT): $(spintrcritical16_OBJECTS) $(spintrcritical16_DEPENDENCIES)
	@rm -f spintrcritical16$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
