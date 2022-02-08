/* 40vxbFdtFslQspi.cdf - Component configuration file */

/*
 * Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16aug17,mze  resolving issue with multi version layers and cdf Folder changes
14jun17,mjn  text updates (F8862)
09feb17,mw1  rename vxbFdtFslQspiFlash to vxbFdtFslQspi (US89250)
18sep14,m_y  added QSPI NOR flash support for Freescale (US46192)
*/

Component DRV_FDT_FSLQSPI {
    NAME            NXP/Freescale QSPI controller
    SYNOPSIS        This component provides the shared driver for the NXP/Freescale Quad Serial Peripheral Interface (QSPI) controller \
                    integrated in various SoCs.
    MODULES         vxbFdtFslQspi.o
    LINK_SYMS       vxbFslQspiDrv
    _INIT_ORDER     usrRoot
    REQUIRES        INCLUDE_VXBUS
    _CHILDREN       FOLDER_DRIVERS_BUS
}

