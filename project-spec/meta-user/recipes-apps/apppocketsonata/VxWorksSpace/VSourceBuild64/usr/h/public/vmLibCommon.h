/* vmLibCommon.h - Virtual Memory Attribute Information */

/*
 * Copyright (c) 1998-2005,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31may16,ajt  removed MMU_ATTR_SUP_IO* and MMU_ATTR_USR_IO* macros
             (V7COR-1608)
02oct06,jmg  As part of Defect #WIND00041347 repclace typedef enum
             mmu_attributes will all #defines
02sep05,pch  add IS_VALID_CACHEABLE macro for SPR 110099
22oct04,pch  SPR 102912: add #ifndef _ASMLANGUAGE
13sep04,dtr  Use SPL7 for NO_BLOCK attribute.
10jun04,pcs  Rename MMU_ATTR_CACHE_IO MMU_ATTR_CACHE_GUARDED
14may04,pcs  Add MMU_ATTR_SPL_[4-7].
28jan04,gls  created from mmuAttr.h
*/

#ifndef __INCvmLibCommonh
#define __INCvmLibCommonh

#ifdef __cplusplus
extern "C" {
#endif

/* includes */
   
/* defines */

#define MMU_ATTR_SUP_RO	   (MMU_ATTR_PROT_SUP_READ)
#define	MMU_ATTR_SUP_RW	   (MMU_ATTR_PROT_SUP_READ | MMU_ATTR_PROT_SUP_WRITE)
#define	MMU_ATTR_SUP_EXE   (MMU_ATTR_PROT_SUP_READ | MMU_ATTR_PROT_SUP_EXE)
#define	MMU_ATTR_SUP_RWX   (MMU_ATTR_SUP_RW 	   | MMU_ATTR_PROT_SUP_EXE)

#define MMU_ATTR_USR_RO	   (MMU_ATTR_PROT_USR_READ)
#define	MMU_ATTR_USR_RW	   (MMU_ATTR_PROT_USR_READ | MMU_ATTR_PROT_USR_WRITE)
#define	MMU_ATTR_USR_EXE   (MMU_ATTR_PROT_USR_READ | MMU_ATTR_PROT_USR_EXE)
#define	MMU_ATTR_USR_RWX   (MMU_ATTR_USR_RW        | MMU_ATTR_PROT_USR_EXE)

#define	MMU_ATTR_SUP_TEXT	(MMU_ATTR_SUP_EXE)
#define	MMU_ATTR_SUP_TEXT_W	(MMU_ATTR_SUP_RWX)
#define	MMU_ATTR_SUP_DATA	(MMU_ATTR_SUP_RW) 
#define	MMU_ATTR_SUP_DATA_RO	(MMU_ATTR_SUP_RO) 

#define	MMU_ATTR_USR_TEXT	(MMU_ATTR_USR_EXE | MMU_ATTR_SUP_TEXT)
#define	MMU_ATTR_USR_TEXT_W	(MMU_ATTR_USR_RWX | MMU_ATTR_SUP_TEXT_W)
#define	MMU_ATTR_USR_DATA	(MMU_ATTR_USR_RW  | MMU_ATTR_SUP_DATA)
#define	MMU_ATTR_USR_DATA_RO	(MMU_ATTR_USR_RO  | MMU_ATTR_SUP_DATA_RO)

/* Special attribute rename */
#define MMU_ATTR_NO_BLOCK       (MMU_ATTR_SPL_7)

/* typedefs */

#ifndef _ASMLANGUAGE
typedef unsigned int MMU_ATTR;
#endif /* _ASMLANGUAGE */

#define MMU_ATTR_MSK_ID_MSK      0x000000e0    /* Distinguishing Bits Mask */
#define MMU_ATTR_PROT_MSK        0x0000003f    /* Protection Mask */
#define MMU_ATTR_PROT_SUP_MSK	 0x00000007    /* Sup Mode protection bits */
#define MMU_ATTR_PROT_SUP_READ	 0x00000001    /* Supervisor -- Read */
#define MMU_ATTR_PROT_SUP_WRITE	 0x00000002    /* Supervisor -- Write */
#define MMU_ATTR_PROT_SUP_EXE	 0x00000004    /* Supervisor -- Execute */
#define MMU_ATTR_PROT_USR_MSK	 0x00000038    /* User Mode protection bits */
#define MMU_ATTR_PROT_USR_READ	 0x00000008    /* User -- Read	*/
#define MMU_ATTR_PROT_USR_WRITE	 0x00000010    /* User -- Write */
#define MMU_ATTR_PROT_USR_EXE	 0x00000020    /* User -- Execute */
#define MMU_ATTR_VALID_MSK       0x00000040    /* Valid Mask */
#define MMU_ATTR_VALID_NOT       0x00000000    /* Valid -- Not Valid */
#define MMU_ATTR_VALID           0x00000040    /* Valid -- Valid */
#define MMU_ATTR_CACHE_MSK       0x00000f80    /* Cache Mask */
#define MMU_ATTR_CACHE_OFF       0x00000080    /* Cache -- Turned off */ 
#define MMU_ATTR_CACHE_COPYBACK  0x00000100    /* Cache -- Copy/Writeback */ 
#define MMU_ATTR_CACHE_WRITETHRU 0x00000180    /* Cache -- Write through */     
#define MMU_ATTR_CACHE_COHERENCY 0x00000200    /* Cache -- mem coherency */ 
#define MMU_ATTR_CACHE_GUARDED   0x00000400    /* Cache -- guarded */    
#define MMU_ATTR_CACHE_DEFAULT	 0x00000800    /* Cache -- use default */
#define MMU_ATTR_SPL_MSK         0x000FF000    /* MMU specific spl attributes */
#define MMU_ATTR_SPL_0           0x00001000 
#define MMU_ATTR_SPL_1           0x00002000 
#define MMU_ATTR_SPL_2           0x00004000 
#define MMU_ATTR_SPL_3           0x00008000 
#define MMU_ATTR_SPL_4           0x00010000 
#define MMU_ATTR_SPL_5           0x00020000 
#define MMU_ATTR_SPL_6           0x00040000 
#define MMU_ATTR_SPL_7           0x00080000  /* Reserved - used for NO_BLOCK */  

/*
 * In principle, a region in sysPhysMemDesc is cacheable if its mask includes
 * specification of validity and cacheability, and the specifications are:
 *       valid
 *   and not cache-off
 *   and one of copyback, writethrough, or default.
 * Due to the relationships among the OFF, CB, and WT bit values,
 * we check for only CB or DEFAULT.
 */
#define	IS_VALID_CACHEABLE(mask, attr)					    \
    (									    \
       ((mask) & MMU_ATTR_VALID_MSK) == MMU_ATTR_VALID_MSK		    \
    && ((mask) & MMU_ATTR_CACHE_MSK) == MMU_ATTR_CACHE_MSK		    \
    && ((attr) & MMU_ATTR_VALID) == MMU_ATTR_VALID			    \
    && ((attr) & (MMU_ATTR_CACHE_COPYBACK | MMU_ATTR_CACHE_DEFAULT)) != 0   \
    )


/* variable declarations */

/* function prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __INCvmLibCommonh */
