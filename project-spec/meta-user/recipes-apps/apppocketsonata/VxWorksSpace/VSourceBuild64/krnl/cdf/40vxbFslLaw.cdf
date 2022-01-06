/* 40vxbFslLaw.cdf - Freescale LAW driver */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20jul17,mjn  text updates (F8862)
01a,23may13,j_z  created
*/

Component       DRV_FSL_LAW {
    NAME        Freescale LAW driver
    SYNOPSIS    vxBus Driver for LAW driver
    MODULES     vxbFslQoriqLaw.o
    LINK_SYMS   qoriqLawDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_OTHER
}
