/*
 *  COPYRIGHT (c) 1988-2002.
 *  On-Line Applications Research Corporation (OAR).
 *  All rights reserved.
 *
 *  $Id: system.h,v 1.7 2007/12/07 02:42:57 ralf Exp $
 */

#ifndef __SYSTEM_h
#define __SYSTEM_h

#define STATIC static
#define INLINE inline

#ifndef NULL
#define NULL 0
#endif

typedef unsigned int   boolean;

#if !defined( TRUE ) || (TRUE != 1)
#undef TRUE
#define TRUE     (1)
#endif

#if !defined( FALSE ) || (FALSE != 0)
#undef FALSE
#define FALSE 0
#endif

#endif
