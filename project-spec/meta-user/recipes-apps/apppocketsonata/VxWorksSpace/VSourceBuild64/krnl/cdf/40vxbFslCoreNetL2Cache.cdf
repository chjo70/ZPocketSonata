/* 40vxbFslCoreNetL2Cache.cdf - CoreNet L2 cache controller */

/*
 * Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
20jul17,mjn  text updates (F8862)
04mar14,ylu  created
*/

Component DRV_CORENET_L2_CACHE {
    NAME        Freescale CORENET L2 cache support driver
    SYNOPSIS    Freescale CORENET L2 cache support driver
    MODULES     vxbFslCoreNetL2Cache.o
    LINK_SYMS   vxbCoreNetL2CacheDrv
    REQUIRES    DRV_BUS_FDT_ROOT
    _CHILDREN   FOLDER_DRIVERS_OTHER
}

