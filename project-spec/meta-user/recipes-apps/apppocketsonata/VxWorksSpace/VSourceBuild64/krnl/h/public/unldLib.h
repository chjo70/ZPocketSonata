/* unldLib.h - header for unload library */

/*
 * Copyright (c) 1992,1993,1996,2004,2005,2010,2013 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01q,01oct13,jdw  Add support for initializer and terminate functions (US12944)
01p,28sep10,jmp  Added errnos to indicate unload failures caused by invalid
                 load flags or invalid flags combination (CQ:WIND00039865).
01o,29apr10,pad  Moved extern C statement after include statements.
01n,23feb10,rlp  UNLD_KEEP_BREAKPOINTS is now deprecated (WIND00201223).
01m,03feb10,rlp  Removed syncUnldRtn function poinrer declaration.
01l,14apr05,v_r  Removed unnecessary includes and marked obsolete errnos.
01k,28feb05,v_r  Fixed SPR #106542 (unldByGroup not working).
		 Removed unused moduleByIdUnload().
01j,21sep04,jn   Final minor modification to allow sharing w/ host
01i,18sep04,jn   Move towards shared code on host and target
01h,05apr04,jn   Clean up - remove unused declarations and development-related
                 comments
01g,30oct96,elp  Added syncUnldRtn function pointer + UNLD_SYNC option.
01f,22aug93,jmm  added option type to supress breakpoint deletion
01e,16aug93,jmm  added new errno - S_unldLib_TEXT_IN_USE
01d,30oct92,jmm  added prototype for reld() (spr 1716)
01c,22sep92,rrr  added support for c++
01b,18sep92,jcf  added include of moduleLib.h.
01a,14may92,jmm  written.
*/

#ifndef __INCunldLibh
#define __INCunldLibh

#include <moduleLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* unldLib Status Codes */

#define S_unldLib_MODULE_NOT_FOUND		(M_unldLib | 1) /* obsoleted */
#define S_unldLib_TEXT_IN_USE			(M_unldLib | 2)
#define S_unldLib_INVALID_UNLOAD_FLAG		(M_unldLib | 3)
#define S_unldLib_ILLEGAL_FLAGS_COMBINATION	(M_unldLib | 4)
#define S_unldLib_USR_TERM_ERROR                (M_unldLib | 5)

/*
 * User options for the unloader
 *
 * The offset.c file (section unldByModuleId options) must keep in sync if a
 * new unloader option is added.
 */

#define UNLD_KEEP_BREAKPOINTS	0x1	/* deprecated */
#define UNLD_FORCE		0x2	/* Do not test whether text sections
					   are in use */

#define UNLD_CPLUS_XTOR_AUTO    0x20	/* call the C++ destructors */
#define UNLD_CPLUS_XTOR_MANUAL  0x40	/* don't call the C++ destructors */

#define UNLD_CALL_TERM_AUTO     0x100   /* Exec usr terminate (default) */
#define UNLD_CALL_TERM_MANUAL   0x200   /* Skip usr terminate */

/* The following options are restricted for internal use only */

#define UNLD_SYNC		0x10000	/* already synchronizing a module */

/* globals */

/* function declarations */

extern STATUS unldByGroup(UINT16 group, int options);
extern STATUS unldByModuleId(MODULE_ID moduleId, int options);
extern STATUS unldByNameAndPath(char * name, char * path, int options);
extern STATUS unldLibInit (void);
extern STATUS unldExecUsrTerm(MODULE_ID moduleId);

#ifdef __cplusplus
}
#endif

#endif /* __INCunldLibh */
