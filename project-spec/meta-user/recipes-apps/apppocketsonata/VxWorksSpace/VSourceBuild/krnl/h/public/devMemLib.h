/* devMemLib.h - device memory object library header file */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,14jan11,pcs  Add S_devMemLib_INVALID_MMU_ATTR.
01b,09jun10,pcs  Moved errno macros and the ioctl function type macros from
                 devMemLibP.h to here.
01a,05mar10,pcs  written
*/

#ifndef __INCdevMemLibh
#define __INCdevMemLibh

#include <vxWorks.h>
#include <vwModNum.h>
#include <vmLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ioctl function type macros */

#define DEVMEM_SET_DEV_ATTR     ((M_devMemLib>>8) | 1)
#define DEVMEM_GET_DEV_ATTR     ((M_devMemLib>>8) | 2)

/* errno macros */

#define S_devMemLib_PHYS_ADDR_OUT_OF_RANGE (M_devMemLib | 1)
#define S_devMemLib_PHYS_ADDR_NOT_ALIGNED  (M_devMemLib | 2)
#define S_devMemLib_INVALID_SIZE           (M_devMemLib | 3)
#define S_devMemLib_INVALID_MMU_ATTR       (M_devMemLib | 4)

/* typedefs */

typedef struct devMem_dev_attr
    {
    PHYS_ADDR		devPhysAddr;    /* device physical address */
    size_t		size;           /* device memory size bytes */
    MMU_ATTR		mmuAttr;        /* device memory mmu attr */
    } DEVMEM_DEV_ATTR;



/* functional API to the library */

STATUS devMemCreate
    (
    char *      devName,        /* Name associated with device mem mapping. */
    int         options,        /* creation options MAP_SHARED */
    PHYS_ADDR   physAddr,       /* Physical address of memory to be mapped. */
    size_t      len,            /* Size of memory to be mapped. */
    MMU_ATTR    attr            /* allowed MMU attributes. */
    );

int devMemUnlink ( const char * name);

int devMemOpen
    (
    const char * name,          /* object name */
    int          oflag,         /* access control flag */
    mode_t       mode           /* permission mode */
    );

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif /* __INCdevMemLibh */
