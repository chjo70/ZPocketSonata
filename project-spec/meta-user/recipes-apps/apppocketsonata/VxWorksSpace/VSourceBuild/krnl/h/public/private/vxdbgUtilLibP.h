/* vxdbgUtilLibP.h - VxDBG library utilities header file */

/*
 * Copyright (c) 2006-2007, 2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
10jul15,vhe  enabled single-step using debug registers (F1122)
21sep10,rlp  Added usrBreakpointInit() prototype.
29apr10,pad  Moved extern C statement after include statements.
27sep07,rlp  Modified usrBreakpointSet prototype to add a cache flush
             policy (CQ:WIND00104297, CQ:WIND00104323, CQ:WIND00104325).
26oct06,rlp  Written
*/

#ifndef __INCvxdbgUtilLibPh
#define __INCvxdbgUtilLibPh

/* includes */

#include <vxWorks.h>
#include <private/vxdbgLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* For UP systems, VXDBG_LOCAL_FLUSH and VXDBG_FLUSH are equivalent. */

typedef enum vxdbg_cache_policy
    {
    VXDBG_NO_FLUSH,			/* no flush required */
    VXDBG_LOCAL_FLUSH,			/* flush the local CPU cache only */
    VXDBG_FLUSH				/* flush cache on all CPUs */
    } VXDBG_CACHE_POLICY;

#ifndef _ASMLANGUAGE

/* externs */

#if     DBG_NO_SINGLE_STEP || DBG_STEP_AND_BP_SHARED_VEC
/* WDB debug trap handler */

extern BOOL	(*_func_wdbTrap) (int level, INSTR * addr, void * pInfo,
				REG_SET * pRegisters, void * pDbgRegSet,
                                BOOL hardware);
/* VxDBG trap handler */

extern BOOL	(*_func_vxdbgTrap) (int level, INSTR * addr, void * pInfo,
				REG_SET * pRegisters, void * pDbgRegSet,
                                BOOL hardware);
#else   /* DBG_NO_SINGLE_STEP */
/* WDB breakpoint handler */

extern BOOL	(*_func_wdbBreakpoint) (int level, void * pInfo,
                                REG_SET * pRegisters, void * pDbgRegSet,
                                BOOL hardware);

/* WDB trace handler */

extern BOOL	(*_func_wdbTrace) (int level, void * pInfo,
				REG_SET * pRegisters);

/* VxDBG breakpoint handler */

extern BOOL	(*_func_vxdbgBreakpoint) (int level, void * pInfo,
                                REG_SET * pRegisters, void * pDbgRegSet,
                                BOOL hardware);

/* VxDBG trace handler */

extern BOOL	(*_func_vxdbgTrace) (int level, void * pInfo,
				REG_SET * pRegisters);
#endif  /* DBG_NO_SINGLE_STEP */

/* function declarations */

extern STATUS	vxdbgBpAddrCheck (RTP_ID memCtx, INSTR * addr, INSTR * val);

#if     DBG_NO_SINGLE_STEP || DBG_STEP_AND_BP_SHARED_VEC
extern void	wdbDbgTrap (INSTR * addr, REG_SET * pRegisters,
					void * pInfo, void * pDbgRegSet,
					BOOL hardware);
#else   /* DBG_NO_SINGLE_STEP */
extern void	wdbDbgBreakpoint (void * pInfo, REG_SET * pRegisters,
                                        void * pDbgRegSet, BOOL hardware);
extern void	wdbDbgTrace (void * pInfo, REG_SET * pRegisters);
#endif  /* DBG_NO_SINGLE_STEP */
extern void	usrBreakpointSet (INSTR * addr, INSTR value,
					RTP_ID pid, VXDBG_CACHE_POLICY policy);
extern void	usrBreakpointInit (void);

#endif	/* _ASMLANGUAGE */
#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgUtilLibPh */
