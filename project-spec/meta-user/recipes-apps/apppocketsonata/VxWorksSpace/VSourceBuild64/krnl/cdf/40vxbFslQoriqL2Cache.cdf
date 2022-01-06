/* 40vxbFslQoriqL2Cache.cdf - QorIQ L2 cache controller */

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
17jul13,l_z  created
*/

Component DRV_QORIQ_L2_CACHE {
    NAME        Freescale QorIQ L2 cache support driver
    SYNOPSIS    Freescale QorIQ L2 cache support driver
    MODULES     vxbFslQoriqL2Cache.o
    LINK_SYMS   vxbQoriqL2CacheDrv
    REQUIRES    DRV_BUS_FDT_ROOT
    _CHILDREN   FOLDER_DRIVERS_OTHER
}
