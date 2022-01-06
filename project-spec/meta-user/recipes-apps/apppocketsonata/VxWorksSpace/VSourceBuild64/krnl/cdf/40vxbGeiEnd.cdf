/* 40vxbGeiEnd.cdf - GEI driver */

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
20arp14,y_y  created. (US33490)
*/
 
Component   INCLUDE_GEI825XX_VXB_END {
        NAME            Intel PRO/1000 VxBus enhanced network driver
        SYNOPSIS        This component creates a "gei" network \
                        interface for the following Intel devices: \
                        82543, 82544, 82540, 82541, 82545, 82546, \
                        82547, 82571, 82572, 82573, 82574, 82575, \
                        82576, 82577, 82578, 82579, 82580, 82583, \
                        I350, I210/I211, Tolapai, 631xESB/632xESB, \
                        ICH8, ICH9, ICH10, PCH, and PCH2 controllers \
                        with copper UTP and TBI multi-mode fiber media \
                        only. Some SERDES adapters have not been tested.

        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbGei825xxEnd.o
        LINK_SYMS       geiDrv
        REQUIRES        INCLUDE_DMA_SYS \
                        INCLUDE_END \
                        INCLUDE_GENERICPHY \
                        INCLUDE_VXBUS
}
