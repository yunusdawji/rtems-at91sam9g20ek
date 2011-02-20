## Process this file with autoconf to produce a configure script.
##
## $Id: configure.ac,v 1.22.2.1 2011/02/02 15:15:57 ralf Exp $

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-lib-libbsp-m68k-mvme147],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.11.1])
RTEMS_BSP_CONFIGURE

RTEMS_PROG_CC_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS

RTEMS_BSP_CLEANUP_OPTIONS(0, 0)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
