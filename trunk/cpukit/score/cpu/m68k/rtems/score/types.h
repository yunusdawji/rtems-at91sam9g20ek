/**
 * @file rtems/score/types.h
 */

/*
 *  This include file contains type definitions pertaining to the Motorola
 *  m68xxx processor family.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: types.h,v 1.14 2008/12/11 00:45:34 ralf Exp $
 */

#ifndef _RTEMS_SCORE_TYPES_H
#define _RTEMS_SCORE_TYPES_H

#ifndef ASM

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  This section defines the basic types for this processor.
 */

typedef uint16_t     Priority_Bit_map_control;
typedef void m68k_isr;
typedef void ( *m68k_isr_entry )( void );

#ifdef RTEMS_DEPRECATED_TYPES
typedef bool	boolean;     		/* Boolean value   */
typedef float	single_precision;	/* single precision float */
typedef double	double_precision;	/* double precision float */
#endif

#ifdef __cplusplus
}
#endif

#endif  /* !ASM */

#endif
