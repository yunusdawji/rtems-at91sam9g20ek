##
## $Id: Makefile.am,v 1.1 2010/04/05 17:06:57 joel Exp $
##

ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am

include_bspdir = $(includedir)/bsp

dist_project_lib_DATA = bsp_specs

include_HEADERS = include/bsp.h
include_HEADERS += include/tm27.h

nodist_include_HEADERS = include/bspopts.h
nodist_include_bsp_HEADERS = ../../shared/include/bootcard.h
DISTCLEANFILES = include/bspopts.h
noinst_PROGRAMS =

include_HEADERS += ../../shared/include/coverhd.h

noinst_LIBRARIES = libbspstart.a
libbspstart_a_SOURCES = start/start.S
project_lib_DATA = start.$(OBJEXT)

dist_project_lib_DATA += startup/linkcmds

noinst_LIBRARIES += libbsp.a
libbsp_a_SOURCES = \
    ../../shared/bspclean.c \
    ../../shared/bspreset_loop.c \
    ../../shared/bsppredriverhook.c \
    ../../shared/bsplibc.c \
    ../../shared/bsppost.c \
    ../../shared/bsppretaskinghook.c \
    ../../shared/bspgetworkarea.c \
    startup/init5225x.c startup/bspstart.c \
    ../../shared/bootcard.c \
    ../../shared/sbrk.c ../../m68k/shared/setvec.c \
    ../../shared/gnatinstallhandler.c
libbsp_a_SOURCES += clock/clock.c
libbsp_a_SOURCES += console/console.c
libbsp_a_SOURCES += console/debugio.c
libbsp_a_SOURCES += timer/timer.c

libbsp_a_LIBADD = \
    ../../../libcpu/@RTEMS_CPU@/shared/cache.rel \
    ../../../libcpu/@RTEMS_CPU@/shared/misc.rel

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
