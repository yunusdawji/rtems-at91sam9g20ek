##
## $Id: Makefile.am,v 1.1 2009/07/29 20:15:33 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = psxmsgq04
psxmsgq04_SOURCES = init.c ../include/pmacros.h \
     ../../support/src/test_support.c

dist_rtems_tests_DATA = psxmsgq04.scn
dist_rtems_tests_DATA += psxmsgq04.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

psxmsgq04_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/include
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(psxmsgq04_OBJECTS) $(psxmsgq04_LDADD)
LINK_LIBS = $(psxmsgq04_LDLIBS)

psxmsgq04$(EXEEXT): $(psxmsgq04_OBJECTS) $(psxmsgq04_DEPENDENCIES)
	@rm -f psxmsgq04$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
