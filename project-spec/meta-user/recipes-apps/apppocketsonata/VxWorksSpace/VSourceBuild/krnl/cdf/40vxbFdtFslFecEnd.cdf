/* 40vxbFdtFslFecEnd.cdf - Freescale FEC END controller */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
14jul14,yjw  created
*/

Component   DRV_END_FDT_FSL_FEC {
        NAME            Freescale FEC enhanced network driver
        SYNOPSIS        This component creates an "fec" network interface for a \
                        Freescale FEC Ethernet controller. The FEC is fully \
                        compliant with the IEEE 802.3-2002 double \
                        speed 10/100 Mb/s specification.
        MODULES         vxbFdtFslFecEnd.o 
        LINK_SYMS       fslFecDrv
        REQUIRES        INCLUDE_DMA_SYS \
                        INCLUDE_END \
                        INCLUDE_FEC_MDIO \
                        INCLUDE_GENERICPHY
        _CHILDREN       FOLDER_NET_END_DRV
}
