##
## $Id: Makefile.am,v 1.1 2009/07/21 19:32:30 joel Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = sp10
sp10_SOURCES = init.c

dist_rtems_tests_DATA = sp10.scn
dist_rtems_tests_DATA += sp10.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

sp10_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(sp10_OBJECTS) $(sp10_LDADD)
LINK_LIBS = $(sp10_LDLIBS)

sp10$(EXEEXT): $(sp10_OBJECTS) $(sp10_DEPENDENCIES)
	@rm -f sp10$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
