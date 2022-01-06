/* 01vxdbg.cdf - VxDBG component description file */

/*
 * Copyright (c) 2007,2011,2013-2014,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
28jan16,jmp  Added INCLUDE_VXDBG_RTP component (Replace INCLUDE_RTP_DEBUG
             which is not delivered by correct layer) (V7COR-3068).
16may14,rlp  Removed WDB references (WB4-1735)
05mar14,ten  Added hdr file for vxdbgCpuLibInit to INCLUDE_VXDBG_CPU_CONTROL
09aug13,cww  Updated INCLUDE_VXDBG_HOOK due to modified
             INCLUDE_TASK_CREATE_HOOKS initialization
21may13,rlp  Added vxdbgLibInit header file.
16mar11,jmp  Performed some component naming/synopsis updates.
12nov10,mze  _WRS_VX_SMP is now obsolete replaced with _WRS_CONFIG_SMP
02jun10,rlp  Added a dependency on task create and switch hooks.
16apr10,rlp  Added usrBreakpoint.c configlette to INCLUDE_VXDBG_RUNCTRL.
13apr10,rlp  Added INCLUDE_VXDBG_RUNCTRL component.
25feb10,rlp  Added VxDBG module component.
18feb10,rlp  Moved INCLUDE_VXDBG initialization to usrToolsInit.
10feb10,rlp  Added INCLUDE_VXDBG and INCLUDE_VXDBG_HOOK components.
04oct07,mze  fix for 104829
19jul07,jmp  written.
*/

/*
DESCRIPTION
This file contains descriptions for the VxDBG components.
*/

Component INCLUDE_VXDBG {
	NAME		VxWorks debug library
	SYNOPSIS	Support for the runtime debug library
	MODULES		vxdbgLib.o
	CONFIGLETTES	usrVxdbg.c
	HDR_FILES	vxdbgLibInit.h
	INIT_RTN	usrVxdbgInit (VXDBG_EVT_TASK_PRIORITY,	\
					   VXDBG_EVT_TASK_OPTIONS,	\
					   VXDBG_EVT_TASK_STACK_SIZE);
        CFG_PARAMS      VXDBG_EVT_TASK_PRIORITY	\
			VXDBG_EVT_TASK_OPTIONS	\
			VXDBG_EVT_TASK_STACK_SIZE
	REQUIRES	INCLUDE_VXDBG_HOOK
}

Parameter VXDBG_EVT_TASK_STACK_SIZE {
        NAME            VxDBG task stack size
        SYNOPSIS        Defines stack size of VxDBG task (bytes)
        TYPE            uint
	DEFAULT		8192
}

Parameter VXDBG_EVT_TASK_PRIORITY {
        NAME            VxDBG task priority
	SYNOPSIS	Defines priority of VxDBG task
        TYPE            uint
        DEFAULT         25
}

Parameter VXDBG_EVT_TASK_OPTIONS {
        NAME            VxDBG events task options
	SYNOPSIS	Defines options of VxDBG task
        DEFAULT         VX_UNBREAKABLE | VX_FP_TASK
}

Component INCLUDE_VXDBG_RUNCTRL {
	NAME		VxWorks RunControl debug library
	SYNOPSIS	runControl support of the runtime debug library
	CONFIGLETTES    usrBreakpoint.c
	MODULES		vxdbgRunCtrlLib.o
	REQUIRES	INCLUDE_VXDBG \
			INCLUDE_TASK_SWITCH_HOOKS
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Component INCLUDE_VXDBG_HOOK {
	NAME		VxWorks debug library hooks
	SYNOPSIS	hooks for the runtime debug library
	INIT_RTN	vxdbgHooksInit ();
        _INIT_ORDER     usrKernelCoreInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_TASK_CREATE_HOOKS
}

Component INCLUDE_VXDBG_MODULE {
	NAME		VxWorks debug library module support
	SYNOPSIS	module management support for the runtime debug library
	MODULES		vxdbgModuleLib.o
	INCLUDE_WHEN	INCLUDE_VXDBG_RUNCTRL INCLUDE_UNLOADER
	_CHILDREN	FOLDER_NOT_VISIBLE
}

#ifdef	_WRS_CONFIG_RTP
Component INCLUDE_VXDBG_RTP {
	NAME		VxWorks process debugging facilities
	SYNOPSIS	Initialize process debugging library.
	INIT_RTN	vxdbgRtpLibInit ();
        _INIT_ORDER     usrKernelCoreInit
	HDR_FILES	vxdbgLibInit.h
	_CHILDREN	FOLDER_NOT_VISIBLE
	INCLUDE_WHEN	INCLUDE_VXDBG INCLUDE_RTP
	REQUIRES	INCLUDE_RTP INCLUDE_RTP_HOOKS
}
#endif	/* _WRS_CONFIG_RTP */

#ifdef _WRS_CONFIG_SMP
Component INCLUDE_VXDBG_CPU_CONTROL {
	NAME		VxDBG CPU control
	SYNOPSIS	CPU control support for VxDBG
	MODULES		vxdbgCpuLib.o
	INIT_RTN	vxdbgCpuLibInit ();
	REQUIRES	INCLUDE_SYSCLK_INIT \
			INCLUDE_VXIPI
	INCLUDE_WHEN	INCLUDE_CORE_DUMP
	_CHILDREN	FOLDER_NOT_VISIBLE
	HDR_FILES	vxdbgLibInit.h
}
#endif	/* _WRS_CONFIG_SMP */
