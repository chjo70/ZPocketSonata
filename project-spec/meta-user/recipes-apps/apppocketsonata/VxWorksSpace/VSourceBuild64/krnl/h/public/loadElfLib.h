/* loadElfLib.h - ELF-specific loader library header */

/*
 * Copyright (c) 1996, 2001, 2004, 2005, 2008-2010, 2016, 2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28jun17,yat  Add loadElfSecDecrypt for secure loader decryption (F9210)
21apr17,aak  Add loadElfSigCheck and secure Loader error handling (F7459)
29apr10,pad  Moved extern C statement after include statements.
26jan10,v_r  Updated for host side new abstraction usage.
30apr09,v_r  Removed unused MAX_SEC_LEN macro.
12mar08,v_r  Now provide full ELF header to elfArchVerify() routine (req
             CQ:WIND00090099).
16aug05,jeg  Fixed build and DLL load failure
25jul05,v_r  Updated copyright.
31mar05,v_r  Fixed SPR #98274 (loader backward compatibility errno review).
17sep04,jn   Move towards shared files
05apr04,jn   Clean up - remove unused declarations and
             development-related comments
05sep01,jn   changing ARM to ELF and created loadElfLibP.h -
             moved utility macros and private type and structure
             definitions to loadElfLibP.h
20jun96,dbt  written from /host/include/loadelf.h v01c
             and /host/include/elfppc.h v01c
*/

#ifndef __INCloadElfLibh
#define __INCloadElfLibh

#ifdef HOST
#else 
#include <vwModNum.h>
#endif /* HOST */

#include <elf.h>
#include <private/loadElfLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* status codes */

#define S_loadElfLib_HDR_READ		    (M_loadElfLib | 1)
#define S_loadElfLib_HDR_ERROR		    (M_loadElfLib | 2)
#define S_loadElfLib_PHDR_MALLOC	    (M_loadElfLib | 3)  /* obsoleted */
#define S_loadElfLib_PHDR_READ		    (M_loadElfLib | 4)  /* obsoleted */
#define S_loadElfLib_SHDR_MALLOC	    (M_loadElfLib | 5)  /* obsoleted */
#define S_loadElfLib_SHDR_READ		    (M_loadElfLib | 6)
#define S_loadElfLib_READ_SECTIONS	    (M_loadElfLib | 7)
#define S_loadElfLib_LOAD_SECTIONS	    (M_loadElfLib | 8)  /* obsoleted */
#define S_loadElfLib_LOAD_PROG		    (M_loadElfLib | 9)  /* obsoleted */
#define S_loadElfLib_SYMTAB		    (M_loadElfLib | 10) /* obsoleted */
#define S_loadElfLib_RELA_SECTION	    (M_loadElfLib | 11)
#define S_loadElfLib_SCN_READ		    (M_loadElfLib | 12) /* obsoleted */
#define S_loadElfLib_SDA_MALLOC		    (M_loadElfLib | 13) /* obsoleted */
#define S_loadElfLib_SST_READ		    (M_loadElfLib | 15) /* obsoleted */

#define S_loadElfLib_JMPADDR_ERROR	    (M_loadElfLib | 20) /* obsoleted */
#define S_loadElfLib_GPREL_REFERENCE	    (M_loadElfLib | 21) /* obsoleted */
#define S_loadElfLib_UNRECOGNIZED_RELOCENTRY	(M_loadElfLib | 22)
#define S_loadElfLib_RELOC		    (M_loadElfLib | 23)
#define S_loadElfLib_UNSUPPORTED	    (M_loadElfLib | 24)
#define S_loadElfLib_REL_SECTION	    (M_loadElfLib | 25)

#define S_loadElfLib_INVALID_ARGUMENT		    (M_loadElfLib | 27)
#define S_loadElfLib_RELOCATION_OFFSET_TOO_LARGE    (M_loadElfLib | 28)
#define S_loadElfLib_RELOCATION_UNIT_NOT_INSTALLED  (M_loadElfLib | 29)

#define S_loadElfLib_SIG_SECTION_ERROR             (M_loadElfLib | 30)
#define S_loadElfLib_SIG_KEY_INVALID               (M_loadElfLib | 31)

/* function declarations */

#ifdef HOST
extern DLL_EXPORT STATUS loadElfInit (void);
/*
 * These funcs are called through function pointers to make it possible to
 * support architecture relocation units that can be loaded or unloaded by a
 * single target server (since the loader code is shared between the host and
 * target).
 */
extern BOOL (* pElfArchVerify) (ELF_EHDR * pEhdr);
extern STATUS (* pElfArchReloc) (BOOL swapNeeded, 
				 LOAD_MODULE_INFO * pLoadModuleInfo,
				 ELF_EHDR * pEhdr, ELF_SHDR * pRelHdr,
				 SCN_ADRS scnAddr, INT64 deltaBaseAddr,
				 SYM_INFO_TBL symInfoTbl);

#else
extern STATUS loadElfInit (void);

#ifdef _WRS_CONFIG_SECURE_LOADER

extern STATUS loadElfSigCheck (
#ifdef _WRS_CONFIG_SECURE_LOADER_ENCRYPTION
                               void ** ppDecryptCtx,
#endif /* _WRS_CONFIG_SECURE_LOADER_ENCRYPTION */
                               int fd, const char * fileName,
                               ELF_EHDR * pEhdr);

#ifdef _WRS_CONFIG_SECURE_LOADER_ENCRYPTION

extern BOOL loadElfSecDecryptSectionCheck (void * pDecryptCtx);

extern BOOL loadElfSecDecryptSegmentCheck (void * pDecryptCtx, UINT32 flags);

extern STATUS loadElfSecDecryptUpdate (void * pDecryptCtx,
                                       int id,
                                       void * pData, size_t dataSize);

extern STATUS loadElfSecDecryptFinish (void * pDecryptCtx);

#endif /* _WRS_CONFIG_SECURE_LOADER_ENCRYPTION */

#endif /* _WRS_CONFIG_SECURE_LOADER */

#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCloadElfLibh */
