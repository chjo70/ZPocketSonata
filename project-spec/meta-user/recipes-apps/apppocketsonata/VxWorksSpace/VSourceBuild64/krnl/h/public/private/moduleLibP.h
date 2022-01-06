/* moduleLibP.h - private module descriptor structure header */

/*
 * Copyright (c) 1998, 2004-2006, 2009-2010, 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
10nov15,zwu  Modify _func_moduleExidxGet prototype (V7COR-2966)
08jul15,elp  added _func_moduleExidxGet() (V7COR-2966).
16apr14,rlp  Added moduleIsLastModuleMatched and moduleSectionsCksumCompare
	     prototypes.
14apr14,rlp  Added moduleSectionsFileChecksumSet().
02jul13,jmp  Added moduleCommonSymEach() & moduleUndefSymEach().
25jun13,elp  Added moduleFlagsSet() (WIND00408631).
29apr10,pad  Moved extern C statement after include statements.
23feb10,v_r  Revert structure fields reorganization until we can update
                 host side as well.
22feb10,v_r  LP64 TODOS cleanup + structure reorganization.
25sep09,v_r  Added library function pointers definitions.
16jun09,v_r  LP64 adaptation: updated sections size and alignment to size_t.
30apr09,v_r  LP64 adaptation (phase #1) : updated code following code
                 adaptation guidelines (excepted FUNCPTR mods and struct reorg).
23oct06,dbt  Added information in section descriptor.
18mar05,v_r  Added moduleSectionChecksumSet() as needed by host side.
15feb05,v_r  Fixed SPR #98274 (loader errno review). Added moduleIdVerify()
		 as it's also used by host side now.
21oct04,x_p  Added moduleDescDestroy prototype
21sep04,jn   Final minor changes to allow code-sharing
18sep04,jn   Move towards shared code between host and target
08jun04,x_p  Added flags in MODULE_SEG_INFO
31may04,jn   Make section related API's available
05apr04,jn   Clean up - remove unused declarations and development-related
                 comments
28oct98,pad  Created based on AE version.  
*/

#ifndef __INCmoduleLibPh
#define __INCmoduleLibPh

/* includes */

#ifdef HOST
#include <host.h>
#include <vmutex.h>
#include <pdLib.h>
#include <tgtmem.h>
#include <objLib.h>
#include <dllLib.h>
#include <private/loadFileLibP.h>
#else
#include <vxWorks.h>
#include <limits.h>
#include <dllLib.h>
#include <semLib.h>
#include <memPartLib.h>
#include <private/handleLibP.h>
#include <private/loadFileLibP.h>
#include <symbol.h>
#endif	/* HOST */

#include <moduleLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */
typedef struct modListDesc         /* module list descriptor */
    {
#ifdef HOST
    OBJ_CORE            handle;	    /* handle management */
#else
    HANDLE              handle;	    /* handle management */
#endif  /* HOST */
    DL_LIST moduleList;		    /* list of loaded modules */
    SEM_ID  moduleListSem;	    /* semaphore to protect moduleList */
    SEM_ID  moduleSectionSem;	    /* semaphore to protect all scn lists */
    SEM_ID  moduleSegmentSem;	    /* semaphore to protect all segment lists */
    DL_LIST moduleCreateHookList;   /* list of associated create hooks */
    SEM_ID  moduleCreateHookSem;    /* semaphore to protect create hooks */
    BOOL    moduleCreateHookInitialized;    /* should be initialized to FALSE */
    PART_ID memPartId;			    /* dedicated memory partition ID */
    } MODLIST_DESC;

typedef struct
    {
    DL_NODE node;
    FUNCPTR func;
    } MODCREATE_HOOK;

/* Library function pointers */

extern MODULE_ID (* _func_moduleIdFigure)
    (
    void * moduleNameOrId /* module name or module ID */
    );

extern STATUS (* _func_moduleSegInfoGet)
    (
    MODULE_ID           moduleId,       /* module to query */
    MODULE_SEG_INFO *   pModSegInfo     /* ptr to module segment info struct */
    );

extern MODLIST_ID (* _func_kernelModuleListIdGet) (void);

extern void (* _func_moduleExidxGet) (void * addr, 
                                      void * exidx_start, void * exidx_end,
                                      void ** pExidxStart, void ** pExidxEnd);

/* defines */

#define MDLNODE_TO_ID(pNode) (pNode != NULL ? (MODULE_ID) ((char *) pNode - \
				   offsetof (MODULE, moduleNode)) \
				 : NULL)

#define SCNNODE_TO_ID(pNode) (pNode != NULL ? (SECTION_ID) ((char *) pNode - \
				   offsetof(SECTION_DESC, sectionNode))\
				 : NULL)

/* global var declarations */

extern MODLIST_ID   kernelModuleListId;

/* Function declarations */

extern STATUS	    moduleDescDestroy(MODULE_ID moduleId, BOOL dealloc);
extern STATUS	    moduleIdVerify(MODULE_ID moduleId);
extern SECTION_ID   moduleFirstSectionGet(MODULE_ID moduleId);
extern SECTION_ID   moduleNextSectionGet(SECTION_ID sectionId);
#ifdef HOST
extern int	    moduleSectionChecksumGet(SECTION_ID sectionId);
#endif
extern STATUS	    moduleSectionChecksumSet(SECTION_ID  sectionId);
extern STATUS	    moduleSectionsFileChecksumSet (SECTION_ID  sectionId);
extern STATUS	    moduleSectionDescFree(SECTION_ID sectionId);
extern SECTION_ID   moduleSectionDescGet(MODULE_ID moduleId);
extern SECTION_ID   moduleSectionRegister (MODULE_ID moduleId, char *name,
					   SECTION_T type, void * location, 
					   size_t length, int flags,
					   size_t alignment);
extern STATUS	    moduleSegInfoGet(MODULE_ID moduleId,
				     MODULE_SEG_INFO * pModSegInfo);
extern STATUS       moduleFlagsSet(MODULE_ID moduleId, int flags);
extern STATUS       moduleCommonSymEach (MODULE_ID moduleId,
					 BOOL (*routine) (SYMBOL_ID symbolId,
							  MODULE_ID moduleId,
							  _Vx_usr_arg_t arg),
					 _Vx_usr_arg_t routineArg,
					 SYMBOL_ID * pLastSym);
extern STATUS       moduleUndefSymEach (MODULE_ID moduleId,
					BOOL (*routine) (char * name,
							  MODULE_ID moduleId,
							  _Vx_usr_arg_t arg),
					_Vx_usr_arg_t routineArg,
					char ** pLast);
extern MODULE_ID    moduleIsLastModuleMatched (char * moduleName);
extern BOOL         moduleSectionsCksumCompare (MODULE_ID module1Id,
                                                 MODULE_ID module2Id);

#ifdef __cplusplus
}
#endif

#endif /* __INCmoduleLibPh */

