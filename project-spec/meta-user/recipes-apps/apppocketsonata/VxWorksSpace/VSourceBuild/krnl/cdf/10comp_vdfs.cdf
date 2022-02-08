/* 10comp_vdfs.cdf - Virtual Disk File System component */

/*
 * Copyright 2015,2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27oct17,jsp  add support for priority scheduling
15aug17,jsp  update the number of open file descriptors (HYP-12099)
17feb15,dcc  re-write
*/

/*
DESCRIPTION
This file contains the description for virtual disk file system component.
*/

Folder FOLDER_DEVFS
    {
    NAME            Virtual Disk file system
    SYNOPSIS        Virtual Disk file system interface
    CHILDREN        INCLUDE_VDFS
    }

Component INCLUDE_VDFS
    {
    NAME            Virtual Disk filesystem
    SYNOPSIS        Virtual Disk file system interface
    MODULES         vdFsLib.o
    INIT_RTN        vdFsInit (NUM_VDFS_FILES);
    CFG_PARAMS      NUM_VDFS_FILES	    \
		    VDFS_PRIO_SCHED_ENABLE  \
		    VDFS_PRIO_SCHED_TIMEOUT
    HDR_FILES       vdFsLib.h
    REQUIRES        INCLUDE_FS_MONITOR	    \
		    INCLUDE_FS_EVENT_UTIL   \
		    INCLUDE_TIMESTAMP64
    CONFIGLETTES    usrVdfs.c
    }

Parameter NUM_VDFS_FILES
    {
    NAME            max # open VDFS files
    TYPE            uint
    DEFAULT         64
    }

Parameter VDFS_PRIO_SCHED_ENABLE
    {
    NAME	    Enables exclusive access to media by high priority blocks
    SYNOPSIS	    This parameter enables a simple scheduler in VDFS that \
		    ensures exclusive access for a defined amount of time for \
		    high priority blocks.
    TYPE	    exists
    DEFAULT	    FALSE
    }

Parameter VDFS_PRIO_SCHED_TIMEOUT
    {
    NAME	    Timeout in microseconds for high priority blocks
    SYNOPSIS	    This value reflacts the amount of time high priority \
		    blocks from different guests are permitted exclusive \
		    access to shared media.
    TYPE	    uint
    DEFAULT	    100
    }
