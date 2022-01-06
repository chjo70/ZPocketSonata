/* 40vxbFslQoriqClk.cdf - QorIQ clock generator */

/*
 * Copyright (c) 2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
05sep17,emj  fix orphaned DRV_QORIQ_CLK component (V7PRO-3978)
20jul17,mjn  text updates (F8862)
20jul16,m_w  added dependency with INCLUDE_DEVCLK_SYS
27nov13,syt  created
*/

Component DRV_QORIQ_CLK {
    NAME        Freescale QorIQ clock device driver
    SYNOPSIS    Freescale QorIQ clock device driver
    MODULES     vxbFdtFslQoriqClk.o
    LINK_SYMS   vxbFslQoriqClockDrv
    REQUIRES    DRV_BUS_FDT_ROOT   \
                INCLUDE_DEVCLK_SYS
    _CHILDREN   FOLDER_DRIVERS_TIMER
}
