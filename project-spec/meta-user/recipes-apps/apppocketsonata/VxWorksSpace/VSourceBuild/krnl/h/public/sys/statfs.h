/* statfs.h - POSIX definitions for obtaining file system statistics */

/*
 * Copyright (c) 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03nov17,ghs  move file system statistics structures and APIs from stat.h (F9150)
*/

#ifndef __INCstatfsh
#define __INCstatfsh

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
    {
    long val[2];                    /* file system id type */
    } fsid_t;

/*
 * file system statistics
 */
struct statfs
    {
    long f_type;                    /* file system type id */
    long f_bsize;                   /* fundamental file system block size */
    long f_blocks;                  /* total blocks in file system */
    long f_bfree;                   /* free block in fs */
    long f_bavail;                  /* free blocks avail to non-superuser */
    long f_files;                   /* total file nodes in file system */
    long f_ffree;                   /* free file nodes in fs */
    fsid_t f_fsid;                  /* file system id */
    long f_spare[7];                /* spare for later */
    };

/*
 * file system statistics
 */
struct statfs64
    {
    long f_type;                    /* file system type id */
    long f_bsize;                   /* fundamental file system block size */
    INT64 f_blocks;                 /* total blocks in file system */
    INT64 f_bfree;                  /* free block in fs */
    INT64 f_bavail;                 /* free blocks avail to non-superuser */
    INT64 f_files;                  /* total file nodes in file system */
    INT64 f_ffree;                  /* free file nodes in fs */
    fsid_t f_fsid;                  /* file system id */
    long f_spare[7];                /* spare for later */
    };

/* file system type id for f_type field in statfs and statfs64 */

#define VD_SET_MAG          (0x06200556)    /* CDROMFS */
#define VD_FS_MAGIC         (0x12345432)    /* VDFS */
#define RAW_FS_MAGIC        (0x12344321)    /* RAWFS */
#define DOS_FS_MAGIC        (0xdfac9723)    /* DOSFS */
#define ROMFS_MAGIC         (0xDEADF00D)    /* ROMFS */
#define VRFS_MAGIC          (0x53465256)    /* VRFS */
#define NFSV2_MAGIC         (0x3253464E)    /* NFSv2 */
#define NFSV3_MAGIC         (0x3353464E)    /* NFSv3 */
#define HRFS_MAGIC          (0x48524653)    /* HRFS */

extern STATUS fstatfs (int, struct statfs *);
extern STATUS fstatfs64 (int _fd, struct statfs64 *_pStat);
#ifdef _WRS_KERNEL
extern STATUS statfs64 (char *_name, struct statfs64 *_pStat);
extern STATUS statfs (char *, struct statfs *);
#else
extern STATUS statfs64 (const char *_name, struct statfs64 *_pStat);
extern STATUS statfs (const char *, struct statfs *);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCstatfsh */
