/* 40QorIQQman.cdf - Freescale QorIQ Queue Manager driver file */

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
05may17,wch  added support for ARM (F8333)
25apr14,fao  created
*/

Component DRV_RESOURCE_QORIQQMAN {
    NAME        Freescale QORIQ Queue Manager (QMan) resource driver
    SYNOPSIS    Use this component to add support for QORIQ QMan.
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbQorIQQman.o vxbQorIQQmanPortal.o
    LINK_SYMS   qmanDrv qportalDrv
}
