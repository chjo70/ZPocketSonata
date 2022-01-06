/* 01warmBoot.cdf - warm boot library component description file */

/*
 * Copyright (c) 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
08apr15,l_z  created. (F3387)
*/

#if (!defined SIMLINUX) && (!defined  SIMNT)
Component INCLUDE_WARM_BOOT {
    NAME            Initialize warm boot library
    SYNOPSIS        This component provides initialization of the warm boot library.
    CONFIGLETTES    usrWarmBootLib.c
    MODULES         warmBootLib.o
    HDR_FILES       warmBootLib.h
    PROTOTYPE       void usrWarmBootLibInit ();
    INIT_RTN        usrWarmBootLibInit();
    _CHILDREN       FOLDER_BOARD_LIB
    _INIT_ORDER     usrRoot
    INIT_AFTER      INCLUDE_BOARD_INIT
    INIT_BEFORE     INCLUDE_VXBUS
}

Component INCLUDE_WARM_BOOT_PROTECT {
    NAME            Protect warm boot data
    SYNOPSIS        This component allows protection of warm boot data.
    REQUIRES        INCLUDE_WARM_BOOT \
    				INCLUDE_MMU_BASIC
    _CHILDREN       FOLDER_BOARD_LIB
}
#endif


