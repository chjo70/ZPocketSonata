/* pgMgrLibP.h - page manager library private header */

/* 
 * Copyright (c) 1999-2005,2007-2010, 2015 Wind River Systems, Inc. 
 *
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
22jan15,pcs  CERT: Added macros PAGE_MGR_PAGE_FREE_IGNORE_RETURN and 
             PAGE_MGR_PAGE_FREE to consolidate the CERT code changes and also 
             removed pgMgrPageFree() and pgMgrPageUnmap().
05nov10,zl   removed pgMgrPhysToVirt and pgMgrVirtToPhys
27apr10,pcs  Updated API's pgMgrPageUnmap and pgMgrPageFree to take an 
             additional parameter option.
29apr10,pad  Moved extern C statement after include statements.
14apr10,zl   added _func_pgMgrOverlapIterate
11jan10,zl   added growRtn to page manager.
24jun09,zl   replaced lastVirtAddr with lastOverlapNode
07apr08,pcs  update for discontiguous overlapped memory support.
29mar07,pcs  change numPagesMapped to type atomic_t.
07sep05,zl   added numPagesMapped to PAGE_MGR_OBJ.
27jun05,zl   cleanup based on new adrSpaceLib APIs.
03jun05,yvp  Added #ifndef	_ASMLANGUAGE. 
             Updated copyright. #include now with angle-brackets.
24jan05,aeg  added pgMgrPrivateUnmap() function prototype (SPR #106381).
13sep04,zl   cleaned up MM private API
10sep04,gls  cleanup
08jul04,tam  changed PAGE_MGR_ATTR_ALLOC_CONTIG_DEFAULT to be 
             PAGE_MGR_ATTR_ALLOC_CONTIG
19may04,tam  moved definition from pgMgrLib.h
22oct03,gls  proted from AE version 01b
*/

#ifndef __INCpgMgrLibPh
#define __INCpgMgrLibPh

/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <dllLib.h>
#include <sllLib.h>
#include <vmLib.h>
#include <private/adrSpaceLibP.h>
#include <base/b_atomic_t.h>

#ifdef __cplusplus
extern "C" {
#endif

/* the page manager can set protection, cache and SPL attributes */

#define PAGE_MGR_ATTR_MMU_MSK		(MMU_ATTR_PROT_MSK | \
					 MMU_ATTR_CACHE_MSK | \
					 MMU_ATTR_SPL_MSK)

#define PAGE_MGR_ATTR_MMU_GET(attr)	((attr) & PAGE_MGR_ATTR_MMU_MSK)

#ifdef _WRS_CONFIG_CERT
/* For CERT, these macros are no-ops. */

#define PAGE_MGR_PAGE_FREE_IGNORE_RETURN(pgMgrId, virtAdr, numPages, option) 
#else
#define PAGE_MGR_PAGE_FREE_IGNORE_RETURN(pgMgrId, virtAdr, numPages, option) \
        ((void )pgMgrPageFree (pgMgrId, virtAdr, numPages, option))
#endif

#ifndef	_ASMLANGUAGE

/* typedefs */

typedef unsigned int PAGE_MGR_ATTR;
typedef unsigned int PAGE_MGR_OPTS;

typedef struct overlapRgnNode
    {
    SL_NODE		slNode;		/* node in the overlap region list */
    VIRT_ADDR		virtAddr;	/* virtual address  */
    size_t		pgCount;	/* size in pages */
    int			refCnt;		/* reference count */
    } OVERLAP_RGN_NODE;

typedef struct pgMgrObj
    {
    PAGE_POOL_ID	virtPgPoolId;	/* virtual page pool */
    PAGE_POOL_ID 	physPgPoolId; 	/* physical page pool */
    OVERLAP_RGN_NODE *	pLastRgnNode;	/* last node added from overlap rgn */
    VM_CONTEXT_ID	vmContextId;	/* VM context ID */
    DL_LIST		mmapList;	/* list of mmap blocks */ 
    PAGE_MGR_OPTS	options;        /* page manager options */
    atomic_t		numPagesMapped;	/* number of mapped pages */
    VIRT_ADDR		(*growRtn)	/* page manager growth routine */
			    (
			    struct pgMgrObj *	pgMgrId,
			    VIRT_ADDR		virtAdr, 
			    PHYS_ADDR		physAdr,
			    size_t		numVirtPages,
			    PAGE_MGR_ATTR	attr
			    );
    } PAGE_MGR_OBJ;

/*
 * Note: lastVirtAddr corresponds to the start address of the last node in the
 *       overlapAddrList that was used by the page manager. Anytime more virtal
 *       addrs are need, the overlapListAddr will be transversed beyond this 
 *       last accessed node.
 *       When the page manager is created, the lastVisrAddr is set to 0.
 *       The access to the lastvirtAddr entry is protected by taking the 
 *       overlapAddrListMutex.
 */

typedef struct pgMgrInfo
    {
    size_t		numPages;	/* number of pages */
    size_t		numPagesMapped;	/* number of pages */
    } PAGE_MGR_INFO;

/* fucntion pointers for scalability */

extern VIRT_ADDR (*_func_pgMgrPageAlloc) (PAGE_MGR_ID pgMgrId, size_t numPages,
					  PAGE_MGR_ATTR attr);
extern STATUS	 (*_func_pgMgrPageMap) (PAGE_MGR_ID pgMgrId, VIRT_ADDR virtAdr,
					PHYS_ADDR physAdr, size_t numPages,
					PAGE_MGR_ATTR attr);
extern STATUS	 (*_func_pgMgrPageFree) (PAGE_MGR_ID pgMgrId, VIRT_ADDR virtAdr,
					 size_t numPages, int option);
extern STATUS	 (*_func_pgMgrOverlapIterate) (STATUS (*callback)
						 (
						 VIRT_ADDR virtAddr,
						 size_t	size,
						 int refCnt
						 ));

/* function prototypes */

STATUS	    pgMgrBaseLibInit (void);
STATUS	    pgMgrLibInit (void);
PAGE_MGR_ID pgMgrCreate (PAGE_MGR_OPTS options);
STATUS	    pgMgrDelete (PAGE_MGR_ID pgMgrId);
VIRT_ADDR   pgMgrPageAlloc (PAGE_MGR_ID pgMgrId, size_t numPages,
                          PAGE_MGR_ATTR attr);
VIRT_ADDR   pgMgrPageAllocAt (PAGE_MGR_ID pgMgrId, VIRT_ADDR virtAdr,
                            PHYS_ADDR physAdr, size_t numPages,
                            PAGE_MGR_ATTR attr);
STATUS	    pgMgrPageMap (PAGE_MGR_ID pgMgrId, VIRT_ADDR virtAdr,
                          PHYS_ADDR physAdr, size_t numPages, 
			  PAGE_MGR_ATTR attr);
#ifndef _WRS_CONFIG_CERT
STATUS 	    pgMgrPageFree (PAGE_MGR_ID pgMgrId, VIRT_ADDR virtAdr,
                           size_t numPages, int option);
STATUS	    pgMgrPageUnmap (PAGE_MGR_ID pgMgrid, VIRT_ADDR virtAdr, 
			    size_t numPages, int option);
#endif /* !_WRS_CONFIG_CERT */
STATUS	    pgMgrPageAttrSet (PAGE_MGR_ID pgMgrId, VIRT_ADDR virtAdr,
                              size_t numPages, MMU_ATTR mmuAttr);
STATUS	    pgMgrPageAttrGet (PAGE_MGR_ID pgMgrId, VIRT_ADDR virtAdr,
                              MMU_ATTR * pMmuAttr);
PAGE_MGR_ID pgMgrInit (PAGE_MGR_OBJ * pPgMgr, PAGE_MGR_OPTS opts);
void        pgMgrShowInit (void);
STATUS	    pgMgrPrivateUnmap (PAGE_MGR_ID pgMgrId);
STATUS	    pgMgrInfoGet (PAGE_MGR_ID pgMgrId, PAGE_MGR_INFO * pgMgrInfo);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpgMgrLibPh */
