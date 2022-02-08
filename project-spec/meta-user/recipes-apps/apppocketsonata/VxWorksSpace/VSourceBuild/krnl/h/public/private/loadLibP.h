/* loadLibP.h - private object module loader library header */

/*
 * Copyright (c) 2002, 2004-2010, 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
23sep15,jmp  Added support for Fix & Continue facility (US65040).
16apr14,rlp  Added loadModuleEx prototype.
	     Modified pLoadRoutine() prototype.
	     Added a new option to check if the module is already loaded.
14apr14,rlp  Compute checksum of loadable sections before relocation.
01oct13,jdw  Add support for initializer and terminate functions (US12944)
29apr10,pad  Moved extern C statement after include statements.
23feb10,v_r  Moved to fully qualified function pointers.
22feb10,v_r  LP64 TODOS cleanup. 
08jan10,v_r  Added 64-bit byteswapping macros and host read/write routines
             (latter untested).
03feb10,rlp  Defined syncLoadRtn as fully qualified function pointer.
16jun09,v_r  LP64 adaptation:: added MEM_WRITE_64 macro and updated
             ALIGN_NEXT.
04jun09,v_r  LP64 adaptation: updated loadCommonSymbolProcess() to use
             ULONG for symbol alignement and size.
30apr09,v_r  LP64 adaptation (phase #1) : updated code following adaptation
             guidelines (except FUNCPTR mods and macro updates).
             Removed unused definitions: loadCommonMatch(),
             loadCommonManage() and loadSectionDirectiveMatch() APIs, 
             COMMON_INFO struct, LOAD_LOW24_INSERT macro.
17apr09,zl   unconditionalized ALIGN_NEXT definition
30apr08,v_r  Network symbol table special flags handling now done in
             loader code.
16apr08,v_r  Added macros to perform unaligned writes (def
             CQ:WIND00120849).
03jul07,p_b  Avoid build warning by renaming locally used SWAB_16() macro
12jul06,dbt  Removed use of tgtMemManyWrite() that has been obsoleted.
18jan06,v_r  Added pointers for loader/unloader hook facility.
26jul05,v_r  Complete loader's ... review.
18mar05,v_r  Include cleanups + code conventions compliancy work.
             Removed loadModuleByFilename() and loadModuleAtByFilename() APIs.
01mar05,v_r  Added pLoadRoutine() prototype.
22feb05,dbt  Cleanup.
06oct04,jn   Clean up comments
21sep04,jn   Move shared macros for relocations out of relocation units
             (elf<Arch>.c)
18sep04,jn   Move towards shared code for host and target loaders
16apr04,jn   Remove section directives - not useful right now
02apr04,jn   Fix warning in bsp builds.  Clean up - remove unused 
             declarations and development-related comments
16may02,fmk  written
*/

#ifndef __INCloadLibPh
#define __INCloadLibPh

/* Include */

#ifdef HOST
#include <sllLib.h>
#include <symbol.h>
#include <symLib.h>
#include <moduleLibP.h>
#include <pdLib.h>
#include <memAttrLib.h>
#include <private/moduleLibP.h> 
#include <private/loadElfLibP.h>
#include <private/loadFileLibP.h>
#include <moduleLib.h>
#include <loadLib.h>
#else
#include <private/loadFileLibP.h>
#include <private/moduleLibP.h>
#include <private/loadElfLibP.h>
#include <loadLib.h>
#endif /* HOST */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* load flags */

#define LOAD_IGNORE_IF_IDENTICAL	LOAD_WRS_RESERVED_1
						/* do not load if the */
                                                /* same module is */
                                                /* already loaded */

#define USR_INIT_FUNC_NAME "_VxModuleAutoInit"
#define USR_TERM_FUNC_NAME "_VxModuleAutoTerm"

#define TEXT_SEG_INFO(pList)	((SEGMENT_INFO_DESC *)pList->head)
#define DATA_SEG_INFO(pList)	((SEGMENT_INFO_DESC *)pList->head->next)
#define BSS_SEG_INFO(pList)	((SEGMENT_INFO_DESC *)pList->head->next->next)

#define ALIGN_NEXT(size,align) (((long) size + (long) align - 1) & \
				(~((long) align - 1)))

#ifdef HOST
/* Swap of two bytes : AB becomes BA */

#ifdef SWAB_16
#undef SWAB_16
#endif

#define SWAB_16(x)	(((UINT16)((x) & 0x00ff) << 8) | \
			 ((UINT16)((x) & 0xff00) >> 8))

/* Swap of four bytes : ABCD becomes DCBA */

#ifdef SWAB_32
#undef SWAB_32
#endif

#define SWAB_32(x)	(((UINT32)((x) & 0x000000ff) << 24) | \
			 ((UINT32)((x) & 0x0000ff00) << 8)  | \
			 ((UINT32)((x) & 0x00ff0000) >> 8)  | \
			 ((UINT32)((x) & 0xff000000) >> 24))

/* Swap of eight bytes: ABDCEFGH becomes HGFECDAB */

#ifdef SWAB_64
#undef SWAB_64
#endif

#ifdef WIN32
/* WIN32 does not support LL suffix */

#define SWAB_64(x)     (((UINT64)((x) & 0x00000000000000ff) << 56)  | \
			((UINT64)((x) & 0x000000000000ff00) << 40)  | \
			((UINT64)((x) & 0x0000000000ff0000) << 24)  | \
			((UINT64)((x) & 0x00000000ff000000) << 8)   | \
			((UINT64)((x) & 0x000000ff00000000) >> 8)   | \
			((UINT64)((x) & 0x0000ff0000000000) >> 24)  | \
			((UINT64)((x) & 0x00ff000000000000) >> 40)  | \
			((UINT64)((x) & 0xff00000000000000) >> 56))
#else /* WIN32 */
#define SWAB_64(x)     (((UINT64)((x) & 0x00000000000000ffLL) << 56)  | \
			((UINT64)((x) & 0x000000000000ff00LL) << 40)  | \
			((UINT64)((x) & 0x0000000000ff0000LL) << 24)  | \
			((UINT64)((x) & 0x00000000ff000000LL) << 8)   | \
			((UINT64)((x) & 0x000000ff00000000LL) >> 8)   | \
			((UINT64)((x) & 0x0000ff0000000000LL) >> 24)  | \
			((UINT64)((x) & 0x00ff000000000000LL) >> 40)  | \
			((UINT64)((x) & 0xff00000000000000LL) >> 56))
#endif /* !WIN32 */

/* Swap bytes in place */

#define SWAP_16(x)	((x) = SWAB_16 (x))
#define SWAP_32(x)	((x) = SWAB_32 (x))
#define SWAP_64(x)	((x) = SWAB_64 (x))

/* Swap only if the boolean (b) is true */

#define MEM_READ_64(pRelocAdrs, offset)                             \
    do                                                              \
        {                                                           \
        if (tgtMemRead (NULL, (pRelocAdrs), &(offset),              \
			sizeof(UINT64), 0, 0) != OK)                \
	    return ERROR;                                           \
	if (swapIsRequired)					    \
	    SWAP_64 (offset);	/* Host format */		    \
        }                                                           \
    while (0);

#define MEM_READ_32(pRelocAdrs, offset)                             \
    do                                                              \
        {                                                           \
        if (tgtMemRead (NULL, (pRelocAdrs), &(offset),              \
			sizeof(UINT32), 0, 0) != OK)                \
	    return ERROR;                                           \
	if (swapIsRequired)					    \
	    SWAP_32 (offset);	/* Host format */		    \
        }                                                           \
    while (0);

#define MEM_READ_16(pRelocAdrs, offset)                             \
    do                                                              \
        {                                                           \
        if (tgtMemRead (NULL, (pRelocAdrs), &(offset),              \
                       sizeof(UINT16), 0, 0) != OK)                 \
            return ERROR;                                           \
	if (swapIsRequired)					    \
	    SWAP_16 (offset); /* Host format */			    \
        } while (0);

#define MEM_READ_8(pRelocAdrs, offset)                              \
    do                                                              \
        {                                                           \
        if (tgtMemRead (NULL, (pRelocAdrs), &(offset),              \
                        sizeof(UINT8), 0, 0) != OK)                 \
            return ERROR;                                           \
        } while (0);

#define MEM_WRITE_64(pRelocAdrs, value64)			    \
    do                                                              \
        {                                                           \
	if (swapIsRequired)					    \
	    SWAP_64 (value64);	/* Target format */		    \
        if (tgtMemWrite (NULL, &(value64), (pRelocAdrs),            \
                             sizeof (UINT64), 0, TRUE) != OK)       \
            return ERROR;                                           \
        } while (0); 

#define MEM_WRITE_32(pRelocAdrs, value32)                           \
    do                                                              \
        {                                                           \
	if (swapIsRequired)					    \
	    SWAP_32 (value32);	/* Target format */		    \
        if (tgtMemWrite (NULL, &(value32), (pRelocAdrs),            \
                             sizeof (UINT32), 0, TRUE) != OK)       \
            return ERROR;                                           \
        } while (0); 

#define MEM_WRITE_16(pRelocAdrs, value16)                           \
    do                                                              \
        {                                                           \
	if (swapIsRequired)					    \
	    SWAP_16 (value16); /* Target format */		    \
        if (tgtMemWrite (NULL, &(value16), (pRelocAdrs),            \
                             sizeof(UINT16), 0, TRUE) != OK)        \
            return ERROR;                                           \
        } while (0);

#define MEM_WRITE_8(pRelocAdrs, value)				    \
    do                                                              \
        {                                                           \
        if (tgtMemWrite (NULL, &value, pRelocAdrs,		    \
			     sizeof (UINT8), 0, TRUE) != OK)	    \
	    return ERROR;                                           \
        } while (0);

/* 
 * Macro to perform unaligned writes (UA = UnAligned). The host relies on
 * WDB which properly handles unaligned accesses which is why we simply use the
 * already existing macros.
 */

#define MEM_WRITE_UA16	    MEM_WRITE_16
#define MEM_WRITE_UA32	    MEM_WRITE_32

#else	/* HOST */

#define MEM_READ_32(pRelocAdrs, offset)	((offset) = *((UINT32 *)(pRelocAdrs)));
#define MEM_READ_16(pRelocAdrs, offset)	((offset) = *((UINT16 *)(pRelocAdrs)));
#define MEM_READ_8(pRelocAdrs, offset)  ((offset) = *((UINT8 *)(pRelocAdrs)));

#define MEM_WRITE_64(pRelocAdrs, value64)	\
	(*((UINT64 *)(pRelocAdrs)) = (value64));
#define MEM_WRITE_32(pRelocAdrs, value32)	\
	(*((UINT32 *)(pRelocAdrs)) = (value32));
#define MEM_WRITE_16(pRelocAdrs, value16)	\
	(*((UINT16 *)(pRelocAdrs)) = (value16));
#define MEM_WRITE_8(pRelocAdrs, value8)         \
    (*((UINT8 *)(pRelocAdrs)) = (value8));

/* 
 * Macros to perform unaligned writes (UA = UnAligned). Instead of doing
 * a simple, direct write which could fault in case of unaligned memory, we
 * defer the job to memcpy() which properly handles unalignement.
 */

#define MEM_WRITE_UA16(pRelocAdrs, value16) memcpy((void *) (pRelocAdrs),   \
						   (void *) &(value16),	    \
						   sizeof (UINT16));

#define MEM_WRITE_UA32(pRelocAdrs, value32) memcpy((void *) (pRelocAdrs),   \
						   (void *) &(value32),	    \
						   sizeof (UINT32));

#endif /* !HOST */

/* misc definitions */

/* Macro to check if the alignment is a power of 2 */

#define CHECK_2_ALIGN(x)        (((x) & ((x) - 1)) == 0)

/* VxWorks image load flag, defined for convenience purpose */

#define LOAD_CORE_FILE          (LOAD_FULLY_LINKED|LOAD_NO_DOWNLOAD)

/* types */

typedef STATUS (*LOAD_USR_FUNC) ( void );

/* externals */

extern void	(* syncLoadRtn) (MODULE_ID moduleId);
extern void	(* pLoaderHooksCall) (MODULE_ID moduleId, UINT32 options);
extern void	(* pUnloaderHooksCall) (MODULE_ID moduleId, UINT32 options);

/* function declarations */

extern STATUS	loadLibInit (BOOL storeAbsSymsArg); 
extern STATUS	loadSysSymTblLoad (int symfd, BOOL allSyms);
extern STATUS	loadUndefinedSymbolProcess (char * name, SYM_INFO * pSymInfo,
					    MODULE_ID moduleId); 
extern STATUS	loadCommonSymbolProcess (char * name, ULONG symSize,
					 ULONG symAlign, SYM_INFO * pSymInfo,
					 MODULE_ID moduleId, 
					 LOAD_FLAG_T loadFlag);
extern STATUS	loadDefinedSymbolProcess (char * name, SYM_ADRS symAddr,
					  SYM_EXT_TYPE symExtType,
					  SYM_INFO * pSymInfo,
					  MODULE_ID moduleId,
					  LOAD_FLAG_T loadFlag);
extern void	loadBuffersFree (void * pBuf);
extern STATUS	loadSegmentsAllocate (MODULE_ID moduleId,
				      LOAD_FLAG_T loadFlags,
				      SL_LIST * pMemInfoList);
extern STATUS	loadSectionsInstall (LOAD_MODULE_INFO * pLoadModuleInfo,
				     LOAD_FLAG_T loadFlags,
				     SL_LIST * pSegInfoList);
extern void	loadFileSectionsChecksum (LOAD_MODULE_INFO * pLoadModuleInfo,
				     LOAD_FLAG_T loadFlags,
				     SL_LIST * pSegInfoList);
extern STATUS	loadSegInfoDescAllocate (SL_LIST * pSegInfoDescList,
					 LOAD_FLAG_T loadFlags,
					LOAD_SEGMENT_DIRECTIVE * pSegDirective,
					 UINT nbSegDirectives);
extern STATUS	loadSegInfoDescFree (SL_LIST * pSegInfoDescList); 
extern STATUS	(* pLoadRoutine) (LOAD_MODULE_INFO *, LOAD_FLAG_T,
				  LOAD_SEGMENT_DIRECTIVE *, UINT,
				  MODULE_ID, BOOL *, MODULE_ID);
extern STATUS	moduleUndefSymAdd (MODULE_ID moduleId, char * symName);

extern STATUS   loadExecUsrFunc( MODULE_ID * pModuleId, SYMTAB_ID symTbl,
                                 int option );
extern STATUS	loadModuleEx (int fd, int options, MODULE_ID * pModuleId);
extern STATUS   loadModuleWithInfoAt (LOAD_MODULE_INFO * pLoadModuleInfo,
                                      int options, char ** ppText,
                                      char ** ppData, char ** ppBss,
                                      MODULE_ID * pModId, int * pErrno);
extern STATUS   loadFixAndContinueInit (BOOL (*facAllocRtn) (
                                            SECTION_INFO_DESC * pCurSection,
                                            MODULE_ID moduleId));
#ifdef __cplusplus
}
#endif

#endif /* __INCloadLibPh */



