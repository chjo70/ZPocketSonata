/* 40vxbFslDma.cdf - Component Definition file for Freescale DMA */

/*
 * Copyright (c) 2013-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
15apr14,ylu  added dependency to INCLUDE_DMA_SYS driver.
23may13,y_y  created
*/

Component       DRV_FSL_DMA {
    NAME        m85xx DMA 
    SYNOPSIS    This component provides the driver for the Freescale's DMA engine. It is intended for use by\
                client drivers performing other high level functions.\
                This driver provide asynchronous DMA transfer functions. Basic Chaining Mode is\
                supported in this version, but list descriptor is not supported yet.
    MODULES     vxbFslDma.o
    LINK_SYMS   vxbFslDmaDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_DMA_SYS
    _CHILDREN   FOLDER_DRIVERS_DMA
}
