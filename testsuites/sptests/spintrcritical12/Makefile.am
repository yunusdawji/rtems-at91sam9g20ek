##
## $Id: Makefile.am,v 1.1 2009/07/21 23:06:13 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = spintrcritical12
spintrcritical12_SOURCES = ../spintrcritical11/init.c \
    ../spintrcritical_support/intrcritical.c

dist_rtems_tests_DATA = spintrcritical12.scn
dist_rtems_tests_DATA += spintrcritical12.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

spintrcritical12_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include
AM_CPPFLAGS += -I$(top_srcdir)/spintrcritical_support
AM_CPPFLAGS += -DEVENT_ALL

LINK_OBJS = $(spintrcritical12_OBJECTS) $(spintrcritical12_LDADD)
LINK_LIBS = $(spintrcritical12_LDLIBS)

spintrcritical12$(EXEEXT): $(spintrcritical12_OBJECTS) $(spintrcritical12_DEPENDENCIES)
	@rm -f spintrcritical12$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
