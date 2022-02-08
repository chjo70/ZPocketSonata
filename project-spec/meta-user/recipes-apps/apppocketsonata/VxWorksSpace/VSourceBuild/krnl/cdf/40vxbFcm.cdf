/* 40vxbFcm.cdf - Component Definition file for eLBC FCM NAND controller */

/*
 * Copyright (c) 2013, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
01b,16jan14,ywu  adopt to vxBus gen2
01a,12dec13,ywu  written.
*/

Component DRV_VXB_FCM {
    NAME        eLBC FCM NAND controller VxBus Driver
    SYNOPSIS    eLBC FCM NAND controller VxBus Driver
    MODULES     vxbFcm.o
    _CHILDREN   FOLDER_FLASH
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    LINK_SYMS   vxbFdtFcmDrv
    _INIT_ORDER usrRoot
    REQUIRES    INCLUDE_VXBUS
#else
    INIT_RTN    vxbFcmRegister();
    PROTOTYPE   void vxbFcmRegister (void);
    _INIT_ORDER hardWareInterFaceBusInit
    REQUIRES    INCLUDE_PLB_BUS     \
                INCLUDE_PARAM_SYS
    INIT_AFTER  INCLUDE_PLB_BUS
#endif
}

