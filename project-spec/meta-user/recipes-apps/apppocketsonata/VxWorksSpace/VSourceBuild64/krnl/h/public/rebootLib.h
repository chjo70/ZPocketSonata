/* rebootLib.h - header file for rebootLib.c */

/*
 * Copyright (c) 1984-1992, 2005, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
02g,06oct10,jpb  Added rebootHookDelete
02f,27jul10,pad  Added C++ inline wrapper scheme for rebootHookAdd().
02e,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
02d,29jul09,cww  LP64 adaptation
02c,21mar05,yvp  Declared reboot hook table globals here.
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCrebootLibh
#define __INCrebootLibh

#ifdef __cplusplus
extern "C" {
#endif

/* externals */

IMPORT int (**pRebootHookTbl)(int);
IMPORT int rebootHookTblSize;

typedef int (* REBOOT_HOOK)(int starttype);

/* function declarations */

extern STATUS 	rebootHookAdd    (REBOOT_HOOK rebootHook);
extern STATUS 	rebootHookDelete (REBOOT_HOOK rebootHook);

extern void 	reboot (int startType);

#ifdef __cplusplus
}
/*
 * Inlined C++ wrapper for the old-style FUNCPTR-based rebootHookAdd() function
 * prototype.
 */

extern STATUS rebootHookAdd (FUNCPTR rebootHook) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline STATUS rebootHookAdd
    (
    FUNCPTR rebootHook
    )
    {
    return rebootHookAdd  ((int (*)(int))rebootHook);
    }
#endif /* __cplusplus */

#endif /* __INCrebootLibh */
