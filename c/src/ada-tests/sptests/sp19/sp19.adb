--
--  MAIN / BODY
--
--  DESCRIPTION:
--
--  This is the entry point for Test SP19 of the Single Processor Test Suite.
--
--  DEPENDENCIES: 
--
--  
--
--  COPYRIGHT (c) 1989-1997.
--  On-Line Applications Research Corporation (OAR).
--
--  The license and distribution terms for this file may in
--  the file LICENSE in this distribution or at
--  http://www.rtems.com/license/LICENSE.
--
--  $Id: sp19.adb,v 1.8 2003/09/04 18:50:40 joel Exp $
--

with RTEMS;
with SPTEST;
with TEST_SUPPORT;

procedure SP19 is
  INIT_ID : RTEMS.ID;
  STATUS  : RTEMS.STATUS_CODES;
begin

   RTEMS.TASK_CREATE(
      RTEMS.BUILD_NAME(  'I', 'N', 'I', 'T' ),
      1,
      RTEMS.MINIMUM_STACK_SIZE,
      RTEMS.NO_PREEMPT,
      RTEMS.FLOATING_POINT,
      INIT_ID,
      STATUS
   );
   TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE OF INIT" );


   RTEMS.TASK_START(
      INIT_ID,
      SPTEST.INIT'ACCESS,
      0,
      STATUS
   );
   TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START OF INIT" );

   loop
      delay 120.0;
   end loop;

end SP19;

