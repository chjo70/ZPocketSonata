/* smaLib.h - gdbServer header file */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21jan14,elp  moved arch headers to private.
24nov14,jmp  Fixed RTP dependency (V7COR-2267).
19nov14,sdt  Added exceptions support (US44279)
07jul14,jmp  created from Hypervisor 2.1 gdb serial code.
*/

#ifndef __INCsmaLibh
#define __INCsmaLibh

#include <vxWorks.h>
#include <smaProtocolLib.h>
#include <regs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* define */

/* debug states */

#define NOT_DEBUGGING   0
#define DEBUGGING       1
#define STOP_RUNNING    2
#define SINGLE_STEP     3

#define HW_BP_FEATURE   "org.gnu.gdb.wr.hwbp"

#if defined(WRHV_ARCH_HAS_LOCAL_MEM_SYNC)
#define VARIABLE_WRITE_SYNC(var,value)  var=value;\
                                        archMemWriteSync (&var, sizeof(var))
#define MEM_WRITE_SYNC(ptr,size)        archMemWriteSync (ptr, size)
#else
#define VARIABLE_WRITE_SYNC(var,value)  var=value
#define MEM_WRITE_SYNC(ptr,size)
#endif

#define MAX_SW_BP       200     /* Maximum number of software breakpoints */

/* GDB operation requests (cannot be OR'ed) */
#define GDB_NO_OP               0
#ifdef  GDB_ARCH_HAS_SKIP_BP
#define GDB_DO_RESUME           1
#endif  /* GDB_ARCH_HAS_SKIP_BP */

#ifndef _ASMLANGUAGE

/* typedef */

/* GDB protocol breakpoint type */

typedef struct
    {
    const char * name;			/* XML entry name */
    const char * value;			/* XML entry value */
    } XML_ARCH_DEFS;

/* function declaration */

extern STATUS   smaInit (void * pStackBase);
extern BOOL     smaExcHandle (int excType, void * pInfo, BOOL systemSuspend);
#ifdef	_WRS_CONFIG_RTP
extern STATUS   smaRtpLibInit (void);
#endif  /* _WRS_CONFIG_RTP */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCsmaLibh */
