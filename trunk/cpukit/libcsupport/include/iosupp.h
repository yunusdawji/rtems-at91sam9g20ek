/**
 * @file rtems/iosupp.h
 */

/*
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: iosupp.h,v 1.9 2005/01/28 08:04:27 ralf Exp $
 */

#ifndef _RTEMS_IOSUPP_H
#define _RTEMS_IOSUPP_H

#ifdef __cplusplus
extern "C" {
#endif

/* character constants */

#define BS              0x08            /* backspace */
#define LF              0x0a            /* line feed */
#define CR              0x0d            /* carriage return */
#define XON             0x11            /* control-Q */
#define XOFF            0x13            /* control-S */

/* structures */

#ifdef IOSUPP_INIT
#define IOSUPP_EXTERN
#else
#undef IOSUPP_EXTERN
#define IOSUPP_EXTERN  extern
#endif

/* functions */

#ifdef __cplusplus
}
#endif

#endif
