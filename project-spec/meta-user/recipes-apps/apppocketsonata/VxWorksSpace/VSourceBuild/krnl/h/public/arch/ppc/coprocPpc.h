/* coprocPpc.h - coprocessor management library header */

/*
 * Copyright 2003-2004, 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,15may12,jmp  CQID: Fix WIND00309977 : Added VX_COPROCS_ALL_TASK
                 definition.
01b,28apr10,pad  Moved extern C statement after include statements.
01a,23jan04,dtr  Adding in SPE support.
01b,04feb04,aeg  removed include of altivecLib.h
01a,?????03,???  written.
*/

#ifndef __INCcoprocPpch
#define __INCcoprocPpch

/* includes */

#include "taskLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define VX_FP_TASK         VX_COPROC1_TASK
#define VX_ALTIVEC_TASK    VX_COPROC2_TASK
#define VX_SPE_TASK        VX_COPROC3_TASK

#define VX_COPROCS_ALL_TASK	VX_FP_TASK | VX_ALTIVEC_TASK | VX_SPE_TASK

#ifdef __cplusplus
}
#endif

#endif /* __INCcoprocPpch */
