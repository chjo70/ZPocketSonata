/* loadFileLibP.h - header for utility func. lib. shared by loader libraries */

/*
 * Copyright (c) 2004-2006, 2009-2010, 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
10oct17,aak  Remove WIBU (F9917)
28jun17,yat  Add pDecryptCtx for secure loader decryption (F9210)
07jul17,h_k  implemented branch island support. (F8938)
27jun17,yat  Add skipSigCheck for secure loader (F7459)
14sep16,f_l  Fixed Linux TLS ABI support (V7RAD-1956)
07sep16,f_l  Added Linux TLS ABI support for DKM.
11dec04,v_r  Removed unused loadModuleInfoFromFilenameOpen() API as well
	     as MODULE_SOURCE structure.
23sep15,jmp  Added support for Fix & Continue facility (US65040).
08jul15,elp  Added EXIDX section (V7COR-2966).
07apr15,vhe  Added support for PPC64 ELF-v2 (F1122)
03jul14,wap  Add secure boot features (US37952)
14apr14,rlp  Added a section checksum info before relocation.
29apr10,pad  Moved extern C statement after include statements.
23feb10,v_r  Removed unused SEG_INFO structure.
23feb10,v_r  Revert structure fields reorganization until we can update
             host side as well.
22feb10,v_r  LP64 TODOS cleanup + structure reorganization.
16jun09,v_r  LP64 adaptation: updated segment/section structures to size_t.
30apr09,v_r  LP64 adaptation (phase #1) : updated code following adaptation
             guidelines (excepted struct reorg).
             Removed unneeded SEC_NAME_MAX define.
23oct06,dbt  Added alignment information in section descriptor.
23nov05,v_r  Implemented loader's cache. This fixes SPR#113798 and SPR#112398.
07mar05,v_r  Included symbol.h
01mar05,v_r  Moved segment type enum to moduleLib.h.
06oct04,jn   Clean up comments
17sep04,jn   Move towards shared files
08apr04,jn   Adjustment needed in segment descriptor structure to handle
             and track alignments correctly
05apr04,jn   Clean up development-related comments
19feb04,jn   Derived from AE's malLib.h
*/

#ifndef __INCloadFileLibPh
#define __INCloadFileLibPh

/* Includes */

#ifdef HOST
#include <host.h>
#include <objLib.h>
#else
#include <vxWorks.h>
#include <errno.h>
#include <vwModNum.h>
#include <private/handleLibP.h>
#endif	/* HOST */

#include <symbol.h>
#include <private/symbolP.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Status codes */

/* Defines */

/* Indexes into the array of segment descriptors */

#define TEXT_SEG_DESC_INDEX 0
#define DATA_SEG_DESC_INDEX 1
#define BSS_SEG_DESC_INDEX 2

#define NUM_KERNEL_MODULE_SEGS  3

/* Type definitions */

typedef unsigned int LOAD_FLAG_T;       /* load flag type */

/* information associated with module while loading is in progress */

typedef enum module_source		/* method file was specified by */
    {
    FROM_FD	   = 0,			/* opened from file descriptor */
    FROM_FILENAME  = 1			/* opened from file name */
    } MODULE_SOURCE;

typedef enum mseek_mode			/* Module position mode flags     */
    {
    MSEEK_SET	= 0,			/* Set pos. from the beginnning   */
    MSEEK_CUR	= 1			/* Set pos. from the current loc. */
    } MSEEK_MODE;

/* Types used throughout various loader header files */

typedef void *          SYM_ADRS;               /* symbol's address */
typedef void **         SYM_ADRS_TBL;           /* table of symbol's addr */

typedef void *          SCN_ADRS;               /* section's address */
typedef void **         SCN_ADRS_TBL;           /* table of section's addr */

typedef enum load_type			/* type of load being performed */
    {
    LOAD_UNKNOWN       = 0,
    LOAD_SYS_SYM_TBL   = 1,  /* Load the system symbol table */
    LOAD_VXWORKS_IMG   = 2,  /* Load vxWorks image (copy on host for tools) */
    LOAD_STAT_EXE      = 3,  /* Load statically linked executable */
    LOAD_DYN_EXE       = 4,  /* Load dynamically linked executable */
    LOAD_KERNEL_MODULE = 5,  /* Load relocatable module into kernel */
    LOAD_SYMS_ONLY     = 6   /* Load symbols only */
    } LOAD_TYPE;

typedef struct fac_section_offset       /* Fix & Continue section offset */
    {
    SL_NODE     secNode;
    char *      name;                   /* section name */
    off_t       offset;                 /* relative offset to original module */
    } FAC_SECTION_OFFSET;

/* 
 * Encapsulation of filesystem accesses. This is where the target loader's cache
 * sits (no cache for the host loader).
 */

typedef struct load_module_info		/* information about file to load */
    {
    int			fd;		/* file descriptor */
    char *		fileName;	/* textual filename from descriptor */
    MODULE_SOURCE       moduleOpened;   /* FROM_FD or FROM_FILENAME */
    LOAD_TYPE           loadType;	/* relocatable, executable, ... */
#ifndef HOST
    void * 		cacheBuffer;	/* readahead buffer */
    size_t		usedCacheSize;  /* soft limit of the cache buffer */
    size_t		cacheIndex;	/* seek pointer into cache buffer */
    size_t		maxCacheSize;	/* tweakable cache size */
    off_t		fileIndex;	/* seek index into fd */
#endif

    /* Fix And Continue */

    BOOL        patch;            /* TRUE = Patched module */
    void *      original_module;  /* Patched original module */
    SL_LIST     sections_offset;  /* List of sections and their offsets */

#ifdef _WRS_CONFIG_LANG_LIB_TLS_STD
    /* Linux TLS ABI */
    void * moduleId;	  /* ID of module being loaded */
#endif /* CONFIG_LANG_LIB_TLS_STD */

#ifdef _WRS_CONFIG_SECURE_LOADER
    BOOL        skipSigCheck;     /* TRUE = skip signature checking */
#ifdef _WRS_CONFIG_SECURE_LOADER_ENCRYPTION
    void *      pDecryptCtx;      /* secure loader decryption context */
#endif /* _WRS_CONFIG_SECURE_LOADER_ENCRYPTION */
#endif /* _WRS_CONFIG_SECURE_LOADER */

#ifdef	_WRS_CONFIG_BRANCH_ISLAND_SUPPORT
    SYM_ADRS *	bIAddrTbl;        /* branch island address table */
#endif	/* _WRS_CONFIG_BRANCH_ISLAND_SUPPORT */
    } LOAD_MODULE_INFO;

typedef struct
    {
    SYM_ADRS    pAddr;  /* symbol's address */
    SYM_TYPE    type;   /* symbol's type */
    SYMBOL_ID   symId;  /* ID of the symbol */
    unsigned char other; /* st_other member of ELF symbol */
    } SYM_INFO;
 
typedef SYM_INFO *      SYM_INFO_TBL;   /* table of symbol address/type info */
typedef SYM_INFO_TBL *  SYMINFO_REFS;   /* table of ptr to symbol info tables */ 

/* section types */

typedef enum section_type       /* Section types */
    {
    SECTION_UNKNOWN =   0,
#define SECTION_UNKNOWN SECTION_UNKNOWN
    SECTION_RODATA =    1,      /* read-only data section */
#define SECTION_RODATA  SECTION_RODATA
    SECTION_TEXT =      2,      /* text section */
#define SECTION_TEXT    SECTION_TEXT
    SECTION_DATA =      3,      /* data section */
#define SECTION_DATA    SECTION_DATA
    SECTION_BSS =       4,      /* bss section */
#define SECTION_BSS     SECTION_BSS
    SECTION_EXIDX =     5       /* exidx section */
#define SECTION_EXIDX   SECTION_EXIDX
    } SECTION_TYPE;

typedef struct modListDesc * MODLIST_ID;        /* module list ID */
typedef struct sectionDesc * SECTION_ID;        /* section ID */

typedef enum section_type SECTION_T;

typedef struct sectionDesc      /* module section descriptor */
    {
#ifdef HOST
    OBJ_CORE    handle;                 /* handle management */
#else
    HANDLE  handle;                     /* handle management */
#endif  /* HOST */
    DL_NODE             sectionNode;    /* double-linked list node information*/
    char *              name;           /* section name */
    void *              address;        /* section address */
    size_t		size;           /* section size */
    enum section_type   type;           /* section type */
    int                 flags;          /* section flags */
    size_t		alignment;	/* section alignment */
    UINT32		checksum;       /* section cksum */
    UINT32              fileChecksum;   /* section cksum before relocation */
    } SECTION_DESC;

typedef struct section_info_desc        /* Info about a loadable section   */ 
    {
    SL_NODE             scnInfoNode;    /* Point to next node in list      */
    char *              name;           /* Section's name                  */
    enum section_type   type;           /* Section's type                  */
    off_t		offset;         /* Offset of section in object module*/
    size_t		size;           /* Section's size                    */
    size_t		alignment;      /* Section's alignment               */
    UINT32              flags;          /* Section's flags                   */
    void *              address;	/* Section's address             */
    off_t		offsetInSeg;    /* Section's offset in segment  */
    UINT32              directiveIdx;  /* Index of the related load directive*/
#ifdef HOST
    BOOL                scnIsCached;
#endif
    SECTION_ID          sectionId;

    /* Fix & Continue */
    BOOL                noInstall;      /* Do not install section in memory */
    } SECTION_INFO_DESC;

typedef struct load_segment_directive
    {
    UINT32	type;                    /* type of the segment */
    void *      address;                 /* address of the segment */
    BOOL        memAllocatedByCaller; /* True iff the caller allocated mem. */
    } LOAD_SEGMENT_DIRECTIVE;

/* variable declarations */

extern size_t	loaderCacheBufferSize;	    /* loader's cache buffer size */

/* declarations */

extern STATUS   loadModuleInfoFromFd (int fd, 
				      LOAD_MODULE_INFO * pLoadModuleInfo);
extern STATUS   loadModuleInfoRelease (LOAD_MODULE_INFO * pLoadModuleInfo);
extern off_t	loadModuleSeek (LOAD_MODULE_INFO * pLoadModuleInfo, 
				off_t offset, MSEEK_MODE mode);
extern STATUS   loadModuleStringRead (LOAD_MODULE_INFO * pLoadModuleInfo, 
				      char * buffer, size_t nBytes);
extern STATUS	loadModuleInfoInit (LOAD_MODULE_INFO * pLoadModuleInfo, int fd,
				    char * fileName, MODULE_SOURCE source);
extern STATUS   loadModuleValueRead (LOAD_MODULE_INFO * pLoadModuleInfo, 
				     void * buffer, size_t nBytes);

#ifdef __cplusplus
}
#endif

#endif /* __INCloadFileLibPh */
