##
## $Id: Makefile.am,v 1.1 2009/06/08 21:05:20 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = sp52
sp52_SOURCES = init.c

dist_rtems_tests_DATA = sp52.scn
dist_rtems_tests_DATA += sp52.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

sp52_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(sp52_OBJECTS) $(sp52_LDADD)
LINK_LIBS = $(sp52_LDLIBS)

sp52$(EXEEXT): $(sp52_OBJECTS) $(sp52_DEPENDENCIES)
	@rm -f sp52$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
