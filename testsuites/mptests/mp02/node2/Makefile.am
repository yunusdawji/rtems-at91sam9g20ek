##
## $Id: Makefile.am,v 1.32 2009/04/03 12:55:13 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = mp02-node2
mp02_node2_SOURCES = ../init.c ../task1.c ../system.h

dist_rtems_tests_DATA = mp02-node2.scn
dist_rtems_tests_DATA += mp02-node2.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

mp02_node2_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -DNODE_NUMBER=2 -I$(srcdir)/..

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(mp02_node2_OBJECTS) $(mp02_node2_LDADD)
LINK_LIBS = $(mp02_node2_LDLIBS)

mp02-node2$(EXEEXT): $(mp02_node2_OBJECTS) $(mp02_node2_DEPENDENCIES)
	@rm -f mp02-node2$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
