/* 40vxbM85xxTimer.cdf - Component Definition file for m85xx timer */

/*
 * Copyright (c) 2007-2008, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
02Dec13,r_y  created
*/

Component       DRV_TIMER_OPENPIC {
    NAME        OpenPic timer
    SYNOPSIS    This component provides the VxBus driver for the openPic timer. A driver-specific data structure\
                (struct openPicTimerInstance) is allocated for each timer instance\
                and a pointer to it is stored in 'pInst->pDrvCtrl' during openPicTimerInstInit().\
                openPicTimerInstance contains an array of (struct openPicTimerData), one for each\
                timer in the instance.
    MODULES     vxbOpenPicTimer.o
    LINK_SYMS   vxbOpenPicTimerDrv
    REQUIRES    INCLUDE_VXBUS \
                INCLUDE_TIMER_SYS
    _CHILDREN   FOLDER_DRIVERS_TIMER
}
