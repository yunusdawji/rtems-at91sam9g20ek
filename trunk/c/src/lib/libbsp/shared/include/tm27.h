/*
 *  Empty stub for tm27.h
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: tm27.h,v 1.2 2008/10/02 21:39:45 joel Exp $
 */

#ifndef _RTEMS_TMTEST27
#error "This is an RTEMS internal file you must not include directly."
#endif

#ifndef __tm27_h
#define __tm27_h

/*
 *  Stuff for Time Test 27
 */

#define MUST_WAIT_FOR_INTERRUPT 0

void Install_tm27_vector(void (*_handler)())
{
}

#define Cause_tm27_intr()  \
  do { \
    ; \
  } while (0)


#define Clear_tm27_intr() \
  do { \
    ; \
  } while (0)

#define Lower_tm27_intr() \
  do { \
    ; \
  } while (0)

#endif
