/* flcustom.h - True Flash File System */

/* Copyright 1984-2004, 2011, 2016 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/* FAT-FTL Lite Software Development Kit
 * Copyright (C) M-Systems Ltd. 1995-1997	*/

/*
modification history
--------------------
21nov16,ffu  add LP64 support in TFFS layer (F4496)
26feb16,ffu  TFFS_HIGH_FAULT_TOLERANCE, TFFS_BACKGROUND_TASK and TFFS_TRUE_STATIC_WL
             handled as vsb config(V7STO-342)
07may13,jxu  eTFFS: added TFFS_FAST_MOUNT, TFFS_HIGH_FAULT_TOLERANCE and
             TFFS_TRUE_STATIC_WL
21mar11,zly  requirement WIND00239771  
29jul04,alr  activated DEFRAGMENT_VOLUME
29jul04,alr  modified file header, restarted history
*/

#ifndef FLCUSTOM_H
#define FLCUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

/* This file is intended for modification only by TFFS SOURCE
 * customers. Customers with the binary distribution of the product 
 * should not modify this file.
 */


/*
 *
 *		Section 2: File System Customization
 *		------------------------------------
 */

/* ISSUE #2.1: Number of drives
 *
 * Defines the maximum number of drives (and sockets) supported.
 *
 * The actual number of drives depends on which socket controllers are
 * actually registered.
 */

#define DRIVES	5


/* ISSUE #2.1: Number of open files (OBSOLETE)
 *
 * Defines the maximum number of files that may be open at a time.
 */

/*#define FILES	  0*/


/* ISSUE #2.2: Sector size
 *
 * Define the log2 of sector size for the FAT & FTL layer. Note that the
 * default 512 bytes is the de-facto standard and practically the only one
 * that provides real PC interoperability.
 */

#define SECTOR_SIZE_BITS	9


/* ISSUE #2.3: Formatting
 *
 * Uncomment the following line if you need to format with fsFormatVolume.
 */

#define FORMAT_VOLUME


/* ISSUE #2.4: Defragmentation
 *
 * Uncomment the following line if you need to defragment with
 * fsDefragmentVolume.
 */

#define DEFRAGMENT_VOLUME

/* ISSUE #2.5: Sub-directories (OBSOLETE)
 *
 * Uncomment the following line if you need support for sub-directories
 */

/* #define SUB_DIRECTORY */


/* ISSUE #2.6: Rename file (OBSOLETE)
 *
 * Uncomment the following line if you need to rename files with fsRenameFile.
 */

/* #define RENAME_FILE */


/* ISSUE #2.7: Split / join file (OBSOLETE)
 *
 * Uncomment the following line if you need to split or join files with
 * fsSplitFile and fsJoinFile
 */

/* #define SPLIT_JOIN_FILE */


/* ISSUE #2.8: 12-bit FAT support (OBSOLETE)
 *
 * Comment the following line if you do not need support for DOS media with
 * 12-bit FAT (typically media of 2 MBytes or less).
 */

/*#define FAT_12BIT*/


/* ISSUE #2.9: Parse path function (OBSOLETE)
 *
 * Uncomment the following line if you need to parse DOS-like path names
 * with fsParsePath.
 */

/* #define PARSE_PATH */


/* ISSUE #2.10: Maximum supported medium size (OBSOLETE)
 *
 * Define here the largest Flash medium size (in MBytes) you want supported.
 */


/* limit is set to 2047 to avoid integer overflow warning */

#define MAX_VOLUME_MBYTES       2047 	


/* ISSUE #2.11: Assumed card parameters
 *
 * This issue is relevant only if you are not defining any allocation
 * routines in #5.2.
 *
 * The following are assumptions about FTL parameters of the Flash media.
 * They affect the size of the heap buffer allocated in FTLLITE.C.
 */

#define ASSUMED_FTL_UNIT_SIZE	0x20000l	/* Intel interleave-2 */
#define	ASSUMED_VM_LIMIT	0x10000l	/* limit at 64 KB */
#define ASSUMED_NFTL_UNIT_SIZE	0x4000l


/* ISSUE #2.12: Number of buffers
 *
 * Normally two sector buffers are needed, one for the FAT layer, another
 * for the FTL layer. You may save about 512 bytes of RAM requirements by
 * uncommenting the following definition.
 * This will come at the cost of both read and write performance.
 */

/*#define SINGLE_BUFFER */


/* ISSUE #2.13: Absolute read & write
 *
 * Uncomment the following line if you want to be able to read & write
 * sectors by absolute sector number (i.e. without regard to files and
 * directories).
 */

#define ABS_READ_WRITE


/* ISSUE #2.14: Low level operations
 *
 * Uncomment the following line if you want to do low level operations.
 * Low level operations include: read from a physical address, write to
 * a physical address, erase a unit according to its physical unit number.
 */

#define LOW_LEVEL


/* ISSUE #2.15: Application exit
 *
 * If the FLite application ever exits, it needs to call fsEXit before
 * exitting. Uncomment the following line to enable this.
 */

/* #define EXIT */


/* ISSUE #2.16: Number of sectors per cluster
 *
 * Define the minimum cluster size in sectors.
 */

#define MIN_CLUSTER_SIZE   4

/* ISSUE #2.17: fast mount 
 *
 * Optimized mounting process 
 */

#define TFFS_FAST_MOUNT

/* ISSUE #2.18: high fault tolerance 
 *
 * Achieving higher fault tolerance by:
 * - never writing in-place
 * - double BAM
 * - checksum of user data
 * By default, it's off, because it causes a little bit performance
 * degration due to the overhead of above listed additional operations.
 * TFFS_BACKGROUND_TASK handled as vsb config
 */

/* ISSUE #2.19: background task 
 *
 * Enabled background task for defragment when system is idle
 * TFFS_BACKGROUND_TASK handled as a vsb config
 */

#ifndef DEFRAGMENT_VOLUME
#undef _WRS_CONFIG_TFFS_BACKGROUND_TASK    /* depends on DEFRAGMENT_VOLUME */
#endif /* DEFRAGMENT_VOLUME */

/* ISSUE #2.20: true static wear-leveling 
 *
 * Enable true static wear-leveling to distribute erase across the
 * whole flash device as evenly as possible
 * TFFS_TRUE_STATIC_WL handled as vsb config
 */

#define TFFS_ENHANCEMENT        /* temporary! */

/*
 *
 *		Section 3: Socket Hardware Customization
 *		----------------------------------------
 */

/* ISSUE #3.1: Vpp voltage
 *
 * If your socket does not supply 12 volts, comment the following line. In
 * this case, you will be able to work only with Flash cards that do not
 * require external 12 Volt Vpp.
 *
 */

#define SOCKET_12_VOLTS


/* ISSUE #3.2: Fixed or removable media
 *
 * If your Flash media is fixed, uncomment the following line, and ignore
 * issue #3.3.
 */

/* #define FIXED_MEDIA */


/* ISSUE #3.3: Hardware card change detection
 *
 * This issue is now obsolete
 *
 */


/* ISSUE #3.4: Interval timer
 *
 * The following defines a timer polling interval in milliseconds. If the
 * value is 0, an interval timer is not installed.
 *
 * If you select an interval timer, you should provide an implementation
 * for 'installTimer' defined in timer.h.
 *
 * An interval timer is not a must, but it is recommended. The following
 * will occur if an interval timer is absent:
 *
 * - Card changes can be recognized only if socket hardware detects them
 *   (see issue #3.2).
 * - The Vpp delayed turn-off procedure is not applied. This may downgrade
 *   write performance significantly if the Vpp switching time is slow.
 * - The watchdog timer that guards against certain operations being stuck
 *   indefinitely will not be active.
 */

#define	POLLING_INTERVAL 100		/* Polling interval in millisec.
					   if 0, no polling is done */


/*
 *
 *		       Section 4: MTD Customization
 *		       ----------------------------
 */

/* ISSUE #4.1: MTD Installation
 *
 * This issue is now obsolete
 *
 */


/* ISSUE #4.2: Background erasing
 *
 * If you include support for Flash technology that has suspend-for-write
 * capability, you can gain considerable write performance and improve
 * real-time response for your write operations by including background erase
 * capability. In some cases, you can gain performance by including this
 * feature even if no suspend-for-write capability is supported. See the
 * FLite manual for complete details.
 *
 * On the other hand, this feature adds to required code & RAM, makes
 * necessary some additional customization on your part, and depends on
 * compiler features that, while defined as ANSI-C standard, may have
 * a problematic implementation in your particular environment. See the
 * FLite manual for complete details.
 *
 * Uncomment the following line to support background erasing.
 */

/* #define	BACKGROUND */


/* ISSUE #4.3: Maximum MTD's and Translation Layers
 *
 * Define here the maximum number of Memory Technology Drivers and
 * Translation Layers that may be installed. Note that the actual
 * number installed is determined by which components are installed in
 * 'registerComponents' (custom.c)
 */

#define MTDS	10	/* Up to 5 MTD's */

#define	TLS	5	/* Up to 3 Translation Layers */

/* 
 * register mtd identify for each drive, more fast, flexible and reasonable.
 * flash simulator works only when TFFS manages MTD identifies in this way.
 */

#define MTD_IDENTIFY_REGISTER

#ifdef __cplusplus
}
#endif

#endif
