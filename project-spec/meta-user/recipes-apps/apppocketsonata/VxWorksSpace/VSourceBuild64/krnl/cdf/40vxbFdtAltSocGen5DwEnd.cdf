/* 40vxbFdtAltSocGen5DwEnd.cdf - Altera DWC END controller */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
17aug15,m_w  decouple the connection with PHY. (V7PRO-2344)
21aug14,m_w  replace INCLUDE_GENERICPHY with INCLUDE_MICREL_PHY (V7PRO-1195)
25apr14,yjw  created (US35705)
*/

Component   DRV_END_FDT_ALT_SOC_GEN5_DWC {
        NAME            Altera SoC Gen 5 DesignWare 3504-0 network driver
        SYNOPSIS        This component creates an "emac" network interface on a \
                        5th generation Altera ARM SoC using the DesignWare 3504 MAC. \
                        It is fully compliant with the IEEE 802.3 10 Mb/s Base-T, \
                        100 Mb/s Base-T, and 1 Gb/s specifications.
        MODULES         vxbFdtAltSocGen5DwEnd.o
        LINK_SYMS       altSocGen5DwDrv
        REQUIRES        INCLUDE_DMA_SYS \
                        INCLUDE_END
        _CHILDREN       FOLDER_NET_END_DRV
}
