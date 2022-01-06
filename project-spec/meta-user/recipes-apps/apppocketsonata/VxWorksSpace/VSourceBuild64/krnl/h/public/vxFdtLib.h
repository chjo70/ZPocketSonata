/* vxFdtLib.h -  VxWorks FDT library defines */

/*
 * Copyright (c) 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11nov14,ymz  made FDT_DBG_MSG void as required by CERT
02mar16,wap  Add vxFirstPropGet() and vxNextPropGet()   
26aug15,ggm  added vxFdtDisable (US65468)
19jun14,x_z  added vxFdtPhysMemInfoGet(). (V7PRO-768)
01mar14,my_  add vxFdtDtbAddressGet (US35020, bootapp part)
06aug13,x_z  Created.
*/

#ifndef __INCvxFdtLibh
#define __INCvxFdtLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <private/kwriteLibP.h> /* _func_kprintf */
#include <vmLib.h>

#ifdef DEBUG
#define FDT_DBG_MSG(fmt, args...)                   \
    do                                              \
        {                                           \
        if (_func_kprintf != NULL)                  \
            _func_kprintf (fmt, ##args);    \
        } while (FALSE);
#else
#define FDT_DBG_MSG(fmt, args...)
#endif /* DEBUG */

/*
 * Every node has one node name as the following convention:
 *      node-name@unit-address
 *
 * Note that the unit-address must match the first address specified in <reg>
 * property of the node, and must be omitted if there is no <reg> property for
 * the node.
 */

/*
 * maximum length of FDT node name, not that EOS and the unit address length is
 * not calculated in the length.
 */

#define FDT_NODE_NAME_LEN   31

/*
 * A device tree must and can only have one root node, and must have the
 * following node in the root node:
 *  1. one cpus node;
 *  2. one memory node at least.
 */

/*
 * A new binding could be created only if no any similiar binding could be found
 * in the existed DTS files used by VxWorks or other popular OS, but the
 * following rules must be followed:
 *  1. <compatible> property should be included;
 *  2. The following standard properties should be used as much as possible;
 *  3. The similiar existed properties should be used as much as possible;
 *  4. The new property should be named as "wrs,<property nmae>" if a new
 *  property is necessary.
 */

/* address/size cells define */

#define FDT_ADRS_CELLS_DEF      2
#define FDT_SIZE_CELLS_DEF      1

/* status defines */

#define FDT_DEV_STA_NAME        "status"
#define FDT_DEV_STA_OK          "okay"      /* device is operational */

/*
 * Device is not presently operational, such as not plugged in or switched off,
 * but it might become operational.
 */

#define FDT_DEV_STA_DIS         "disabled"

/*
 * Device is not operational because of one serious error and unlikely to become
 * operational without repair.
 */

#define FDT_DEV_STA_FAIL        "fail"

/*
 * Device is not operational because of one device specified serious error and
 * unlikely to become operational without repair. The string format should be
 * "fail-sss", that "sss" is just the device specified serious error.
 */

#define FDT_DEV_STA_FAIL_SSS    "fail-"

/* device type define */

/* FC Code */

#define FDT_DEVTYPE_DISP        "display"
#define FDT_DEVTYPE_BLK         "block"     /* mass storage devices */
#define FDT_DEVTYPE_BYTE        "byte"      /* sequential-access mass storage */
                                            /* devices */
#define FDT_DEVTYPE_NET         "network"
#define FDT_DEVTYPE_SERIAL      "serial"

#define VX_FDT_CHILD(offset)    vxFdtFirstSubnode(offset)
#define VX_FDT_PEER(offset)     vxFdtNextSubnode(offset)

/* device match entry */

typedef struct fdtMemInfo
    {
    UINT64  uStartAdrs; /* start address */
    size_t  size;       /* size */
    } FDT_MEM_INFO;


/* FDT library initialization routine */

IMPORT STATUS vxFdtLibInit
    (
    void *  pDtbSrc,     /* pointer to DTB */
    void *  pDtbReloc,   /* pointer to DTB relocation buffer  */
    UINT32  uDtbMaxLen   /* maximum length of DTB */
    );

/* basic functions */

IMPORT UINT16 vxFdt16ToCpu(UINT16 val);
IMPORT UINT16 vxCpuToFdt16(UINT16 val);
IMPORT UINT32 vxFdt32ToCpu(UINT32 val);
IMPORT UINT32 vxCpuToFdt32(UINT32 val);
IMPORT UINT64 vxFdt64ToCpu(UINT64 val);
IMPORT UINT64 vxCpuToFdt64(UINT64 val);

IMPORT int vxFdtPathOffset (char * pPath);
IMPORT int vxFdtNextNode (int offset, int *depth);
IMPORT int vxFdtParentOffset (int offset);
IMPORT int vxFdtFirstSubnode (int offset);
IMPORT int vxFdtNextSubnode (int offset);
IMPORT const void * vxFdtGetName(int offset ,int * pLen);
IMPORT const void * vxFdtPropGet(int offset, char * pPropName, int * pLen);
IMPORT const void * vxFdtFirstPropGet(int offset, char ** pPropName, int * pLen, int * propOffset);
IMPORT const void * vxFdtNextPropGet(int offset, char ** pPropName, int * pLen, int * propOffset);
IMPORT int  vxFdtPropSet (int offset, char * pPropName, void * val, int pLen);
IMPORT int vxFdtNodeOffsetByPhandle(UINT32  phandle);
IMPORT int vxFdtNodeOffsetByCompatible(int startoffset, char *compatible);
IMPORT int vxFdtNodeCheckCompatible(int offset, char *compatible);

IMPORT STATUS vxFdtCellGet(int  offset, int *pAdrsCell, int *pSizeCell);

/* FDT device default register map routine (no address flag) */

IMPORT STATUS vxFdtDefRegGet
    (
    int          offset,      /* start node offset */
    UINT32       barIndx,     /* bar index */
    PHYS_ADDR *  pRegBarAddr, /* register address */
    size_t *     pRegBarSize  /* register size */
    );

/* FDT device default DMA address map routine (no address flag) */

IMPORT STATUS vxbFdtDevDefDmaMap
    (
    int             nodeOffset,     /* node offset */
    ULONG           uDmaAdrs,
    ULONG *         pMappedAdrs
    );

/* FDT memory information obtain routine */

IMPORT STATUS vxFdtMemInfoGet
    (
    FDT_MEM_INFO *  pMemInfo,
    UINT32          uMaxBanks
    );

IMPORT BOOL vxFdtIsEnabled
    (
    int             offset
    );

IMPORT STATUS vxFdtDisable
    (
    int             offset
    );

/* FDT stdout obtain routine */

IMPORT int vxFdtStdoutGet(void);

/* FDT physical memory information obtain routine */

IMPORT int vxFdtPhysMemInfoGet
    (
    PHYS_MEM_DESC * pPhysMemDesc,
    int             physMemDescNum,
    UINT            uState
    );

/* FDT bootargs obtain routine */

IMPORT STATUS vxFdtBootargsGet
    (
    char *  pString,    /* where to copy bootargs           */
    int     strLen      /* maximum number of bytes to copy  */
    );

IMPORT void * vxFdtDtbAddressGet(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxFdtLibh */

