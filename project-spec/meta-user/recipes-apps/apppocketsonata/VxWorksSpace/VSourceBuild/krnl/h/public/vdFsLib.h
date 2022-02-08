/* vdFsLib.h - header for virtual disk block device file system library */

/*
 * Copyright 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27oct17,jsp  add support for priority scheduling
15aug17,jsp  update number of max open file descriptors (HYP-12099)
31jul17,ghs  integrate file system type magic number (F9150)
28jun15,jsp  convert routines to use select() library
23mar15,dcc  consolidate errnos
16mar15,dcc  cleanup
12mar15,dcc  added support for DMABUF
05mar15,dcc  initial support for ASYNC mode
17feb15,dcc  ported from rawfsLib.h
*/

#ifndef __INCvdFsLibh
#define __INCvdFsLibh

#include <sys/time.h>
#include <iosLib.h>
#include <lstLib.h>
#include <semLib.h>
#include <vwModNum.h>
#include <drv/xbd/xbd.h>
#include <drv/xbd/bio.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VDFS_DEF_MAX_FILES	64	/* default max number of open files */

#define FIOHANDLESET    1073
#define FIOHANDLEGET    1074
#define FIOFDGET        1075
#define FIODMABUFSET    1076
#define O_DMABUF        0x400000

#define VDFS_READ       0x0
#define VDFS_WRITE      0x1

struct vdFsAiocb
    {
    int                 vdfs_handle;
    off_t               vdfs_offset;
    volatile void *     vdfs_data;
    size_t              vdfs_nbytes;
    size_t              vdfs_resid;
    unsigned            vdfs_error;
    uint16_t            vdfs_req_opcode;
    uint16_t            vdfs_reqprio;
    };

/* Volume descriptor */

typedef struct              /* VD_VOL_DESC */
    {
    DEV_HDR     vdVdDevHdr;     /* std. I/O system device header */
    u_int       magic;          /* VD_FS_MAGIC */
    int         vdVdStatus;     /* (OK | ERROR) */
    SEM_ID      vdVdSemId;      /* volume descriptor semaphore id */
    device_t    vdVdXbd;        /* Backing block device */
    void *	vdRootXbd;	/* root block device pointer */
    int         vdVdRetry;      /* current retry count for I/O errors */
    unsigned    vdVdBlkSize;	/* block size for device */
    sector_t    vdVdNBlocks;	/* number of blocks */
    } VD_VOL_DESC;

/* Volume states */

#define VD_VD_READY_CHANGED 0   /* vol not accessed since rdy change */
#define VD_VD_RESET         1   /* volume reset but not mounted */
#define VD_VD_MOUNTED       2   /* volume mounted */
#define VD_VD_CANT_RESET    3   /* volume reset failed */
#define VD_VD_CANT_MOUNT    4   /* volume mount failed */

/* Function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern VD_VOL_DESC *vdFsDevInit (char *pVolName, device_t xbd);
extern STATUS vdFsInit (int maxFiles);
extern STATUS vdFsVolUnmount (VD_VOL_DESC *pVd);
extern STATUS vdFsAioXferQSelect (int width, FAST fd_set *pFds,
                                  struct timeval * pTimeOut);
extern STATUS vdFsAioXferQEntryTake (int fd, struct vdFsAiocb * cb);
extern STATUS vdFsAioXferQNonEmpty(int fd);
extern STATUS vdFsAioXferQSizeSet(int fd, uint32_t size);
extern STATUS vdFsAioXferQSizeGet (int fd, uint32_t *size);

#else   /* __STDC__ */

extern VD_VOL_DESC * vdFsDevInit ();
extern STATUS vdFsInit ();
extern STATUS vdFsVolUnmount ();
extern STATUS vdFsAioXferQSelect();
extern STATUS vdFsAioXferQEntryTake ();
extern STATUS vdFsAioXferQNonEmpty();
extern STATUS vdFsAioXferQSizeSet();
extern STATUS vdFsAioXferQSizeGet ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCvdFsLibh */


