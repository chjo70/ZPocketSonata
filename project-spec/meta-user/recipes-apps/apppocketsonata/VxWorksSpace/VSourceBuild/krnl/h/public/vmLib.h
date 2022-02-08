/* vmLib.h - header for architecture independent mmu interface */

/* 
 * Copyright (c) 1984-2005, 2007, 2009-2010, 2014-2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
29jul15,pcs  Made vmPageLock() and vmPageUnlock()() not supported for CERT.
01mar15,ymz  fixed flexelint warning
01aug14,jmz  V7PRO-1118 - add Intel Write Combining Option
05nov10,zl   add deprecation warning to vmPhysTranslate(), removed it 
                 from 64-bit.
29apr10,pad  Moved extern C statement after include statements.
25aug09,zl   added vmPageUnmap() declaration.
21apr09,zl   LP64 updates. Replaced msize_t with size_t.
20jul07,j_b  re-assign VM_STATE_BUFFERABLE for ARMARCH6
02may07,zl   introduced msize_t.
06mar07,pcs  Add prototype for vmPageMap.
11aug05,zl   move init routines to future non-public section.
07jul05,zl   added no-alias error codes.
15apr05,zl   added S_vmLib_FUNCTION_UNSUPPORTED.
07feb05,zl   removed inclusion of private header files
22oct04,pch  SPR 102912: add #ifndef _ASMLANGUAGE
14oct04,pcs  Change VM_STATE_GUARDED_NOT & VM_STATE_MEM_COHERENCY_NOT from
             MMU_ATTR_CACHE_DEFAULT to 0.
30sep04,rlg  undo false checkin - return cache state bits to proper
             settings
12oct04,pcs  Remove protectSemId from struct vm_context, since it is not
             being used.
29sep04,pcs  Change VM_STATE_CACHEABLE,VM_STATE_MEM_COHERANCY_NOT &
             VM_STATE_GUARDED_NOT from MMU_ATTR_CACHE_COPYBACK to
             VM_ATTR_CACHE_DEFAULT.
11jun04,pcs  Rename MMU_ATTR_CACHE_IO to MMU_ATTR_CACHE_GUARDED.
11may04,tam  added S_vmLib_KERNEL_TEXT_NOT_ALIGNED
03may04,pcs  Add prototypes for optimize/lock/unlock .
17dec03,zmm  Change VM_STATE_WBACK definitions.
26sep03,scm  fix for vmLib prototypes...
17sep03,scm  x-bit support...
04sep03,pcs  Add SEM_ID protectSemId; to struct vm_context.
09jul03,pcs  change physicalAddr to type PHYS_ADDR from void *
08may03,pes  PAL conditional compilation cleanup. Phase 2.
14mar03,dcc  moved VM_CONTEXT_ID definition to types/vxWind.h
26jul01,scm  add extended small page table support for XScale...
13nov98,jpd  added vmMpuLib routine definitions and new error numbers.
09apr98,hdn  added support for Pentium and PentiumPro.
09mar98,jpd  added extra ARM VM_STATEs.
28nov96,jpd  added comment about VM_STATE_CACHEABLE_WRITETHROUGH for
             ARM710A as well as MC68040.
01jan96,tpr  changed value of the PPC specific macro.
18sep95,tpr  added VM_STATE_MASK_MEM_COHERENCY, VM_STATE_MASK_GUARDED,
             VM_STATE_MASK_GUARDED and VM_STATE_MASK_EXECUTE for powerPc.
26jul94,tpr  added VM_STATE_CACHEABLE_NOT_IMPRECISE for MC68060.
09feb93,rdc  added prototypes for vmBaseStateSet and vmBasePageSizeGet;
19oct92,pme  replaced _STDC__ by __STDC__.
19oct92,jcf  cleanup. added vmContextDelete() prototype.
22sep92,rrr  added support for c++
22sep92,rdc  changed prototype for vmGlobalInfoGet.
             Added prototype for vmPageBlockSizeGet.
             Added support for sun1e.
30jul92,rdc  added prototype for vmContextShow.
28jul92,rdc  added non-ansi function prototypes and prototypes for 
             vmBaseLib.c and vmShow.c.
13jul92,rdc  moved private data structures to vmLibP.h.
09jul92,rdc  added VM_LIB_INFO and PHYS_MEM_DESC.
08jul92,rdc  written.
*/

#ifndef __INCvmLibh
#define __INCvmLibh

#include <vxWorks.h>
#include <mmuLib.h>
#include <mmuAttr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_vmLib_NOT_PAGE_ALIGNED		(M_vmLib | 1)
#define S_vmLib_BAD_STATE_PARAM			(M_vmLib | 2)
#define S_vmLib_BAD_MASK_PARAM			(M_vmLib | 3)
#define S_vmLib_ADDR_IN_GLOBAL_SPACE		(M_vmLib | 4)
#define S_vmLib_TEXT_PROTECTION_UNAVAILABLE	(M_vmLib | 5)
#define S_vmLib_KERNEL_TEXT_NOT_ALIGNED		(M_vmLib | 6)
#define S_vmLib_FUNCTION_UNSUPPORTED		(M_vmLib | 7)
#define S_vmLib_PHYS_PAGES_ALREADY_MAPPED	(M_vmLib | 8)
#define S_vmLib_NOALIAS_SUPPORT_NOT_INCLUDED	(M_vmLib | 9)

/*
 * The VM_STATE_XXX macros have been redefined to use the MMU_ATTR_XXX 
 * macros defined in vmLibCommon.h; use of the VM_STATE_XXX macros should 
 * be avoided.
 */

#define VM_STATE_MASK_VALID		MMU_ATTR_VALID_MSK
#define VM_STATE_MASK_WRITABLE		MMU_ATTR_PROT_MSK
#define VM_STATE_MASK_CACHEABLE		MMU_ATTR_CACHE_MSK

#define VM_STATE_VALID			MMU_ATTR_VALID
#define VM_STATE_VALID_NOT		MMU_ATTR_VALID_NOT
#define VM_STATE_WRITABLE		MMU_ATTR_SUP_RWX
#define VM_STATE_WRITABLE_NOT		(MMU_ATTR_PROT_SUP_READ | \
					 MMU_ATTR_PROT_SUP_EXE)
#define VM_STATE_CACHEABLE		MMU_ATTR_CACHE_DEFAULT
#define VM_STATE_CACHEABLE_NOT		MMU_ATTR_CACHE_OFF
#define VM_STATE_CACHEABLE_WRITETHROUGH	MMU_ATTR_CACHE_WRITETHRU

/* additional cache states for PowerPC arch. */

#define VM_STATE_MASK_MEM_COHERENCY	MMU_ATTR_CACHE_MSK
#define VM_STATE_MEM_COHERENCY		MMU_ATTR_CACHE_COHERENCY
#define VM_STATE_MEM_COHERENCY_NOT	0

#define VM_STATE_MASK_GUARDED		MMU_ATTR_CACHE_MSK
#define VM_STATE_GUARDED		MMU_ATTR_CACHE_GUARDED
#define VM_STATE_GUARDED_NOT		0

/* additional cache states for i86 arch */

#define VM_STATE_WBACK                  MMU_ATTR_CACHE_COPYBACK     
#define VM_STATE_WBACK_NOT              MMU_ATTR_CACHE_WRITETHRU    

#define VM_STATE_MASK_WBACK		VM_STATE_MASK_MEM_COHERENCY 
#define VM_STATE_MASK_GLOBAL		MMU_ATTR_SPL_MSK	    
#define VM_STATE_GLOBAL			MMU_ATTR_SPL_0   	    
#define VM_STATE_GLOBAL_NOT		0               	    

#if ((CPU_FAMILY == I80X86) && (_VX_CPU != _VX_PENTIUM))
/* Write Combine attribute */

#define VM_STATE_MASK_WCOMBINE          MMU_ATTR_SPL_MSK
#define VM_STATE_WCOMBINE               MMU_ATTR_SPL_1
#define VM_STATE_WCOMBINE_NOT           0
#endif /* (CPU_FAMILY == I80X86 && _VX_CPU != _VX_PENTIUM) */

/* additional cache states for ARM/XScale arch. */

#if (CPU == ARMARCH6)

#define VM_STATE_MASK_BUFFERABLE	(MMU_ATTR_CACHE_MSK)
#define VM_STATE_BUFFERABLE		(MMU_ATTR_CACHE_GUARDED | \
                           		 MMU_ATTR_CACHE_OFF)  /* Cache I/O */
#define VM_STATE_BUFFERABLE_NOT		0x00

#else

#define VM_STATE_MASK_BUFFERABLE	(MMU_ATTR_CACHE_MSK | MMU_ATTR_SPL_MSK)
#define VM_STATE_BUFFERABLE		(MMU_ATTR_SPL_0)
#define VM_STATE_BUFFERABLE_NOT		0x00

#endif /* CPU == ARMARCH6 */

#if (CPU == XSCALE)

#define VM_STATE_MASK_EX_CACHEABLE      (MMU_ATTR_CACHE_MSK | MMU_ATTR_SPL_MSK)
#define VM_STATE_NO_COALESCE		(MMU_ATTR_SPL_2 | MMU_ATTR_CACHE_OFF)
#define VM_STATE_WRITEALLOCATE		(MMU_ATTR_SPL_3 | MMU_ATTR_CACHE_COPYBACK)
#define VM_STATE_CACHEABLE_MINICACHE	(MMU_ATTR_SPL_1) 
#define VM_STATE_EX_CACHEABLE_NOT	0x00

/* backwards compatability for vxWorks 5.5 */

#define VM_STATE_MASK_EX_BUFFERABLE	VM_STATE_MASK_EX_CACHEABLE
#define VM_STATE_EX_BUFFERABLE		VM_STATE_NO_COALESCE
#define VM_STATE_EX_CACHEABLE		VM_STATE_WRITEALLOCATE
#define VM_STATE_EX_BUFFERABLE_NOT	VM_STATE_EX_CACHEABLE_NOT

#else

/* additional cache states for ARM SA-1100 */

#define VM_STATE_CACHEABLE_MINICACHE	0x30	

#endif /* CPU == XSCALE */


#ifndef	_ASMLANGUAGE

/*
 * physical memory descriptor is used to map virtual memory in sysLib 
 * and usrConfig.
 */

typedef struct phys_mem_desc
    {
    VIRT_ADDR	virtualAddr;		/* block virtual address */
    PHYS_ADDR	physicalAddr;		/* block physical address */
    size_t	len;			/* block length */
    UINT	initialStateMask;	/* mask parameter to vmStateSet */
    UINT	initialState;		/* state parameter to vmStateSet */
    } PHYS_MEM_DESC;

typedef size_t msize_t;			/* for migration purpose only */

IMPORT PHYS_MEM_DESC sysPhysMemDesc[];
IMPORT int sysPhysMemDescNumEnt;


/* function declarations */

extern STATUS	vmStateSet (VM_CONTEXT_ID context, VIRT_ADDR pVirtual,
			    size_t len, UINT stateMask, UINT state);
extern STATUS	vmStateGet (VM_CONTEXT_ID context, VIRT_ADDR pageAddr,
			    UINT *state);
extern STATUS	vmMap (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr,
		       PHYS_ADDR physicalAddr, size_t len);
extern STATUS	vmPageMap (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr,
			   PHYS_ADDR physicalAddr, size_t len, UINT stateMask,
			   UINT state);
extern STATUS	vmPageUnmap (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr,
			     size_t numBytes);
extern STATUS	vmTranslate (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr,
			     PHYS_ADDR *physicalAddr);
#ifndef _WRS_CONFIG_LP64
extern STATUS	vmPhysTranslate (VM_CONTEXT_ID context, PHYS_ADDR physicalAddr,
				 VIRT_ADDR *virtualAddr )
    _WRS_DEPRECATED("Please see vmPhysTranslate() reference guide for details");
#endif
extern size_t	vmPageSizeGet (void);
extern STATUS	vmTextProtect (BOOL setState);
extern STATUS	vmBufferWrite (VM_CONTEXT_ID vmCtx, VIRT_ADDR fromAddr,
			       VIRT_ADDR toAddr, size_t nbBytes);
extern STATUS	vmPageOptimize (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr, 
				size_t len, UINT option);
#ifndef _WRS_CONFIG_CERT
extern STATUS	vmPageLock (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr,
			    size_t len, UINT option);
extern STATUS	vmPageUnlock (VM_CONTEXT_ID context, VIRT_ADDR virtualAddr);
#endif
extern STATUS	vmContextShow (VM_CONTEXT_ID context);
extern STATUS	vmAttrShow (UINT mmuAttr, UINT mmuAttrMask);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvmLibh */
