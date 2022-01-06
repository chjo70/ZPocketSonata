/* aimMmuLib.h - MMU library portion of the Architecture Independent Manager */

/*
 * Copyright 2003, 2004, 2006, 2007, 2010-2012, 2014-2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
24jun15,w_x  Remove some unnecessary VSB options according to HLD review (F2518)
26feb15,w_x  Support LP64 configurable virtual address bits to decode (F2518)
20nov14,h_k  LP64 adaptation to support PPC64.(F2518)
27apr15,pcs  In struct MMU_ARCH_LIB_FUNCS, replace function pointer 
             mmuAttrTranslate with mmuSplTranslate & mmusplArchTranslate.
14mar14,x_z  add MMU_ARCH_LIB_ATTRS. (US18830)
28feb12,h_k  made TLB sync config flexible to be able to share one binary
             with different CPU variants. (WIND00320752)
01feb11,slk  add mmuTlbPoolCreateHook hook for region and page table pool
             creation
21jul10,wiq  Remove useless typedef. (WIND00054776)
09jun10,d_c  Add mmuPostStateSetHook to MMU_ARCH_LIB_FUNCS.
29apr10,pad  Moved extern C statement after include statements.
14jan10,cwl  Remove the function aimMmuShowInit(). (WIND00184839)
29nov06,sru  Added complete prototypes and header comments for the
             function pointers that make up the AD-MMU interface.
29jan07,h_k  added an extra argument to MODIFYLOCALPTEFUNC.
29nov04,dtr  Add region tbl ptr to MMU_TRANS_TBL.
23nov04,dtr  Mod to API for 860 support.
29sep04,dtr  Add Show routines externs.
17sep04,sru  Added 'pWritable' parameter to LOCKIMPORTFUNC.
30aug04,dtr  Modify allocation buffer for static TLB entries.
06aug04,sru  Added support for importing locked regions at startup.
08jun04,sru  Moved attribute definitions to mmuAimBaseLib.h.
19may04,dtr  Add extra function for ISR callable state.
08apr04,dtr  Adding in new feature support aimMmuLock/Unlock/optimization.
04may04,sru  add support for query of TLB size
12nov03,jtp  Change mmuPteSet global parameter type to BOOL
07nov03,sru  change model for bufferwrite
04nov03,jtp  change API for fine-grain PTE get
30oct03,sru  add AD-MMU hook for TransTblGet
07apr03,sru  written
*/

#ifndef __INCaimMmuLibh
#define __INCaimMmuLibh

#include <vxWorks.h>
#ifndef	_ASMLANGUAGE
#include <aimMmuBaseLib.h>
#include <private/vmLibP.h>
#ifdef _WRS_ENABLE_TLB_POOL_CREATE_HOOK
#include <poolLib.h>
#endif /* _WRS_ENABLE_TLB_POOL_CREATE_HOOK */
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
extern "C" {
#endif

/* options for various AIM calls */

#define AIM_MMU_OPT_LOCK_NONE		0
#define AIM_MMU_OPT_LOCK_IMPORT		1

/* masks for page sizes */

#define MMU_PAGE_MASK_1K	  0x0000001
#define MMU_PAGE_MASK_2K	  0x0000002
#define MMU_PAGE_MASK_4K	  0x0000004
#define MMU_PAGE_MASK_8K	  0x0000008
#define MMU_PAGE_MASK_16K	  0x0000010
#define MMU_PAGE_MASK_32K	  0x0000020
#define MMU_PAGE_MASK_64K	  0x0000040
#define MMU_PAGE_MASK_128K	  0x0000080
#define MMU_PAGE_MASK_256K	  0x0000100
#define MMU_PAGE_MASK_512K	  0x0000200
#define MMU_PAGE_MASK_1M	  0x0000400
#define MMU_PAGE_MASK_2M	  0x0000800
#define MMU_PAGE_MASK_4M	  0x0001000
#define MMU_PAGE_MASK_8M	  0x0002000
#define MMU_PAGE_MASK_16M	  0x0004000
#define MMU_PAGE_MASK_32M	  0x0008000
#define MMU_PAGE_MASK_64M	  0x0010000
#define MMU_PAGE_MASK_128M	  0x0020000
#define MMU_PAGE_MASK_256M	  0x0040000
#define MMU_PAGE_MASK_512M	  0x0080000
#define MMU_PAGE_MASK_1G	  0x0100000

#define MMU_PAGE_SIZE_MIN	1024
#define MMU_PAGE_MASK_MIN	MMU_PAGE_MASK_1K
#define BIT_SHIFT_1K            10
#define MAX_BITS                31
#ifdef	_WRS_CONFIG_LP64
#define VIRT_ADDR_BITS_MAX	64
#define VIRT_ADDR_BITS_DEC	48 /* 48-64 */
#define VIRT_ADDR_MASK	0xFFFFFFFFFFFFFFFF
#else
#define VIRT_ADDR_BITS_MAX	32
#define VIRT_ADDR_BITS_DEC	32
#define VIRT_ADDR_MASK	0xFFFFFFFF
#endif	/* _WRS_CONFIG_LP64 */
#define PTE_ATTR_PHYS_ADDR	0x01
#define PTE_ATTR_PAGE_SIZE	0x02
#define PTE_ATTR_GLOBAL		0x04
#define PTE_ATTR_CONTEXT	0x08
#define PTE_ATTR_STATE		0x10
#define PTE_ATTR_VIRT_ADDR	0x20
#define PTE_ATTR_VALID		0x40	/* AIM-readable valid state */
#define PTE_ATTR_ISR_CALLABLE   0x80
#ifndef	_ASMLANGUAGE
typedef char MMU_PAGE_TBL;		/* placeholder */
typedef void *MMU_REGION_TBL;
typedef MMU_REGION_TBL *MMU_CONTEXT_TBL;
typedef int MMU_CONTEXT;

typedef struct mmuTransTblStruct
  {
  MMU_CONTEXT context;
  MMU_REGION_TBL *regionTblPtr;
  } MMU_TRANS_TBL;

/* PTE_ATTR - a structured used to read/write PTE attribute info. */

typedef struct mmu_pte_attr
  { 
  PHYS_ADDR physAddr;
  VIRT_ADDR virtAddr;
  size_t pageSize;
  BOOL global;
  UINT context;
  UINT state;
  BOOL valid;				/* AIM-readable valid state */
  BOOL isrCallable;
  } PTE_ATTR;


/* MMU_PTE_ATTR mask bits.  Used to control PTE set/get functions */


/* type of table mmuTlbPoolCreateHook should create */

#ifdef _WRS_ENABLE_TLB_POOL_CREATE_HOOK
typedef enum
    {
    PAGE_TABLE,
    REGION_TABLE
    } AIM_MMU_TBL_TYPE;
#endif /* _WRS_ENABLE_TLB_POOL_CREATE_HOOK */


typedef struct
    {
    VIRT_ADDR	virtAddr;
    size_t     	pageSize;
    BOOL	imported;
    } STATIC_ENTRY_REGION;

/*
 * MMU_ARCH_LIB_ATTRS is a data structure that is allocated by the AIM
 * base library.  It is filled in with MMU-specific attributes during
 * the initialization of the architecture-dependent MMU library.  From
 * that point forward, the data structure is used by the AIM for its
 * internal management.
 */

typedef struct
    {
    /* fields filled in by the AD-MMU */

    ULONG  pageSizeMask;
    ULONG  lockSizeMask;
    UINT contextMin;		/* inclusive */
    UINT contextMax;		/* inclusive */
    size_t pteSize;		/* units are bytes */
    size_t contextTblAlign;
    ULONG  regionTblNumEntries;
    ULONG  pageTblNumEntries;
    ULONG  tlbNumEntries;	/* sum of hardware TLB resources */
    ULONG  tlbLockNumEntries;   /* sum of hardware TLB resources available 
				   for locking */
    size_t sizeOfRegionTbl;
    size_t sizeOfPageTbl;
    size_t sizeOfContextTbl;

    /* fields filled in by the AIM during initialization */

    size_t pageSize;
    size_t blockSize;
    UINT regionShift;		/* rightward bitshift to create region idx */
    ULONG  regionMask;		/* post-shift mask of region idx */
    UINT pageShift;		/* rightward bitshift to create page idx */
    ULONG  pageMask;		/* post-shift mask of page idx */

    UINT regionBits;		/* count of number of set bits */
    } MMU_ARCH_LIB_ATTRS;

/*
 * MMU_ARCH_LIB_FUNCS is a data structure that is allocated by the AIM
 * library.  It is filled in with function pointers that are exported 
 * by the architecture-dependent MMU library.  The AIM uses these 
 * function pointers to implement its MMU services.
 */

typedef struct
    {
    /*
     * mmuTlbInvalidateAllDynamic - Required AD-MMU function.  Discard
     * all non-locked TLB entries from the TLB hardware.
     */
    
    void (*mmuTlbInvalidateAllDynamic) (void);  

    /*
     * mmuTlbInvalidate - Required AD-MMU function.  Discard
     * single TLB entry that maps the requested [context,vaddr] pair.
     */

    void (*mmuTlbInvalidate)
	(
	int context,		/* address space identifer for vaddr */
	VIRT_ADDR vaddr		/* virtual address to invalidate in TLB */
	);

    /*
     * kmemPtrToPageTablePtr - 	Optional AD-MMU function.  Used when
     * an architecture needs to perform a transformation on a pointer
     * allocated from the kernel heap before the pointer placed into
     * page tables.  MIPS uses this to translate KSEGM addresses to 
     * KSEG0 addresses so that accesses to the page tables are made
     * from non-mapped virtual addresses.
     */

    VIRT_ADDR (*kmemPtrToPageTablePtr)
	(
        VIRT_ADDR vaddr		/* kernel heap address to convert */
        );

    /*
     * pageTablePtrToKmemPtr - Optional AD-MMU function.  Used to
     * invert the transformation performed by kmemPtrToPageTablePtr.
     * If a kmemPtrToPageTablePtr function is provided by the AD-MMU,
     * this function must be provided as well.
     */

    VIRT_ADDR (*pageTablePtrToKmemPtr)
	(
        VIRT_ADDR vaddr		/* page table address to convert */
        );

    /*
     * mmuEnable - Required AD-MMU function.  Used to enable or disable
     * the memory management hardware for the CPU.
     */

    STATUS (*mmuEnable)
	(
	BOOL enable		/* TRUE = enable, FALSE = disable */
	);

    /*
     * mmuPteSet - Required AD-MMU function.  Used to completely replace
     * the contents of a PTE with the provided page attributes.
     */

    void (*mmuPteSet)
	(
	void * pPte,		/* pointer to MMU-dependent PTE */
	PHYS_ADDR physAddr,	/* new physical address */
	VIRT_ADDR virtAddr,	/* virtual address for PTE */
	UINT newState,		/* new MMU-dependent state */
	BOOL newGlobal,		/* new global state */
	size_t newPageSize,	/* new page size */
	void *pRte		/* pointer to MMU-dependent RTE */
	);

    /*
     * mmuPteInit - Required AD-MMU function.   Used to initialize a PTE
     * to a known state.  The default known state for a PTE is UNMAPPED.
     * which must be distinguishable from the VALID/INVALID state.
     */

    void (*mmuPteInit)
	(
	void * pPte		/* pointer to MMU-dependent PTE */
	);

    /*
     * mmuPteStateGet - Required AD-MMU function.  This is used to determine
     * the architecture-dependent state information for the requested PTE.
     * Both the pointer to the PTE and the pointer to the RTE are provided,
     * so architectures that store ancilliacy information in the RTE can
     * access it.
     */

    UINT (*mmuPteStateGet)
	(
	void * pPte,		/* pointer to MMU-dependent PTE */
	void * pRte		/* pointer to MMU-dependent RTE */
	);
    
    /*
     * mmuPteValidGet - Required AD-MMU function.  Returns TRUE or FALSE
     * depending on whether or not the referenced PTE is in the VALID or
     * INVALID state.
     */

    BOOL (*mmuPteValidGet)
	(
	void * pPte		/* pointer to MMU-dependent PTE */
	);

    /*
     * mmuPteGlobalGet - Required AD-MMU function.  Returns TRUE or FALSE
     * depending on whether or not the referenced PTE refers to a global 
     * or non-global page.
     */

    BOOL (*mmuPteGlobalGet)
	(
	void * pPte		/* pointer to MMU-dependent PTE */
	);

    /*
     * mmuPtePageSizeGet - Required AD-MMU function.  Returns the size in
     * bytes of the address space spanned by the PTE.  For most PTEs, the
     * value returned by this function will be equal to the default page
     * size for the architecture.  For pages that are part of an optimized
     * region, the size can be substantially larger.
     */

    size_t (*mmuPtePageSizeGet)
	(
	void * pPte		/* pointer to MMU-dependent PTE */
	);

    /*
     * mmuPtePhysAddrGet - Required AD-MMU function.  Returns the physical
     * address that is mapped by the PTE.
     */

    PHYS_ADDR (*mmuPtePhysAddrGet)
	(
	void * pPte		/* pointer to MMU-dependent PTE */
	);

    /*
     * mmuStateValidGet - Required AD-MMU function.  Returns the validity
     * of the PTE.  Note that PTE's can transition between the valid and
     * invalid state without losing any other page properties, such as
     * caching mode or physical address.  The "valid" state is distinct
     * from "unmapped".  These two states must be distinguishable at the
     * AD-MMU level.
     */

    BOOL (*mmuStateValidGet)
	(
	UINT pteState		/* state retrieved from PTE */
	);

    /*
     * mmuStateCacheModeGet - Required AD-MMU function.  Returns the
     * architecture-dependent cache mode contained within the PTE.
     */

    UINT (*mmuStateCacheModeGet)
	(
	UINT pteState		/* state retrieved from PTE */
	);

    /*
     * mmuStateWriteEnabledGet - Required AD-MMU function.  Returns the
     * write-enabled state of the PTE.  This query is used to determine
     * whether or not the page is writable from supervisor state.
     */

    BOOL (*mmuStateWriteEnabledGet)
	(
	UINT pteState		/* state retrieved from PTE */
	);

    /*
     * mmuCurrentSet - Required AD-MMU function.  Performs whatever
     * architecture-dependent operations are required so that the 
     * requested context becomes the current address map.  This
     * may involve touching CPU-specific registers (e.g., ASID registers
     * on MIPS), or may involve changes to global variables that are used
     * by TLB miss handlers to find the top of the current translation
     * tables.
     */

    void (*mmuCurrentSet)
	(
	MMU_CONTEXT_TBL * pContext, /* pointer to array of contexts */
	int context		    /* which context to use */
	);

    /*
     * mmuCurrentGet - Deprecated function.
     */

    UINT (*mmuCurrentGet) (void);

    /*
     * mmuPageWrite - Required AD-MMU function.  Used to copy data to 
     * (possibly) write-protected destination pages.  The data referenced 
     * by 'numBytes' is guaranteed to be contained completely within the 
     * pages referenced by the 'src' and 'dst' PTEs.  The AD-MMU can
     * choose to implement this by making modifications to the PTES, or 
     * it may also choose to bypass the MMU entirely if this capability
     * is provided by the architecture.
     */

    void (*mmuPageWrite) 
	(
	int context,		/* context in which to do the operation */
	void * pPteSrc,		/* PTE for source page */
	VIRT_ADDR virtAddrSrc,	/* source address for copy */
	void * pPteDst,		/* PTE for destination page */
	VIRT_ADDR virtAddrDst,	/* destination address for copy */
	size_t numBytes		/* number of bytes of data to copy */
	);

    /*
     * mmuSplTranslate - Optional AD-MMU function.  If provided by the
     * AD-MMU, this function is used to translate state information
       from architecture-independent to architecture-dependent.
     */

    STATUS (*mmuSplTranslate)
        (
        UINT            attr,
        UINT            attrMask,
        MMU_ARCH_ATTR * pToDep,
        MMU_ARCH_ATTR * pToDepMask
        );

    /*
     * mmuSplArchTranslate - Optional AD-MMU function.  If provided by the
     * AD-MMU, this function is used to translate state information
       from architecture-dependent to architecture-independent.
     */

    STATUS (*mmuSplArchTranslate)
        (
        MMU_ARCH_ATTR   depAttr,
        UINT *          pToIndep
        );

#ifndef	_WRS_CONFIG_LP64
    /*
     * mmuTransTblGet - (being deprecated)
     */

    UINT * (*mmuTransTblGet)
	(
	MMU_CONTEXT_TBL * pContext,	/* pointer to array of contexts */
	int context			/* which context to use */
	);
#endif	/* !_WRS_CONFIG_LP64 */

    /*
     * mmuLockPteUpdate - Optional AD-MMU function.  This function is
     * required only if the AD-MMU supports page size optimization
     * and the architecture needs to lock a page while modifying the page
     * size.
     */

    STATUS (*mmuLockPteUpdate)
	(
	MMU_CONTEXT context, 		/* which context to use */
	void * pPte,			/* pointer to MMU-dependent PTE */
	VIRT_ADDR virtAddr,		/* virtual address for PTE */
	size_t size,			/* of address range in bytes */
	BOOL lock			/* lock or unlock  */
	);
	
    /*
     * mmuLock - Optional AD-MMU function.  This function is required 
     * only if the AD-MMU supports page locking.
     */

    STATUS (*mmuLock)
	(
	void * pPte,		/* pointer to MMU-dependent PTE */
	VIRT_ADDR,
	size_t
	);

    /*
     * mmuUnlock - Optional AD-MMU function.  This function is
     * reuired only if the AD-MMU supports page locking.
     */

    STATUS (*mmuUnlock)
	(
	VIRT_ADDR
	);

    /*
     * mmuPteLockGet - Optional AD-MMU function.  This function is
     * required only if the AD-MMU supports page locking.  This function
     * returns true if the PTE is locked into the hardware TLB resources 
     * of the CPU, and FALSE otherwise.
     */

    BOOL (*mmuPteLockGet)
	(
	void * pPte		/* pointer to MMU-dependent PTE */
	);

    /*
     * mmuPteSetLockState - Optional AD-MMU function.  This function is
     * required only if the AD-MMU supports page locking.  This function
     * sets an array of PTEs locked or unlocked accordingly.
     */

    STATUS (*mmuPteSetLockState)
	(
	void * pPte,		/* pointer to MMU-dependent PTE */
	UINT,
	BOOL,
	BOOL
	);

    /*
     * mmuPteSetForDynamic - Optional AD-MMU function.  This function is
     * required only if the AD-MMU supports page size optimization.
     * This function sets the optimized page size or resets to the
     * default page size.
     */

    STATUS (*mmuPteSetForDynamic)
	(
	void * pPte,		/* pointer to MMU-dependent PTE */
	void * pLocalPte,
	UINT,
	PHYS_ADDR,
	BOOL,
	BOOL,
	VIRT_ADDR
	);
    
    /*
     * mmuPteMaxPhysBitsGet - Required AD-MMU function unless the number
     * of address bits in a physical address is 32 bits.
     * This function returns the number of address bits in a physical
     * address.  This should a value between 32 an 64, depending on
     * the number of significant physical address bits supported by the MMU.
     */

    UINT (*mmuPteMaxPhysBitsGet) (void);
    
    /*
     * mmuPteIsrCallableGet - Optional AD-MMU function.  This function
     * returns TRUE if the PTE can be modified from within interrupt
     * context, and FALSE otherwise.
     */

    BOOL (*mmuPteIsrCallableGet)
	(
	void * pPte
	);

    /*
     * mmuLockImport - Optional AD-MMU function.  Architectures that 
     * set up locked TLB entries as part of system initialization must
     * provide this function.  During initialization, the MMU AIM calls
     * this function with increasing index numbers (0, 1, 2...) to 
     * retrieve the set of address ranges that the architecture has
     * locked.  The AD-MMU returns OK if it has a valid locked region
     * for the index, and ERROR otherwise.  For each valid region, the
     * AD-MMU returns the virtual address, size, and writeability of
     * the memory region that is locked.
     */

    STATUS (*mmuLockImport)
	(
	int index,
	VIRT_ADDR * pVirtAddr,
	size_t * pSize,
	BOOL * pWritable
	);
    
    /*
     * mmuPostStateSetHook - Optional AD-MMU function. If set to
     * non-NULL, this function is called at the end of
     * aimMmuStateSet(), after all pages in the subject block have
     * been set to the new state, and the MMU has been invalidated for
     * those pages.
     */
    
#ifdef _WRS_ENABLE_MMU_POST_STATE_SET_HOOK    
    STATUS (*mmuPostStateSetHook)
        (
        MMU_TRANS_TBL *pTransTbl, /* MMU Translation table pointer */
        VIRT_ADDR virtAddr,       /* Virtual address of memory block */
        PHYS_ADDR physAddr,       /* Physical address */	
        size_t numPages,            /* Number of pages in memory block */
        size_t pageSize,          /* Page size in memory block */
        UINT stateMask,           /* State mask */
        UINT state,               /* New arch-dependent state for block */
        UINT affectedStateBits,   /* Mask indicating modified state bits */
        BOOL optimize             /* Optimization flag */
      );
#endif /* _WRS_ENABLE_MMU_POST_STATE_SET_HOOK */
    
    /*
     * mmuTlbPoolCreateHook - Optional AD-MMU function.  Architectures
     * can use this hook to supply their version of poolCreate for
     * the MMU region and page tables.  This allows the use of special
     * memory regions for the tables among other options.  This hook is
     * used as part of the aimMmuLibInit operation.
     */

#ifdef _WRS_ENABLE_TLB_POOL_CREATE_HOOK
    POOL_ID (*mmuTlbPoolCreateHook)
        (
        const char *  pName,     /* optional name to assign to pool */
        size_t        itmSize,   /* size in bytes of a pool item */
        size_t        alignment, /* alignment of a pool item */
                                 /* (must be power of 2, or 0) */
        ULONG        initCnt,    /* initial number of items to put in pool */
        ULONG        incrCnt,    /* min # of items to add to pool */
                                 /* (if 0, no pool expansion is done) */
        PART_ID      partId,     /* memory partition ID */
        ULONG        options,    /* initial options for pool */
        AIM_MMU_TBL_TYPE tblType /* pool table type (region or page)  */
        );
#endif /* _WRS_ENABLE_TLB_POOL_CREATE_HOOK */

#if defined(_WRS_CONFIG_SMP)
    /*
     * mmuTlbInvalidateAllDynamicSMP - Optional AD-MMU function in SMP.
     * Discard all non-locked TLB entries from the TLB hardware.
     */
    
    void (*mmuTlbInvalidateAllDynamicSMP) (void);  

    /*
     * mmuTlbInvalidateSMP - Optional AD-MMU function in SMP.  Discard
     * single TLB entry that maps the requested [context,vaddr] pair.
     */

    void (*mmuTlbInvalidateSMP)
	(
	int context,		/* address space identifer for vaddr */
	VIRT_ADDR vaddr		/* virtual address to invalidate in TLB */
	);
#endif	/* _WRS_CONFIG_SMP */

    } MMU_ARCH_LIB_FUNCS;

extern STATUS		aimMmuLibInit (void);
extern void		aimMmuMapShow (UINT);
extern void		aimMmuOptimizeMemShow (int);
extern STATUS aimMmuBaseLibInit (void);
extern MMU_ARCH_LIB_ATTRS mmuArchLibAttrs;
#endif	/* !_ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCaimMmuLibh */

