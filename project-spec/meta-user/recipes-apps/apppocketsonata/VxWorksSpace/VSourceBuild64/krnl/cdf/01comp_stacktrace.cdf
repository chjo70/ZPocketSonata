/* 01comp_stacktrace.cdf - cafe components */

/*
 * Copyright (c) 2010-2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
28sep14,gxu  Hide "stacktrace sampler" in vxworks configure GUI - WB4-3663
03jun14,sdt  Fix dependency with shared data
27may14,sdt  Reworked stacktrace module part support - WB4-3207
20may14,sdt  Renamed memory_map_module_vx
03apr14,wzc  fix the initilization sequence.(WB4-3054)
17feb14,wzc  remove the dependency on module manager(WB4-2684)
*/

/*
DESCRIPTION
This file contains component descriptions for the stack tracing library.
*/


#if (defined _WRS_CONFIG_STACKTRACE)

Component INCLUDE_STACKTRACE_MODULE {
	NAME		Stacktrace module support
	SYNOPSIS	module manager's hooks for stack trace library
	MODULES		memory_map_module_vx.o
	INCLUDE_WHEN	INCLUDE_STACKTRACE INCLUDE_MODULE_MANAGER
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Component INCLUDE_STACKTRACE_SHD {
	NAME		Stacktrace shared data support
	SYNOPSIS	shared data's hooks for stack trace library
	MODULES		memory_map_shd_vx.o
	INCLUDE_WHEN	INCLUDE_STACKTRACE INCLUDE_SHARED_DATA INCLUDE_SC_SD
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Component INCLUDE_STACKTRACE {
	NAME		Stack tracing logic
	SYNOPSIS	Stack tracing logic
	CONFIGLETTES	usrStacktrace.c
	PROTOTYPE	IMPORT void usrStacktraceInit(void);
	INIT_RTN	usrStacktraceInit();
	INIT_AFTER	usrLoaderInit
	_INIT_ORDER	usrToolsInit
	_CHILDREN	FOLDER_TOOLS
}

#ifdef _WRS_CONFIG_COMPONENT_STACKTRACE_SAMPLER_TEST
Component INCLUDE_STACKTRACE_SAMPLER {
        NAME            Stacktrace sampler test
        SYNOPSIS        Collects periodic stacktrace samples from a running \
                        system, collecting statistics and data on both \
                        successful and failed traces.
        LINK_SYMS       ST_ContextSamplerTest
        _CHILDREN       FOLDER_NOT_VISIBLE
        REQUIRES        INCLUDE_STACKTRACE
}
#endif  /* COMPONENT_STACKTRACE_SAMPLER_TEST */

#endif  /* ifdef _WRS_CONFIG_STACKTRACE */
