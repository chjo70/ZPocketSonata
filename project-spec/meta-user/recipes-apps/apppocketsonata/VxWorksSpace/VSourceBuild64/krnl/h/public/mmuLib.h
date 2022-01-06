/* mmuLib.h - mmuLib header file */

/*
 * Copyright (c) 1984-2004, 2009, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03sep15,h_k  moved S_mmuLib_INVALID_XXX macros to mmuLib.h. (V7COR-3487)
16jul10,scm  add errno for already mapped address...
23jun10,scm  add errno for invalid phys addr... WIND00217705
20jan09,jb   Adding 64-bit support
15nov04,h_k  renamed mmuSh7750LibInit to mmuShLibInit. removed
             mmuSh7700LibInit.
22oct04,pch  SPR 102912: add #ifndef _ASMLANGUAGE
29sep04,pcs  Update the prototype of mmuPpcLibInit to use 2 more
             parameters.
06aug04,sru  Add S_mmulib_LOCK_REQUIRED errno.
06jul04,dtr  Add in errno values for aimMmu to fix SPR 98263.
20jan03,jb   Resolving SPR 79707
01mar00,frf  Add SH4 support for T2.
28aug98,st   added prototype for mmuSh7750LibInit.
15nov96,wt   added prototype for mmuSh7700LibInit.
20jan99,cdp  removed support for old ARM libraries.
12nov98,cdp  removed prototype mmuLibInit() for new ARM architectures.
09apr98,hdn  added PentiumPro support.
19sep95,tpr  added prototype mmuPpcLibInit() for PowerPC.
24nov93,hdn  added prototype mmuLibInit() for I80X86.
02dec93,pme  added Am29K family support.
01oct92,jcf  rolled out 01g to remove warnings.
27sep92,kdl  deleted prototypes for mmu1eLibInit, mmu30LibInit, mmu40LibInit
22sep92,rrr  added support for c++
22sep92,rdc  added support for sun1e.
17sep92,rdc  added prototypes and errors for sun1e.
30jul92,rdc  added prototypes for mmu30LibInit and mmu40LibInit.
28jul92,rdc  removed superfluous function prototypes.
08jul92,rdc  written.
*/

#ifndef __INCmmuLibh
#define __INCmmuLibh

#ifdef __cplusplus
extern "C" {
#endif

#define	S_mmuLib_INVALID_PAGE_SIZE		(M_mmuLib | 1)
#define	S_mmuLib_NO_DESCRIPTOR			(M_mmuLib | 2)
#define	S_mmuLib_INVALID_DESCRIPTOR		(M_mmuLib | 3)

/* sun4 specific codes */

#define	S_mmuLib_OUT_OF_PMEGS			(M_mmuLib | 5)

/* virtual addresses must be in the first or last 1/2 Gibabyte of
 * virtual address space
 */

#define	S_mmuLib_VIRT_ADDR_OUT_OF_BOUNDS	(M_mmuLib | 6)

/* additional errno required by aim */
/* Trying to change state of locked page or lock again is illegal */
#define	S_mmuLib_TLB_LOCKED_PAGE		(M_mmuLib | 7)
/* Trying to unlock a region which is not locked is an error */
#define	S_mmuLib_TLB_PAGE_NOT_LOCKED		(M_mmuLib | 8)
#define S_mmuLib_LOCK_NO_MORE_TLB_RESOURCES     (M_mmuLib | 9)

/* Cannot optimize or lock a non contiguous phys addr or state*/
#define S_mmuLib_NOT_CONTIGUOUS_ADDR            (M_mmuLib | 10)
#define S_mmuLib_NOT_CONTIGUOUS_STATE           (M_mmuLib | 11)

/* Cannot optimize or lock a page marked as ISR callable */
/* Cannot change state of page in ISR unless marked */
#define	S_mmuLib_ISR_CALL_BLOCKED		(M_mmuLib | 12)
#define S_mmuLib_MARKED_ISR_CALLABLE            (M_mmuLib | 13)

/* Illegal to lock a non global page */
#define S_mmuLib_NOT_GLOBAL_PAGE                (M_mmuLib | 15)

/* Illegal to unlock a region required by the vxWorks kernel */
#define S_mmulib_LOCK_REQUIRED			(M_mmuLib | 16)

/* Invalid physical address */
#define S_mmulib_INVALID_PHYS_ADDR		(M_mmuLib | 17)

/* Already mapped address */
#define S_mmulib_VIRT_ADDR_ALREADY_MAPPED	(M_mmuLib | 18)

/* Invalid union initialization */
#define S_mmuLib_INVALID_UNION_INIT		(M_mmuLib | 19)

/* Invalid MMU attribute */
#define S_mmuLib_INVALID_ATTR			(M_mmuLib | 20)

/* Invalid global mapping operation */
#define S_mmuLib_INVALID_GLOBAL_PAGE_OP		(M_mmuLib | 21)


#ifndef	_ASMLANGUAGE
typedef struct mmuTransTblStruct * MMU_TRANS_TBL_ID;

#if defined(__STDC__) || defined(__cplusplus)

STATUS mmu30LibInit (int pageSize);
STATUS mmu40LibInit (int pageSize);
STATUS mmu1eLibInit (int pageSize);
#if (CPU_FAMILY != ARM)
STATUS mmuLibInit (int pageSize);
#endif
STATUS mmuPro32LibInit (int pageSize);
STATUS mmuPro36LibInit (int pageSize);
STATUS mmuX86_64LibInit (int pageSize);
STATUS mmuAm29kLibInit (int pageSize);
STATUS mmuPpcLibInit (int mmuType, int * pPhysMemDesc, int elementNb, int *,
                      void * hashTableStartAddr,u_int hashTableSize);
STATUS mmuShLibInit (int pageSize);

#else	/* __STDC__ */

STATUS mmu30LibInit ();
STATUS mmu40LibInit ();
STATUS mmu1eLibInit ();
#if (CPU_FAMILY != ARM)
STATUS mmuLibInit ();
#endif
STATUS mmuPro32LibInit ();
STATUS mmuPro36LibInit ();
STATUS mmuX86_64LibInit ();
STATUS mmuAm29kLibInit ();
STATUS mmuPpcLibInit ();
STATUS mmuShLibInit ();

#endif	/* __STDC__ */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuLibh */
