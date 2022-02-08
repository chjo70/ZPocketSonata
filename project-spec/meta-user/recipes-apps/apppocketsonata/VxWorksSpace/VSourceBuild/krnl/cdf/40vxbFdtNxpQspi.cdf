/* 40vxbFdtNxpQspi.cdf - Component configuration file */

/*
 * Copyright (c) 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24jul17,ffu  added QSPI NOR flash support for NXP L1046(F9437)
*/

Component DRV_FDT_NXPQSPI {
    NAME            NXP QSPI controller driver
    SYNOPSIS        Shared driver for NXP QSPI controller \
                    integrated in various SoCs.
    MODULES         vxbFdtNxpQspi.o
    LINK_SYMS       vxbNxpQspiDrv
    REQUIRES        INCLUDE_VXBUS
    _CHILDREN       FOLDER_FLASH
}

