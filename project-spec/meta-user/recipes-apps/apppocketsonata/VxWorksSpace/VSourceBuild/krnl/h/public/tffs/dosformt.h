/* dosformt.h - True Flash File System */

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
21nov16,ffu  add LP64 support in TFFS layer (F4496)
29jul10,pad  Moved extern C statement after include statements.
29jul04,alr  modified file header, restarted history
*/

#ifndef DOSFORMT_H
#define DOSFORMT_H

#include "flbase.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The BIOS parameter block (a part of the boot sector)		*/
/* Note that this is NOT the customary definition of the BPB    */
/* (customary is to start it on 'bytesPerSector'). To avoid the */
/* nuisance of a structure that starts at an odd offset, we add */
/* the first 11 bytes of the boot sector here.			*/
typedef struct {
  unsigned char	jumpInstruction[3];
  char		OEMname[8];
  Unaligned	bytesPerSector;
  unsigned char	sectorsPerCluster;
  LEushort	reservedSectors;
  unsigned char	noOfFATS;
  Unaligned	rootDirectoryEntries;
  Unaligned	totalSectorsInVolumeDOS3;
  unsigned char	mediaDescriptor;
  LEushort	sectorsPerFAT;
  LEushort	sectorsPerTrack;
  LEushort	noOfHeads;
  LEulong	noOfHiddenSectors;
  LEulong	totalSectorsInVolume;
} BPB;


typedef struct {
  BPB		bpb;
  unsigned char	physicalDriveNo;
  char		reserved0;
  char		extendedBootSignature;
  char		volumeId[4];
  char		volumeLabel[11];
  char		systemId[8];
  char		bootstrap[448];
  LEushort	signature;
} DOSBootSector;


typedef struct {
  char		name[11];
  unsigned char	attributes;		/* mapped below */
  unsigned char	reserved[10];
  LEushort	updateTime;
	/* The date field is encoded as follows:	      		*/
	/* 	bit 0-4:	Day of month (1-31)			*/
	/* 	bit 5-8:	Month (1-12)				*/
	/*	bit 9-15:	Year relative to 1980			*/
  LEushort	updateDate;
	/* The DOS time field is encoded as follows:			*/
	/*	bit 0-4:	seconds divided by 2 (0-29)		*/
	/*      bit 5-10:	minutes (0-59)				*/
	/*	bit 11-15:	hours (0-23)				*/
  LEushort	startingCluster;
  LEulong	fileSize;
} DirectoryEntry;


/* Directory entry attribute bits */

#define	ATTR_READ_ONLY	1
#define	ATTR_HIDDEN	2
#define	ATTR_SYSTEM	4
#define	ATTR_VOL_LABEL	8
#define	ATTR_DIRECTORY	0x10
#define	ATTR_ARCHIVE	0x20

#define DIRECTORY_ENTRY_SIZE	sizeof(DirectoryEntry)

#define DIRECTORY_ENTRIES_PER_SECTOR	(SECTOR_SIZE / DIRECTORY_ENTRY_SIZE)

#define	NEVER_USED_DIR_ENTRY	0
#define	DELETED_DIR_ENTRY	((char) 0xe5)


/* FAT definitions */

#define	FAT_FREE	 0
#define	FAT_BAD_CLUSTER	 0xfff7
#define	FAT_LAST_CLUSTER 0xffff		/* actually any of 0xfff8-0xffff */


/* Partition table definitions */

#define PARTITION_SIGNATURE	0xaa55

#define CYLINDER_SECTOR(cylinder,sector)	\
	((sector) + ((cylinder & 0xff) << 8) + ((cylinder & 0x300) >> 2))

typedef struct {
  char		reserved[0x1be];
  /* First partition entry starts here. We do not map it as a	*/
  /* separate structure because it is not longword aligned	*/
  unsigned char	activeFlag;	/* 80h = bootable */
  unsigned char startingHead;
  LEushort	startingCylinderSector;
  char		type;
  unsigned char	endingHead;
  LEushort	endingCylinderSector;
  Unaligned4	startingSectorOfPartition;
  Unaligned4	sectorsInPartition;
  /* Partition entries 2,3 and 4 are structured as the 1st partition */
  char		partition23and4[0x30];
  LEushort	signature;	/* = PARTITION_SIGNATURE */
} PartitionTable;

#ifdef __cplusplus
}
#endif

#ifdef FORMAT_VOLUME

#ifdef __cplusplus
extern "C" {
#endif

/* Formatting parameter structure definition */

typedef struct {
  /* FTL formatting section */
  unsigned int	bootImageLen;
		/* Space to reserve for a boot-image at the start of the
		   medium. The FLite volume will begin at the next higher
		   erase unit boundary */

  unsigned	percentUse;
		/* FTL performance depends on how full the Flash media is,
		   getting slower when the media is close to 100%. It is
		   possible to avoid the worst consequences of this effect by
		   formatting the media to less than 100% capacity, so
		   guaranteeing some free space at all times. This of course
		   sacrifices some capcity.
		   The standard value to use is 99 */

  unsigned	noOfSpareUnits;
		/* FTL needs at least one spare erase unit to function as a
		   read/write media (it is possible to specify 0 to achieve
		   WORM functionality). It is possible to specify more than
		   one spare unit, which costs more media space.
		   The advantage to doing this is in case one of the Flash
		   erase units becomes bad and unerasable in the future, one
		   of the spare units will need to replace it. A second spare
		   unit will then enable to continue read/write functionality
		   (in its absence, the media will go into read-only mode).
		   The standard value to use is 1 */

  unsigned int	vmAddressingLimit;
		/* A part of the FTL Virtual Map always resides in RAM. The
		   RAM part is the one that is used to address the part of
		   the media below the VM addressing limit. Reading and
		   writing to this part is usually faster to some degree.
		   The downside is that the bigger the limit, the more RAM
		   size is required.
		   To get the extra RAM requirement in bytes, divide the
		   limit by 128 or by 256, depending on whether you
		   specified in #2.9 more than 32 or not, respectively.
		   The minimum VM limit is 0.
		   The standard value to use is 0x10000 (first 64 KBytes) */

  FLStatus	(*progressCallback)(int totalUnitsToFormat,
				    int totalUnitsFormattedSoFar);
		/* Progress callback routine, will be called if not NULL.
		   The callback routine is called after erasing each unit,
		   and its parameters are the total number of erase units
		   to format and the number erased so far.
		   The callback routine returns a Status value. A value of
		   OK (0) allows formatting to continue. Any other value
		   will abort the formatting with the returned status code. */

  /* DOS formatting section */
  char		volumeId[4];
		/* Volume identification number */

  char FAR1 *	volumeLabel;
		/* Volume label string. If NULL, no label */

  unsigned 	noOfFATcopies;
		/* It is customary to format DOS media with 2 FAT copies.
		   The first copy is always used, but more copies make it
		   possible to recover if the FAT becomes corrupted (a
		   rare occurrence). On the other hand, this slows down
		   performance and uses media space.
		   The standard value to use is 2 */

  unsigned	embeddedCISlength;
		/* Length in bytes of CIS to embed after the unit header */

  char FAR1 *	embeddedCIS;
		/* The unit header is structured as a beginning of a PCMCIA
		   'tuple' chain (a CIS). The unit header contains a
		   data-organization tuple, which points past the end of the
		   unit header to a location which usually just contains
		   hex FF's which mark an 'end-of-tuple-chain'. Optionally,
		   it is possible to embed an entire CIS chain at this
		   location. If so, 'embeddedCISlength' marks the length in
		   bytes */

} FormatParams;

/* Standard initializer for FormatParams structure */
#define STD_FORMAT_PARAMS	{0, 99, 1, 0x10000l, NULL, {0,0,0,0}, NULL, 2, 0, NULL}

#ifdef __cplusplus
}
#endif

#include "fltl.h"

#ifdef __cplusplus
extern "C" {
#endif

extern FLStatus flDosFormat(TL *, FormatParams FAR1 *formatParams);

#ifdef __cplusplus
}
#endif

#endif /* FORMAT_VOLUME */

#endif /* DOSFORMT_H */

