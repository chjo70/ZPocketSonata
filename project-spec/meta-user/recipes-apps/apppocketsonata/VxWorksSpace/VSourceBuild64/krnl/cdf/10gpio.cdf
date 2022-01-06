/* 10gpio.cdf - Component configuration file */

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
15arp16,l_z  fix typo for FOLDER_SUBSYSTEM. (V7PRO-3016)
23sep13,c_t  created for VxBus GEN2
*/

Folder FOLDER_SUB_GPIO {                    
    NAME            GPIO
    SYNOPSIS        This folder contains the general purpose I/O (GPIO) support subsystem.  
    _CHILDREN       FOLDER_SUBSYSTEM       
}

Component INCLUDE_GPIO_SYS {
    NAME            VxBus GPIO subsystem
    SYNOPSIS        This component provides a routine to initialize the VxBus GPIO subsystem.
    PROTOTYPE       STATUS vxbGpioLibInit (void);
    INIT_RTN        vxbGpioLibInit();
    _INIT_ORDER     usrRoot
    INIT_BEFORE     INCLUDE_VXBUS
    REQUIRES        INCLUDE_VXBUS
    _CHILDREN       FOLDER_SUB_GPIO
}
