/* vxbDmaEndBufLib.h - buffer and DMA system for END drivers */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23dec13,l_z  created
*/

#ifndef __INCvxbDmaEndBufBufLibh
#define __INCvxbDmaEndBufBufLibh

/* includes */
#include <vsbConfig.h>
#include <hwif/util/vxbDmaBufLib.h>

#ifdef __cplusplus
extern "C" {
#endif

IMPORT STATUS vxbDmaBufMapMblkLoad
    (
#ifdef _WRS_CONFIG_VXBUS
    VXB_DEV_ID      pInst,
#else
    VXB_DEVICE_ID   pInst,
#endif
    VXB_DMA_TAG_ID  dmaTagID,
    VXB_DMA_MAP_ID  map,
    M_BLK_ID        pMblk,
    int             flags
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbDmaEndBufBufLibh */
