/* 40feiVxbEnd.cdf - Component configuration file */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
24mar15,j_l Initial modifications for IA 32 bit GEN2 support
15jun14,y_y created from fei8255xVxbEnd.h(01d). (US33490)
*/

Component   INCLUDE_FEI8255X_VXB_END {
        NAME            FEI Intel PRO/100 VxBus enhanced network driver
        SYNOPSIS        This component creates an "fei" network \
                        interface for the Intel PRO/100 series \
                        of 10/100 Ethernet controllers including \
                        the i82557, i82558, i82559, i82550, and \
                        i82551.
        MODULES         vxbFei8255xEnd.o
        _CHILDREN       FOLDER_NET_END_DRV
        LINK_SYMS       feiDrv
        REQUIRES        INCLUDE_DMA_SYS \
                        INCLUDE_END \
                        INCLUDE_GENERICPHY \
                        INCLUDE_VXBUS
}

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
Component       INCLUDE_FEI8255X_VXB_END {
        REQUIRES        += INCLUDE_CACHE_DMA32_LIB
}
#endif /* !_WRS_CONFIG_COMPAT69_ADR_SPACE */
