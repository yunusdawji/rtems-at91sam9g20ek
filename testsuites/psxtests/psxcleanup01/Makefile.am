##
## $Id: Makefile.am,v 1.1 2009/10/12 00:00:04 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psxcleanup01
psxcleanup01_SOURCES = init.c ../include/pmacros.h

dist_rtems_tests_DATA = psxcleanup01.scn

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psxcleanup01_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psxcleanup01_OBJECTS) $(psxcleanup01_LDADD)
LINK_LIBS = $(psxcleanup01_LDLIBS)

psxcleanup01$(EXEEXT): $(psxcleanup01_OBJECTS) $(psxcleanup01_DEPENDENCIES)
	@rm -f psxcleanup01$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
