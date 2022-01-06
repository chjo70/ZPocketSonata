/* usrRomfs.c - ROMFS initialization */

/* Copyright 2003, 2009, 2014, 2015 Wind River Systems, Inc. */

/*
modification history
--------------------
01sep15,clt  Added configurable romfs device name (F4862)
14aug15,j_x  cleanup VIP build warnings (V7RAD-554)
11mar14,ghs  Fix CID 103578
14may09,zly  LP64 support 
07jul04,c_c  Don't use romfs_image.h anymore.
15may03,md   written.
*/

/*
DESCRIPTION
This file is included by bootConfig.c and usrConfig.c. The file contains
routines for configuring a ROMFS file system using the system default
image.

SEE ALSO: usrExtra.c

NOMANUAL
*/

#ifndef  __INCusrRomfs
#define  __INCusrRomfs

/* includes */
#include "romfsLib.h"			/* read-only file system interfaces */
#include "romfsDrv.h"			/* romfs block device driver */
#include <stdio.h>


/* 
 * ROM filesystem image will come from romfs_image.o object file, which defines
 * two symbols (see below): 
 */

extern const char romfsImage[];               /* The file system */
extern const char romfsImageEnd[];    /* address of its end */

/* forward declarations */
STATUS usrRomfsConfig (void);

/*******************************************************************************
*
* usrRomfsConfig - mount the file system romfs image
*
* This routine mounts the included file system image on the /romfs mount point.
*
* RETURNS: OK or ERROR.
*
* SEE ALSO:
* .pG "I/O System, Local File Systems"
*/

STATUS usrRomfsConfig (void)
    {
    int romfsImageLen = (int)(romfsImageEnd - romfsImage);     /* size of ROM fs */
    char *pName = ROMFS_DEV_NAME;

    if (romfsImageLen != 0)
        {
        BLK_DEV * pBlkDev;

        pBlkDev = (BLK_DEV *)romfsBlkDevCreate((char *)&romfsImage,
                                               romfsImageLen, 0);
        if (pBlkDev == NULL)
            {
            printErr ("Error creating romfs block device!\n");
            return (ERROR);
            }
        if ((pName == NULL)||(*pName == '\0'))
            {
            (void)romfsFsDevCreate ("/romfs", pBlkDev);
            }
        else
            {
            (void)romfsFsDevCreate (pName, pBlkDev);
            }
        }
    return (OK);
    }

#endif /* __INCusrRomfs */
