## $Id: Makefile.am,v 1.10 2009/12/14 18:28:02 joel Exp $

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../../../testsuites/automake/compile.am

include $(top_srcdir)/ada.am

AM_ADAFLAGS += -I$(srcdir)/..

noinst_PROGRAMS = mp01_ada_mp01_node2
mp01_ada_mp01_node2_SOURCES = mp01_node2.adb ../mptest.adb config.h
mp01_ada_mp01_node2_SOURCES += ../mptest.ads
mp01_ada_mp01_node2_SOURCES += ../../../support/init.c

mp01_ada_mp01_node2$(EXEEXT): mp01_node2.adb ../mptest.adb init.$(OBJEXT)
	$(GNATCOMPILE) -margs -a $< -o $@

scndir = $(rtems_ada_testsdir)
dist_scn_DATA = ada_mp01-node2.scn

include $(top_srcdir)/../../../testsuites/automake/local.am
