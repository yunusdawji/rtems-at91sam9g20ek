/*
 *  Copyright (c) 2004,2005 Ralf Corsepius, Ulm, Germany.
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: concat.h,v 1.3 2005/10/27 07:23:53 ralf Exp $
 */

#ifndef _RTEMS_CONCAT_H
#define _RTEMS_CONCAT_H

/* ANSI concatenation macros.  */

#define CONCAT1(a, b) CONCAT2(a, b)
#define CONCAT2(a, b) a ## b

#define EXPAND0(x) x
#define CONCAT0(a,b) EXPAND0(a)EXPAND0(b)

#endif
