/* ppcArchVarsP.h - PowerPC private variables */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,21sep10,jpb  created
*/

#ifndef __INCppcArchVarsPh
#define __INCppcArchVarsPh

#ifdef __cplusplus
extern "C" {
#endif

extern FUNCPTR _func_mmuCacheFlushLoadAdrsGet;

extern FUNCPTR _func_ppc440x5RefreshTlb0;
extern FUNCPTR _func_cache440EarlyCleanup;

extern FUNCPTR _func_cacheArchEnable;
extern FUNCPTR _func_cacheArchDisableFromMmu;


#ifdef __cplusplus
}
#endif

#endif /* __INCppcArchVarsPh */
