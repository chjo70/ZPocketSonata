/* usrKernel.c - wind kernel initialization */

/*
 * Copyright (c) 1992-2011, 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14aug17,sub  Added check statement to verify the sections of the
             kernel fit within the first RAM descriptor. (V7COR-4611)
05dec16,y_h  added power off hook initialization, support ACPI
             event feature (F6446)
09aug16,l_l  pass DKM_TLS_SIZE to tlsLibInit (US80079)
01jun16,l_l  supported standard TLS ABI. (US80078)
17nov16,dlk  Increase VX_MAX_TASK_CREATE_RTNS default from 20 to 40 (F7384).
09aug15,l_z  add fast warm boot support. (F3387)
04aug15,h_k  cleaned up compiler warnings at tlsLibInit() call. (F2518)
09apr15,h_k  removed HOOK_TBL_READ_RESERVE, HOOK_TBL_READ_UNRESERVE from
             tickAnnounce(). (V7COR-2742)
16oct14,jpb  Added new parameter for taskLibInit. (Req: WIND00195513)
26aug14,cww  added table of tick announce hooks (US43182)
18may14,zl   added multicore time partitioning support (US39018)
04jun14,wap  Correct issues uncovered by static analysis (V7COR-1242)
16may14,rlp  Removed WDB references (WB4-1735).
27mar14,cww  removed reference to FREE_RAM_ADRS
02may14,cww  fixed mangled modhist (V7COR-863)
31mar14,pcs  Added include of configlette sysMemUtils.c to pull in
	     sysMemSizeGet for COMPAT69 
24mar14,pcs  Set kIP.vmPageSize to 0 for MMU-kernel
26feb14,ten  Added usrRoot prototype since usrConfig.h no longer supplies it.
26feb14,h_k  cleaned up a compiler warning in VIP with
             INCLUDE_TIME_PART_SCHEDULER in Diab 5.9.4.
30jan14,pcs  changes corresponding to combining the two heaps for MMU-less 
             kernel.
20jan14,h_k  added pending queues to temporarily promote mutex owner to
             the current process for time partition scheduler.
06nov13,h_k  added INCLUDE_TIME_PART_SCHEDULER support.
04sep13,xms  fix CHECKED_RETURN error. (WIND00414265)
29may13,cww  added default VX_MAX_TASK_CREATE_RTNS (WIND00419299)
26mar13,cww  made task create/delete hook table size configurable
             (WIND00395617)
13dec11,jpb  WIND00274334.  Added inclusion of tlsLibP.h when INCLUDE_TLS
             is configured.
10feb11,rlp  Enabled system mode agent for LP64.
17nov10,gvm  fix compilation warnings
25aug10,kk   add initialization of _func_eventTaskShow and
            _func_eventRsrcShow
07jul10,cww  Removed reference to sysCpuAvailableGet
18may10,cww  Temporary workaround for sysCpuAvailableGet error in 64-bit
21apr10,kk   replace Q_PRI_BMAP_MAX_PRIORITIES with
             VX_TASK_PRIO_SYSTEM_MAX
18feb10,cww  Fix memPoolEndAdrs to point to the last byte of the pool
26jan10,d_c  SMP M-N updates: Update vxCpuConfigured to account
             for running out of available processors when loaded
             to a physical CPU other than 0.
10feb10,zl   exclude readyQHead for custom scheduler
11jan10,zl   change kernel heap size calculation conditional to
             INCLUDE_ADR_SPACE_LIB.
04nov09,pcs  Updated to reflect the name changes to the 64bit heaps.
11sep09,gls  added error if VX_SMP_NUM_CPUS is greater than
             VX_MAX_SMP_CPUS (WIND00166615)
03sep09,gls  added error if VX_SMP_NUM_CPUS less than one (WIND00160676)
08sep09,pcs  Size the 64-bit kernel heap using a configuration parameter.
29jul09,cww  Update reboot hook pointer type
03feb09,zl   replaced qInit() with specific queue init routines.
13jul09,pch  Add support for INCLUDE_TM_TIMING_FRAMEWORK
19sep08,gls  added kernelLockInit() (Defect #124069)
28aug08,zl   switched to new ready queue classes.
25aug08,jpb  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
13may08,zl   Use CPUSET_SETALL() for vxCpuSetConfigured initialization.
03mar08,zl   moved SMP ready queue configuration to new configlette.
05dec07 d_c  CQ108763: Change vxCpuSetConfigured computation so that
             it works when vxCpuConfigured == 32. Needed especially
             for Raza.
06sep07,pch  CQ102745: resizeable idle-task exception stacks
05sep07,jmg  Added a default value for VX_SMP_NUM_CPUS for SMP
08aug07,zl   added vxCpuSetConfigured.
27jun07,kk   set up vxCpuConfigured with min (VX_SMP_NUM_CPUS,
             sysCpuAvailableGet, VX_MAX_SMP_CPUS)
01mar07,kk   call workQInit with WIND_JOBS_MAX, to match BSP build.
31jan07,lei  removed globalReadyQBMap.
05feb07,pes  Remove 'const' designation from vxCpuConfigured declaration.
30jan07,jmg  Added testing for inclusion of INCLUDE_TASK_ROTATE (Req.
             WIND0071010)
23jan07,jmg  Added check for VX_GLOBAL_NO_STACK_FILL (Req. WIND00083667).
07nov06,dbt  Added support for __thread variables.
17oct06,lei  added vxCpuConfigured and pJobPool; moved localReadyQHead from
             kernelLib.c to here; changed the array size of localReadyQBMap
             to VX_SMP_NUM_CPUS
28jul06,lei  renamed local and global ready queue BMap.
17jul06,mmi  VX_MAX_SMP_CPU to VX_MAX_SMP_CPUS
01mar06,lei  Added SMP support
14feb06,kk   replace VX_NATIVE_SCHEDULER with VX_TRADITIONAL_SCHEDULER
14feb06,jln  added comments about tick queue
10feb06,jlk  Removed posixPse52Mode
03feb06,jlk  Added posixPse52Mode
03aug05,jln  Supported user-specified kernel scheduler
13jul05,jln  Added INCLUDE_POSIX_PTHREAD_SCHED
09jul05,yvp  Deleted include of cfgQueues.c. Code review cleanups.
09jun05,yvp  added config for MAX_ISR_JOBS and MAX_REBOOT_HOOKS.
             INCLUDE_ISR_OBJECTS is a new component.
25feb05,pcs  Modified to reflect the change to the prototype of fn.
             taskLibInit
22nov04,zl   test KERNEL_HEAP_SIZE parameter against sysMemTop().
21apr04,cjj  mods for configurable work queue size.
06apr04,yp   removing global memPoolStartAdrs which is now passed to
             usrMmuInit as an argument
22mar04,hya  Changed tickQHead to use deltaQ.
23oct03,tam  added address space allocator support
21oct03,dat  cleanup of RTP component structure removed interaction
09oct03,tam  inserted objLibInit() into usrKernelInit()
19sep03,pad  Renamed TASK_OVERFLOW_SIZE and TASK_UNDERFLOW_SIZE into
             TASK_STACK_OVERFLOW_SIZE and TASK_STACK_UNDERFLOW_SIZE.
14sep03,kk   updated taskLibInit() to pass in task defaults.
19jun03,dcc  added rtpKernelInit()
04jun03,kam  added ISR object initialization routine
08apr03,to   deleted initialization of activeQHead.
20jan99,jpd  added INITIAL_MEM_ALLOCATION.
18sep95,ism  imported conditional include of wvLib.h from bootConfig.c
28mar95,kkk  moved kernel defines to configAll.h
07dec93,smb  configuration change for windview
10nov92,jcf  configuration change for MicroWorks.
18sep92,jcf  written.
*/

/*
DESCRIPTION
This file is used to configure and initialize the Wind kernel.  This file is
included by usrConfig.c.

NOMANUAL
*/

#include <vsbConfig.h>
#include <private/cpusetP.h>
#include <private/qLibP.h>
#include <vxCpuLib.h>
#include <private/adrSpaceLibP.h>
#include <private/tickLibP.h>
#ifdef _WRS_CONFIG_SYS_PWR_OFF
#include <powerOffLib.h>
#include <private/powerOffLibP.h>
#endif /* _WRS_CONFIG_SYS_PWR_OFF */

#ifdef _WRS_CONFIG_COMPAT69
/* include sysMemUtils.c to pull in routine sysMemSizeGet(). */
#include <sysMemUtils.c>
#endif

#ifdef  INCLUDE_TLS
#include <private/tlsLibP.h>
#endif /* INCLUDE_TLS */

#ifdef _WRS_CONFIG_SMP
#include <private/readyQLibP.h>
#endif /* _WRS_CONFIG_SMP */

extern void usrRoot (char *pMemPoolStart, unsigned memPoolSize);

#ifdef	INCLUDE_TIME_PART_SCHEDULER
#include <private/timePartLibP.h>
#endif /* INCLUDE_TIME_PART_SCHEDULER */

#ifdef INCLUDE_SELECT
#include "private/selectLibP.h"         /* for selectLibInit() prototype */
#endif /* INCLUDE_SELECT */

#ifndef INCLUDE_WARM_BOOT
#define FREE_MEM_START_ADRS (end)
#else
#define FREE_MEM_START_ADRS (warmBootDataEndGet())
#endif

#ifdef  INCLUDE_INITIAL_MEM_ALLOCATION
#define MEM_POOL_START (char *) \
	    (ROUND_UP(FREE_MEM_START_ADRS, (INITIAL_MEM_ALIGNMENT)) + \
	    (INITIAL_MEM_SIZE))
#else   /* INCLUDE_INITIAL_MEM_ALLOCATION */
#define MEM_POOL_START (char *) FREE_MEM_START_ADRS
#endif  /* INCLUDE_INITIAL_MEM_ALLOCATION */

#ifdef _WRS_CONFIG_SMP

/* default the value to 2 for SMP builds */

#ifndef VX_SMP_NUM_CPUS
#define VX_SMP_NUM_CPUS 2
#endif /* VX_SMP_NUM_CPUS */

#if (VX_SMP_NUM_CPUS <= 0)
#error VX_SMP_NUM_CPUS must be a value greater than 0.
#endif /* (VX_SMP_NUM_CPUS <= 0) */

#if (VX_SMP_NUM_CPUS > VX_MAX_SMP_CPUS)
#error VX_SMP_NUM_CPUS must be a value less than or equal to VX_MAX_SMP_CPUS
#endif /* (VX_SMP_NUM_CPUS <= 0) */

#else /* _WRS_CONFIG_SMP */

#ifdef VX_SMP_NUM_CPUS
#undef VX_SMP_NUM_CPUS
#endif /* VX_SMP_NUM_CPUS */

#define VX_SMP_NUM_CPUS 1

#endif /* _WRS_CONFIG_SMP */

/* 
 * Validate that Q_PRI_BMAP_MAX_PRIORITIES is always greater than 
 * VX_TASK_PRIO_SYSTEM_MAX, otherwise, we may set up the ready queue 
 * incorrectly.
 */

#if (Q_PRI_BMAP_MAX_PRIORITIES < VX_TASK_PRIO_SYSTEM_MAX)
#error Q_PRI_BMAP_MAX_PRIORITIES must be greater than VX_TASK_PRIO_SYSTEM_MAX \
for the ready queue.
#endif

/*
 * default vxCpuConfigured to VX_SMP_NUM_CPUS, which is configured by
 * the BSP. For UP, only 1 CPU is configured. For SMP, vxCpuConfigured
 * is calculated with
 * min (VX_MAX_SMP_CPUS, VX_SMP_NUM_CPUS, sysCpuAvailableGet()).
 */

unsigned int vxCpuConfigured = VX_SMP_NUM_CPUS;

# ifdef _WRS_CONFIG_SMP

/* 
 * Circular buffer for the kernel work queue.
 * VX_MAX_SMP_CPUS is used instead of VX_SMP_NUM_CPUS
 * since "pJobPool" is declared in "private/workQLibP.h" as
 * "extern JOB pJobPool[][VX_MAX_SMP_CPUS];"
 *
 * for a 2-dimensional array, the 2nd subscript, or column
 * has to be specified.
 */

JOB     	pJobPool [WIND_JOBS_MAX][VX_MAX_SMP_CPUS];

#ifdef	INCLUDE_TIME_PART_SCHEDULER
CPU_READY_QUEUE kernelRdyQueue[VX_MAX_SMP_CPUS];
#endif /* INCLUDE_TIME_PART_SCHEDULER */

# else /* _WRS_CONFIG_SMP */

/* custom schedulers provide their own ready queue implementation */

#if !defined(INCLUDE_CUSTOM_SCHEDULER) && !defined(INCLUDE_TIME_PART_SCHEDULER)
BMAP_LIST	readyQBMap;             /* bit mapped ready queue list array */
#endif	/* !INCLUDE_CUSTOM_SCHEDULER && !INCLUDE_TIME_PART_SCHEDULER */

Q_HEAD		readyQHead;		/* multi-way ready queue head */

/* Circular buffer for the kernel work queue */

JOB		pJobPool[WIND_JOBS_MAX];
#endif  /* _WRS_CONFIG_SMP */

#ifdef INCLUDE_EXC_TASK

/* MAX_ISR_JOBS must have a positive non-zero value if used. */

#if (MAX_ISR_JOBS == 0)
#error "MAX_ISR_JOBS == 0!!! Should be a positive integer."
#endif

ISR_JOB isrJobPool [MAX_ISR_JOBS]; /* circular buffer for ISR jobs */

#endif	/* INCLUDE_EXC_TASK */

#ifdef _WRS_CONFIG_TASK_CREATE_HOOKS

/*
 * If this VSB option is enabled, these tables must be declared even if the
 * corresponding component is removed (they are referenced directly from
 * taskLib).  However, without the component, VX_MAX_TASK_CREATE_RTNS is not
 * defined, so we do it here. For BSP builds, this is defined in configAll.h,
 * and the size can be customized from there.
 */

#ifndef VX_MAX_TASK_CREATE_RTNS
#define VX_MAX_TASK_CREATE_RTNS 40
#endif

HOOK_TBL_DECL (taskCreateHooks, VX_MAX_TASK_CREATE_RTNS);
HOOK_TBL_DECL (taskDeleteHooks, VX_MAX_TASK_CREATE_RTNS);
#endif

/*
 * Reboot hooks are optional. If used, define VX_MAX_REBOOT_HOOKS to a
 * positive value.
 */

#ifdef INCLUDE_REBOOT_HOOKS
int (*rebootHookTbl [MAX_REBOOT_HOOKS])(int);
#endif	/* INCLUDE_REBOOT_HOOKS */

#ifdef INCLUDE_POWER_OFF_HOOKS
void (*powerOffHookTbl [MAX_POWER_OFF_HOOKS])(void);
#endif /* INCLUDE_POWER_OFF_HOOKS */

/* configuration check for INCLUDE_TASK_ROTATE */

#if (defined (INCLUDE_TASK_ROTATE) && \
     (VX_TRAD_SCHED_CONSTANT_RDY_Q != TRUE) && \
     (VX_NATIVE_SCHED_CONSTANT_RDY_Q != TRUE))
#error The INCLUDE_TASK_ROTATE component requires \
       VX_NATIVE_SCHED_CONSTANT_RDY_Q be set to TRUE
#endif	/* INCLUDE_TASK_ROTATE && VX_*_SCHED_CONSTANT_RDY_Q */

#ifdef	INCLUDE_TM_TIMING_FRAMEWORK
/* "end of usrInit()" timestamp */
TM_TIMESTAMP_TYPE	tmTfwUsrInitEndTime = TM_TIMESTAMP_INIT_VAL;
#endif	/* INCLUDE_TM_TIMING_FRAMEWORK */

char *		memPoolEndAdrs;		/* end of the kernel memory pool */

/*******************************************************************************
*
* usrKernelInit - configure kernel data structures
*
* \NOMANUAL
*/

void usrKernelInit
    (
    BOOL noStackFill
    )
    {
    _KERNEL_INIT_PARAMS	kIP;
#ifdef INCLUDE_KERNEL_PROXIMITY_HEAP
    PHYS_MEM_DESC       memDesc;
    char *              firstRamDescStartAddr;
    char *              firstRamDescEndAddr;
    static const char * pErrorMsg = "usrKernelInit: first memory descriptor "
                                    "cannot accomodate kernel sections and "
                                    "the kernel proximity heap.\n";
#endif

#ifdef _WRS_CONFIG_SMP
    /*
     * set the number of CPUs available for SMP.
     * Any uses of vxCpuConfigured before here will use the value
     * of vxCpuConfigured set to VX_SMP_NUM_CPUS, which is the value
     * configured by the BSP.  vxCpuConfigured will also be updated when the 
     * idle tasks are created in case there are fewer than CPUs than expected,
     * eg. if we are not starting on core 0.
     */

    vxCpuConfigured = min (VX_MAX_SMP_CPUS, VX_SMP_NUM_CPUS);

    kernelLockInit ();
#endif /* _WRS_CONFIG_SMP */

#ifdef INCLUDE_REBOOT_HOOKS
    pRebootHookTbl = &rebootHookTbl[0];
    rebootHookTblSize = MAX_REBOOT_HOOKS;
#endif	/* INCLUDE_REBOOT_HOOKS */

#ifdef INCLUDE_POWER_OFF_HOOKS
    pPowerOffHookTbl = &powerOffHookTbl[0];
    powerOffHookTblSize = MAX_POWER_OFF_HOOKS;
#endif /* INCLUDE_POWER_OFF_HOOKS */

#ifdef INCLUDE_ISR_OBJECTS
    isrLibInit ();                      /* initialize ISR object */
#endif	/* INCLUDE_ISR_OBJECTS */

    globalNoStackFill = noStackFill; 	/* Global stack fill variable */

    taskLibInit (TASK_USER_EXC_STACK_SIZE,
		 TASK_KERNEL_EXC_STACK_SIZE,
		 TASK_USER_EXC_STACK_OVERFLOW_SIZE,
		 0, /* Not used for now, reserved for future use. */
		 TASK_USER_EXEC_STACK_OVERFLOW_SIZE,
		 TASK_USER_EXEC_STACK_UNDERFLOW_SIZE,
		 TASK_KERNEL_EXEC_STACK_OVERFLOW_SIZE,
		 TASK_KERNEL_EXEC_STACK_UNDERFLOW_SIZE); /* initialize task */
							 /* object          */

    /*
     * configure the kernel scheduler descriptor, and the initialzation
     * NOTE: INCLUDE_VX_NATIVE_SCHEDULER and VX_NATIVE_SCHED_CONSTANT_RDY_Q
     * is being replaced by INCLUDE_VX_TRADITIONAL_SCHEDULER and
     * VX_TRAD_SCHED_CONSTANT_RDY_Q
     */

#if (defined (INCLUDE_VX_NATIVE_SCHEDULER) || \
     defined (INCLUDE_VX_TRADITIONAL_SCHEDULER))
    /* install the standard priority based preemptive scheduler */

#if ((VX_TRAD_SCHED_CONSTANT_RDY_Q == TRUE) || \
     (VX_NATIVE_SCHED_CONSTANT_RDY_Q == TRUE))

#ifndef _WRS_CONFIG_SMP
    (void) qPriBMapInit (&readyQHead, Q_TRAD_PRI_BMAP, &readyQBMap, 
			 VX_TASK_PRIO_SYSTEM_MAX);
#else
    readyQInit (Q_TRAD_PRI_BMAP, VX_TASK_PRIO_SYSTEM_MAX);
#endif

#else /* !VX_TRAD_SCHED_CONSTANT_RDY_Q */

#ifndef _WRS_CONFIG_SMP
    qPriListInit (&readyQHead, Q_TRAD_PRI_LIST, QUEUE_NONINTERRUPTIBLE);
#else
# error VX_TRAD_SCHED_CONSTANT_RDY_Q is required for SMP
#endif

#endif /* !VX_TRAD_SCHED_CONSTANT_RDY_Q */

#elif (defined (INCLUDE_POSIX_PTHREAD_SCHEDULER))

#ifndef _WRS_CONFIG_SMP

#ifdef INCLUDE_PX_SCHED_SPORADIC_POLICY
    (void) qPriBMapInit (&readyQHead, Q_PX_SS_PRI_BMAP, &readyQBMap, 
			 VX_TASK_PRIO_SYSTEM_MAX);
#else
    (void) qPriBMapInit (&readyQHead, Q_PX_PRI_BMAP, &readyQBMap, 
			 VX_TASK_PRIO_SYSTEM_MAX);
#endif

#else /* _WRS_CONFIG_SMP */

#ifdef INCLUDE_PX_SCHED_SPORADIC_POLICY
    readyQInit (Q_PX_SS_PRI_BMAP, VX_TASK_PRIO_SYSTEM_MAX);
#else
    readyQInit (Q_PX_PRI_BMAP, VX_TASK_PRIO_SYSTEM_MAX);
#endif

#endif /* _WRS_CONFIG_SMP */

    /*
     * POSIX_PTHREAD_RR_TIMESLICE is the configuration parameter for POSIX
     * thread Round Robin scheduling. It specifies the time slice for
     * POSIX threads with SCHED_RR policy. This parameter can be changed
     * through the configuration MACRO in 00vxWorks.cdf.
     */

    roundRobinSlice = POSIX_PTHREAD_RR_TIMESLICE;

    /* install the round robin hook */

    tickAnnounceHookAdd ((FUNCPTR) taskPxWindTickAnnounceHook);
    roundRobinHookInstalled = TRUE;

#elif (defined (INCLUDE_TIME_PART_SCHEDULER))

#ifdef _WRS_CONFIG_SMP
    readyQInit (Q_TRAD_PRI_BMAP, VX_TASK_PRIO_SYSTEM_MAX);
#else
    (void) qTimePartInit (&readyQHead, Q_TIME_PART, VX_TASK_PRIO_SYSTEM_MAX);
#endif /* SMP */

#elif (!defined(INCLUDE_CUSTOM_SCHEDULER))

#error Need to choose 1 component from INCLUDE_VX_TRADITIONAL_SCHEDULER, \
       INCLUDE_POSIX_PTHREAD_SCHEDULER, INCLUDE_CUSTOM_SCHEDULER, or \
       INCLUDE_TIME_PART_SCHEDULER

#endif /* INCLUDE_POSIX_PTHREAD_SCHEDULER */


#if (TASK_PRIORITY_SET_COMPATIBLE == TRUE)
    /*
     * To ease migration for applications that expect the old (incorrect)
     * behaviour for priority changes (including priority inheritance), the
     * TASK_PRIORITY_SET_COMPATIBLE configuration parameter is provided.
     * With the old behaviour (parameter set TRUE), a running task may
     * be preemted when it's priority is lowered to a level at which other
     * ready tasks are waiting. This configuration option will be
     * eventually removed.
     */

#ifdef INCLUDE_Q_PRI_LIST
    qTradPriListSetCompatible ();
#endif
#ifdef INCLUDE_Q_PRI_BMAP
    qTradPriBMapSetCompatible ();
#endif
#endif /* VX_TASK_PRIORITY_SET_COMPATIBLE == TRUE */

    /* Initialize tick queue */

    qPriDeltaInit (&tickQHead, Q_PRI_DELTA);

    /* queue for deferred work */

    workQInit (WIND_JOBS_MAX);

#ifdef INCLUDE_KERNEL_PROXIMITY_HEAP
    /* 
     *  Read the first RAM descriptor entry. 
     *  don't need return from function call 
     */
    (void) sysMemDescGet (MEM_DESC_RAM, 0, &memDesc);

    firstRamDescStartAddr = (char *) memDesc.virtualAddr;
    firstRamDescEndAddr   = (char *) (memDesc.virtualAddr + memDesc.len - 1);

#ifndef _WRS_CONFIG_MMULESS_KERNEL
    memPoolEndAdrs   = (char *) MEM_POOL_START + KERNEL_PROXIMITY_HEAP_SIZE - 1;
#else
    /*
     * For MMU-less mode, we have a single heap. 
     * The heap is created using all the remaining RAM from the first RAM
     * descriptor entry. So set memPoolEndAdrs to firstRamDescEndAddr.
     */

    memPoolEndAdrs   = firstRamDescEndAddr;
#endif

    /* Check for address rollovers */

    if (memPoolEndAdrs > MEM_POOL_START)
	{
	/* memPoolEndAdrs is valid, but check that the descriptor covers it */

	if (firstRamDescEndAddr > firstRamDescStartAddr)
	    {
            if (MEM_POOL_START > firstRamDescEndAddr)
                {

               /*
                * Kernel sections including the kernel proximity heap
                * does not fit within the first RAM descriptor.
                */

                sysExcMsg += sprintf (sysExcMsg, pErrorMsg);

                EDR_INIT_FATAL_INJECT (NULL, NULL, NULL, NULL, pErrorMsg);

                }
            else
                {
                memPoolEndAdrs = min (firstRamDescEndAddr, memPoolEndAdrs);
                }
	    }
	}
    else
	{
	/* The configured KERNEL_PROXIMITY_HEAP_SIZE causes rollover */

	if (firstRamDescEndAddr > firstRamDescStartAddr)
	    {

	    /*
	     * If the entire 0th descriptor can be used, use the smaller of the
	     * end of the 0th descriptor or the end of the kernel region
	     */

	    memPoolEndAdrs = min (firstRamDescEndAddr,
				  (char *)(KERNEL_SYS_MEM_RGN_BASE + 
					   KERNEL_SYS_MEM_RGN_SIZE - 1));
	    }
	else
	    {
	    /* Use the end of the kernel region as a last resort */

	    memPoolEndAdrs = (char *) (KERNEL_SYS_MEM_RGN_BASE + 
		                       KERNEL_SYS_MEM_RGN_SIZE - 1);
	    }
	}
#else
#ifdef INCLUDE_ADR_SPACE_LIB
    memPoolEndAdrs = min ((char *) MEM_POOL_START + KERNEL_HEAP_SIZE,
			  sysMemTop ());
#else
    memPoolEndAdrs = sysMemTop ();
#endif
    memPoolEndAdrs--;
#endif

#ifdef	INCLUDE_TLS
    /* Initialize Thread Local Storage library for __thread variables support */

#ifdef _WRS_CONFIG_LANG_LIB_TLS_STD
#ifndef DKM_TLS_SIZE
#define DKM_TLS_SIZE 0
#endif
    tlsLibInit (wrs_kernel_tls_data_start,
		(size_t) wrs_kernel_tls_data_size,
		(size_t) wrs_kernel_tls_mem_size,
		(size_t) wrs_kernel_tls_data_align,
		(size_t) DKM_TLS_SIZE);
#else
    tlsLibInit (wrs_kernel_tls_vars_start,
    		(size_t) wrs_kernel_tls_vars_size,
		wrs_kernel_tls_data_start,
		(size_t) wrs_kernel_tls_data_size,
		(size_t) wrs_kernel_tls_data_align);
#endif
#endif	/* INCLUDE_TLS */

    /* start the kernel specifying usrRoot as the root task */

    bfill ((char *)&kIP, sizeof(kIP), 0);

    kIP.rootRtn		= (FUNCPTR) usrRoot;
    kIP.rootMemSize	= ROOT_STACK_SIZE;
    kIP.pMemPoolStart	= MEM_POOL_START;
    kIP.pMemPoolEnd	= memPoolEndAdrs;
    kIP.intStackSize	= ISR_STACK_SIZE;
    kIP.lockOutLevel	= INT_LOCK_LEVEL;
#ifdef _WRS_CONFIG_MMULESS_KERNEL
    kIP.vmPageSize	= 0;
#else
    kIP.vmPageSize	= VM_PAGE_SIZE;
#endif

#ifdef	_ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK
# ifdef	INCLUDE_PROTECT_INTERRUPT_STACK
	/* else already zero, by bfill above */
    kIP.intStackOverflowSize  = INTERRUPT_STACK_OVERFLOW_SIZE;
    kIP.intStackUnderflowSize = INTERRUPT_STACK_UNDERFLOW_SIZE;
# endif  /* INCLUDE_PROTECT_INTERRUPT_STACK */
#endif	/* _ARCH_SUPPORTS_PROTECT_INTERRUPT_STACK */

#ifdef	_WRS_CONFIG_SMP

# ifdef  IDLE_TASK_EXCEPTION_STACK_SIZE
    kIP.idleTaskExcepStkSize = IDLE_TASK_EXCEPTION_STACK_SIZE;
# else
    kIP.idleTaskExcepStkSize = KERNEL_TASK_EXC_STACK_SIZE;
# endif  /* IDLE_TASK_EXCEPTION_STACK_SIZE */

# ifdef  _ARCH_SUPPORTS_PROTECT_IDLE_TASK_STACK
#  ifdef  INCLUDE_PROTECT_IDLE_TASK_STACK

#   ifdef  IDLE_TASK_EXC_STACK_OVERFLOW_SIZE
    kIP.idleTaskExcepStkOverflowSize = IDLE_TASK_EXC_STACK_OVERFLOW_SIZE;
#   endif  /* IDLE_TASK_EXC_STACK_OVERFLOW_SIZE */

#   ifdef  IDLE_TASK_EXC_STACK_UNDERFLOW_SIZE
    kIP.idleTaskExcepStkUnderflowSize = IDLE_TASK_EXC_STACK_UNDERFLOW_SIZE;
#   endif  /* IDLE_TASK_EXC_STACK_UNDERFLOW_SIZE */

#  endif  /* INCLUDE_PROTECT_IDLE_TASK_STACK */
# endif  /* _ARCH_SUPPORTS_PROTECT_IDLE_TASK_STACK */
#endif	/* _WRS_CONFIG_SMP */

/* initialized the _func_eventXXX for both proj build and BSP build */

#ifdef INCLUDE_VXEVENTS
#ifdef INCLUDE_TASK_SHOW
    _func_eventTaskShow = eventTaskShow;
#endif /* INCLUDE_TASK_SHOW) */
#if (defined (INCLUDE_SEM_SHOW) || (defined (INCLUDE_MSG_Q_SHOW)))
    _func_eventRsrcShow = eventRsrcShow;
#endif /* defined (INCLUDE_SEM_SHOW) || (defined (INCLUDE_MSG_Q_SHOW)) */
#endif /* INCLUDE_VXEVENTS */

#ifdef	INCLUDE_TM_TIMING_FRAMEWORK
/* Capture an "end of usrInit()" timestamp */
    TM_TIMESTAMP_GET(tmTfwUsrInitEndTime);
#endif	/* INCLUDE_TM_TIMING_FRAMEWORK */

    kernelInit (_KERNEL_INIT_PARAMS_VN_AND_SIZE, &kIP);

    /* we do not return from kernelInit() */
    }
