/* unldLibP.h - private header for unload library */

/*
 * Copyright (c) 2009-2010, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
04nov14,jmp  Added unldCompleteHook() for VxWorks TOS module tracking (US44278).
             Removed obsolete syncUnldRtn function pointer.
29apr10,pad  Moved extern C statement after include statements.
25feb10,rlp  Removed unldBreakpointsRemove routine.
23feb10,rlp  Added unldBreakpointsRemove prototype (WIND00201223).
03feb10,v_r  Adapted for host side usage.
03feb10,rlp  Added syncUnldRtn function poinrer declaration.
25sep09,v_r  Written.
*/

#ifndef __INCunldLibPh
#define __INCunldLibPh

#ifdef HOST
#include <host.h>
#else /* HOST */
#include <vxWorks.h>
#endif /* !HOST */
#include <moduleLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS (* _func_unldByModuleId)
    (
    MODULE_ID   moduleId,	/* module ID to unload */
    int         options		/* options */
    );

extern void __attribute__ ((noinline)) unldCompleteHook (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCunldLibPh */
