/*
 *  COPYRIGHT (c) 1997-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may in
 *  the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: dumpbuf.h,v 1.5 2009/11/29 11:57:23 ralf Exp $
 */

#ifndef __DUMP_BUFFER_h
#define __DUMP_BUFFER_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Print Memory Buffer
 *
 *  This method prints @a length bytes beginning at @a buffer in
 *  a nice format similar to what one would expect from a debugger
 *  or ROM monitor.
 *
 *  @param[in] buffer is the address of the buffer
 *  @param[in] length is the length of the buffer
 */
void rtems_print_buffer(
  unsigned char *buffer,
  int            length
);

#ifdef __cplusplus
}
#endif

#endif
/* end of include file */
