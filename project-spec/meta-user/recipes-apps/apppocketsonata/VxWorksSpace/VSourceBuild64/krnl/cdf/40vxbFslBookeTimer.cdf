/* 40vxbFslBookeTimer.cdf - Component Definition file for FSL Book E timer */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19jul17,mjn  Folder restructure (F8862)
23may13,x_z  created
*/

Component       DRV_TIMER_FSL_BOOKE {
    NAME        Freescale Book E Timer Driver
    SYNOPSIS    VxBus Driver for Freescale Book E Timer
    MODULES     vxbFslBookeTimer.o
    LINK_SYMS   vxbFslBookeTimerDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_TIMER_SYS
    _CHILDREN   FOLDER_DRIVERS_TIMER
}
