/* 40vxbFslPpcDecTimer.cdf - Component Definition file for FSL DEC timer */

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
19jul17,mjn  Folder restructure (F8862)
23aug14,syt  created.(F2505)
*/

Component       DRV_TIMER_PPC_DEC {
    NAME        Freescale PPC DEC Timer Driver
    SYNOPSIS    VxBus Driver for Freescale Book E Timer
    MODULES     vxbFslPpcDecTimer.o
    LINK_SYMS   vxbFslPpcDecTimerDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_TIMER_SYS
    _CHILDREN   FOLDER_DRIVERS_TIMER
}
