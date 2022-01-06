/* romfsLib.h - ROMFS file system driver */

/*
 * Copyright 2003, 2009-2010, 2014-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jul17,ghs  integrate file system type magic number (F9150)
01sep15,clt  Added romfsVolumeCreate() (F4862)
01dec14,clt  Added Cert support
27may10,pad  Moved extern C statement after include statements.
07may09,zly  LP64 support
05may03,md   written
*/

#ifndef romfsLib_h
#define romfsLib_h

#include <vxWorks.h>
#include <sys/types.h>
#include <iosLib.h>
#include <blkIo.h>
#include <private/semLibP.h>
#include <romfsDrv.h>
#ifdef _WRS_CONFIG_FS_COMMON
#include <fsEventUtilLib.h>
#endif
#include <sys/stat.h>
#include <spinLockLib.h>
#include <poolLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* block size of underlying device */

#define DEV_BSIZE   ROMFS_BLOCK_SIZE

typedef struct romfsVolDescr    /* volume descriptor, one per mounted volume */
    {
    DEV_HDR        devHdr;           /* for adding to device table            */
    BLK_DEV  *     pBlkDev;          /* pointer to block device structure     */
    int            magic;            /* magic number                          */
    u_char         cache[DEV_BSIZE]; /* buffer cache for one block            */
    int            cBlockNum;        /* cached block number                   */
    SEM_ID         devSem;           /* device mutual-exclusion semaphore     */
    POOL_ID  	   pFdPool;          /* file descriptor pool ID               */
    spinlockTask_t romfsPoolLock;    /* control access to FD pool             */
    } ROMFS_VOL_DESC;

typedef ROMFS_VOL_DESC * ROMFS_VOL_DESC_ID;

extern int vxBlkIO (void * p, int type, daddr_t bn, uint_t bsize,
                    char * rfsbuf, uint_t * rs);

/* user-callable functions prototypes */

extern STATUS romfsFsInit (unsigned maxFiles);

extern STATUS romfsVolumeCreate (char * pDevName, char * pAddr,
                                 size_t romfsImageLen, off_t offset);
extern ROMFS_VOL_DESC_ID romfsFsDevCreate (char * devName, BLK_DEV * pBlkDev);

#ifdef __cplusplus
}
#endif

#endif /* romfsLib_h */
