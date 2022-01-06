/* 10smp.cdf - symmetric multiprocessing (SMP) components */

/*
 * Copyright (c) 2007-2008, 2010-2011, 2013-2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12jan18,r_h  added component dependence (V7PRO-4226)
17apr17,own  Minor changes to SYNOPSIS and NAME descriptors (F8862).
22apr16,emj  CERT: Update to produce partially linked objects (US79607)
01apr15,zl   added INCLUDE_SMP_SCHED_FEPT_POLICY (V7COR-2913)
26mar15,pfl  addressed build issue (V7SP-47)
22aug14,cww  removed INCLUDE_SMP_SCHED_SMT_POLICY workaround
19jun14,cww  added conditional around INCLUDE_SMP_SCHED_SMT_POLICY (US39018)
03apr14,h_k  added hidden INCLUDE_PROTECT_INTERRUPT_STACK_NON_CORE0
             component. (VXW6-19208)
13feb14,ylu  fix INCLUDE_CPC component for VXBUS_LEGACY build,
             surround INCLUDE_VXBUS with _WRS_CONFIG_VXBUS_LEGACY. (VXW7-1128)  
12dec13,ylu  added support for vx7 SMP feature.
18oct13,h_k  cleaned up obsoleted SOURCE attribute.
02aug11,zl   added SMT scheduler component
12nov10,mze  _WRS_VX_SMP is now obsolete replaced with _WRS_CONFIG_SMP
31oct08,kk   rename INCLUDE_SMP_DEMO to INCLUDE_SMP_INIT in
             INCLUDE_SMP_DEMO (CQ:WIND00141978)
13oct08,zl   removed API_READY_QUEUE
26aug08,jpb  Removed LAYER from components.
27jun08,zl   made INCLUDE_READY_QUEUE_DELTA default
25mar08,zl   changed INCLUDE_ENABLE_ALL_CPUS to INCLUDE_SMP_INIT.
15mar08,zl   added configlette for delta ready queue.
03mar08,zl   added ready queue API definitions.
04oct07,mze  fix for 104829
13sep07,pch  CQ102745: idle-task exception stack configurability
13jul07,kk   clean up SMP components
06jul07,tor  vxIpiLib dependency of SMP
26apr07,pee  added source mode support
11apr07,kk   fix INCLUDE_CPC component for UP source level build
09mar07,pad  Removed the MODULES and LAYER attribute from INCLUDE_CPC since
             this is conflicting with the UP build.
05mar07,kk   written

*/

/*
DESCRIPTION
This file contains descriptions for the symmetric multiprocessing (SMP) 
components. All components in this file are only visible for projects created
with SMP support.

*/

#ifdef _WRS_CONFIG_SMP

Api API_SMP_SCHED_POLICIES {
	NAME 		SMP scheduler policy selector
	SYNOPSIS 	API selection for SMP scheduler policy
	_CHILDREN 	FOLDER_KERNEL
	DEFAULTS 	INCLUDE_SMP_SCHED_DEFAULT_POLICY
}

Component INCLUDE_SMP_SCHED_DEFAULT_POLICY {
	NAME 		Default SMP scheduler policy
	SYNOPSIS 	This is the default SMP scheduler policy. It's aim is \
			to run the highest priority ready tasks as soon as \
			possible by quickly propagating necessary task context \
			switches across CPUs.
	MODULES		readyQDeltaLib.o
	ARCHIVE 	librqdef.a
	PROVIDES 	API_SMP_SCHED_POLICIES
}

Component INCLUDE_SMP_SCHED_FEPT_POLICY {
	NAME 		FEPT SMP scheduler policy
	SYNOPSIS 	This is the FIFO Equal Priority Task SMP scheduler \
			policy. It ensures the FIFO round-robin order for \
			tasks with the same priority irrespective of task CPU \
			affinities. It also guarantees that a task preempted \
			by a higher priority task resumes execution once the \
			higher priority task blocks. The tradeoff (compared to \
			the default scheduling policy) is reduced performance, \
			especially for systems with large number of CPUs.
	MODULES		readyQFeptLib.o
	ARCHIVE 	librqfept.a
	PROVIDES 	API_SMP_SCHED_POLICIES
}

/*
 * Architectures that support symmetric multi-therading policy must override 
 * the MODULES definition without the leading underscore character.
 */

Component INCLUDE_SMP_SCHED_SMT_POLICY {
	NAME 		SMP scheduler policy with SMT support
	SYNOPSIS 	This is an extension to the default scheduling policy \
			to provide load balancing for processors with \
			Symmetric Multi-Threading support (such as \
			Hyper-Threading Technology).
#ifdef _WRS_CONFIG_ITL_COMMON
        REQUIRES        INCLUDE_SMT_ENABLE
#endif
	MODULES		_readyQDeltaSmtLib.o
	ARCHIVE 	librqsmt.a
	PROVIDES 	API_SMP_SCHED_POLICIES
}

Component INCLUDE_CPC {
	NAME		Cross-Processor Call (SMP Only)
	SYNOPSIS	CPUs Cross-Processor Call (SMP Only)
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		cpcLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	INIT_RTN	cpcInit ();
	HDR_FILES	private/cpcLibP.h
	REQUIRES	INCLUDE_SYSCLK_INIT
	INCLUDE_WHEN	INCLUDE_KERNEL
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    INIT_AFTER  INCLUDE_VXBUS
#endif /* _WRS_CONFIG_VXBUS_LEGACY */
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Component INCLUDE_IDLE_TASKS {
	NAME		Idle Tasks Support (SMP Only)
	SYNOPSIS	Add Idle Tasks Support (SMP Only)
	INIT_RTN	kernelIdleTaskActivate();
	REQUIRES	INCLUDE_KERNEL
	INCLUDE_WHEN	INCLUDE_KERNEL
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Parameter IDLE_TASK_EXCEPTION_STACK_SIZE {
	NAME		Size of the idle task's exception stack
	SYNOPSIS	The size of the stack used for reschedule and task switch hooks.
	TYPE		uint
	DEFAULT		4096
	_CFG_PARAMS	INCLUDE_KERNEL
}

 /*
  * Definition is generic, but not necessarily available on all arch.  Those
  * which support it will specify the INIT_ORDER, and override _CHILDREN to
  * make it visible/selectable.
  */

Component INCLUDE_PROTECT_IDLE_TASK_STACK {
	NAME		enable guard pages on the idle task exception stack
	SYNOPSIS	Insert guard pages on the idle task exception stack, to protect against overflow or underflow while running task switch or swap hooks.
	_CHILDREN	FOLDER_NOT_VISIBLE
	CFG_PARAMS	IDLE_TASK_EXC_STACK_OVERFLOW_SIZE	\
			IDLE_TASK_EXC_STACK_UNDERFLOW_SIZE
	REQUIRES	INCLUDE_MMU_BASIC
	PROTOTYPE	void usrIdleTaskStkProtect (void);
	INIT_RTN	usrIdleTaskStkProtect ();
	CONFIGLETTES	usrIdleStacks.c
}

Parameter IDLE_TASK_EXC_STACK_OVERFLOW_SIZE {
	NAME		Idle task exception stack overflow protection size
	SYNOPSIS	Size (in bytes) of the protected area above the idle task exception stack.
	TYPE		uint
	DEFAULT		VM_PAGE_SIZE
}

Parameter IDLE_TASK_EXC_STACK_UNDERFLOW_SIZE {
	NAME		Idle task exception stack underflow protection size
	SYNOPSIS	Size (in bytes) of the protected area below the idle task exception stack.
	TYPE		uint
	DEFAULT		VM_PAGE_SIZE
}

Component INCLUDE_PROTECT_INTERRUPT_STACK_NON_CORE0 {
	NAME		enable guard pages for interrupt stack on non-primary cores
	SYNOPSIS	insert underflow and overflow guard pages on interrupt stack on non-primary cores
	_CHILDREN	FOLDER_NOT_VISIBLE
	INCLUDE_WHEN	INCLUDE_PROTECT_INTERRUPT_STACK
	REQUIRES	INCLUDE_PROTECT_INTERRUPT_STACK
	PROTOTYPE	void usrKernelIntStkProtectNonCore0 (void);
	/*
	 * This init routine must be executed after the system completes to get
	 * the available core number from the hardware, that is usually done by
	 * sysHwInit(), the component is INCLUDE_SYSHW_INIT, or sysHwInit2() at
	 * latest, called from the init routine belongs to INCLUDE_SYSHW_INIT2
	 * or INCLUDE_SYSCLK_INIT.
	 */
	INIT_RTN	usrKernelIntStkProtectNonCore0 ();
}

/* 
 * ENABLE_ALL_CPUS configuration parameter is in 00vxWorks.cdf. 
 * The parameter is placed in 00vxWorks.cdf because it is of the 
 * INCLUDE_KERNEL component and no SMP components here should be
 * exposed.
 */

Component INCLUDE_SMP_INIT {
	NAME		Enable multi-processor capability of the kernel
	CONFIGLETTES	usrSmp.c
	INIT_RTN	usrSmpInit ();
	REQUIRES	API_SMP_SCHED_POLICIES
	_REQUIRES	INCLUDE_KERNEL
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Component INCLUDE_SMP_DEMO {
	NAME		Symmetric multiprocessing (SMP) demos
	SYNOPSIS	This component supports symmetric multiprocessing (SMP) demos.
	LINK_SYMS	smpDemoModules
	REQUIRES	INCLUDE_CPC \
			INCLUDE_SMP_INIT \
			INCLUDE_IDLE_TASKS
	_CHILDREN	FOLDER_KERNEL
}
#endif	/* _WRS_CONFIG_SMP */
