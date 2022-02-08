/* 40vxbFslEdma.cdf - Component configuration file */

/* Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
17nov14,y_f  created. (US47599)
*/

Component DRV_DMA_FDT_FSL_EDMA {
    NAME            Freescale eDMA support 
    SYNOPSIS        This component provides DMA support for Freescale eDMA compatible devices. The controller's primary purpose\
                    is to service user-programmed data transfers between two end-point devices.

This driver supports standard VxBus DMA library interfaces.
    MODULES         vxbFslEdma.o
    LINK_SYMS       vxbFdtFslEdmaDrv
    REQUIRES        DRV_BUS_FDT_ROOT    \
                    INCLUDE_DMA_SYS
    _CHILDREN       FOLDER_DRIVERS_DMA
}