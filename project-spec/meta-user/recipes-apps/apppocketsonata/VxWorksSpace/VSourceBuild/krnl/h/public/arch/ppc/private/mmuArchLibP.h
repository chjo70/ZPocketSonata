/* mmuArchLibP.h - Architecture dependent MMU library header */

/*
 * Copyright (c) 2011, 2016, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20apr17,syt  implemented mmuCacheSync().(V7PRO-3480)
12sep16,h_k  fixed MMU protection disable and enable. (V7PRO-3268)
             shrank MMU page table to half in LP64.
23jul15,w_x  Update mmuL2/3/4EntrySet() to also increase word3 (V7PRO-2739)
23jul15,w_x  Update mmuL2/3/4EntryGet() to remove valid attribute check (F2518)
21jul15,w_x  Update mmuE500DirectPageMap() with MMU_LIB_FUNCS semantics (F2518)
16jul15,w_x  Merge Core OS MMU changes, set mmuLibFuncs.mmuDirectPageMap
             for LP64 (F2518)
07jul15,w_x  Update TLB miss handling with regard to SMP/SMT (F2518) 
03jul15,syt  checked VALID bit in functions mmuL2EntryGet, mmuL3EntryGet
             and mmuL4EntryGet (F2518)
01jul15,xms  fixed compiler warning. (F2518)
30jun15,p_x  handle global variable mmuPpcHasBeenEnabled. (V7RAD-175)
24jun15,w_x  prevent access to non-canonical address (F2518)
19jun15,w_x  remove mmuPpcDirectPageMap() (now in mmuE500Tlb.c) (F2518)
21may15,syt  updated function mmuPpcDirectPageMap. (F2518)
20mar15,ylu  undefined _WRS_MMU_FOUR_LEVEL_PT for PPC32. (F2518)
20mar15,ylu  updated for PPC32 (F2518)
16mar15,w_x  Integrated to VxWorks 7 with update for PPC64 (F2518)
28jan04,zl   created
*/

#ifndef __INCmmuArchLibPh
#define __INCmmuArchLibPh

#include <vxWorks.h>
#include <string.h>
#include <arch/ppc/mmuE500Lib.h>
#include <intLib.h>
#include <cacheLib.h>
#include <arch/ppc/mmuArchVars.h>           /* mmuPpcIEnabled, mmuPpcDEnabled */
#include <private/excLibP.h>                /* excExtendedVectors */
#include <private/adrSpaceLibP.h>           /* NON_CANONICAL_RGN_BASE/SIZE */
#include <arch/ppc/excPpcLib.h>             /* _EXC_OFF_DATA_MISS */
#include <arch/ppc/private/excArchLibP.h>   /* vectorPtr, vectorBase */
#include <sysLib.h>                         /* sysExcMsg */
#include <private/kwriteLibP.h>             /* _func_kprintf */

#ifdef __cplusplus
extern "C" {
#endif

#define _WRS_MMU_HAS_STATIC_MAP_INFO
#define _WRS_MMU_HAS_ASID
#define _WRS_MMU_SW_TLB_COHERENCY
#undef  _WRS_MMU_USES_OS_IMPL_ATTR
#undef  _WRS_MMU_SUPPORTS_PAGE_LOCK
#undef  _MMU_HAS_CANONICAL_ADDRESS_SPACE
#undef  _WRS_MMU_CACHE_PT_BASE        /* xxx - needs windALib support */
#undef  _WRS_MMU_EXTRA_SPL_TRANSLATE
#undef  _WRS_MMU_HAS_VIRT_SEG_INFO

#define _MMU_SUPPORTS_MAS6_ISIZE

#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined (PPC_e6500)
#undef  _MMU_SUPPORTS_MAS6_ISIZE
#endif /* PPC_e500v2 || PPC_e500mc || PPC_e6500 */

#define _MMU_MAX_PHYS_BITS              MMUE500_NO_BITS_PHYS_ADDR
#define _MMU_ATTR_INVALID               0xffffffff
#define _MMU_INIT_ATTR                  MMU_STATE_CACHEABLE_NOT
#define _MMU_STATIC_MAP_ENTRY_COUNT     16
#define _MMU_PAGE_SIZE                  MMU_PAGE_SIZE

/*
 * Protection attribute definitions used by mmuAttrProtTransArrayLocal
 */

#define _MMU_PROT_R______   MMU_STATE_SUP_R             /*  0: R-- --- */
#define _MMU_PROT_RW_____   MMU_STATE_SUP_RW            /*  1: RW- --- */
#define _MMU_PROT_R_X____   MMU_STATE_SUP_RX            /*  2: R-X --- */
#define _MMU_PROT_RWX____   MMU_STATE_SUP_RWX           /*  3: RWX --- */
#define _MMU_PROT_R___R__   MMU_STATE_SUP_R_USR_R       /*  4: R-- R-- */
#define _MMU_PROT_RW__R__   MMU_STATE_SUP_RW_USR_R      /*  5: RW- R-- */
#define _MMU_PROT_R_X_R__   MMU_STATE_SUP_RX_USR_R      /*  6: R-X R-- */
#define _MMU_PROT_RWX_R__   MMU_STATE_SUP_RWX_USR_R     /*  7: RWX R-- */
#define _MMU_PROT_R____W_   _MMU_ATTR_INVALID           /*  8: R-- -W- */
#define _MMU_PROT_RW___W_   _MMU_ATTR_INVALID           /*  9: RW- -W- */
#define _MMU_PROT_R_X__W_   _MMU_ATTR_INVALID           /* 10: R-X -W- */
#define _MMU_PROT_RWX__W_   _MMU_ATTR_INVALID           /* 11: RWX -W- */
#define _MMU_PROT_R___RW_   _MMU_ATTR_INVALID           /* 12: R-- RW- */
#define _MMU_PROT_RW__RW_   MMU_STATE_SUP_RW_USR_RW     /* 13: RW- RW- */
#define _MMU_PROT_R_X_RW_   _MMU_ATTR_INVALID           /* 14: R-X RW- */
#define _MMU_PROT_RWX_RW_   MMU_STATE_SUP_RWX_USR_RW    /* 15: RWX RW- */
#define _MMU_PROT_R_____X   _MMU_ATTR_INVALID           /* 16: R-- --X */
#define _MMU_PROT_RW____X   _MMU_ATTR_INVALID           /* 17: RW- --X */
#define _MMU_PROT_R_X___X   _MMU_ATTR_INVALID           /* 18: R-X --X */
#define _MMU_PROT_RWX___X   _MMU_ATTR_INVALID           /* 19: RWX --X */
#define _MMU_PROT_R___R_X   _MMU_ATTR_INVALID           /* 20: R-- R-X */
#define _MMU_PROT_RW__R_X   _MMU_ATTR_INVALID           /* 21: RW- R-X */
#define _MMU_PROT_R_X_R_X   MMU_STATE_SUP_RX_USR_RX     /* 22: R-X R-X */
#define _MMU_PROT_RWX_R_X   MMU_STATE_SUP_RWX_USR_RX    /* 23: RWX R-X */
#define _MMU_PROT_R____WX   _MMU_ATTR_INVALID           /* 24: R-- -WX */
#define _MMU_PROT_RW___WX   _MMU_ATTR_INVALID           /* 25: RW- -WX */
#define _MMU_PROT_R_X__WX   _MMU_ATTR_INVALID           /* 26: R-X -WX */
#define _MMU_PROT_RWX__WX   _MMU_ATTR_INVALID           /* 27: RWX -WX */
#define _MMU_PROT_R___RWX   _MMU_ATTR_INVALID           /* 28: R-- RWX */
#define _MMU_PROT_RW__RWX   _MMU_ATTR_INVALID           /* 29: RW- RWX */
#define _MMU_PROT_R_X_RWX   _MMU_ATTR_INVALID           /* 30: R-X RWX */
#define _MMU_PROT_RWX_RWX   MMU_STATE_SUP_RWX_USR_RWX   /* 31: RWX RWX */

/*
 * Cache attribute definitions used by mmuAttrCacheTransArrayLocal[]
 */

#define _MMU_CACHE_INV___       _MMU_ATTR_INVALID                   /*  0: Invalid */
#define _MMU_CACHE_OFF___       MMU_STATE_CACHEABLE_NOT             /*  1: Off */
#define _MMU_CACHE_CPB___       MMU_STATE_CACHEABLE_COPYBACK        /*  2: CB */
#define _MMU_CACHE_WRT___       MMU_STATE_CACHEABLE_WRITETHROUGH    /*  3: WT */
#define _MMU_CACHE_INV_C_       _MMU_ATTR_INVALID                   /*  4: Inv + C */
#define _MMU_CACHE_OFF_C_       (MMU_STATE_MEM_COHERENCY | \
                                 MMU_STATE_CACHEABLE_NOT)           /*  5: Off + C */
#define _MMU_CACHE_CPB_C_       (MMU_STATE_MEM_COHERENCY | \
                                 MMU_STATE_CACHEABLE_COPYBACK)      /*  6: CB + C */
#define _MMU_CACHE_WRT_C_       (MMU_STATE_MEM_COHERENCY | \
                                 MMU_STATE_CACHEABLE_WRITETHROUGH)  /*  7: WT + C */
#define _MMU_CACHE_INV__G       _MMU_ATTR_INVALID                   /*  8: Inv + G */
#define _MMU_CACHE_OFF__G       (MMU_STATE_GUARDED       | \
                                 MMU_STATE_CACHEABLE_NOT)           /*  9: Off + G */
#define _MMU_CACHE_CPB__G       (MMU_STATE_GUARDED       | \
                                 MMU_STATE_CACHEABLE_COPYBACK)      /* 10: CB + G */
#define _MMU_CACHE_WRT__G       (MMU_STATE_GUARDED       | \
                                 MMU_STATE_CACHEABLE_WRITETHROUGH)  /* 11: WT + G */
#define _MMU_CACHE_INV_CG       _MMU_ATTR_INVALID                   /* 12: Inv + C + G */
#define _MMU_CACHE_OFF_CG       (MMU_STATE_GUARDED       | \
                                 MMU_STATE_MEM_COHERENCY | \
                                 MMU_STATE_CACHEABLE_NOT)           /* 13: Off + C + G */
#define _MMU_CACHE_CPB_CG       (MMU_STATE_GUARDED       | \
                                 MMU_STATE_MEM_COHERENCY | \
                                 MMU_STATE_CACHEABLE_COPYBACK)      /* 14: CB + C + G */
#define _MMU_CACHE_WRT_CG       (MMU_STATE_GUARDED       | \
                                 MMU_STATE_MEM_COHERENCY | \
                                 MMU_STATE_CACHEABLE_WRITETHROUGH)  /* 15: WT + C + G */
#define _MMU_CACHE_DEF___       _MMU_ATTR_INVALID                                                                 /* 16: Default */

/* Valid-bit definitions used by mmuAttrValidTransArrayLocal[] */

#define _MMU_VALID_NOT          MMU_STATE_VALID_NOT
#define _MMU_VALID              MMU_STATE_VALID


/* Special attribute definitions used by mmuAttrSplTransArrayLocal[] */

#define _MMU_SPL_NO_BLOCK       (0x40 << MMU_PTE_W2_SHIFT)  /* U3 in PTE word 2 */
#define _MMU_SPL_GLOBAL         (0x80 << MMU_PTE_W2_SHIFT)  /* U2 in PTE word 2 */
#define _MMU_SPL_ENDIAN         0x01                        /* E in PTE word 1  */

#define _MMU_SPL_0              _MMU_SPL_ENDIAN
#define _MMU_SPL_1              _MMU_ATTR_INVALID
#define _MMU_SPL_2              _MMU_ATTR_INVALID
#define _MMU_SPL_3              _MMU_ATTR_INVALID
#define _MMU_SPL_4              _MMU_ATTR_INVALID
#define _MMU_SPL_5              _MMU_ATTR_INVALID
#define _MMU_SPL_6              _MMU_ATTR_INVALID        /* xxx - _MMU_SPL_GLOBAL requires redef of MMU_ATTR_NOT_GLOBAL */
#define _MMU_SPL_7              _MMU_SPL_NO_BLOCK

/* xxx - see _MMU_SPL_6
#define _MMU_MASK_SPL        (_MMU_SPL_NO_BLOCK    |        \
                 _MMU_SPL_GLOBAL    |        \
                 _MMU_SPL_ENDIAN)
*/
#define _MMU_MASK_SPL           (_MMU_SPL_NO_BLOCK | _MMU_SPL_ENDIAN)

/* Attribute mask definitions used by mmuAttrMaskTransArrayLocal[] */

#define _MMU_MASK_P__           (MMU_STATE_MASK_PROTECTION)
#define _MMU_MASK__V_           (MMU_STATE_MASK_VALID)
#define _MMU_MASK___C           (MMU_STATE_MASK_CACHEABLE      | \
                                 MMU_STATE_MASK_MEM_COHERENCY  | \
                                 MMU_STATE_MASK_GUARDED)
#define _MMU_MASK_PV_           (_MMU_MASK_P__ | _MMU_MASK__V_)
#define _MMU_MASK_P_C           (_MMU_MASK_P__ | _MMU_MASK___C)
#define _MMU_MASK__VC           (_MMU_MASK__V_ | _MMU_MASK___C)
#define _MMU_MASK_PVC           (_MMU_MASK_P__ | _MMU_MASK__V_ | _MMU_MASK___C)

/* PTE access macros */

#define MMU_PTE_W1_MASK         (MMU_STATE_MASK_WIMG | _MMU_SPL_ENDIAN)
#define MMU_PTE_W1_TID_SHIFT    16
#define MMU_PTE_W2_MASK         (MMU_STATE_MASK_PROTECTION | \
                                 _MMU_SPL_NO_BLOCK         | \
                                 _MMU_SPL_GLOBAL)
#define MMU_PTE_W2_SHIFT         MMU_STATE_PROTECTION_BIT_SHIFT
#define _MMU_TBL_ATTR_MASK       _MMU_MASK_P__
#define _MMU_TBL_ATTR            MMU_STATE_SUP_R

#define _MMU_ASID_COUNT                 256
#define _MMU_ASID_ERROR                 _MMU_ASID_COUNT
#define _MMU_ASID_KERNEL                1
#define _MMU_ASID_GLOBAL                0

#define _MMU_CTX_KERNEL                 _MMU_ASID_KERNEL
#define _MMU_CTX_GLOBAL                 _MMU_ASID_GLOBAL

#define _MMU_LOOP_WITH_PROTECTION_DISABLE(entry, count, sizeofEntry, body)     \
    {                                                                          \
    VIRT_ADDR   firstPage;                                                     \
    VIRT_ADDR   lastPage;                                                      \
    VIRT_ADDR   currentPage;                                                   \
    long        nPage;                                                         \
    long        start;                                                         \
    long        ix;                                                            \
    long        iy;                                                            \
    MMU_CTX_ID  pid;                                                           \
    int         key;                                                           \
                                                                               \
    firstPage = (VIRT_ADDR) ROUND_DOWN (entry, MMU_PAGE_SIZE);                 \
    lastPage  = (VIRT_ADDR) ROUND_DOWN (&entry [count - 1], MMU_PAGE_SIZE);    \
                                                                               \
    nPage = (long) (lastPage - firstPage) / MMU_PAGE_SIZE + 1;                 \
    start = ((long) entry & (MMU_PAGE_SIZE - 1)) / sizeofEntry;                \
                                                                               \
    pid = mmuPpcPidGet();                                                      \
    ix = 0;                                                                    \
                                                                               \
    key = INT_CPU_LOCK ();                                                     \
                                                                               \
    for (iy = 0; iy < nPage; iy++)                                             \
        {                                                                      \
        currentPage = firstPage + iy * MMU_PAGE_SIZE;                          \
                                                                               \
        mmuE500ProtectionOverride (currentPage, 0x5);   /* TLB w3, SUP R/W */  \
        mmuE500TlbInvalidateEntry (currentPage, 0, _MMU_CTX_GLOBAL);           \
        mmuE500TlbInvalidateEntry (currentPage, 0, pid);                       \
                                                                               \
        for (; ((ix + start) < ((MMU_PAGE_SIZE / sizeofEntry) * (iy + 1)))     \
               && (ix < count); ix++)                                          \
            {                                                                  \
            body;                                                              \
            }                                                                  \
                                                                               \
        mmuE500ProtectionOverride ((VIRT_ADDR) -1, 0x0);                       \
        mmuE500TlbInvalidateEntry (currentPage, 0, _MMU_CTX_GLOBAL);           \
        mmuE500TlbInvalidateEntry (currentPage, 0, pid);                       \
        }                                                                      \
                                                                               \
    INT_CPU_UNLOCK (key);                                                      \
    }

/* type defines */

#ifdef _WRS_MMU_FOUR_LEVEL_PT
typedef struct {
    UINT32 w[4];
}                               MMU_L4_ENTRY;       /* MMU level 4 entry */

typedef union {
    struct
	{
	UINT32 w[4];
	} w32;
    struct
	{
	UINT32 w[2];
	MMU_L4_ENTRY * l4Entry;
	} tbl;
}                               MMU_L3_ENTRY;       /* MMU level 3 entry */
#endif /* _WRS_MMU_FOUR_LEVEL_PT */

typedef union {
    struct
	{
	UINT32 w[4];
	} w32;
#ifdef	_WRS_MMU_FOUR_LEVEL_PT
    struct
	{
	UINT32 w[2];
	MMU_L3_ENTRY * l3Entry;
	} tbl;
#endif	/* _WRS_MMU_FOUR_LEVEL_PT */
}                               MMU_L2_ENTRY;       /* MMU level 2 entry */

typedef VIRT_ADDR               MMU_L1_ENTRY;       /* MMU level 1 entry */

typedef unsigned int            MMU_ASID;
typedef MMU_ASID                MMU_CTX_ID;
typedef unsigned long           MMU_CTX_TBASE;


/* imports */

IMPORT  MMU_CTX_TBASE           mmuE500ContextTbl[_MMU_ASID_COUNT];
IMPORT  codeBase                excVecBaseAltAdrs;
IMPORT  UINT32	                mmuPpcHasBeenEnabled;    /* for excEnt */

#ifdef _WRS_CONFIG_SMP
IMPORT  UINT32                  mmuTlb1EnteyIndex[VX_MAX_SMP_CPUS];
#else
IMPORT  UINT32                  mmuTlb1EnteyIndex;
#endif /* _WRS_CONFIG_SMP */

#ifdef	_WRS_CONFIG_SMP
IMPORT PPC_TLB_SAVE mmuPpcTlbSaveArea [];
#else
IMPORT PPC_TLB_SAVE mmuPpcTlbSaveArea;
#endif	/* _WRS_CONFIG_SMP */

IMPORT MMU_ASID mmuAsidAlloc (void);
IMPORT STATUS   mmuAsidFree (MMU_ASID);
IMPORT  void    mmuE500DataTlbMissHandler(); 
IMPORT  void    mmuE500InstTlbMissHandler(); 
IMPORT  INSTR   ppcBrCompute (VOIDFUNCPTR, INSTR *, int);
IMPORT  void    mmuE500TlbDynamicInvalidate (void);
IMPORT  void    mmuE500TlbStaticInvalidate (void);
IMPORT  void    mmuPpcPidSet (UINT8);
IMPORT  UINT32  mmuPpcPidGet (void);
IMPORT  void    mmuE500TlbInvalidateEntryAll (MMU_CTX_ID);
IMPORT  void    mmuE500TlbInvalidateEntry (VIRT_ADDR, UINT32, MMU_CTX_ID);
IMPORT  void    mmuE500ProtectionOverride (VIRT_ADDR, UINT32);
IMPORT  void    mmuPpcAEnable (UINT);
IMPORT  void    mmuPpcADisable (UINT);
IMPORT  STATUS  cacheArchEnable (CACHE_TYPE);
IMPORT  void    cacheAimE500DisableIFromMmu (void);
IMPORT  void    cacheAimE500DisableDFromMmu (void);
_WRS_INLINE STATUS mmuStaticMapInfoAdd (VIRT_ADDR virtAddr, size_t length,                                        
                                        PHYS_ADDR physAddr, MMU_ARCH_ATTR attr);
#ifdef _WRS_CONFIG_LP64
IMPORT  STATUS mmuE500DirectPageMap
            	(
                MMU_TRANS_TBL_ID    pTransTbl,
                PHYS_ADDR           physAddr,
                size_t              physSize
            	);
#endif /* _WRS_CONFIG_LP64 */

/*******************************************************************************
*
* mmuArchLibInit - MMU library initialization
*
* This routine initializes data structures used to store E500 mmu page tables
* so that subsequent page mapping operations can be performed, and so that
* the TLB miss handler exceptions can consult the data structures with
* meaningful results.
*
* RETURNS: OK or ERROR.
*/

_WRS_INLINE STATUS mmuArchLibInit (void)
    {
    vectorPtr   mmuVector;
    INSTR *     mmuVectorCode;
    INSTR       mmuHandlerBranch;
    vectorBase  excVecBase = (vectorBase) excVecBaseGet ();
    static char dataMissMsg[]="E500 MMU config failed: DTLB miss handler\n"
                              "is too far from the vector table\n";
    static char instMissMsg[]="E500 MMU config failed: ITLB miss handler\n"
                              "is too far from the vector table\n";
    void * func;

    /* initialize mmuProtect */

#ifdef	_WRS_CONFIG_SMP
    int    i;

    for (i = 0; i < VX_MAX_SMP_CPUS; i++)
	{
	mmuPpcTlbSaveArea[i].protVirtAddr = (VIRT_ADDR) -1;
	}
#else
    mmuPpcTlbSaveArea.protVirtAddr = (VIRT_ADDR) -1;
#endif	/* _WRS_CONFIG_SMP */

    /* global context ID is never to be used for translation table ID */

    mmuE500ContextTbl[_MMU_CTX_GLOBAL] = (ULONG)NULL;

    /* Address of vector, in vector execution space */

    mmuVector = (vectorPtr)(excVecBase + (vecTblOffset)_EXC_OFF_INST_MISS);

    /* Address of vector, in normal code space */

    mmuVectorCode = (INSTR *)(CODE_PTR_FROM_VECTOR_PTR(mmuVector));

    func = mmuE500InstTlbMissHandler;

    if (excExtendedVectors == TRUE)
        {
#ifdef    _WRS_CONFIG_LP64
        /* Install handler address into existing vector */

        mmuVectorCode[EXT_ENT_OFF]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF]) << 16)   | \
                    MSW((int)((long)FUNCREF(func)>>32)));

        mmuVectorCode[EXT_ENT_OFF+1]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+1]) << 16) | \
                    LSW((int)((long)FUNCREF(func)>>32)));

        mmuVectorCode[EXT_ENT_OFF+3]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+3]) << 16) | \
                    MSW((int)(long)FUNCREF(func)));

        mmuVectorCode[EXT_ENT_OFF+4]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+4]) << 16) | \
                    LSW((int)(long)FUNCREF(func)));

        CACHE_TEXT_UPDATE ((void *)&mmuVectorCode[EXT_ENT_OFF], 20);
#else
        /* Install handler address into existing vector */

        mmuVectorCode[EXT_ENT_OFF]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF]) << 16)
                    | MSW((int)func));
        mmuVectorCode[EXT_ENT_OFF+1]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+1]) << 16)
                    | LSW((int)func));

        (void) CACHE_TEXT_UPDATE ((void *)&mmuVectorCode[EXT_ENT_OFF], 8);
#endif /* _WRS_CONFIG_LP64 */
        }
    else
        {
        /* Compute short jump instruction to handler from vector */

        mmuHandlerBranch = ppcBrCompute ((VOIDFUNCPTR) FUNCREF(func),
                                         &((INSTR *)mmuVector)[ENT_OFF], 1);
        if (mmuHandlerBranch == (INSTR)0)
            {
            size_t len = strlen(sysExcMsg);
            strncat(&(sysExcMsg[len]), instMissMsg, (0x100 - len));
            sysExcMsg += len;

            return (ERROR);
            }

        /* Install jump to handler into existing vector */

        mmuVectorCode[ENT_OFF] = mmuHandlerBranch;
        CACHE_TEXT_UPDATE ((void *)&mmuVectorCode[ENT_OFF], 4);
        }

    /* Address of vector, in vector execution space */

    mmuVector = (vectorPtr)(excVecBase + (vecTblOffset)_EXC_OFF_DATA_MISS);

    /* Address of vector, in normal code space */

    mmuVectorCode = (INSTR *)(CODE_PTR_FROM_VECTOR_PTR(mmuVector));

    func = mmuE500DataTlbMissHandler;

    if (excExtendedVectors == TRUE)
        {
#ifdef    _WRS_CONFIG_LP64

        /* Install handler address into existing vector */

        mmuVectorCode[EXT_ENT_OFF]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF]) << 16)
              | MSW((int)((long)FUNCREF(func)>>32)));

        mmuVectorCode[EXT_ENT_OFF+1]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+1]) << 16)
              | LSW((int)((long)FUNCREF(func)>>32)));

        mmuVectorCode[EXT_ENT_OFF+3]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+3]) << 16)
              | MSW((int)(long)FUNCREF(func)));

        mmuVectorCode[EXT_ENT_OFF+4]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+4]) << 16)
              | LSW((int)(long)FUNCREF(func)));

        CACHE_TEXT_UPDATE ((void *)&mmuVectorCode[EXT_ENT_OFF], 8);
#else
     
        /* Install handler address into existing vector */

        mmuVectorCode[EXT_ENT_OFF]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF]) << 16)
              | MSW((int)func));
        mmuVectorCode[EXT_ENT_OFF+1]
        = (INSTR) ((MSW((int)mmuVectorCode[EXT_ENT_OFF+1]) << 16)
              | LSW((int)func));
        (void) CACHE_TEXT_UPDATE ((void *)&mmuVectorCode[EXT_ENT_OFF], 8);
#endif /* _WRS_CONFIG_LP64 */ 
        }
    else
        {
        /* Compute short jump instruction to handler from vector */

        mmuHandlerBranch = ppcBrCompute ((VOIDFUNCPTR) FUNCREF(func),
                                         &((INSTR *)mmuVector)[ENT_OFF], 1);

        if (mmuHandlerBranch == (INSTR)0)
            {
            size_t len = strlen(sysExcMsg);
            strncat(&(sysExcMsg[len]), instMissMsg, (0x100 - len));
            sysExcMsg += len;

            return (ERROR);
            }

        /* Install jump to handler into existing vector */

        mmuVectorCode[ENT_OFF] = mmuHandlerBranch;
        CACHE_TEXT_UPDATE ((void *)&mmuVectorCode[ENT_OFF], 4);
        }

    /*
     * Remove old CAM TLB1 entries, leave TLB0
     * entries as required for mem access
     */
    /*
     * xxx - BSP (p4080) sets up some static TLBs w/o protection (why?)
     * original mmuE500Lib re-executes static TLB init (why?)
     */

    /* mmuE500TlbStaticInvalidate();*/ /* Just CAMs without IPROT set */

    mmuE500TlbDynamicInvalidate();

    mmuPpcPidSet (MMU_ASID_GLOBAL);

#ifdef _WRS_CONFIG_LP64

    mmuLibFuncs.mmuDirectPageMap = mmuE500DirectPageMap;

    /* a static entry is used to prevent access to non-canonical address */
    
    (void) mmuStaticMapInfoAdd (NON_CANONICAL_RGN_BASE, NON_CANONICAL_RGN_SIZE,
                         -1UL, _MMU_ATTR_INVALID);

#endif /* _WRS_CONFIG_LP64 */

    return (OK);
    }

/*******************************************************************************
*
* mmuTlbInvalidateEntry - Invalidate tlb entry
*
* This routine invalidate tlb entry matching an effective addr and context ID
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

_WRS_INLINE void mmuTlbInvalidateEntry
    (
    VIRT_ADDR   virtAddr,        /* address    */
    size_t      entrySize,       /* entry size */
    MMU_CTX_ID  ctxId            /* PID        */
    )
    {
    UINT32    tSize;

    if (virtAddr == _MMU_TLB_ENTRY_ALL)
        {
        mmuE500TlbInvalidateEntryAll (ctxId);
        return;
        }

#ifdef _MMU_SUPPORTS_MAS6_ISIZE

    /* MAS6 ISIZE support (ISA 2.06+) */

    if (entrySize == 0x1000)            /* 4k */
        tSize = 0x02;
    else if (entrySize == 0x10000)      /* 64k */
        tSize = 0x06;
    else if (entrySize == 0x100000)     /* 1M */
        tSize = 0x0A;
    else if (entrySize == 0x1000000)    /* 16M */
        tSize = 0x0E;
    else
        tSize = 0;
#else
    tSize = 0;
#endif

    mmuE500TlbInvalidateEntry (virtAddr, tSize, ctxId);
    }

/*******************************************************************************
*
* mmuCacheSync - sync the mmu
*
* This routine cleans or invalidates cache for the buffer changed from cached
* to un-cached.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/

_WRS_INLINE void mmuCacheSync
    (
    MMU_ARCH_ATTR   oldAttr,
    MMU_ARCH_ATTR   newAttr,
    VIRT_ADDR       virtAddr,
    size_t          size
    )
    {
    MMU_ARCH_ATTR   oldCache = oldAttr & MMU_STATE_MASK_CACHEABLE;

    /* test if the buffer is write accessible */

    if (((oldAttr & MMU_STATE_MASK_VALID) == MMU_STATE_VALID) &&
        (oldCache != MMU_STATE_CACHEABLE_NOT) && (oldAttr & _MMU_SW))
        {
        MMU_ARCH_ATTR   newCache = newAttr & MMU_STATE_MASK_CACHEABLE;

        /*
         * Check to see if cache state is changing and requires cache
         * maintenance.
         * We also need to clean or invalidate cache when the buffer becomes
         * write inaccessible in case the cache state will be changed later
         * while the buffer is inaccessible.
         */

        if (((newAttr & MMU_STATE_MASK_VALID) == MMU_STATE_VALID_NOT) ||
            (!(newAttr & _MMU_SW)) || (oldCache != newCache))
            {
            if (oldCache == MMU_STATE_CACHEABLE_COPYBACK)
                (void) cacheClear (DATA_CACHE, (void *) virtAddr, size);
            else
                (void) cacheInvalidate (DATA_CACHE, (void *) virtAddr, size);
            }
        }
    }

/*******************************************************************************
*
* mmuL1ToTranslationBase -
*/

_WRS_INLINE MMU_CTX_TBASE mmuL1ToTranslationBase
    (
    MMU_L1_ENTRY * pL1
    )
    {
    MMU_CTX_TBASE tBase;

    tBase = (MMU_CTX_TBASE) pL1;

    return (tBase);
    }

/*******************************************************************************
*
* mmuCtxIdAlloc -
*/

_WRS_INLINE MMU_CTX_ID mmuCtxIdAlloc
    (
    MMU_CTX_TBASE    tBase
    )
    {
    MMU_CTX_ID        ctxId;

    if ((ctxId = mmuAsidAlloc()) == _MMU_ASID_ERROR)
        return (_MMU_CTXID_ERROR);

    mmuE500ContextTbl[ctxId] = tBase;

    return (ctxId);
    }

/*******************************************************************************
*
* mmuCtxIdFree -
*/

_WRS_INLINE STATUS mmuCtxIdFree
    (
    MMU_CTX_ID        ctxId
    )
    {
    mmuE500ContextTbl[ctxId] = (ULONG)NULL;

    return mmuAsidFree (ctxId);
    }

/*******************************************************************************
*
* mmuContextSet -
*/

_WRS_INLINE void mmuContextSet
    (
    MMU_CTX_TBASE    transBase,
    MMU_CTX_ID       ctxId
    )
    {
    mmuPpcPidSet (ctxId);
    }

/*******************************************************************************
*
* mmuStartup -
*/

_WRS_INLINE void mmuStartup (void)
    {
    extern BOOL cacheIToEnable;        /* xxx - should be in ppcArchVarsP.h */
    extern BOOL cacheDToEnable;

    if (cacheIToEnable)
        cacheAimE500DisableIFromMmu ();

    mmuPpcAEnable (MMU_I_ADDR_TRANS);        /* enable instruction MMU */
    mmuPpcIEnabled = TRUE;            /* tell I MMU is turned on */

    /* test if the Instruction cache should be enabled too */

    if (cacheIToEnable)
        cacheArchEnable (_INSTRUCTION_CACHE);    /* enable I */

    if (cacheDataEnabled)
        {
        /*
         * D-cache already enabled.  Clear and disable it before
         * enabling the MMU, since some areas currently in the
         * cache may become non-cacheable when the MMU is enabled
         * -- in general, such paradoxes have unspecified results.
         * Clearing only the part(s) whose cacheability changes,
         * while possible in principle, is too complex in practice.
         */
        cacheAimE500DisableDFromMmu ();
        }

    mmuPpcAEnable (MMU_D_ADDR_TRANS);        /* enable data MMU */
    mmuPpcDEnabled = TRUE;            /* tell D MMU is turned on */

    /* test if the Data cache should be enabled too */

    if (cacheDToEnable)
        cacheArchEnable (_DATA_CACHE);      /* enable D cache */

	mmuPpcHasBeenEnabled = TRUE;
    }

/*******************************************************************************
*
* mmuShutdown -
*/

_WRS_INLINE void mmuShutdown (void)
    {
    extern BOOL cacheIToEnable;
    extern BOOL cacheDToEnable;

    /*
     * if the Instruction cache is enabled, then disable the
     * instruction cache before disabling the Instruction MMU.
     */
    if (cacheIToEnable)
        cacheAimE500DisableIFromMmu ();

    /* disable the Instruction MMU */

    mmuPpcADisable (MMU_I_ADDR_TRANS);

    /* set the flag to tell that the Instruction MMU is disabled */

    mmuPpcIEnabled = FALSE;

    /*
     * if the Data cache is enabled, then disable the Data cache
     * before disabling the Data MMU.
     */
    if (cacheDToEnable)
        cacheAimE500DisableDFromMmu ();

    /* disable the Data MMU */

    mmuPpcADisable (MMU_D_ADDR_TRANS);

    /* set the flag to tell that the Data MMU is disabled */
    mmuPpcDEnabled = FALSE;

	mmuPpcHasBeenEnabled = FALSE;
    }

/*******************************************************************************
*
* mmuProtectionDisable -
*/

_WRS_INLINE int mmuProtectionDisable
    (
    void *    addr
    )
    {
    int key;

    /* prevent migration to another CPU  */

    key = INT_CPU_LOCK();

    /* TLB w3, SUP R/W */

    mmuE500ProtectionOverride (ROUND_DOWN (addr, MMU_PAGE_SIZE), 0x5);

    /* invalidate for both global and current context */

    mmuE500TlbInvalidateEntry ((VIRT_ADDR)addr, 0, _MMU_CTX_GLOBAL);
    mmuE500TlbInvalidateEntry ((VIRT_ADDR)addr, 0, mmuPpcPidGet());

    return (key);
    }

/*******************************************************************************
*
* mmuProtectionEnable -
*/

_WRS_INLINE void mmuProtectionEnable
    (
    void *      addr,
    int         key
    )
    {
    mmuE500ProtectionOverride ((VIRT_ADDR) -1, 0x0);

    /* invalidate for both global and current context */

    mmuE500TlbInvalidateEntry ((VIRT_ADDR)addr, 0, _MMU_CTX_GLOBAL);
    mmuE500TlbInvalidateEntry ((VIRT_ADDR)addr, 0, mmuPpcPidGet());

    /* re-enable preemption; it was disabled in mmuProtectionDisable */

    INT_CPU_UNLOCK (key);
    }

/*******************************************************************************
*
* mmuPhysToPtr -
*/

_WRS_INLINE void * mmuPhysToPtr
    (
    PHYS_ADDR physAddr
    )
    {
    return (void *)(VIRT_ADDR)(physAddr);
    }

/*******************************************************************************
*
* mmuPtrToPhys -
*/

_WRS_INLINE PHYS_ADDR mmuPtrToPhys
    (
    void * pTbl
    )
    {
    return (PHYS_ADDR)(VIRT_ADDR)(pTbl);
    }

#ifdef _WRS_MMU_FOUR_LEVEL_PT

/*******************************************************************************
*
* mmuL1IndexGet -
*/

_WRS_INLINE UINT mmuL1IndexGet
    (
    VIRT_ADDR virtAddr
    )
    {
    return ((UINT) ((virtAddr & MMU_L1_INDEX_MASK) >> MMU_L1_INDEX_SHIFT));
    }

/*******************************************************************************
*
* mmuL1EntryClear -
*/

_WRS_INLINE void mmuL1EntryClear
    (
    MMU_L1_ENTRY *      pL1,
    size_t              count
    )
    {
    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL1, count, sizeof (*pL1),
				       pL1[ix] = MMU_L1_INIT_ENTRY);
    }

/*******************************************************************************
*
* mmuL2IndexGet -
*/

_WRS_INLINE UINT mmuL2IndexGet
    (
    VIRT_ADDR virtAddr
    )
    {
    return ((UINT) ((virtAddr & MMU_L2_INDEX_MASK) >> MMU_L2_INDEX_SHIFT));
    }

/*******************************************************************************
*
* mmuL2EntryTableSet -
*/

_WRS_INLINE void mmuL2EntryTableSet
    (
    MMU_L1_ENTRY * pL1,
    MMU_L2_ENTRY * pL2
    )
    {
    int key;

    key = mmuProtectionDisable (pL1);
    *pL1 = (MMU_L1_ENTRY) pL2;
    mmuProtectionEnable (pL1, key);
    }

/*******************************************************************************
*
* mmuL2EntryTableGet -
*/

_WRS_INLINE MMU_L2_ENTRY * mmuL2EntryTableGet
    (
    MMU_L1_ENTRY * pL1
    )
    {
    MMU_L2_ENTRY * pL2 = NULL;

    if (*pL1 != MMU_L1_INIT_ENTRY)
        pL2 = (MMU_L2_ENTRY *) *pL1;

    return (pL2);
    }

/*******************************************************************************
*
* mmuL2EntryClear -
*/

_WRS_INLINE void mmuL2EntryClear
    (
    MMU_L2_ENTRY *      pL2,
    size_t              count
    )
    {
    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL2, count, sizeof (*pL2),
        {
        pL2[ix].w32.w[0] = MMU_L2_ENTRY_INIT_W0;
        pL2[ix].w32.w[1] = MMU_L2_ENTRY_INIT_W1;
        pL2[ix].w32.w[2] = MMU_L2_ENTRY_INIT_W2;
        pL2[ix].w32.w[3] = MMU_L2_ENTRY_INIT_W3;
        });
    }

#ifdef _WRS_MMU_SUPPORTS_L2_MAP
/*******************************************************************************
*
* mmuL2EntrySet -
*/
_WRS_INLINE STATUS mmuL2EntrySet
    (
    MMU_L2_ENTRY *      pL2,
    VIRT_ADDR           virtAddr,
    PHYS_ADDR           physAddr,
    size_t              count,
    MMU_ARCH_ATTR       attr,
    MMU_CTX_ID          ctxId,
    BOOL                isNew
    )
    {
    UINT32              word0;
    UINT32              word1;
    UINT32              word2;
    UINT32              word3;

    /* xxx - validate state changes / remap */

    /* compute the four PTE words */

    word0 = (attr & MMU_STATE_MASK_VALID) |
            (ctxId << MMU_PTE_W1_TID_SHIFT) |
            _MMU_TLB_TS_1 |
            MMU_L2_TLB_SIZE_W0;

#ifdef	_WRS_CONFIG_LP64
    word1 = attr & MMU_PTE_W1_MASK;
    word2 = (UINT32) (physAddr & 0xfffff000) |
            ((attr & MMU_PTE_W2_MASK) >> MMU_PTE_W2_SHIFT);
#else
    word1 = virtAddr | (attr & MMU_PTE_W1_MASK);
    word2 = physAddr | ((attr & MMU_PTE_W2_MASK) >> MMU_PTE_W2_SHIFT);
#endif	/* _WRS_CONFIG_LP64 */

#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
    word3 = (UINT32) (physAddr >> 32);
#else
    word3 = 0;
#endif

    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL2, count, sizeof (*pL2),
        {
        pL2[ix].w32.w[0] = word0;
        pL2[ix].w32.w[1] = word1;
        pL2[ix].w32.w[2] = word2;
        pL2[ix].w32.w[3] = word3;

        /*
         * increment virtual and physical address; note that there are chances
         * for physAddr to cross 4GB boundaries, in which case word3 should also
         * be updated.
         */

#ifndef	_WRS_CONFIG_LP64
        word1 += MMU_L2_MAP_SIZE;
#endif	/* !_WRS_CONFIG_LP64 */

        word2 += MMU_L2_MAP_SIZE;
        
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
        physAddr += MMU_L2_MAP_SIZE;
        word3 = (UINT32) (physAddr >> 32);
#endif         
        });

    return (OK);
    }

/*******************************************************************************
*
* mmuL2EntryGet -
*/

_WRS_INLINE STATUS mmuL2EntryGet
    (
    MMU_L2_ENTRY *      pL2,
    PHYS_ADDR *         pPhysAddr,
    MMU_ARCH_ATTR *     pAttr
    )
    {
    PHYS_ADDR        physAddr;
    MMU_ARCH_ATTR    mmuAttr;

    if (pL2->w32.w[2] == MMU_L2_ENTRY_INIT_W2)
        return (ERROR);

    if (pPhysAddr != NULL)
        {
        physAddr = pL2->w32.w[2] & 0xfffff000;
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
        physAddr |= ((PHYS_ADDR)pL2->w32.w[3] << 32);
#endif
        *pPhysAddr = physAddr;
        }

    if (pAttr != NULL)
        {
        mmuAttr  = (MMU_ARCH_ATTR) pL2->w32.w[0] & MMU_STATE_MASK_VALID;      

        mmuAttr |= pL2->w32.w[1] & MMU_PTE_W1_MASK;

        /*
         * Note that the writable & execute bits are in a different bit position in
         * PTE than in the MMU_ARCH_ATTR.
         */

        mmuAttr |= (pL2->w32.w[2] << MMU_PTE_W2_SHIFT) & MMU_PTE_W2_MASK;
        *pAttr = mmuAttr;
        }

    return (OK);
    }
#endif /* _WRS_MMU_SUPPORTS_L2_MAP */

/*******************************************************************************
*
* mmuL3IndexGet -
*/

_WRS_INLINE UINT mmuL3IndexGet
    (
    VIRT_ADDR virtAddr
    )
    {
    return ((UINT) ((virtAddr & MMU_L3_INDEX_MASK) >> MMU_L3_INDEX_SHIFT));
    }

/*******************************************************************************
*
* mmuL3EntryTableSet -
*/

_WRS_INLINE void mmuL3EntryTableSet
    (
    MMU_L2_ENTRY * pL2,
    MMU_L3_ENTRY * pL3
    )
    {
    int key;

    /* address is shifted to avoid conflict with VALID bit  */

    key = mmuProtectionDisable (pL2);
    pL2->tbl.w[0] = MMU_L2_TYPE_L3_TBL;
    pL2->tbl.w[1] = MMU_L2_ENTRY_INIT_W1;
    pL2->tbl.l3Entry = pL3;
    mmuProtectionEnable (pL2, key);
    }

/*******************************************************************************
*
* mmuL3EntryTableGet -
*/

_WRS_INLINE MMU_L3_ENTRY * mmuL3EntryTableGet
    (
    MMU_L2_ENTRY * pL2
    )
    {
    UINT32  word0;
    MMU_L3_ENTRY * pL3 = NULL;

    word0 = pL2->tbl.w[0];

    if ((word0 & MMU_L2_TYPE_MASK_W0) == MMU_L2_TYPE_L3_TBL)
        pL3 = pL2->tbl.l3Entry;

    return (pL3);
    }

/*******************************************************************************
*
* mmuL3EntryClear -
*/

_WRS_INLINE void mmuL3EntryClear
    (
    MMU_L3_ENTRY *    pL3,
    size_t            count
    )
    {
    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL3, count, sizeof (*pL3),
        {
        pL3[ix].w32.w[0] = MMU_L3_ENTRY_INIT_W0;
        pL3[ix].w32.w[1] = MMU_L3_ENTRY_INIT_W1;
        pL3[ix].w32.w[2] = MMU_L3_ENTRY_INIT_W2;
        pL3[ix].w32.w[3] = MMU_L3_ENTRY_INIT_W3;
        });
    }

#ifdef _WRS_MMU_SUPPORTS_L3_MAP
/*******************************************************************************
*
* mmuL3EntrySet -
*/

_WRS_INLINE STATUS mmuL3EntrySet
    (
    MMU_L3_ENTRY *  pL3,
    VIRT_ADDR       virtAddr,
    PHYS_ADDR       physAddr,
    size_t          count,
    MMU_ARCH_ATTR   attr,
    MMU_CTX_ID      ctxId,
    BOOL            isNew
    )
    {
    UINT32          word0;
    UINT32          word1;
    UINT32          word2;
    UINT32          word3;

    /* xxx - validate state changes / remap */

    /* compute the four PTE words */

    word0 = (attr & MMU_STATE_MASK_VALID) |
            (ctxId << MMU_PTE_W1_TID_SHIFT) |
            _MMU_TLB_TS_1 |
            MMU_L3_TLB_SIZE_W0;

#ifdef	_WRS_CONFIG_LP64
    word1 = attr & MMU_PTE_W1_MASK;
    word2 = (UINT32) (physAddr & 0xfffff000) |
            ((attr & MMU_PTE_W2_MASK) >> MMU_PTE_W2_SHIFT);
#else
    word1 = virtAddr | (attr & MMU_PTE_W1_MASK);
    word2 = physAddr | ((attr & MMU_PTE_W2_MASK) >> MMU_PTE_W2_SHIFT);
#endif	/* _WRS_CONFIG_LP64 */

#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
    word3 = (UINT32) (physAddr >> 32);
#else
    word3 = 0;
#endif

    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL3, count, sizeof (*pL3),
        {
        pL3[ix].w32.w[0] = word0;
        pL3[ix].w32.w[1] = word1;
        pL3[ix].w32.w[2] = word2;
        pL3[ix].w32.w[3] = word3;

        /*
         * increment virtual and physical address; note that there are chances
         * for physAddr to cross 4GB boundaries, in which case word3 should also
         * be updated.
         */

#ifndef	_WRS_CONFIG_LP64
        word1 += MMU_L3_MAP_SIZE;
#endif	/* !_WRS_CONFIG_LP64 */

        word2 += MMU_L3_MAP_SIZE;
        
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
        physAddr += MMU_L3_MAP_SIZE;
        word3 = (UINT32) (physAddr >> 32);
#endif        
        });

    return (OK);
    }

/*******************************************************************************
*
* mmuL3EntryGet -
*/

_WRS_INLINE STATUS mmuL3EntryGet
    (
    MMU_L3_ENTRY *      pL3,
    PHYS_ADDR *         pPhysAddr,
    MMU_ARCH_ATTR *     pAttr
    )
    {
    PHYS_ADDR        physAddr;
    MMU_ARCH_ATTR    mmuAttr;

    if (pL3->w32.w[2] == MMU_L3_ENTRY_INIT_W2)
        return (ERROR);

    if (pPhysAddr != NULL)
        {
        physAddr = pL3->w32.w[2] & 0xfffff000;
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
        physAddr |= ((PHYS_ADDR)pL3->w32.w[3] << 32);
#endif
        *pPhysAddr = physAddr;
        }

    if (pAttr != NULL)
        {
        mmuAttr  = (MMU_ARCH_ATTR) pL3->w32.w[0] & MMU_STATE_MASK_VALID;

        mmuAttr |= pL3->w32.w[1] & MMU_PTE_W1_MASK;

        /*
         * Note that the writable & execute bits are in a different bit position in
         * PTE than in the MMU_ARCH_ATTR.
         */

        mmuAttr |= (pL3->w32.w[2] << MMU_PTE_W2_SHIFT) & MMU_PTE_W2_MASK;
        *pAttr = mmuAttr;
        }

    return (OK);
    }
#endif /* _WRS_MMU_SUPPORTS_L3_MAP */

/*******************************************************************************
*
* mmuL4IndexGet -
*/

_WRS_INLINE UINT mmuL4IndexGet
    (
    VIRT_ADDR virtAddr
    )
    {
    return ((UINT) ((virtAddr & MMU_L4_INDEX_MASK) >> MMU_L4_INDEX_SHIFT));
    }

/*******************************************************************************
*
* mmuL4EntryTableSet -
*/

_WRS_INLINE void mmuL4EntryTableSet
    (
    MMU_L3_ENTRY * pL3,
    MMU_L4_ENTRY * pL4
    )
    {
    int key;

    /* address is shifted to avoid conflict with VALID bit  */

    key = mmuProtectionDisable (pL3);
    pL3->tbl.w[0] = MMU_L3_TYPE_L4_TBL;
    pL3->tbl.w[1] = MMU_L3_ENTRY_INIT_W1;
    pL3->tbl.l4Entry = pL4;
    mmuProtectionEnable (pL3, key);
    }

/*******************************************************************************
*
* mmuL4EntryTableGet -
*/

_WRS_INLINE MMU_L4_ENTRY * mmuL4EntryTableGet
    (
    MMU_L3_ENTRY * pL3
    )
    {
    UINT32 word0;
    MMU_L4_ENTRY * pL4 = NULL;

    word0 = pL3->tbl.w[0];

    if ((word0 & MMU_L3_TYPE_MASK_W0) == MMU_L3_TYPE_L4_TBL)
        pL4 = pL3->tbl.l4Entry;

    return (pL4);
    }

/*******************************************************************************
*
* mmuL4EntryClear -
*/

_WRS_INLINE void mmuL4EntryClear
    (
    MMU_L4_ENTRY *  pL4,
    size_t          count
    )
    {
    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL4, count, sizeof (*pL4),
        {
        pL4[ix].w[0] = MMU_L4_ENTRY_INIT_W0;
        pL4[ix].w[1] = MMU_L4_ENTRY_INIT_W1;
        pL4[ix].w[2] = MMU_L4_ENTRY_INIT_W2;
        pL4[ix].w[3] = MMU_L4_ENTRY_INIT_W3;
        });
    }

#ifdef _WRS_MMU_SUPPORTS_L4_MAP
/*******************************************************************************
*
* mmuL4EntrySet -
*/

_WRS_INLINE STATUS mmuL4EntrySet
    (
    MMU_L4_ENTRY *   pL4,
    VIRT_ADDR        virtAddr,
    PHYS_ADDR        physAddr,
    size_t           count,
    MMU_ARCH_ATTR    attr,
    MMU_CTX_ID       ctxId,
    BOOL             isNew
    )
    {
    UINT32           word0;
    UINT32           word1;
    UINT32           word2;
    UINT32           word3;

    /* xxx - validate state changes / remap */

    /* compute the four PTE words */

    word0 = (attr & MMU_STATE_MASK_VALID) |
            (ctxId << MMU_PTE_W1_TID_SHIFT) |
            _MMU_TLB_TS_1;

#ifdef	_WRS_CONFIG_LP64
    word1 = attr & MMU_PTE_W1_MASK;
#else
    word1 = virtAddr | (attr & MMU_PTE_W1_MASK);
#endif	/* _WRS_CONFIG_LP64 */

    word2 = (UINT32) (physAddr | ((attr & MMU_PTE_W2_MASK) >> MMU_PTE_W2_SHIFT)) & 0xFFFFFFFF;

#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
    word3 = (UINT32) ((physAddr >> 32) & 0xFFFFFFFF);
#else
    word3 = 0;
#endif


    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL4, count, sizeof (*pL4),
        {
        pL4[ix].w[0] = word0;
        pL4[ix].w[1] = word1;
        pL4[ix].w[2] = word2;
        pL4[ix].w[3] = word3;

        /*
         * increment virtual and physical address; note that there are chances
         * for physAddr to cross 4GB boundaries, in which case word3 should also
         * be updated.
         */

#ifndef	_WRS_CONFIG_LP64
        word1 += MMU_L4_MAP_SIZE;
#endif	/* !_WRS_CONFIG_LP64 */

        word2 += MMU_L4_MAP_SIZE;
        
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
        physAddr += MMU_L4_MAP_SIZE;
        word3 = (UINT32) (physAddr >> 32);
#endif           
        });

    return (OK);
    }

/*******************************************************************************
*
* mmuL4EntryGet -
*/

_WRS_INLINE STATUS mmuL4EntryGet
    (
    MMU_L4_ENTRY *      pL4,
    PHYS_ADDR *         pPhysAddr,
    MMU_ARCH_ATTR *     pAttr
    )
    {
    PHYS_ADDR        physAddr;
    MMU_ARCH_ATTR    mmuAttr;

    if (pL4->w[2] == MMU_L4_ENTRY_INIT_W2)
        return (ERROR);

    if (pPhysAddr != NULL)
        {
        physAddr = pL4->w[2] & 0xfffff000;
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
        physAddr |= ((PHYS_ADDR)pL4->w[3] << 32);
#endif
        *pPhysAddr = physAddr;
        }

    if (pAttr != NULL)
        {
        mmuAttr  = (MMU_ARCH_ATTR) pL4->w[0] & MMU_STATE_MASK_VALID;
        
        mmuAttr |= pL4->w[1] & MMU_PTE_W1_MASK;

        /*
         * Note that the writable & execute bits are in a different bit position in
         * PTE than in the MMU_ARCH_ATTR.
         */

        mmuAttr |= (pL4->w[2] << MMU_PTE_W2_SHIFT) & MMU_PTE_W2_MASK;
        *pAttr = mmuAttr;
        }

    return (OK);
    }
#endif /* _WRS_MMU_SUPPORTS_L4_MAP */


#else /* _WRS_MMU_FOUR_LEVEL_PT */

/*******************************************************************************
*
* mmuL1IndexGet -
*/

_WRS_INLINE UINT mmuL1IndexGet
    (
    VIRT_ADDR virtAddr
    )
    {
    UINT addr = 0;
    addr = (UINT) (virtAddr >> (MMU_L2_MAP_WIDTH + MMU_PAGE_SIZE_BITS));
    return addr;
    }

/*******************************************************************************
*
* mmuL1EntryClear -
*/

_WRS_INLINE void mmuL1EntryClear
    (
    MMU_L1_ENTRY *    pL1,
    size_t            count
    )
    {
    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL1, count, sizeof (*pL1),
				       pL1[ix] = MMU_L1_INIT_ENTRY);
    }

/*******************************************************************************
*
* mmuL2IndexGet -
*/

_WRS_INLINE UINT mmuL2IndexGet
    (
    VIRT_ADDR virtAddr
    )
    {
    UINT addr = 0;
    addr = (UINT) ((virtAddr & MMU_L2_INDEX_MASK) >> MMU_PAGE_SIZE_BITS);
    return addr;
    }

/*******************************************************************************
*
* mmuL2EntryTableSet -
*/

_WRS_INLINE void mmuL2EntryTableSet
    (
    MMU_L1_ENTRY * pL1,
    MMU_L2_ENTRY * pL2
    )
    {
    int key;

    key = mmuProtectionDisable (pL1);
    *pL1 = (MMU_L1_ENTRY) pL2;
    mmuProtectionEnable (pL1, key);
    }

/*******************************************************************************
*
* mmuL2EntryTableGet -
*/

_WRS_INLINE MMU_L2_ENTRY * mmuL2EntryTableGet
    (
    MMU_L1_ENTRY * pL1
    )
    {
    MMU_L2_ENTRY * pL2 = NULL;

    if (*pL1 != MMU_L1_INIT_ENTRY)
        pL2 = (MMU_L2_ENTRY *) *pL1;

    return (pL2);
    }

/*******************************************************************************
*
* mmuL2EntryClear -
*/

_WRS_INLINE void mmuL2EntryClear
    (
    MMU_L2_ENTRY *  pL2,
    size_t          count
    )
    {
    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL2, count, sizeof (*pL2),
        {
        pL2[ix].w32.w[0] = MMU_L2_ENTRY_INIT_W0;
        pL2[ix].w32.w[1] = MMU_L2_ENTRY_INIT_W1;
        pL2[ix].w32.w[2] = MMU_L2_ENTRY_INIT_W2;
        pL2[ix].w32.w[3] = MMU_L2_ENTRY_INIT_W3;
        });
    }

#ifdef _WRS_MMU_SUPPORTS_L2_MAP
/*******************************************************************************
*
* mmuL2EntrySet -
*/

_WRS_INLINE STATUS mmuL2EntrySet
    (
    MMU_L2_ENTRY *   pL2,
    VIRT_ADDR        virtAddr,
    PHYS_ADDR        physAddr,
    size_t           count,
    MMU_ARCH_ATTR    attr,
    MMU_CTX_ID       ctxId,
    BOOL             isNew
    )
    {
    UINT32              word0;
    UINT32              word1;
    UINT32              word2;
    UINT32              word3;

    /* xxx - validate state changes / remap */

    /* compute the four PTE words */

    word0 = (attr & MMU_STATE_MASK_VALID) |
            (ctxId << MMU_PTE_W1_TID_SHIFT) |
            _MMU_TLB_TS_1;
#ifdef	_WRS_CONFIG_LP64
    word1 = attr & MMU_PTE_W1_MASK;
#else
    word1 = virtAddr | (attr & MMU_PTE_W1_MASK);
#endif	/* _WRS_CONFIG_LP64 */

    word2 = (UINT32) (physAddr | ((attr & MMU_PTE_W2_MASK) >> MMU_PTE_W2_SHIFT)) & 0xFFFFFFFF;

#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
    word3 = (UINT32) ((physAddr >> 32) & 0xFFFFFFFF);
#else
    word3 = 0;
#endif

    _MMU_LOOP_WITH_PROTECTION_DISABLE (pL2, count, sizeof (*pL2),
        {
        pL2[ix].w32.w[0] = word0;
        pL2[ix].w32.w[1] = word1;
        pL2[ix].w32.w[2] = word2;
        pL2[ix].w32.w[3] = word3;

        /*
         * increment virtual and physical address; note that here we do not
         * cross L2 table boundaries, so word3 remains the same.
         */

#ifndef	_WRS_CONFIG_LP64
        word1 += MMU_L2_MAP_SIZE;
#endif	/* !_WRS_CONFIG_LP64 */

        word2 += MMU_L2_MAP_SIZE;
        });

    return (OK);
    }

/*******************************************************************************
*
* mmuL2EntryGet -
*/

_WRS_INLINE STATUS mmuL2EntryGet
    (
    MMU_L2_ENTRY *   pL2,
    PHYS_ADDR *      pPhysAddr,
    MMU_ARCH_ATTR *  pAttr
    )
    {
    PHYS_ADDR        physAddr;
    MMU_ARCH_ATTR    mmuAttr;

    if (pL2->w32.w[2] == MMU_L2_ENTRY_INIT_W2)
        return (ERROR);

    if (pPhysAddr != NULL)
        {
        physAddr = pL2->w32.w[2] & 0xfffff000;
#if defined(PPC_e500v2) || defined(PPC_e500mc) || defined(PPC_e6500)
        physAddr |= ((PHYS_ADDR)pL2->w32.w[3] << 32);
#endif
        *pPhysAddr = physAddr;
        }

    if (pAttr != NULL)
        {
        mmuAttr  = pL2->w32.w[0] & MMU_STATE_MASK_VALID;
        mmuAttr |= pL2->w32.w[1] & MMU_PTE_W1_MASK;

        /*
         * Note that the writable & execute bits are in a different bit position in
         * PTE than in the MMU_ARCH_ATTR.
         */

        mmuAttr |= (pL2->w32.w[2] << MMU_PTE_W2_SHIFT) & MMU_PTE_W2_MASK;
        *pAttr = mmuAttr;
        }

    return (OK);
    }
#endif /* _WRS_MMU_SUPPORTS_L2_MAP */

#endif /* _WRS_MMU_FOUR_LEVEL_PT */

/*******************************************************************************
*
* mmuAttrValidate - validate a MMU attribute
*
* This roution is used to validate legality of a MMU attribute.
*
* RETURNS: OK or ERROR
*
* ERRNO: N/A
*/

_WRS_INLINE STATUS mmuAttrValidate
    (
    MMU_ARCH_ATTR    attr
    )
    {
    if (attr == _MMU_ATTR_INVALID)
        return (ERROR);
    else
        return (OK);
    }

#ifdef __cplusplus
    }
#endif

#endif /* __INCmmuArchLibPh */
