--
--  SPTEST / SPECIFICATION
--
--  DESCRIPTION:
--
--  This package is the specification for Test 15 of the RTEMS
--  Single Processor Test Suite.
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
--  $Id: sptest.ads,v 1.7 2008/03/11 20:12:52 joel Exp $
--

with RTEMS;

package SPTEST is

--
--  These arrays contain the IDs and NAMEs of all RTEMS tasks created
--  by this test.
--

   TASK_ID   : array ( RTEMS.UNSIGNED32 range 1 .. 3 ) of RTEMS.ID;
   TASK_NAME : array ( RTEMS.UNSIGNED32 range 1 .. 3 ) of RTEMS.NAME;

--
--  These arrays contain the IDs and NAMEs of all RTEMS partitions created
--  by this test.
--

   PARTITION_ID   : array ( RTEMS.UNSIGNED32 range 1 .. 3 ) of RTEMS.ID;
   PARTITION_NAME : array ( RTEMS.UNSIGNED32 range 1 .. 3 ) of RTEMS.NAME;

--
--  These arrays define the memory areas used for the partitions in
--  this test.
--

   AREA_1 : array ( RTEMS.UNSIGNED32 range 0 .. 4095 ) of RTEMS.UNSIGNED8;
   for AREA_1'ALIGNMENT use RTEMS.STRUCTURE_ALIGNMENT;

   AREA_2 : array ( RTEMS.UNSIGNED32 range 0 ..  273 ) of RTEMS.UNSIGNED8;
   for AREA_2'ALIGNMENT use RTEMS.STRUCTURE_ALIGNMENT;


--
--  INIT
--
--  DESCRIPTION:
--
--  This RTEMS task initializes the application.
--

   procedure INIT (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   );
   pragma Convention (C, INIT);

--
--  PUT_ADDRESS_FROM_AREA_1
--
--  DESCRIPTION:
--
--  This subpgram prints the offset of the address TO_BE_PRINTED 
--  from the first byte of AREA_1.
--
--  NOTE:
--
--  This subprogram is used because the actual address of AREA_1
--  varies based upon the size of the executable, the target board,
--  and the target processor.
--

   procedure PUT_ADDRESS_FROM_AREA_1 (
      TO_BE_PRINTED : in     RTEMS.ADDRESS
   );

--
--  PUT_ADDRESS_FROM_AREA_2
--
--  DESCRIPTION:
--
--  This subprogram prints the offset of the address TO_BE_PRINTED 
--  from the first byte of AREA_2.
--
--  NOTE:
--
--  This subprogram is used because the actual address of AREA_1
--  varies based upon the size of the executable, the target board,
--  and the target processor.
--

   procedure PUT_ADDRESS_FROM_AREA_2 (
      TO_BE_PRINTED : in     RTEMS.ADDRESS
   );

--
--  TASK_1
--
--  DESCRIPTION:
--
--  This RTEMS task tests the Partition Manager.
--

   procedure TASK_1 (
      ARGUMENT : in     RTEMS.TASK_ARGUMENT
   );
   pragma Convention (C, TASK_1);

end SPTEST;
