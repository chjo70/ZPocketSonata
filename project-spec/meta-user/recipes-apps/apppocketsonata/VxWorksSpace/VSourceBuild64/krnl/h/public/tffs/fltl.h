/* fltl.h - True Flash File System */

/*
 * Copyright (c) 1984-2004, 2010, 2013, 2016 Wind River Systems, Inc.
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
28mar13,jxu  eTFFS: added getFreeSectors and validateSector
29jul10,pad  Moved extern C statement after include statements.
29jul04,alr  modified file header, restarted history
*/

#ifndef FLTL_H
#define FLTL_H

#include "flflash.h"

#ifdef __cplusplus
extern "C" {
#endif

/* See interface documentation of functions in ftllite.c	*/

typedef struct tTL TL;		/* Forward definition */
typedef struct tTLrec TLrec; 	/* Defined by translation layer */

struct tTL 
    {
    TLrec *     rec;

    const void FAR0 *(*mapSector) (TLrec *, SectorNo sectorNo, 
            CardAddress *physAddr);
    FLStatus (*writeSector) (TLrec *, SectorNo sectorNo, 
            void FAR1 *fromAddress);
    FLStatus (*deleteSector) (TLrec *, SectorNo sectorNo, unsigned int noOfSectors);

    FLStatus (*validateSector) (TLrec *, SectorNo sectorNo, 
            char FAR1 * userBuffer);

    void (*tlSetBusy) (TLrec *, FLBoolean);
    void (*dismount) (TLrec *);

#if defined(DEFRAGMENT_VOLUME) || defined(SINGLE_BUFFER)
    FLStatus (*defragment) (TLrec *, unsigned int FAR2 *bytesNeeded);
    SectorNo (*getFreeSectors) (TLrec *, unsigned int * pDefragNeeded, unsigned int * pWlNeeded);
#endif

#ifdef FORMAT_VOLUME
    SectorNo (*sectorsInVolume) (TLrec *);
#endif
    };

#ifdef FORMAT_VOLUME

#ifdef __cplusplus
}
#endif

#include "dosformt.h"

#ifdef __cplusplus
extern "C" {
#endif

#endif /* FORMAT_VOLUME */

/* Translation layer registration information */

extern int noOfTLs;	/* No. of translation layers actually registered */

typedef struct 
    {
    FLStatus (*mountRoutine) (FLFlash *flash, TL *tl, FLFlash **volForCallback);
#ifdef FORMAT_VOLUME
    FLStatus (*formatRoutine) (FLFlash *flash, FormatParams FAR1 *formatParams);
#endif
    } TLentry;

extern TLentry tlTable[];

extern FLStatus	flMount(unsigned volNo, TL *, FLFlash *);

#ifdef FORMAT_VOLUME
extern FLStatus	flFormat(unsigned, FormatParams FAR1 *formatParams);
#endif

#ifdef __cplusplus
}
#endif

#endif /* FLTL_H */

