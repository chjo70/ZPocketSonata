/* usrRamDisk.c - POSIX advisory file locking */

/*
 * Copyright 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24jul17,ghs  clean build warning (V7STO-904)
14Jun16,lyj  written.

*/


/* includes */
#ifndef _INCusrRamDiskc
#define _INCusrRamDiskc

#include "vxWorks.h"
#include "xbdRamDisk.h"

#if defined(INCLUDE_DOSFS_FMT)
#include <dosFsLib.h>
#endif

#if defined(INCLUDE_HRFS_FORMAT)
#include <hrFsLib.h>
#endif

/* defines */
void usrRamDiskInit(unsigned blockSize, unsigned totalSize, BOOL flag, const char * name);
/* typedefs */

/* globals */

/* externs */

void usrRamDiskInit
    (
    unsigned      blockSize,
    unsigned      totalSize,
    BOOL          flag,
    const char *  name
    )
    {
    device_t ramDiskDevice;
    STATUS formatStatus = OK;

    ramDiskDevice = xbdRamDiskDevCreate (blockSize, totalSize, flag,name);

    if (ramDiskDevice == NULLDEV)
        {
        printf ("usrRamDiskInit: RAM disk device creation failed!\n");
        return;
        }

#if defined (INCLUDE_RAM_DISK_FORMAT_NONE)
    return;
#elif defined (INCLUDE_RAM_DISK_FORMAT_ANY)
#if defined(INCLUDE_HRFS_FORMAT)
    formatStatus = hrfsFormat ((char *)name, 0, 0, 0);
#elif defined(INCLUDE_DOSFS_FMT)
    formatStatus = dosFsVolFormat (name, 0, 0);
#else
    printf ("usrRamDiskInit: No file systems have been included!\n");
#endif
#elif defined (INCLUDE_RAM_DISK_FORMAT_DOSFS)
#if defined (INCLUDE_DOSFS_FMT)
    formatStatus = dosFsVolFormat (name, 0, 0);
#else
    printf ("usrRamDiskInit: No file system have been included!\n");
#endif
#elif defined (INCLUDE_RAM_DISK_FORMAT_HRFS)
#if defined (INCLUDE_HRFS_FORMAT)
    formatStatus = hrfsFormat ((char *)name, 0, 0, 0);
#else
    printf ("usrRamDiskInit: No file system have been included!\n");
#endif
#endif

    if (formatStatus == ERROR)
        {
        printf ("usrRamDiskInit: format error: errno = 0x%x\n", errnoGet());
        }

    return;
    }

#endif /* end of _INCusrRamDiskc */

                                  
