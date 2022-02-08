/* loadRtpLibP.h - private header file for Real Time Process module loader */

/*
 * Copyright 2003-2004, 2008-2010, 2012, 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10oct17,aak  Remove WIBU (F9917)
28jun17,yat  Add pDecryptCtx for secure loader decryption (F9210)
05may17,yat  clean up code as part of secure loader changes (F7459)
14apr17,dlk  Support more than two loadable segments (F7415)
05oct15,pad  Added loadRtpSymLibInit() declaration here (V7SEC-134)
11dec14,v_r  loadRtpFileSymbolsRegister now local.
02dec14,v_r  Removed dead code. Added _func_loadRtpFileSymbolsRegister/
03jul14,wap  Add secure boot features (US37952)
06mar12,pad  Added S_loadRtpLib_TOO_FEW_SEGMENTS errno.
01sep10,jpb  Added function pointers _func_loadRtpDeltaBaseAddrApply &
             _func_loadRtpSymsPolicyOverride.  Moved definition of
             VXE_ADDR here.
29apr10,pad  Moved extern C statement after include statements.
20nov09,zl   updated for LP64
16jul08,pad  Added exeType field and associated macros for the
             RTP_IMAGE_INFO structure.
13jun08,pad  Replaced unused S_loadRtpLib_UNSUPPORTED_RELOC with
             S_loadRtpLib_NO_RELOCATION_SECTION.
29mar04,jn   Rename rtpLoadLib -> loadRtpLib
26mar04,jn   Move arch-independent calculations into rtpLoadLib.c
24mar04,pad  Added a RTP_LOAD_LOCAL_SYMBOLS flag.
16mar04,pad  Changed some parameter names for loadRtpFileSymbolsRegister().
05mar04,pad  Adaptation for making the application loader act as a symbol
             recorder: added prototype for loadRtpFileSymbolsRegister() and
             added a symOwnerId field to the RTP_IMAGE_INFO structure.
18feb04,pad  Added flag RTP_LOAD_SYMBOLS_ONLY (required for the shared
             libraries).
11nov03,jn   Fix bit mapping for load flags
21oct03,jn   Integrate rtp loader which handles executables
18aug03,jn   Written.
*/

/*
DESCRIPTION
The loadRtpLib library provides the API's that are used to load Real Time
Process (RTP) object modules.  This header provides the interfaces that are
available to other vxWorks system code that uses this library.

These API's are designed to be called only by the RTP library or other
vxWorks system code, not by user code or from the shell.  There are
several operations that must be done to create an RTP; relocating the
code and loading it into memory is just one small part of creating the
RTP.  Therefore attempting to use these routines in isolation, apart
from the rest of the RTP library, will not result in a viable RTP.

For now, the only object module format which is supported for RTP's is
ELF.
*/

#ifndef __INCloadRtpLibPh
#define __INCloadRtpLibPh

#include <symLib.h>
#include <elf.h>
#include <vwModNum.h>
#include <private/loadElfLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * Don't use 0x0 for an option flag - if the option argument is 0x0,
 * the loader performs its default behavior.
 */

#define RTP_LOAD_NO_SYMBOLS	0x1	/* do not load any symbols for RTP */
#define RTP_LOAD_GLOBAL_SYMBOLS	0x2	/* load only global RTP symbols */
#define RTP_LOAD_ALL_SYMBOLS	0x4	/* load all RTP symbols */
#define RTP_LOAD_LOCAL_SYMBOLS	0x8	/* load local RTP symbols */
#define RTP_LOAD_SYMBOLS_ONLY	0x100	/* prevents loading of text and data */

/* Executable file types (may be OR'ed) */

#define RTP_EXE_CLEAR_TYPE	0x0	/* just to reset the field to no type */
#define RTP_EXE_RELOCATABLE	0x1	/* relocatable .vxe file */
#define RTP_EXE_ABS_LINKED	0x2	/* absolutely linked .vxe file */

/* Error Status codes */

#define S_loadRtpLib_INVALID_ARGUMENT               (M_loadRtpLib | 101)
#define S_loadRtpLib_INVALID_OPTION                 (M_loadRtpLib | 102)
#define S_loadRtpLib_SYMTBL_DESTROY_INCOMPLETE      (M_loadRtpLib | 103)
#define S_loadRtpLib_TOO_MANY_SEGMENTS              (M_loadRtpLib | 104)
#define S_loadRtpLib_NO_LOADABLE_SEGMENT            (M_loadRtpLib | 105)
#define S_loadRtpLib_ADDRESS_OVERFLOW               (M_loadRtpLib | 106)
#define S_loadRtpLib_SEGMENT_READ                   (M_loadRtpLib | 107)
#define S_loadRtpLib_COMMON_SYMBOL                  (M_loadRtpLib | 108)
#define S_loadRtpLib_UNDEFINED_SYMBOL               (M_loadRtpLib | 109)
#define S_loadRtpLib_NO_RELOCATION_SECTION          (M_loadRtpLib | 110)
#define S_loadRtpLib_NOT_EXECUTABLE                 (M_loadRtpLib | 111)
#define S_loadRtpLib_NO_ENTRY_POINT                 (M_loadRtpLib | 112)
#define S_loadRtpLib_NO_PROG_HDR                    (M_loadRtpLib | 113)
#define S_loadRtpLib_FIRST_LOAD_SEG_NOT_EXECUTABLE  (M_loadRtpLib | 114)
#define S_loadRtpLib_SECOND_LOAD_SEG_NOT_WRITEABLE  (M_loadRtpLib | 115)
#define S_loadRtpLib_DATA_SEG_BEFORE_TEXT_SEG       (M_loadRtpLib | 116)
#define S_loadRtpLib_TOO_FEW_SEGMENTS               (M_loadRtpLib | 117)
#define S_loadRtpLib_INVALID_SEGMENTS               (M_loadRtpLib | 118)

/*
 * The following errnos are CERT-specific (no shared libs or dynamic exe +
 * additional parameter validation)
 * */

#define S_loadRtpLib_DYNAMIC_SEGMENTS_NOT_SUPPORTED (M_loadRtpLib | 118)
#define S_loadRtpLib_INSUFFICIENT_MEMORY            (M_loadRtpLib | 119)

/*
 * The ELF loader API uses the ELF_HDR types for 32-bit/64-bit abstraction
 *
 * A local abstraction is introduced in case a future implementation
 * will use build-time conditionals instead of the runtime abstraction
 * provided by the ELF_HDR_* macros and related API.
 */

#define VXE_EHDR                        ELF_EHDR
#define VXE_PHDR                        ELF_PHDR
#define VXE_SHDR                        ELF_SHDR

#define VXE_HDR_E_ENTRY(h)              ELF_HDR_E_ENTRY(h)
#define VXE_HDR_E_PHNUM(h)              ELF_HDR_E_PHNUM(h)
#define VXE_HDR_E_SHNUM(h)              ELF_HDR_E_SHNUM(h)
#define VXE_HDR_E_SHOFF(h)              ELF_HDR_E_SHOFF(h)
#define VXE_HDR_E_TYPE(h)               ELF_HDR_E_TYPE(h)

#define VXE_HDR_P_FILESZ(h)             ELF_HDR_P_FILESZ(h)
#define VXE_HDR_P_FLAGS(h)              ELF_HDR_P_FLAGS(h)
#define VXE_HDR_P_MEMSZ(h)              ELF_HDR_P_MEMSZ(h)
#define VXE_HDR_P_OFFSET(h)             ELF_HDR_P_OFFSET(h)
#define VXE_HDR_P_TYPE(h)               ELF_HDR_P_TYPE(h)
#define VXE_HDR_P_VADDR(h)              ELF_HDR_P_VADDR(h)

#define VXE_HDR_SH_ENTSIZE(h)           ELF_HDR_SH_ENTSIZE(h)
#define VXE_HDR_SH_FLAGS(h)             ELF_HDR_SH_FLAGS(h)
#define VXE_HDR_SH_INFO(h)              ELF_HDR_SH_INFO(h)
#define VXE_HDR_SH_LINK(h)              ELF_HDR_SH_LINK(h)
#define VXE_HDR_SH_OFFSET(h)            ELF_HDR_SH_OFFSET(h)
#define VXE_HDR_SH_SIZE(h)              ELF_HDR_SH_SIZE(h)
#define VXE_HDR_SH_TYPE(h)              ELF_HDR_SH_TYPE(h)

#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
#define VXE_HDR_SH_PTR(pShdr)           ((pShdr)->type == ELF32 ?              \
                                           ((void *) &(pShdr)->elf.scnHdr32) : \
                                           ((void *) &(pShdr)->elf.scnHdr64))

#define VXE_SHDR_SIZE(pEhdr)            ((pEhdr)->type == ELF32 ?              \
                                           sizeof (Elf32_Shdr) :               \
                                           sizeof (Elf64_Shdr))
#else /* !_WRS_LOADER_NO_ELF64_SUPPORT */
#define VXE_HDR_SH_PTR(pShdr)           ((void *) &(pShdr)->elf.scnHdr32)
#define VXE_SHDR_SIZE(pEhdr)            sizeof (Elf32_Shdr)
#endif /* _WRS_LOADER_NO_ELF64_SUPPORT */

/* 32-bit/64-bit abstraction for symbols uses compile-time conditionals */

#ifdef _WRS_CONFIG_LP64

/* table of pointers to symbol tables */

typedef Elf64_Sym **                    SYMTBL_REFS;
#define VXE_SYM                         Elf64_Sym
#define VXE_ADDR                        Elf64_Addr
#define VXE_ST_BIND(stInfo)             ELF64_ST_BIND(stInfo)
#define VXE_ST_TYPE(stInfo)             ELF64_ST_TYPE(stInfo)

#else /* _WRS_CONFIG_LP64 */

/* table of pointers to symbol tables */

typedef Elf32_Sym **                    SYMTBL_REFS;
#define VXE_SYM                         Elf32_Sym
#define VXE_ADDR                        Elf32_Addr
#define VXE_ST_BIND(stInfo)             ELF32_ST_BIND(stInfo)
#define VXE_ST_TYPE(stInfo)             ELF32_ST_TYPE(stInfo)

#endif /* _WRS_CONFIG_LP64 */


/*
 * The maximum number of non-empty loadable segments supported.
 * May be increased if necessary.
 */

#define LOADER_MAX_SEGMENTS   (6)

/* typedefs */

/*
 * struct rtpSegInfo holds the information needed about non-empty loadable
 * segments, for an RTP executable (after loading is complete).
 */

typedef struct rtpSegInfo
    {
    void * vaddr;     /* in memory starting virtual address of segment */
                      /* Note: this address is not necessarily page aligned */
    size_t memsz;     /* size of segment in memory */
    size_t filesz;    /* size of segment data in file, <= memsz */
    UINT32 flags;     /* segment flags, inc. PF_X, PF_W, PF_R */

    /*
     * Possible future extension:
     * For some purposes it might also be useful to store the starting
     * physical address (for shared libraries, where physical pages for
     * a segments are allocated contiguously), the in-file offset of the
     * segment, or the segment alignment (p_align or its base 2 logarithm).
     */
    } RTP_SEG_INFO;

#define RTP_IMAGE_INFO_LEGACY_MEMBERS

typedef struct rtpImageInfo
    {
#ifdef RTP_IMAGE_INFO_LEGACY_MEMBERS
    void *      textStart;      /* address where installed text begins */
    size_t      textSize;       /* size of installed text segment */
    void *      dataStart;      /* address where installed data begins */
    size_t      dataSize;       /* size of data segment, not including bss */
    void *      bssStart;       /* address where bss begins */
    size_t      bssSize;        /* size of bss region */
#endif

    /*
     * Up to LOADER_MAX_SEGS segments.  The first unused entry has NULL vaddr.
     */

    struct rtpSegInfo segs [LOADER_MAX_SEGMENTS];

    void *	entryPt;	/* ELF entry point */
    SYMTAB_ID	symTbl;		/* RTP's symbol table id */
    void *	symOwnerId;	/* owner of the symbols registered in sym tab */
    void *	rtpAllocAddr;	/* Address of memory allocated for RTP text +
				   data/bss segments - Unused at this time */
    UINT32	exeType;	/* type of RTP executable */

    /* particular loadable segment indices (presently heuristic) */

    UINT8       nw_ix;          /* index of 1st non-writable segment */
    UINT8       text_ix;        /* index in segs of "text segment" */
    UINT8       data_ix;        /* index in segs of "data segment" */
    UINT8       bss_ix;         /* index in segs of "bss segment" */

    } RTP_IMAGE_INFO;

/*
 * The RTP_FILE_INFO structure is intended for use only within
 * loadRtpLib itself.  However, it's convenient to have the definition
 * available when performing some automated tests (see loaderRtpTest).
 */

typedef struct rtpFileInfo
    {
    ELF_EHDR	ehdr;		/* ELF header  */

#ifdef _WRS_CONFIG_SECURE_LOADER_ENCRYPTION
    void * pDecryptCtx;
#endif /* _WRS_CONFIG_SECURE_LOADER_ENCRYPTION */
    } RTP_FILE_INFO;

/* Globals */

/*
 * This variable enables users to change the default options for RTP loading.
 * It can be any combination of the bit flags declared above, RTP_LOAD_*.
 */

extern int loadRtpDefaultOptions;

extern int loadRtpDefaultSymTblSize;

/* Function declarations */

extern struct rtpFileInfo * loadRtpFileInfoCreate (void);

extern STATUS loadRtpLibInit (void);

extern STATUS loadRtpFileVerify
    (
    int			  fd,		/* file descriptor */
    struct rtpFileInfo *  pRtpFileInfo, /* loader internal information */
    UINT32		  options	/* bit field for option flags */
    );

extern STATUS loadRtpFileLoad
    (
    int                  fd,            /* file descriptor */
    struct rtpFileInfo * pRtpFileInfo,  /* loader internal information */
    RTP_IMAGE_INFO *     pRtpImageInfo, /* for returning information */
    UINT32               options        /* bit field for option flags */
    );

extern STATUS loadRtpFileSymbolsRegister
    (
    int		fd,		/* exec or shared object file descriptor */
    void *	symOwnerId,	/* ID associated with symbols to register */
    SYMTAB_ID	symTblId,	/* symbol table where to register the symbols */
    void *	textBase,	/* base address of text segment in memory */
    void *	dataBase,	/* base address of data segment in memory */
    UINT32	options		/* bit field for option flags */
    );

extern void loadRtpFileInfoDestroy
    (
    struct rtpFileInfo * pRtpFileInfo   /* loader internal information */
    );

extern STATUS loadRtpSymTblDestroy
    (
    SYMTAB_ID symTbl,  /* symbol table to destroy */
    UINT32    options  /* bit field for option flags */
    );

/* for use by the arch relocation units: */

extern STATUS loadRtpRelocAdrsCompute
    (
    Elf32_Addr   r_offset,	 /* "offset" from relocation structure */
    void **	 ppRelocAdrs, 	 /* relocation address */
    INT64        baseAddr        /* RTP base address(= file addr - real addr)*/
    );

extern STATUS loadRtpImageMemFree
    (
    RTP_IMAGE_INFO * pRtpImageInfo, /* holds information about RTP image */
    UINT32 options                  /* bit field for option flags */
    );

/* function pointers */

extern STATUS (*_func_loadRtpDeltaBaseAddrApply)
    (
    VXE_ADDR     fileVAddr,      /* virtual address (toolchain's layout) */
    INT64        deltaBaseAddr,  /* delta base addr. (file addr - mem addr)*/
    void **      ppMemVAddr      /* returned virtual address (memory layout) */
    );

extern STATUS (*_func_loadRtpSymsPolicyOverride)
    (
    int overridePolicy          /* policy for RTP symbols registration */
    );

extern STATUS (* _func_loadRtpFileSymbolsRegister)
    (
    int		fd,		/* exec or shared object file descriptor */
    void *	symOwnerId,	/* ID associated with symbols to register */
    SYMTAB_ID	symTblId,	/* symbol table where to register the symbols */
    void *	textBase,	/* base address of text segment in memory */
    void *	dataBase,	/* base address of data segment in memory */
    UINT32	options		/* bit field for option flags */
    );

extern STATUS loadRtpSymLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCloadRtpLibPh */
