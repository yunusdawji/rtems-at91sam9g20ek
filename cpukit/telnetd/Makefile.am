##
## $Id: Makefile.am,v 1.24 2007/09/24 21:35:10 joel Exp $
##

include $(top_srcdir)/automake/compile.am

if LIBNETWORKING
if LIBSHELL
include_rtemsdir = $(includedir)/rtems
include_rtems_HEADERS = pty.h telnetd.h passwd.h

project_lib_LIBRARIES = libtelnetd.a
libtelnetd_a_SOURCES = check_passwd.c des.c icmds.c pty.c telnetd.c
libtelnetd_a_CPPFLAGS = $(AM_CPPFLAGS)
endif
endif

EXTRA_DIST = README

include $(srcdir)/preinstall.am
include $(top_srcdir)/automake/local.am
