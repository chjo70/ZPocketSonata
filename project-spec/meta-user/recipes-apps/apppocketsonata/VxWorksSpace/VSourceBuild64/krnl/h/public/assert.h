/* assert.h - ANSI standard assert functions header */

/*
 * Copyright (c) 1992, 2005, 2007, 2010, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
15mar16,pad  Added CERT requirement annotation for assert() (US77388)
10sep10,mcm  Fix for WIND00046825 - added multiple inclusion protection.
29apr10,pad  Moved extern C statement after include statements.
13jul07,kk   remove _WRS_VX_SMP reference
25may05,md   added ASSERT_K, removed __STDC__ stuff.
13nov92,smb  fixed assert macro to not generate warnings
22sep92,rrr  added support for c++
20jul92,smb  added __assert extern.
04jul92,jcf  cleaned up.
03jul92,smb  written.
*/

#ifndef __INCasserth
#define __INCasserth

#include <types/vxANSI.h>

#ifdef __cplusplus
extern "C" {
#endif

#undef assert
#ifdef NDEBUG
#define assert(ignore)	((void) 0)
#else /* turn debugging on */

#define _ASSERT_STR(z) _ASSERT_TMP(z)
#define _ASSERT_TMP(z) #z

extern void __assert (const char *msg);

                                                        /* req: VX7-19730 */
#define assert(test) ((void) \
		      ((test) ? ((void) 0) : \
		       __assert("Assertion failed: "#test", file " 	\
                                __FILE__ ", line "_ASSERT_STR(__LINE__)"\n")))
#endif	/* NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* __INCasserth */
