/* loadLib.h - object module loader library header */

/*
 * Copyright (c) 1984, 1986-1988, 1990-1992, 1996, 2002, 2004-2010, 2013-2014,
 *               2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. 
 */

/*
modification history
--------------------
20apr17,aak  Added Secure Loader error handling event (F7459)
16apr14,rlp  Added new options for WR future enhancements.
	     Added a new errno if the same module is already loaded.
19mar14,rlp  LOAD_COMMON_HEAP option is now available for vx7 BSPs (VXW7-2758)
01oct13,jdw  Add support for initializer and terminate functions (US12944)
25jun13,elp  Added LOAD_MODULE_LOADING (WIND00408631).
29apr10,pad  Moved extern C statement after include statements.
14apr10,v_r  Added ability to load DKMs into the kernel common heap (req
             CQ:WIND00202013).
06jul09,v_r  Added DKM incompatibility errno (CQ:WIND00117257).
30apr09,v_r  Updated for LP64.
29apr08,v_r  Added new errnos and flag for ABI/ISA mismatch (req
             CQ:WIND00090099).
26jun07,v_r  Loader now supports fully linked on the target (req
             CQ:WIND00058858). Added missing symbol table errno.
04jun07,v_r  Added errno about SDA not being supported in the loader.
11aug06,v_r  Added new errno for invalid load flags (for CQ:WIND00039907
             defect fix).
02aug06,v_r  Added new load options for use with WEAK symbols (defect
             CQ:WIND00059364).
17jul06,jmp  Updated copyright.
07jul06,v_r  Added new errno for use with LOAD_NO_DOWNLOAD flag
             (CQ:WIND00056511).
25jul05,v_r  Updated copyright.
18mar05,v_r  Fixed SPR #98274 (loader errno backward compatibility review).
             Includes cleanups.
01mar05,v_r  Moved pLoadRoutine() prototype to loadLibP.h.
18sep04,jn   Move toward shared code on host and target
08jun04,jn   Rename generic errno string
05apr04,jn   Clean up - remove unused declarations and development-related
             comments
08may02,fmk  - add LOAD_COMMON flags
             - move non-public declarations for loadModuleAtSym(),
             loadModuleGet(),addSegNames() and loadSegmentsAllocate()
             to loadLibP.h
30oct96,elp  Added LOAD_LOADED_BY_TGTSVR flag + syncLoadRtn function
             pointer.
01oct96,elp  added LOAD_MODULE_INFO_ONLY flag (SPR# 6775).
22sep92,rrr  added support for c++
22jul92,jmm  removed NO_TRACK_MODULE define
             moved SEG_INFO here from various loaders
             added prototypes for addSegNames and loadSegmentsAllocate
21jul92,jmm  added HIDDEN_MODULE define
18jun92,ajm  made object module independant
26may92,rrr  the tree shuffle
14may92,ajm  rewritten for object module independent loadLib
             updated copyright
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed copyright notice
02aug91,ajm  added mips specific error entries
24mar91,del  added I960 defines.
05oct90,dnw  deleted private routines.
05oct90,shl  added ANSI function prototypes.
             made #endif ANSI style.
             added copyright notice.
07aug90,shl  added INCloadLibh to #endif.
05jun88,dnw  changed ldLib to loadLib.
07aug87,ecs  added LD_NO_ADDRESS.
24dec86,gae  changed stsLib.h to vwModNum.h.
10aug84,dnw  removed unused status code: S_ldLib_UNDEFINED_SYMBOL.
07aug84,ecs  added include of stsLib.h
             added status codes
             added inclusion test
29jun84,ecs  changed values of *_SYMBOLS so default would be GLOBAL_SYMBOLS
27apr84,dnw  written
*/

#ifndef __INCloadLibh
#define __INCloadLibh

#include <moduleLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_loadLib_ROUTINE_NOT_INSTALLED		(M_loadLib | 1)
#define S_loadLib_TOO_MANY_SYMBOLS		(M_loadLib | 2) /* obsoleted */
#define S_loadLib_ILLEGAL_FLAGS_COMBINATION	(M_loadLib | 3)
#define S_loadLib_INVALID_ARGUMENT	        (M_loadLib | 4)
#define S_loadLib_UNDEFINED_REFERENCES		(M_loadLib | 5)
#define S_loadLib_UNSPECIFIED_SEGMENT_ADDRESS	(M_loadLib | 6)
#define S_loadLib_INVALID_LOAD_FLAG		(M_loadLib | 7)
#define S_loadLib_SDA_NOT_SUPPORTED		(M_loadLib | 8)
#define S_loadLib_MISSING_SYMBOL_TABLE		(M_loadLib | 9)
#define S_loadLib_ABI_MISMATCH			(M_loadLib | 10)
#define S_loadLib_ISA_MISMATCH			(M_loadLib | 11)
#define S_loadLib_INCOMPATIBLE_MODULE		(M_loadLib | 12)
#define S_loadLib_USR_INIT_ERROR		(M_loadLib | 13)
#define S_loadLib_ALREADY_LOADED		(M_loadLib | 14)

/* a general security event ID */

#define SEC_EVENT_LOADER_MODULE_LOAD_FAILED     (M_loadLib | 1)

/* 
 * 'old' load flags - now primarily used by 'ld', but loadModule can
 * be called with these load flags, so these values must not be used for
 * other load flags.
 */

#define NO_SYMBOLS      -1
#define GLOBAL_SYMBOLS  0
#define ALL_SYMBOLS     1

/* load flags */

#define LOAD_NO_SYMBOLS	        0x2
#define LOAD_LOCAL_SYMBOLS	0x4
#define LOAD_GLOBAL_SYMBOLS	0x8
#define LOAD_ALL_SYMBOLS	(LOAD_LOCAL_SYMBOLS | LOAD_GLOBAL_SYMBOLS)
#define HIDDEN_MODULE		0x10	/* Don't display module */
					/* from moduleShow() */

#define LOAD_FULLY_LINKED       0x20
#define LOAD_NO_DOWNLOAD        0x40	/* unsupported */

#define LOAD_FORCE		0x80	/* forced loading (no sanity checks) */

#define LOAD_COMMON_MATCH_NONE	0x100	/* Only alloc, no search (default) */
#define LOAD_COMMON_MATCH_USER	0x200	/* Core file excluded from search  */
#define LOAD_COMMON_MATCH_ALL	0x400	/* Core file included in search    */

#define LOAD_COMMON_HEAP	0x800	/* load DKM into the kernel common */
					/* heap */

#define LOAD_CPLUS_XTOR_AUTO    0x1000	/* call C++ constructors on load */
#define LOAD_CPLUS_XTOR_MANUAL  0x2000	/* do not call C++ constructors */

#define LOAD_WEAK_MATCH_NONE	0x10000	/* register WEAKs as globals */
#define LOAD_WEAK_MATCH_ALL	0x20000	/* use existing global def. (default) */

#define LOAD_CALL_INIT_AUTO     0x100000 /* Exec usr init (default) */
#define LOAD_CALL_INIT_MANUAL   0x200000 /* Defer usr init execution */

#define LOAD_MODULE_INFO_ONLY	0x1000000	/* host/target symtbls sync */
#define LOAD_LOADED_BY_TGTSVR	0x2000000	/* host/target symtbls sync */

#define LOAD_WRS_RESERVED_1	0x4000000	/* reserved for WR future use */
#define LOAD_WRS_RESERVED_2	0x8000000	/* reserved for WR future use */

#define LOAD_MODULE_LOADING	0x80000000	/* flags used by moduleLib */

#define LD_NO_ADDRESS   ((void *) NONE)

/* function declarations */

extern MODULE_ID    loadModule (int fd, int symFlag); 
extern MODULE_ID    loadModuleAt (int fd, int symFlag, char **ppText,
				  char **ppData, char **ppBss);
extern STATUS       loadExecUsrInit(MODULE_ID moduleId);

#ifdef __cplusplus
}
#endif

#endif /* __INCloadLibh */
