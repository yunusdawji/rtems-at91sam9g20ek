##
## $Id: Makefile.am,v 1.3 2010/03/27 14:59:26 joel Exp $
##

include $(top_srcdir)/automake/compile.am

include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS = rtems/asm.h

include_rtems_bfindir = $(includedir)/rtems/bfin
include_rtems_bfin_HEADERS = rtems/bfin/bfin.h rtems/bfin/bf533.h

include_rtems_scoredir = $(includedir)/rtems/score
include_rtems_score_HEADERS = rtems/score/cpu.h rtems/score/bfin.h \
    rtems/score/cpu_asm.h rtems/score/types.h

noinst_LIBRARIES = libscorecpu.a
libscorecpu_a_SOURCES = cpu.c cpu_asm.S
libscorecpu_a_CPPFLAGS = $(AM_CPPFLAGS)

include $(srcdir)/preinstall.am
include $(top_srcdir)/automake/local.am
