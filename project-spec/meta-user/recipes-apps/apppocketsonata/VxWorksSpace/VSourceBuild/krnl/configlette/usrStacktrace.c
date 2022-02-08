/* usrStacktrace.c - configuration file for stacktrace support */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03jun14,sdt  Fix dependency with shared data
27may14,sdt  Written
*/

/*
DESCRIPTION

This library configures and initializes the stacktrace support
*/

/* Includes */

#include <st_stdbool.h>

/* externals */

extern char wrs_kernel_text_start[];
extern char wrs_kernel_text_end[];
extern bool ST_context_init(void * tS, void * tE);

#ifdef	INCLUDE_STACKTRACE_MODULE
extern void stacktraceModuleHooksInit(void);
#endif /* INCLUDE_STACKTRACE_MODULE */

#ifdef INCLUDE_RTP
extern void stacktraceRtpHooksInit(void);
#endif /* INCLUDE_RTP */

#ifdef INCLUDE_STACKTRACE_SHD
extern void stacktraceShdHooksInit(void);
#endif /* INCLUDE_STACKTRACE_SHD */


/******************************************************************************
*
* usrStacktraceInit - configure and initialize the stacktrace support
*
*/

void usrStacktraceInit(void)
{
#ifdef	INCLUDE_STACKTRACE_MODULE
	stacktraceModuleHooksInit();
#endif

#ifdef INCLUDE_RTP
	stacktraceRtpHooksInit();
#endif

#ifdef INCLUDE_STACKTRACE_SHD
	stacktraceShdHooksInit();
#endif

	(void)ST_context_init(wrs_kernel_text_start, wrs_kernel_text_end);
}
