/*
 *  malloc_report_statistics with plugin Implementation
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: malloc_report_statistics_plugin.c,v 1.3 2009/09/14 14:48:38 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef RTEMS_NEWLIB
#include "malloc_p.h"
#include "inttypes.h"

void malloc_report_statistics_with_plugin(
  void                  *context,
  rtems_printk_plugin_t  print
)
{
  rtems_malloc_statistics_t *s;
  uintmax_t allocated;

  s = &rtems_malloc_statistics;

  allocated  = s->lifetime_allocated - s->lifetime_freed;

  (*print)(
    context,
    "Malloc statistics\n"
    "  avail:%"PRIu32"k  allocated:%"PRIu32"k (%"PRId32"%%) "
      "max:%"PRIu32"k (%"PRIu32"%%)"
      " lifetime:%"PRIu32"k freed:%"PRIu32"k\n",
    s->space_available / 1024,
    allocated / 1024,
    /* avoid float! */
    (allocated * 100) / s->space_available,
    s->max_depth / 1024,
    (s->max_depth * 100) / s->space_available,
    (uint32_t) (s->lifetime_allocated / 1024),
    (uint32_t) (s->lifetime_freed / 1024)
  );
  (*print)(
    context,
    "  Call counts:   malloc:%"PRIu32"   memalign:%"PRIu32"   free:%"PRIu32
       "   realloc:%"PRIu32"   calloc:%"PRIu32"\n",
    s->malloc_calls,
    s->memalign_calls,
    s->free_calls,
    s->realloc_calls,
    s->calloc_calls
  );
}

#endif
