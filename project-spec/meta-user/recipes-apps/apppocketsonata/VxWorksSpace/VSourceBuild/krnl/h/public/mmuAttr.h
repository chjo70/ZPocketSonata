/* mmuAttr.h - Memory Attribute Information */

/*
 * Copyright (c) 1998-2000, 2003-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01l,27may10,pad  Moved extern C statement after include statements.
01k,28jan04,gls  added include of vmLibCommon.h
01j,19sep03,pcs  Change enumeration value from 16 bit to 32 bit.
01i,24jul03,gls  Ported to Base 6
01h,17jan00,map  removed RGN_TYPE and PHYS_REGION
01g,12nov99,tam  define VIRT_ADDR if not already defined
01f,09nov99,tam  renamed RGN_MAP_ONE_TO_ONE to RGN_MAP_LINEAR,
                 updated PHYS_REGION to include virtual address field.
01e,04aug99,gls  restructured the page attributes
01d,06may99,gls  renamed file from memAttr.h to mmuAttr.h
01c,27jan99,map  added RGN_MAP entries.
01b,21jan99,map  moved PHYS_REGION definition from memInfo.h
01a,16nov98,map  written.
*/

#ifndef __INCmmuAttrh
#define __INCmmuAttrh

/* includes */

#include <vmLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif
   
/* defines */

#define	MMU_ATTR_PROT_GET(attr)		((attr) & MMU_ATTR_PROT_MSK)	    
#define MMU_ATTR_PROT_USR_GET(attr)	((attr) & MMU_ATTR_PROT_USR_MSK)
#define	MMU_ATTR_PROT_SUP_GET(attr)	((attr) & MMU_ATTR_PROT_SUP_MSK)
#define	MMU_ATTR_CACHE_GET(attr)	((attr) & MMU_ATTR_CACHE_MSK)
#define	MMU_ATTR_VALID_GET(attr)	((attr) & MMU_ATTR_VALID_MSK)
#define	MMU_ATTR_SPL_GET(attr)		((attr) & MMU_ATTR_SPL_MSK)
#define MMU_ATTR_MSK_ID_GET(mask)       ((mask) & MMU_ATTR_MSK_ID_MSK)

#define	MMU_ATTR_PROT_USR_TO_SUP(attr)	(((attr) & MMU_ATTR_PROT_USR_MSK) >> 3)
#define	MMU_ATTR_PROT_SUP_TO_USR(attr)	(((attr) & MMU_ATTR_PROT_SUP_MSK) << 3)

/*
 * The following macros do not necessarily belong in this file given their
 * use, which should be limited strictly to vmlib.c.  They have been
 * placed here because they are dependent upon the values defined here. 
 * This will help to prevent inconsistancies.
 */

#define MMU_ATTR_PROT_INDEX_SHIFT  1     /* used by vmLib */
#define MMU_ATTR_CACHE_INDEX_SHIFT 7     /* used by vmLib */
#define MMU_ATTR_VALID_INDEX_SHIFT 6     /* used by vmLib */
#define MMU_ATTR_MSK_INDEX_SHIFT   5     /* used by vmLib */

#define MMU_ATTR_PROT_STATE_NUM    32     /* used by vmLib */
#define MMU_ATTR_CACHE_STATE_NUM   16     /* used by vmLib */
#define MMU_ATTR_VALID_STATE_NUM   2      /* used by vmLib */

/* typedefs */

/* function prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuAttrh */
