/* taskHookLib.h - header file for taskHookLib.c */

/*
 * Copyright (c) 1984-1992, 2008-2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02d,10mar09,zl   updated for LP64
02c,04sep08,gls  renamed taskHookInit() to taskCreateHookInit()
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCtaskHookLibh
#define __INCtaskHookLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern void	taskCreateHookInit (void);
extern STATUS 	taskCreateHookAdd (FUNCPTR createHook);
extern STATUS 	taskCreateHookDelete (FUNCPTR createHook);
extern STATUS 	taskDeleteHookAdd (FUNCPTR deleteHook);
extern STATUS 	taskDeleteHookDelete (FUNCPTR deleteHook);
extern STATUS 	taskSwapHookAdd (FUNCPTR swapHook);
extern STATUS 	taskSwapHookAttach (FUNCPTR swapHook, TASK_ID tid, 
				    BOOL in, BOOL out);
extern STATUS 	taskSwapHookDelete (FUNCPTR swapHook);
extern STATUS 	taskSwapHookDetach (FUNCPTR swapHook, TASK_ID tid, 
				    BOOL in, BOOL out);
extern STATUS 	taskSwitchHookAdd (FUNCPTR switchHook);
extern STATUS 	taskSwitchHookDelete (FUNCPTR switchHook);
extern void	taskHookShowInit (void);
extern void 	taskCreateHookShow (void);
extern void 	taskDeleteHookShow (void);
extern void 	taskSwapHookShow (void);
extern void 	taskSwitchHookShow (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskHookLibh */
