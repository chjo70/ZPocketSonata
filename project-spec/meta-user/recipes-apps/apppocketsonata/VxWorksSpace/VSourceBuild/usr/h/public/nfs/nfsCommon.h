/* nfsCommon.h - nfsDrv header */

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
12oct17,ghs  copy nfsCommon.h from kernel space (V7STO-943)
*/

#ifndef __INCnfsCommonh
#define __INCnfsCommonh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#ifndef UNUSED_VAL
#define UNUSED_VAL        (-1U)
#endif

/* file status types -- from the nfs protocol spec, if these change,
   then the FSTAT values in ioLib.h should also be changed */

#define NFS_FSTAT_DIR           0040000         /* directory */
#define NFS_FSTAT_CHR           0020000         /* character special file */
#define NFS_FSTAT_BLK           0060000         /* block special file */
#define NFS_FSTAT_REG           0100000         /* regular file */
#define NFS_FSTAT_LNK           0120000         /* symbolic link file */
#define NFS_FSTAT_NON           0140000         /* named socket */

/* nfsLib status codes */

#define S_nfsLib_NFS_AUTH_UNIX_FAILED           (M_nfsLib | 1)
#define S_nfsLib_NFS_INAPPLICABLE_FILE_TYPE     (M_nfsLib | 2)

#define S_nfsLib_NFS_OK                 (M_nfsStat | (int) NFS_OK)
#define S_nfsLib_NFSERR_PERM            (M_nfsStat | (int) NFSERR_PERM)
#define S_nfsLib_NFSERR_NOENT           (M_nfsStat | (int) NFSERR_NOENT)
#define S_nfsLib_NFSERR_IO              (M_nfsStat | (int) NFSERR_IO)
#define S_nfsLib_NFSERR_NXIO            (M_nfsStat | (int) NFSERR_NXIO)
#define S_nfsLib_NFSERR_ACCESS          (M_nfsStat | (int) NFSERR_ACCESS)
#define S_nfsLib_NFSERR_EXIST           (M_nfsStat | (int) NFSERR_EXIST)
#define S_nfsLib_NFSERR_NODEV           (M_nfsStat | (int) NFSERR_NODEV)
#define S_nfsLib_NFSERR_NOTDIR          (M_nfsStat | (int) NFSERR_NOTDIR)
#define S_nfsLib_NFSERR_ISDIR           (M_nfsStat | (int) NFSERR_ISDIR)
#define S_nfsLib_NFSERR_INVAL           (M_nfsStat | (int) NFSERR_INVAL)
#define S_nfsLib_NFSERR_FBIG            (M_nfsStat | (int) NFSERR_FBIG)
#define S_nfsLib_NFSERR_NOSPC           (M_nfsStat | (int) NFSERR_NOSPC)
#define S_nfsLib_NFSERR_ROFS            (M_nfsStat | (int) NFSERR_ROFS)
#define S_nfsLib_NFSERR_NAMETOOLONG     (M_nfsStat | (int) NFSERR_NAMETOOLONG)
#define S_nfsLib_NFSERR_NOTEMPTY        (M_nfsStat | (int) NFSERR_NOTEMPTY)
#define S_nfsLib_NFSERR_DQUOT           (M_nfsStat | (int) NFSERR_DQUOT)
#define S_nfsLib_NFSERR_STALE           (M_nfsStat | (int) NFSERR_STALE)
#define S_nfsLib_NFSERR_WFLUSH          (M_nfsStat | (int) NFSERR_WFLUSH)
#define S_nfsLib_NFSERR_REMOTE          (M_nfsStat | (int) NFSERR_REMOTE)
#define S_nfsLib_NFSERR_BADHANDLE       (M_nfsStat | (int) NFSERR_BADHANDLE)
#define S_nfsLib_NFSERR_NOT_SYNC        (M_nfsStat | (int) NFSERR_NOT_SYNC)
#define S_nfsLib_NFSERR_BAD_COOKIE      (M_nfsStat | (int) NFSERR_BAD_COOKIE)
#define S_nfsLib_NFSERR_NOTSUPP         (M_nfsStat | (int) NFSERR_NOTSUPP)
#define S_nfsLib_NFSERR_TOOSMALL        (M_nfsStat | (int) NFSERR_TOOSMALL)
#define S_nfsLib_NFSERR_SERVERFAULT     (M_nfsStat | (int) NFSERR_SERVERFAULT)
#define S_nfsLib_NFSERR_BADTYPE         (M_nfsStat | (int) NFSERR_BADTYPE)
#define S_nfsLib_NFSERR_JUKEBOX         (M_nfsStat | (int) NFSERR_JUKEBOX)

/* default NFS parameters */

#define NFS_TIMEOUT_SEC         25
#define NFS_TIMEOUT_USEC        0

#ifdef _WRS_CONFIG_NFS3_BLKSIZE_FACTOR
#define NFS_SOCKOPTVAL		(_WRS_CONFIG_NFS3_BLKSIZE_FACTOR * 8800)
#else
#define NFS_SOCKOPTVAL		8800
#endif

#define NFS_REXMIT_SEC          5
#define NFS_REXMIT_USEC         0

#define NFS_RETRY_SEC           2

#define AUTH_UNIX_FIELD_LEN     50      /* UNIX authentication info */
#define MAX_GRPS                20      /* max. # of groups that user is in */

/* The max size for UDP packet payload,  63K = 64512  = 0xFC00   */
#define NFS_CLNT_UDPPKT_MAXSIZE          64512

/* Max number of versions supported for the MOUNT protocol */
#define MAX_MNT_VERSIONS 4
#define MAX_MNT_SUPPORTED_VERSIONS 2

#define WRITE_PERMISSION  2

#define NFS_CACHE_WRITE_THROUGH   0x1


enum nfsstat {
	NFS_OK = 0,
	NFSERR_PERM = 1,
	NFSERR_NOENT = 2,
	NFSERR_IO = 5,
	NFSERR_NXIO = 6,
	NFSERR_ACCESS = 13,
	NFSERR_EXIST = 17,
	NFSERR_XDEV = 18,
	NFSERR_NODEV = 19,
	NFSERR_NOTDIR = 20,
	NFSERR_ISDIR = 21,
	NFSERR_INVAL = 22,
	NFSERR_FBIG = 27,
	NFSERR_NOSPC = 28,
	NFSERR_ROFS = 30,
	NFSERR_MLINK = 31,
	NFSERR_NAMETOOLONG = 63,
	NFSERR_NOTEMPTY = 66,
	NFSERR_DQUOT = 69,
	NFSERR_STALE = 70,
	NFSERR_REMOTE = 71,
	NFSERR_WFLUSH = 99,
	NFSERR_BADHANDLE = 10001,
	NFSERR_NOT_SYNC = 10002,
	NFSERR_BAD_COOKIE = 10003,
	NFSERR_NOTSUPP = 10004,
	NFSERR_TOOSMALL = 10005,
	NFSERR_SERVERFAULT = 10006,
	NFSERR_BADTYPE = 10007,
	NFSERR_JUKEBOX = 10008
};

#ifdef __cplusplus
}
#endif

#endif /* __INCnfsCommonh */
