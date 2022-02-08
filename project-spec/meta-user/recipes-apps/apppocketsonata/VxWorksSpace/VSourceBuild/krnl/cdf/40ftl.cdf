/* 40ftl.cdf - flash management component */

/*
 * Copyright 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,03jul13,jxu  added INCLUDE_FLASH_SIM_FTL and INCLUDE_FLASH_SIM_TFFS 
01d,14nov12,jxu  removed _INIT_ORDER of ftl components and instead added them
                 to usrIosExtraInit().
01c,08nov12,jxu  added ftl show component.
01b,22oct12,jxu  WIND00383785: auto mount failed. The ftl cache component 
                 should be initialized before ftl.
01a,09mar12,jxu  written.
*/

/*
DESCRIPTION
This file contains the description for the flash translation layer (FTL) 
component.
*/

Parameter FTL_SERVICE_TASK_ENABLE 
    {
    NAME	        Enables ftl background service task
    SYNOPSIS        Creates a background task for performing time-consuming operations including garbage collection, wear-leveling, discarding (optional) and flushing cache (optional). 
    TYPE            BOOL
    DEFAULT	        TRUE 
    }

Parameter FTL_MEM_BUDGET_CFG_PROFILE
    {
    NAME           Configure the memory budget for ftl
    SYNOPSIS       (0 - minimum memory, 1 - moderate memory (default), 2 - maximum memory). The minimum memory profile will make ftl use the minimum memory that it requires to work, which trades time for space. The maximum memory means that ftl can allocate memory for use when it deems it's necessary for performance's sake. The moderate memory indicates a balance between the other two profiles.
    TYPE           int
    DEFAULT        2 
    }

Parameter FTL_AUTO_MOUNT
    {
    NAME	       FTL-managed device auto-mount
    SYNOPSIS       Mounts all the ftl managed devices detected at system boot phase when set to true.
    TYPE            BOOL
    DEFAULT	        FALSE 
    }
    
Parameter FTL_DATA_CACHE_SIZE
    {
    NAME	        Data cache size
    SYNOPSIS        Sets the data cache size (in bytes) for each mounted ftl device 
    TYPE	        unsigned	
    DEFAULT	        0x400000        /* 4MB */ 
    }

Component INCLUDE_FTL
    {
    NAME           Flash Translation Layer for NAND flash
    SYNOPSIS       It's the main component for managing raw NAND flash. It implements the basic functionalities including garbage collection, wear-leveling, bad block management, data caching and mapping.
    MODULES        ftlLbd.o ftlMap.o ftlMeta.o ftlGc.o ftlWl.o ftlBm.o \
                   ftlMtd.o ftlMount.o ftlTask.o ftlUtil.o ftlXbd.o \
                   ftlVx.o
    INIT_RTN       usrFtlInit (FTL_MEM_BUDGET_CFG_PROFILE, FTL_SERVICE_TASK_ENABLE, FTL_AUTO_MOUNT, 0);
    CONFIGLETTES   usrFtl.c
    HDR_FILES      ftlLib.h
    INIT_AFTER     INCLUDE_MTD 
    CFG_PARAMS     FTL_MEM_BUDGET_CFG_PROFILE   \
                   FTL_SERVICE_TASK_ENABLE      \
                   FTL_AUTO_MOUNT
    REQUIRES       INCLUDE_XBD                  \
                   INCLUDE_IO_FILE_SYSTEM       \
                   INCLUDE_FS_MONITOR
    }

Component INCLUDE_FTL_FORMAT
    {
    NAME           FTL format library
    SYNOPSIS	 This library implements functionality of formatting a flash device and \
			 making the device ready for use by upper layers of ftl. It provides two \
			 APIs for formatting flash devices. The recommended one for use between \
			 them is the ftlAdvFormat. It takes more flexible arguments than the \
			 ftlFormat that only accept a fixed number of arguments. The ftlFormat \
			 is easier for use in interactive enivonment through.
    MODULES        ftlFormat.o
    INIT_RTN       ftlFormatLibInit ();
    HDR_FILES      ftlLib.h
    REQUIRES       INCLUDE_RAWFS \
                   INCLUDE_FTL
    INIT_AFTER     INCLUDE_RAWFS
    }

Component INCLUDE_FTL_SHOW
    {
    NAME           FTL show library 
    SYNOPSIS       It provides various routines for displaying the internals of ftl managed flash devices, which can be used for debugging or evaluation.
    MODULES        ftlShow.o
    INIT_RTN       ftlShowLibInit();
    HDR_FILES      ftlLib.h
    REQUIRES       INCLUDE_RAWFS \
                   INCLUDE_FTL
    INIT_AFTER     INCLUDE_RAWFS
    }

Component INCLUDE_FTL_DISCARD
    {
    NAME           FTL discard support
    SYNOPSIS       Support reclaiming the spaces discarded by file system. It's benefitial for performance in most cases.
    MODULES        ftlDiscard.o
    INIT_RTN       ftlDiscardLibInit ();
    HDR_FILES      ftlLib.h
    REQUIRES       INCLUDE_FTL
    }

Component INCLUDE_FTL_CACHE
    {
    NAME           FTL data cache 
    SYNOPSIS       FTL data cache is intended for better performance by caching hot data in main memory without accessing the flash device for each I/O request.
    MODULES        ftlCache.o
    INIT_RTN       usrFtlCacheInit (FTL_DATA_CACHE_SIZE);
    CONFIGLETTES   usrFtl.c
    INIT_BEFORE    INCLUDE_FTL
    HDR_FILES      ftlLib.h
    CFG_PARAMS     FTL_DATA_CACHE_SIZE
    REQUIRES       INCLUDE_FTL
    }

Component INCLUDE_FLASH_SIM
    {
    NAME           Flash simulator library
    SYNOPSIS       Flash simulator can be used to simulate both NAND and NOR flash with different geometry. 
    MODULES        fsimLib.o
                   fsimChip.o
    }

Component INCLUDE_FLASH_SIM_FTL
    {
    NAME           Flash simulator support for FTL
    MODULES        fsimMtd.o
    }

Component INCLUDE_FLASH_SIM_TFFS
    {
    NAME           Flash simulator support for TFFS 
    MODULES        fsimTffs.o
    }

Folder FOLDER_FTL
    {
    NAME           Flash Translation Layer for NAND flash
    SYNOPSIS       FTL and related components 
    CHILDREN       INCLUDE_FTL                   \
                   INCLUDE_FTL_FORMAT            \
                   INCLUDE_FTL_CACHE             \
                   INCLUDE_FTL_DISCARD           \
                   INCLUDE_FTL_SHOW              \
                   INCLUDE_FLASH_SIM             \
                   INCLUDE_FLASH_SIM_FTL         \
                   INCLUDE_FLASH_SIM_TFFS
    DEFAULTS       INCLUDE_FTL
                   INCLUDE_FTL_FORMAT
    _CHILDREN      FOLDER_FLASH
    }

