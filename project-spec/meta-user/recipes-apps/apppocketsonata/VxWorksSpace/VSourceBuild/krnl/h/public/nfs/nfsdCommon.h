/* nfsdLib.h - NFS v3 Server Library Header */

/*
 * Copyright (c) 2003, 2006, 2008, 2011-2012, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
-------------------- 
26sep16,yjl  NFS cache can point to a deleted version of a file (V7STO-502)
05jan12,txu  fix WIND00326552: NFS client cannot send a too large packet
24jun11,y_t  req WIND00236547: improve nfs ls performance.
01sep10,zly  support the 3rd FS`s errno mapping.(WIND00183171)
07may10,lxj  change NFS_FILE_HANDLE struct for matching NFSn_FILE_HANDLE
29apr10,pad  Moved extern C statement after include statements.
05feb10,y_t  update for LP64
28aug08,lyc  fixed for WIND117813
07sep06,mwv  update include paths
15sep03,msc  written
*/

#ifndef __INCnfsdCommonh
#define __INCnfsdCommonh

#include <limits.h>
#include <nfs/nfs2dLib.h>
#include <nfs/nfs3dLib.h>
#include <dirent.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Data Structures */

/* Common data of file handle irrespective of v2 or v3 */
/*
 * NFS_FILE_HANDLE, NFS2_FILE_HANDLE and NFS3_FILE_HANDLE data struct have
 * the same common header data members, and they have the same data type.
 * Make sure all the 3 data structs be changed if common data members
 * be changed. There is no limit for private data members.
 */

/* The max size for UDP packet payload,  63K = 64512  = 0xFC00   */
#define NFS_SRV_UDPPKT_MAXSIZE          64512

#if 0
typedef struct
    {
    INT32   volumeId;        /* Volume identifier of the File System */
    UINT32  fsId;            /* Inode of the exported directory */
    UINT32  inode;           /* Inode of the file as returned from stat */
    UINT32  cookie;
    } NFS_FILE_HANDLE; 
#endif

typedef struct
    {
    int     fd;
    int     inUse;
    time_t  expires;
    UINT64  use;
    int     inode;
    int     volumeId;
    int     fsId;
    int     mode;
    time_t  st_ctime; /* time of last status change */
    } nfsFileCache;

typedef STATUS (* pFs2NfsErrnoHookRtn) (int, int*);

extern  NFS3_SERVER_STATUS  nfs3ServerStatus;
extern  NFS2_SERVER_STATUS  nfs2ServerStatus;

#define nfsdClose( fh )	\
    {                   \
    fh->inUse = FALSE;  \
    }

#if defined(__STDC__) || defined(__cplusplus)

extern nfsFileCache *nfsdOpen (NFS_FILE_HANDLE *fh, int mode);
extern void nfsdCacheSearchClose( NFS_FILE_HANDLE *fh); 
extern STATUS  nfsdStatusGet (void * serverStats, int version);
extern STATUS  nfsdStatusShow (int options);
extern STATUS  nfsdFhCreate (NFS_FILE_HANDLE * parentDir, char * fileName,
                             NFS_FILE_HANDLE * fh);

extern STATUS  nfsdFhToName (NFS_FILE_HANDLE * fh, char * fileName);
extern nfsstat nfsdErrToNfs (int theErr);
extern void    nfsdFhHton (NFS_FILE_HANDLE * fh);
extern void    nfsdFhNtoh (NFS_FILE_HANDLE * fh);
extern int     nfsdFsReadOnly (NFS_FILE_HANDLE * fh);
extern STATUS  nfsdFsErrnoHookAdd (pFs2NfsErrnoHookRtn pfn);
extern STATUS  nfsdFsErrnoHookDelete (pFs2NfsErrnoHookRtn pfn);
extern DIRPLUS *opendirplus (const char *dirName);
extern struct  dirent *	readdirplus (DIRPLUS * pDir);
extern STATUS  closedirplus (DIRPLUS * pDir);

#else

extern nfsFileCache *nfsdOpen ();
extern void nfsdCacheSearchClose();
extern STATUS  nfsdStatusGet ();
extern STATUS  nfsdStatusShow ();
extern STATUS  nfsdFhCreate ();
extern STATUS  nfsdFhToName ();
extern nfsstat nfsdErrToNfs ();
extern void    nfsdFhHton ();
extern void    nfsdFhNtoh ();
extern int     nfsdFsReadOnly ();
extern STATUS  nfsdFsErrnoHookAdd ();
extern STATUS  nfsdFsErrnoHookDelete ();
extern DIRPLUS *opendirplus ();
extern struct  dirent *	readdirplus ();
extern STATUS  closedirplus ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnfsdCommonh */
