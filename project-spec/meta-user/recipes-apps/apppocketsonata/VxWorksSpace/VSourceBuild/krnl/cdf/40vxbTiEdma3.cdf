/* 40vxbTiEdma3.cdf - TI EDMA3 driver */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
12dec13,y_f  created
*/

Component       DRV_TI_EDMA3 {
    NAME        TI EDMA3
    SYNOPSIS    This component implements a driver for TI EDMA3 (Enhanced DMA version 3) \
                controller. The controller's primary purpose is to service user-programmed\
                data transfers between two end-point devices.\
                \
                The TI EMDA3 controller uses PARAM set for DMA transfer. A PARAM set\
                is a set of parameters that define how the transfer should be handled,\
                eg. source address, destination address, interrupt mode, etc. Before \
                actually triggering the DMA engine, one or more PARAM set(s) must be \
                set correctly.\
                \
                The TI EDMA3 controller has an internal buffer RAM, before triggering\
                any DMA transfer, PARAM set must be copied to the corresponding \
                internal buffer RAM.
    MODULES     vxbTiEdma3.o
    LINK_SYMS   vxbFdtTiEdma3Drv
    REQUIRES    INCLUDE_VXBUS   \
                INCLUDE_DMA_SYS
    _CHILDREN   FOLDER_DRIVERS_DMA
}

