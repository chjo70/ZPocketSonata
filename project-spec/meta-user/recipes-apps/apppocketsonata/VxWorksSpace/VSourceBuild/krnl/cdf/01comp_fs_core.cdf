/* 01comp_fs_core.cdf - File System Core component */

/*
 * Copyright 2014 - 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22jan17,jbm  Editing, fix blank SYNOPSIS
14jun16,lyj  there is no VIP option to automatically format a Ramdisk at system 
             initialization time (V7STO-645)
17feb15,dcc  added FOLDER_VDFS
17feb14,ghs  re-write
*/

/*
DESCRIPTION
This file contains the description for the file system core component.
*/

Folder FOLDER_FILESYSTEM
    {
    NAME            File system 
    SYNOPSIS        This folder contains components and parameters that you \
                    can use to configure a file system for your project. 
    _CHILDREN       FOLDER_STORAGE
    CHILDREN        INCLUDE_FS_EVENT_UTIL \
                    INCLUDE_FS_MONITOR    \
                    INCLUDE_RAM_DISK      \
                    SELECT_RAM_DISK_FORMAT\
                    FOLDER_VDFS           \
                    FOLDER_DOSFS          \
                    FOLDER_HRFS           \
                    FOLDER_DEVFS          \
                    FOLDER_NFS
    }

Component INCLUDE_FS_EVENT_UTIL
    {
    NAME            File system event utilities
    SYNOPSIS        This component includes the file system event utilities. 
    MODULES         fsEventUtilLib.o
    HDR_FILES       fsEventUtilLib.h
    INIT_RTN        fsEventUtilLibInit ();
    REQUIRES        INCLUDE_ERF
    INCLUDE_WHEN    INCLUDE_HRFS          \
                    INCLUDE_HRFS_READONLY \
                    INCLUDE_RAWFS         \
                    INCLUDE_CDROMFS       \
                    INCLUDE_XBD_TRANS     \
                    INCLUDE_DOSFS
    }

Component INCLUDE_FS_MONITOR
    {
    NAME            File system monitor
    SYNOPSIS        This component includes the file system monitor. 
    MODULES         fsMonitor.o           \
                    xbdPartition.o
    HDR_FILES       fsMonitor.h
    INIT_RTN        fsMonitorInit ();
    REQUIRES        INCLUDE_RAWFS
    _REQUIRES       INCLUDE_CDROMFS       \
                    INCLUDE_DOSFS
    }


Component INCLUDE_RAM_DISK_FORMAT_NONE
    {
    NAME           RAM disk not formatted
    SYNOPSIS       This component specifies that the RAM disk is not formatted \
                   when it is created.
    }

Component INCLUDE_RAM_DISK_FORMAT_ANY
    {
    NAME           RAM disk formatted as any type
    SYNOPSIS       This component specifies that the RAM disk is formatted as \
                   any file system type.
    }

Component INCLUDE_RAM_DISK_FORMAT_DOSFS
    {
    NAME           RAM disk formatted with dosFs
    SYNOPSIS       This component specifies that the RAM disk is formatted as \
                   dosFs. 
    REQUIRES       INCLUDE_DOSFS_FMT
    }

Component INCLUDE_RAM_DISK_FORMAT_HRFS
    {
    NAME           RAM disk formatted as HRFS
    SYNOPSIS       This component specifies that the RAM disk is formatted as \
                   a Highly Reliable File System (HRFS). 
    REQUIRES       INCLUDE_HRFS_FORMAT
    }

Selection SELECT_RAM_DISK_FORMAT
    {
    NAME            RAM disk format selection
    SYNOPSIS        Selects the file system format for the RAM disk.
    COUNT           1-1
    CHILDREN        INCLUDE_RAM_DISK_FORMAT_NONE   \
                    INCLUDE_RAM_DISK_FORMAT_ANY    \
                    INCLUDE_RAM_DISK_FORMAT_DOSFS  \
                    INCLUDE_RAM_DISK_FORMAT_HRFS
    DEFAULTS        INCLUDE_RAM_DISK_FORMAT_NONE
    }

Component INCLUDE_RAM_DISK
    {
    NAME            RAM disk
    SYNOPSIS        This component creates an XBD-based RAM disk.
    CFG_PARAMS      RAM_DISK_BLK_SIZE      \
                    RAM_DISK_SIZE          \
                    RAM_DISK_DEV_NAME
    INIT_RTN        usrRamDiskInit       (RAM_DISK_BLK_SIZE,        \
                                          RAM_DISK_SIZE,            \
                                          FALSE,                    \
                                          RAM_DISK_DEV_NAME);
    CONFIGLETTES    usrRamDisk.c
    HDR_FILES       xbdRamDisk.h
    REQUIRES        INCLUDE_XBD_RAMDRV \
                    SELECT_RAM_DISK_FORMAT
    }

Parameter RAM_DISK_BLK_SIZE
    {
    NAME            RAM disk block size
    SYNOPSIS        This parameter specifies the RAM disk block size.
    TYPE            unsigned
    DEFAULT         512
    }

Parameter RAM_DISK_SIZE
    {
    NAME            RAM disk size
    SYNOPSIS        This parameter specifies the amount of RAM (in bytes) \
                    allocated for the RAM disk. 
    TYPE            unsigned
    DEFAULT         0x10000
    }

Parameter RAM_DISK_DEV_NAME
    {
    NAME            RAM disk logical device name
    SYNOPSIS        This parameter sets the default RAM disk device name.
    TYPE            string
    DEFAULT         "/ram0"
    }

