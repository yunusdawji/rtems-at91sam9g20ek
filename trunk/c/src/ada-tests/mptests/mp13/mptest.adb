--
--  MPTEST / BODY
--
--  DESCRIPTION:
--
--  This package is the implementation for Test 13 of the RTEMS
--  Multiprocessor Test Suite.
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
--  $Id: mptest.adb,v 1.5 2007/10/01 22:58:09 joel Exp $
--

with INTERFACES; use INTERFACES;
with RTEMS;
with TEST_SUPPORT;
with TEXT_IO;
with UNSIGNED32_IO;

package body MPTEST is

--PAGE
--
--  INIT
--

   procedure INIT (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   ) is
      STATUS : RTEMS.STATUS_CODES;
   begin

      TEXT_IO.NEW_LINE( 2 );
      TEXT_IO.PUT( "*** TEST 13 -- NODE " );
      UNSIGNED32_IO.PUT(
         TEST_SUPPORT.NODE,
         WIDTH => 1
      );
      TEXT_IO.PUT_LINE( " ***" );

      MPTEST.TASK_NAME( 1 ) := RTEMS.BUILD_NAME(  '1', '1', '1', ' ' );
      MPTEST.TASK_NAME( 2 ) := RTEMS.BUILD_NAME(  '2', '2', '2', ' ' );

      MPTEST.QUEUE_NAME( 1 ) := RTEMS.BUILD_NAME(  'M', 'S', 'G', ' ' );

      MPTEST.SEMAPHORE_NAME( 1 ) := RTEMS.BUILD_NAME(  'S', 'E', 'M', ' ' );

      if TEST_SUPPORT.NODE = 1 then

         TEXT_IO.PUT_LINE( "Creating Message Queue (Global)" );
         RTEMS.MESSAGE_QUEUE_CREATE(
            MPTEST.QUEUE_NAME( 1 ),
            3,
            RTEMS.GLOBAL + RTEMS.LIMIT,
            MPTEST.QUEUE_ID( 1 ),
            STATUS
         );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "MESSAGE_QUEUE_CREATE" );

         TEXT_IO.PUT_LINE( "Creating Semaphore (Global)" );
         RTEMS.SEMAPHORE_CREATE(
            MPTEST.SEMAPHORE_NAME( 1 ),
            1,
            RTEMS.GLOBAL + RTEMS.PRIORITY,
            MPTEST.SEMAPHORE_ID( 1 ),
            STATUS
         );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "SEMAPHORE_CREATE" );

         RTEMS.SEMAPHORE_OBTAIN(
            MPTEST.SEMAPHORE_ID( 1 ),
            RTEMS.DEFAULT_OPTIONS,
            RTEMS.NO_TIMEOUT,
            STATUS
         );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "SEMAPHORE_OBTAIN" );

      end if;

      TEXT_IO.PUT_LINE( "Creating Test_task 1 (local)" );
         RTEMS.TASK_CREATE(
         MPTEST.TASK_NAME( 1 ),
         1,
         2048,
         RTEMS.TIMESLICE,
         RTEMS.DEFAULT_ATTRIBUTES,
         MPTEST.TASK_ID( 1 ),
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE" );

      TEXT_IO.PUT_LINE( "Starting Test_task 1 (local)" );
      RTEMS.TASK_START(
         MPTEST.TASK_ID( 1 ),
         MPTEST.TEST_TASK_1'ACCESS,
         0,
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START" );

      TEXT_IO.PUT_LINE( "Creating Test_task 2 (local)" );
      RTEMS.TASK_CREATE(
         MPTEST.TASK_NAME( 2 ),
         1,
         2048,
         RTEMS.TIMESLICE,
         RTEMS.DEFAULT_ATTRIBUTES,
         MPTEST.TASK_ID( 2 ),
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE" );

      TEXT_IO.PUT_LINE( "Starting Test_task 2 (local)" );
      RTEMS.TASK_START(
         MPTEST.TASK_ID( 2 ),
         MPTEST.TEST_TASK_2'ACCESS,
         0,
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START" );

      if TEST_SUPPORT.NODE = 1 then

         RTEMS.TASK_WAKE_AFTER( 5 * TEST_SUPPORT.TICKS_PER_SECOND, STATUS );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_WAKE_AFTER" );

         TEXT_IO.PUT_LINE( "*** END OF TEST 13 ***" );

         RTEMS.SHUTDOWN_EXECUTIVE( 0 );

      end if;

      TEXT_IO.PUT_LINE( "Deleting initialization task" );
      RTEMS.TASK_DELETE( RTEMS.SELF, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_DELETE OF SELF" );

   end INIT;

--PAGE
--
--  TEST_TASK_1
--

   procedure TEST_TASK_1 (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   ) is
      COUNT               : RTEMS.UNSIGNED32;
      RECEIVE_BUFFER_AREA : RTEMS.BUFFER;
      RECEIVE_BUFFER      : RTEMS.BUFFER_POINTER;
      STATUS              : RTEMS.STATUS_CODES;
   begin

      RECEIVE_BUFFER :=
         RTEMS.TO_BUFFER_POINTER( RECEIVE_BUFFER_AREA'ADDRESS );

      TEXT_IO.PUT_LINE( "Getting QID of message queue" );

      loop

         RTEMS.MESSAGE_QUEUE_IDENT(
            MPTEST.QUEUE_NAME( 1 ),
            RTEMS.SEARCH_ALL_NODES,
            MPTEST.QUEUE_ID( 1 ),
            STATUS
         );

         exit when RTEMS.IS_STATUS_SUCCESSFUL( STATUS );

      end loop;

      if TEST_SUPPORT.NODE = 1 then

         TEXT_IO.PUT_LINE( "Receiving message ..." );
         RTEMS.MESSAGE_QUEUE_RECEIVE(
            MPTEST.QUEUE_ID( 1 ),
            RECEIVE_BUFFER,
            RTEMS.DEFAULT_OPTIONS,
            RTEMS.NO_TIMEOUT,
            STATUS
         );
         TEXT_IO.PUT_LINE( "How did I get back from here???" );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "MESSAGE_QUEUE_RECEIVE" );

      end if;

      RTEMS.TASK_WAKE_AFTER( TEST_SUPPORT.TICKS_PER_SECOND, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_WAKE_AFTER" );

      TEXT_IO.PUT_LINE( "Receiving message ..." );
      RTEMS.MESSAGE_QUEUE_RECEIVE(
         MPTEST.QUEUE_ID( 1 ),
         RECEIVE_BUFFER,
         RTEMS.DEFAULT_OPTIONS,
         2 * TEST_SUPPORT.TICKS_PER_SECOND,
         STATUS
      );
      TEST_SUPPORT.FATAL_DIRECTIVE_STATUS(
         STATUS,
         RTEMS.TIMEOUT,
         "MESSAGE_QUEUE_RECEIVE"
      );
      TEST_SUPPORT.FATAL_DIRECTIVE_STATUS(
         STATUS,
         RTEMS.TIMEOUT,
         "MESSAGE_QUEUE_OBTAIN"
      );

      TEXT_IO.PUT_LINE(
         "message_queue_receive correctly returned TIMEOUT"
      );

      TEXT_IO.PUT_LINE( "Deleting self" );
      RTEMS.TASK_DELETE( RTEMS.SELF, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_DELETE OF SELF" );

   end TEST_TASK_1;

--PAGE
--
--  TEST_TASK_2
--

   procedure TEST_TASK_2 (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   ) is
      STATUS : RTEMS.STATUS_CODES;
   begin

      TEXT_IO.PUT_LINE( "Getting SMID of semaphore" );

      loop

         RTEMS.SEMAPHORE_IDENT(
            MPTEST.SEMAPHORE_NAME( 1 ),
            RTEMS.SEARCH_ALL_NODES,
            MPTEST.SEMAPHORE_ID( 1 ),
            STATUS
         );

         exit when RTEMS.IS_STATUS_SUCCESSFUL( STATUS );

      end loop;

      if TEST_SUPPORT.NODE = 1 then

         RTEMS.TASK_WAKE_AFTER( TEST_SUPPORT.TICKS_PER_SECOND, STATUS );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_WAKE_AFTER" );

         TEXT_IO.PUT_LINE( "Releasing semaphore ..." );
         RTEMS.SEMAPHORE_RELEASE( MPTEST.SEMAPHORE_ID( 1 ), STATUS );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "SEMAPHORE_RELEASE" );

         RTEMS.TASK_WAKE_AFTER( TEST_SUPPORT.TICKS_PER_SECOND / 2, STATUS );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_WAKE_AFTER" );

         TEXT_IO.PUT_LINE( "Getting semaphore ..." );
         RTEMS.SEMAPHORE_OBTAIN(
            MPTEST.SEMAPHORE_ID( 1 ),
            RTEMS.DEFAULT_OPTIONS,
            RTEMS.NO_TIMEOUT,
            STATUS
         );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "SEMAPHORE_OBTAIN" );

         TEXT_IO.PUT_LINE( "Getting semaphore ..." );
         RTEMS.SEMAPHORE_OBTAIN(
            MPTEST.SEMAPHORE_ID( 1 ),
            RTEMS.DEFAULT_OPTIONS,
            RTEMS.NO_TIMEOUT,
            STATUS
         );
         TEXT_IO.PUT_LINE( "How did I get back from here???" );
         TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "SEMAPHORE_OBTAIN" );

      end if;

      RTEMS.TASK_WAKE_AFTER( TEST_SUPPORT.TICKS_PER_SECOND / 2, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_WAKE_AFTER" );

      TEXT_IO.PUT_LINE( "Getting semaphore ..." );
      RTEMS.SEMAPHORE_OBTAIN(
         MPTEST.SEMAPHORE_ID( 1 ),
         RTEMS.DEFAULT_OPTIONS,
         RTEMS.NO_TIMEOUT,
         STATUS
      );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "SEMAPHORE_OBTAIN" );

      TEXT_IO.PUT_LINE( "Releasing semaphore ..." );
      RTEMS.SEMAPHORE_RELEASE( MPTEST.SEMAPHORE_ID( 1 ), STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "SEMAPHORE_RELEASE" );

      RTEMS.TASK_WAKE_AFTER( TEST_SUPPORT.TICKS_PER_SECOND, STATUS );
      TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_WAKE_AFTER" );

      TEXT_IO.PUT_LINE( "Getting semaphore ..." );
      RTEMS.SEMAPHORE_OBTAIN(
         MPTEST.SEMAPHORE_ID( 1 ),
         RTEMS.DEFAULT_OPTIONS,
         2 * TEST_SUPPORT.TICKS_PER_SECOND,
         STATUS
      );
      TEST_SUPPORT.FATAL_DIRECTIVE_STATUS(
         STATUS,
         RTEMS.TIMEOUT,
         "SEMAPHORE_OBTAIN"
      );
      TEXT_IO.PUT_LINE( "semaphore_obtain correctly returned TIMEOUT" );

      TEXT_IO.PUT_LINE( "*** END OF TEST 13 ***" );

      RTEMS.SHUTDOWN_EXECUTIVE( 0 );

   end TEST_TASK_2;

end MPTEST;
