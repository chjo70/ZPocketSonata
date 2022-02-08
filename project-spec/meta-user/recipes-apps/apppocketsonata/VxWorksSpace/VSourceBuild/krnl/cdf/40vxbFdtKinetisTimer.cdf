/* 40vxbFdtKinetisTimer.cdf - Component Definition file for Kinetis timer */

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
14jun17,mjn  text updates (F8862)
26jun14 mpc  created (US40538)
*/

Component       DRV_TIMER_FDT_KINETIS {
    NAME        Freescale Kinetis timer
    SYNOPSIS    This component provides the Freescale Kinetis timer driver.
    MODULES     vxbFdtKinetisTimer.o
    LINK_SYMS   vxbFdtKinetisTimerDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_TIMER_SYS
    _CHILDREN   FOLDER_DRIVERS_TIMER
}
