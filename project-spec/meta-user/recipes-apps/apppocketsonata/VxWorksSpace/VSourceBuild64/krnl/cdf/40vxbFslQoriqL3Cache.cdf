/* 40vxbFslQoriqL3Cache.cdf - QorIQ L3 cache controller */

/*
 * Copyright (c) 2013-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
20jul17,mjn  text updates (F8862)
03mar14,b_m  update component name
27nov13,syt  created
*/

Component DRV_QORIQ_L3_CACHE {
    NAME        Freescale QorIQ L3 cache support driver
    SYNOPSIS    Freescale QorIQ L3 cache support driver
    MODULES     vxbFslQoriqL3Cache.o
    LINK_SYMS   vxbQoriqL3CacheDrv
    REQUIRES    DRV_BUS_FDT_ROOT
    _CHILDREN   FOLDER_DRIVERS_OTHER
}
