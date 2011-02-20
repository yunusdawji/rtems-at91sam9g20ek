dnl $Id: path-ksh.m4,v 1.2 2003/11/26 06:18:03 ralf Exp $

AC_DEFUN([RTEMS_PATH_KSH],
[
dnl NOTE: prefer bash over ksh over sh
AC_PATH_PROGS(KSH,bash ksh sh)
if test -z "$KSH"; then
dnl NOTE: This cannot happen -- /bin/sh must always exist
AC_MSG_ERROR(
[***]
[    Cannot determine a usable shell bash/ksh/sh]
[    Please contact your system administrator] );
fi
])
