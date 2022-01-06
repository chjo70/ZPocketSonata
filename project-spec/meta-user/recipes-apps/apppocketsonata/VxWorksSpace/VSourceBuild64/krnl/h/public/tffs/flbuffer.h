/* flbuffer.h - True Flash File System */

/*
 * Copyright (c) 1984-2004, 2010, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/* FAT-FTL Lite Software Development Kit
 * Copyright (C) M-Systems Ltd. 1995-1997	*/

/*
modification history
--------------------
02jun16,zly  revise previous changes.
11may16,zly  clean strick-aliasing warning.
29jul10,pad  Moved extern C statement after include statements.
29jul04,alr  modified file header, restarted history
*/

#ifndef FLBUFFER_H
#define FLBUFFER_H

#include "flbase.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Following macros are defined for testing purpose and could be
 * removed in future when the stuff controlled by them works well.
 */

#define TFFS_ENHANCEMENT        /* temporary! */

typedef struct
    {
    char                formatPattern[15];
    unsigned char       noOfTransferUnits;      /* no. of transfer units */
    LEulong             wearLevelingInfo;
    /*
     * jxu: the definition of unit number as short int type does lead to
     * a limication of flash size supported by ftl. This would prevent ftl
     * from being used on NOR Flash of large size.
     */
    LEushort            logicalUnitNo;
    unsigned char       log2SectorSize;
    unsigned char       log2UnitSize;
    LEushort            firstPhysicalEUN; /* units reserved for boot image */
    LEushort            noOfUnits;              /* no. of formatted units */
    LEulong             virtualMediumSize;  /* virtual size of volume */
    LEulong             directAddressingMemory;
                                        /* directly addressable memory */
    LEushort            noOfPages;      /* no. of virtual pages */
    unsigned char       flags;
    unsigned char       eccCode;
    LEulong             serialNumber;
    LEulong             altEUHoffset;
    LEulong             BAMoffset;
#ifdef TFFS_ENHANCEMENT
    char                reserved[8];
    /*
     * jxu: do checksum of unit header only if DOUBLE_BAI flag is enabled.
     * Doing checksum of the FTL meta data is necessary because the
     * NOR Flash is envolving this years to larger capacity with higher
     * bit-flip rate and any such kind of error might cause corruption of ftl.
     * NOTE: this is not specified by the pretty old FTL specification.
     * It would not cause any backward and forward compatibility issue.
     */

    LEushort            chksum; /* we used 2 bytes from reserved area
                                 * for storing CRC checksum of the header
                                 * itself.*/
    LEushort            secondLun;    /* second logical unit no */
#endif /* #ifdef TFFS_ENHANCEMENT */
    char                embeddedCIS[4]; /* Actual length may be larger. By */
                    /* default, this contains FF's */
    } UnitHeader;

typedef struct {
  union dataUnion
      {
      unsigned char data[SECTOR_SIZE];	/* sector buffer */
      UnitHeader    unitHdr;
      LEulong       leul;
      }dataUnion;

  SectorNo	sectorNo;		/* current sector in buffer */
  void		*owner;			/* owner of buffer */
  FLBoolean	dirty;			/* sector in buffer was changed */
  FLBoolean	checkPoint;		/* sector in buffer must be flushed */
} FLBuffer;

#ifdef __cplusplus
}
#endif

#endif /* FLBUFFER_H */
