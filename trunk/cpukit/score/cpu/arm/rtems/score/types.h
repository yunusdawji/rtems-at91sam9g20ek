/**
 * @file
 *
 * @ingroup ScoreCPU
 *
 * @brief ARM architecture types API.
 */

/*
 *  $Id: types.h,v 1.18 2010/04/08 10:13:46 thomas Exp $
 *
 *  This include file contains type definitions pertaining to the
 *  arm processor family.
 *
 *  COPYRIGHT (c) 2000 Canon Research Centre France SA.
 *  Emmanuel Raguet, mailto:raguet@crf.canon.fr
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 */

#ifndef _RTEMS_SCORE_TYPES_H
#define _RTEMS_SCORE_TYPES_H

#ifndef ASM

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ScoreCPU
 *
 * @{
 */

/*
 *  This section defines the basic types for this processor.
 */

typedef uint16_t         Priority_Bit_map_control;

#ifdef RTEMS_DEPRECATED_TYPES
typedef bool		boolean;            /* Boolean value   */
typedef float           single_precision;   /* single precision float */
typedef double          double_precision;   /* double precision float */
#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* !ASM */

#endif
