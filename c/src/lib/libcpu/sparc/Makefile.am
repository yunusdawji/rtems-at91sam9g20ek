##
## $Id: Makefile.am,v 1.21 2008/09/26 13:40:04 ralf Exp $
##

ACLOCAL_AMFLAGS = -I ../../../aclocal

include $(top_srcdir)/../../../automake/compile.am

noinst_PROGRAMS =

include_libcpudir = $(includedir)/libcpu
include_libcpu_HEADERS = ../shared/include/cache.h

noinst_PROGRAMS += cache.rel
cache_rel_SOURCES = cache/cache.c cache/cache_.h \
    ../shared/src/cache_aligned_malloc.c ../shared/src/cache_manager.c
cache_rel_CPPFLAGS = $(AM_CPPFLAGS) -I$(srcdir)/cache
cache_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

if has_instruction_cache
cache_rel_CPPFLAGS += -DHAS_INSTRUCTION_CACHE
endif

noinst_PROGRAMS += syscall.rel
syscall_rel_SOURCES = syscall/syscall.S syscall/syscall.h
syscall_rel_CPPFLAGS = $(AM_CPPFLAGS)
syscall_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

noinst_PROGRAMS += reg_win.rel
reg_win_rel_SOURCES = reg_win/window.S
reg_win_rel_CPPFLAGS = $(AM_CPPFLAGS)
reg_win_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../automake/local.am
