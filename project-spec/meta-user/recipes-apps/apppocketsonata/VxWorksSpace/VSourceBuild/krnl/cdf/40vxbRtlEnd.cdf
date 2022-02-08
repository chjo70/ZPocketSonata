/* 40vxbRtlEnd.cdf - RealTek END driver */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
20oct15,fao  created. (US65600)
*/

Component   INCLUDE_RTL8169_VXB_END {
        NAME            RealTek 8169 VxBus enhanced network driver
        SYNOPSIS        This component creates an "rtg" network \
                        interface for the RealTek 'C+' family of \
                        PCI 10/100 and 10/100/1000 Ethernet controllers.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbRtl8169End.o
        LINK_SYMS       rtgDrv
        REQUIRES        INCLUDE_DMA_SYS \
                        INCLUDE_CACHE_DMA32_LIB \
                        INCLUDE_END \
                        INCLUDE_RTL8169PHY \
                        INCLUDE_VXBUS
}
