##
## $Id: Makefile.am,v 1.26 2009/04/03 12:51:09 ralf Exp $
##

MANAGERS = io message semaphore

rtems_tests_PROGRAMS = tm11
tm11_SOURCES = task1.c system.h ../include/timesys.h \
    ../../support/src/tmtests_empty_function.c

dist_rtems_tests_DATA = tm11.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am

tm11_LDADD = $(MANAGERS_NOT_WANTED:%=$(PROJECT_LIB)/no-%.rel)

OPERATION_COUNT = @OPERATION_COUNT@
AM_CPPFLAGS += -I$(top_srcdir)/include -DOPERATION_COUNT=$(OPERATION_COUNT)
AM_CPPFLAGS += -I$(top_srcdir)/../support/include

LINK_OBJS = $(tm11_OBJECTS) $(tm11_LDADD)
LINK_LIBS = $(tm11_LDLIBS)

tm11$(EXEEXT): $(tm11_OBJECTS) $(tm11_DEPENDENCIES)
	@rm -f tm11$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am
