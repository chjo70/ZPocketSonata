/* nfs2dLib.h - Network File System Server library header */

/*
 * Copyright (c) 1994, 2003, 2005 - 2006, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01i,24jun11,y_t  req WIND00236547: improve nfs ls performance.
01h,07may10,lxj  change fsId and inode from ULONG to UINT for NFS protocol
01g,29apr10,pad  Moved extern C statement after include statements.
01f,01sep06,mwv  update the include paths
01e,01dec05,dlk  Use __INCnfs2dLibh rather than __INCnfsdLibh to protect
                 against multiple inclusion (SPR #114404).
01d,08aug03,bmk  added extern declaration for group_export (SPR #4220)
01c,21apr94,jmm  more cleanup of prototypes; added NFSD_ARGUMENT
01b,20apr94,jmm  added new prototypes
01a,31mar94,jmm  written.
*/

#ifndef __INCnfs2dLibh
#define __INCnfs2dLibh

#include <limits.h>
#include <nfs/xdr_nfs2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Extern declaration for group_export */

extern int group_export;

/*
 * NFS_FILE_HANDLE, NFS2_FILE_HANDLE and NFS3_FILE_HANDLE data struct have
 * the same common header data members, and they have the same data type.
 * Make sure all the 3 data structs be changed if common data members
 * be changed. There is no limit for private data members.
 */

typedef struct
    {
    INT32  volumeId;        /* Volume identifier of the File System */
    UINT32 fsId;            /* Inode of the exported directory */
    UINT32 inode;           /* Inode of the file as returned from stat */
    UINT32 cookie;
    INT8   reserved[16];    /* NFS v2 File Handle has 32 bytes */
    } NFS2_FILE_HANDLE;

/* 
 * Structure to hold the statistics of
 * number of NFS v2 RPC calls received from remote clients. 
 */

typedef struct
    {
    int nullCalls;         /* Number of calls to NFSPROC_NULL */
    int getattrCalls;      /* Number of calls to NFSPROC_GETATTR */
    int setattrCalls;      /* Number of calls to NFSPROC_SETATTR */
    int rootCalls;         /* Number of calls to NFSPROC_ROOT */
    int lookupCalls;       /* Number of calls to NFSPROC_LOOKUP */
    int readlinkCalls;     /* Number of calls to NFSPROC_READLINK */
    int readCalls;         /* Number of calls to NFSPROC_READ */
    int writecacheCalls;   /* Number of calls to NFSPROC_WRITECACHE */
    int writeCalls;        /* Number of calls to NFSPROC_WRITE */
    int createCalls;       /* Number of calls to NFSPROC_CREATE */
    int removeCalls;       /* Number of calls to NFSPROC_REMOVE */  
    int renameCalls;       /* Number of calls to NFSPROC_RENAME */
    int linkCalls;         /* Number of calls to NFSPROC_LINK */
    int symlinkCalls;      /* Number of calls to NFSPROC_SYMLINK */ 
    int mkdirCalls;        /* Number of calls to NFSPROC_MKDIR */ 
    int rmdirCalls;        /* Number of calls to NFSPROC_RMDIR */
    int readdirCalls;      /* Number of calls to NFSPROC_READDIR */
    int statfsCalls;       /* Number of calls to NFSPROC_STATFS */
    } NFS2_SERVER_STATUS;

/* 
 * Union of Expected Argument for NFS v2 procedure 
 * call (wherever applicable).
 * Description against each argument not given as the member
 * name is descriptive enough.
 * The definitions of types are available in "xdr_nfs2.h" file
 */

typedef union
    {
    nfs_fh2       nfsproc_getattr_2_arg; 
    sattrargs     nfsproc_setattr_2_arg; 
    diropargs     nfsproc_lookup_2_arg;  
    nfs_fh2       nfsproc_readlink_2_arg;
    readargs      nfsproc_read_2_arg;   
    writeargs     nfsproc_write_2_arg;  
    createargs    nfsproc_create_2_arg; 
    diropargs     nfsproc_remove_2_arg; 
    renameargs    nfsproc_rename_2_arg; 
    linkargs      nfsproc_link_2_arg;   
    symlinkargs   nfsproc_symlink_2_arg;
    createargs    nfsproc_mkdir_2_arg;  
    diropargs     nfsproc_rmdir_2_arg;  
    readdirargs   nfsproc_readdir_2_arg;
    nfs_fh2       nfsproc_statfs_2_arg; 
    } NFS2D_ARGUMENT;

#ifdef __cplusplus
}
#endif

#endif /* __INCnfs2dLibh */
