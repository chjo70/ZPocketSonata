/* devMemLibP.h - device memory object private header */

/* 
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,09jun10,pcs  Move the errno macros and the ioctl function type macros to
                 devMemLib.h.
01a,05mar10,pcs  created.
*/

#ifndef __INCdevMemLibPh
#define __INCdevMemLibPh

/* includes */

#include <vxWorks.h>
#include <vmLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEVMEM_DEFAULT_ATTR (MMU_ATTR_SUP_RW | MMU_ATTR_USR_RW | \
                             MMU_ATTR_VALID | MMU_ATTR_CACHE_DEFAULT)

#define DEVMEM_ATTR_MASK    (MMU_ATTR_PROT_MSK | MMU_ATTR_VALID_MSK | \
                             MMU_ATTR_SPL_MSK)

#ifndef _ASMLANGUAGE

/* typedefs */

/* globals */


/* base level function prototypes */

STATUS devMemFsLibInit (const char * devName);
STATUS devMemFullNameGet (const char * name, char * fullName);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdevMemLibPh */
