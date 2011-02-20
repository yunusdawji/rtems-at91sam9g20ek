/*
 *  Cache Management Support Routines for the SPARC
 *
 *  $Id: cache.c,v 1.2 2000/11/27 17:02:39 joel Exp $
 */

#include <rtems.h>
#include "cache_.h"


#if defined(HAS_INSTRUCTION_CACHE)

void _CPU_cache_invalidate_entire_instruction ( void )
{
  asm volatile ("flush");
}

/* XXX these need to be addressed */
void _CPU_cache_freeze_instruction ( void )
{
}

void _CPU_cache_unfreeze_instruction ( void )
{
}

void _CPU_cache_enable_instruction ( void )
{
}

void _CPU_cache_disable_instruction (   void )
{
}

#endif
/* end of file */
