/* nfs3dLib.h - NFS v3 Server Library Header */

/*
 * Copyright (c) 2003, 2006, 2011-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/* 
modification history
--------------------
01i,14sep12,yjl  Fix WIND00376255, dosFs to be compatible with Windows FAT32
                 naming rules for file/directory name length
01h,06aug12,txu  Fix WIND00367917: NFS v3 client does not support READDIRPLUS
01g,24jun11,y_t  req WIND00236547: improve nfs ls performance.
01f,21jun11,sjz  Improve NFS performance for the requirement WIND00236547.
01e,07may10,lxj  change fsId and inode from ULONG to UINT for NFS protocol
01d,29apr10,pad  Moved extern C statement after include statements.
01c,07sep06,mwv  update include paths
01b,20apr06,pcm  added support for chmod()
01a,08aug03,smc  written
*/

#ifndef __INCnfs3dLibh
#define __INCnfs3dLibh

#include <limits.h>
#include <nfs/xdr_nfs3.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WRS_CONFIG_DOSFS_NAME_LENGTH_COMPAT
#define NFS3_MAXPATHLEN            1024
#define NFS3_MAXNAMLEN             255
#else
#define USE_CHECK_NAMELENGTH    
#define USE_FILE_PATHLENGTH

#ifdef  USE_FILE_PATHLENGTH
#define NFS3_MAXPATHLEN            1036
#else
#define NFS3_MAXPATHLEN            1024 
#endif
    
#ifdef USE_CHECK_NAMELENGTH 
#define NFS3_MAXNAMLEN             1020
#else   
#define NFS3_MAXNAMLEN             255
#endif
#endif

#define NFS3_DEFAULT_STACK_SIZE    14000
#define NFS3_DEFAULT_NFS_SERVERS   4
#define NFS3_DEFAULT_PRIORITY      55
#define NFS3_DEFAULT_FILE_SYSTEMS  10

/* NFS specific FS Info parameters */
#ifdef _WRS_CONFIG_NFS3_BLKSIZE_FACTOR
#define NFS3_MAXBLKSIZE     (_WRS_CONFIG_NFS3_BLKSIZE_FACTOR * 8192) 
#else
#define NFS3_MAXBLKSIZE    8192
#endif

#define NFS3_PAGE_SIZE     1024
#define NFS3_DIRPAGE_SIZE   4096

/* NFSv3 file system properties */
#define NFS3_FSF_LINK           0x0001
#define NFS3_FSF_SYMLINK        0x0002
#define NFS3_FSF_HOMOGENEOUS    0x0008
#define NFS3_FSF_CANSETTIME     0x0010
/* Some shorthands. See nfs3dLib.c */
#define NFS3_FSF_DEFAULT        0x001B
#define NFS3_FSF_BILLYBOY       0x0018
#define NFS3_FSF_READONLY       0x0008

/* Max num of entries in the Queue */
#define QLEN_PER_SRVR           10

/* #define OUTPUT_FMT              "%15s      %8d\n" */

/* 
 * NFS3_ACCESS_WRITE is defined as an OR of
 * MODIFY | EXTEND | DELETE accesses.
 * 0x0004 | 0x0008 | 0x0010
 */

#define NFS3_ACCESS_WRITE  0x001C
#define NFS3_ACCESS_RONLY  0x0023
#define NFS3_ACCESS_RW     0x003F

#define NFS3_DOS_WR_ACCESS     0x092
#define NFS3_DOS_RW            0x01FF
                           
/* Macros to access the reply structure members of NFS v3 procedures */
#define FILE_HANDLE_LEN      data.data_len
#define FILE_HANDLE          data.data_val

#define POST_OP_HANDLE_LEN   handle.FILE_HANDLE_LEN
#define POST_OP_HANDLE       handle.FILE_HANDLE

#define ATTR_FOL         attributes_follow

#define BEFORE_ATTR_FOL  before.ATTR_FOL
#define AFTER_ATTR_FOL   after.ATTR_FOL

#define OBJ_ATTR_FOLLOW        obj_attributes.attributes_follow
#define SYMLINK_ATTR_FOLLOW    symlink_attributes.attributes_follow
#define FILE_ATTR_FOLLOW       file_attributes.attributes_follow
#define DIR_ATTR_FOLLOW        dir_attributes.attributes_follow

/* File Handle Information as per DOS FS on VxWorks */
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
    INT8   reserved[48];    /* NFS v3 File Handle has 64 bytes */
    } NFS3_FILE_HANDLE;

/* NFS v3 Procedure call statistics */

typedef struct
    {
    int nullCalls;          /* Number of calls to NFSPROC_NULL */
    int getattrCalls;       /* Number of calls to NFSPROC_GETATTR */
    int setattrCalls;       /* Number of calls to NFSPROC_SETATTR */
    int lookupCalls;        /* Number of calls to NFSPROC_LOOKUP */ 
    int accessCalls;        /* Number of calls to NFSPROC_ACCESS */
    int readlinkCalls;      /* Number of calls to NFSPROC_READLINK */
    int readCalls;          /* Number of calls to NFSPROC_READ */
    int writeCalls;         /* Number of calls to NFSPROC_WRITE */
    int createCalls;        /* Number of calls to NFSPROC_CREATE */
    int mkdirCalls;         /* Number of calls to NFSPROC_MKDIR */
    int symlinkCalls;       /* Number of calls to NFSPROC_SYMLINK */
    int mknodCalls;         /* Number of calls to NFSPROC_MKNOD */
    int removeCalls;        /* Number of calls to NFSPROC_REMOVE */
    int rmdirCalls;         /* Number of calls to NFSPROC_RMDIR */
    int renameCalls;        /* Number of calls to NFSPROC_RENAME */
    int linkCalls;          /* Number of calls to NFSPROC_LINK */
    int readdirCalls;       /* Number of calls to NFSPROC_READDIR */
    int readdirplusCalls;   /* Number of calls to NFSPROC_READDIRPLUS */
    int fsstatCalls;        /* Number of calls to NFSPROC_FSSTAT */
    int fsinfoCalls;        /* Number of calls to NFSPROC_FSINFO */
    int pathconfCalls;      /* Number of calls to NFSPROC_PATHCONF */
    int commitCalls;        /* Number of calls to NFSPROC_COMMIT */
    } NFS3_SERVER_STATUS;   

/* 
 * Union of Expected Argument for NFS v3 procedure 
 * call (wherever applicable).
 * Description against each argument not given as the member
 * name is descriptive enough
 * The definitions of types are available in "xdr_nfs3.h" file
 */

typedef union
    {
    GETATTR3args     nfsproc_getattr_3_arg;
    SETATTR3args     nfsproc_setattr_3_arg;
    LOOKUP3args      nfsproc_lookup_3_arg;
    ACCESS3args      nfsproc_access_3_arg;
    READLINK3args    nfsproc_readlink_3_arg;
    READ3args        nfsproc_read_3_arg;
    WRITE3args       nfsproc_write_3_arg;
    CREATE3args      nfsproc_create_3_arg;
    MKDIR3args       nfsproc_mkdir_3_arg;
    SYMLINK3args     nfsproc_symlink_3_arg;
    MKNOD3args       nfsproc_mknod_3_arg;
    REMOVE3args      nfsproc_remove_3_arg;
    RMDIR3args       nfsproc_rmdir_3_arg;
    RENAME3args      nfsproc_rename_3_arg;
    LINK3args        nfsproc_link_3_arg;
    READDIR3args     nfsproc_readdir_3_arg;
    READDIRPLUS3args nfsproc_readdirplus_3_arg;
    FSSTAT3args      nfsproc_fsstat_3_arg;
    FSINFO3args      nfsproc_fsinfo_3_arg;
    PATHCONF3args    nfsproc_pathconf_3_arg;
    COMMIT3args      nfsproc_commit_3_arg;
    } NFS3D_ARGUMENT;

#ifdef __cplusplus
}
#endif

#endif /* __INCnfs3dLibh */
