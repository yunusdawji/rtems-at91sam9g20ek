## Process this file with autoconf to produce a configure script.
## 
## $Id: configure.ac,v 1.21.2.1 2011/02/02 15:18:11 ralf Exp $

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-tests-tmitrontests],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([tmitronsem01])
RTEMS_TOP([../..],[..])

RTEMS_CANONICAL_TARGET_CPU

AM_INIT_AUTOMAKE([no-define foreign 1.11.1])
AM_MAINTAINER_MODE


RTEMS_ENV_RTEMSBSP

RTEMS_PROJECT_ROOT

RTEMS_PROG_CC_FOR_TARGET

RTEMS_CANONICALIZE_TOOLS

RTEMS_CHECK_CUSTOM_BSP(RTEMS_BSP)


OPERATION_COUNT=${OPERATION_COUNT-100}
AC_SUBST(OPERATION_COUNT)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile
tmitronsem01/Makefile
])
AC_OUTPUT
