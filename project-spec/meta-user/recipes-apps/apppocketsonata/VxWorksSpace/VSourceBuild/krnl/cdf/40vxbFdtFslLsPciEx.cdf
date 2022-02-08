/* 40vxbFdtFslLsPciEx.cdf - Freescale Layerscape VxBus PCI Express driver */

/*
 * Copyright (c) 2014-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20jul17,mjn  text updates (F8862)
10aug15,wap  Change dependency on VxBus to dependency on PCI bus
10dec14,swu  created. (US47600)
*/

Component DRV_PCIEX_FDT_FSL_LS {
        NAME            Freescale Layerscape PCI Express support
        SYNOPSIS        Freescale Layerscape PCI Express
        MODULES         vxbFdtFslLsPciEx.o
        LINK_SYMS       vxbFdtFslLsPciExDrv
        REQUIRES        INCLUDE_PCI_BUS \
			INCLUDE_PCI_AUTOCONF
        _CHILDREN       FOLDER_DRIVERS_PCI
}

