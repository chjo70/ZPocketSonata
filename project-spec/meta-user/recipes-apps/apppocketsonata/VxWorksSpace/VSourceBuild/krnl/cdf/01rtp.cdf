/* 01rtp.cdf - Real Time Process component definitions */

/*
 * Copyright (c) 2003-2010, 2012-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10apr17,own  Removed redundancy from component and parameter NAME values.
             Created FOLDER_RTP_STARTUP_FACILITY folder for startup facilities.
             Improved SYNOPSIS content. Child components of FOLDER_NOT_VISIBLE
             were excluded from improvements (F8862).
22apr16,emj  CERT: Update to produce partially linked objects (US79607)
18dec14,ymz  split INCLUDE_SC_IOS for CERT subset and non-cert subset
08dec14,v_r  CERT: RTP symbol table support now disabled
09nov14,gls  removed INCLUDE_SYSCTL for the certification profile
02dec14,v_r  RTP symbol table support now optional
08oct14,gls  added INCLUDE_RTP_SIGNALS
12may14,cww  added CERT restriction
05nov15,rr   add vxAtomicScLib.o to INCLUDE_SC_KERNEL 
30sep15,rr   Added RTP_MEM_FILL parameter (V7COR-3084)
29jan15,jmp  Increased default RTP_HOOK_TBL_SIZE (V7COR-2525).
09jan14,h_k  moved INCLUDE_RTP_APPL_INIT_CMD_SHELL_SCRIPT to
             02shell_commands.cdf.
10jan12,pcs  decouple INCLUDE_SHARED_DATA from INCLUDE_SHL since shared
             libraries no longer use shared data. (iter23 merge)
02aug13,pcs  updated to use config option _WRS_CONFIG_COMPAT69_ADR_SPACE
09mar10,pad  Do not show RTP_OVERLAPPED_ADDRESS_SPACE, RTP_CODE_REGION_SIZE
	     and RTP_CODE_REGION_START parameters for VxWorks 64-bit.
27jan10,cww  Added memRtpLibInit to header file
25jan10,kk   change to use overlap as default
08jan10,zl   split INCLUDE_MMAP from INCLUDE_SC_MMAN. Moved KERNEL_HEAP_SIZE
             parameter to 02mm.cdf
08dec09,cww  Added INCLUDE_TASK_STACK_ALLOC
22sep09,kk   hide INCLUDE_RTP_POSIX_PSE52 (WIND00182189)
04sep09,kk   remove unused RTP_KERNEL_STACK_SIZE parameter (WIND00180527)
13aug09,cww  Updated ordering of RTP init routines
23jun08,pad  Added the RTP_OVERLAPPED_ADDRESS_SPACE parameter to switch
	     between flat and overlapped virtual memory models.
07may08,pad  Added the RTP_CODE_REGION_SIZE and RTP_CODE_REGION_START
	     parameters.
17oct07,mfj  Fixing problem with KERNEL_HEAP_SIZE (WIND00102855)
01aug07,act  io footprint work (from pcm)
06jul06,pcs  RTP heap options is now configurable.
17mar06,pad  Fixed pxCpuTimerLib.o module name (SPR #119108).
14feb06,jln  added INCLUDE_POSIX_THREAD_CPUTIME component
18jan06,pad  Added component INCLUDE_RTP_POSIX_PSE52 and parameter
	     RTP_FD_NUM_MAX. Changed call to rtpLibInit().
18aug05,kk   updated synopsis for RTP_SIGNAL_QUEUE_SIZE
03aug05,kk   make the RTP_SIGNAL_QUEUE_SIZE default to be 32 to conform to
             POSIX
09jul05,yvp  Hook components now depend on INCLUDE_HOOKS.
22jun05,yvp  Added dependency on INCLUDE_TASK_RESTART and 
	     INCLUDE_TASK_CREATE_DELETE for system calls.
12may05,kk   added dependency of VXEVENTS for RTP (SPR# 109130)
20apr05,gls  added INCLUDE_OBJ_OWNERSHIP (SPR #106150)
15apr05,yvp  Fixed INCLUDE_RTP_APPL_INIT_STRING default value (SPR 107365).
	     Changed INCLUDE_RTP_APPL_USER configlette (SPR 105759).
26feb05,pcs  Modified to reflect the change to the prototype of fn.
             rtpLibInit
27jan05,dbt  Removed dependency on loader (SPR #101436).
24nov04,kk   ensure RTP_HOOKS gets included when SHL is included
24nov04,fle  Fixed simple quotes in components synopses
23nov04,zl   added type definition to KERNEL_HEAP_SIZE.
22nov04,yvp  Added synopsis for RTP startup facility components.
15nov04,yvp  Changed prototype for usrRtpAppInitString().
11nov04,job  System call components added to usrScInit init group.
	     Fix INCLUDE_MEM_RTP; added INCLUDE_SC_SD, INCLUDE_SC_SHL
18oct04,fr   added INCLUDE_OBJ_OPEN to INCLUDE_RTP (SPR 101491)
14oct04,pad  Moved rtpHookLibInit in the usrRoot group, to be initialized
             before rtpLib (SPR #102595).
02oct04,gls  added private/sdLibP.h to INCLUDE_SHARED_DATA component
02oct04,bpn  Moved shell commands components to 01shell.cdf.
25sep04,dcc  added objRtpLib.o to the list of rtp modules
23sep04,kk   added INCLUDE_RTP_SHOW_SHELL_CMD
02sep04,yvp  rtpHookLibInit() prototype change.
31aug04,job  Made INCLDUE_RTP require INCLUDE_LOADER_CODE (SPR#101151)
28aug04,dbt  Fixed previous modification.
27aug04,gls  added SD_HOOK_TBL_SIZE
28jul04,md   Removed need for INCLUDE_EDR_SYSDBG_FLAG
28jun04,job  Changed INCLUDE_SYSCTL_API to INCLUDE_SYSCTL
21jun04,kk   added INIT_ORDER for RTP_HOOKS & SYSCALL_HOOKS, added
             INCLUDE_SHL_SHELL_CMD
20may04,job  INCLUDE_RTP now requires INCLUDE_SYSCTL_API
20may04,gls  renamed mmScLib to mmanScLib
18may04,yvp  Added INCLUDE_RTP_APPL_INIT_CMD_SHELL_SCRIPT.
18may04,bpn  Added invisible INCLUDE_RTP_SHELL_C component.
03may04,kk   added INCLUDE_SHL_SHOW component
09apr04,kk   added INCLUDE_SHL components
07may04,yvp  Added RTP Startup Facility Components INCLUDE_RTP_APPL_*
06apr04,gls  added INCLUDE_SHARED_DATA_SHOW
06apr04,job  Pass TASK_STACK_OVERFLOW_SIZE and TASK_STACK_UNDERFLOW_SIZE
	     to rtpLibInit(). Removed the INIT_AFTER line from the
	     definition of INCLUDE_RTP_APPL
05apr04,yvp  Moved RTP_APPL component inclusion in tree to this file. Made
             RTP component a child of the OS folder.
02apr04,tam  fixed init of SHARTED_DATA (SPR 95720)
03mar04,md   include ED&R policies when RTP's are included
24feb04,yvp  Added component INCLUDE_RTP_APPL.
18feb04,ans  Added RTP_SIGNAL_QUEUE_SIZE CFG_PARAMS in INCLUDE_RTP component.
12dec03,yvp  Added syscallTbl.h to INCLUDE_RTP inlcude list.
08dec03,m_s  removed definition of SC_POSIX
05dec03,zl   added INCLUDE_MEM_RTP component, RTP_HEAP_INIT_SIZE parameter
04dec03,ans  removed REQUIRES SC_POSIX from INCLUDE_RTP component
03dec03,bpn  Fixed init of the component INCLUDE_RTP_SHELL_CMD.
21oct03,dat  SC_IOS subcomponent, general cleanup/refactor of RTP components.
11nov03,kk   added INCLUDE_WHEN on INCLUDE_SHOW_ROUTINES for all show
             components
04nov03,kk   added SHARED DATA component
23oct03,tam  added KERNEL_HEAP_SIZE parameter to RTP component.
12nov03,yvp  Added support for RTP hooks.
31oct03,yvp  Added INCLUDE_RTP_ARCH.
03oct03,ans  INCLUDE_RTP now REQUIRES INCLUDE_SC_POSIX
29sep03,pad  Now force the inclusion of system call handler components.
22sep03,bpn  Added INCLUDE_RTP_SHELL_CMD component.
04sep03,nrj  added auxiliary vector module
19aug03,kk   removed rtpElfLoadLib.o, rtpALib.o, excScPpcALib.o 
             from INCLUDE_RTP. The ALib.o files should be arch specific.
             made kernel stack size a page.
	     added INCLUDE_RTP_SHOW component
15jul03,job  Fixed spelling mistakes
14jul03,nrj  added modules that are arch specific, system call
27jun03,nrj  written to include RTP
*/

/*
This file contains descriptions for all of the RTP components.
*/

/* Attach main RTP folder to the root folder, don't make it a default */

Folder	FOLDER_RTP {
	NAME		Real-time process (RTP)
	SYNOPSIS	This folder includes components and parameters \
    			for configuring real-time processes (RTPs).
	_CHILDREN	FOLDER_OS
	CHILDREN	INCLUDE_RTP \
                        INCLUDE_RTP_SIGNALS \
			INCLUDE_SHARED_DATA \
			INCLUDE_SHL \
			INCLUDE_RTP_HOOKS \
			INCLUDE_SYSCALL_HOOKS
	DEFAULTS	INCLUDE_RTP
}

Component INCLUDE_RTP {
	NAME		Real-time process
	SYNOPSIS	This component defines a real-time process (RTP). This component \
			is the foundation for user space applications.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		rtpLib.o rtpAuxvLib.o syscallLib.o objRtpLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
        INIT_RTN        rtpLibInit (RTP_HOOK_TBL_SIZE, SYSCALL_HOOK_TBL_SIZE, \
				    RTP_SIGNAL_QUEUE_SIZE, \
				    TASK_USER_EXC_STACK_OVERFLOW_SIZE, \
				    TASK_USER_EXEC_STACK_OVERFLOW_SIZE, \
				    TASK_USER_EXEC_STACK_UNDERFLOW_SIZE, \
				    RTP_FD_NUM_MAX, RTP_MEM_FILL);
	HDR_FILES	rtpLib.h private/rtpLibP.h auxv.h syscallLib.h \
			syscallTbl.h private/syscallLibP.h
#ifndef _WRS_CONFIG_CERT
	REQUIRES	INCLUDE_MEM_RTP \
			INCLUDE_TASK_STACK_ALLOC \
			INCLUDE_SC_KERNEL \
			INCLUDE_SC_IOS \
			INCLUDE_SC_MMAN \
                        INCLUDE_SYSCTL \
			INCLUDE_RTP_ARCH \
			INCLUDE_OBJ_OPEN \
			INCLUDE_OBJ_OWNERSHIP \
			INCLUDE_VXEVENTS
#else
	REQUIRES	INCLUDE_MEM_RTP \
			INCLUDE_TASK_STACK_ALLOC \
			INCLUDE_SC_KERNEL \
			INCLUDE_SC_IOS \
			INCLUDE_SC_MMAN \
			INCLUDE_RTP_ARCH \
			INCLUDE_OBJ_OPEN \
			INCLUDE_OBJ_OWNERSHIP \
			INCLUDE_VXEVENTS
#endif /* _WRS_CONFIG_CERT */

#ifdef _WRS_CONFIG_COMPAT69_ADR_SPACE
	CFG_PARAMS	RTP_HOOK_TBL_SIZE \
			SYSCALL_HOOK_TBL_SIZE \
			RTP_SIGNAL_QUEUE_SIZE \
			RTP_HEAP_INIT_SIZE \
			RTP_HEAP_DEFAULT_OPTIONS \
			RTP_FD_NUM_MAX \
			RTP_CODE_REGION_START \
			RTP_CODE_REGION_SIZE \
			RTP_OVERLAPPED_ADDRESS_SPACE \
			RTP_MEM_FILL
#else /* _WRS_CONFIG_COMPAT69_ADR_SPACE */
	CFG_PARAMS	RTP_HOOK_TBL_SIZE \
			SYSCALL_HOOK_TBL_SIZE \
			RTP_SIGNAL_QUEUE_SIZE \
			RTP_HEAP_INIT_SIZE \
			RTP_HEAP_DEFAULT_OPTIONS \
			RTP_FD_NUM_MAX \
			RTP_MEM_FILL
#endif /* _WRS_CONFIG_COMPAT69_ADR_SPACE */
}

Component INCLUDE_RTP_ARCH {
        NAME            Arch components for RTP
        _CHILDREN       FOLDER_NOT_VISIBLE
        REQUIRES        INCLUDE_RTP
}

Component INCLUDE_RTP_SIGNALS {
	NAME		Signals (RTP)
	SYNOPSIS	This component provides POSIX signal support for RTPs.
	MODULES		rtpSigLib.o rtpSigScLib.o
	INIT_RTN	rtpSigLibInit ();
	REQUIRES	INCLUDE_RTP INCLUDE_SIGNALS
	INCLUDE_WHEN	INCLUDE_RTP \
			INCLUDE_SIGNALS
	HDR_FILES	rtpLib.h private/rtpSigLibP.h private/sigLibP.h
	INIT_AFTER      INCLUDE_RTP	
}

#ifndef _WRS_CONFIG_CERT
Component INCLUDE_RTP_SYMBOL_TABLE {
	NAME		Symbol table support (RTP)
	SYNOPSIS	This component provides symbol table support for RTPs. To \
			support debugging, this feature allows you to register symbols \
			during or after you load any RTPs and shared libraries. 
	MODULES		loadRtpSymLib.o
	INIT_RTN	loadRtpSymLibInit ();
	_INIT_ORDER	usrSymTblInit
	INIT_AFTER      INCLUDE_RTP
	INCLUDE_WHEN	INCLUDE_SYM_TBL INCLUDE_RTP
        _CHILDREN       FOLDER_NOT_VISIBLE
}
#endif /* _WRS_CONFIG_CERT */

Component INCLUDE_RTP_SHOW {
	NAME		Show routines (RTP)
	SYNOPSIS	This component provides support for the rtpMemShow(), \
			rtpShow(), and rtpHookShow() functions. It is also a \
			requirement for syscallShow(). This component, along with \
			INCLUDE_DISK_UTIL, provide useful shell functions.
	MODULES		rtpShow.o
	INIT_RTN	rtpShowInit ();
	HDR_FILES	rtpLib.h
	INCLUDE_WHEN	INCLUDE_RTP \
			INCLUDE_SHOW_ROUTINES
	_CHILDREN	FOLDER_SHOW_ROUTINES
	_INIT_ORDER	usrShowInit

}

Component INCLUDE_SHARED_DATA {
	NAME		Shared data region support
	SYNOPSIS	This component provides data sharing between RTPs or the kernel. \
			It is included in the BUNDLE_RTP_DEPLOY bundle.
	MODULES		sdLib.o
	INIT_RTN	sdLibInit (SD_HOOK_TBL_SIZE);
	CFG_PARAMS	SD_HOOK_TBL_SIZE
	REQUIRES	INCLUDE_RTP INCLUDE_SC_SD
	HDR_FILES	sdLib.h private/sdLibP.h
}

Component INCLUDE_SHARED_DATA_SHOW {
	NAME		Shared data show routine
	SYNOPSIS	This component adds sdShow() to display information \
			on shared data regions. It is included in the BUNDLE_RTP_DEVELOP bundle. 
	MODULES		sdShow.o
	INIT_RTN	sdShowInit ();
	REQUIRES	INCLUDE_SHARED_DATA
	HDR_FILES	sdLib.h
	INCLUDE_WHEN	INCLUDE_SHARED_DATA \
			INCLUDE_SHOW_ROUTINES
	_CHILDREN	FOLDER_SHOW_ROUTINES
	_INIT_ORDER	usrShowInit
	INIT_AFTER      INCLUDE_RTP_SHOW	
}

Component INCLUDE_SHL {
	NAME		Shared library support
	SYNOPSIS	This component provides support for the sharing of code \
			between RTPs. This component is required for shared library support.
	MODULES		shlLib.o
	INIT_RTN	shlLibInit ();
	REQUIRES	INCLUDE_RTP \
			INCLUDE_SC_SHL \
			INCLUDE_RTP_HOOKS
	HDR_FILES	shlLib.h
}

Component INCLUDE_SHL_SHOW {
	NAME		Shared library show routines
	SYNOPSIS	This component adds show functions to display information \
			about shared libraries in RTPs. It is included in the \
			BUNDLE_RTP_DEVELOP bundle.
	MODULES		shlShow.o
	INIT_RTN	shlShowInit ();
	REQUIRES	INCLUDE_SHL
	HDR_FILES	shlLib.h
	INCLUDE_WHEN	INCLUDE_SHL \
			INCLUDE_SHOW_ROUTINES
	_CHILDREN	FOLDER_SHOW_ROUTINES
	_INIT_ORDER	usrShowInit
	INIT_AFTER      INCLUDE_RTP_SHOW	
}

Component INCLUDE_RTP_SHELL_C {
	NAME		Shell C routines
	SYNOPSIS	This component provides a list of commands for the shell C \
			interpreter related to RTPs. Before starting an RTP, you must \
			build a VxWorks image project with either this component or \
			INCLUDE_RTP_SHOW_SHELL_CMD enabled. However, using this component \
			allows you to use the rtpSp command directly (without a prior cmd).
	MODULES		usrRtpLib.o
	INIT_RTN	usrRtpLibInit ();
	PROTOTYPE	extern STATUS usrRtpLibInit();
	_INIT_ORDER	usrToolsInit
	_CHILDREN       FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_RTP
	INCLUDE_WHEN	INCLUDE_RTP INCLUDE_SHELL_INTERP_C
}


Component INCLUDE_RTP_HOOKS {
	NAME		Hook support (RTP)
	SYNOPSIS	This component includes hook functions that can be called on \
			RTP operations. It also enables the initialization of a shared \
			library. In addition, it allows you to register kernel functions \
			that can be executed at various points in a process' life cycle. \
			This component is included in the BUNDLE_RTP_DEPLOY bundle.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		rtpHookLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	INIT_RTN	rtpHookLibInit (RTP_HOOK_TBL_SIZE);
	REQUIRES	INCLUDE_RTP \
                        INCLUDE_HOOKS
}

Component INCLUDE_SYSCALL_HOOKS {
	NAME		System call hook support
	SYNOPSIS	This component includes hook functions that can be called on \
			system calls.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		syscallHookLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	INIT_RTN	syscallHookLibInit ();
	REQUIRES	INCLUDE_RTP \
                        INCLUDE_HOOKS
	_INIT_ORDER	usrKernelExtraInit
}

/* 
 * INCLUDE_RTP_POSIX_PSE52 is a utility component. This component
 * does not drag in code, it simply sets a set of parameters appropriate
 * for PSE52 support. This component alone does not provide PSE52 support,
 * it requires inclusion of the set of CDF components associated with PSE52,
 * as done in the BUNDLE_RTP_POSIX_PSE52 bundle.
 * This component is hidden to avoid confusion. Users are encouraged to 
 * use the BUNDLE_RTP_POSIX_PSE52 to pick up PSE52 support.
 */

Component INCLUDE_RTP_POSIX_PSE52 {
	NAME		POSIX PSE52 support for RTPs
	SYNOPSIS	Utility component used in configlette code to set parameters appropriately for POSIX PSE52.
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Component INCLUDE_POSIX_THREAD_CPUTIME {
        NAME            POSIX thread CPU-time clock
        SYNOPSIS        This component supports an RTP-only thread CPU-time \
                        clock/timer. For more information, see the POSIX \
                        information in the VxWorks 7 Programmer's Guide.
        MODULES         pxCpuTimerLib.o
        INIT_RTN        pxCpuTimeLibInit ();
        HDR_FILES       private/pxCpuTimeLibP.h
	_CHILDREN	FOLDER_RTP
	_INIT_ORDER	usrKernelExtraInit
	INIT_AFTER      INCLUDE_POSIX_TIMERS	
        REQUIRES        INCLUDE_POSIX_TIMERS INCLUDE_POSIX_CLOCKS \
                        INCLUDE_POSIX_PTHREAD_SCHEDULER
}

Parameter RTP_FD_NUM_MAX
	{
	NAME		Number of entries in an RTP fd table
	SYNOPSIS	For any given RTP, the maximum number of file descriptors (fd) \
			for all I/O devices cannot exceed the value of this parameter.
	TYPE		uint
	DEFAULT		20
	}

Parameter RTP_HOOK_TBL_SIZE
	{
	NAME		Number of entries in the RTP create/delete hook table
	SYNOPSIS	The value of this configuration parameter specifies the number \
			of entries in the RTP hook table.
        TYPE 		uint
        DEFAULT 	16
	}

Parameter SD_HOOK_TBL_SIZE
	{
	NAME		Number of entries in the SD hook tables
	SYNOPSIS	This parameter defines the number of entries in the shared data \
			(SD) hook tables.
        TYPE 		uint
        DEFAULT 	8
	}

Parameter SYSCALL_HOOK_TBL_SIZE
	{
	NAME		Number of entries in the system call hook tables
	SYNOPSIS	This parameter sets the number of entries in the system call \
			hook tables. If system call hook functions are not required or \
			used in a deployed system, set this parameter's value to zero \
			(doing so also disables the syscallMonitor() facility).
        TYPE 		uint
        DEFAULT 	8
	}

Parameter RTP_HEAP_DEFAULT_OPTIONS {
        NAME            Memory partition options for the RTP heap
        SYNOPSIS        This parameter defines the default memory partition \
                        for an RTP heap.
        TYPE            UINT
        DEFAULT         (MEM_ALLOC_ERROR_LOG_FLAG      | \
                         MEM_ALLOC_ERROR_EDR_WARN_FLAG | \
                         MEM_BLOCK_ERROR_LOG_FLAG      | \
                         MEM_BLOCK_ERROR_EDR_FATAL_FLAG | \
                         MEM_BLOCK_CHECK)
}

Parameter RTP_HEAP_INIT_SIZE
        {
        NAME            Initial size of the heap
        SYNOPSIS        This parameter sets the initial size in bytes for the \
                        heap for each RTP created; the HEAP_INITIAL_SIZE \
                        environment variable can override this parameter.
        TYPE            uint
        DEFAULT         0x10000
        }

Parameter RTP_SIGNAL_QUEUE_SIZE
	{
	NAME		Number of queued signals
	SYNOPSIS        This parameter defines the maximum number of queued signals \
			allowed in a process. The default value, 32, is set in accordance \
			with the POSIX 1003.1 standard (_POSIX_SIGQUEUE_MAX). Changing the \
			value to a lower number can cause problems for applications \
			relying on POSIX guidelines. For POSIX, this value must be at least 32.
        TYPE 		uint
        DEFAULT 	32
	}

#ifdef _WRS_CONFIG_COMPAT69_ADR_SPACE
/*
 * For 64-bit VxWorks, RTPs are always executed in an overlapped
 * virtual memory space and nothing about this is configurable.
 */

Parameter RTP_CODE_REGION_START
	{
	NAME		Memory area for an absolutely linked RTP
	SYNOPSIS	This parameter defines the base address of the virtual memory \
			region reserved for the text and data/bss segments (that is, all \
			loadable sections) of absolutely linked RTP executables. If \
			the address is null, no such region is reserved.
	TYPE		uint
	DEFAULT		0
	}

Parameter RTP_CODE_REGION_SIZE
	{
	NAME		Size of the area for an absolutely-linked RTP
	SYNOPSIS	This parameter sets the size of the virtual memory region \
			reserved for the text and data/bss segments (that is, all loadable \
			sections) of absolutely linked RTP executables. If \
			the size is null, no such region is reserved.
	TYPE		uint
	DEFAULT		0
	}

Parameter RTP_OVERLAPPED_ADDRESS_SPACE
	{
	NAME		Use overlapped virtual address space
	SYNOPSIS	This parameter controls whether each RTP has its own private \
			view of the virtual address space (all views overlapping) or \
			whether they all share a flat virtual address space \
			(legacy). By default, RTPs run in overlapped mode.
	TYPE		bool
	DEFAULT		TRUE
	}
#endif /* _WRS_CONFIG_COMPAT69_ADR_SPACE */

Component INCLUDE_MEM_RTP {
	NAME		Memory configuration setup
	SYNOPSIS	This component initializes memory parameters to pass to the RTP.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		memRtpLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	HDR_FILES	private/rtpLibP.h
	INIT_RTN	memRtpLibInit (RTP_HEAP_INIT_SIZE,RTP_HEAP_DEFAULT_OPTIONS);
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER	usrScInit
}

Folder	FOLDER_RTP_STARTUP_FACILITY {
	NAME		RTP startup facility
	SYNOPSIS	This folder contains different startup facilities \
			that can be used to launch an RTP.
	_CHILDREN	FOLDER_APPLICATION
	CHILDREN	INCLUDE_RTP_APPL_USER \
                        INCLUDE_RTP_APPL_INIT_STRING \
			INCLUDE_RTP_APPL_INIT_BOOTLINE \
			INCLUDE_RTP_APPL_INIT_CMD_SHELL_SCRIPT
}

Component INCLUDE_RTP_APPL_USER {
	NAME		5. User space entry point
	SYNOPSIS    	This component launches an RTP from a user-defined \
			function. It is used to configure usrRtpAppInit() \
			and is in the BUNDLE_RTP_DEPLOY bundle.
	PROTOTYPE	void usrRtpAppInit (void);
	INIT_RTN	usrRtpAppInit ();
	REQUIRES	INCLUDE_RTP 
	_INIT_ORDER     usrRoot
	HELP		RTP Application Startup facility
}

Component INCLUDE_RTP_APPL_INIT_STRING {
	NAME		6. RTP launcher
	SYNOPSIS    	This component launches RTPs from a string-encoded list. \
			That list is defined by this component's parameter, \
			RTP_APPL_INIT_STRING. This component is almost the same as \
			INCLUDE_RTP_APPL_INIT_BOOTLINE in both format and behavior. The \
			difference between the two being that INCLUDE_RTP_APPL_INIT_STRING \
			can accept both whitespace and ^ delimiters in its input string.
	CONFIGLETTES	usrRtpAppInitString.c
	INIT_RTN	usrRtpAppInitString ();
	CFG_PARAMS	RTP_APPL_INIT_STRING
	REQUIRES	INCLUDE_RTP 
	_INIT_ORDER     usrRoot
	HELP		RTP Application Startup facility
}

Parameter RTP_APPL_INIT_STRING {
	NAME		String-encoded RTP list
	SYNOPSIS	This parameter hosts a string-encoded list of RTPs that will \
			be launched after bootup. For more information, see the "VxWorks 7 \
			Programmer's Guide: Automatic Execution of RTP Applications."
    	TYPE            string
	DEFAULT		""
}

Parameter RTP_MEM_FILL {
	NAME		Memory cleared before allocation
	SYNOPSIS	When set to TRUE, this parameter fills the RTP stack with 0xee, \
			and all other RTP memory allocations with 0. This parameter \
			overrides VX_NO_STACK_FILL for the RTP execution stack. \
			VX_GLOBAL_NO_STACK_FILL overrides this component (RTP_MEM_FILL) \
			for the RTP task execution stack. A TRUE value implies memory \
			allocated to private mapping is initialized to 0. This improves \
			security but decreases performance. Set to FALSE to improve performance.
	TYPE		BOOL
	DEFAULT		TRUE
}

Component INCLUDE_RTP_APPL_INIT_BOOTLINE {
	NAME		7. Boot line RTP launcher
	SYNOPSIS    	This parameter launches RTPs from a string-encoded list in \
			the boot parameters (see also INCLUDE_RTP_APPL_INIT_STRING). These \
			RTPs are started automatically at boot time.
	CONFIGLETTES	usrRtpAppInitBootline.c
	INIT_RTN	usrRtpAppInitBootline ();
	REQUIRES	INCLUDE_RTP 
	_INIT_ORDER     usrRoot
	HELP		RTP Application Startup facility
}

/*
 * system call sub-components are always included, be sure to
 * add them to the REQUIRES list for INCLUDE_RTP.  Since they are
 * not individually selectable, attach them to the NOT_VISIBLE folder.
 * They are initialized last, just before the user application.
 */

Component INCLUDE_SC_KERNEL {
	NAME		WIND system call handlers
	SYNOPSIS	system call handlers for WIND kernel 
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		windScLib.o vxAtomicScLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	PROTOTYPE	void windScInit (void);
	INIT_RTN	windScInit ();
#ifdef _WRS_CONFIG_CERT
	REQUIRES	INCLUDE_TASK_CREATE_DELETE
#else
	REQUIRES	INCLUDE_TASK_CREATE_DELETE	\
			INCLUDE_TASK_RESTART
#endif
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER     usrScInit
}

Component INCLUDE_SC_MMAN {
	NAME		Memory management system call handlers
	SYNOPSIS	system call handlers for memory management
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		mmanScLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	PROTOTYPE	void mmanScLibInit (void);
	INIT_RTN	mmanScLibInit ();
	REQUIRES	INCLUDE_MMAP
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER     usrScInit
}

Component INCLUDE_SC_SD {
	NAME		Shared Data system call handlers
	SYNOPSIS	system call handlers for shared data
	MODULES		sdScLib.o sdLib.o
	PROTOTYPE	void sdScInit (void);
	INIT_RTN	sdScInit ();
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER     usrScInit
}

Component INCLUDE_SC_SHL {
	NAME		Shared Library system call handlers
	SYNOPSIS	system call handlers for shared libraries
	MODULES		shlScLib.o shlLib.o
	PROTOTYPE	void shlScLibInit (void);
	INIT_RTN	shlScLibInit ();
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER     usrScInit
}

Component INCLUDE_SC_RTP_LIMITS {
	NAME		RTP limits system call handler
	SYNOPSIS	system call handler for RTP prlimits
	MODULES		rtpIoLib.o
#ifndef _WRS_CONFIG_CERT
	INCLUDE_WHEN	INCLUDE_SC_IOS
#endif
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER     usrScInit
}

Component INCLUDE_SC_PIPE {
	NAME		pipe system call handler
	SYNOPSIS	system call handler for pipes
	MODULES		iosPipeScLib.o
#ifndef _WRS_CONFIG_CERT
	INCLUDE_WHEN	INCLUDE_SC_IOS
#endif
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER     usrScInit
}

Component INCLUDE_SC_IOS {
	NAME		IOS system calls
	SYNOPSIS	IOS system calls
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		iosScLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	INIT_RTN	iosScLibInit ();
	HDR_FILES	iosScLib.h
	REQUIRES	INCLUDE_RTP \
			INCLUDE_IO_RTP
	_CHILDREN	FOLDER_NOT_VISIBLE
	_INIT_ORDER     usrScInit
}

/* Attach RTP_SHOW to SHOW ROUTINES folder, init with other show routines */

