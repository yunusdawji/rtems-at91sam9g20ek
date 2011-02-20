/*
 *  lstat() - BSD 4.3 and SVR4 - Get File Status
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: lstat.c,v 1.5 2008/09/01 11:42:19 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#define _STAT_NAME         lstat
#define _STAT_R_NAME       _lstat_r
#define _STAT_FOLLOW_LINKS false

#include "stat.c"
