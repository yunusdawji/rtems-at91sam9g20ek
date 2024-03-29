## Process this file with autoconf to produce a configure script.
##
## $Id: configure.ac,v 1.33.2.1 2011/02/02 15:16:50 ralf Exp $

AC_PREREQ([2.68])
AC_INIT([rtems-c-src-lib-libbsp-powerpc-psim],[_RTEMS_VERSION],[http://www.rtems.org/bugzilla])
AC_CONFIG_SRCDIR([bsp_specs])
RTEMS_TOP(../../../../../..)

RTEMS_CANONICAL_TARGET_CPU
AM_INIT_AUTOMAKE([no-define nostdinc foreign 1.11.1])
RTEMS_BSP_CONFIGURE

RTEMS_PROG_CC_FOR_TARGET
RTEMS_CANONICALIZE_TOOLS
RTEMS_PROG_CCAS

RTEMS_CHECK_NETWORKING

AM_CONDITIONAL(HAS_NETWORKING,test "$HAS_NETWORKING" = "yes")

RTEMS_CONFIG_BUILD_SUBDIRS(tools)

RTEMS_BSPOPTS_SET([PPC_USE_SPRG],[*],[0])
RTEMS_BSPOPTS_HELP([PPC_USE_SPRG],
[If defined, then the PowerPC specific code in RTEMS will use some
of the special purpose registers to slightly optimize interrupt
response time.  The use of these registers can conflict with
other tools like debuggers.])

RTEMS_BSPOPTS_SET([PPC_VECTOR_FILE_BASE],[*],[0xFFF00100])
RTEMS_BSPOPTS_HELP([PPC_VECTOR_FILE_BASE],
[This defines the base address of the exception table.
 NOTE: Vectors are actually at 0xFFF00000 but file starts at offset.])

RTEMS_BSPOPTS_SET([CLOCK_DRIVER_USE_FAST_IDLE],[psim],[1])
RTEMS_BSPOPTS_HELP([CLOCK_DRIVER_USE_FAST_IDLE],
[This sets a mode where the time runs as fast as possible when
 a clock ISR occurs while the IDLE thread is executing.  This can
 significantly reduce simulation times.])

RTEMS_BSP_CLEANUP_OPTIONS(0, 0)

# Explicitly list all Makefiles here
AC_CONFIG_FILES([Makefile])

RTEMS_PPC_EXCEPTIONS

AC_OUTPUT
