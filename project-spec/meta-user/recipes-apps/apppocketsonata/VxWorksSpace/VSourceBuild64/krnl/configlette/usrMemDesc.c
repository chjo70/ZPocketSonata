/* usrMemDesc.c - memory descriptor stub file  */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06nov15,pcs  Resolved build warnings generated when Component 
             INCLUDE_CACHE_DMA32_LIB was included.(V7COR-3747)
29jan15,w_x  Fix carving of DMA32 area to prevent it fall over 4GB (V7PRO-1675)
26aug14,yjw  fix cortexm build error (US40548)
29may14,syt  corrected a typo in function. (V7PRO-919)
15feb14,x_z  updated carve logic and clean. (VXW7-1838)
15feb14,cww  remove sysMemTop() from vx7 builds (TA40644)
21jan14,r_y  missing carvedCnt variable declaration.(VXW7-1377)
14jan14,r_y  replace vmPageSizeGet with VM_PAGE_SIZE.(VXW7-1241)
13jan14,x_z  Fixed compling warnings.
31oct13,r_y  fix code error(CQ:WIND00441344)
21oct13,l_z  Add sysMemTop()
19aug13,x_z  Created.
*/

#include <vxWorks.h>
#include <sysLib.h>
#include <vmLib.h>
#include <string.h>
#include <private/kwriteLibP.h> /* _func_kprintf */

/* defines */

#define MEM_DESC_MSG(fmt, args...)                 \
    do                                              \
        {                                           \
        if (_func_kprintf != NULL)                  \
            _func_kprintf (fmt, ##args);            \
        } while (FALSE)

#define CACHE_DMA32_AREA_TOP (0x100000000) /* 4GB */

/* globals */

PHYS_MEM_DESC sysPhysMemDesc [SYS_MEM_DESC_NUM] = {{0}};
int sysPhysMemDescNumEnt = SYS_MEM_DESC_NUM;

/* locals */

/* Physical RAM descriptors */

LOCAL PHYS_MEM_DESC sysPhysRamDesc [SYS_MEM_DESC_NUM]   = {{0}};
LOCAL int           sysPhysRamDescCnt                   = 0;

#ifdef INCLUDE_CACHE_DMA32_LIB

/*
 * DMA memory descriptors used to provide DMA memory block below 4G physical
 * address if INCLUDE_CACHE_DMA32_LIB is defined.
 */

LOCAL PHYS_MEM_DESC sysDma32MemDesc     = {0};
LOCAL int           sysDma32MemDescCnt  = 0;
#endif /* INCLUDE_CACHE_DMA32_LIB */

#ifdef INCLUDE_USER_RESERVED_MEMORY

/*
 * user reserved memory descriptors if INCLUDE_USER_RESERVED_MEMORY is defined
 */

LOCAL PHYS_MEM_DESC sysUserMemDesc  = {0};
LOCAL int           sysUserMemDescCnt   = 0;
#endif /* INCLUDE_USER_RESERVED_MEMORY */

#ifdef INCLUDE_EDR_PM

/* persistent memory descriptors if INCLUDE_EDR_PM is defined */

LOCAL PHYS_MEM_DESC sysPmMemDesc = {0};
LOCAL int           sysPmMemDescCnt   = 0;
#endif /* INCLUDE_EDR_PM */

/* forward declarations */

#if (defined(INCLUDE_CACHE_DMA32_LIB) && (DMA32_HEAP_SIZE != 0))        || \
    (defined(INCLUDE_USER_RESERVED_MEMORY) && (USER_RESERVED_MEM != 0)) || \
    (defined(INCLUDE_EDR_PM) && (PM_RESERVED_MEM != 0))
LOCAL STATUS sysMemDescCarve
    (
    PHYS_MEM_DESC * pMemDesc,   /* destination memory descriptor table  */
    size_t          carveSize   /* size to be craved from sysPhysRamDesc[0]  */
    );
#endif

/*******************************************************************************
*
* sysPhysMemDescInit - hook for memory auto sizing
*
* This routine does nothing.
*
* RETURNS: N/A
*/

void sysMemDescInit (void)
    {
    }

/*******************************************************************************
*
* sysMemDescGet - return memory descriptors describing memory layout
*
* This routine is used during system boot to describe the memory
* layout to the kernel and included components. It supports
* memory autoconfiguration. It also supports carving memory from
* the first contiguous block of RAM for 32-bit DMA and persistent
* memory. This routine assumes that enough memory is provided
* in the 0th descriptor to support all of these segments.
*
* RETURNS: OK , or ERROR if no required descriptor.
*/

STATUS sysMemDescGet
    (
    MEM_DESC_TYPE   memDescType,    /* type of memory being queried */
    int             index,          /* index of memory block for the type */
    PHYS_MEM_DESC * pMemDesc        /* where to return description */
    )
    {
    PHYS_MEM_DESC * pDesc;
    int             descCnt;

    /* initialize memory descriptor if necessary */

    if (sysPhysRamDescCnt == 0)
        {

        /*
         * sysPhysMemDesc[] is only used for RAM and need be kept for other
         * subsystems
         */

        memcpy ((void *) sysPhysRamDesc, (void *) sysPhysMemDesc,
                sizeof (PHYS_MEM_DESC) * sysPhysMemDescNumEnt);
        sysPhysRamDescCnt = sysPhysMemDescNumEnt;

        /* carve DMA32 memory */

#if defined(INCLUDE_CACHE_DMA32_LIB) && (DMA32_HEAP_SIZE != 0)
        if (sysMemDescCarve (&sysDma32MemDesc, DMA32_HEAP_SIZE) == OK)
            {
            sysDma32MemDescCnt = 1;
            /* fixed DMA32 memory attribute if necessary */

#   ifdef SYS_DMA32_MEM_ATTR
            sysDma32MemDesc.initialState = SYS_DMA32_MEM_ATTR;
#   endif /* SYS_DMA32_MEM_ATTR */

#   ifdef SYS_DMA32_MEM_ATTR_MASK
            sysDma32MemDesc.initialStateMask = SYS_DMA32_MEM_ATTR_MASK;
#   endif /* SYS_DMA32_MEM_ATTR */
            
            if (sizeof (size_t) == 4)
                MEM_DESC_MSG ("carved %d bytes at phys addr %p for ", 
                sysDma32MemDesc.len, sysDma32MemDesc.physicalAddr);
            else
                MEM_DESC_MSG ("carved %ld bytes at phys addr %p for ", 
                sysDma32MemDesc.len, sysDma32MemDesc.physicalAddr);
            
            MEM_DESC_MSG ("DMA32 memory from Physical RAM\n");
            }
#endif /* INCLUDE_CACHE_DMA32_LIB */

        /* carve user reserved memory */

#if defined(INCLUDE_USER_RESERVED_MEMORY) && (USER_RESERVED_MEM != 0)
        if (sysMemDescCarve (&sysUserMemDesc, USER_RESERVED_MEM) == OK)
            {
            sysUserMemDescCnt = 1;
            
            if (sizeof (size_t) == 4)
                MEM_DESC_MSG ("carved %d bytes at phys addr %p for ", 
                sysUserMemDesc.len, sysUserMemDesc.physicalAddr);
            else
                MEM_DESC_MSG ("carved %ld bytes at phys addr %p for ", 
                sysUserMemDesc.len, sysUserMemDesc.physicalAddr);
            
            MEM_DESC_MSG ("user reserved memory from Physical RAM\n");
            }
#endif /* INCLUDE_USER_RESERVED_MEMORY */

        /* carve persistent memory */

#if defined(INCLUDE_EDR_PM) && (PM_RESERVED_MEM != 0)
        if (sysMemDescCarve (&sysPmMemDesc, PM_RESERVED_MEM) == OK)
            {
            sysPmMemDescCnt = 1;
            
            if (sizeof (size_t) == 4)
                MEM_DESC_MSG ("carved %d bytes at phys addr %p for ", 
                sysPmMemDesc.len, sysPmMemDesc.physicalAddr);
            else
                MEM_DESC_MSG ("carved %ld bytes at phys addr %p for ", 
                sysPmMemDesc.len, sysPmMemDesc.physicalAddr);
            
            MEM_DESC_MSG ("persistent memory from Physical RAM\n");
            }
#endif /* INCLUDE_EDR_PM */
        }

    if (memDescType == MEM_DESC_RAM)
        {
        pDesc   = sysPhysRamDesc;
        descCnt = sysPhysRamDescCnt;
        }

#ifdef INCLUDE_CACHE_DMA32_LIB
    else if (memDescType == MEM_DESC_DMA32_RAM)
        {
        pDesc   = &sysDma32MemDesc;
        descCnt = sysDma32MemDescCnt;
        }
#endif /* INCLUDE_CACHE_DMA32_LIB */

#ifdef INCLUDE_USER_RESERVED_MEMORY
    else if (memDescType == MEM_DESC_USER_RESERVED_RAM)
        {
        pDesc   = &sysUserMemDesc;
        descCnt = sysUserMemDescCnt;
        }
#endif /* INCLUDE_USER_RESERVED_MEMORY */

#ifdef INCLUDE_EDR_PM
    else if (memDescType == MEM_DESC_PM_RAM)
        {
        pDesc   = &sysPmMemDesc;
        descCnt = sysPmMemDescCnt;
        }
#endif /* INCLUDE_EDR_PM */
    else
        return (ERROR);

    if (index >= descCnt)
        return (ERROR);

    *pMemDesc = pDesc[index];
    return (OK);
    }

#if (defined(INCLUDE_CACHE_DMA32_LIB) && (DMA32_HEAP_SIZE != 0))        || \
    (defined(INCLUDE_USER_RESERVED_MEMORY) && (USER_RESERVED_MEM != 0)) || \
    (defined(INCLUDE_EDR_PM) && (PM_RESERVED_MEM != 0))
/*******************************************************************************
*
* sysMemDescCarve - carve requested size from physical RAM descriptor table
*
* This routine carves the requested size from the physical RAM descriptor table.
*
* RETURNS: OK, or ERROR if requested size is not less than first RAM bank size.
*/

LOCAL STATUS sysMemDescCarve
    (
    PHYS_MEM_DESC * pMemDesc,   /* destination memory descriptor table  */
    size_t          carveSize   /* size to be craved from source table  */
    )
    {
#ifdef _WRS_CONFIG_UNSUPPORTS_MMU
    size_t  size = carveSize;
#else /* _WRS_CONFIG_UNSUPPORTS_MMU */
    size_t  size = ROUND_UP (carveSize, VM_PAGE_SIZE);
#endif /* !_WRS_CONFIG_UNSUPPORTS_MMU */
#ifdef INCLUDE_CACHE_DMA32_LIB
    PHYS_ADDR ramTop = sysPhysRamDesc[0].physicalAddr + 
                       sysPhysRamDesc[0].len;
#endif /* INCLUDE_CACHE_DMA32_LIB */
    
    if (size >= sysPhysRamDesc[0].len)
        {
        MEM_DESC_MSG ("No enough memory to reserve from Physical RAM\n");
        return (ERROR);
        }
            
    pMemDesc->virtualAddr       = (VIRT_ADDR) MEM_DESC_ADDR_KERNEL_ASSIGNED;
    
#ifdef INCLUDE_CACHE_DMA32_LIB

    if ((pMemDesc == &sysDma32MemDesc) && (ramTop >= CACHE_DMA32_AREA_TOP))
        {
        if (sysPhysRamDesc[0].physicalAddr >= CACHE_DMA32_AREA_TOP)
            {
            MEM_DESC_MSG ("Can not reserve DMA32 area from %p\n",
                           sysPhysRamDesc[0].physicalAddr);
            return (ERROR);
            }

        /* DMA32 area should be lower than 4GB */
        
        pMemDesc->physicalAddr  = CACHE_DMA32_AREA_TOP - size;
        
        /* sysPhysRamDesc[0] is now a new RAM DESC */
        
        sysPhysRamDesc[0].len   = (size_t) (pMemDesc->physicalAddr - 
                                  sysPhysRamDesc[0].physicalAddr);
        
        /* Adding a new RAM DESC sysPhysRamDesc[sysPhysRamDescCnt] */
        
        sysPhysRamDesc[sysPhysRamDescCnt].physicalAddr = CACHE_DMA32_AREA_TOP;
        sysPhysRamDesc[sysPhysRamDescCnt].len = (size_t) (ramTop - 
                                                CACHE_DMA32_AREA_TOP);
        sysPhysRamDesc[sysPhysRamDescCnt].initialState = 
            sysPhysRamDesc[0].initialState;
        sysPhysRamDesc[sysPhysRamDescCnt].initialStateMask = 
            sysPhysRamDesc[0].initialStateMask;
        if (sysPhysRamDesc[0].virtualAddr != MEM_DESC_ADDR_KERNEL_ASSIGNED)
            sysPhysRamDesc[sysPhysRamDescCnt].virtualAddr =
            sysPhysRamDesc[0].virtualAddr + 
            (size_t) (CACHE_DMA32_AREA_TOP - sysPhysRamDesc[0].physicalAddr);
        
        /* Increase RAM DESC count */ 
        
        sysPhysRamDescCnt += 1;
        }
    else
#endif /* INCLUDE_CACHE_DMA32_LIB */
        {
        sysPhysRamDesc[0].len  -= size;
        pMemDesc->physicalAddr  = sysPhysRamDesc[0].physicalAddr + 
                                  sysPhysRamDesc[0].len;
        }
    pMemDesc->len               = size;
    pMemDesc->initialStateMask  = sysPhysRamDesc[0].initialStateMask;
    pMemDesc->initialState      = sysPhysRamDesc[0].initialState;

    return (OK);
    }
#endif


