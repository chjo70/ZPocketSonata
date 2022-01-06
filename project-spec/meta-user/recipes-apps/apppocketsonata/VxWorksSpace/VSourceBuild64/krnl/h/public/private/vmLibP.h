/* vmLibP.h - private header for architecture independent mmu interface */

/* 
 * Copyright (c) 1992-1993, 2003-2010, 2014, 2016 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
16dec16,cfm  added mmuDataNoExec (F7142)
29jul15,pcs  Made vmPteSizeGet() not supported for CERT.
03jun15,pcs  Added the prototype for _func_taskMmuCurrentSet
21may15,pcs  Update code corresponding to the deletion of the macro
             _WRS_MMU_HAS_MAP_STATE_API
03may15,pcs  Added mmuDirectPageMap to struct MMU_LIB_FUNCS and added macro
             VM_DIRECT_MAP_SUPPORT_AVAILABLE()
01may15,pcs  Update code corresponding to the deletion of the macro 
             _WRS_ARCH_HAS_TASK_MMU_CURRENT_SET
27apr15,pcs  Updated MMU_LIB_FUNCS to make mmuPteSizeGet() and 
             mmuOptimizedSizeGet() available for are arches.
27apr15,pcs  Deleted macro _WRS_MMU_HAS_SPL_TRANSLATE_API and all code 
             associated with it as part of unifying the VM/MMU layer for all 
             arches.
12dec14,pcs  Added VM_DEFAULT_CACHE_COHERENCY_ATTR to DEFAULT_VM_MAP_ATTR
                 (V7COR-2363).
27jan14,pcs  Removed entry mmuSoftCfgEnabled from struct vmLibInfo and deleted 
             macro VM_MMUSOFT_ENABLED
05nov10,zl   removed VM_PHYS_TRANSLATE() for 64-bit VxWorks.
25oct10,zl   added TASK_MMU_CURRENT_SET()
01jul10,zl   added page optimization field to VM_LIB_INFO
29apr10,pad  Moved extern C statement after include statements.
10sep09,jb   Fix Optimized size prototypes
24aug09,zl   added page optimization info routines, vmPgMap() options.
01jun09,zl   added MMU_ARCH_ATTR.
21apr09,zl   LP64 updates. Replaced msize_t with size_t
21apr09,gls  added MMU_ATTR_NOT_GLOBAL
26sep08,pcs  Fixed types inconsistencies with VM_CONTEXT_BUFFER_WRITE macro 
             arguments. Defect:WIND00084242
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in vsb.  
             Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
08jun07,kk   added vxSmpP.h
02may07,zl   introduced strong-typed function pointers, removed vmTransTblGet().
11may07,pcs  Add macro VM_DEFAULT_CACHE_COHERENCY_ATTR
06mar07,pcs  update vmPgMap to add 2 extra params.
13feb07,pes  Add support for _WRS_MMU_HAS_MAP_STATE_API macro.
05jul06,zl   removed mmuPageUnProtect from MMU_LIB_FUNCS.
11aug05,zl   moved common VM macros from the source files
29jun05,zl   removed adrSpaceId parameter from VM_CONTEXT_SWITCH();
             added vmKernelContextIdGet() and vmPgMap();
10jun05,jmp  updated VM_LIB_INFO to support vmContigBlockEach(), added
             VM_CONTIG_BLOCK_EACH() macro.
03jun05,yvp  Added #ifndef	_ASMLANGUAGE. 
             Updated copyright. #include now with angle-brackets.
07feb05,zl   moved VM_CONTEXT from vmLib.h
12oct04,pcs  Remove struct entries pVmCtxLockRtn & pVmPageProtectRtn since
             they are really not being used.
30sep04,pcs  Moved VM_CTX_MASK_XXX macros from vmLib.h to here.
20sep04,tam  added vmInfoGet() and VM_INFO
07jul04,aeg  removed VM_CONTEXT_CLASS related definitions.
03may04,pcs  Add support for optimize/lock/unlock feature's.
29apr04,pcs  Add a macro to get max physical address bit's supported by the CPU.
01apr04,zl   added mmuSoftCfgEnabled to VM_LIB_INFO.
19feb04,yp   adding data struct for tracking extra mappings
10nov03,yp   adding addrSpaceSegInfo structure
30oct03,sru  remove MMU_TRANS_TBL typedef
15oct03,sru  fix prototypes for PHYS_ADDR
19sep03,pcs  Implement code review changes.
11jul03,pcs  Port to Base 6.
22may03,dcc  added prototypes of vmContextTerminate () and vmContextDestroy ().
13feb93,kdl  fixed test in VM_TEXT_PAGE_PROTECT macro.
10feb93,rdc  added support for text page protection routine. 
08oct92,rdc  fixed VM_TRANSLATE macro.
22sep92,rrr  added support for c++
30jul92,rdc  added pointer to vmTranslate routine to VM_LIB_INFO.
27jul92,rdc  modified VM_LIB_INFO.
10jul92,rdc  written.
*/

#ifndef __INCvmLibPh
#define __INCvmLibPh


#include <vxWorks.h>
#include <vsbConfig.h>
#include <memLib.h>
#include <lstLib.h>
#include <private/objLibP.h>
#include <private/classLibP.h>
#include <private/semLibP.h>
#include <vmLib.h>
#include <mmuLib.h>
#include <private/vxSmpP.h>   /* for _WRS_MMU_HAS_MAP_STATE_API */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/*
 * For SMP, any shared data region that is created from the RAM need
 * to be memory coherent.
 * So we need to set the page attribute to MMU_ATTR_CACHE_COHERENCY.
 * The arches, need to specify this via the macro
 * VM_DEFAULT_CACHE_COHERENCY_ATTR
 * If they don't then we need to default to a valid value which for the PPC
 * arch is MMU_ATTR_CACHE_COHERENCY.
 */

#ifndef VM_DEFAULT_CACHE_COHERENCY_ATTR

#ifdef _WRS_CONFIG_SMP
/* For SMP */
#if  (CPU_FAMILY == PPC)
#define VM_DEFAULT_CACHE_COHERENCY_ATTR MMU_ATTR_CACHE_COHERENCY
#else
#define VM_DEFAULT_CACHE_COHERENCY_ATTR 0x0
#endif /* (CPU_FAMILY == PPC) */

#else
/* For UP */
#define VM_DEFAULT_CACHE_COHERENCY_ATTR 0x0
#endif /* _WRS_CONFIG_SMP */

#endif /* VM_DEFAULT_CACHE_COHERENCY_ATTR */

/* 
 * default MMU attr & attr mask used by the mapping fns. 
 * when the user doesn't specify one. 
 */

#define DEFAULT_VM_MAP_ATTR_MASK  (MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK |    \
                                   MMU_ATTR_CACHE_MSK | MMU_ATTR_SPL_MSK)
#define DEFAULT_VM_MAP_ATTR       ((MMU_ATTR_VALID | MMU_ATTR_SUP_RWX |        \
                                   MMU_ATTR_CACHE_DEFAULT |                    \
                                   VM_DEFAULT_CACHE_COHERENCY_ATTR))
/*
 * attribute mask values for vmContigBlockEach() for special cases:
 *   - VM_ATTR_ALL: all atributes used for block contiguity check
 *   - VM_ATTR_NONE: ignore all attributes
 */

#define VM_ATTR_ALL		  DEFAULT_VM_MAP_ATTR_MASK
#define VM_ATTR_NONE		  0x00000000

/*
 * options for vmPgMap() 
 *  - VM_MAP_NOALIAS: prevent mapping aliases for a physical address range. 
 *    This option requires the inverse page table component to be present. 
 *    Any feature relying on it must make INCLUDE_VM_INVTBL component 
 *    an explicit dependency.
 *  - VM_MAP_GLOBAL: perform mapping as a global mapping. Global mappings 
 *    are implicitly present in all VM contexts in the system (kernel and
 *    all RTPs).
 * The bit selection is such that it does not conflicts with the VM attribute
 * (VM_ATTR_xxx) and the address space alloc options (ADR_SPACE_OPT_xxx).
 */

#define VM_MAP_NOALIAS		  0x00100000
#define VM_MAP_GLOBAL		  0x00200000
#define VM_MAP_OPTIONS_MASK	  (VM_MAP_NOALIAS | VM_MAP_GLOBAL)

/* 
 * VM_SPACE_ALL can be used with vmContigBlockEach() to scan the entire
 * virtual address space (e.g. by vmContextShow()
 */

#define VM_SPACE_ALL	  	  ((size_t) -1)

/* validate arch configuration */

#if defined (_WRS_CONFIG_LP64)			&& \
   !defined (_WRS_MMU_HAS_BLOCK_INFO_API)
#warning "For 64-bit MMU libraries the block info API is required"
#endif

/*
 * Let the architecture specify wether the architecture dependent
 * MMU attribute type is 32-bit or 64-bit.
 */

#ifdef _WRS_MMU_HAS_64BIT_ARCH_ATTR
# ifdef _WRS_CONFIG_LP64
typedef unsigned long        MMU_ARCH_ATTR;
# else
typedef unsigned long long   MMU_ARCH_ATTR;
# endif
#else
typedef unsigned int         MMU_ARCH_ATTR;
#endif

#if (CPU_FAMILY == I80X86)
#define MMU_ATTR_NOT_GLOBAL     (~MMU_ATTR_SPL_0)
#else
#define MMU_ATTR_NOT_GLOBAL     0xffffffff
#endif /* (CPU_FAMILY == I80X86) */

/* compute if page is aligned without using "%" (SPR 6833) */

#define NOT_PAGE_ALIGNED(addr)	   ((((ULONG)(addr)) & (vmPageSize - 1)) != 0)

/* Convert from state to index into architecture dependent state array */

#define STATE_TO_PROT_INDEX(state) ((MMU_ATTR_PROT_GET(state)) >> \
				    MMU_ATTR_PROT_INDEX_SHIFT)

#define STATE_TO_CACHE_INDEX(state) ((MMU_ATTR_CACHE_GET(state)) >> \
				    MMU_ATTR_CACHE_INDEX_SHIFT)

#define STATE_TO_VALID_INDEX(state) ((MMU_ATTR_VALID_GET(state)) >> \
				    MMU_ATTR_VALID_INDEX_SHIFT)

/* Convert from architecture dependent state array index to state */

#define PROT_INDEX_TO_STATE(index) (((UINT)(index) << \
				     MMU_ATTR_PROT_INDEX_SHIFT) | \
				    MMU_ATTR_PROT_SUP_READ)

#define CACHE_INDEX_TO_STATE(index) ((UINT)index << MMU_ATTR_CACHE_INDEX_SHIFT)

#define VALID_INDEX_TO_STATE(index) ((UINT)index << MMU_ATTR_VALID_INDEX_SHIFT)

/* Convert from mask to index into architecture dependent mask array */

#define STATEMASK_TO_INDEX(statemask) ((MMU_ATTR_MSK_ID_GET(statemask)) >> \
				       MMU_ATTR_MSK_INDEX_SHIFT)

/* VM context mutex semaphore options */

#define VM_MUTEX_OPTIONS	(SEM_Q_PRIORITY | SEM_DELETE_SAFE | \
				SEM_INVERSION_SAFE)

/* macros to reference mmuLib routines indirectly through mmuLibFunc table */

#define MMU_PAGE_SIZE_GET       (*(mmuLibFuncs.mmuPageSizeGet))
#define MMU_ENABLE 	  	(*(mmuLibFuncs.mmuEnable))
#define MMU_TRANS_TBL_CREATE 	(*(mmuLibFuncs.mmuTransTblCreate))
#define MMU_STATE_SET 	  	(*(mmuLibFuncs.mmuStateSet))
#define MMU_CURRENT_SET 	(*(mmuLibFuncs.mmuCurrentSet))
#define MMU_GLOBAL_PAGE_MAP 	(*(mmuLibFuncs.mmuGlobalPageMap))

#define MMU_STATE_GET 	  	(*(mmuLibFuncs.mmuStateGet))
#define MMU_PAGE_MAP 	  	(*(mmuLibFuncs.mmuPageMap))
#define MMU_PAGE_UNMAP 	  	(*(mmuLibFuncs.mmuPageUnMap))
#define MMU_TRANSLATE 	  	(*(mmuLibFuncs.mmuTranslate))
#ifndef _WRS_CONFIG_LP64
#define MMU_PHYS_TRANSLATE  	(*(mmuLibFuncs.mmuPhysTranslate))
#endif
#define MMU_PAGE_OPTIMIZE       (*(mmuLibFuncs.mmuPageOptimize))
#define MMU_BUFFER_WRITE        (*(mmuLibFuncs.mmuBufferWrite))
#define MMU_PAGE_LOCK           (*(mmuLibFuncs.mmuPageLock))
#define MMU_PAGE_UNLOCK         (*(mmuLibFuncs.mmuPageUnlock))
#define MMU_MAX_PHYS_BITS_GET   (*(mmuLibFuncs.mmuMaxPhysBitsGet))

#define MMU_TRANS_TBL_DELETE 	(*(mmuLibFuncs.mmuTransTblDelete))
#define MMU_TRANS_TBL_UNION 	(*(mmuLibFuncs.mmuTransTblUnion))
#define MMU_TRANS_TBL_MASK 	(*(mmuLibFuncs.mmuTransTblMask))
#define MMU_ATTACH_INIT         (*(mmuLibFuncs.mmuTransTblUnionInit))
#define MMU_PAGE_BLOCK_SIZE_GET (*(mmuLibFuncs.mmuBlockSizeGet))
#define MMU_CONTIG_BLOCK_INFO_GET (*(mmuLibFuncs.mmuContigBlockInfoGet))

#define MMU_PTE_SIZE_GET	(*(mmuLibFuncs.mmuPteSizeGet))
#define MMU_OPTIMIZED_SIZE_GET	(*(mmuLibFuncs.mmuOptimizedSizeGet))

#define MMU_SPL_TRANSLATE(attr, mask, pArchAttr, pArchMask)		\
	((mmuLibFuncs.mmuSplTranslate == NULL) ? OK :			\
	  (*(mmuLibFuncs.mmuSplTranslate)) (attr, mask, pArchAttr, pArchMask))
	
#define MMU_SPL_ARCH_TRANSLATE(depAttr, pToIndep) 			\
	((mmuLibFuncs.mmuSplArchTranslate == NULL) ? OK :		\
	  (*(mmuLibFuncs.mmuSplArchTranslate)) (depAttr, pToIndep))

typedef struct vmLibInfo
    {
    BOOL vmLibInstalled;		/* full mmu support available */
    #define  vmBaseLibInstalled		vmLibInstalled
					/* vmBaseLibInstalled is for 5.x */
					/* style usage, but in 6.x is  */
					/* equivalent with vmLibInstalled */
    BOOL protectTextSegs;		/* TRUE == protext text segments */
    BOOL pgOptimize;			/* TRUE: enable page optimization */

    STATUS (*pVmStateSetRtn)		/* pointer to vmStateSet() */
	(
	VM_CONTEXT_ID	context,
	VIRT_ADDR	virtAdrs,
	size_t		len,
	UINT		stateMask,
	UINT		state
	);
    STATUS (*pVmStateGetRtn)		/* pointer to vmStateGet() */
	(
	VM_CONTEXT_ID	context,
	VIRT_ADDR	pageAddr,
	UINT *		pState
	);
    STATUS (*pVmEnableRtn)		/* pointer to vmEnable() */
	(
	BOOL enable
	);
    size_t (*pVmPageSizeGetRtn)		/* ptr to vmPageSizeGet() */
	(
	void
	);
    STATUS (*pVmTranslateRtn)		/* ptr vmTranslate() */
	(
	VM_CONTEXT_ID	context,
	VIRT_ADDR	virtualAddr,
	PHYS_ADDR *	physicalAddr
	);
#ifndef _WRS_CONFIG_LP64
    STATUS (*pVmPhysTranslateRtn) 	/* ptr vmPhysTranslate() */
	(
	VM_CONTEXT_ID	context,
	PHYS_ADDR	physicalAddr,
	VIRT_ADDR *	virtualAddr
	) _WRS_DEPRECATED("Please see vmPhysTranslate() guide for details");
#endif
    STATUS (*pVmPageMapRtn)		/* pointer to vmMap() */
	(
	VM_CONTEXT_ID	context,
	VIRT_ADDR	virtualAddr,
	PHYS_ADDR	physicalAddr,
	size_t		len
	);
    STATUS (*pVmPageUnMapRtn)		/* pointer to vmPgUnMap() */
	(
	VM_CONTEXT_ID	vmCtx,
	VIRT_ADDR	virtAdr,
	size_t		len
	);
    STATUS (*pVmBufferWriteRtn)		/* ptr to vmBufferWrite() */
	(
	VM_CONTEXT_ID	vmCtx,
	VIRT_ADDR	fromAddr,
	VIRT_ADDR	toAddr,
	size_t		len
	);
    STATUS (*pVmCtxSwitchRtn)		/* pointer to vmContextSwitch() */
	(
	VM_CONTEXT_ID	vmContextId
	);
    STATUS (*pVmContigBlockEachRtn)	/* pointer to vmContigBlockEach() */
	(
	VM_CONTEXT_ID	context,
	VIRT_ADDR	startAddr,
	size_t		len,
	UINT		stateMask,
	STATUS 	      (*eachRtn)
			    (
			    VIRT_ADDR	virtAddr,
			    size_t	size,
			    PHYS_ADDR	physAddr,
			    UINT	attr,
			    void *	pArg
			    ),
	void *		pEachArg
	);
    } VM_LIB_INFO;

/* Macros used internally by the OS components. */

#define VM_CTX_MASK_OUT        0x0      
#define VM_CTX_MASK_IN         0x1
#define VM_CTX_MASK_DELETE     0x2
#define VM_CTX_MASK_L2_FREE    0x4

#define VM_MMU_TRANS_TBL_GET(vmCtxId)	(vmCtxId->mmuTransTbl)
#define VM_DIRECT_MAP_SUPPORT_AVAILABLE() \
        ((mmuLibFuncs.mmuDirectPageMap != NULL) ? TRUE : FALSE)

/*
 * The following macros should be used by components that may need to 
 * call vmLib routines if the VM library is installed, but don't 
 * actually require VM support.
 *
 * Failure to do so will break the scalability of the system in regards 
 * to virtual memory management support.
 */

#define VM_INSTALLED		(vmLibInfo.vmLibInstalled)
#define VM_PG_OPTIMIZE		(vmLibInfo.pgOptimize)


#define VM_STATE_SET(context, virtualAddr, len, stateMask, state) \
    ((vmLibInfo.pVmStateSetRtn == NULL) ? \
    (ERROR) : \
    ((*vmLibInfo.pVmStateSetRtn) (context, (VIRT_ADDR) virtualAddr, len, \
				  stateMask, state)))

#define VM_STATE_GET(context, pageAddr, pState) \
    ((vmLibInfo.pVmStateGetRtn == NULL) ? \
    (ERROR) : \
    ((*vmLibInfo.pVmStateGetRtn) (context, (VIRT_ADDR) pageAddr, pState)))

#define VM_ENABLE(enable) \
    ((vmLibInfo.pVmEnableRtn == NULL) ? \
    (ERROR) : \
    ((*vmLibInfo.pVmEnableRtn) (enable)))

/*
 * VM_PAGE_SIZE_GET() should return 0 instead of ERROR when pVmPageSizeGetRtn
 * is NULL. But there is a lot of legacy code dating back to 5.x that
 * has been written with the current assumption.
 */

#define VM_PAGE_SIZE_GET() \
    ((vmLibInfo.pVmPageSizeGetRtn == NULL) ? \
    ((size_t) ERROR) : \
    ((*vmLibInfo.pVmPageSizeGetRtn) ()))

#define VM_TRANSLATE(context, virtualAddr, pPhysicalAddr) \
    ((vmLibInfo.pVmTranslateRtn == NULL) ? \
    (ERROR) : \
    ((*vmLibInfo.pVmTranslateRtn) (context, (VIRT_ADDR) virtualAddr, \
				   pPhysicalAddr)))

#ifndef _WRS_CONFIG_LP64
#define VM_PHYS_TRANSLATE(context, physicalAddr, pVirtualAddr) \
    ((vmLibInfo.pVmPhysTranslateRtn == NULL) ? \
    (ERROR) : \
    ((*vmLibInfo.pVmPhysTranslateRtn) (context, physicalAddr, pVirtualAddr)))
#endif

#define VM_PAGE_MAP(context, virtAddr, physAddr, len) \
    ((vmLibInfo.pVmPageMapRtn == NULL) ? \
    (ERROR) : \
    ((*vmLibInfo.pVmPageMapRtn) (context, virtAddr, physAddr, len)))

#define VM_PAGE_UNMAP(context, virtAddr, len) \
    ((vmLibInfo.pVmPageUnMapRtn == NULL) ? \
    (ERROR) : \
    ((*vmLibInfo.pVmPageUnMapRtn) (context, virtAddr, len)))

/*
 * VM_CONTEXT_BUFFER_WRITE() should be used only in very specific cases where
 * the current context cannot be defined using VM_CURRENT_GET() and therefore
 * the context to use must be passed to vmBufferWrite(). Nevertheless the
 * context ID passed to VM_CONTEXT_BUFFER_WRITE() must correspond to the
 * context in place.
 */

#define VM_CONTEXT_BUFFER_WRITE(context, fromAddr, toAddr, nbBytes) \
    ((vmLibInfo.pVmBufferWriteRtn == NULL) ? \
     (memcpy((void *)toAddr, (void *)fromAddr, nbBytes), OK) : \
     ((*vmLibInfo.pVmBufferWriteRtn) (context, (VIRT_ADDR) fromAddr, \
				      (VIRT_ADDR) toAddr, nbBytes)))

#define VM_CONTEXT_SWITCH(context) \
    ((vmLibInfo.pVmCtxSwitchRtn == NULL) ? \
    (OK) : \
    ((*vmLibInfo.pVmCtxSwitchRtn) (context)))

#define VM_CONTIG_BLOCK_EACH(context, startAddr, len, \
			     stateMask, eachRtn, eachArg) \
	    ((vmLibInfo.pVmContigBlockEachRtn == NULL) ? \
	     (ERROR) : \
	     ((*vmLibInfo.pVmContigBlockEachRtn) (context, startAddr, len,\
						  stateMask, eachRtn, eachArg)))

typedef struct vm_context
    {
    OBJ_CORE		objCore;	
    MMU_TRANS_TBL_ID	mmuTransTbl;   
    SEMAPHORE		sem;
    } VM_CONTEXT;

typedef struct
    {
    MMU_TRANS_TBL_ID (*mmuTransTblCreate) (void);
    STATUS (*mmuTransTblDelete)
	(
	MMU_TRANS_TBL_ID pTransTbl
	);
    STATUS (*mmuEnable)
	(
	BOOL enable
	);
    STATUS (*mmuStateSet)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	virtualAddr,
	size_t		numPages,
	MMU_ARCH_ATTR	stateMask,
	MMU_ARCH_ATTR	state,
	BOOL		optimize
	);
    STATUS (*mmuStateGet)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	effectiveAddr,
	MMU_ARCH_ATTR *	state
	);
    STATUS (*mmuPageMap)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	virtualAddr,
	PHYS_ADDR	physicalAddr,
	size_t		numPages,
	BOOL		optimize,
	MMU_ARCH_ATTR	attr
	);
    STATUS (*mmuGlobalPageMap)
	(
	VIRT_ADDR	virtualAddr,
	PHYS_ADDR	physicalAddr,
	size_t		numPages,
	BOOL		optimize,
	MMU_ARCH_ATTR	attr
	);
    STATUS (*mmuTranslate)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	inputAddr,
	PHYS_ADDR *	outputAddr
	);
    void (*mmuCurrentSet)
	(
	MMU_TRANS_TBL_ID pTransTbl
	);
    size_t (*mmuPageSizeGet) (void);
    STATUS (*mmuPhysTranslate)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	PHYS_ADDR	inputAddr,
	VIRT_ADDR *	outputAddr
	);
    STATUS (*mmuSplTranslate)
	(
	UINT            attr,
	UINT            attrMask,
	MMU_ARCH_ATTR * pToDep,
	MMU_ARCH_ATTR * pToDepMask
	);
    STATUS (*mmuSplArchTranslate)
	(
	MMU_ARCH_ATTR   depAttr,
	UINT *          pToIndep
	);
    STATUS (*mmuPageOptimize)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	virtAddr,
	size_t		numPages,
	UINT		option
	);
    STATUS (*mmuBufferWrite)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	fromAddr,
	VIRT_ADDR	toAddr,
	size_t		nbBytes
	);
    STATUS (*mmuPageLock)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	virtAddr,
	size_t		numPages,
	UINT		option
	);
    STATUS (*mmuPageUnlock)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	virtAddr,
	UINT		option
	);
    UINT (*mmuMaxPhysBitsGet) (void);
    STATUS (*mmuPageUnMap)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	virtAdr,
	size_t		numPages
	);
    size_t (*mmuBlockSizeGet) (void);
    STATUS (*mmuTransTblUnion)
	(
	MMU_TRANS_TBL_ID pTransTbl1,
	MMU_TRANS_TBL_ID pTransTbl2
	);
    STATUS (*mmuTransTblUnionInit)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	startAddr,
	size_t		length
	);
    STATUS (*mmuTransTblMask)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	startAddr,
	VIRT_ADDR	endAddr,
	UINT		options
	);
#ifdef _WRS_MMU_HAS_BLOCK_INFO_API
    STATUS (*mmuContigBlockInfoGet)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	startAddr,
	MMU_ARCH_ATTR	stateMask,
	PHYS_ADDR *	pPhysAddr,
	MMU_ARCH_ATTR *	pAttr,
	size_t *	pNumPages
	);
#endif /* _WRS_MMU_HAS_BLOCK_INFO_API */

    STATUS (*mmuPteSizeGet)
	(
	MMU_TRANS_TBL_ID pTransTbl,
	VIRT_ADDR	virtAddr,
	size_t *	pPteSize
	);

    STATUS (*mmuOptimizedSizeGet)
	(
	size_t		size,
	size_t *	pOptimSize
	);
    STATUS (*mmuDirectPageMap)
        (
         MMU_TRANS_TBL_ID pTransTbl,
         PHYS_ADDR regionBase,
         size_t regionSize
         );
    } MMU_LIB_FUNCS;

/* 
 * On architectures that either will not allow page based mmu support on the
 * entire virtual memory range, as in MIPS and SH, or where the virtual
 * address range must be shared with the host, as in the case of the
 * simulators, the address space allocator must know what ranges are
 * allocatable and in what privilege mode. 
 */

typedef enum virt_seg_type
    {
    VIRT_SEG_TYPE_NO_MAP	= 0x00000000,	/* mapping not possible */ 
    VIRT_SEG_TYPE_K_MAP		= 0x00000001,	/* kernel mode only */
    VIRT_SEG_TYPE_U_MAP		= 0x00000002,	/* user mode only */
    VIRT_SEG_TYPE_KU_MAP	= 0x00000004	/* kernel or user mode */
    } VIRT_SEG_TYPE;

typedef struct virt_seg_info
    {
    VIRT_ADDR 		start;
    size_t     		length;
    VIRT_SEG_TYPE	type;
    } VIRT_SEG_INFO;

typedef struct virt_extra_map_info
    {
    VIRT_ADDR 		virtAdr;
    size_t     		len;
    PHYS_ADDR		physAdr;
    } VIRT_EXTRA_MAP_INFO;

typedef struct vm_info
    {
    BOOL	noExecSupported;
    BOOL	optimSupported;
    size_t	mmuPageSize;
    UINT	ramDefaultAttr;
    UINT	cacheDefault;
    UINT	reserved1;
    } VM_INFO;

extern VM_LIB_INFO   vmLibInfo;
extern CLASS_ID      vmContextClassId;
extern VM_CONTEXT    sysVmContext;

extern MMU_LIB_FUNCS mmuLibFuncs;
extern BOOL          mmuDataNoExec;
extern int	     mmuPhysAddrShift;
extern size_t	     mmuArchCopySize;
extern int	     mmuPhysAddrShift;

extern MMU_ARCH_ATTR * mmuProtStateTransTbl;
extern MMU_ARCH_ATTR * mmuCacheStateTransTbl;
extern MMU_ARCH_ATTR * mmuValidStateTransTbl;
extern MMU_ARCH_ATTR * mmuMaskTransTbl;

/*
 * declaration of mmuInvalidState has been inconsistent for 32-bit 
 * MMU libraries. We enforce it at least for 64-bit here.
 */
#ifdef _WRS_CONFIG_LP64
extern MMU_ARCH_ATTR   mmuInvalidState;
#endif

extern void (*_func_taskMmuCurrentSet)(MMU_TRANS_TBL_ID pTransTbl);

/* function declarations */

extern VM_CONTEXT_ID 	vmGlobalMapInit (PHYS_MEM_DESC * pMemDescArray, 
			  		 int numDescArrayElements, BOOL enable,
					 UINT cacheDefault);
extern STATUS 		vmBaseLibInit (void);
extern STATUS		vmLibInit (void);
extern STATUS		vmCtxInit (VM_CONTEXT_ID pContext);
extern STATUS		vmCtxTerminate (VM_CONTEXT_ID context);
extern STATUS		vmCtxDestroy (VM_CONTEXT_ID context, BOOL dealloc);
extern STATUS		vmInfoGet (VM_INFO * pVmInfo);
extern STATUS		vmContigBlockEach (VM_CONTEXT_ID context,
					   VIRT_ADDR startAddr, size_t len,
					   UINT stateMask, 
					   STATUS (*eachRtn)
						       (
						       VIRT_ADDR virtAddr,
						       size_t    size,
						       PHYS_ADDR physAddr,
						       UINT      attr,
						       void *    pArg
						       ),
					   void * pEachArg);
extern size_t		vmPageBlockSizeGet (void);
extern VM_CONTEXT_ID	vmCurrentGet (void);
extern STATUS 		vmCurrentSet (VM_CONTEXT_ID context);
extern void 		vmShowInit (void);
extern char * 		vmAttrStringGet (UINT mmuAttr, UINT mmuAttrMask,
					 char * buffer);
extern void		vmContextHeaderPrint (void);
extern UINT             vmMaxPhysBitsGet (void); 
extern VM_CONTEXT_ID    vmCtxCreate (void);
extern STATUS           vmCtxDelete (VM_CONTEXT_ID context);
extern STATUS           vmCtxInit (VM_CONTEXT_ID context);
extern STATUS           vmCtxUnion (VM_CONTEXT_ID vmCtx1, VM_CONTEXT_ID vmCtx2);
extern STATUS           vmCtxUnionInit (VM_CONTEXT_ID vmCtx, \
                                        VIRT_ADDR startAddr, size_t length);
extern STATUS           vmCtxMask (VM_CONTEXT_ID vmCtx, VIRT_ADDR virtStartAdr,
                                   VIRT_ADDR virtEndAdr, UINT options);
extern STATUS           vmContextSwitch (VM_CONTEXT_ID  context);
extern STATUS           vmPgUnMap (VM_CONTEXT_ID vmCtx, VIRT_ADDR virtAdr,
                                   size_t numBytes);
extern STATUS           vmPgMap (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr,
				 PHYS_ADDR physicalAddr, size_t len, 
				 UINT stateMask, UINT state, UINT options);
extern VM_CONTEXT_ID	vmKernelContextIdGet(void);
extern STATUS		vmContextRangeShow (VM_CONTEXT_ID context, 
					    VIRT_ADDR startAddr, 
					    size_t len);

extern STATUS		vmAttrToArchConvert (UINT32 indepStateMask, 
					     UINT32 indepState,
					     MMU_ARCH_ATTR * pDepStateMask, 
					     MMU_ARCH_ATTR * pDepState);
extern STATUS		vmAttrToIndepConvert (MMU_ARCH_ATTR depState, 
					      UINT32 * pIndepState);
#ifndef _WRS_CONFIG_CERT
extern STATUS		vmPteSizeGet (VM_CONTEXT_ID vmCtx, VIRT_ADDR virtAddr,
				      size_t * pPteSize);
#endif
extern STATUS		vmOptimizedSizeGet (size_t size, size_t * pOptimSize);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvmLibPh */
