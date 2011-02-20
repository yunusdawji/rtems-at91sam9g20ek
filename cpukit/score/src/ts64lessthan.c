/**
 * @file score/src/ts64lessthan.c
*/

/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ts64lessthan.c,v 1.1 2008/12/09 21:27:35 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>

#include <rtems/system.h>
#include <rtems/score/timestamp.h>

#if defined(CPU_RTEMS_SCORE_TIMESTAMP_IS_INT64) && \
    !defined(CPU_RTEMS_SCORE_TIMESTAMP_INT64_INLINE)
bool _Timestamp64_Less_than(
  Timestamp64_Control *_lhs,
  Timestamp64_Control *_rhs
)
{
  return (*(_lhs) < *(_rhs));
}
#endif
