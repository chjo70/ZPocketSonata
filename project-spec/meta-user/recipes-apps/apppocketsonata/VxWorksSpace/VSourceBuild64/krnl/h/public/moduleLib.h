/* moduleLib.h - object module list management header */

/*
 * Copyright (c) 1992, 1996, 2003-2005, 2009-2010, 2014-2016
 * Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */ 

/*
modification history
--------------------
22jan16,x_p  Fix & Continue TOC support (V7COR-3992)
23sep15,jmp  Added support for Fix & Continue facility (US65040).
22aug14.wap  Fix defect V7COR-1541, add a custom section flag to
             indicate encrypted/signed ELF image sections when
             security is enabled
16apr14,rlp  Added a field for module's modification time.
17dec10,jmp  Updated moduleEach() and moduleSegEach() to use fully
             qualified function pointer instead of FUNCPTR
             (CQ:WIND00246939).
01apr10,pad  Moved declaration of extern C block for C++ after the
             inclusion of header files.
22feb10,v_r  LP64 TODOS cleanup.
18jan10,rlp  Added undefined and common symbol lists.
16jun09,v_r  LP64 adaptation: updated segment sizes to size_t.
30apr09,v_r  LP64 adaptation (phase #1) : updated code following code
             adaptation guidelines (excepted FUNCPTR mods and struct reorg).
14feb05,v_r  Fixed SPR #98274 (loader errno review).
             Moved private routines to moduleLibP.h
             Added segment type for loadFileLibP.h
             Cleanups.
02feb05,v_r  Fixed SPR #104657 (moduleShow() does not present display
             options) by moving the now unsupported display options in 
             moduleShow.c and removing the unused ones.
             Updated copyright notice to 2005.
10jan05,v_r  Fixed SPR #104659 (moduleShow now a separate component, need
             to include moduleShow.h in moduleLib.h)
21oct04,x_p  Added moduleSectionDescFree() prototype.
18sep04,jn   Move towards shared code for host and target
05apr04,jn   Clean up - remove unused declarations and development-related
             comments
03apr03,jn   merge from AE loader moduleLibh 
03apr03,to   replaced OBJ_CORE with HANDLE in MODULE (de-classify).
11sep96,pad  added MODULE_GROUP_MAX definition (SPR #7133).
30oct92,jmm  added prototype for moduleCheck() - spr 1693
22sep92,rrr  added support for c++
27aug92,jmm  changed MODULE_SEG_INFO struct to always include TEXT/DATA/BSS
             changed symFlags to flags
             added prototypes for moduleNameGet(), moduleFlagsGet()
             changed type for ctors and dtors to VOIDFUNCPTR
01aug92,srh  added lists for static constructors/destructors to
             MODULE struct.
09apr92,jmm  written
*/

#ifndef __INCmoduleLibh
#define __INCmoduleLibh

/* includes */

#ifdef HOST 
#include "host.h"
#include "tgtmem.h"
#include "pdLib.h"
#include "wtxtypes.h"
#include "dllLib.h"
#include "sllLib.h"
#else
#include "dllLib.h"
#include "sllLib.h"
#include "limits.h"
#include "private/handleLibP.h"
#include "memPartLib.h"
#include "moduleShow.h"
#endif	/* HOST */

#ifdef __cplusplus
extern "C" {
#endif

/* moduleLib Status Codes */

#define S_moduleLib_MODULE_NOT_FOUND		(M_moduleLib | 1)
#define S_moduleLib_HOOK_NOT_FOUND              (M_moduleLib | 2)
#define S_moduleLib_BAD_CHECKSUM                (M_moduleLib | 3)
#define S_moduleLib_MAX_MODULES_LOADED          (M_moduleLib | 4)
#define S_moduleLib_INVALID_SECTION_ID          (M_moduleLib | 5)
#define S_moduleLib_INVALID_MODULE_ID		(M_moduleLib | 6)

/* max number of module groups */

#define MODULE_GROUP_MAX	65535

/* Types of object module formats - for backward compatibility */

#define MODULE_A_OUT 0          /* format is a.out */
#define MODULE_B_OUT 1          /* format is b.out */
#define MODULE_ECOFF 2          /* format is ECOFF */
#define MODULE_ELF   3          /* format is ELF */

/* Types of segments */

#define SEGMENT_UNKNOWN	0       /* unknown segment */
#define SEGMENT_TEXT    2       /* text segment */
#define SEGMENT_DATA    4       /* data segment */
#define SEGMENT_BSS     8       /* bss segment */

/* segment flag bits */

#define SEG_FREE_MEMORY		1 /* Free memory when deleting this segment */
#define SEG_WRITE_PROTECTION	2 /* Segment's memory is write-protected,
				   * need to call memory managment routines
				   * to unprotect when deleting */

/* section flag bits */

#define SCN_FREE_MEMORY		1 /* Free memory when deleting this section */
#define SCN_NO_CHECKSUM		2 /* do not perform checksum of this section */
#define SCN_ENCRYPTED		4 /* Section is encrypted/digitally signed */

/* moduleCheck() options */

#define MODCHECK_NOPRINT	0x1 /* Don't print module names during check */

#define MODCHECK_TEXT		0x2	/* check text sections */
#define MODCHECK_DATA		0x4	/* check data sections */
#define MODCHECK_BSS		0x8	/* check bss sections */
#define MODCHECK_RODATA		0x10	/* check read-only sections */

#define MODCHECK_ALL		(MODCHECK_TEXT | \
				 MODCHECK_DATA | \
				 MODCHECK_BSS  | \
				 MODCHECK_RODATA) /* check all sections */

/* module status information */

#define MODULE_REPLACED	0x00010000 /* set if the module is loaded twice */

#ifdef _WRS_CONFIG_LP64
typedef size_t	SEG_SIZE;
#else /* _WRS_CONFIG_LP64 */
typedef int	SEG_SIZE;
#endif /* !_WRS_CONFIG_LP64 */

/* Typedefs */

typedef struct
    {
    DL_NODE	segmentNode;	    	/* double-linked list node information*/
    void *	address;		/* segment address */
    SEG_SIZE	size;			/* segment size */
    int		type;			/* segment type*/
    int		flags;			/* segment flags */
    } SEGMENT;

typedef SEGMENT * SEGMENT_ID;		/* segment ID */

typedef struct
    {
    void *	textAddr;		/* address of text segment */
    void *	dataAddr;		/* address of data segment */
    void *	bssAddr;		/* address of bss segment */
    SEG_SIZE	textSize;		/* size of text segment */
    SEG_SIZE	dataSize;		/* size of data segment */
    SEG_SIZE	bssSize;		/* size of bss segment */
    int		textFlags;		/* flags for text segment */
    int		dataFlags;		/* flags for data segment */
    int		bssFlags;		/* flags for bss segment */
    } MODULE_SEG_INFO;

typedef struct
    {
    char		name [NAME_MAX];/* module name */
    int			format;         /* object module format */
    int			group;		/* group number */
    MODULE_SEG_INFO	segInfo;	/* segment info */
    } MODULE_INFO;

typedef UINT16 MOD_GROUP;

typedef struct module
    {
#ifdef HOST
    OBJ_CORE	handle;		    /* handle management */
#else
    HANDLE	handle;		    /* handle management */
#endif	/* HOST */
    DL_NODE	moduleNode;	    /* double-linked list node information */

    /*
     * nameWithPath is now the preferred field to use for name and 
     * path. The separate name and path fields are kept for backward
     * compatibility, but they may not hold valid information, since
     * they are of limited size. 
     */

    char *	nameWithPath;	    /* module name and path */
    char	name [NAME_MAX];    /* module name */
    char	path [PATH_MAX];    /* module path */
    int		flags;		    /* symFlags as passed to the loader */
    DL_LIST	sectionList;	    /* list of section */
    DL_LIST	segmentList;	    /* list of segments */
    int         format;		    /* object module format. Only ELF now */
    MOD_GROUP	group;		    /* group number */
    VOIDFUNCPTR * ctors;	    /* list of static constructor callsets */
    VOIDFUNCPTR * dtors;	    /* list of static destructor callsets */
    UINT	commTotalSize;	    /* memory used by common symbols */
    BOOL	swapNeeded;	    /* TRUE if the headers need byte swap */
    int		undefSymCount;	    /* number of undefined symbols */
#ifdef HOST
    DL_LIST	undefSymList;	    /* list of undefined symbol names */
#else
    SL_LIST	undefSymList;	    /* list of undefined symbol names */
    SL_LIST	commonSymList;	    /* list of common symbol structures */
#endif
    void *	user1;		    /* reserved for use by end-user */
    time_t	mtime;		    /* time of modification time */
    void *	reserved2;	    /* reserved for use by WRS */
    void *	reserved3;	    /* reserved for use by WRS */
    void *	reserved4;	    /* reserved for use by WRS */

    /* Fix & Continue information */
    BOOL        patch;              /* TRUE if module is a patch */
    struct module * original_module;/* pointer to original module */
    SL_LIST     sections_offset;    /* sections offsets list */
#if defined(_WRS_CONFIG_LP64) && (CPU_FAMILY==PPC)
    void *       tocBase;           /* module TOC (PPC64) */
    BOOL         tocFound;          /* TOC found (PPC64) */
#endif
    } MODULE;

typedef struct module * MODULE_ID;  /* module ID */
 
/* function declarations */

extern STATUS	    moduleCheck (int options);
extern MODULE_ID    moduleCreate (char * name, int format, int flags);
extern STATUS	    moduleCreateHookAdd (FUNCPTR moduleCreateHookRtn);
extern STATUS	    moduleCreateHookDelete (FUNCPTR moduleCreateHookRtn);
extern STATUS	    moduleDelete (MODULE_ID moduleId);
extern MODULE_ID    moduleEach	(BOOL (*routine) (MODULE_ID moduleId,
						 _Vx_usr_arg_t userArg),
				 _Vx_usr_arg_t userArg);
extern MODULE_ID    moduleFindByGroup (int groupNumber);
extern MODULE_ID    moduleFindByName (char * moduleName);
extern MODULE_ID    moduleFindByNameAndPath (char * moduleName,
						    char * pathName);
extern int	    moduleFlagsGet (MODULE_ID moduleId);
extern MODULE_ID    moduleIdFigure (void * moduleNameOrId);
extern int	    moduleIdListGet(MODULE_ID * idList, int maxModules);
extern STATUS	    moduleInfoGet (MODULE_ID moduleId,
				    MODULE_INFO * pModuleInfo);
extern STATUS	    moduleInit (MODULE_ID moduleId, char * name, int format, 
				  int flags);
extern STATUS	    moduleLibInit (void);
extern char *	    moduleNameGet (MODULE_ID moduleId);
extern STATUS	    moduleSegAdd (MODULE_ID moduleId, int type, void * location,
				    size_t length, int flags);
extern SEGMENT_ID   moduleSegEach (MODULE_ID moduleId,
				   BOOL (*routine) (SEGMENT_ID segmentId,
						    MODULE_ID moduleId,
						    _Vx_usr_arg_t userArg),
				   _Vx_usr_arg_t userArg);
extern SEGMENT_ID   moduleSegFirst (MODULE_ID moduleId);
extern SEGMENT_ID   moduleSegGet (MODULE_ID moduleId);
extern SEGMENT_ID   moduleSegNext (SEGMENT_ID segmentId);

#ifdef __cplusplus
}

/*
 * Inlined C++ wrappers for the old-style FUNCPTR based function
 * prototypes.
 */

extern MODULE_ID moduleEach (FUNCPTR routine, _Vx_usr_arg_t userArg) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");
extern SEGMENT_ID moduleSegEach (MODULE_ID moduleId, FUNCPTR routine,
				 _Vx_usr_arg_t userArg) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline MODULE_ID moduleEach
    (
    FUNCPTR routine,
    _Vx_usr_arg_t userArg
    )
    {
    return moduleEach ((BOOL (*)(MODULE_ID moduleId,
				 _Vx_usr_arg_t userArg))routine,
		       userArg);
    }

inline SEGMENT_ID moduleSegEach 
    (
    MODULE_ID moduleId,
    FUNCPTR routine,
    _Vx_usr_arg_t userArg
    )
    {
    return moduleSegEach (moduleId,
			  (BOOL (*)(SEGMENT_ID segmentId,
				    MODULE_ID moduleId,
				    _Vx_usr_arg_t userArg))routine,
			  userArg);
    }
#endif /* __cplusplus */

#endif /* __INCmoduleLibh */

