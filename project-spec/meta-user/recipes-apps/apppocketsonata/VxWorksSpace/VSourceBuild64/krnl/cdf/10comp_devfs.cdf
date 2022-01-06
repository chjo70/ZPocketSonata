/* 10comp_devfs.cdf - Device File System component */

/*
 * Copyright 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17feb14,ghs  re-write
*/

/*
DESCRIPTION
This file contains the description for device file system component.
*/

Folder FOLDER_DEVFS
    {
    NAME            Device file system
    SYNOPSIS        Device file system interface
    CHILDREN        INCLUDE_RAWFS
    }

Component INCLUDE_RAWFS
    {
    NAME            raw filesystem
    SYNOPSIS        Raw block device file system interface
    MODULES         rawFsLib.o
    INIT_RTN        rawFsInit (NUM_RAWFS_FILES);
    CFG_PARAMS      NUM_RAWFS_FILES
    HDR_FILES       rawFsLib.h
    REQUIRES        INCLUDE_FS_MONITOR INCLUDE_FS_EVENT_UTIL
    }

Parameter NUM_RAWFS_FILES
    {
    NAME            max # open RAWFS files
    TYPE            uint
    DEFAULT         5
    }

