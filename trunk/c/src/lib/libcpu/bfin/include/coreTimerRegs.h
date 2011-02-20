/*  Blackfin Core Timer Registers
 *
 *  Copyright (c) 2008 Kallisti Labs, Los Gatos, CA, USA
 *             written by Allan Hessenflow <allanh@kallisti.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: coreTimerRegs.h,v 1.1 2008/08/15 20:18:41 joel Exp $
 */

#ifndef _coreTimerRegs_h_
#define _coreTimerRegs_h_

/* register addresses */

#define TCNTL                                     0xffe03000
#define TPERIOD                                   0xffe03004
#define TSCALE                                    0xffe03008
#define TCOUNT                                    0xffe0300c


/* register fields */

#define TCNTL_TINT                                0x00000008
#define TCNTL_TAUTORLD                            0x00000004
#define TCNTL_TMREN                               0x00000002
#define TCNTL_TMPWR                               0x00000001

#endif /* _coreTimerRegs_h_ */

