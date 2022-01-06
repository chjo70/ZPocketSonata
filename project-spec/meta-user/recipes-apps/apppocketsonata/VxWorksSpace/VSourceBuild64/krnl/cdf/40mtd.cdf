/* 40mtd.cdf - Memory technology device component description file */

/*
 * Copyright (c) 2012-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11may15,yjl  fix V7STO-357 Wrong definition of FOLDER_MTD
10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
16jan14,ywu  adopt to vxBus gen2
07jan12,x_z  adjusted usrMtdInit() location. 
24dec12,x_z  added FOLDER_MTD and moved it to moved to FOLDER_PERIPHERALS;
             added INCLUDE_MTD_SHOW.
22oct12,x_z  added support for Flash usage.
28aug12,x_z  rewritten.
31may12,m_y  written.
*/

Folder  FOLDER_FLASH 
    {
    NAME            Flash device components
    SYNOPSIS        Flash device components
#ifdef _WRS_CONFIG_BDM_XBD
        _CHILDREN   FOLDER_BDM
#else
        _CHILDREN   FOLDER_STORAGE
#endif
    }

Folder  FOLDER_MTD {
        NAME        MTD
        SYNOPSIS    Memory Technology Device(MTD) layer
        _CHILDREN   FOLDER_FLASH
        CHILDREN    INCLUDE_MTD     \
                    INCLUDE_MTD_SHOW
}

Component INCLUDE_MTD {
    NAME            MTD component
    SYNOPSIS        Memory Technology Device(MTD) component
    CONFIGLETTES    usrMtd.c
    MODULES         mtdCore.o
    PROTOTYPE       void usrMtdInit (char *);
    INIT_RTN        usrMtdInit (MTD_CFG_STR);
    _INIT_ORDER     usrRoot
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    INIT_AFTER      INCLUDE_VXBUS
#else
    INIT_AFTER      INCLUDE_SYSCLK_INIT
    INIT_BEFORE     INCLUDE_CPC
#endif
    _CHILDREN       FOLDER_MTD
    CFG_PARAMS      MTD_CFG_STR
}

Parameter MTD_CFG_STR {
    NAME            MTD config string
    SYNOPSIS        Specifies the configuration for MTD component, and is \
                    composed of Flash chip strings - \
                        "<Flash chip 0 string>;<Flash chip 1 string>...".\
                    And Flash chip string is composed of Flash partitions \
                    strings - \
                        "$<Flash instance name>#<chip index>:\
                        <Flash partition 0 string>;\
                        <Flash partition 1 string>...".\
                    And then Flash partition string is the following - \
                        "<start block address>,<block count>,<MTD device name>#\
                        <Flash group index>,<Flash usage>".
                    And Flash usage is defined in flash.h.
    TYPE            char *
    DEFAULT         "$gpmc0#0:0x0,0x100,/nvram#0,1;0x100,0x700,/ftl0#0,0"
}

Component INCLUDE_MTD_SHOW {
    NAME            MTD show routines
    SYNOPSIS        Memory Technology Device(MTD) show routines
    MODULES         mtdShow.o
    PROTOTYPE       void mtdShowInit (void);
    INIT_RTN        mtdShowInit ();
    _INIT_ORDER     usrRoot
    INIT_AFTER      INCLUDE_MTD
#ifdef _WRS_CONFIG_VXBUS_LEGACY
    INIT_BEFORE     usrIosCoreInit
#endif
    _CHILDREN       FOLDER_MTD
    REQUIRES        INCLUDE_MTD
}

