/* 40vxbFdtFslLsGateClk.cdf - Freescale Layerscape gate clock system control */

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
20jul17,mjn  text updates (F8862)
01dec14,sye  written. (US47603)
*/

Component DRV_CLK_FSL_LS_GATE {
        NAME            FDT Freescale Layerscape Gate Clock Driver
        SYNOPSIS        FDT Freescale Layerscape Gate Clock Driver
        MODULES         vxbFdtFslLsGateClk.o
        LINK_SYMS       fslGenGateDrv           \
                        fslDummyClkDrv          \
                        fslLsGateClkDrv
        REQUIRES        DRV_BUS_FDT_ROOT        \
                        INCLUDE_DEVCLK_SYS
        _CHILDREN       FOLDER_DRIVERS_TIMER
}
