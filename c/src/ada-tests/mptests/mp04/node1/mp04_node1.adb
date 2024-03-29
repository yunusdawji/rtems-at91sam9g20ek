--
--  MAIN / BODY
--
--  DESCRIPTION:
--
--  This is the entry point for Test MP04_NODE1 of the Multiprocessor
--  Test Suite.
--
--  DEPENDENCIES: 
--
--  
--
--  COPYRIGHT (c) 1989-2007.
--  On-Line Applications Research Corporation (OAR).
--
--  The license and distribution terms for this file may in
--  the file LICENSE in this distribution or at
--  http://www.rtems.com/license/LICENSE.
--
--  $Id: mp04_node1.adb,v 1.2 2009/12/14 21:28:53 joel Exp $
--

with RTEMS;
with MPTEST;
with TEST_SUPPORT;

procedure MP04_NODE1 is
  INIT_ID : RTEMS.ID;
  STATUS  : RTEMS.STATUS_CODES;
begin

   RTEMS.TASK_CREATE(
      RTEMS.BUILD_NAME(  'I', 'N', 'I', 'T' ),
      1,
      RTEMS.MINIMUM_STACK_SIZE,
      RTEMS.NO_PREEMPT,
      RTEMS.DEFAULT_ATTRIBUTES,
      INIT_ID,
      STATUS
   );
   TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE OF INIT" );


   RTEMS.TASK_START(
      INIT_ID,
      MPTEST.INIT'ACCESS,
      0,
      STATUS
   );
   TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START OF INIT" );

   loop
      delay 120.0;
   end loop;

end MP04_NODE1;

