##
## $Id: Makefile.am,v 1.32 2009/04/03 12:55:13 ralf Exp $
##

MANAGERS = all

rtems_tests_PROGRAMS = mp12-node1
mp12_node1_SOURCES = ../init.c ../system.h

dist_rtems_tests_DATA = mp12-node1.scn
dist_rtems_tests_DATA += mp12-node1.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

mp12_node1_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

AM_CPPFLAGS += -DNODE_NUMBER=1 -I$(srcdir)/..

AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(mp12_node1_OBJECTS) $(mp12_node1_LDADD)
LINK_LIBS = $(mp12_node1_LDLIBS)

mp12-node1$(EXEEXT): $(mp12_node1_OBJECTS) $(mp12_node1_DEPENDENCIES)
	@rm -f mp12-node1$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
