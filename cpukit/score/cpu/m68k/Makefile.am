##
## $Id: Makefile.am,v 1.39 2006/01/12 09:57:43 ralf Exp $
##

include $(top_srcdir)/automake/compile.am

noinst_LIBRARIES = libscorecpu.a
libscorecpu_a_CPPFLAGS = $(AM_CPPFLAGS)

include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS = rtems/asm.h

include_rtems_m68kdir = $(includedir)/rtems/m68k
include_rtems_m68k_HEADERS = rtems/m68k/m68302.h rtems/m68k/m68360.h \
    rtems/m68k/qsm.h rtems/m68k/sim.h

include_rtems_scoredir = $(includedir)/rtems/score
include_rtems_score_HEADERS = rtems/score/cpu.h rtems/score/m68k.h \
    rtems/score/types.h

libscorecpu_a_SOURCES = cpu.c cpu_asm.S

include $(srcdir)/preinstall.am
include $(top_srcdir)/automake/local.am
