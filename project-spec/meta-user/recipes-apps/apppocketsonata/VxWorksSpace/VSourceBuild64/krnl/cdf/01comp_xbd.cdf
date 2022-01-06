/* 00comp_hrfs.cdf - Highly Reliable File System component */

/*
 * Copyright 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22jan17,jbm  Editing, fixed blank SYNOPSIS, removed tabs
17nov14,yjl  Provide a VSB or cdf configure to change
             the stack size of "tXbdService" task (V7STO-204)
07may14,m_y  add INCLUDE_XBD_BLK_CACHE (US15841)
17feb14,ghs  re-write
*/

/*
DESCRIPTION
This file contains the description for the HRFS component.
*/

Folder FOLDER_BDM
    {
    NAME            Block device management
    SYNOPSIS        This folder contains components and parameters related \
                    to block device management.
    _CHILDREN       FOLDER_STORAGE
    CHILDREN        INCLUDE_XBD                \
                    INCLUDE_XBD_BLK_DEV        \
                    INCLUDE_XBD_RAMDRV         \
                    INCLUDE_XBD_PART_LIB       \
                    INCLUDE_XBD_BLK_CACHE
    }



Parameter XBD_BLK_DEV_TASK_PRIORITY
    {
    NAME            Service task priority
    TYPE            int
    DEFAULT         200
    }

Parameter XBD_BLK_DEV_TASK_STACK_SIZE
    {
    NAME            Service task stack size
    TYPE            int
    DEFAULT         4096
    }

Parameter XBD_BLK_DEV_DIRECT_BIO_HANDLING
    {
    NAME            Direct BIO handling mode
    TYPE            BOOL
    DEFAULT         FALSE
}

Component INCLUDE_XBD
    {
    NAME            Extended block device support
    SYNOPSIS        This component includes support for an extended block device. 
    MODULES         xbd.o                  \
                    bio.o
    INIT_RTN        xbdInit ();
    REQUIRES        INCLUDE_DEVICE_MANAGER \
                    INCLUDE_IO_REMOVABLE
    INCLUDE_WHEN    INCLUDE_HRFS           \
                    INCLUDE_HRFS_READONLY  \
                    INCLUDE_RAWFS          \
                    INCLUDE_CDROMFS        \
                    INCLUDE_XBD_TRANS      \
                    INCLUDE_DOSFS
    }

Component INCLUDE_XBD_BLK_DEV
    {
    NAME            XBD block device (legacy)
    SYNOPSIS        This component provides support for legacy block devices \
                    that are designed to work the predecessor to XBD: the \
                    cache block I/O (CBIO) facility. It provides a wrapper XBD \
                    facility that converts the block I/O driver interface \
                    based on the BLK_DEV logical block device structure into an \
                    XBD API-compliant interface. \
                    NOTE: The Wind River devices that require the \
                    INCLUDE_XBD_BLK_DEV component in addition to INCLUDE_XBD \
                    are floppy and TrueFFS (the disk-access emulator for flash) \
                    drivers. Any third-party device drivers based on the \
                    BLK_DEV interface also require INCLUDE_XBD_BLK_DEV. The \
                    Wind River drivers that do not require the \
                    INCLUDE_XBD_BLK_DEV component are USB block storage, ATA, \
                    and the XBD RAM disk. \
                    CAUTION: Depending on the implementation of the driver, \
                    the INCLUDE_XBD_BLK_DEV component may not properly detect \
                    media insertion and removal. It may, therefore remove the \
                    file system when the media is removed, or not instantiate \
                    a file system when media is inserted.
    HDR_FILES       xbdBlkDev.h
    INIT_RTN        xbdBlkDevLibInit (XBD_BLK_DEV_TASK_PRIORITY, \
                                      XBD_BLK_DEV_TASK_STACK_SIZE, \
                                      XBD_BLK_DEV_DIRECT_BIO_HANDLING);
    MODULES         xbdBlkDev.o
    CFG_PARAMS      XBD_BLK_DEV_TASK_PRIORITY \
                    XBD_BLK_DEV_TASK_STACK_SIZE \
                    XBD_BLK_DEV_DIRECT_BIO_HANDLING
    REQUIRES        INCLUDE_XBD
    }

Parameter XBD_BLK_CACHE_DEF_NODE_COUNT
    {
    NAME            Default XBD block cache node count
    SYNOPSIS        This parameter specifies the default XBD cache node count.
    TYPE            int
    DEFAULT         16
    }

Parameter XBD_BLK_CACHE_DEF_NODE_SIZE
    {
    NAME            Default XBD block cache node size
    TYPE            int
    DEFAULT         16384
    }

Component INCLUDE_XBD_BLK_CACHE
    {
    NAME            XBD block cache
    SYNOPSIS        This component includes the XBD block cache. 
    INIT_RTN        xbdBlkCacheInit (XBD_BLK_CACHE_DEF_NODE_COUNT, \
                                     XBD_BLK_CACHE_DEF_NODE_SIZE);
    MODULES         xbdBlkCache.o
    CFG_PARAMS      XBD_BLK_CACHE_DEF_NODE_COUNT \
                    XBD_BLK_CACHE_DEF_NODE_SIZE
    REQUIRES        INCLUDE_XBD
    }

Component INCLUDE_XBD_RAMDRV
    {
    NAME            XBD RAM drive
    SYNOPSIS        This component provides support for RAM disks. For more \
                    information, see the RAM disk topics in the VxWorks 7 \
                    programmer's guide.
    LINK_SYMS       xbdRamDiskDevCreate
    REQUIRES        INCLUDE_XBD
    }

Component INCLUDE_XBD_PART_LIB
    {
    NAME            XBD disk partition handler
    SYNOPSIS        VxWorks provides support for PC-style disk partitioning with the \
                    INCLUDE_XBD_PART_LIB component, which facilitates sharing \
                    fixed disks and removable cartridges between VxWorks target \
                    systems and PCs running Windows. This component includes two \
                    modules: xbdPartition, which manages partitions; and partLib, \
                    which provides partitioning facilities. The xbdPartition \
                    facility creates a device for each partition that is \
                    detected on media. Each partition that is detected is probed by \
                    the file system monitor and an I/O device is added to VxWorks. \
                    This device is an instantiation of the file system found by \
                    the file system monitor (or rawFs, if the file system is not \
                    recognized or detected). If no partitions are detected, a single \
                    device is created to represent the entire media. There can be up \
                    to four partitions on a single media.
    REQUIRES        INCLUDE_XBD \
                    INCLUDE_RAWFS
    LINK_SYMS       partLibCreate xbdCreatePartition
    }

