/* prjConfig.c - dynamically generated configuration file */


/*
GENERATED: Thu Nov 18 11:01:18 +0900 2021
DO NOT EDIT - file is regenerated whenever the project changes.
This file contains the non-BSP system initialization code
to Create a bootable VxWorks image (custom configured).
*/


/* includes */

#include <vxWorks.h>
#ifdef _WRS_CONFIG_COMPAT69
#   include <config.h>
#else /* !_WRS_CONFIG_COMPAT69 */
#   include <prjParams.h>
#endif /* _WRS_CONFIG_COMPAT69 */
#include <altivecLib.h>
#include <applUtilLib.h>
#include <arch/ppc/archPpc.h>
#include <arch/ppc/vxPpcLib.h>
#include <boardLib.h>
#include <cacheLib.h>
#include <classLib.h>
#include <condVarLib.h>
#include <cplusLib.h>
#include <dataCollectorLib.h>
#include <dbgLib.h>
#include <dosFsLib.h>
#include <drv/erf/erfLib.h>
#include <drv/manager/device.h>
#include <endLib.h>
#include <envLib.h>
#include <etherMultiLib.h>
#include <eventLib.h>
#include <excLib.h>
#include <fioLib.h>
#include <fsEventUtilLib.h>
#include <fsMonitor.h>
#include <hashLib.h>
#include <hookLib.h>
#include <hostLib.h>
#include <hwif/util/vxbIsrDeferLib.h>
#include <hwif/util/vxbParamLib.h>
#include <hwif/vxBus.h>
#include <intLib.h>
#include <ioLib.h>
#include <iosLib.h>
#include <jobQueueLib.h>
#include <loadElfLib.h>
#include <logLib.h>
#include <lstLib.h>
#include <math.h>
#include <miiBus.h>
#include <moduleLib.h>
#include <msgQLib.h>
#include <mux2Lib.h>
#include <muxLib.h>
#include <net/mbuf.h>
#include <netBufLib.h>
#include <netLib.h>
#include <nfs/nfs2Drv.h>
#include <nfs/nfs2Lib.h>
#include <nfs/nfsCommon.h>
#include <nfs/nfsDebug.h>
#include <objLib.h>
#include <private/adrSpaceLibP.h>
#include <private/condVarLibP.h>
#include <private/coprocLibP.h>
#include <private/cpcLibP.h>
#include <private/dbgLibP.h>
#include <private/eventDefsP.h>
#include <private/eventPointLibP.h>
#include <private/eventPointStubLibP.h>
#include <private/excLibP.h>
#include <private/fioLibP.h>
#include <private/isrLibP.h>
#include <private/jobLibP.h>
#include <private/kernelBaseLibP.h>
#include <private/kernelLibP.h>
#include <private/kwriteLibP.h>
#include <private/ledLibP.h>
#include <private/logLibP.h>
#include <private/memPartLibP.h>
#include <private/moduleHookLibP.h>
#include <private/offsetsP.h>
#include <private/pgMgrLibP.h>
#include <private/pgPoolLibP.h>
#include <private/pgPoolPhysLibP.h>
#include <private/pgPoolVirtLibP.h>
#include <private/poolLibP.h>
#include <private/qLibP.h>
#include <private/randomNumGenP.h>
#include <private/seqDrvP.h>
#include <private/shellLibP.h>
#include <private/svDataCollectorLibP.h>
#include <private/timerLibP.h>
#include <private/tipLibP.h>
#include <private/tlsLibP.h>
#include <private/vmLibP.h>
#include <private/vxMemProbeLibP.h>
#include <private/workQLibP.h>
#include <private/wvFileUploadPathLibP.h>
#include <private/wvUploadPathP.h>
#include <ptyDrv.h>
#include <rBuffLib.h>
#include <rawFsLib.h>
#include <rebootLib.h>
#include <remLib.h>
#include <selectLib.h>
#include <semLib.h>
#include <shellInterpLib.h>
#include <sigLib.h>
#include <sigevent.h>
#include <sockLib.h>
#include <stdio.h>
#include <string.h>
#include <subsys/int/vxbIntLib.h>
#include <subsys/int/vxbIsrHandler.h>
#include <symLib.h>
#include <sysLib.h>
#include <sysSymTbl.h>
#include <syslog.h>
#include <taskHookLib.h>
#include <taskLib.h>
#include <tffs/backgrnd.h>
#include <tffs/dosformt.h>
#include <tffs/fatlite.h>
#include <tffs/flbase.h>
#include <tffs/flbuffer.h>
#include <tffs/flcustom.h>
#include <tffs/flflash.h>
#include <tffs/flsocket.h>
#include <tffs/flsysfun.h>
#include <tffs/flsystem.h>
#include <tffs/fltl.h>
#include <tffs/pcic.h>
#include <tffs/reedsol.h>
#include <tffs/stdcomp.h>
#include <tffs/tffsDrv.h>
#include <tickLib.h>
#include <time.h>
#include <ttyLib.h>
#include <tyLib.h>
#include <unldLib.h>
#include <vxAtomicLib.h>
#include <vxLib.h>
#include <vxdbgLibInit.h>
#include <wdLib.h>
#include <wvLib.h>
#include <wvTmrLib.h>


/* imports */

IMPORT char etext [];                   /* defined by loader */
IMPORT char end [];                     /* defined by loader */
IMPORT char edata [];                   /* defined by loader */

/* forward declarations */

IMPORT void vxbNorFlashAmdCmdSetRegister(void);
IMPORT void usrBoardLibInit (void );
IMPORT void usrAimCpuInit (void);
IMPORT void excIntNestLogInit (void);                     IMPORT _RType taskMsrDefault;    
IMPORT void vxbClkLibInit(void);
IMPORT STATUS vxbDmaLibInit (void);
IMPORT void endEtherHdrInit (void);
IMPORT STATUS eventPointLibInit (void);
IMPORT STATUS eventPointStubLibInit (void);
IMPORT void usrFdtInit (void *, int);
IMPORT STATUS vxbIntLibInit (UINT32);
IMPORT STATUS vxbIsrHandlerInit (UINT32, UINT32);
extern STATUS logInit (int, int, int);
extern void miiBusMonitorTaskInit (void);
extern void miiBusLibInit (void);
IMPORT void usrMtdInit (char *);
IMPORT void vxbFlashStubInit (char *);
IMPORT STATUS hostnameSetup (char * );
IMPORT STATUS objInfoInit (void);
IMPORT void pmapInit (void);
extern STATUS umaskLibInit (int);
extern STATUS pxUserGroupLibInit (void);
IMPORT STATUS rpcInit (void);
IMPORT void secHashMd5OpensslInit(void);
IMPORT void secHashSha1OpensslInit(void);
IMPORT void secHashSha256OpensslInit(void);
IMPORT void semBCreateLibInit (void);
IMPORT void semCCreateLibInit (void);
IMPORT void semMCreateLibInit (void);
extern int sigeventLibInit (void);
IMPORT void usrStacktraceInit(void);
extern void syslogLibInit (void);
IMPORT void taskCreateLibInit (void);
IMPORT STATUS tyLibInit (int xoffThresh, int xonThresh, size_t wrtThresh, BOOL monTrapDisable);
extern void usrAppInit (void);
IMPORT STATUS vxbAuxClkLibInit (void);
IMPORT STATUS vxbSysClkLibInit (void);
extern void vxCpuLibInit (void);
IMPORT STATUS vxIpiLibInit (void);
IMPORT void vxmux_mux_mblk_init (void);


/* BSP_STUBS */



/* configlettes */

#include <sysComms.c>
#include <edrDefaultPolicy.c>
#include <edrStub.c>
#include <intrinsics.c>
#include <ipcom_config.c>
#include <ipcom_ipd_config.c>
#include <ipnet_config.c>
#include <ipnet_radvd_config.c>
#include <iptcp_config.c>
#include <sysClkInit.c>
#include <usrAimCpu.c>
#include <usrAltivec.c>
#include <usrBanner.c>
#include <usrBoardLibInit.c>
#include <usrBootLine.c>
#include <usrBreakpoint.c>
#include <usrCache.c>
#include <usrCoprocs.c>
#include <usrDosfs.c>
#include <usrFdt.c>
#include <usrIo.c>
#include <usrIsrDefer.c>
#include <usrKernel.c>
#include <usrKernelStack.c>
#include <usrMemDesc.c>
#include <usrMmuInit.c>
#include <usrMtd.c>
#include <usrNetApplUtil.c>
#include <usrNetBoot.c>
#include <usrNetDaemon.c>
#include <usrNetEndLib.c>
#include <usrNetHostTblCfg.c>
#include <usrNfs.c>
#include <usrPmap.c>
#include <usrRtpBaseLib.c>
#include <usrSemLib.c>
#include <usrSerial.c>
#include <usrShell.c>
#include <usrSmp.c>
#include <usrStacktrace.c>
#include <usrStandalone.c>
#include <usrStartup.c>
#include <usrSysSymTbl.c>
#include <usrSyslog.c>
#include <usrTffs.c>
#include <usrTip.c>
#include <usrVxbTimerSys.c>
#include <usrVxdbg.c>
#include <usrWindview.c>


/******************************************************************************
*
* usrKernelExtraInit - Extended kernel facilities
*/

void usrKernelExtraInit (void)
    {
                                        /* This component includes the hash library. This library supports the creation and maintenance of a chained hash table. Hash tables efficiently store hash nodes for fast access. They are frequently used for symbol tables, or other name-to-identifier functions. A chained hash table is an array of singly-linked list heads, with one list head per element of the hash table. During creation, a hash table is passed two user-definable functions, the hashing function, and the hash node comparator. The hashTblCreate( ) function creates a hash table. The hashTblInit( ) function initializes a hash table. The hashTblDelete() function deletes a hash table. The hashTblTerminate() function terminates a hash table. The hashTblDestroy() function destroys a hash table. The hashTblPut() function puts a hash node into the specified hash table. The hashTblFind() function finds a hash node that matches the specified key. The hashTblRemove() function removes a hash node from a hash table. The hashTblEach() function calls a function for each node in a hash table. The hashFuncIterScale() function provides an iterative scaling hashing function for strings. The hashFuncModulo() function provides a hashing function using a remainder technique. The hashFuncMultiply() function is a multiplicative hashing function. The hashKeyCmp() function compares keys as 32-bit identifiers. The hashKeyStrCmp() function compares keys based on strings they point to. */
    excSigLibInit();                    /* This component enables signal generation on an exception. */
    sigInit (POSIX_SIGNAL_MODE);        /* This component provides the sigLib library. This library provides the signal interfaces in the RTP environment. The signal model in user-mode is designed to follow the POSIX process model. Signals alter the flow of control of tasks by communicating asynchronous events within or between task contexts. Using the APIs provided by this library, signals can be sent from an RTP task to either another RTP or a public task in another RTP. Signals can be sent to an RTP using the kill() or raise() functions, and will be caught by any task in that RTP which has unmasked that signal. Signals can also be sent to specific tasks in the current or another RTP using the taskKill() function. Tasks that receive signals can either be waiting synchronously for the signal, or can have their signal mask setup to unblock that signal. If there is no such task waiting for the signal, the signal remains pended in the RTP and is delivered when one such task becomes available. */
    sigeventLibInit ();                 /* This component provides kernel signal event support. This is required for SIGEV_THREAD support in an RTP. */
                                        /* Includes the POSIX directory utilities. */
    pxUserGroupLibInit();               /* This component adds support for POSIX users and groups in the kernel environment. */
    clockLibInit (HIGH_RES_POSIX_CLOCK, POSIX_CLOCK_TIMER); /* This component includes support for POSIX clocks. */
    timerLibInit ();                    /* This component provides support for POSIX timers. */
    timerOpenInit ();                   /* This component provides the open/close/unlink interfaces for timers. */
    randomSWNumGenInit ();              /* This component provides the randomSWNGenLib library. This library provides the implementation to generate a software random number. When an application requests random bytes, the content of the destination buffer is first used as random seed. Thereafter, the random state buffer is hashed and the hash output is returned as random bytes. If more bytes are requested than the hash output size, the hash output is used as seed and thereafter the random state buffer is hashed again. This process is repeated until the requested number of random bytes has been generated. */
    jobQueueLibInit();                  /* Includes the jobQueueLib library. It provides a prioritized work deferral mechanism. */
    symLibInit ();                      /* Set of routines to manipulate symbols and symbol tables */
    }



/******************************************************************************
*
* usrIosExtraInit - extended I/O system
*/

void usrIosExtraInit (void)
    {
    excInit (MAX_ISR_JOBS);             /* This component includes the excLib facility. This generic exception handling facility includes the following functions: excInit(), which initializes the exception handling package; excJobAdd(), which requests a task-level function call from the interrupt level; excJobAddDefer(), which requests a deferred task-level function call; and excHookAdd(), which specifies a function to be called with exceptions. */
    syslogLibInit ();                   /* This component provides the system logging facility. The syslogLib facility can be configured to log messages before it is initialized. These messages are stored in static memory until initialization is complete and the system logger has started (tLogTask). As the POSIX clocks facility is also not yet initialized when log messages are written to static memory, the timestamp assigned to these messages is not accurate (it starts from 1970-01-01T00:00:00.000000Z). */
    logInit (consoleFd, MAX_LOG_MSGS, LOG_TASK_PRIORITY); /* This component provides the logLib library. This library handles message logging. It is usually used to display error messages on the system console, but such messages can also be sent to a disk file or printer. The logMsg() and logTask() functions are the basic components of the logging system. The logMsg() function has the same calling sequence as printf(), but instead of formatting and outputting the message directly, it sends the format string and arguments to a message queue. The logTask() task waits for messages on this message queue. It formats each message according to the format string and arguments in the message, prepends the ID of the sender, and writes it on one or more file descriptors that have been specified as logging output streams (by logInit() or subsequently set by logFdSet() or logFdAdd()). */
    stdioInit ();                       /* This component includes the buffered IO library.  */
    fioLibInit ();                      /* This component includes the formatting for printf, scanf, and so forth. */
    floatInit ();                       /* This component allows printf and other routines to format floats correctly.  */
    devInit (DEVICE_MANAGER_MAX_NUM_DEVICES); /* Device Manager */
    xbdInit ();                         /* This component includes support for an extended block device.  */
    fsMonitorInit ();                   /* This component includes the file system monitor.  */
    fsEventUtilLibInit ();              /* This component includes the file system event utilities.  */
    usrDosfsInit (DOSFS_DEFAULT_MAX_FILES, DOSFS_DEFAULT_CREATE_OPTIONS); /* MS-DOS-Compatible File System: dosFs main module */
    dosFsShowInit();                    /* Includes the show routines for Dos FS provided by the dosFsShow library. */
    rawFsInit (NUM_RAWFS_FILES);        /* Raw block device file system interface */
    ptyDrv ();                          /* Allows communication between processes */
    vxbFlashStubInit (VXBFLASH_CFG_STR); /* stub for vxbus NOR/SPI flash driver */
    tffsDrv ();                         /* This component is the core TrueFFS Component. Including this component triggers the correct sequence of events, at boot time, for initializing this product. It also ensures that the socket driver is included in your system. It allows a DOS file system to placed in Flash memory. */
    usrTffsConfig (TFFS_DRIVE_NUMBER, TFFS_REMOVABLE, TFFS_MOUNT_POINT ); /* Including this component adds automatic detection (on booting) and mounting of existing formatted TrueFFS drives. */
    usrBootLineParse ((char *)BOOT_LINE_ADRS); /* This component provides support to parse some boot device configuration information. */
    }



/******************************************************************************
*
* usrShowInit - Enable object show routines
*/

void usrShowInit (void)
    {
    taskShowInit ();                    /* This component provides functions to show task-related information, such as task status, register values, and so forth. Task information is crucial as a debugging aid and user-interface convenience during the development cycle of an application. The taskShow() and taskRegsShow() functions are used to display task information. It is important to keep in mind that tasks may change their state or even get deleted between the time the information is gathered and the time it is utilized. Information provided by these functions should therefore be viewed as a snapshot of the system, and not relied upon unless the task is consigned to a known state, such as suspended. */
    memShowInit ();                     /* This component includes the memShow library. This library contains memory partition information display functions. The memShow() function shows blocks and statistics for the current heap partition. The memPartShow() function shows available and allocated memory in the specified partition. */
    semShowInit ();                     /* This component includes the semShow library in your project. This library provides functions to show semaphore statistics, such as semaphore type, semaphore queuing method, tasks pended, and so forth. Functions in this library are meant to be used as debugging aids that display semaphore information to standard output. Due to the dynamic nature of semaphore operations, the information displayed may no longer be accurate by the time it is provided. */
    symShowInit ();                     /* Routines to display information about symbols and symbol tables */
                                        /* This component provides the handleShow library. This library provides functions to show handle information. */
    coprocShowInit ();                  /* task coprocessor registers */
    }



/******************************************************************************
*
* usrWindviewInit - 
*/

void usrWindviewInit (void)
    {
    windviewConfig ();                  /* Initialize and control event logging of the System Viewer. */
    wvTmrRegister ((UINTFUNCPTR) seqStamp,					(UINTFUNCPTR) seqStampLock,					(FUNCPTR) seqEnable,					(FUNCPTR) seqDisable,					(FUNCPTR) seqConnect,					(UINTFUNCPTR) seqPeriod,					(UINTFUNCPTR) seqFreq); /* Supports sequential timestamping. This is recommended if you are new to the System Viewer. */
    rBuffLibInit ();                    /* System Viewer ring of buffers for event logging */
    wvFileUploadPathLibInit ();         /* Initialize the path for the file upload. */
    }



/******************************************************************************
*
* usrLoaderInit - The target loader initialization sequence.
*/

void usrLoaderInit (void)
    {
    moduleLibInit ();                   /* This component includes the support library for module entities. */
    loadElfInit ();                     /* ELF loader */
    loadLibInit (STORE_ABS_SYMBOLS);    /* This component provides support to download modules to running targets. */
    unldLibInit ();                     /* This component enables removal of dynamically-loaded modules. */
    moduleHookLibInit ();               /* This component includes pluggable hooks to extend the loader/unloader behavior. */
    }



/******************************************************************************
*
* usrSymTblInit - Enable onboard symbol tables
*/

void usrSymTblInit (void)
    {
    usrSysSymTblInit ();                /* initialize system symbol table */
    usrStandaloneInit ();               /* Preferred method if not booting from the network */
    }



/******************************************************************************
*
* usrShellInit - The kernel shell initialization sequence
*/

void usrShellInit (void)
    {
    shellLibInit ();                    /* This component includes the shell core files. */
    dbgLibInit (DEBUG_STACK_TRACE_BUF_SIZE); /* This component includes the primary interactive functions for VxWorks. The following facilities are provided: task breakpoints, task single-stepping, symbolic disassembly, symbolic task stack tracing. */
    ledModeRegister (viLedLibInit);     /* This component provides an editing mode similar to the vi editor. */
    shellInterpRegister (shellInterpCInit); /* This component provides the C interpreter for the kernel shell. */
    usrShell ();                        /* This component includes the target-resident kernel shell, which is spawned as a task. Any function that is invoked from the kernel shell, rather than spawned, runs in the shell's context. The task name for a shell on the console is "tShell0". The kernel shell is re-entrant, and more than one shell task can run at a time (hence the number suffix). In addition, if a user logs in remotely (using rlogin or telnet) to a VxWorks target, the name reflects that fact as well. For example, "tShellRem1". The "tShell" basename is configurable, see the VxWorks 7 Kernel Shell User's Guide. */
    }



/******************************************************************************
*
* usrToolsInit - Software development tools
*/

void usrToolsInit (void)
    {
    eventPointStubLibInit ();           /* stub eventpoint implementation */
    eventPointLibInit ();               /* eventpoints instrumentation */
    dataCollectorLibInit ();            /* This component provides data collectors for generic analysis tools. See the dataCollectorLib entry in the VxWorks 7 Kernel DEBUG ANALYSIS API Reference for detailed description of the different routines in this library.  */
    svDataCollectorLibInit ();          /* Data collectors for System Viewer */
    usrLoaderInit ();                   /* The target loader initialization sequence. */
    usrStacktraceInit();                /* Stack tracing logic */
    usrSymTblInit ();                   /* Enable onboard symbol tables */
    usrVxdbgInit (VXDBG_EVT_TASK_PRIORITY,						   VXDBG_EVT_TASK_OPTIONS,						   VXDBG_EVT_TASK_STACK_SIZE); /* Support for the runtime debug library */
    usrWindviewInit ();                 /* usrWindviewInit */
    tlsLoadLibInit ();                  /* __thread variables loader support */
    usrTipInit (TIP_CONFIG_STRING, TIP_ESCAPE_CHARACTER); /* interactive utility to connect to and manage multiple serial lines */
    usrShowInit ();                     /* Enable object show routines */
    usrShellInit ();                    /* The kernel shell initialization sequence */
    }



/******************************************************************************
*
* usrKernelCreateInit - Object creation functions
*/

void usrKernelCreateInit (void)
    {
    semDeleteLibInit ();                /* This component provides the semDeleteLib library that contains functions that terminate and delete semaphores. The semDelete() call terminates a semaphore and deallocates any associated memory. The deletion of a semaphore unblocks tasks pended on that semaphore; the functions that were pended return ERROR. Take care when deleting semaphores, particularly those used for mutual exclusion, to avoid deleting a semaphore out from under a task that already has taken (owns) that semaphore. Applications should adopt the protocol of only deleting semaphores that the deleting task has successfully taken. */
    taskCreateLibInit ();               /* This component provides the capability to dynamically instantiate and delete tasks. */
    msgQCreateLibInit ();               /* This component provides the msgQCreateLib library. This library contains functions for creating and deleting message queues. The functions to initialize and operate on message queues are implemented in msgQLib. */
    wdCreateLibInit ();                 /* This component provides wdCreateLib. This library provides creation and deletion functions for the watchdog facility. The functions to initialize and operate on watchdogs are implemented in wdLib. */
    }



/******************************************************************************
*
* usrKernelCoreInit - Core kernel facilities
*/

void usrKernelCoreInit (void)
    {
    eventLibInit (VXEVENTS_OPTIONS);    /* This component provides event facilities. VxWorks events provide a means of communication and synchronization between tasks and other tasks, interrupt service routines (ISRs) and tasks, semaphores and tasks, and message queues and tasks. Events can be sent explicitly by tasks and ISRs, and can be sent when message queues or semaphores are free. Only tasks can receive events. Events can be used as a lighter-weight alternative to binary semaphores for task-to-task and ISR-to-task synchronization (because no object must be created). They can also be used to notify a task that a semaphore has become available, or that a message has arrived on a message queue. The events facility provides a mechanism for coordinating the activity of a task using up to thirty-two events that can be sent to it explicitly by other tasks and ISRs, or when semaphores and message queues are free. A task can wait on multiple events from multiple sources. Events thereby provide a means for coordination of a complex matrix of activity without allocation of additional system resources. */
                                        /* This component provides a library that provides the interface to VxWorks binary semaphores. Binary semaphores are the most versatile, efficient, and conceptually simple type of semaphore. They can be used to control mutually exclusive access to shared devices or data structures, or synchronize multiple tasks, or task-level and interrupt-level processes. Binary semaphores form the foundation of numerous VxWorks facilities. */
                                        /* This component provides the semCLib library. This library provides the interface to VxWorks counting semaphores. Counting semaphores are useful for guarding multiple instances of a resource. A counting semaphore can be viewed as a cell in memory whose contents keep track of a count. */
                                        /* This component provides the semRWLib and windSemRWLib libraries. semRWLib provides the interface to VxWorks reader/writer semaphores. Reader/writer semaphores provide a method of synchronizing groups of tasks that can be granted concurrent access to a resource with those tasks that require mutually exclusive access to that resource. Typically, this correlates to those tasks that intend to modify a resource and those which intend only to view it. windSemRWLib contains the implementation of the windSemRWDelete() function. A call to windSemRWDelete() unblocks any tasks pending on a read/write semaphore. If the deletion safety option is enabled, any and all owners have their safety count decremented. If the inversion safe option is enabled, any and all owners have their priority inheritance information updated. */
    semOpenInit ();                     /* This component provides the open/close/unlink interfaces for semaphores. */
    condVarOpenInit ();                 /* This component provides the open/close/unlink interfaces for condition variables. */
    msgQLibInit ();                     /* This component provides message queue support using the msgQLib library. This library contains functions for creating and using message queues, the primary inter-task communication mechanism in VxWorks. Message queues allow a variable number of messages (varying in length) to be queued in first-in-first-out (FIFO) order. Any task or interrupt service routine (ISR) can send messages to a message queue. Any task can receive messages from a message queue. Multiple tasks can send to, and receive from, the same message queue. Full-duplex communication between two tasks generally requires two message queues, one for each direction. For more information, see the reference information for msgQLib. */
    msgQOpenInit ();                    /* This component provides the open/close/unlink interfaces for message queues. */
    wdLibInit ();                       /* This component provides a general watchdog timer facility. Any task can create a watchdog timer and use it to run a specified function in the context of the system-clock ISR, after a specified delay. Once a timer has been created with wdCreate(), it can be started with wdStart(). The wdStart() function specifies what function to run, a parameter for that function, and the amount of time (in ticks) before the function is to be called. The timeout value is in ticks as determined by the system clock; see sysClkRateSet() for more information. After the specified delay ticks have elapsed, unless wdCancel() is called first to cancel the timer, the timeout function is invoked with the parameter specified in the wdStart() call. The timeout function is invoked whether the task which started the watchdog is running, suspended, or deleted. The timeout function executes only once per wdStart() invocation; there is no need to cancel a timer with wdCancel() after it has expired, or in the expiration callback itself. Note that the timeout function is invoked at interrupt level, rather than in the context of the task. Thus, there are restrictions on what the function can do. Watchdog functions are constrained to the same rules as interrupt service routines. For example, they cannot take semaphores, issue other calls that can block, or use I/O system functions like printf(). Note: You can defer watchdog function invocation. As such, isrIdCurrent is either a valid ISR_ID or is NULL in the case of deferral. */
    taskOpenInit ();                    /* This component provides the open/close/unlink interfaces for tasks. */
    vxdbgHooksInit ();                  /* hooks for the runtime debug library */
    }



/******************************************************************************
*
* usrClkInit - Clock system initialization.
*/

void usrClkInit (void)
    {
    usrVxbTimerSysInit();               /* This component includes support for the VxBus timer. */
    vxbSysClkLibInit();                 /* This component includes support for the VxBus system clock. */
    vxbAuxClkLibInit();                 /* This component includes support for the VxBus auxiliary clock. */
    sysClkInit ();                      /* This component starts the system clock. */
    }



/******************************************************************************
*
* usrNetworkInit0 - Initialize the network subsystem for drivers
*/

void usrNetworkInit0 (void)
    {
    netBufLibInitialize (NETBUF_LEADING_CLSPACE_DRV); /* Network Buffer Library */
    netBufPoolInit ();                  /* netBufLib Generic Pool */
    linkBufPoolInit ();                 /* Network Buffer Library */
    vxmux_null_buf_init ();             /* Minimal clusterless network pool implementation for IPCOM */
    usrNetDaemonInit(NET_JOB_NUM_CFG,                        NET_TASK_DEFAULT_PRIORITY, NET_TASK_OPTIONS,                        NET_TASK_STACKSIZE); /* This component includes support for the network daemon. The network daemon, tNet0, performs network driver and network protocol processing for the VxWorks network stack. */
    muxCommonInit();                    /* MUX common support (all protocol and device styles) */
    mux2LibInit();                      /* Support mux2Bind() protocols and their APIs */
    vxmux_mux_mblk_init ();             /* MUX private support for M_BLK/Ipcom_pkt conversion */
    mux2OverEndInit();                  /* Support mux2Bind() protocols over END-style devices */
    endEtherHdrInit ();                 /* M_BLK ethernet/802.3 header build and parse */
    endLibInit();                       /* Support for END-style network devices. */
    }



/******************************************************************************
*
* usrIosCoreInit - core I/O system
*/

void usrIosCoreInit (void)
    {
    iosInit (NUM_DRIVERS, NUM_FILES, "/null"); /* Basic IO system component */
    iosPathLibInit ();                  /* File System IO component */
    iosRmvLibInit ();                   /* Removable IO component */
    iosPxLibInit (IOS_POSIX_PSE52_MODE); /* POSIX IO component */
    iosRtpLibInit ();                   /* RTP IO component */
                                        /* Miscellaneous IO component */
    selectInit (NUM_FILES);             /* This provides the kernel selectLib library which includes select() and related functions. */
    usrIsrDeferInit ();                 /* This component provides the ISR defferal library used by interrupt service routines to defer interrupt processing from interrupt context to task context. Device drivers use this library by allocating a deferral task, and then enqueueing work on the task's work queue. This library is designed to work with VxBus-compliant device drivers.  */
    tyLibInit (TYLIB_XOFF_PCNT, TYLIB_XON_PCNT, 				TYLIB_WRT_THRESHLD, TYLIB_MON_TRAP_DISABLE); /* Allows communication between processes */
    ttyDrv ();                          /* Provides terminal device access to serial channels. */
    coprocLibInit();                    /* generalized coprocessor support */
    }



/******************************************************************************
*
* usrNetHostInit - 
*/

void usrNetHostInit (void)
    {
    usrNetHostTblSetup ();              /* host table support */
    hostnameSetup (pTgtName);           /* assign local hostname to target */
    }



/******************************************************************************
*
* usrNetRemoteInit - 
*/

void usrNetRemoteInit (void)
    {
    remLibInit(RSH_STDERR_SETUP_TIMEOUT); /* Remote Command Library */
    }



/******************************************************************************
*
* usrNetAppInit - 
*/

void usrNetAppInit (void)
    {
    rpcInit ();                         /* This daemon is a Remote Procedure Call (RPC) server that acts as a central registrar for RPC services running on the same machine. RPC clients query the daemon to find out how to contact the various servers. */
    usrNfsInit (2);                                                              usrNfs2CacheInit (NFS2_CLIENT_CACHE_DEFAULT_NUM_LINES,                                         NFS2_CLIENT_CACHE_DEFAULT_LINE_SIZE,                                         NFS2_CLIENT_CACHE_DEFAULT_OPTIONS); /* This component provides nfs2Lib and nfs2Drv, which provide support for an NFS version two client. Using this client, you can mount exported NFS (version two) directories to your VxWorks target. This component requires the INCLUDE_CORE_NFS_CLIENT component. This component initializes the NFS v2 client at boot time with a call to nfs2Drv( ), as well as a call to nfsAuthUnixSet( ) as follows: nfsAuthUnixSet ( sysBootParams.hostName, NFS_USER_ID, NFS_GROUP_ID, 0, (int *) 0); Values for the NFS_USER_ID and NFS_GROUP_ID parameters are taken from the corresponding INCLUDE_CORE_NFS_CLIENT component parameters. */
    nfsDebugInit(NFS_DEBUG_LEVEL);      /* This component implements the Network File System (NFS) debug information.  */
    }



/******************************************************************************
*
* usrNetworkInit - Initialize the reset of the network subsystem
*/

void usrNetworkInit (void)
    {
    usrNetBoot ();                      /* Copy boot parameters for futher use by network */
    usrNetmaskGet ();                   /* Extracts netmask value from address field */
    usrNetHostInit ();                  /* initialize host table */
    usrNetRemoteInit ();                /* initialize network remote I/O access */
    usrNetEndLibInit();                 /* Support for network devices using MUX/END interface. */
    ipcom_config_usr_create ();         /* Includes the IPCOM user-side functions. */
    ipcom_config_create ();             /* Includes VxWorks IPCOM support. */
    usrNetAppInit ();                   /* initialize network application protocols */
    }



/******************************************************************************
*
* usrSecHashInit - Initialize the secHash providers
*/

void usrSecHashInit (void)
    {
    secHashMd5OpensslInit();            /* Registers an MD5 provider for the secHash MD5 API. The implementation is based on the low-level openssl APIs. This provider does not require the full openssl lib to be linked in. */
    secHashSha1OpensslInit();           /* Registers an SHA1 provider for the secHash SHA1 API. The implementation is based on the low-level openssl APIs. This provider does not require the full openssl lib to be linked in. */
    secHashSha256OpensslInit();         /* Registers an SHA256 provider for the secHash SHA256 API. The implementation is based on the low-level openssl APIs. This provider does not require the full openssl lib to be linked in. */
    }



/******************************************************************************
*
* usrRoot - Entry point for post-kernel initialization
*/

void usrRoot (char *pMemPoolStart, unsigned memPoolSize)
    {
    usrKernelCoreInit ();               /* Core kernel facilities */
    poolLibInit ();                     /* This component includes the Memory Pool library. Pools provide a fast and efficient memory management when an application uses a large number of identically sized memory blocks (for example, structures and objects) by minimizing the number of allocations from a memory partition. The use of pools also reduces possible fragmentation caused by frequent memory allocation and freeing. A pool is a dynamic set of statically sized memory blocks. All blocks in a pool are of the same size. The size of blocks are specified at pool creation and all the blocks are aligned on the block size; the block size must be a power of 2. */
    memInit (pMemPoolStart, memPoolSize,                                  MEM_PART_DEFAULT_OPTIONS); /* This component provides the memLib library. This library provides the API for allocating and freeing blocks of memory of arbitrary size from an RTP heap. This library implements an RTP heap as a dedicated memory partition. One private heap is created automatically for every RTP. The library provides ANSI allocation functions and enhanced memory management features, including error handling and aligned allocation. Most of the memLib functions are simple wrappers to the memory partition management functions which implement the actual memory management functionalty. For more information about the memory partition management facility, see the reference entry for memPartLib. */
    memPartLibInit (pMemPoolStart, memPoolSize); /* This component includes the core memory partition manager. */
    kProxHeapInit (pMemPoolStart, memPoolSize); /* This component provides the kProxHeapLib library. This library provides the function that initializes the kernel proximity heap partition. The kernel proximity heap is a memory partition created in the kernel system memory region. */
    pgPoolLibInit();                    /* Generic Page Pool Allocator */
    pgPoolVirtLibInit();                /* Page Pool Allocator for Virtual Space */
    pgPoolPhysLibInit();                /* Page Pool Allocator for Physical Space */
                                        /* This is the basic MMU component. It includes an API which is used for programmatic management of virtual memory. */
    usrMmuInit ();                      /* This component initializes the kernel's global MMU mappings according to the BSP's sysPhysMemDesc[ ] table. */
    pmapInit();                         /* This component provides the functionality to map or unmap physical address to the kernel/RTP context. */
    kCommonHeapInit (KERNEL_COMMON_HEAP_INIT_SIZE, KERNEL_COMMON_HEAP_INCR_SIZE); /* This component includes the kernel common heap which is the memory partition used by the kernel and kernel applications for dynamic memory allocation. Physical memory is allocated from the global RAM pool and virtual memory is allocated from the kernel virtual memory pool region. The heap is managed using the standard ANSI memory allocation functions, malloc(), free(), and so on. For more information, see the reference entries for memPartLib and memLib. */
    usrKernelCreateInit ();             /* Object creation functions */
    usrNetApplUtilInit ();              /* This component provides support for the stack and application logging utility. */
    memInfoInit ();                     /* This component provides the memInfo library. This library provides functions for obtaining information about a memory partition or the kernel heap. */
    envLibInit (ENV_VAR_USE_HOOKS);     /* This component provides the envLib library. This library provides a UNIX-compatible environment variable facility. Environment variables are created or modified with a call to putenv(): putenv ("variableName=value"); . The value of a variable can be retrieved with a call to getenv(), which returns a pointer to the value string. Tasks can share a common set of environment variables, or they can optionally create their own private environments, either automatically when the task create hook is installed, or by an explicit call to envPrivateCreate(). The task must be spawned with the VX_PRIVATE_ENV option set to receive a private set of environment variables. Private environments created by the task creation hook inherit the values of the environment of the task that called taskSpawn() (because task create hooks run in the context of the calling task). */
    edrStubInit ();                     /* This component provides the error detection and reporting (ED&R) error-injection stub. */
    boardInit();                        /* This component provides a function to initialize the board. */
    erfLibInit (ERF_MAX_USR_CATEGORIES, ERF_MAX_USR_TYPES, ERF_TASK_STACK_SIZE); /* Provides support for the event reporting framework for use by other libraries. */
    kernelIdleTaskActivate();           /* Add Idle Tasks Support (SMP Only) */
    usrSecHashInit ();                  /* Initialize the secHash providers */
    usrIosCoreInit ();                  /* core I/O system */
    usrNetworkInit0 ();                 /* Initialize the network subsystem for drivers */
    usrShellBannerInit ();              /* This component toggles shell-specific elements in the banner. */
    vxbClkLibInit();                    /* This component enables the VxBus clock device subsystem. */
    vxbDmaLibInit();                    /* This component provides a function to initialize the VxBus DMA subsystem. */
    vxbIsrHandlerInit (VXB_MAX_INTR_VEC, VXB_MAX_INTR_CHAIN); /* This component supports provides the VxBus ISR handler module initialization function. */
    vxbIntLibInit (VXB_MAX_INTR_DEFER); /* This component includes support for VxBus interrupt library initialization. */
    vxIpiLibInit ();                    /* This component includes inter-processor interrupts for symmetric multiprocessing (SMP) and asymmetric multiprocessing (AMP). */
    miiBusFdtLibInit();                 /* MII bus FDT subsystem */
    miiBusLibInit();                    /* Includes the MII bus subsystem.  */
    vxbParamLibInit ();                 /* This component provides the mechanism for drivers to obtain parameter values. Driver parameters are values which have a useful default value which can be overridden by BSPs (DTS file).  */
    vxbNorFlashAmdCmdSetRegister();     /* AMD/Spansion Nor Flash command set library */
    vxbLibInit ();                      /* This component provides a routines to initalize the VxBus subsystem. */
    excIntNestLogInit();                     vxMsrSet(vxMsrGet() | taskMsrDefault);                     sysIntEnableFlagSet (); /* Enable interrupts at appropriate point in root task */
    usrSerialInit ();                   /* This component provides initialization for the Serial I/O component. */
    usrClkInit ();                      /* Clock system initialization. */
    cpcInit ();                         /* CPUs Cross-Processor Call (SMP Only) */
    vxdbgCpuLibInit ();                 /* CPU control support for VxDBG */
                                        /* Architecture common modules for hardware floating point */
    pgMgrBaseLibInit();                 /* Basic Page Manager Library */
    usrKernelExtraInit ();              /* Extended kernel facilities */
    miiBusMonitorTaskInit();            /* This component spawns the MII bus monitor task. */
    usrMtdInit (MTD_CFG_STR);           /* Memory Technology Device(MTD) component */
    usrIosExtraInit ();                 /* extended I/O system */
    sockLibInit ();                     /* Socket API */
    selTaskDeleteHookAdd ();            /* selectInit, part 2, install task delete hook */
    cplusCtorsLink ();                  /* Ensures that compiler-generated initialization functions, including initializers for C++ static objects, are called at kernel start up time. */
    usrSmpInit ();                      /* Enable multi-processor capability of the kernel */
    usrNetworkInit ();                  /* Initialize the reset of the network subsystem */
    usrBanner ();                       /* This component displays the Wind River banner on startup. */
    usrToolsInit ();                    /* Software development tools */
    usrAppInit ();                      /* This component calls the initialization function for your application, usrAppInit() in your usrAppInit.c project file, after system start up. */
                                        /* Nor Flash VxBus Driver */
    }



/******************************************************************************
*
* usrInit - Pre-kernel initialization
*/

void usrInit (int startType)
    {
    sysStart (startType);               /* This component clears BSS and sets up the vector table base address. */
    _func_kprintf = kprintf;            /* This component provides the kprintf( ) function that performs formatted output. This is similar to printf( ) except that the output characters are sent to the target's console port (not the STD_OUT file descriptor) in polled mode. */
    usrFdtInit ((void*)DTB_RELOC_ADDR, (int)DTB_MAX_LEN); /* This component provides the flat device tree library. */
    usrBoardLibInit();                  /* This component provides a function to initialize the board subsystem, supplying BSP access APIs. */
    usrAimCpuInit ();                   /* This component includes CPU library support. */
    cacheLibInit (USER_I_CACHE_MODE, USER_D_CACHE_MODE); /* include cache support */
    excVecInit ();                      /* This component provides architecture-dependent facilities for handling processor exceptions. */
    vxCpuLibInit ();                    /* This component enables the initialization of the CPU identification functions. */
    usrCacheEnable ();                  /* This component can be used to optionally enable caches. */
    objInfoInit ();                     /* This component provides object management functions that require lookup in a list of objects, such as the objNameToId() function. */
    objLibInit ((OBJ_ALLOC_FUNC)FUNCPTR_OBJ_MEMALLOC_RTN,                                     (OBJ_FREE_FUNC)FUNCPTR_OBJ_MEMFREE_RTN,                                       OBJ_MEM_POOL_ID,                                                              OBJ_LIBRARY_OPTIONS); /* This component provides the objLib library. This library provides the interface to the VxWorks user object management facilities. */
    vxMemProbeInit ();                  /* This component initializes vxMemProbe( ) exception handler support. */
    wvLibInit ();                       /* Low-level kernel instrumentation needed by System Viewer */
    classListLibInit ();                /* This component provides object class list management. */
    semLibInit ();                      /* This component provides the semaphore support infrastructure. Semaphores are the basis for synchronization and mutual exclusion in VxWorks. They are powerful in their simplicity and form the foundation for numerous VxWorks facilities. Different semaphore types serve different needs, and while the behavior of the types differs, their basic interface is the same. This library provides semaphore functions common to all VxWorks semaphore types. For all types, the two basic operations are semTake() and semGive(), the acquisition or relinquishing of a semaphore. Mutex semaphores offer the greatest speed while binary semaphores offer the broadest applicability. The semLib library provides all of the semaphore operations, including functions for semaphore control, deletion, and information. Semaphores must be validated before any semaphore operation can be undertaken. An invalid semaphore ID results in ERROR, and an appropriate `errno' is set. */
                                        /* This component provides a library that provides the interface to VxWorks mutual-exclusion semaphores. Mutual-exclusion semaphores offer convenient options suited for situations requiring mutually exclusive access to resources. Typical applications include sharing devices and protecting data structures. Mutual-exclusion semaphores are used by many higher-level VxWorks facilities. The mutual-exclusion semaphore is a specialized version of the binary semaphore, designed to address issues inherent in mutual exclusion, such as recursive access to resources, priority inversion, and deletion safety. The fundamental behavior of the mutual-exclusion semaphore is identical to the binary semaphore (see the reference entry for semBLib), except for the following restrictions: it can only be used for mutual exclusion; it can only be given by the task that took it; it may not be taken or given from interrupt level; and the semFlush() operation is illegal. These last two operations have no meaning in mutual-exclusion situations. */
                                        /* This component provides the semMCreate() function. This function creates mutual-exclusion semaphores. */
    condVarLibInit ();                  /* This component provides support for condition variables. Condition variables allow tasks to wait on both an event to occur, and to acquire a mutex that protects an object associated with that event. Thus, condition variables are acquired by taking a mutex, and waiting on the condition variable. When the event is signaled, a task is unblocked and the mutex given to that task, which can then access the protected resource. Note that signaling a condition variable only unblocks a waiting resource - if a condition variable is signaled before a task waits on that condition variable, then the waiting task must wait until the condition variable is signaled again. A condition variable can only be associated with one mutex at a time (if there are waiters, all waiters must have held the same mutex when the condition variable was waited on. No condition variable function is callable from an ISR. For detailed descriptions of the functions provided in this component, see the reference entry for condVarLib. */
    classLibInit ();                    /* This component provides object class management. */
    kernelBaseInit ();                  /* This is a required component. DO NOT REMOVE. */
    taskCreateHookInit ();              /* This component provides user callouts on task creation and deletion. It is required to use the task hook library. */
                                        /* This component provides thread-local storage, a compiler facility that allows for allocation of a variable such that there are unique instances of the variable for each thread (or task, in VxWorks terms). */
    umaskLibInit(UMASK_DEFAULT);        /* This component adds support for the POSIX file mode creation mask in the kernel environment. That is, it supports the unmask() function. */
    usrKernelInit (VX_GLOBAL_NO_STACK_FILL); /* Context switch and interrupt handling. This is a required component. DO NOT REMOVE */
    }

