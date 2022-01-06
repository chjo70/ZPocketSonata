/* 40bdm_nvram.cdf - NVRAM component description file */

/*
 * Copyright (c) 2014, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07may15,jmz  US55875 - Make INCLUDE_NVRAM_NULL available for all builds
18mar14,j_l  US32795 - restore INCLUDE_NVRAM_NULL for non-FDT builds
26feb14,ghs  create 
*/

#ifdef _WRS_CONFIG_VXBUS_LEGACY
#ifndef _WRS_CONFIG_FDT
Parameter NV_RAM_SIZE 
    {
	NAME		NVRAM size
	SYNOPSIS	NVRAM size (bytes)
	_CFG_PARAMS INCLUDE_MEMORY_CONFIG
	DEFAULT		0x100
    }

Parameter NV_BOOT_OFFSET 
    {
	NAME		NVRAM boot offset
	SYNOPSIS	NVRAM boot offset
	_CFG_PARAMS INCLUDE_MEMORY_CONFIG
	DEFAULT		0x0
    }

Parameter NV_RAM_SIZE_WRITEABLE 
    {
	NAME		NVRAM Writeable size
	SYNOPSIS	NVRAM Writeable size (bytes)
	_CFG_PARAMS INCLUDE_MEMORY_CONFIG
	DEFAULT		NV_RAM_SIZE
    }

Component INCLUDE_NVRAM_FLASH 
    {
    NAME            NVRAM to Flash mapping component
    SYNOPSIS        Use FLASH memory as non-volatile RAM
    _CHILDREN       FOLDER_BDM
    CONFIGLETTES    usrFlashNvRam.c
    }

Component INCLUDE_NON_VOLATILE_RAM 
    {
    NAME            Non Volatile Memory Library
    SYNOPSIS        Non Volatile Memory Library
    INIT_RTN        vxbNonVolLibInit();
    _CHILDREN       FOLDER_BDM
    REQUIRES        INCLUDE_VXBUS
    }

Component DRV_NVRAM_FILE
    {
    NAME            Driver for file-based non-volatile RAM support
    SYNOPSIS        Driver for file-based non-volatile RAM support
    _CHILDREN       FOLDER_BDM
    _INIT_ORDER     hardWareInterFaceBusInit
    INIT_RTN        vxbFileNvRamRegister();
    PROTOTYPE       void vxbFileNvRamRegister(void);
    MODULES         vxbFileNvRam.o
    REQUIRES        INCLUDE_PLB_BUS \
                    INCLUDE_NON_VOLATILE_RAM
    }

#endif /* _WRS_CONFIG_FDT */
#endif /* _WRS_CONFIG_VXBUS_LEGACY */

Component INCLUDE_NVRAM_NULL
    {
    NAME            NVRAM to Flash mapping component
    SYNOPSIS        Use FLASH memory as non-volatile RAM
    _CHILDREN       FOLDER_BDM
    CONFIGLETTES    usrNullNvRam.c
    }
