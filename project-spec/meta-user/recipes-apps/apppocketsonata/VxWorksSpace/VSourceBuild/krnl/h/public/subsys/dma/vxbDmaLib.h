/* vxbDmaLib.h - vxbus DMA interfaces header file */

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
25dec15,l_z  added vxBus.h. (V7PRO-2617)
04nov15,sye  added declaration of vxbDmaChanConfig() (V7PRO-2550)
13jul15,y_f  added advanced method for allocating channel. (V7PRO-1679)
22feb14,y_f  change srcAddrWidth and destAddrWidth from UINT8 to UINT32
08jan14,sye  added dmaEvent for VXB_DMA_SLAVE_CONFIG.
29nov13,l_z  written
*/

/*
DESCRIPTION
This library provides the DMA specific interfaces
*/

#ifndef _INC_vxbDmaLibH
#define _INC_vxbDmaLibH

/* includes */

#include <vxWorks.h>
#include <lstLib.h>
#include <sllLib.h>
#include <hwif/vxBus.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * enum dma_slave_buswidth - defines bus with of the DMA slave
 * device, source or target buses
 */

#define VXB_DMA_BUSWIDTH_UNDEFINED  0
#define VXB_DMA_BUSWIDTH_1_BYTE     1
#define VXB_DMA_BUSWIDTH_2_BYTES    2
#define VXB_DMA_BUSWIDTH_4_BYTES    4
#define VXB_DMA_BUSWIDTH_8_BYTES    8

/*
 * Note: The capability is not to be set by drivers.  It is
 * automatically set as dma devices are registered.
 */

#define VXB_DMA_MEMCPY          0x1
#define VXB_DMA_INTERRUPT       0x2
#define VXB_DMA_SG              0x4

/* when no need to set dmaEvent in VXB_DMA_SLAVE_CONFIG */

#define VXB_DMA_EVENT_INVALID   (-1)

#define VXB_DMA_CHAN_INVALID    (-1)

typedef enum vxbDmaTransDir {
    VXB_DMA_MEM_TO_MEM,
    VXB_DMA_MEM_TO_DEV,
    VXB_DMA_DEV_TO_MEM,
    VXB_DMA_DEV_TO_DEV
} VXB_DMA_TRANS_DIR;

typedef enum vxbDmaCtrlCmd {
    VXB_DMA_TERMINATE_ALL,
    VXB_DMA_PAUSE,
    VXB_DMA_RESUME,
    VXB_DMA_CONFIG
} VXB_DMA_CTRL_CMD;

typedef struct vxbDmaSlaveConfig {
    VXB_DMA_TRANS_DIR direction;
    VIRT_ADDR         src;
    VIRT_ADDR         dest;
    UINT32            srcAddrWidth;
    UINT32            destAddrWidth;
    UINT32            srcMaxBurst;
    UINT32            destMaxBurst;
    int               dmaEvent;
    UINT32            txFrame;
} VXB_DMA_SLAVE_CONFIG;

typedef void (* VXB_DMA_COMPLETE_FN)(void * pArg);

typedef struct vxbDmaTx VXB_DMA_TX;

typedef STATUS (* VXB_DMA_START)(VXB_DMA_TX *pVxbDmaTx);

typedef struct vxbDmaChan VXB_DMA_CHAN;

struct vxbDmaTx {
    PHYS_ADDR           pDesc;  /* physical address */
    VXB_DMA_COMPLETE_FN fn;
    void *              pArg;
    VXB_DMA_CHAN *      dmaChan;
    VXB_DMA_START       pVxbDmaStart;
};

typedef struct vxbDmaDev {
    SL_NODE         dmaNode;
    VXB_DEV_ID      pDev;
    SL_LIST         vxbDmaChanList;
    int             flag;
} VXB_DMA_DEV;

struct vxbDmaChan {
    SL_NODE        node;
    VXB_DMA_DEV *  pVxbDmaDev;
    UINT32         uCap;
    int            flag;
};

/* function declarations */

void vxbDmaRegister (VXB_DMA_DEV * pVxbDmaDev);
void vxbDmaUnregister (VXB_DMA_DEV * pVxbDmaDev);
void vxbDmaChanAdd (VXB_DMA_DEV * pVxbDmaDev, VXB_DMA_CHAN * pVxbDmachan);
VXB_DMA_CHAN * vxbDmaChanAlloc (UINT32 uCap);
VXB_DMA_CHAN * vxbDmaChanAllocAdvance (char * pName, UINT32 unit, int chanNum,
                                       UINT32 uCap);
void vxbDmaChanFree (VXB_DMA_CHAN * pDmaChan);
STATUS vxbDmaChanStart (VXB_DMA_TX * pVxbDmaTx);
STATUS vxbDmaChanConfig (VXB_DMA_CHAN * pDmaChan, VXB_DMA_SLAVE_CONFIG * pConfig);
STATUS vxbDmaChanControl (VXB_DMA_CHAN * pDmaChan,VXB_DMA_CTRL_CMD cmd,void * pArg);
VXB_DMA_TX * vxbDmaChanPreMemCpy (VXB_DMA_CHAN * pDmaChan, VIRT_ADDR src, VIRT_ADDR dest,
                                  size_t len, int flag);
VXB_DMA_TX * vxbDmaChanPreScg (VXB_DMA_CHAN * pDmaChan, LIST * srcList, LIST * descList,
                               size_t len, int flag);

#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbDmaMethod.h>

#endif /* _INC_vxbDmaLibH */
