/* wvTmrLibP.h - function pointers for wvTmrLib */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,10feb10,tcr  created
*/

#ifndef __wvTmrLibPh
#define __wvTmrLibPh

#ifdef __cplusplus
extern "C" {
#endif

extern int         (*_func_tmrStamp)(void);
extern int   	   (*_func_tmrStampLock)(void);
extern int         (*_func_tmrFreq)(void);
extern int         (* _func_tmrPeriod)(void);
extern STATUS      (*_func_tmrConnect)(void (*routine)(),int arg);/* time stamp
								     function
								     pointer */
extern void	   (*_func_tmrEnable)(void);
extern void	   (*_func_tmrDisable)(void);


#ifdef __cplusplus
}
#endif


#endif /* __wvTmrLibPh */

