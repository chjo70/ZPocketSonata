/* 10devclk.cdf - Device Clock Component configuration file */

/*
 * Copyright (c) 2013, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
-------------------
14jun17,mjn  text updates (F8862)
31aug16,l_z  disable INCLUDE_DEVCLK_SYS when FDT is excluded. (V7PRO-3296)
15arp16,l_z  fix typo for FOLDER_SUBSYSTEM. (V7PRO-3016)
23sep13,c_t  created for VxBus GEN2
*/

#ifdef _WRS_CONFIG_FDT
Component INCLUDE_DEVCLK_SYS {
    NAME            VxBus clock device subsystem
    SYNOPSIS        This component enables the VxBus clock device subsystem.
    PROTOTYPE       void vxbClkLibInit(void);
    INIT_RTN        vxbClkLibInit();
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    REQUIRES        INCLUDE_VXBUS
    _CHILDREN       FOLDER_CLOCK
}
#endif /* _WRS_CONFIG_FDT */
