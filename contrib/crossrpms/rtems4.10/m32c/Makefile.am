# $Id: Makefile.am,v 1.119.2.10 2011/01/29 11:42:59 ralf Exp $

TARGET = m32c-rtems4.10

include $(top_srcdir)/mkspec.am

BINUTILS_VERS = 2.20.1
BINUTILS_PKGVERS = $(BINUTILS_VERS)
BINUTILS_RPMREL = 3
include ../binutils.am
BINUTILS_OPTS +=

GCC_VERS = 4.4.5
GCC_PKGVERS = $(GCC_VERS)
GCC_RPMREL = 5
NEWLIB_VERS = 1.18.0
NEWLIB_PKGVERS = $(NEWLIB_VERS)
NEWLIB_RPMREL = `expr $(GCC_RPMREL) + 15`
include ../gcc.am
GCC_OPTS +=

GDB_VERS = 7.1
GDB_PKGVERS = $(GDB_VERS)
GDB_RPMREL = 4
include ../gdb.am
GDB_OPTS +=
