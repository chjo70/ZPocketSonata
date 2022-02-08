/* 20comp_dosfs.cdf - DOS File System component */

/*
 * Copyright 2014 - 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
09sep15,yjl  Fix V7STO-481, add doc about DOSFS_COMPAT_NT
18feb14,ghs  re-write.
*/

/*
DESCRIPTION
This file contains the description for DOS File System component.
*/

/* DosFs 2.0 module description */

Parameter DOSFS_DEFAULT_MAX_FILES
    {
    NAME            Default maximum open files (DosFs)
	SYNOPSIS		Defines the maximum number of files. The default is 20.
    TYPE            int
    DEFAULT         20
    }

Parameter DOSFS_DEFAULT_CREATE_OPTIONS
    {
    NAME            Default DosFs Create Options
	SYNOPSIS		The default parameter for the dosFsLib component. It \
					specifies the action to be taken when a dosFs file system \
					is instantiated. Its default is DOSFS_CHK_NONE, so the media \
					is not checked for errors on mount.
    TYPE            int
    DEFAULT         0x04      /* DOS_CHK_NONE */
    }

Parameter DOSFS_COMPAT_NT
    {
    NAME            DosFs Windows NT Compatible Option
    TYPE            bool
    SYNOPSIS        Directory entry NT flag compatibility with Windows, only used for FAT32.
                    If TRUE VxWorks has the same explanation about the field 
                    (offset 0x0c of directory entry) as Windows NT.
    DEFAULT         FALSE
    }

Parameter DOSFS_DEFAULT_DATA_DIR_CACHE_SIZE
    {
    NAME            Disk data and directory-group cache size
	SYNOPSIS		Defines the disk-data and directory-group cache size for each dosFs volume.
    TYPE            unsigned
    DEFAULT         0x800000 /* 8M */
    }

Parameter DOSFS_DEFAULT_FAT_CACHE_SIZE
    {
    NAME            Disk FAT group cache size
	SYNOPSIS		Defines the size of the FAT group cache for each dosFs volume.
    TYPE            unsigned
    DEFAULT         0x100000 /* 1M */
    }

Parameter DOSFS_BLOCKS_PER_DATA_DIR_CACHE_GROUP
    {
    NAME            Data/Dir block group size
	SYNOPSIS		Sets the default block group size in the Data/Dir cache.
    TYPE            unsigned
    DEFAULT         512
    }

Parameter DOSFS_BLOCKS_PER_FAT_CACHE_GROUP
    {
    NAME            Fat block group size
	SYNOPSIS		Sets the default block group size in the Fat cache.
    TYPE            unsigned
    DEFAULT         32
    }

Parameter DOSFS_CACHE_BACKGROUND_FLUSH_TASK_ENABLE
    {
    NAME            Enable background flush task for dosFs cache
	SYNOPSIS		The cache-flushing mode. Set to FALSE (default), cache-flushing \
					takes place in the context of the user's read/write task. Set to \
					TRUE, a separate high-priority task is spawned to carry out cache \
					flushing. Use of a separate task speeds up write operations \
					(especially when dosFs is configured with a larger cache size), but \
					using a separate high-priority task might not be suitable for \
					systems with strict real-time requirements.
    TYPE            bool
    DEFAULT         FALSE
    }

Parameter DOSFS_PRTMSG_LEVEL
    {
    NAME            Print message level
    SYNOPSIS        Print messages according to this value.
    TYPE            UINT32
    DEFAULT         1
    }

Parameter DOSFS_DEFAULT_VOL_BIO_BUFFER_SIZE
    {
    NAME            Default size in blocks of a bio data buffer
    SYNOPSIS        Default value is 32 (blocks)
    TYPE            UINT32
    DEFAULT         32
    }

Folder FOLDER_DOSFS
    {
    NAME            DosFs file system components (dosFs2)
    SYNOPSIS        DOS File System, and related components
    _CHILDREN       FOLDER_FILESYSTEM
    CHILDREN        INCLUDE_DOSFS_MAIN    \
                    INCLUDE_DOSFS_FAT     \
                    SELECT_DOSFS_DIR      \
                    INCLUDE_DOSFS_FMT     \
                    INCLUDE_DOSFS_CHKDSK  \
                    INCLUDE_XBD_TRANS     \
                    INCLUDE_DOSFS_CACHE   \
                    INCLUDE_DOSFS_SHOW    \
                    INCLUDE_DOSFS_PRTMSG_LEVEL \
                    INCLUDE_DOSFS_VOL_BIO_BUFFER_SIZE \
                    INCLUDE_DOSFS
    DEFAULTS        INCLUDE_DOSFS_MAIN     \
                    INCLUDE_DOSFS_FAT      \
                    INCLUDE_DOSFS_SHOW     \
                    INCLUDE_DOSFS_DIR_VFAT \
                    INCLUDE_DOSFS_PRTMSG_LEVEL \
                    INCLUDE_DOSFS_VOL_BIO_BUFFER_SIZE
    }

Selection SELECT_DOSFS_DIR
    {
    NAME            DOS file system directory handlers
    COUNT           1-
    CHILDREN        INCLUDE_DOSFS_DIR_VFAT INCLUDE_DOSFS_DIR_FIXED
    DEFAULTS        INCLUDE_DOSFS_DIR_VFAT
    }

Component INCLUDE_DOSFS_MAIN
    {
    NAME            dosfs File System Main Module (dosFs2)
    SYNOPSIS        MS-DOS-Compatible File System: dosFs main module
    MODULES         dosFsLib.o
    INIT_RTN        usrDosfsInit (DOSFS_DEFAULT_MAX_FILES, DOSFS_DEFAULT_CREATE_OPTIONS);
    CONFIGLETTES    usrDosfs.c
    CFG_PARAMS      DOSFS_DEFAULT_MAX_FILES       \
                    DOSFS_DEFAULT_CREATE_OPTIONS
    REQUIRES        INCLUDE_DOSFS_FAT      \
                    SELECT_DOSFS_DIR       \
                    INCLUDE_XBD            \
                    INCLUDE_FS_MONITOR     \
                    INCLUDE_IO_FILE_SYSTEM  \
                    INCLUDE_FS_EVENT_UTIL  \
                    INCLUDE_DOSFS_VOL_BIO_BUFFER_SIZE
    }

Component INCLUDE_DOSFS_FAT
    {
    NAME            DOS file system FAT12/16/32 handler
    SYNOPSIS        DosFs FAT12/16/32 FAT handler
    MODULES         dosFsFat.o
    REQUIRES        INCLUDE_DOSFS_MAIN
    }

Component INCLUDE_DOSFS_DIR_VFAT
    {
    NAME            DOS file system VFAT directory handler
    SYNOPSIS        VFAT Variable-length file names support, Win95/NT compatible
    MODULES         dosVDirLib.o
    REQUIRES        INCLUDE_DOSFS_MAIN
    CFG_PARAMS      DOSFS_COMPAT_NT
    }

Component INCLUDE_DOSFS_DIR_FIXED
    {
    NAME            DOS file system old directory format handler
    SYNOPSIS        Strict 8.3 and VxLongs proprietary long names
    MODULES         dosDirOldLib.o
    REQUIRES        INCLUDE_DOSFS_MAIN
    }

Component INCLUDE_DOSFS_FMT
    {
    NAME            DOS file system volume formatter module
    SYNOPSIS        High level formatting of DOS volumes
    MODULES         dosFsFmtLib.o
    REQUIRES        INCLUDE_RAWFS        \
                    INCLUDE_DOSFS_MAIN
    }

Component INCLUDE_DOSFS_CHKDSK
    {
    NAME            DOS file system consistency checker
    SYNOPSIS        Consistency checking set on per-device basis
    MODULES         dosChkLib.o
    REQUIRES        INCLUDE_DOSFS_MAIN
    }

Component INCLUDE_DOSFS_CACHE
    {
    NAME            Dos FS cache handler
    SYNOPSIS        Dos FS cache size is set on per-device basis
    MODULES         dosFsCacheLib.o
    HDR_FILES       dosFsLib.h
    INIT_RTN        dosFsCacheLibInit (DOSFS_DEFAULT_DATA_DIR_CACHE_SIZE, \
                                       DOSFS_DEFAULT_FAT_CACHE_SIZE, \
                                       DOSFS_CACHE_BACKGROUND_FLUSH_TASK_ENABLE);
    LINK_SYMS       dosFsCacheCreate
    CFG_PARAMS      DOSFS_DEFAULT_DATA_DIR_CACHE_SIZE \
                    DOSFS_BLOCKS_PER_DATA_DIR_CACHE_GROUP \
                    DOSFS_DEFAULT_FAT_CACHE_SIZE \
                    DOSFS_BLOCKS_PER_FAT_CACHE_GROUP \
                    DOSFS_CACHE_BACKGROUND_FLUSH_TASK_ENABLE
    REQUIRES        INCLUDE_DOSFS_MAIN
    }

Component INCLUDE_DOSFS_SHOW
    {
    NAME            Dos FS show routines
    SYNOPSIS        Includes the show routines for Dos FS provided by the dosFsShow library.
    MODULES         dosFsShow.o
    HDR_FILES       dosFsLib.h
    INIT_RTN        dosFsShowInit();
    REQUIRES        INCLUDE_DOSFS_MAIN
    INCLUDE_WHEN    INCLUDE_DOSFS_MAIN
    }

Component INCLUDE_DOSFS_PRTMSG_LEVEL
    {
    NAME            Print message level
    SYNOPSIS        Print messages accoding to DOSFS_PRTMSG_LEVEL
    CFG_PARAMS      DOSFS_PRTMSG_LEVEL
    }

Component INCLUDE_DOSFS_VOL_BIO_BUFFER_SIZE
    {
    NAME            Dos FS BIO buffer size
    SYNOPSIS        Volume bio buffer size can be set for performance
    CFG_PARAMS      DOSFS_DEFAULT_VOL_BIO_BUFFER_SIZE
    REQUIRES        INCLUDE_DOSFS_MAIN
    }

/* Backward compatible configuration */

Component INCLUDE_DOSFS
    {
    NAME            DOS filesystem backward-compatibility
    SYNOPSIS        Old dosFs API module, depreciated

    REQUIRES        INCLUDE_DOSFS_MAIN        \
                    INCLUDE_DOSFS_DIR_VFAT    \
                    INCLUDE_DOSFS_DIR_FIXED   \
                    INCLUDE_DOSFS_FAT         \
                    INCLUDE_DOSFS_CHKDSK      \
                    INCLUDE_DOSFS_FMT
    }

