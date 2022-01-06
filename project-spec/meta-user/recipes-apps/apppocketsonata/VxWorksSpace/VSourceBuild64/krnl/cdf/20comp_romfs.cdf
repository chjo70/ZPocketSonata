/* 20comp_romfs.cdf - Rom File System component */

/*
 * Copyright 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22jan17,jbm  Fixed spelling error, removed tabs, minor editing.
27apr16,gls  Updated dependencies for certKernel.o support
08jan16,cww  Increased ROMFS_MAX_OPEN_FILES under CERT to 16
01sep15,clt  Added INCLUDE_ROMFS_DRV and ROMFS_DEV_NAME (F4862)
03dec14,clt  Added max open file param for CERT
24jan14,ghs  create
*/

/*
DESCRIPTION
This file contains the description for the ROM File System component.
*/

Folder FOLDER_FILESYSTEM
    {
    NAME            File system 
    SYNOPSIS        This folder contains components and parameters that \
                    can be used to configure your project's file system.
    _CHILDREN       FOLDER_STORAGE
    }

Folder FOLDER_ROMFS
    {
    NAME            ROMFS file system
    SYNOPSIS        This folder contains components and parameters that can \
                    be used to include and configure a read-only memory-based \
                    file system in your project.
    _CHILDREN       FOLDER_FILESYSTEM
    CHILDREN        INCLUDE_ROMFS_DRV \
                    INCLUDE_ROMFS
    }

Component INCLUDE_ROMFS_DRV
    {
    NAME            ROMFS file system driver
    SYNOPSIS        Includes a driver for read-only memory-based file system. \
                    It is initialized at runtime.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
    MODULES         romfs.o romfsLib.o romfsDrv.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
    INIT_RTN        romfsFsInit (ROMFS_MAX_OPEN_FILES); 
    HDR_FILES       romfsLib.h
    REQUIRES        INCLUDE_IO_FILE_SYSTEM    \
                    INCLUDE_MEM_MGR_BASIC     \
                    INCLUDE_SEM_MUTEX         \
                    INCLUDE_FORMATTED_OUT_BASIC
    CFG_PARAMS      ROMFS_MAX_OPEN_FILES
    }

Component INCLUDE_ROMFS
    {
    NAME            ROMFS file system
    SYNOPSIS        Includes a read-only memory-based file system.
    CONFIGLETTES    usrRomfs.c
    INIT_RTN        usrRomfsConfig ();
    REQUIRES        INCLUDE_ROMFS_DRV
    CFG_PARAMS      ROMFS_DEV_NAME          
    }

Parameter ROMFS_DEV_NAME {
    NAME            Device name
    SYNOPSIS        This parameter specifies the device name. By default, it is \
                    /romfs.
    DEFAULT         "/romfs"
}

Parameter ROMFS_MAX_OPEN_FILES {
    NAME            Default maximum open files (ROMFS)
    SYNOPSIS        This parameter specifies the maximum number of files that \
                    can be opened. By default, it is set to 16.
#ifdef _WRS_CONFIG_CERT
    DEFAULT         16
#else
    DEFAULT         NUM_FILES
#endif /* _WRS_CONFIG_CERT */
}
