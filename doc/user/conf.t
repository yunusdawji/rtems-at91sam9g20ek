@c  COPYRIGHT (c) 1988-2008.
@c  On-Line Applications Research Corporation (OAR).
@c  All rights reserved.
@c
@c  $Id: conf.t,v 1.64 2010/03/04 14:40:06 joel Exp $
@c

@c The following macros from confdefs.h have not been discussed in this
@c chapter:
@c 
@c CONFIGURE_NEWLIB_EXTENSION - probably not needed
@c 
@c In addition, there should be examples of defining your own
@c Device Driver Table, Init task table, etc.
@c
@c Regardless, this is a big step up. :)
@c 

@chapter Configuring a System

@section Introduction

RTEMS must be configured for an application.  This configuration
information encompasses a variety of information including 
the length of each clock tick, the maximum number of each RTEMS
object that can be created, the application initialization tasks,
and the device drivers in the application.  This information
is placed in data structures that are given to RTEMS at
system initialization time.  This chapter details the 
format of these data structures as well as a simpler
mechanism to automate the generation of these structures.

@ifset is-Ada
System configuration is ALWAYS done from C.  When developing
an Ada application, the user is responsible for creating at
least one C file which contains the Ada run-time initialization
and the RTEMS System Configuration.  There is no Ada binding
for RTEMS System Configuration information.  Thus all examples
and data structures shown in this chapter are in C.
@end ifset

@section Automatic Generation of System Configuration

@cindex confdefs.h
@findex confdefs.h

RTEMS provides the @code{rtems/confdefs.h} C language header file that
based on the setting of a variety of macros can automatically
produce nearly all of the configuration tables required
by an RTEMS application.  Rather than building the individual
tables by hand, the application simply specifies the values
for the configuration parameters it wishes to set.  In the following
example, the configuration information for a simple system with
a message queue and a time slice of 50 milliseconds is configured:

@example
@group
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MICROSECONDS_PER_TICK   1000 /* 1 millisecond */
#define CONFIGURE_TICKS_PER_TIMESLICE       50 /* 50 milliseconds */

#define CONFIGURE_MAXIMUM_TASKS 4
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
@end group
@end example

This system will begin execution with the single initialization task
named @code{Init}.  It will be configured to have both a console
device driver (for standard I/O) and a clock tick device driver.

For each configuration parameter in the configuration tables, the
macro corresponding to that field is discussed.  Most systems
can be easily configured using the @code{rtems/confdefs.h} mechanism.

The @code{CONFIGURE_INIT} constant must be defined in order to
make @code{rtems/confdefs.h} instantiate the configuration data
structures.  This can only be defined in one source file per
application that includes @code{rtems/confdefs.h} or the symbol
table will be instantiated multiple times and linking errors
produced.

The user should be aware that the defaults are intentionally
set as low as possible.  By default, no application resources
are configured.  The @code{rtems/confdefs.h} file ensures that
at least one application tasks or thread is configured
and that at least one of the initialization task/thread
tables is configured.

The @code{rtems/confdefs.h} file estimates the amount of 
memory required for the RTEMS Executive Workspace.  This
estimate is only as accurate as the information given
to @code{rtems/confdefs.h} and may be either too high or too
low for a variety of reasons.  Some of the reasons that
@code{rtems/confdefs.h} may reserve too much memory for RTEMS
are:

@itemize @bullet
@item All tasks/threads are assumed to be floating point.
@end itemize

Conversely, there are many more reasons, the resource
estimate could be too low:

@itemize @bullet
@item Task/thread stacks greater than minimum size must be
accounted for explicitly by developer.

@item Memory for messages is not included.

@item Device driver requirements are not included.


@item Network stack requirements are not included.

@item Requirements for add-on libraries are not included.
@end itemize

In general, @code{rtems/confdefs.h} is very accurate when given
enough information.  However, it is quite easy to use
a library and not account for its resources.

The following subsection list all of the constants which can be
set by the user.

@subsection Library Support Definitions

This section defines the file system and IO library
related configuration parameters supported by
@code{rtems/confdefs.h}.

@itemize @bullet
@findex CONFIGURE_MALLOC_STATISTICS
@item @code{CONFIGURE_MALLOC_STATISTICS} is defined when the application
wishes to enable the gathering of more detailed statistics on the
C Malloc Family of routines.

@findex CONFIGURE_MALLOC_BSP_SUPPORTS_SBRK
@item @code{CONFIGURE_MALLOC_BSP_SUPPORTS_SBRK} is defined by a BSP
to indicate that it does not allocate all available memory to the
C Program Heap used by the Malloc Family of routines.  If defined,
when @code{malloc()} is unable to allocate memory, it will call
the BSP supplied @code{sbrk()} to obtain more memory.

@findex CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS
@item @code{CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS} is set to the
maximum number of files that can be concurrently open.  Libio requires
a Classic RTEMS semaphore for each file descriptor as well as one 
global one.  The default value is 3 file descriptors which is
enough to support standard input, output, and error output.

@findex CONFIGURE_TERMIOS_DISABLED
@item @code{CONFIGURE_TERMIOS_DISABLED} is defined if the
software implementing POSIX termios functionality is
not going to be used by this application.  By default, this
is not defined and resources are reserved for the
termios functionality.

@findex CONFIGURE_NUMBER_OF_TERMIOS_PORTS
@item @code{CONFIGURE_NUMBER_OF_TERMIOS_PORTS} is set to the
number of ports using the termios functionality.  Each 
concurrently active termios port requires resources.
By default, this is set to 1 so a console port can be
used.

@findex CONFIGURE_HAS_OWN_MOUNT_TABLE
@item @code{CONFIGURE_HAS_OWN_MOUNT_TABLE} is defined when the
application provides their own filesystem mount table.  The
mount table is an array of @code{rtems_filesystem_mount_table_t}
entries pointed to by the global variable
@code{rtems_filesystem_mount_table}.  The number of
entries in this table is in an integer variable named
@code{rtems_filesystem_mount_table_t}.

@findex CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM
@item @code{CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM} is defined
if the application wishes to use the full functionality
IMFS.  By default, the miniIMFS is used.  The miniIMFS
is a minimal functionality subset of the In-Memory
FileSystem (IMFS).  The miniIMFS is comparable
in functionality to the pseudo-filesystem name space provided 
before RTEMS release 4.5.0.  The miniIMFS supports
only directories and device nodes and is smaller in executable
code size than the full IMFS.

@findex CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM
@item @code{CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM} is defined
if the application wishes to use the device-only filesytem. The 
device-only filesystem supports only device nodes and is smaller 
in executable code size than the full IMFS and miniIMFS.

@findex CONFIGURE_APPLICATION_DISABLE_FILESYSTEM
@item @code{CONFIGURE_APPLICATION_DISABLE_FILESYSTEM} is defined
if the application dose not intend to use any kind of filesystem
supports(including printf family). 


@findex CONFIGURE_STACK_CHECKER_ENABLED
@item @code{CONFIGURED_STACK_CHECKER_ENABLED} is defined when
the application wishes to enable run-time stack bounds checking.
This increases the time required to create tasks as well as adding
overhead to each context switch.  By default, this is not defined and
thus stack checking is disabled.  NOTE: In 4.9 and older, this was named
@code{STACK_CHECKER_ON}

@end itemize

@subsection Basic System Information

This section defines the general system configuration parameters supported by
@code{rtems/confdefs.h}.

@itemize @bullet
@findex CONFIGURE_HAS_OWN_CONFIGURATION_TABLE
@item @code{CONFIGURE_HAS_OWN_CONFIGURATION_TABLE} should only be defined
if the application is providing their own complete set of configuration 
tables.

@findex CONFIGURE_EXECUTIVE_RAM_WORK_AREA
@item @code{CONFIGURE_EXECUTIVE_RAM_WORK_AREA} is the base 
address of the RTEMS RAM Workspace.  By default, this value
is NULL indicating that the BSP is to determine the location
of the RTEMS RAM Workspace.

@findex CONFIGURE_UNIFIED_WORK_AREAS
@item @code{CONFIGURE_UNIFIED_WORK_AREAS} configures RTEMS to use a
single memory pool for the RTEMS Workspace and C Program Heap.  If not
defined, there will be separate memory pools for the RTEMS Workspace and
C Program Heap.  Having separate pools does have some advantages in the
event a task blows a stack or writes outside its memory area. However,
in low memory systems the overhead of the two pools plus the potential
for unused memory in either pool is very undesirable.

In high memory environments, this is desirable when you want to use the
RTEMS "unlimited" objects option.  You will be able to create objects
until you run out of all available memory rather then just until you
run out of RTEMS Workspace.

@item @code{CONFIGURE_MICROSECONDS_PER_TICK} is the length
of time between clock ticks.  By default, this is set to
10000 microseconds.

@findex CONFIGURE_TICKS_PER_TIMESLICE
@item @code{CONFIGURE_TICKS_PER_TIMESLICE} is the length
of the timeslice quantum in ticks for each task.  By
default, this is 50.

@findex CONFIGURE_MAXIMUM_PRIORITY
@item @code{CONFIGURE_MAXIMUM_PRIORITY} is the maximum numeric priority
of any task in the system and one less that the number of priority levels
in the system.  The numerically greatest priority is the logically lowest
priority in the system and will thus be used by the IDLE task.  Valid values
for this configuration parameter must be one (1) less than than a power
of two (2) between 4 and 256 inclusively.  In other words, valid values
are 3, 7, 31, 63, 127, and 255.  Reducing the number of priorities in the
system reduces the amount of memory allocated from the RTEMS Workspace.
By default, RTEMS supports 256 priority levels ranging from 0 to 255 so
the default value for this field is 255.

@findex CONFIGURE_MICROSECONDS_PER_TICK
@fnindex CONFIGURE_MINIMUM_STACK_SIZE
@item @code{CONFIGURE_MINIMUM_STACK_SIZE} is set to the number of bytes
the application wants the minimum stack size to be for every task or 
thread in the system.  By default, this is set to the recommended minimum
stack size for this processor.

@fnindex CONFIGURE_INTERRUPT_STACK_SIZE
@item @code{CONFIGURE_INTERRUPT_STACK_SIZE} is set to the 
size of the interrupt stack.  The interrupt stack size is
usually set by the BSP but since this memory may be allocated
from the RTEMS Ram Workspace, it must be accounted for.  The
default for this field is the configured minimum stack size.  [NOTE:
In some BSPs, changing this constant does NOT change the
size of the interrupt stack, only the amount of memory
reserved for it.] If not specified, the interrupt stack
will be of minimum size.  The default value is the configured
minimum stack size.

@findex CONFIGURE_TASK_STACK_ALLOCATOR
@item @code{CONFIGURE_TASK_STACK_ALLOCATOR}
may point to a user provided routine to allocate task stacks.
The default value for this field is NULL which indicates that
task stacks will be allocated from the RTEMS Workspace.

@findex CONFIGURE_TASK_STACK_DEALLOCATOR
@item @code{CONFIGURE_TASK_STACK_DEALLOCATOR}
may point to a user provided routine to free task stacks.
The default value for this field is NULL which indicates that
task stacks will be allocated from the RTEMS Workspace.

@findex CONFIGURE_ZERO_WORKSPACE_AUTOMATICALLY
@item @code{CONFIGURE_ZERO_WORKSPACE_AUTOMATICALLY}
indicates whether RTEMS should zero the RTEMS Workspace and
C Program Heap as part of its initialization.  If set to
TRUE, the Workspace is zeroed.  Otherwise, it is not.
Unless overridden by the BSP, the default value for this
field is FALSE.

@findex CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE
@item @code{CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE} is a helper macro
which is used to assist in computing the total amount of memory
required for message buffers.  Each message queue will have its
own configuration with maximum message size and maximum number of
pending messages.  The interface for this macro is as follows:

@example
CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE(max_messages, size_per)
@end example

Where @code{max_messages} is the maximum number of pending messages
and @code{size_per} is the size in bytes of the user message.

@findex CONFIGURE_MESSAGE_BUFFER_MEMORY
@item @code{CONFIGURE_MESSAGE_BUFFER_MEMORY} is set to the number of
bytes the application requires to be reserved for pending message queue
buffers.  This value should include memory for all buffers across
all APIs.  The default value is 0. 

The following illustrates how the help macro
@code{CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE} can be used to assist in
calculating the message buffer memory required.  In this example, there
are two message queues used in this application.  The first message
queue has maximum of 24 pending messages with the message structure
defined by the type @code{one_message_type}.  The other message queue
has maximum of 500 pending messages with the message structure defined
by the type @code{other_message_type}.

@example

#define CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE \
 (CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE( \
    24, sizeof(one_message_type) + \
  CONFIGURE_MESSAGE_BUFFERS_FOR_QUEUE( \
    500, sizeof(other_message_type) \
 )
@end example

@findex CONFIGURE_MEMORY_OVERHEAD
@item @code{CONFIGURE_MEMORY_OVERHEAD} is set to the number of
kilobytes the application wishes to add to the requirements calculated
by @code{rtems/confdefs.h}.  The default value is 0.

@findex CONFIGURE_EXTRA_TASK_STACKS
@item @code{CONFIGURE_EXTRA_TASK_STACKS} is set to the number of
bytes the applications wishes to add to the task stack requirements
calculated by @code{rtems/confdefs.h}.  This parameter is very important.
If the application creates tasks with stacks larger then the 
minimum, then that memory is NOT accounted for by @code{rtems/confdefs.h}.
The default value is 0.

@end itemize

NOTE: The required size of the Executive RAM Work Area is calculated
automatically when using the @code{rtems/confdefs.h} mechanism.

@c
@c
@c
@subsection Idle Task Configuration

This section defines the IDLE task related configuration parameters
supported by @code{rtems/confdefs.h}.

@itemize @bullet

@fnindex CONFIGURE_IDLE_TASK_BODY
@item @code{CONFIGURE_IDLE_TASK_BODY} is set to the method name
corresponding to the application specific IDLE thread body.  If
not specified, the BSP or RTEMS default IDLE thread body will
be used.  The default value is NULL.

@fnindex CONFIGURE_IDLE_TASK_STACK_SIZE
@item @code{CONFIGURE_IDLE_TASK_STACK_SIZE} is set to the 
desired stack size for the IDLE task.  If not specified,
the IDLE task will have a stack of minimum size.  The default
value is the configured minimum stack size.

@fnindex CONFIGURE_IDLE_TASK_INITIALIZES_APPLICATION
@item @code{CONFIGURE_IDLE_TASK_INITIALIZES_APPLICATION} is set to
indicate that the user has configured @b{NO} user initialization tasks
or threads and that the user provided IDLE task will perform application
initialization and then transform itself into an IDLE task.  If you
use this option be careful, the user IDLE task @b{CANNOT} block at
all during the initialization sequence.  Further, once application
initialization is complete, it must make itself preemptible and 
enter an IDLE body loop.  By default, this is not the mode of operation
and the user is assumed to provide one or more initialization tasks.

@end itemize

@c
@c
@c
@subsection Device Driver Table

This section defines the configuration parameters related
to the automatic generation of a Device Driver Table.  As
@code{rtems/confdefs.h} only is aware of a small set of 
standard device drivers, the generated Device Driver
Table is suitable for simple applications with no
custom device drivers.

@itemize @bullet
@findex CONFIGURE_HAS_OWN_DEVICE_DRIVER_TABLE
@item @code{CONFIGURE_HAS_OWN_DEVICE_DRIVER_TABLE} is defined if
the application wishes to provide their own Device Driver Table.
The table generated is an array of @code{rtems_driver_address_table}
entries named @code{Device_drivers}.  By default, this is not
defined indicating the @code{rtems/confdefs.h} is providing the
device driver table.

@findex CONFIGURE_MAXIMUM_DRIVERS
@item @code{CONFIGURE_MAXIMUM_DRIVERS} is defined
as the number of device drivers per node.  By default, this is 
set to 10.

@findex CONFIGURE_MAXIMUM_DEVICES
@item @code{CONFIGURE_MAXIMUM_DEVICES} is defined
to the number of individual devices that may be registered
in the system.  By default, this is set to 4.

@findex CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
@item @code{CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER}
is defined
if the application wishes to include the Console Device Driver.
This device driver is responsible for providing standard input
and output using "/dev/console".  By default, this is not
defined.

@findex CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER
@item @code{CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER}
is defined
if the application wishes to include the Clock Device Driver.
This device driver is responsible for providing a regular
interrupt which invokes the @code{rtems_clock_tick} directive.
By default, this is not defined.

@findex CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER
@item @code{CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER}
is defined if the application wishes to include the Timer Driver.
This device driver is used to benchmark execution times
by the RTEMS Timing Test Suites.  By default, this is not
defined.

@findex CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
@item @code{CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER} is defined
when the application does @b{NOT} want the Clock Device Driver
and is @b{NOT} using the Timer Driver.  The inclusion or
exclusion of the Clock Driver must be explicit in typical
user applications.  This is intended to prevent the common
user error of using the Hello World example as the baseline
for an application and leaving out a clock tick source.

@findex CONFIGURE_APPLICATION_NEEDS_RTC_DRIVER
@item @code{CONFIGURE_APPLICATION_NEEDS_RTC_DRIVER}
is defined if the application wishes to include the Real-Time Clock Driver.
By default, this is not defined.

@findex CONFIGURE_APPLICATION_NEEDS_WATCHDOG_DRIVER
@item @code{CONFIGURE_APPLICATION_NEEDS_WATCHDOG_DRIVER}
is defined if the application wishes to include the Watchdog Driver.
By default, this is not defined.

@findex CONFIGURE_APPLICATION_NEEDS_FRAME_BUFFER_DRIVER
@item @code{CONFIGURE_APPLICATION_NEEDS_FRAME_BUFFER_DRIVER}
is defined
if the application wishes to include the BSP's Frame Buffer Device Driver.
Most BSPs do not provide a Frame Buffer Device Driver.  If this is
defined and the BSP does not have this device driver, then the user
will get a link time error for an undefined symbol.
By default, this is not defined.

@findex CONFIGURE_APPLICATION_NEEDS_STUB_DRIVER
@item @code{CONFIGURE_APPLICATION_NEEDS_STUB_DRIVER}
is defined if the application wishes to include the Stub Device Driver.
This device driver simply provides entry points that return
successful and is primarily a test fixture.
By default, this is not defined.

@findex CONFIGURE_BSP_PREREQUISITE_DRIVERS
@item @code{CONFIGURE_BSP_PREREQUISITE_DRIVERS} is defined if the
BSP has device drivers it needs to include in the Device Driver
Table.  This should be defined to the set of device driver entries that
will be placed in the table at the @b{FRONT} of the Device Driver Table
and initialized before any other drivers @b{INCLUDING} any application
prerequisite drivers.  By default,this is not defined.

@findex CONFIGURE_APPLICATION_PREREQUISITE_DRIVERS
@item @code{CONFIGURE_APPLICATION_PREREQUISITE_DRIVERS} is defined if the
application has device drivers it needs to include in the Device Driver
Table.  This should be defined to the set of device driver entries that
will be placed in the table at the @b{FRONT} of the Device Driver Table
and initialized before any other drivers @b{EXCEPT} any BSP prerequisite
drivers.  By default,this is not defined.

@findex CONFIGURE_APPLICATION_EXTRA_DRIVERS
@item @code{CONFIGURE_APPLICATION_EXTRA_DRIVERS} is defined if the
application has device drivers it needs to include in the Device Driver
Table.  This should be defined to the set of device driver entries that
will be placed in the table at the @b{END} of the Device Driver Table.
By default,this is not defined.

@end itemize

@subsection Multiprocessing Configuration

This section defines the multiprocessing related
system configuration parameters supported by @code{rtems/confdefs.h}.
This class of Configuration Constants are only applicable if
@code{CONFIGURE_MP_APPLICATION} is defined.

@itemize @bullet
@findex CONFIGURE_HAS_OWN_MULTIPROCESSING_TABLE
@item @code{CONFIGURE_HAS_OWN_MULTIPROCESSING_TABLE} is defined
if the application wishes to provide their own Multiprocessing
Configuration Table.  The generated table is named
@code{Multiprocessing_configuration}.  By default, this
is not defined.

@findex CONFIGURE_MP_NODE_NUMBER
@item @code{CONFIGURE_MP_NODE_NUMBER} is the node number of
this node in a multiprocessor system.  The default node number
is @code{NODE_NUMBER} which is set directly in RTEMS test Makefiles.

@findex CONFIGURE_MP_MAXIMUM_NODES
@item @code{CONFIGURE_MP_MAXIMUM_NODES} is the maximum number
of nodes in a multiprocessor system.  The default is 2.

@findex CONFIGURE_MP_MAXIMUM_GLOBAL_OBJECTS
@item @code{CONFIGURE_MP_MAXIMUM_GLOBAL_OBJECTS}
is the maximum number
of concurrently active global objects in a multiprocessor
system.  The default is 32.

@findex CONFIGURE_MP_MAXIMUM_PROXIES
@item @code{CONFIGURE_MP_MAXIMUM_PROXIES} is the maximum number
of concurrently active thread/task proxies in a multiprocessor
system.  The default is 32.

@findex CONFIGURE_MP_MPCI_TABLE_POINTER
@item @code{CONFIGURE_MP_MPCI_TABLE_POINTER} is the pointer
to the MPCI Configuration Table.  The default value of
this field is @code{&MPCI_table}.
@end itemize

@subsection Classic API Configuration

This section defines the Classic API related
system configuration parameters supported by @code{rtems/confdefs.h}.

@itemize @bullet
@findex CONFIGURE_MAXIMUM_TASKS
@item @code{CONFIGURE_MAXIMUM_TASKS} is the maximum number of
Classic API tasks that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_DISABLE_CLASSIC_API_NOTEPADS
@item @code{CONFIGURE_DISABLE_CLASSIC_API_NOTEPADS} should be defined
if the user does not want to have support for Classic API Notepads
in their application.  By default, this is not defined and Classic API
Notepads are supported.

@findex CONFIGURE_MAXIMUM_TIMERS
@item @code{CONFIGURE_MAXIMUM_TIMERS} is the maximum number of
Classic API timers that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_MAXIMUM_SEMAPHORES
@item @code{CONFIGURE_MAXIMUM_SEMAPHORES} is the maximum number of
Classic API semaphores that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_MAXIMUM_MESSAGE_QUEUES
@item @code{CONFIGURE_MAXIMUM_MESSAGE_QUEUES} is the maximum number of
Classic API message queues that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_MAXIMUM_PARTITIONS
@item @code{CONFIGURE_MAXIMUM_PARTITIONS} is the maximum number of
Classic API partitions that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_MAXIMUM_REGIONS
@item @code{CONFIGURE_MAXIMUM_REGIONS} is the maximum number of
Classic API regions that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_MAXIMUM_PORTS
@item @code{CONFIGURE_MAXIMUM_PORTS} is the maximum number of
Classic API ports that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_MAXIMUM_PERIODS
@item @code{CONFIGURE_MAXIMUM_PERIODS} is the maximum number of
Classic API rate monotonic periods that can be concurrently active. 
The default for this field is 0.

@findex CONFIGURE_MAXIMUM_USER_EXTENSIONS
@item @code{CONFIGURE_MAXIMUM_USER_EXTENSIONS} is the maximum number of
Classic API user extensions that can be concurrently active. 
The default for this field is 0.

@end itemize

@subsection Classic API Initialization Tasks Table Configuration

The @code{rtems/confdefs.h} configuration system can automatically
generate an Initialization Tasks Table named 
@code{Initialization_tasks} with a single entry.  The following
parameters control the generation of that table.

@itemize @bullet
@findex CONFIGURE_RTEMS_INIT_TASKS_TABLE
@item @code{CONFIGURE_RTEMS_INIT_TASKS_TABLE} is defined
if the user wishes to use a Classic RTEMS API Initialization
Task Table.  The application may choose to use the initialization
tasks or threads table from another API.  By default, this
field is not defined as the user MUST select their own
API for initialization tasks.

@findex CONFIGURE_HAS_OWN_INIT_TASK_TABLE
@item @code{CONFIGURE_HAS_OWN_INIT_TASK_TABLE} is defined
if the user wishes to define their own Classic API Initialization
Tasks Table.  This table should be named @code{Initialization_tasks}.
By default, this is not defined.

@findex CONFIGURE_INIT_TASK_NAME
@item @code{CONFIGURE_INIT_TASK_NAME} is the name
of the single initialization task defined by the
Classic API Initialization Tasks Table.  By default
the value is @code{rtems_build_name( 'U', 'I', '1', ' ' )}.

@findex CONFIGURE_INIT_TASK_STACK_SIZE
@item @code{CONFIGURE_INIT_TASK_STACK_SIZE}
is the stack size
of the single initialization task defined by the
Classic API Initialization Tasks Table.  By default
value is the configured minimum stack size.

@findex CONFIGURE_INIT_TASK_PRIORITY
@item @code{CONFIGURE_INIT_TASK_PRIORITY}
is the initial priority
of the single initialization task defined by the
Classic API Initialization Tasks Table.  By default
the value is 1 which is the highest priority
in the Classic API.

@findex CONFIGURE_INIT_TASK_ATTRIBUTES
@item @code{CONFIGURE_INIT_TASK_ATTRIBUTES}
is the task attributes
of the single initialization task defined by the
Classic API Initialization Tasks Table.  By default
the value is @code{RTEMS_DEFAULT_ATTRIBUTES}.

@findex CONFIGURE_INIT_TASK_ENTRY_POINT
@item @code{CONFIGURE_INIT_TASK_ENTRY_POINT}
is the entry point (a.k.a. function name)
of the single initialization task defined by the
Classic API Initialization Tasks Table.  By default
the value is @code{Init}.

@findex CONFIGURE_INIT_TASK_INITIAL_MODES
@item @code{CONFIGURE_INIT_TASK_INITIAL_MODES}
is the initial execution mode
of the single initialization task defined by the
Classic API Initialization Tasks Table.  By default
the value is @code{RTEMS_NO_PREEMPT}.

@findex CONFIGURE_INIT_TASK_ARGUMENTS
@item @code{CONFIGURE_INIT_TASK_ARGUMENTS}
is the task argument
of the single initialization task defined by the
Classic API Initialization Tasks Table.  By default
the value is 0.

@end itemize


@subsection POSIX API Configuration

The parameters in this section are used to configure resources
for the RTEMS POSIX API.  They are only relevant if the POSIX API
is enabled at configure time using the @code{--enable-posix} option.

@itemize @bullet
@findex CONFIGURE_MAXIMUM_POSIX_THREADS
@item @code{CONFIGURE_MAXIMUM_POSIX_THREADS} is the maximum number of
POSIX API threads that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_POSIX_MUTEXES
@item @code{CONFIGURE_MAXIMUM_POSIX_MUTEXES} is the maximum number of
POSIX API mutexes that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES
@item @code{CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES} is the maximum number of
POSIX API condition variables that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_POSIX_KEYS
@item @code{CONFIGURE_MAXIMUM_POSIX_KEYS} is the maximum number of
POSIX API keys that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_POSIX_TIMERS
@item @code{CONFIGURE_MAXIMUM_POSIX_TIMERS} is the maximum number of
POSIX API timers that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_POSIX_QUEUED_SIGNALS
@item @code{CONFIGURE_MAXIMUM_POSIX_QUEUED_SIGNALS} is the maximum number of
POSIX API queued signals that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES
@item @code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES} is the maximum number of
POSIX API message queues that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_POSIX_SEMAPHORES
@item @code{CONFIGURE_MAXIMUM_POSIX_SEMAPHORES} is the maximum number of
POSIX API semaphores that can be concurrently active.
The default is 0.

@end itemize

@subsection POSIX Initialization Threads Table Configuration

The @code{rtems/confdefs.h} configuration system can automatically
generate a POSIX Initialization Threads Table named 
@code{POSIX_Initialization_threads} with a single entry.  The following
parameters control the generation of that table.

@itemize @bullet
@findex CONFIGURE_POSIX_INIT_THREAD_TABLE
@item @code{CONFIGURE_POSIX_INIT_THREAD_TABLE}
is defined
if the user wishes to use a POSIX API Initialization
Threads Table.  The application may choose to use the initialization
tasks or threads table from another API.  By default, this
field is not defined as the user MUST select their own
API for initialization tasks.

@findex CONFIGURE_POSIX_HAS_OWN_INIT_THREAD_TABLE
@item @code{CONFIGURE_POSIX_HAS_OWN_INIT_THREAD_TABLE}
is defined if the user wishes to define their own POSIX API Initialization
Threads Table.  This table should be named @code{POSIX_Initialization_threads}.
By default, this is not defined.

@findex CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT
@item @code{CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT}
is the entry point (a.k.a. function name)
of the single initialization thread defined by the
POSIX API Initialization Threads Table.  By default
the value is @code{POSIX_Init}.

@findex CONFIGURE_POSIX_INIT_THREAD_STACK_SIZE
@item @code{CONFIGURE_POSIX_INIT_THREAD_STACK_SIZE}
is the stack size of the single initialization thread defined by the
POSIX API Initialization Threads Table.  By default
value is twice the configured minimum stack size.

@end itemize

@subsection ITRON API Configuration

The parameters in this section are used to configure resources
for the RTEMS ITRON API.  They are only relevant if the POSIX API
is enabled at configure time using the @code{--enable-itron} option.

@itemize @bullet
@findex CONFIGURE_MAXIMUM_ITRON_TASKS
@item @code{CONFIGURE_MAXIMUM_ITRON_TASKS}
is the maximum number of
ITRON API tasks that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_ITRON_SEMAPHORES
@item @code{CONFIGURE_MAXIMUM_ITRON_SEMAPHORES}
is the maximum number of
ITRON API semaphores that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_ITRON_EVENTFLAGS
@item @code{CONFIGURE_MAXIMUM_ITRON_EVENTFLAGS}
is the maximum number of
ITRON API eventflags that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_ITRON_MAILBOXES
@item @code{CONFIGURE_MAXIMUM_ITRON_MAILBOXES}
is the maximum number of
ITRON API mailboxes that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_ITRON_MESSAGE_BUFFERS
@item @code{CONFIGURE_MAXIMUM_ITRON_MESSAGE_BUFFERS}
is the maximum number of
ITRON API message buffers that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_ITRON_PORTS
@item @code{CONFIGURE_MAXIMUM_ITRON_PORTS}
is the maximum number of
ITRON API ports that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_ITRON_MEMORY_POOLS
@item @code{CONFIGURE_MAXIMUM_ITRON_MEMORY_POOLS}
is the maximum number of
ITRON API memory pools that can be concurrently active.
The default is 0.

@findex CONFIGURE_MAXIMUM_ITRON_FIXED_MEMORY_POOLS
@item @code{CONFIGURE_MAXIMUM_ITRON_FIXED_MEMORY_POOLS}
is the maximum number of
ITRON API fixed memory pools that can be concurrently active.
The default is 0.

@end itemize

@subsection ITRON Initialization Task Table Configuration

The @code{rtems/confdefs.h} configuration system can automatically
generate an ITRON Initialization Tasks Table named
@code{ITRON_Initialization_tasks} with a single entry.  The following
parameters control the generation of that table.

@itemize @bullet
@findex CONFIGURE_ITRON_INIT_TASK_TABLE
@item @code{CONFIGURE_ITRON_INIT_TASK_TABLE} is defined
if the user wishes to use a ITRON API Initialization
Tasks Table.  The application may choose to use the initialization
tasks or threads table from another API.  By default, this
field is not defined as the user MUST select their own
API for initialization tasks.

@findex CONFIGURE_ITRON_HAS_OWN_INIT_TASK_TABLE
@item @code{CONFIGURE_ITRON_HAS_OWN_INIT_TASK_TABLE}
is defined if the user wishes to define their own ITRON API Initialization
Tasks Table.  This table should be named @code{ITRON_Initialization_tasks}.
By default, this is not defined.

@findex CONFIGURE_ITRON_INIT_TASK_ENTRY_POINT
@item @code{CONFIGURE_ITRON_INIT_TASK_ENTRY_POINT}
is the entry point (a.k.a. function name)
of the single initialization task defined by the
ITRON API Initialization Tasks Table.  By default
the value is @code{ITRON_Init}.

@findex CONFIGURE_ITRON_INIT_TASK_ATTRIBUTES
@item @code{CONFIGURE_ITRON_INIT_TASK_ATTRIBUTES}
is the attribute set
of the single initialization task defined by the
ITRON API Initialization Tasks Table.  By default
the value is @code{TA_HLNG}.

@findex CONFIGURE_ITRON_INIT_TASK_PRIORITY
@item @code{CONFIGURE_ITRON_INIT_TASK_PRIORITY}
is the initial priority
of the single initialization task defined by the
ITRON API Initialization Tasks Table.  By default
the value is @code{1} which is the highest priority
in the ITRON API.

@findex CONFIGURE_ITRON_INIT_TASK_STACK_SIZE
@item @code{CONFIGURE_ITRON_INIT_TASK_STACK_SIZE}
is the stack size of the single initialization task defined by the
ITRON API Initialization Tasks Table.  By default
value is the configured minimum stack size.

@end itemize

@subsection Ada Tasks

This section defines the system configuration parameters supported
by @code{rtems/confdefs.h} related to configuring RTEMS to support
a task using Ada tasking with GNAT.

@itemize @bullet
@findex CONFIGURE_GNAT_RTEMS
@item @code{CONFIGURE_GNAT_RTEMS} is defined to inform
RTEMS that the GNAT Ada run-time is to be used by the 
application.  This configuration parameter is critical
as it makes @code{rtems/confdefs.h} configure the resources
(mutexes and keys) used implicitly by the GNAT run-time.
By default, this parameter is not defined.

@findex CONFIGURE_MAXIMUM_ADA_TASKS
@item @code{CONFIGURE_MAXIMUM_ADA_TASKS} is the 
number of Ada tasks that can be concurrently active
in the system.  By default, when @code{CONFIGURE_GNAT_RTEMS}
is defined, this is set to 20.

@findex CONFIGURE_MAXIMUM_FAKE_ADA_TASKS
@item @code{CONFIGURE_MAXIMUM_FAKE_ADA_TASKS} is
the number of "fake" Ada tasks that can be concurrently
active in the system.  A "fake" Ada task is a non-Ada
task that makes calls back into Ada code and thus
implicitly uses the Ada run-time.

@end itemize

@section Configuration Table

@cindex Configuration Table
@cindex RTEMS Configuration Table

The RTEMS Configuration Table is used to tailor an
application for its specific needs.  For example, the user can
configure the number of device drivers or which APIs may be used.
THe address of the user-defined Configuration Table is passed as an
argument to the @code{rtems_initialize_executive}
directive, which MUST be the first RTEMS directive called.  
The RTEMS Configuration Table is defined in the following C structure:

@findex rtems_configuration_table
@example
@group
typedef struct @{
  void                           *work_space_start;
  uintptr_t                       work_space_size;
  uint32_t                        maximum_extensions;
  uint32_t                        microseconds_per_tick;
  uint32_t                        ticks_per_timeslice;
  void                          (*idle_task)( void );
  uint32_t                        idle_task_stack_size;
  uint32_t                        interrupt_stack_size;
  void *                        (*stack_allocate_hook)( size_t );
  void                          (*stack_free_hook)( void * );
  bool                            do_zero_of_workspace;
  uint32_t                        maximum_drivers;
  uint32_t                        number_of_device_drivers;
  rtems_driver_address_table     *Device_driver_table;
  uint32_t                        number_of_initial_extensions;
  rtems_extensions_table         *User_extension_table;
#if defined(RTEMS_MULTIPROCESSING)
  rtems_multiprocessing_table    *User_multiprocessing_table;
#endif
  rtems_api_configuration_table  *RTEMS_api_configuration;
  posix_api_configuration_table  *POSIX_api_configuration;
  itron_api_configuration        *ITRON_api_configuration;
@} rtems_configuration_table;
@end group
@end example

@table @b
@item work_space_start
is the address of the RTEMS RAM Workspace.  
This area contains items such as the
various object control blocks (TCBs, QCBs, ...) and task stacks.
If the address is not aligned on a four-word boundary, then
RTEMS will invoke the fatal error handler during
@code{rtems_initialize_executive}.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_EXECUTIVE_RAM_WORK_AREA}
which defaults to @code{NULL}.  Normally, this field should be 
configured as @code{NULL} as BSPs will assign memory for the
RTEMS RAM Workspace as part of system initialization.

@item work_space_size
is the calculated size of the
RTEMS RAM Workspace.  The section Sizing the RTEMS RAM Workspace
details how to arrive at this number.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_EXECUTIVE_RAM_SIZE}
and is calculated based on the other system configuration settings.

@item microseconds_per_tick
is number of microseconds per clock tick.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MICROSECONDS_PER_TICK}.
If not defined by the application, then the
@code{CONFIGURE_MICROSECONDS_PER_TICK} macro defaults to 10000 
(10 milliseconds).

@item ticks_per_timeslice
is the number of clock ticks for a timeslice.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_TICKS_PER_TIMESLICE}.

@item idle_task
is the address of the optional user
provided routine which is used as the system's IDLE task.  If
this field is not NULL, then the RTEMS default IDLE task is not
used.  This field may be NULL to indicate that the default IDLE
is to be used.  When using the @code{rtems/confdefs.h} mechanism
for configuring an RTEMS application, the value for this field
corresponds to the setting of the macro @code{CONFIGURE_IDLE_TASK_BODY}.

@item idle_task_stack_size
is the size of the RTEMS idle task stack in bytes.  If this number is less
than the configured minimum stack size, then the idle task's stack will
be set to the minimum.  When using the @code{rtems/confdefs.h} mechanism
for configuring an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_IDLE_TASK_STACK_SIZE}.

@item interrupt_stack_size
is the size of the RTEMS interrupt stack in bytes.  If this number is less
than configured minimum stack size, then the interrupt stack will be set
to the minimum.  When using the @code{rtems/confdefs.h} mechanism for
configuring an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_INTERRUPT_STACK_SIZE}.

@item stack_allocate_hook
may point to a user provided routine to allocate task stacks.
The default is to allocate task stacks from the RTEMS Workspace.
When using the @code{rtems/confdefs.h} mechanism
for configuring an RTEMS application, the value for this field
corresponds to the setting of the macro
@code{CONFIGURE_TASK_STACK_ALLOCATOR}.

@item stack_free_hook
may point to a user provided routine to free task stacks.
The default is to allocate task stacks from the RTEMS Workspace.
When using the @code{rtems/confdefs.h} mechanism
for configuring an RTEMS application, the value for this field
corresponds to the setting of the macro
@code{CONFIGURE_TASK_STACK_DEALLOCATOR}.

@item do_zero_of_workspace
indicates whether RTEMS should zero the RTEMS Workspace and
C Program Heap as part of its initialization.  If set to
TRUE, the Workspace is zeroed.  Otherwise, it is not.
When using the @code{rtems/confdefs.h} mechanism
for configuring an RTEMS application, the value for this field
corresponds to the setting of the macro
@code{CONFIGURE_ZERO_WORKSPACE_AUTOMATICALLY}.

@item maximum_drivers
is the maximum number of device drivers that can be registered.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_DRIVERS}.

@item number_of_device_drivers
is the number of device drivers for the system.  There should be
the same number of entries in the Device Driver Table.  If this field
is zero, then the @code{User_driver_address_table} entry should be NULL.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field is calculated
automatically based on the number of entries in the 
Device Driver Table.  This calculation is based on the assumption
that the Device Driver Table is named @code{Device_drivers}
and defined in C.  This table may be generated automatically
for simple applications using only the device drivers that correspond
to the following macros:

@itemize @bullet

@item @code{CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER}
@item @code{CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER}
@item @code{CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER}
@item @code{CONFIGURE_APPLICATION_NEEDS_RTC_DRIVER}
@item @code{CONFIGURE_APPLICATION_NEEDS_STUB_DRIVER}

@end itemize

Note that network device drivers are not configured in the
Device Driver Table.

@item Device_driver_table
is the address of the Device Driver Table.  This table contains the entry
points for each device driver.  If the number_of_device_drivers field is zero,
then this entry should be NULL. The format of this table will be
discussed below.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the Device Driver Table is assumed to be
named @code{Device_drivers} and defined in C.  If the application is providing
its own Device Driver Table, then the macro
@code{CONFIGURE_HAS_OWN_DEVICE_DRIVER_TABLE} must be defined to indicate
this and prevent @code{rtems/confdefs.h} from generating the table.

@item number_of_initial_extensions
is the number of initial user extensions.  There should be
the same number of entries as in the User_extension_table.  If this field
is zero, then the User_driver_address_table entry should be NULL.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_NUMBER_OF_INITIAL_EXTENSIONS}
which is set automatically by @code{rtems/confdefs.h} based on the size
of the User Extensions Table.

@item User_extension_table
is the address of the User
Extension Table.  This table contains the entry points for the
static set of optional user extensions.  If no user extensions
are configured, then this entry should be NULL.  The format of
this table will be discussed below.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the User Extensions Table is named
@code{Configuration_Initial_Extensions} and defined in
confdefs.h.  It is initialized based on the following
macros:

@itemize @bullet

@item @code{CONFIGURE_INITIAL_EXTENSIONS}
@item @code{STACK_CHECKER_EXTENSION}

@end itemize

The application may configure one or more initial user extension
sets by setting the @code{CONFIGURE_INITIAL_EXTENSIONS} macro.  By
defining the @code{STACK_CHECKER_EXTENSION} macro, the task stack bounds
checking user extension set is automatically included in the
application.

@item User_multiprocessing_table
is the address of the Multiprocessor Configuration Table.  This
table contains information needed by RTEMS only when used in a multiprocessor
configuration.  This field must be NULL when RTEMS is used in a
single processor configuration.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the Multiprocessor Configuration Table
is automatically generated when the @code{CONFIGURE_MP_APPLICATION}
is defined.  If @code{CONFIGURE_MP_APPLICATION} is not defined, the this
entry is set to NULL.  The generated table has the name
@code{Multiprocessing_configuration}.

@item RTEMS_api_configuration
is the address of the RTEMS API Configuration Table.  This table
contains information needed by the RTEMS API.  This field should be
NULL if the RTEMS API is not used.  [NOTE: Currently the RTEMS API
is required to support support components such as BSPs and libraries 
which use this API.]  This table is built automatically and this
entry filled in, if using the @code{rtems/confdefs.h} application
configuration mechanism.  The generated table has the name
@code{Configuration_RTEMS_API}.

@item POSIX_api_configuration
is the address of the POSIX API Configuration Table.  This table
contains information needed by the POSIX API.  This field should be
NULL if the POSIX API is not used.  This table is built automatically
and this entry filled in, if using the @code{rtems/confdefs.h} application
configuration mechanism.  The @code{rtems/confdefs.h} application 
mechanism will fill this field in with the address of the
@code{Configuration_POSIX_API} table of POSIX API is configured
and NULL if the POSIX API is not configured.

@end table

@section RTEMS API Configuration Table

@cindex RTEMS API Configuration Table

The RTEMS API Configuration Table is used to configure the 
managers which constitute the RTEMS API for a particular application.  
For example, the user can configure the maximum number of tasks for 
this application. The RTEMS API Configuration Table is defined in 
the following C structure:

@findex rtems_api_configuration_table
@example
@group
typedef struct @{
  uint32_t  maximum_tasks;
  uint32_t  maximum_timers;
  uint32_t  maximum_semaphores;
  uint32_t  maximum_message_queues;
  uint32_t  maximum_partitions;
  uint32_t  maximum_regions;
  uint32_t  maximum_ports;
  uint32_t  maximum_periods;
  uint32_t  maximum_barriers;
  uint32_t  number_of_initialization_tasks;
  rtems_initialization_tasks_table *User_initialization_tasks_table;
@} rtems_api_configuration_table;
@end group
@end example

@table @b
@item maximum_tasks
is the maximum number of tasks that
can be concurrently active (created) in the system including
initialization tasks.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_TASKS}.
If not defined by the application, then the @code{CONFIGURE_MAXIMUM_TASKS}
macro defaults to 0.

@item maximum_timers
is the maximum number of timers
that can be concurrently active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_TIMERS}.
If not defined by the application, then the @code{CONFIGURE_MAXIMUM_TIMERS}
macro defaults to 0.

@item maximum_semaphores
is the maximum number of
semaphores that can be concurrently active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_SEMAPHORES}.
If not defined by the application, then the @code{CONFIGURE_MAXIMUM_SEMAPHORES}
macro defaults to 0.

@item maximum_message_queues
is the maximum number of
message queues that can be concurrently active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_MESSAGE_QUEUES}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_MESSAGE_QUEUES} macro defaults to 0.

@item maximum_partitions
is the maximum number of
partitions that can be concurrently active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_PARTITIONS}.
If not defined by the application, then the @code{CONFIGURE_MAXIMUM_PARTITIONS}
macro defaults to 0.

@item maximum_regions
is the maximum number of regions
that can be concurrently active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_REGIONS}.
If not defined by the application, then the @code{CONFIGURE_MAXIMUM_REGIONS}
macro defaults to 0.

@item maximum_ports
is the maximum number of ports into
dual-port memory areas that can be concurrently active in the
system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_PORTS}.
If not defined by the application, then the @code{CONFIGURE_MAXIMUM_PORTS}
macro defaults to 0.

@item number_of_initialization_tasks
is the number of initialization tasks configured.  At least one
RTEMS initialization task or POSIX initializatin must be configured
in order for the user's application to begin executing.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the user must define the
@code{CONFIGURE_RTEMS_INIT_TASKS_TABLE} to indicate that there
is one or more RTEMS initialization task.  If the application
only has one RTEMS initialization task, then the automatically
generated Initialization Task Table will be sufficient.  The following
macros correspond to the single initialization task:
  
@itemize @bullet

@item @code{CONFIGURE_INIT_TASK_NAME} - is the name of the task.  
If this macro is not defined by the application, then this defaults
to the task name of @code{"UI1 "} for User Initialization Task 1.

@item @code{CONFIGURE_INIT_TASK_STACK_SIZE} - is the stack size
of the single initialization task.  If this macro is not defined
by the application, then this defaults to configured minimum
stack size.

@item @code{CONFIGURE_INIT_TASK_PRIORITY} - is the initial priority
of the single initialization task.  If this macro is not defined
by the application, then this defaults to 1.

@item @code{CONFIGURE_INIT_TASK_ATTRIBUTES} - is the attributes
of the single initialization task.  If this macro is not defined
by the application, then this defaults to @code{RTEMS_DEFAULT_ATTRIBUTES}.

@item @code{CONFIGURE_INIT_TASK_ENTRY_POINT} - is the entry point
of the single initialization task.  If this macro is not defined
by the application, then this defaults to the C language routine
@code{Init}.

@item @code{CONFIGURE_INIT_TASK_INITIAL_MODES} - is the initial execution
modes of the single initialization task.  If this macro is not defined
by the application, then this defaults to @code{RTEMS_NO_PREEMPT}.

@item @code{CONFIGURE_INIT_TASK_ARGUMENTS} - is the argument passed to the 
of the single initialization task.  If this macro is not defined
by the application, then this defaults to 0.


@end itemize


has the option to have 
 value for this field corresponds
to the setting of the macro @code{}.

@item User_initialization_tasks_table
is the address of the Initialization Task Table. This table contains the
information needed to create and start each of the
initialization tasks.  The format of this table will be discussed below.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_EXECUTIVE_RAM_WORK_AREA}.

@end table

@section POSIX API Configuration Table

@cindex POSIX API Configuration Table

The POSIX API Configuration Table is used to configure the
managers which constitute the POSIX API for a particular application.
For example, the user can configure the maximum number of threads for
this application. The POSIX API Configuration Table is defined in
the following C structure:
 
@findex posix_initialization_threads_table
@findex posix_api_configuration_table
@example
@group
typedef struct @{
  void       *(*thread_entry)(void *);
@} posix_initialization_threads_table;
 
typedef struct @{
  int                                 maximum_threads;
  int                                 maximum_mutexes;
  int                                 maximum_condition_variables;
  int                                 maximum_keys;
  int                                 maximum_timers;
  int                                 maximum_queued_signals;
  int                                 maximum_message_queues;
  int                                 maximum_message_queue_descriptors;
  int                                 maximum_semaphores;
  int                                 maximum_barriers;
  int                                 maximum_rwlocks;
  int                                 maximum_spinlocks;
  int                                 number_of_initialization_threads;
  posix_initialization_threads_table *User_initialization_tasks_table;
@} posix_api_configuration_table;
@end group
@end example
 
@table @b
@item maximum_threads
is the maximum number of threads that
can be concurrently active (created) in the system including
initialization threads.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_POSIX_THREADS}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_POSIX_THREADS} macro defaults to 0.

@item maximum_mutexes
is the maximum number of mutexes that can be concurrently 
active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_POSIX_MUTEXES}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_POSIX_MUTEXES} macro defaults to 0.

@item maximum_condition_variables
is the maximum number of condition variables that can be 
concurrently active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_POSIX_CONDITION_VARIABLES} macro defaults to 0.

@item maximum_keys
is the maximum number of keys that can be concurrently active in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_POSIX_KEYS}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_POSIX_KEYS} macro defaults to 0.

@item maximum_timers
is the maximum number of POSIX timers that can be concurrently active
in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_POSIX_TIMERS}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_POSIX_TIMERS} macro defaults to 0.

@item maximum_queued_signals
is the maximum number of queued signals that can be concurrently 
pending in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MAXIMUM_POSIX_QUEUED_SIGNALS}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_POSIX_QUEUED_SIGNALS} macro defaults to 0.

@item maximum_message_queues
is the maximum number of POSIX message queues that can be concurrently
active in the system.  When using the @code{rtems/confdefs.h}
mechanism for configuring an RTEMS application, the
value for this field corresponds to the setting of the macro
@code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES}.  If not defined by the
application, then the @code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES}
macro defaults to 0.

@item maximum_message_queue_descriptors
is the maximum number of POSIX message queue descriptors
that can be concurrently active in the system.  When using the
@code{rtems/confdefs.h} mechanism for configuring an RTEMS application,
the value for this field corresponds to the setting of the macro
@code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUE_DESCRIPTORS}.
If not defined by the application, then the
@code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUE_DESCRIPTORS} macro defaults
to the value of @code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES}

@item maximum_semaphores
is the maximum number of POSIX semaphore that can be concurrently
active in the system.  When using the @code{rtems/confdefs.h}
mechanism for configuring an RTEMS application, the
value for this field corresponds to the setting of the macro
@code{CONFIGURE_MAXIMUM_POSIX_SEMAPHORES}.  If not defined by the
application, then the @code{CONFIGURE_MAXIMUM_POSIX_SEMAPHORES}
macro defaults to 0.

@item maximum_barriers
is the maximum number of POSIX barriers that can be concurrently
active in the system.  When using the @code{rtems/confdefs.h}
mechanism for configuring an RTEMS application, the
value for this field corresponds to the setting of the macro
@code{CONFIGURE_MAXIMUM_POSIX_BARRIERS}.  If not defined by the
application, then the @code{CONFIGURE_MAXIMUM_POSIX_BARRIERS}
macro defaults to 0.

@item maximum_rwlocks
is the maximum number of POSIX rwlocks that can be concurrently
active in the system.  When using the @code{rtems/confdefs.h}
mechanism for configuring an RTEMS application, the
value for this field corresponds to the setting of the macro
@code{CONFIGURE_MAXIMUM_POSIX_SPINLOCKS}.  If not defined by the
application, then the @code{CONFIGURE_MAXIMUM_POSIX_SPINLOCKS}
macro defaults to 0.

@item maximum_spinlocks
is the maximum number of POSIX spinlocks that can be concurrently
active in the system.  When using the @code{rtems/confdefs.h}
mechanism for configuring an RTEMS application, the
value for this field corresponds to the setting of the macro
@code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES}.  If not defined by the
application, then the @code{CONFIGURE_MAXIMUM_POSIX_MESSAGE_QUEUES}
macro defaults to 0.

@item number_of_initialization_threads
is the number of initialization threads configured.  At least one
initialization threads must be configured.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the user must define the
@code{CONFIGURE_POSIX_INIT_THREAD_TABLE} to indicate that there
is one or more POSIX initialization thread.  If the application
only has one POSIX initialization thread, then the automatically
generated POSIX Initialization Thread Table will be sufficient.  The following
macros correspond to the single initialization task:

@itemize @bullet

@item @code{CONFIGURE_POSIX_INIT_THREAD_ENTRY_POINT} - is the entry
point of the thread.  If this macro is not defined by the application,
then this defaults to the C routine @code{POSIX_Init}.

@item @code{CONFIGURE_POSIX_INIT_TASK_STACK_SIZE} - is the stack size
of the single initialization thread.  If this macro is not defined
by the application, then this defaults to twice the configured
minimum stack size.

@end itemize
 
@item User_initialization_threads_table
is the address of the Initialization Threads Table. This table contains the
information needed to create and start each of the initialization threads.  
The format of each entry in this table is defined in the 
@code{posix_initialization_threads_table} structure.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the address of the @code{POSIX_Initialization_threads} structure.

@end table

@section CPU Dependent Information Table

@cindex CPU Dependent Information Table

The CPU Dependent Information Table is used to
describe processor dependent information required by RTEMS.
This table is generally used to supply RTEMS with information
only known by the Board Support Package.  The contents of this
table are discussed in the CPU Dependent Information Table
chapter of the Applications Supplement document for a specific
target processor.

The @code{rtems/confdefs.h} mechanism does not support generating this
table.  It is normally filled in by the Board Support Package.

@section Initialization Task Table

@cindex Initialization Tasks Table

The Initialization Task Table is used to describe
each of the user initialization tasks to the Initialization
Manager.  The table contains one entry for each initialization
task the user wishes to create and start.  The fields of this
data structure directly correspond to arguments to the
@code{@value{DIRPREFIX}task_create} and
@code{@value{DIRPREFIX}task_start} directives.  The number of entries is
found in the @code{number_of_initialization_tasks} entry in the
Configuration Table.  

The format of each entry in the
Initialization Task Table is defined in the following C structure:

@findex rtems_initialization_tasks_table
@example
typedef struct @{
  rtems_name           name;
  size_t               stack_size;
  rtems_task_priority  initial_priority;
  rtems_attribute      attribute_set;
  rtems_task_entry     entry_point;
  rtems_mode           mode_set;
  rtems_task_argument  argument;
@} rtems_initialization_tasks_table;
@end example

@table @b
@item name
is the name of this initialization task.

@item stack_size
is the size of the stack for this initialization task.

@item initial_priority
is the priority of this initialization task.

@item attribute_set
is the attribute set used during creation of this initialization task.

@item entry_point
is the address of the entry point of this initialization task.

@item mode_set
is the initial execution mode of this initialization task.

@item argument
is the initial argument for this initialization task.

@end table

A typical declaration for an Initialization Task Table might appear as follows:

@example
rtems_initialization_tasks_table
Initialization_tasks[2] = @{
   @{ INIT_1_NAME,
     1024,
     1,
     DEFAULT_ATTRIBUTES,
     Init_1,
     DEFAULT_MODES,
     1

   @},
   @{ INIT_2_NAME,
     1024,
     250,
     FLOATING_POINT,
     Init_2,
     NO_PREEMPT,
     2

   @}
@};
@end example

@section Driver Address Table

@cindex Device Driver Table

The Device Driver Table is used to inform the I/O Manager of the set of
entry points for each device driver configured in the system.  The table
contains one entry for each device driver required by the application.
The number of entries is defined in the number_of_device_drivers entry
in the Configuration Table.  This table is copied to the Device Drive
Table during the IO Manager's initialization giving the entries in this
table the lower major numbers.  The format of each entry in the Device
Driver Table is defined in the following C structure:

@findex rtems_driver_address_table
@example
typedef struct @{
  rtems_device_driver_entry initialization_entry;
  rtems_device_driver_entry open_entry;
  rtems_device_driver_entry close_entry;
  rtems_device_driver_entry read_entry;
  rtems_device_driver_entry write_entry;
  rtems_device_driver_entry control_entry;
@} rtems_driver_address_table;
@end example

@table @b
@item initialization_entry
is the address of the entry point called by
@code{rtems_io_initialize}
to initialize a device driver and its associated devices.

@item open_entry
is the address of the entry point called by @code{rtems_io_open}.

@item close_entry
is the address of the entry point called by @code{rtems_io_close}.

@item read_entry
is the address of the entry point called by @code{rtems_io_read}.

@item write_entry
is the address of the entry point called by @code{rtems_io_write}.

@item control_entry
is the address of the entry point called by @code{rtems_io_control}.

@end table

Driver entry points configured as NULL will always
return a status code of @code{@value{RPREFIX}SUCCESSFUL}.  No user code will be
executed in this situation.

A typical declaration for a Device Driver Table might appear as follows:

@example
rtems_driver_address_table Driver_table[2] = @{
   @{ tty_initialize, tty_open,  tty_close,  /* major = 0 */
     tty_read,       tty_write, tty_control
   @},
   @{ lp_initialize, lp_open,    lp_close,   /* major = 1 */
     NULL,          lp_write,   lp_control
   @}
@};
@end example

More information regarding the construction and
operation of device drivers is provided in the I/O Manager
chapter.

@section User Extensions Table

@cindex User Extensions Table

The User Extensions Table is used to inform RTEMS of
the optional user-supplied static extension set.  This table
contains one entry for each possible extension.  The entries are
called at critical times in the life of the system and
individual tasks.  The application may create dynamic extensions
in addition to this single static set.  The format of each entry
in the User Extensions Table is defined in the following C structure:

@example
typedef void           rtems_extension;
typedef void (*rtems_task_create_extension)(
   Thread_Control * /* executing */,
   Thread_Control * /* created */
);
typedef void (*rtems_task_delete_extension)(
   Thread_Control * /* executing */,
   Thread_Control * /* deleted */
);
typedef void (*rtems_task_start_extension)(
   Thread_Control * /* executing */,
   Thread_Control * /* started */
);
typedef void (*rtems_task_restart_extension)(
   Thread_Control * /* executing */,
   Thread_Control * /* restarted */
);
typedef void (*rtems_task_switch_extension)(
   Thread_Control * /* executing */,
   Thread_Control * /* heir */
);
typedef void (*rtems_task_begin_extension)(
   Thread_Control * /* beginning */
);
typedef void (*rtems_task_exitted_extension)(
   Thread_Control * /* exiting */
);
typedef void (*rtems_fatal_extension)(
   Internal_errors_Source /* the_source */,
   bool                   /* is_internal */,
   uint32_t               /* the_error */
);

typedef struct @{
  rtems_task_create_extension      thread_create;
  rtems_task_start_extension       thread_start;
  rtems_task_restart_extension     thread_restart;
  rtems_task_delete_extension      thread_delete;
  rtems_task_switch_extension      thread_switch;
  rtems_task_begin_extension       thread_begin;
  rtems_task_exitted_extension     thread_exitted;
  rtems_fatal_extension            fatal;
@} rtems_extensions_table;
@end example

@table @b

@item thread_create
is the address of the
user-supplied subroutine for the TASK_CREATE extension.  If this
extension for task creation is defined, it is called from the
task_create directive.  A value of NULL indicates that no
extension is provided.

@item thread_start
is the address of the user-supplied
subroutine for the TASK_START extension.  If this extension for
task initiation is defined, it is called from the task_start
directive.  A value of NULL indicates that no extension is
provided.

@item thread_restart
is the address of the user-supplied
subroutine for the TASK_RESTART extension.  If this extension
for task re-initiation is defined, it is called from the
task_restart directive.  A value of NULL indicates that no
extension is provided.

@item thread_delete
is the address of the user-supplied
subroutine for the TASK_DELETE extension.  If this RTEMS
extension for task deletion is defined, it is called from the
task_delete directive.  A value of NULL indicates that no
extension is provided.

@item thread_switch
is the address of the user-supplied
subroutine for the task context switch extension.  This
subroutine is called from RTEMS dispatcher after the current
task has been swapped out but before the new task has been
swapped in.  A value of NULL indicates that no extension is
provided.  As this routine is invoked after saving the current
task's context and before restoring the heir task's context, it
is not necessary for this routine to save and restore any
registers.

@item thread_begin
is the address of the user-supplied
subroutine which is invoked immediately before a task begins
execution.  It is invoked in the context of the beginning task.
A value of NULL indicates that no extension is provided.

@item thread_exitted
is the address of the user-supplied
subroutine which is invoked when a task exits.  This procedure
is responsible for some action which will allow the system to
continue execution (i.e. delete or restart the task) or to
terminate with a fatal error.  If this field is set to NULL, the
default RTEMS TASK_EXITTED handler will be invoked.

@item fatal
is the address of the user-supplied
subroutine for the FATAL extension.  This RTEMS extension of
fatal error handling is called from the 
@code{@value{DIRPREFIX}fatal_error_occurred}
directive.  If the user's fatal error handler returns or if this
entry is NULL then the default RTEMS fatal error handler will be
executed.

@end table

A typical declaration for a User Extension Table
which defines the TASK_CREATE, TASK_DELETE, TASK_SWITCH, and
FATAL extension might appear as follows:

@example
rtems_extensions_table User_extensions = @{
   task_create_extension,
   NULL,
   NULL,
   task_delete_extension,
   task_switch_extension,
   NULL,
   NULL,
   fatal_extension
@};
@end example

More information regarding the user extensions is
provided in the User Extensions chapter.

@section Multiprocessor Configuration Table

@cindex Multiprocessor Configuration Table

The Multiprocessor Configuration Table contains
information needed when using RTEMS in a multiprocessor
configuration.  Many of the details associated with configuring
a multiprocessor system are dependent on the multiprocessor
communications layer provided by the user.  The address of the
Multiprocessor Configuration Table should be placed in the
@code{User_multiprocessing_table} entry in the primary Configuration
Table.  Further details regarding many of the entries in the
Multiprocessor Configuration Table will be provided in the
Multiprocessing chapter.  


When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the macro @code{CONFIGURE_MP_APPLICATION} must
be defined to automatically generate the Multiprocessor Configuration Table.
If @code{CONFIGURE_MP_APPLICATION}, is not defined, then a NULL pointer
is configured as the address of this table.

The format of the Multiprocessor Configuration Table is defined in 
the following C structure:

@example
typedef struct @{
  uint32_t          node;
  uint32_t          maximum_nodes;
  uint32_t          maximum_global_objects;
  uint32_t          maximum_proxies;
  uint32_t          extra_mpci_receive_server_stack;
  rtems_mpci_table *User_mpci_table;
@} rtems_multiprocessing_table;
@end example

@table @b
@item node
is a unique processor identifier
and is used in routing messages between nodes in a
multiprocessor configuration.  Each processor must have a unique
node number.  RTEMS assumes that node numbers start at one and
increase sequentially.  This assumption can be used to advantage
by the user-supplied MPCI layer.  Typically, this requirement is
made when the node numbers are used to calculate the address of
inter-processor communication links.  Zero should be avoided as
a node number because some MPCI layers use node zero to
represent broadcasted packets.  Thus, it is recommended that
node numbers start at one and increase sequentially.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MP_NODE_NUMBER}.
If not defined by the application, then the @code{CONFIGURE_MP_NODE_NUMBER}
macro defaults to the value of the @code{NODE_NUMBER} macro which is
set on the compiler command line by the RTEMS Multiprocessing Test Suites.


@item maximum_nodes
is the number of processor nodes in the system.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MP_MAXIMUM_NODES}.
If not defined by the application, then the @code{CONFIGURE_MP_MAXIMUM_NODES}
macro defaults to the value 2.

@item maximum_global_objects
is the maximum number of global objects which can exist at any
given moment in the entire system.  If this parameter is not the
same on all nodes in the system, then a fatal error is generated
to inform the user that the system is inconsistent.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MP_MAXIMUM_GLOBAL_OBJECTS}.
If not defined by the application, then the
@code{CONFIGURE_MP_MAXIMUM_GLOBAL_OBJECTS} macro defaults to the value 32.


@item maximum_proxies
is the maximum number of proxies which can exist at any given moment
on this particular node.  A proxy is a substitute task control block
which represent a task residing on a remote node when that task blocks
on a remote object.  Proxies are used in situations in which delayed
interaction is required with a remote node.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MP_MAXIMUM_PROXIES}.
If not defined by the application, then the @code{CONFIGURE_MP_MAXIMUM_PROXIES}
macro defaults to the value 32.

@item extra_mpci_receive_server_stack
is the extra stack space allocated for the RTEMS MPCI receive server task
in bytes.  The MPCI receive server may invoke nearly all directives and 
may require extra stack space on some targets.

@item User_mpci_table
is the address of the Multiprocessor Communications Interface
Table.  This table contains the entry points of user-provided functions
which constitute the multiprocessor communications layer.  This table
must be provided in multiprocessor configurations with all
entries configured.  The format of this table and details
regarding its entries can be found in the next section.
When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the value for this field corresponds
to the setting of the macro @code{CONFIGURE_MP_MPCI_TABLE_POINTER}.
If not defined by the application, then the
@code{CONFIGURE_MP_MPCI_TABLE_POINTER} macro defaults to the 
address of the table named @code{MPCI_table}.


@end table

@section Multiprocessor Communications Interface Table

@cindex  Multiprocessor Communications Interface Table

This table defines the set of callouts that must be provided by 
an Multiprocessor Communications Interface implementation.  

When using the @code{rtems/confdefs.h} mechanism for configuring
an RTEMS application, the name of this table is assumed
to be @code{MPCI_table} unless the application sets
the @code{CONFIGURE_MP_MPCI_TABLE_POINTER} when configuring a
multiprocessing system. 

The format of this table is defined in 
the following C structure:

@example
typedef struct @{
  uint32_t                        default_timeout; /* in ticks */
  uint32_t                        maximum_packet_size;
  rtems_mpci_initialization_entry initialization;
  rtems_mpci_get_packet_entry     get_packet;
  rtems_mpci_return_packet_entry  return_packet;
  rtems_mpci_send_entry           send_packet;
  rtems_mpci_receive_entry        receive_packet;
@} rtems_mpci_table;
@end example

@table @b
@item default_timeout
is the default maximum length of time a task should block waiting for
a response to a directive which results in communication with a remote node.
The maximum length of time is a function the user supplied
multiprocessor communications layer and the media used.  This
timeout only applies to directives which would not block if the
operation were performed locally.

@item maximum_packet_size
is the size in bytes of the longest packet which the MPCI layer is capable
of sending.  This value should represent the total number of bytes available
for a RTEMS interprocessor messages.

@item initialization
is the address of the entry point for the initialization procedure of the
user supplied multiprocessor communications layer.

@item get_packet
is the address of the entry point for the procedure called by RTEMS to
obtain a packet from the user supplied multiprocessor communications layer.

@item return_packet
is the address of the entry point for the procedure called by RTEMS to
return a packet to the user supplied multiprocessor communications layer.

@item send
is the address of the entry point for the procedure called by RTEMS to
send an envelope to another node.  This procedure is part of the user
supplied multiprocessor communications layer.

@item receive
is the address of the entry point for the
procedure called by RTEMS to retrieve an envelope containing a
message from another node.  This procedure is part of the user
supplied multiprocessor communications layer.

@end table

More information regarding the required functionality of these
entry points is provided in the Multiprocessor chapter.

@section Determining Memory Requirements

Since memory is a critical resource in many real-time
embedded systems, the RTEMS Classic API was specifically designed to allow
unused managers to be forcibly excluded from the run-time environment.
This allows the application designer the flexibility to tailor
RTEMS to most efficiently meet system requirements while still
satisfying even the most stringent memory constraints.  As
result, the size of the RTEMS executive is application
dependent.

It is not necessary for RTEMS Application Developers to calculate
the amount of memory required for the RTEMS Workspace.  This
is done automatically by @code{<rtems/confdefs.h>}.  
See @ref{Configuring a System Sizing the RTEMS RAM Workspace} for
more details on how 
this works.  In the event, you are interested in the memory required
for an instance of a particular RTEMS object, please run the test
@code{spsize} on your target board.

RTEMS is built to be a library and any routines that you do not 
directly or indirectly require in your application will @b{NOT}
be included in your executable image.  However, some managers
may be explicitly excluded and no attempt to create these instances
of these objects will succeed even if they are configured.
The following Classic API managers may be optionally excluded:

@itemize @bullet
@item signal
@item region
@item dual ported memory
@item event
@item multiprocessing
@item partition
@item timer
@item semaphore
@item message
@item rate monotonic
@end itemize

RTEMS is designed to be built and installed as a library
that is linked into the application.  As such, much of
RTEMS is implemented in such a way that there is a single
entry point per source file.  This avoids having the 
linker being forced to pull large object files in their
entirety into an application when the application references
a single symbol.  In the event you discover an RTEMS method
that is included in your executable but never entered, please
let us know.  It might be an opportunity to break a dependency
and shrink many RTEMS applications.

RTEMS based applications must somehow provide memory
for RTEMS' code and data space.  Although RTEMS' data space must
be in RAM, its code space can be located in either ROM or RAM.
In addition, the user must allocate RAM for the RTEMS RAM
Workspace.  The size of this area is application dependent and
can be calculated using the formula provided in the Memory
Requirements chapter of the Applications Supplement document
for a specific target processor.

All private RTEMS data variables and routine names used by
RTEMS begin with the underscore ( _ ) character followed by an
upper-case letter.  If RTEMS is linked with an application, then
the application code should NOT contain any symbols which begin
with the underscore character and followed by an upper-case
letter to avoid any naming conflicts.  All RTEMS directive names
should be treated as reserved words.

@section Sizing the RTEMS RAM Workspace

The RTEMS RAM Workspace is a user-specified block of
memory reserved for use by RTEMS.  The application should NOT
modify this memory.  This area consists primarily of the RTEMS
data structures whose exact size depends upon the values
specified in the Configuration Table.  In addition, task stacks
and floating point context areas are dynamically allocated from
the RTEMS RAM Workspace.

The @code{rtems/confdefs.h} mechanism calcalutes the size
of the RTEMS RAM Workspace automatically.  It assumes that
all tasks are floating point and that all will be allocated
the miminum stack space.  This calculation also automatically
includes the memory that will be allocated for internal use
by RTEMS.  The following macros may be set
by the application to make the calculation
of memory required more accurate:

@itemize @bullet

@item @code{CONFIGURE_MEMORY_OVERHEAD}
@item @code{CONFIGURE_EXTRA_TASK_STACKS}

@end itemize

The starting address of the RTEMS RAM Workspace must
be aligned on a four-byte boundary.  Failure to properly align
the workspace area will result in the 
@code{@value{DIRPREFIX}fatal_error_occurred}
directive being invoked with the
@code{@value{RPREFIX}INVALID_ADDRESS} error code.

The file @code{<rtems/confdefs.h>} will calculate the 
value that is specified as the @code{work_space_size}
parameter of the Configuration Table. There are many
parameters the application developer can specify to
help @code{<rtems/confdefs.h>} in its calculations.  Correctly
specifying the application requirements via parameters
such as @code{CONFIGURE_EXTRA_TASK_STACKS} and
@code{CONFIGURE_MAXIMUM_TASKS} is critical.

The allocation of objects can operate in two modes. The default mode
has an object number ceiling. No more than the specified number of
objects can be allocated from the RTEMS RAM Workspace. The number of objects
specified in the particular API Configuration table fields are
allocated at initialisation. The second mode allows the number of
objects to grow to use the available free memory in the RTEMS RAM Workspace.

The auto-extending mode can be enabled individually for each object
type by using the macro @code{rtems_resource_unlimited}. This takes a value
as a parameter, and is used to set the object maximum number field in
an API Configuration table. The value is an allocation unit size. When
RTEMS is required to grow the object table it is grown by this
size. The kernel will return the object memory back to the RTEMS RAM Workspace
when an object is destroyed. The kernel will only return an allocated
block of objects to the RTEMS RAM Workspace if at least half the allocation
size of free objects remain allocated. RTEMS always keeps one
allocation block of objects allocated. Here is an example of using 
@code{rtems_resource_unlimited}:

@example
#define CONFIGURE_MAXIMUM_TASKS rtems_resource_unlimited(5)
@end example

The user is cautioned that future versions of RTEMS may not have the
same memory requirements per object. Although the value calculated is
suficient for a particular target processor and release of RTEMS,
memory usage is subject to change across versions and target
processors.  To avoid problems, the user should accurately 
specify each configuration parameter and allow
@code{<rtems/confdefs.h>} to calculate the memory requirements.
The memory requirements are likely to change each
time one of the following events occurs:

@itemize @bullet
@item a configuration parameter is modified,
@item task or interrupt stack requirements change,
@item task floating point attribute is altered,
@item RTEMS is upgraded, or
@item the target processor is changed.
@end itemize

Failure to provide enough space in the RTEMS RAM
Workspace will result in the 
@code{@value{DIRPREFIX}fatal_error_occurred} directive
being invoked with the appropriate error code.
