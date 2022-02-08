/* 40vxbFdtFslImxEnd.cdf - Freescale ENET END controller */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
19feb14,g_x  make the component visible in workbench (VXW7-1956)
23may13,y_c  created
*/

Component   DRV_END_FDT_FSL_IMX {
        NAME            Freescale IMX ENET enhanced network driver
        SYNOPSIS        This component creates an "enet" network interface for \
                        the Freescale ENET Ethernet controller found on i.MX \
                        embedded processors. The ENET is fully compliant with the \
                        IEEE 802.3-2002 triple speed 10/100/1000 Mb/s specification.
        MODULES         vxbFdtFslImxEnd.o 
        LINK_SYMS       iMxEnetDrv
        REQUIRES        INCLUDE_DMA_SYS \
                        INCLUDE_END \
                        INCLUDE_GENERICPHY
        _CHILDREN       FOLDER_NET_END_DRV
}
