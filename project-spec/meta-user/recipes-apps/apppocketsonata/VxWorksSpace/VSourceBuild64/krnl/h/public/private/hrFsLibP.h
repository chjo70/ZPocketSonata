/* hrfsLibP.h - Highly reliabe file system private header file */

/*
 * Copyright (c) 2005-2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17jan18,ghs  add HRFS error handle definitions (F10082)
31jul17,ghs  clean warning (F9150)
03mar16,txu  Fix V7STO-595: buffer should be invalidated after file is truncated
03mar16,txu  fix V7STO-594: trieOffset is not really used in HRFS
04dec15,txu  fix V7STO-509: HRFS deadlocks on multithreaded write/rename
             attempts in highspeed mode when disk is full
16jun15,yjl  Updated FIOPATHCONF handling for Big Endian LP64 (V7RAD-155)
01jan14,ghs  Remove useless head files (US29308)
02jul13,myt  WIND00424679 - restore all operation to atomic semantic
             in default mode
05mar13,myt  WIND00401243 - initialize semaphore when mounting hrfs instead of
             in every transaction
13sep12,myt  WIND00368976 - add two varible to record freeInode and
             freeDataBlk in this trans avoid to be changed by next
             trans in hrfsHighSpeedWriteMode.
12myt11,myt  add a writing superblock num macro definition
13jul11,jxu  add dirRenameSlot for rename operation (WIND00287328).
06apr11,jxu  WIND00252514 - HRFS is soon corrupt once full
             reserved constant number of blocks for file deletion or
             truncation when disk is full.
09apr10,lxj  adapted for LP64 support
28oct09,hui  manual merge to 64 bit
01oct09,gls  removed use of POSIX APIs
01jul09,hui  WIND142041 - HRFS performance improvement
02jun09,xia  Modified for hrfsAscTime()
19aug08,hui  WIND000129267 - HRFS poor performance when performing more than
             one writes.
22jan07,act  add discard-interface info
03nov06,jlk  WIND00083334 - File deletion strategy change.
26may06,jlk  added stuff for commit policy changes
04jan06,act  add POSIX file locking
16nov05,md   added time function protos and in-core structures
01nov05,pcm  made direct, indirect, indirect2 and indirect3 into an array;
             added trieOffset[] to HRFS_VOLUME_DESC
04aug05,jlk  Moved formatter function pointer, hrfsFmtRtn, to hrFsLib.h
22jul05,jlk  code review changes
18jul05,jlk  Added formatter function pointer, hrfsFmtRtn
28jun05,jlk  clean-up and added diskModified flag to volume descriptor
17jun05,jlk  removed prototype for hrfsXbdSyncDone()
17may05,pcm  added hrfsTransactionRollback()
29apr05,jlk  moved in CRC #defines from hrFsSuperBlk.c. Added inode state
             defines. Fixed bug where the generation field in the inode was
             defined to be 8 bytes instead of 4. Added <state> field to
             inode. Added some prototypes.
25apr05,jlk  moved version #defines and id string to hrFsLib.h and fixed
             endian check
21apr05,jlk  added freeInodes and freeDataBlks fields to TMR. Re-arranged
             volume descriptor for alignment purposes and removed unused
             fields. Added prototypes for hrfsMount() and hrfsStat()
15apr05,pcm  added <numInodesToDelete> field to HRFS_TMR
15apr05,act  add a dirSlot to HRFS_INODE (incore inode)
14apr05,pcm  changed INODE_JOURNAL_ENTRIES from 4 to 7
14apr05,pcm  removed HRFS_MODE_BIT_xxx; the S_IFxxx definitions to be used
11apr05,pcm  changed DIRENT's field  fileName string size to
             HRFS_DIRENT HRFS_MAX_FILENAME_LEN + 1
24mar05,jlk  added prototype for hrfsCommit()
23mar05,jlk  debug stuff and moved nBlocks field in inode structure
21mar05,jlk  moved nBlocks field in inode structure for alignment reasons
21mar05,jlk  fixed bug in big endian versions of htodll and dtohll macros
             and added padding to super block structure to make the size
             a multiple of 8.
16mar05,pcm  changed parameters to hrfsInodeGet()
15mar05,pcm  made htodll() a function call to htodll_le() for little endian
15mar05,pcm  reworked htodll() and dtohll() macros
10mar05,act  remove unwanted data from HRFS_DEV
08mar05,jlk  fixed up for new mount code
08mar05,jlk  changed prototype for hrfsInodeAlloc()
07mar05,pcm  added VTOI macro and various function prototypes
07mar05,jlk  added mode bits for inode
01mar05,jlk  removed pointer to the inode journal to
             HRFS_VOLUME_DESC. Added some more prototypes.
28feb05,pcm  added HRFS_INODE_ROOT_DIR
25feb05,pcm  changed iNodeNunber to iNodeNumber in INODE_JOURNAL
24feb05,pcm  added mount.h to includes, and new fields to HRFS_VOLUME_DESC
24feb05,jlk  added nBlocks and reserved fields to inode structure
23feb05,jlk  added a pointer to the inode journal to HRFS_VOLUME_DESC.
             added transaction numbers to HRFS_VOLUME_DESC
11feb05,pcm  added HRFS_TMR structure, and fields to HRFS_VOLUME_DESC
09feb05,jlk  added sectorsPerBlk & sectorsPerBlk2 fields to the
             HRFS_VOLUME_DESC structure
03feb05,pcm  changed HRFS_SUPER_BLOCK field in HRFS_VOLUME_DESC to a ptr
03feb05,jlk  updated inode struct to include an on-disk and an in-memory
             version
26jan05,pcm  added HRFS_DEV structure
21jan05,jlk  written
*/

#ifndef __INChrfsLibP
#define __INChrfsLibP

#include <vxWorks.h>
#include <hrFsLib.h>
#include <drv/xbd/bio.h>
#include <mount.h>
#include <vnode.h>
#include <dllLib.h>
#include <buf.h>
#include <private/tree.h>
#include <private/semLibP.h>
#include <vxAtomicLib.h>

/* defines */

/*
 * NOTE:
 *
 * The option SEM_NO_ID_VALIDATE is used to bypass object validation
 * in the inline semaphore routines.  Performance is enhanced dramatically,
 * particularly for SMP, by doing this.  It does require, however, that the
 * semaphore take/give operations never be called on an invalid semaphore.
 * That is, a semaphore that has not be intialized or a semaphore that
 * has been 'destroyed'.
 */

#define HRFS_MUTEX_CREATE_OPTIONS (SEM_Q_PRIORITY | SEM_INVERSION_SAFE)
#define HRFS_MUTEX_INLINE_OPTIONS (HRFS_MUTEX_CREATE_OPTIONS | \
                                   SEM_NO_ID_VALIDATE)

#define HRFS_BINARY_CREATE_OPTIONS (SEM_Q_PRIORITY)
#define HRFS_BINARY_INLINE_OPTIONS (HRFS_BINARY_CREATE_OPTIONS | \
                                    SEM_NO_ID_VALIDATE)

#ifdef __cplusplus
extern "C" {
#endif

int hrfsMutexInit (SEMAPHORE *pMutex);
int hrfsSemInit (SEMAPHORE *pSem);

int hrfsMutexDestroy (SEM_ID mutexId);
int hrfsSemDestroy (SEM_ID semId);

int hrfsMutexLock (SEM_ID mutexId);
int hrfsMutexUnlock (SEM_ID mutexId);

#ifdef __cplusplus
}
#endif

#ifndef HRFS_DEBUG_BMP
    #define hrfsPrintBmp(x,y)
#endif

#ifndef HRFS_DEBUG_SUPER
    #define hrfsPrintSuperBlk(x)
#endif

/* The number of inodes in the journal */
#define INODE_JOURNAL_ENTRIES 7

/* The number that represents an invalid block */
#define INVALID_BLK_NUM         ((UINT32)(-1))
#define INVALID_INODE_NUM       ((UINT32)(-1))

#define HRFS_VOLUME_MAGIC  (0x00a87cb7)

/* CRC */
#define HRFS_INTIAL_CRC32  0xffffffff  /* Initial 32 bit FCS value */
#define HRFS_GOOD_CRC32    0xdebb20e3  /* Good final 32 bit FCS value */

/* Inode states */
#define HRFS_INODE_STATE_FREE      0xFF
#define HRFS_INODE_STATE_ALLOC     0xFE
#define HRFS_INODE_STATE_TO_BE_DEL 0xFC

/* Reserved inode numbers */
#define INODE_START_NUMBER   2
#define HRFS_INODE_ROOT_DIR  INODE_START_NUMBER

#define HRFS_MAX_INODES      0xffffffff /* max value of an unsigned int */

/* max block num when writing superblock */
#define HRFS_MAX_BLK_NUM_FOR_WRITE_SUPBLK 512

/* reserve number blocks for remove/unlink file when the disk full.
 *
 * HRFS use copy on write tech for file system modification, that means any
 * change will copy and then write the change data to other space (but not
 * overwrite existing block). But when the disk is nearly full (there are not
 * enough free blocks), file system can't work, due to any operation will
 * consume free blocks even if we remove or truncate file.
 *
 * So, file system reserved HRFS_MAX_BLK_NUM_RESERVED(16) blocks, it should
 * be used when the disk full(have no any other free blocks). These 16 blocks
 * only be used when the operations are FREEing blocks, typical remove/truncate
 * file, for other operation(e.g. create/write/rename file), file system will
 * return ERROR with S_hrfsLib_DISK_FULL error number.
 */
#define HRFS_MAX_BLK_NUM_RESERVED        (16U)

/* Macro to get inode from vnode */
#define HRFS_VTOI(ip,vnp) \
    ip = (VTODATA(HRFS_INODE, vnp));  \
    ip->iNodeNumber = (UINT32)vnp->v_inode;


/*
 * Byte swap macros for converting in memory representations to disk
 * representations for various types.
 */

#if _BYTE_ORDER == _BIG_ENDIAN

#define dtohl(x)        (x)
#define dtohs(x)        (x)
#define htodl(x)        (x)
#define htods(x)        (x)
#define dtohll(x)       (x)
#define htodll(x)       (x)

#else

#define dtohl(x)        ((((x) & 0x000000ff) << 24) |   \
                         (((x) & 0x0000ff00) <<  8) |   \
                         (((x) & 0x00ff0000) >>  8) |   \
                         (((x) & 0xff000000) >> 24))

#define htodl(x)        ((((x) & 0x000000ff) << 24) |   \
                         (((x) & 0x0000ff00) <<  8) |   \
                         (((x) & 0x00ff0000) >>  8) |   \
                         (((x) & 0xff000000) >> 24))

#define dtohs(x)        ((((x) & 0x00ff) << 8) |    \
                         (((x) & 0xff00) >> 8))

#define htods(x)        ((((x) & 0x00ff) << 8) |    \
                         (((x) & 0xff00) >> 8))

#ifdef __cplusplus
extern "C" {
#endif

extern  UINT64 htodll_le (UINT64);

#ifdef __cplusplus
}
#endif


#define htodll(x)    htodll_le(x)
#define dtohll(x)    htodll(x)

#endif /* _BYTE_ORDER */

/*
 * Macro to determine the numnber of inodes per block based on a 64 byte sized
 * inode
 */
#define INODES_PER_BLK(bsize) ((bsize) >> 6)

/* Macro to round up the number of inodes based on inodes per block */
#define NUM_INODES_UP(iperblk, ni) ((iperblk) + (((ni) - 1) & (-(iperblk))))

/*
 * Macro to convert bytes to blocks based on a block size specified as a power
 * of 2
 */
#define BYTES_TO_BLKS(bytes, blkSize2) ((bytes) >> (blkSize2))

/*
 * Time conversion macros.
 */
#define TIMESPEC_TO_HRFSTIME(ts) \
    ((hrfsTime_t)(ts).tv_sec * 1000 + ((ts).tv_nsec + 999999) / 1000000)

#define HRFSTIME_TO_TV_SEC(htime)  (htime / 1000)
#define HRFSTIME_TO_TV_NSEC(htime) ((htime % 1000) * 1000000)

#define HRFS_STANDALONE      0
#define HRFS_AUTOMATIC       1
#define HRFS_ATOMIC          2

#define HRFS_VBTOHB(vb) ((struct hrfsBuf *)(vb->b_priv))
#define HRFS_SYNC       1
#define HRFS_ASYNC      0

#define HRFS_COMMIT_POINT    4 /* 40% cache usage*/
#define HRFS_COMMIT_PERIOD   5 /* 5 seconds */

#define HRFS_EXCEPTION(x)                                                    \
            do                                                         \
                {                                                      \
                if (x)                                                 \
                   hrfsPanic(__FILE__, __LINE__, "HRFS EXCEPTION\n"); \
                } while(0)

/* hrfs operations definition used by hrfs data blocks allocator to
 * allocate reserved blocks for file deletion operations when disk full.
 *
 * HRFS operations are divided into several classes:
 *    HRFS_VOP_UNLINK      -- remove a file,
 *    HRFS_VOP_INACTIVATE  -- removed a file and close the last reference,
 *    HRFS_VOP_RMDIR       -- remove a directory,
 *    HRFS_VOP_TRUNC       -- truncate a file,
 *    HRFS_VOP_NONDELETE   -- other operations which would consume disk space.
 */

#define  HRFS_VOP_NONDELETE     0x0
#define  HRFS_VOP_UNLINK        0x01
#define  HRFS_VOP_INACTIVATE    0x02
#define  HRFS_VOP_RMDIR         0x04
#define  HRFS_VOP_TRUNC         0x08

/* volume status */
#define  HRFS_VOL_OK            0
#define  HRFS_VOL_REWINDING     1

/*
 * enums
 */

enum HRFS_TRANS_STATE
    {
    NO_COMMIT,
    NEED_COMMIT,
    START_COMMIT,
    FINISH_COMMIT,
    QUIT_COMMIT
    };

enum HRFS_VOL_STATE
    {
    HRFS_VOLUME_DEAD,
    HRFS_VOLUME_CREATED,
    HRFS_VOLUME_MOUNTED,
    HRFS_VOLUME_DYING
    };

#ifdef __cplusplus
extern "C" {
#endif

/*
 * typedefs
 */

/* The type used to represent a file's size. 64 bits, unsigned */
typedef INT64  fsize_t;

/* The type used to represent the generation number of an inode */
typedef UINT32  fgen_t;

/* Types used to represent the file owners' UID and GID values */
typedef UINT32  fid_t;

/* Type used to represent the number of hard links to a file */
typedef UINT16  linkCount_t;

/* Type used to represent the mode bits of a file */
typedef UINT16  fmode_t;

/* HRFS Volume State type */
typedef enum HRFS_VOL_STATE HRFS_VOL_STATE;

/* Time in HRFS is a 64 bit signed quantity of ms since 1970 */

typedef INT64   hrfsTime_t;

/* The on-disk representation of an HRFS V1.1 inode */
typedef struct hrfs_inode_disk_struct_v1r1
    {
    hrfsTime_t  ctime;       /* The last time the file attributes */
                             /* (inode) were changed. */
    hrfsTime_t  mtime;       /* The last time the file data was changed */
    fsize_t     size;        /* The size of the file */
    fgen_t      generation;  /* # of times inode has been allocated */
    fid_t       uid;         /* UID of value of the owner of the file */
    fid_t       gid;         /* GID of value of the owner of the file */
    UINT32      nBlocks;     /* The number of blocks associated with inode */
    UINT32      indirect[4]; /* Direct & Indirect block references */
    linkCount_t linkCount;   /* Number of hard links to file */
    fmode_t     mode;        /* Mode bits for file */
    u_char      state;       /* State:  free, allocated, to be deleted */
    char        reserved[2]; /* Pad out size to 64 bytes */
    UINT8       version;     /* version format of inode */
    } _WRS_PACK_ALIGN(1) HRFS_DISK_INODE_V1R1, * HRFS_DISK_INODE_PTR_V1R1;

/* The on-disk representation of an HRFS V1.2 inode */
typedef struct hrfs_inode_disk_struct_v1r2
    {
    fsize_t     size;        /* The size of the file */
    fgen_t      generation;  /* # of times inode has been allocated */
    fid_t       uid;         /* UID of value of the owner of the file */
    fid_t       gid;         /* GID of value of the owner of the file */
    UINT32      nBlocks;     /* The number of blocks associated with inode */
    UINT32      indirect[4]; /* Direct & Indirect block references */
    linkCount_t linkCount;   /* Number of hard links to file */
    fmode_t     mode;        /* Mode bits for file */
    u_char      ctime[6];    /* The last time the file attributes */
                             /* (inode) were changed. */
    u_char      mtime[6];    /* The last time the file data was changed */
    u_char      atime[6];    /* The last time the file data was accessed */
    u_char      state;       /* State:  free, allocated, to be deleted */
    UINT8       version;     /* version format of inode */
    } _WRS_PACK_ALIGN(1) HRFS_DISK_INODE_V1R2, * HRFS_DISK_INODE_PTR_V1R2;

/* Holder for on-disk representation inode */
typedef struct
    {
    char    space[64];   /* Pad out size to 64 bytes */
    } HRFS_DISK_INODE, *HRFS_DISK_INODE_PTR;

/* The in-memory representation of an HRFS inode */
typedef struct hrfs_incore_inode
    {
    hrfsTime_t  ctime;       /* The last time the file attributes */
                             /* (inode) were changed. */
    hrfsTime_t  mtime;       /* The last time the file data was changed */
    hrfsTime_t  atime;       /* The last time the file data was accessed */
    fsize_t     size;        /* The size of the file */
    fgen_t      generation;  /* # of times inode has been allocated */
    fid_t       uid;         /* UID of value of the owner of the file */
    fid_t       gid;         /* GID of value of the owner of the file */
    UINT32      nBlocks;     /* The number of blocks associated with inode */
    UINT32      indirect[4]; /* Direct & Indirect block references */
    linkCount_t linkCount;   /* Number of hard links to file */
    fmode_t     mode;        /* Mode bits for file */
    u_char      state;       /* State:  free, allocated, to be deleted */
    UINT32      version;     /* version format of on-disk inode */
    } HRFS_INCORE_INODE, * HRFS_INCORE_INODE_PTR;

/*
 * When we allocate block for a file, the last allocating information can be
 * used for guide which block to allocate. By doing this, we can speed up the
 * allocating speed and reduce the disk fragment.
 *
 * XXX - More information can be added in this structure to optimize further.
 */
typedef struct hrfs_alloc_pos
    {
    UINT32     lastAllocPhyBlkNum;
    } HRFS_ALLOC_POS, * HRFS_ALLOC_POS_PTR;

typedef struct hrfs_inode_struct
    {
    DL_NODE           delNode;    /* Node of "to be del" list */
    HRFS_INCORE_INODE iNodeData;
    UINT32            iNodeNumber;
    UINT32            dirSlot;    /* directory slot from lookup op */
    UINT32            dirInode;   /* inode number of subdirectory being deleted from */
    UINT32            dirDelSlot;    /* saved dirSlot for final unlink */
    UINT32            dirRenameSlot; /* saved dirSlot for rename */
    HRFS_ALLOC_POS    iAllocPos;     /* guide which block to alloc */
    } HRFS_INODE, * HRFS_INODE_PTR;

/* The representation of the HRFS inode journal */
typedef struct hrfs_inode_journal_struct
    {
    UINT64          transNumber;                         /* Transaction #. */
    UINT32          iNodeNumber[INODE_JOURNAL_ENTRIES];  /* I-Node #s. */
    char            reserved[28];                        /* For alignment. */
    HRFS_DISK_INODE iNodeData[INODE_JOURNAL_ENTRIES];    /* Inode data */
    } _WRS_PACK_ALIGN(1) HRFS_INODE_JOURNAL, * HRFS_INODE_JOURNAL_PTR;

typedef struct hrfs_tmr          /* HRFS Transaction Master Record */
    {
    UINT64    transNumber;       /* HRFS transaction number */
    UINT64    timeStamp;         /* HRFS timestamp */
    UINT32    numInodesToDelete;
    UINT32    numFreeInodes;
    UINT32    numFreeDataBlocks;
    UINT32    spare;
    } _WRS_PACK_ALIGN(1) HRFS_TMR;

/*
 * The representation of the HRFS Super Block. The size of this structure must
 * be a multiple of 8
 */
typedef struct hrfs_disk_super_block_struct
    {
    char      idString[8];  /* Identification or eyecatcher string */
    INT64     ctime;        /* time at which superblock was created. */
    UINT8     majorVers;    /* Major version number */
    UINT8     minorVers;    /* Minor version number */
    UINT16    blkSize2;     /* Block size as a power of 2. */
    UINT32    totalBlks;    /* Total # of blocks in fs (including offset). */

    UINT32    reservedBlks; /* Size of the reserved space at */
                            /* the start of the media. */

    UINT32    iNodeCount;   /* The number of iNodes this file */
                            /* system instantiation has. */

    UINT32    bgSize;       /* Block group size  (=dsSize + 1 for 1st iter) */
    UINT32    dsSize;       /* Data space size   (=bgSize - 1 for 1st iter) */
    UINT32    nBlkGroups;   /* Number of block groups. (1 for 1st iteration) */

    UINT32    fsbOff[2];    /* 1st & 2nd free space bitmap offsets */
    UINT32    fibOff[2];    /* 1st & 2nd free inode bitmap offsets */

    UINT32    itOff;        /* inode table offset */
    UINT32    ijOff;        /* inode journal offset */

    UINT32    tmOff[2];     /* 1st & 2nd transaction map offsets */
    UINT32    tmrOff[2];    /* 1st & 2nd transaction  master record offsets */

    UINT32    dsOff;        /* data space offset */
    UINT32    pad;          /* pad out structure */
    UINT32    crc;          /* superblock CRC */
    } _WRS_PACK_ALIGN(1) HRFS_DISK_SUPER_BLOCK, * HRFS_DISK_SUPER_BLOCK_PTR;

typedef struct hrfs_incore_super_block_struct
    {
    char      idString[8];  /* Identification or eyecatcher string */
    INT64     ctime;        /* time at which superblock was created. */
    UINT8     majorVers;    /* Major version number */
    UINT8     minorVers;    /* Minor version number */
    UINT16    blkSize2;     /* Block size as a power of 2. */
    UINT32    totalBlks;    /* Total # of blocks in fs (including offset). */

    UINT32    reservedBlks; /* Size of the reserved space at */
                            /* the start of the media. */

    UINT32    iNodeCount;   /* The number of iNodes this file */
                            /* system instantiation has. */

    UINT32    bgSize;       /* Block group size  (=dsSize + 1 for 1st iter) */
    UINT32    dsSize;       /* Data space size   (=bgSize - 1 for 1st iter) */
    UINT32    nBlkGroups;   /* Number of block groups. (1 for 1st iteration) */

    UINT32    fsbOff[2];    /* 1st & 2nd free space bitmap offsets */
    UINT32    fibOff[2];    /* 1st & 2nd free inode bitmap offsets */

    UINT32    itOff;        /* inode table offset */
    UINT32    ijOff;        /* inode journal offset */

    UINT32    tmOff[2];     /* 1st & 2nd transaction map offsets */
    UINT32    tmrOff[2];    /* 1st & 2nd transaction  master record offsets */

    UINT32    dsOff;        /* data space offset */
    UINT32    pad;          /* pad out structure */
    UINT32    crc;          /* superblock CRC */
    } HRFS_INCORE_SUPER_BLOCK, * HRFS_INCORE_SUPER_BLOCK_PTR;

/* HRFS directory entry */
typedef struct hrfs_dirent
    {
    UINT32         iNodeNumber;      /* iNode corresponding to file */
    unsigned char  fileName[HRFS_MAX_FILENAME_LEN + 1];   /* File Name */
    } _WRS_PACK_ALIGN(1) HRFS_DIRENT, * HRFS_DIRENT_PTR;

typedef struct hrfsTransaction
    {
    UINT64                 transNo;

    SEMAPHORE              transMutex;

    int                    state;
    SEMAPHORE              stateSem;

    /*
     * We don't use the delay write code before, since it is in the vnode layer,
     * it is not suit for the new transaction mechanism of HRFS.
     *
     * So we put the delay write code in HRFS layer to make the new
     * transaction mechanism be easy to implement.
     */

    /*
     * metaBlkList contains dirty buffers of meta data in current transaction:
     * 1) the buffers in metaBlkList can't be scheduled.
     * 2) the next transaction won't start until finsh commiting metaBlkList of
     *    current transaction.
     * 3) buffers are not in free list.
     */

    TAILQ_HEAD(, hrfsBuf)  metaBlkList;

    /*
     * dataBlkList contains dirty buffers of file data in current transaction:
     * 1) it can be scheduled.
     * 2) starting next transaction is allowed when committing dataBlkList.
     * 3) buffers are not in free list.
     */

    TAILQ_HEAD(, hrfsBuf)  dataBlkList;

    int                    datablkNo;
    SEMAPHORE              datablkNoSem;

    int                    totalBlkNo;
    UINT32                 freeInodesCommitTrans;
    UINT32                 freeDataBlksCommitTrans;

    /*
     * For the current transaction, it can journal inode when the previous is
     * committing. The journal for the new transaction is empty and can't be
     * committed to disk until the previous is totally commtted. So we can
     * jouranl the inode of current transaction in the memory and commit it when
     * committing the current transaction.
     */

    HRFS_INODE_JOURNAL_PTR inodeJournal;
    int                    freeJournalCnt;

     /* back the TMR for recovering some variables of volume desc
      * upon failed transaction. */

    HRFS_TMR               savedTMR;

    int                    aliveHandleNo;
    SEMAPHORE              aliveHandleNoSem;

    TAILQ_HEAD(freeQueue, blkEntry) pinList;

    void                 * validFsbTm;
    void                 * validFibTm;

    int                    totalHandleNo;
    } HRFS_TRANSACTION;

typedef struct hrfsBuf
    {
    TAILQ_ENTRY(hrfsBuf)  dirtyList;
    struct buf          * owner;
    HRFS_TRANSACTION    * trans;
    } HRFS_BUF;

/*
 * Fields that describe the physical layout of the backing media,
 * try to go in the volume descriptor.
 */
RB_HEAD(blkTree, blkEntry);

typedef struct hrfs_volume_desc      /* HRFS volume descriptor structure */
    {
    u_int                 magic;          /* value: HRFS_VOLUME_MAGIC */
    HRFS_VOL_STATE        state;          /* Created/Mounted/Dying/Dead */
    HRFS_INCORE_SUPER_BLOCK *pSuperBlk;   /* HRFS Super Block */
    device_t              device;         /* device associated with volume */
    sector_t              nSectors;       /* # of sectors on backing media */
    UINT32                sectorSize;     /* sector size of backing media */
    UINT32                sectorsPerBlk;  /* The number of sectors in a block */
    UINT32                sectorsPerBlk2; /* The number of sectors in a block */
                                          /* as a power of 2 */
    UINT32                blkSize;        /* block size in bytes */
    UINT32                blkCount;       /* # of blocks */
    int                   validTransSet;  /* valid transaction set: 0 or 1 */
    UINT64                validTransNo;   /* The transaction number of the */
                                          /* last set transaction point */
    UINT64                workingTransNo; /* The transaction number of the */
                                          /* current transaction. */
    atomic_t              volState;       /* volume status.       */
    BOOL                  multiTrans;     /* Used for atomic set: 0 or 1 */
    int                   commitPeriod;
    TASK_ID               commitTask;
    UINT32                numInodesToDelete;

    /*
     * HRFS allow two transaction works together: one is commiting to disk and
     * another is writing to cache. In this way, HRFS can make full use of CPU
     * and disk I/O. curTrans is the transaction which is writing to cache and
     * prevTrans is the transaction which is commiting to the disk.
     */

    HRFS_TRANSACTION    * workTrans;

    HRFS_TRANSACTION    * commitTrans;

    HRFS_TRANSACTION      transBuf[2];

    SEMAPHORE             volMutex;
    int                   volMutexInit;
    SEMAPHORE             barrierSem;
    int                   barrierSemInit;
    int                   handleBarrier;

    SEM_ID                commitTaskWaitSem;
    SEM_ID                fsMutex;
    SEM_ID                rollbackSem;

    struct blkTree        pinTree;

    /*
     * The "allocation rotors" make the block allocator scan from the
     * middle back to the middle, instead of start to end every time.
     * Each scan starts from wherever the last scan was successful.
     * This tends to make blocks (and inodes) get allocated sequentially.
     *
     * This is purely for optimization (and not yet turned on).
     */

    UINT32                allocRotor[2];  /* [0]: FSB, [1]: FIB */

    /*
     * These are mainly used for the "sector discard" interface, but also
     * help speed up allocation.
     *
     * The "bitmap point" number controls when the code switches from
     * "raw blocks" to "bitmap".  It can never be larger than the raw
     * block array, of course, but for some applications performance may
     * be better with a smaller number (and for debugging we want to
     * be able to set it to a tiny number).  We are using the rawBlocks
     * field if blksFreedThisTrans <= blksFreedBitmapPoint, otherwise we
     * are using the bitmap.
     *
     * The "magic number" 8192 here is based on the maximum file system and
     * block size ... probably should use a #define for this.
     */

    BOOL                  doDiscard;
    UINT32                blksFreedThisTrans;   /* blocks freed since commit */
    UINT32                inodesFreedThisTrans; /* inodes freed since commit */

    UINT32                freeInodes;
    UINT32                freeDataBlks;
    struct mount *        pMount;
    DL_LIST               toBeDelList;    /* List of "to be deleted" inodes */

    void *                pBlkData;
    SEM_ID                bioSem;      /* Binary semaphore for BIO/XBD calls */
    } HRFS_VOLUME_DESC;

typedef struct hrfsHandle
    {
    HRFS_TRANSACTION * trans;
    HRFS_VOLUME_DESC * volDesc;
    int                policy;
    int                wrBlkNo;
    int                hrfsVop;   /* hrfs operations */
    } HRFS_HANDLE;

typedef struct hrfs_dev             /* HRFS device structure */
    {
    HRFS_VOLUME_DESC  hrfsVolDesc;  /* HRFS Volume Descriptor */

    u_char *          pSectorData;  /* sector scratch-pad */
    SEM_ID            bioSem;       /* Binary semaphore for BIO/XBD calls */
    } HRFS_DEV;

typedef struct hrfs_tm              /* structure used by time functions */
    {
    struct tm tm;    /* original [tm] structure.                   */
    int       msec;  /* milliseconds after the second - [0..999]   */
    } HRFS_TM;

struct blkEntry
    {
    RB_ENTRY(blkEntry)    rbNode;
    TAILQ_ENTRY(blkEntry) qNode;
    UINT32 blkNo;
    };

typedef struct hrfsErrHandleParam
    {
    FUNCPTR             funptr;
    char *              msg;
    _Vx_usr_arg_t       arg1;
    _Vx_usr_arg_t       arg2;
    _Vx_usr_arg_t       arg3;
    _Vx_usr_arg_t       arg4;
    BOOL                ignoreFlag;
    UINT32              blkNum;
    UINT32              dataType;
    unsigned            bio_flag;
    HRFS_VOLUME_DESC *  pVolDesc;
    struct bio *        pBio;
    struct buf *        pBuf;
    } HRFS_ERR_HANDLE_PARAM;

typedef void(*HRFS_USER_DEF_HANDLER)(const char *, int, HRFS_ERR_HANDLE_PARAM*);

/* externs */

extern int    hrfsMaxBuffers;
extern int    hrfsCurBuffers;

extern STATUS hrfsSuperBlockRd (HRFS_DEV * devPtr);
extern UINT32 hrfsCksum (char * data, UINT32 crcIn, UINT32 size);
extern int hrfsInodePut(HRFS_HANDLE *,struct vnode *, HRFS_DEV *, HRFS_INODE_PTR);
extern int hrfsInodePutRewind(struct vnode *, HRFS_DEV *, HRFS_INODE_PTR);
int hrfsValidateInodeJournal(HRFS_HANDLE *, UINT32 *, int);
int hrfsUpdateInodeJournal(HRFS_HANDLE *, HRFS_DEV *, HRFS_INODE_PTR);
extern int  hrfsJournalRewindTrans (HRFS_TRANSACTION * trans,
                                    HRFS_VOLUME_DESC * pVolDesc);

extern int  hrfsInodeGet       (struct vnode *);
extern int  hrfsInodeAlloc     (HRFS_HANDLE *, HRFS_DEV *, HRFS_INODE *,
                                struct vattr *);
extern int  hrfsDataBlockAlloc (HRFS_HANDLE *, HRFS_DEV *, HRFS_INODE *,
                                UINT32 *);
extern int  hrfsDataBlockFree  (HRFS_HANDLE *, HRFS_DEV *, UINT32);
extern int  hrfsInodeFree      (HRFS_HANDLE *, HRFS_DEV *, UINT32);

extern int  hrfsCommit (struct mount *);
extern int  hrfsMount  (struct mount *);
extern int  hrfsStat   (struct mount *, struct statvfs *);

extern int  hrfsInodeGetInternal (struct vnode *, HRFS_VOLUME_DESC *,
                                  HRFS_INODE *);
extern int  hrfsTransactionRollback  (struct mount *);

extern void hrfsFreeBufs (struct hrfsBuf * *, int, int);

extern int  hrfsFindTriePath(struct vnode *, UINT32, HRFS_INODE_PTR,
                     HRFS_VOLUME_DESC *, UINT32 *, struct hrfsBuf * *);

extern void hrfsVopInternalReadStrategy (struct vnode * pSyncer,
                                         struct buf * pBuf,
                                         UINT32 pbn);
extern int  hrfsDirEntFromSlot (struct vnode *, struct hrfsBuf **,
                                HRFS_DIRENT **);

extern UINT32 hrfsBitGet(unsigned char *, UINT32);

extern void hrfsInodeDiskCoreConvertV1R1 (HRFS_INCORE_INODE *pDest,
                                          HRFS_DISK_INODE_V1R1 *pSrc);
extern void hrfsInodeCoreDiskConvertV1R1 (HRFS_DISK_INODE_V1R1 *pDest,
                                          HRFS_INCORE_INODE *pSrc);
extern void hrfsInodeDiskCoreConvertV1R2 (HRFS_INCORE_INODE *pDest,
                                          HRFS_DISK_INODE_V1R2 *pSrc);
extern void hrfsInodeCoreDiskConvertV1R2 (HRFS_DISK_INODE_V1R2 *pDest,
                                          HRFS_INCORE_INODE *pSrc);

extern void hrfsSuperblockDiskCoreConvert(HRFS_INCORE_SUPER_BLOCK *pDest,
                                          HRFS_DISK_SUPER_BLOCK *pSrc);
extern void hrfsSuperblockCoreDiskConvert(HRFS_DISK_SUPER_BLOCK *pDest,
                                          HRFS_INCORE_SUPER_BLOCK *pSrc);

extern hrfsTime_t hrfsTimeGet      (void);
extern STATUS     hrfsTimeSplit    (hrfsTime_t msec, HRFS_TM * pHrfsTm);
extern hrfsTime_t hrfsTimeCondense (HRFS_TM * pHrfsTm);

struct hrfsHandle * hrfsProtectBegin (HRFS_VOLUME_DESC * hrfsVol, int policy);
void hrfsProtectEnd(struct hrfsHandle * handle,int result);
int hrfsReadBlk(struct vnode *, lblkno_t, int, struct hrfsBuf  * *, int);
int hrfsCowBlk(struct hrfsHandle *, struct vnode *, struct hrfsBuf *,
               struct hrfsBuf  * *, void *);
int hrfsWriteBlk(struct hrfsHandle *,struct vnode *, struct hrfsBuf *);
HRFS_BUF * hrfsGetBlk(struct vnode *, lblkno_t, int size, int);
void hrfsRelseBlk(struct hrfsBuf *);
void hrfsSyncXbdDone(struct bio *);
STATUS hrfsInternalErrorHandler(const char *, int, HRFS_ERR_HANDLE_PARAM *);
void hrfsUpdateErrHandlePolicy (UINT32 policy,
                                HRFS_USER_DEF_HANDLER pHandler);

#ifdef HRFS_DEBUG_BMP
extern void hrfsPrintBmp         (unsigned char *, UINT32);
#endif

#ifdef HRFS_DEBUG_SUPER
extern void hrfsPrintSuperBlk    (HRFS_INCORE_SUPER_BLOCK_PTR);
#endif

int blkKeyCompare(struct blkEntry *,struct blkEntry *);
RB_PROTOTYPE(blkTree, blkEntry, rbNode, blkKeyCompare);

/* global configuration options */

extern BOOL hrfsAccessTimeStampEnabled;
extern BOOL hrfsHighSpeedWriteMode;

/* global tables for hrfs vnode operations */

extern const struct vfsops    * hrfsVfsOps;
extern const struct vnode_ops * hrfsOps;
extern const struct vnode_ops * hrfsDirOps;
extern const struct vnode_ops * hrfsFileOps;
extern const struct vnode_ops * hrfsSymLinkOps;

/* R/W vnode operator table definition */

extern const struct vfsops    hrfsVfsOpsConfigRW;
extern const struct vnode_ops hrfsOpsConfigRW;
extern const struct vnode_ops hrfsDirOpsConfigRW;
extern const struct vnode_ops hrfsFileOpsConfigRW;
extern const struct vnode_ops hrfsSymLinkOpsConfigRW;

/* R/O vnode operator table definition */

extern const struct vfsops    hrfsVfsOpsConfigRO;
extern const struct vnode_ops hrfsOpsConfigRO;
extern const struct vnode_ops hrfsDirOpsConfigRO;
extern const struct vnode_ops hrfsFileOpsConfigRO;
extern const struct vnode_ops hrfsSymLinkOpsConfigRO;

/*
 * HRFS vnode operators
 */

extern int  hrfsVopLookup   (struct vnode *, struct vnode **fvp,
                             struct componentname *);
extern int  hrfsVopOpen     (struct vnode *, int, struct ucred *);
extern int  hrfsVopClose    (struct vnode *, int, struct ucred *);
extern int  hrfsVopCloseWithUpdate (struct vnode *, int, struct ucred *);
extern int  hrfsVopIoctl    (struct vnode *, u_long, void *, int,
                             struct ucred *);
extern int  hrfsVopIoctl    (struct vnode *, u_long, void *, int,
                             struct ucred *);
extern void hrfsVopPrint    (struct vnode *);
extern int  hrfsVopActivate (struct vnode *);
extern int  hrfsVopAccess   (struct vnode *, int, struct ucred *);
extern int  hrfsFileVopRead (struct vnode *, struct uio *, int,
                             struct ucred *);
extern int  hrfsVopFsync    (struct vnode *, struct ucred *, int);
extern int  hrfsVopSeek     (struct vnode *, voff_t, voff_t,
                             struct ucred *);
extern int  hrfsVopAbortop  (struct vnode *, struct componentname *);
extern int  hrfsVopGetAttr  (struct vnode *, struct vattr *,
                             struct ucred *);
extern int  hrfsVopReadDir  (struct vnode *, struct dirent *,
                             struct ucred *, int *, int *);
extern int  hrfsVopPathConf (struct vnode * vp, long name, long * retval);

extern int  hrfsVfsStart    (struct mount *  pMount, int  flags);
extern int  hrfsVfsUnmount  (struct mount *  pMount, int  flags);
extern int  hrfsVfsRoot     (struct mount *  pMount,
                             struct vnode ** ppRoot);
extern int  hrfsVfsStatVfs  (struct mount *  pMount,
                             struct statvfs * pStat);
extern int  hrfsVfsVget     (struct mount *  pMount, ino_t  iNodeNum,
                             struct vnode ** ppVnode);
extern void hrfsVfsInit     (void);
extern void hrfsVfsReInit   (void);
extern void hrfsVfsDone     (void);
extern int  hrfsVopCreate   (struct vnode *, struct vnode **,
                             struct componentname *, struct vattr *);
extern int  hrfsVopInactive (struct vnode *);
extern int  hrfsFileVopWrite(struct vnode *, struct uio *,
                             int, struct ucred *);
extern int  hrfsVopSetAttr  (struct vnode *, struct vattr *,
                             struct ucred *);
extern int  hrfsVopTruncate (struct vnode *, voff_t, int, struct ucred *);
extern int  hrfsVopLink     (struct vnode * dvp, struct vnode * vp,
                             struct componentname * cnp);
extern int  hrfsVopUnlink   (struct vnode * dvp, struct vnode * vp,
                             struct componentname * cnp);
extern int  hrfsVopMkDir    (struct vnode *dvp, struct vnode **vpp,
                             struct componentname *cnp, struct vattr *vap);
extern int  hrfsVopRmDir    (struct vnode *dvp, struct vnode *vp,
                             struct componentname *cnp);
extern int  hrfsVopRename   (struct vnode *, struct vnode *,
                             struct componentname *, struct vnode *,
                             struct vnode *, struct componentname *);
extern int hrfsVopAdvLock (struct vnode *, void *, int, struct flock *, int);

extern int  hrfsVfsWriteTransStart (struct mount *, BOOL);
extern int  hrfsVfsWriteTransEnd (struct mount *, int);
extern void hrfsVopReadStrategy (struct vnode *, struct buf *);
extern int  hrfsVopReadInactive (struct vnode *);

extern BOOL hrfsInodeToBeDeleted (HRFS_VOLUME_DESC *, UINT32);
extern int hrfsInternalTruncate (HRFS_HANDLE *, HRFS_DEV *, struct vnode *,
                                 struct ucred *, voff_t);
void hrfsUpdateBioPhy(HRFS_VOLUME_DESC * , struct bio *, UINT32);

int hrfsUpdateTriePath(struct hrfsHandle *, HRFS_DEV *, struct vnode *,
                       UINT32, UINT32, struct hrfsBuf * *);
int hrfsDeleteTriePath(struct hrfsHandle *, HRFS_DEV *, struct vnode *,
                       UINT32, struct hrfsBuf * *);

void hrfsCommitTask(_Vx_usr_arg_t, _Vx_usr_arg_t, _Vx_usr_arg_t, _Vx_usr_arg_t,
                    _Vx_usr_arg_t, _Vx_usr_arg_t, _Vx_usr_arg_t, _Vx_usr_arg_t,
                    _Vx_usr_arg_t, _Vx_usr_arg_t);

void hrfsRebusyBlk(struct hrfsBuf *);
void hrfsPanic(const char *, int, const char *fmt, ...);
void hrfsWaitTransCommit(HRFS_VOLUME_DESC *);

/* r/w init function */

extern int hrfsWrLibInit (int _maxBufs, int _maxFiles);

#ifdef __cplusplus
    }
#endif

#endif /* __INChrfsLibP */
