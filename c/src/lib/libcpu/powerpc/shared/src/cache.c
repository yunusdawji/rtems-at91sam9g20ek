/**
 * @file
 *
 * #ingroup powerpc_shared
 *
 * @brief Source file for the Cache Manager PowerPC support.
 */

/*
 *  Cache Management Support Routines for the MC68040
 * Modified for MPC8260 Andy Dachs <a.dachs@sstl.co.uk>
 * Surrey Satellite Technology Limited (SSTL), 2001
 *
 *  $Id: cache.c,v 1.12 2009/11/30 05:07:54 ralf Exp $
 */

#include <rtems.h>
#include "cache_.h"
#include <rtems/powerpc/registers.h>

/*
 * CACHE MANAGER: The following functions are CPU-specific.
 * They provide the basic implementation for the rtems_* cache
 * management routines. If a given function has no meaning for the CPU,
 * it does nothing by default.
 *
 * FIXME: Some functions simply have not been implemented.
 */

#if defined(ppc603) || defined(ppc603e) || defined(mpc8260) /* And possibly others */

/* Helpful macros */
#define PPC_Get_HID0( _value ) \
  do { \
      _value = 0;        /* to avoid warnings */ \
      asm volatile( \
          "mfspr %0, 0x3f0;"     /* get HID0 */ \
          "isync" \
          : "=r" (_value) \
          : "0" (_value) \
      ); \
  } while (0)

#define PPC_Set_HID0( _value ) \
  do { \
      asm volatile( \
          "isync;" \
          "mtspr 0x3f0, %0;"     /* load HID0 */ \
          "isync" \
          : "=r" (_value) \
          : "0" (_value) \
      ); \
  } while (0)

void _CPU_cache_enable_data (
	void )
{
  uint32_t   value;
  PPC_Get_HID0( value );
  value |= HID0_DCE;        /* set DCE bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_disable_data (
	void )
{
  uint32_t   value;
  PPC_Get_HID0( value );
  value &= ~HID0_DCE;        /* clear DCE bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_invalidate_entire_data (
	void )
{
  uint32_t  value;
  PPC_Get_HID0( value );
  value |= HID0_DCI;        /* set data flash invalidate bit */
  PPC_Set_HID0( value );
  value &= ~HID0_DCI;        /* clear data flash invalidate bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_freeze_data (
	void )
{
  uint32_t  value;
  PPC_Get_HID0( value );
  value |= HID0_DLOCK;        /* set data cache lock bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_unfreeze_data (
	void )
{
  uint32_t  value;
  PPC_Get_HID0( value );
  value &= ~HID0_DLOCK;        /* set data cache lock bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_flush_entire_data (
	void )
{
  /*
   * FIXME: how can we do this?
   */
}

void _CPU_cache_enable_instruction (
	void )
{
  uint32_t   value;
  PPC_Get_HID0( value );
  value |= 0x00008000;       /* Set ICE bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_disable_instruction (
	void )
{
  uint32_t   value;
  PPC_Get_HID0( value );
  value &= 0xFFFF7FFF;       /* Clear ICE bit */
  PPC_Set_HID0( value );
}


void _CPU_cache_invalidate_entire_instruction (
	void )
{
  uint32_t  value;
  PPC_Get_HID0( value );
  value |= HID0_ICFI;        /* set data flash invalidate bit */
  PPC_Set_HID0( value );
  value &= ~HID0_ICFI;        /* clear data flash invalidate bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_freeze_instruction (
	void )
{
  uint32_t  value;
  PPC_Get_HID0( value );
  value |= HID0_ILOCK;        /* set instruction cache lock bit */
  PPC_Set_HID0( value );
}

void _CPU_cache_unfreeze_instruction (
	void )
{
  uint32_t  value;
  PPC_Get_HID0( value );
  value &= ~HID0_ILOCK;        /* set instruction cache lock bit */
  PPC_Set_HID0( value );
}

#elif ( defined(mpx8xx) || defined(mpc860) || defined(mpc821) )

#define mtspr(_spr,_reg) \
  __asm__ volatile ( "mtspr %0, %1\n" : : "i" ((_spr)), "r" ((_reg)) )
#define isync \
  __asm__ volatile ("isync\n"::)

void _CPU_cache_flush_entire_data ( void ) {}
void _CPU_cache_invalidate_entire_data ( void ) {}
void _CPU_cache_freeze_data ( void ) {}
void _CPU_cache_unfreeze_data ( void ) {}

void _CPU_cache_enable_data ( void )
{
  uint32_t   r1;
  r1 = (0x2<<24);
  mtspr( 568, r1 );
  isync;
}

void _CPU_cache_disable_data ( void )
{
  uint32_t   r1;
  r1 = (0x4<<24);
  mtspr( 568, r1 );
  isync;
}

void _CPU_cache_invalidate_entire_instruction ( void ) {}
void _CPU_cache_freeze_instruction ( void ) {}
void _CPU_cache_unfreeze_instruction ( void ) {}

void _CPU_cache_enable_instruction ( void )
{
  uint32_t   r1;
  r1 = (0x2<<24);
  mtspr( 560, r1 );
  isync;
}

void _CPU_cache_disable_instruction ( void )
{
  uint32_t   r1;
  r1 = (0x4<<24);
  mtspr( 560, r1 );
  isync;
}

#else

#warning Most cache functions are not implemented

void _CPU_cache_flush_entire_data(void)
{
	/* Void */
}

void _CPU_cache_invalidate_entire_data(void)
{
	/* Void */
}

void _CPU_cache_freeze_data(void)
{
	/* Void */
}

void _CPU_cache_unfreeze_data(void)
{
	/* Void */
}

void _CPU_cache_enable_data(void)
{
	/* Void */
}

void _CPU_cache_disable_data(void)
{
	/* Void */
}

void _CPU_cache_invalidate_entire_instruction(void)
{
	/* Void */
}

void _CPU_cache_freeze_instruction(void)
{
	/* Void */
}

void _CPU_cache_unfreeze_instruction(void)
{
	/* Void */
}


void _CPU_cache_enable_instruction(void)
{
	/* Void */
}

void _CPU_cache_disable_instruction(void)
{
	/* Void */
}

#endif

void _CPU_cache_invalidate_1_data_line(
	const void * _address )
{
  register const void *__address = _address;
  asm volatile ( "dcbi 0,%0" :: "r"(__address) : "memory" );
}

void _CPU_cache_flush_1_data_line(
	const void * _address )
{
  register const void *__address = _address;
  asm volatile ( "dcbf 0,%0" :: "r" (__address) : "memory" );
}


void _CPU_cache_invalidate_1_instruction_line(
	const void * _address )
{
  register const void *__address = _address;
  asm volatile ( "icbi 0,%0" :: "r" (__address) : "memory");
}

/* end of file */
