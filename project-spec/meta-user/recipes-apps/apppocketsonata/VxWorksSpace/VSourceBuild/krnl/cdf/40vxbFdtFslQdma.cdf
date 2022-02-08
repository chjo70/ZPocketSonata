/* 40vxbFdtFslQdma.cdf - Component configuration file */

/* Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20jul17,mjn  text updates (F8862)
24nov14,y_f  created. (US50708)
*/

Component DRV_DMA_FDT_FSL_QDMA {
    NAME            DMA support for Freescale qDMA compatible devices
    SYNOPSIS        Freescale qDMA support
    MODULES         vxbFslQdma.o
    LINK_SYMS       vxbFdtFslQdmaDrv
    REQUIRES        DRV_BUS_FDT_ROOT    \
                    INCLUDE_DMA_SYS
    _CHILDREN       FOLDER_DRIVERS_DMA
}