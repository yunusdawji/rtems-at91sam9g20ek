## Process this file with autoconf to produce a configure script.
## 
## $Id: configure.ac,v 1.12.6.1 2011/02/02 15:18:18 ralf Exp $

AC_PREREQ([2.68])
AC_INIT([rtems-tools-cpu-generic],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([size_rtems.in])
RTEMS_TOP(../../..)

RTEMS_CANONICAL_TARGET_CPU

AM_INIT_AUTOMAKE([no-define foreign 1.11.1])
AM_MAINTAINER_MODE

RTEMS_PATH_KSH

RTEMS_TOOLPATHS
AC_SUBST(program_prefix)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile
size_rtems])
AC_OUTPUT
