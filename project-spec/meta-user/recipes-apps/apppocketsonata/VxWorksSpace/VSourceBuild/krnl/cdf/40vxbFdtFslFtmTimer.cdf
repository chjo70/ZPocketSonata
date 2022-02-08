/* 40vxbFdtFslFtmTimer.cdf - Component Definition file for Freescale Flex timer */

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
05nov14 g_x  created (US40538)
*/

Component       DRV_TIMER_FDT_FSL_FTM {
    NAME        Freescale flex timer
    SYNOPSIS    This component provides the Freescale flex timer driver.
                The Flex Timer has 2 to 8 channel timers that supports input capture, output\
                compare, and the generation of PWM signals. Its counter is only 16 bits. The\
                prescaler can be 1, 2, 4, 8, 16, 32, 64, 128.\
                To obtain best precision, the prescaler is set to a value that makes it have a\
                maximum rollover counter value.
    MODULES     vxbFdtFslFtmTimer.o
    LINK_SYMS   vxbFdtFslFlexTimerDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_TIMER_SYS \
                DRV_BUS_FDT_ROOT
    _CHILDREN   FOLDER_DRIVERS_TIMER
}
