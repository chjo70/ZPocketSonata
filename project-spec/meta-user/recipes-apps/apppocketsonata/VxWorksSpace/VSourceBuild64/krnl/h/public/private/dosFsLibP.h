/* dosFsLibP.h - DOS file system private header file */

/*
 * Copyright (c) 1984-2007, 2009-2013, 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jul17,ghs integrate file system type magic number (F9150)
25apr17,yjl To detect directory entry with file size set (V7STO-808)
08nov16,y_y add semaphore to protect dosFsDiscard and fix typo. (V7STO-714)
22apr16,yjl dosFsVolFormat() in usrAppInit() sometimes fails. (V7STO-619)
22dec15,yjl unlink(fileName) system call of VxWorks6.9+ATOM does not work
            correctly (V7STO-546)
26oct15,yjl UP/SMP:SD card initialization take longer time on all board
20nov13,ghs Merge continuous trim block (WIND00439644)
10oct13,ghs Expand _PARM_PATH_MAX to be compatible with Windows FAT32
            (WIND00438274)
31jan13,xwu Fix WIND00399652 dosFsCacheCreate() user shall be able to define
            smaller cache size
30jan13,ghs Add a link node field for DOS_CACHE_DESC (WIND00395472)
25sep12,zly Change invlBlks and dirtyBlks to int from short type.
            (WIND00365563)
14sep12,yjl Fix WIND00376255, dosFs to be compatible with Windows FAT32
            naming rules for file/directory name length.
10aug12,yjl Fix defect WIND00364508, To get correct block size from disk
            and not always uses 512
13may11,yjl Fix defect WIND00259953, dosFs: moving directory creates
            bogus directory entries
27jul10,sjz fix defect WIND00224526, upgrade tiny cache for high performance
18may10,yjl manually merge from 6.8.1 to 6.9
29apr10,pad Moved extern C statement after include statements.
21apr10,yjl fix defect WIND00208806
01feb10,hps fix WIND00198472
18jan10,hps replace semTake stateMtx with spinLock and modify default
            values for BLOCKS_PER_DATA_DIR_CACHE_GROUP and FS_SETSIZE
27oct09,yjl fix for FS_NFDBITS define, fsMask in place of fd_mask
23oct09,yjl manually merge release6_7-64bit
03aug09,hps requirement WIND00142043, group cache with background flush
29jul09,yjl remove warning about howmany
22jul09,yjl requirement WIND00142043
08jul09,zly remove macro "DOS_VOLUME_BIO_BUFFER_SIZE"(WIND00161794)
04jun09,yjl check in for performance WIND00142043 DOSFS Performance
20aug07,jlk WIND00100989: Added dirty count.
29jun07,act WIND00096598: rename can detach directories
03may07,pcm added 'readOnly' field to volume descriptor
17jan07,act add discard-interface discovery
25oct06,pcm made changes for DosFS Cache
21aug06,pcm added extern VOIDFUNCPTR's
03mar06,dcc fixed SPR 117527
23jan06,dcc optimized backwards seeks.
12oct05,dcc implemented non DMA-safe option for dosFs cache.
29sep05,dcc implemented write cache.
04aug05,dcc added more cache statistics data.
04aug05,jlk moved formatter function pointer, dosFsFmtRtn, to dosFsLib.h
18jul05,jlk Added formatter function pointer, dosFsFmtRtn
07apr05,dcc added cache support to dosFs.
18apr05,dcc updated dosFs formatter.
30mar05,dcc updated to use several bios per volume.
31jan05,dcc modified to use XBD interface.
07oct04,act split flags and mode in pathLkup function
26aug04,feg Coverity code coverage bug #261 of 2004-06-22
18apr04,act add Unicode; change (and document) chkdsk semi-secret info
04apr04,jkf SPR#95752: changing openMode from u_char to u_int
21mar04,act changes to support clean bit
04mar04,act fix spelling in comments, type of parDirStartCluster
02sep03,jkf add volWriteOpt to DOS_VOLUME_DESC for write-through support.
03mar02,jkf SPR#29751, added volIsCaseSens to DOS_VOLUME_DESC, orig by chn
30nov01,jkf SPR#68203, add updateLastAccessDate boolean to DOS_VOLUME_DESC
17nov01,jkf fixing dosFsVolIsFat12 divide error.
10nov01,jkf SPR#32178, made dosFsVolDescGet public, moved
            DOS_VOLUME_DESC_ID typedef to public dosFsLib.h
30jul01,jkf SPR#69031, common code for both AE & 5.x.
13mar01,jkf SPR#34704, adding dosFsVolIsFat12
29feb00,jkf removed semLibP.h usage for t3.
31aug99,jkf CBIO API overhaul changes.
31jul99,jkf added DOS_BOOT_FSTYPE_ID, and DOS_BOOT_FSTYPE_LEN,
            SPR#28272, 28273, 28274, 28275.
31jul99,jkf T2 merge, tidiness & spelling.
21dec98,mjc changed name of <contigEnd> field in structure <DOS_FILE_HDL>
            to <contigEndPlus1>
22nov98,vld field <seekOut> changed to <seekOutPos> in
            DOS_FILE_DESC structure;
            added macros POS_TO_DD_COOKIE() and DD_COOKIE_TO_POS();
            fields <rootStartSec> and <rootNSec> added to
            DOS_DIR_DESC structure
23sep98,vld field <bufToDisk> added to CHK_DSK_DESC;
17sep98,vld field <activeCopyNum> added to DOS_FAT_DESC;
            changed prototypes of some func ptr fields of DOS_FAT_DESC;
            func ptr field <syncToggle> added to DOS_FAT_DESC;
            added constant DOS_FAT_RAW;
            added constant DOS_FAT_SET_ALL;
            changed prototypes of some function ptrs
            in DOS_FAT_DESC;
16sep98,vld definition of DOS_VOL_LABEL_LEN moved to dosFsLib.h
02jul98,lrn ready for prerelease
22jan98,vld written,
*/

#ifndef __INCdoFsLibP
#define __INCdoFsLibP

#include <vxWorks.h>
#include <private/dosFsVerP.h>
#include <semLib.h>
#include <spinLockLib.h>
#include <iosLib.h>
#include <dirent.h>
#include <stat.h>

#include <dosFsLib.h>
#include <drv/xbd/bio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* use 64-bit arithmetic */

#define SIZE64

#define DOS_VX_LONG_NAMES_SYS_ID    "VXEXT"

#define SLASH           '/'
#define BACK_SLASH      '\\'
#define DOT             '.'
#define SPACE           ' '
/*
 * handlers ID.
 * Each handler (FAT, Directory and so on) must have its own
 * identification number in order to be able to distinguish
 * different handler types when selecting handlers
 */
/* directory handlers */

#define DOS_DIR_HDLR_MASK   (1 << 8)    /* dir handlers mask */
#define DOS_DIROLD_ID       (DOS_DIR_HDLR_MASK +1)  /* 8.3 and vxLong names */

/* FAT handlers */

#define DOS_FAT_HDLR_MASK   (1 << 9)    /* fat handlers mask */

/* function arguments */

/* for directory handler API */

#define DH_TIME_CREAT   1
#define DH_TIME_MODIFY  (1<<1)
#define DH_TIME_ACCESS  (1<<2)
#define DH_SIZE_UPDATE  (1<<4)
#define DH_DELETE       (1<<8)

/* FAT handler API */

#define FAT_NOT_ALLOC   0
#define FAT_ALLOC       (1<<31)
#define FAT_ALLOC_ONE   (FAT_ALLOC|1)
#define FH_INCLUDE      0
#define FH_EXCLUDE      1
#define FH_FILE_START   (-1L)

/* dosFs file system constants */

#define DOS_BOOT_SEC_NUM        0       /* sector number of boot sector */
#define DOS_MIN_CLUST           2       /* lowest cluster number used */
#define DOS_SYS_ID_LEN          8       /* length of system ID string */
#define DOS_FAT_12BIT_MAX       4085    /* max clusters for 12-bit FAT entries*/
#define DOS_NFILES_DEFAULT      20      /* default max number of files */
#define DOS_FAT_DEFAULT_SECTOR_SIZE  512  /* fat default sector size */

/* Boot sector offsets */

/*   Because the MS-DOS boot sector format has word data items
 *   on odd-byte boundaries, it cannot be represented as a standard C
 *   structure.  Instead, the following symbolic offsets are used to
 *   isolate data items.  Non-string data values longer than 1 byte are
 *   in "Intel 8086" order.
 *
 *   These definitions include fields used by MS-DOS Version 4.0.
 */
#define DOS_BOOT_JMP            0x00    /* 8086 jump instruction     (3 bytes)*/
#define DOS_BOOT_SYS_ID         0x03    /* system ID string          (8 bytes)*/
#define DOS_BOOT_BYTES_PER_SEC  0x0b    /* bytes per sector          (2 bytes)*/
#define DOS_BOOT_SEC_PER_CLUST  0x0d    /* sectors per cluster       (1 byte) */
#define DOS_BOOT_NRESRVD_SECS   0x0e    /* # of reserved sectors     (2 bytes)*/
#define DOS_BOOT_NFATS          0x10    /* # of FAT copies           (1 byte) */
#define DOS_BOOT_MAX_ROOT_ENTS  0x11    /* max # of root dir entries (2 bytes)*/
#define DOS_BOOT_NSECTORS       0x13    /* total # of sectors on vol (2 bytes)*/
#define DOS_BOOT_MEDIA_BYTE     0x15    /* media format ID byte      (1 byte) */
#define DOS_BOOT_SEC_PER_FAT    0x16    /* # of sectors per FAT copy (2 bytes)*/
#define DOS_BOOT_SEC_PER_TRACK  0x18    /* # of sectors per track    (2 bytes)*/
#define DOS_BOOT_NHEADS         0x1a    /* # of heads (surfaces)     (2 bytes)*/
#define DOS_BOOT_NHIDDEN_SECS   0x1c    /* # of hidden sectors       (4 bytes)*/
#define DOS_BOOT_LONG_NSECTORS  0x20    /* total # of sectors on vol (4 bytes)*/
#define DOS_BOOT_DRIVE_NUM      0x24    /* physical drive number     (1 byte) */
#define DOS_BOOT_SIG_REC        0x26    /* boot signature record     (1 byte) */
#define DOS_BOOT_VOL_ID         0x27    /* binary volume ID number   (4 bytes)*/
#define DOS_BOOT_VOL_LABEL      0x2b    /* volume label string      (11 bytes)*/
#define DOS_BOOT_FSTYPE_ID      0x36    /* new MS ID, FAT12 or FAT16 */
#define DOS_BOOT_FSTYPE_LEN     0x08    /* length in bytes of FSTYPE */
#define DOS_BOOT_FSTYPE_FAT16   "FAT16   "  /* FSTYPE_ID FAT16 */
#define DOS_BOOT_FSTYPE_FAT12   "FAT12   "  /* FSTYPE_ID FAT12 */
#define DOS_BOOT_SYSID_FAT32    "FAT32   "  /* FAT32 SYS_ID, */
#define DOS_BOOT_PART_TBL       0x1be   /* first disk partition tbl (16 bytes)*/
#define DOS_EXT_BOOT_SIG        0x29    /* value written to boot signature */
                                        /* record to indicate extended */
                                        /* (DOS v4) boot record in use  */
/* extended FAT32 fields offsets */

#define DOS32_BOOT_SEC_PER_FAT  0x24    /* sectors per FAT           (4 bytes)*/
#define DOS32_BOOT_EXT_FLAGS    0x28    /* FAT  miscellaneous flags  (2 bytes)*/
#define DOS32_BOOT_FS_VERSION   0x2a    /* file system version       (2 bytes)*/
#define DOS32_BOOT_ROOT_START_CLUST 0x2c /* root start cluster       (4 bytes)*/
#define DOS32_BOOT_FS_INFO_SEC  0x30    /* file system info sector   (2 bytes)*/
#define DOS32_BOOT_BOOT_BKUP    0x32    /* bkup of boot sector       (2 bytes)*/
#define DOS32_BOOT_RESERVED     0x3a    /* reserved area             (6 bytes)*/
#define DOS32_BOOT_BIOS_DRV_NUM 0x40    /* 0x80 for hard disk        (1 byte)*/
#define DOS32_BOOT_SIGNATURE    0x42    /* ')' (0x29)                (1 byte)*/
#define DOS32_BOOT_VOL_ID       0x43    /* binary volume Id          (4 bytes*/
#define DOS32_BOOT_VOL_LABEL    0x47    /* volume label string      (11 bytes)*/
#define DOS32_BOOT_FS_TYPE      0x52    /* string FAT32 */

#define DOS_BOOT_BUF_SIZE       0x80    /* size of buffer large enough to */
                                        /* get boot sector data to */
                                        /* ( without partition table ) */

#ifdef _WRS_CONFIG_DOSFS_NAME_LENGTH_COMPAT
#define CHK_MAX_PATH    1080
#else
#define CHK_MAX_PATH    1024    /* max path in check disk's message */
#endif

/* macros */

typedef long            fsMask;

#define FS_SETSIZE      1024
#define FS_NBBY         8
#define FS_NFDBITS      (sizeof (fsMask) * FS_NBBY) /* bits per mask */
#define fsHowmany(x, y) ((unsigned int)(((x)+((y)-1)))/(unsigned int)(y))

typedef struct fsSet
    {
    fsMask  fsBits[fsHowmany(FS_SETSIZE, FS_NFDBITS)];
    } FS_SET;

#define FS_CLR(n, p)    ((p)->fsBits[(n)/FS_NFDBITS] &= ~((1L) << ((n) % FS_NFDBITS)))
#define FS_ISSET(n, p)  ((p)->fsBits[(n)/FS_NFDBITS] & ((1L) << ((n) % FS_NFDBITS)))
#define FS_SET(n, p)    ((p)->fsBits[(n)/FS_NFDBITS] |= ((1L) << ((n) % FS_NFDBITS)))
#define FS_ZERO(p)      bzero ((char *) (p), sizeof (*(p)))

/* sector macros */

#define NSECTORS(pVolDesc, off)   ((off) >> (pVolDesc)->secSizeShift)
#define OFFSET_IN_SEC(pVolDesc, off)          \
                ((off) & ((pVolDesc)->bytesPerSec - 1))

/* conversions of sector <-> cluster numbers */

/* check, if directory is root */

#define IS_ROOT(pFd)  \
    ((pFd)->pFileHdl->dirHdl.parDirStartCluster == (uint32_t) NONE)

#define ROOT_SET(pFd) \
    ((pFd)->pFileHdl->dirHdl.parDirStartCluster = (uint32_t) NONE)

/* FAT entry types, returned by clustValueSet() and clustValueGet() */

#define DOS_FAT_AVAIL   0x00000001  /* available cluster */
#define DOS_FAT_EOF     0x00000002  /* end of file's cluster chain */
#define DOS_FAT_BAD     0x00000004  /* bad cluster (damaged media) */
#define DOS_FAT_ALLOC   0x00000008  /* allocated cluster */
#define DOS_FAT_INVAL   0x00000010  /* invalid cluster (illegal value) */
#define DOS_FAT_RESERV  0x00000020  /* reserved cluster */
#define DOS_FAT_RAW     0x00000040  /* write raw data, when fat copy */
                                    /* is used as temporary buffer */
#define DOS_FAT_SET_ALL 0x00000080  /* fill all bytes of FAT copy with */
                                    /* a specified value. */
#define DOS_FAT_ERROR   0x11111111  /* CBIO ERROR */

/*
 * handlers Id-s. All installed handlers are sorted by
 * Id-s, and are tried on every volume in accordance with that order
 */
#define DOS_MAX_HDLRS       4       /* max handlers of one type */
#define DOS_FATALL_HDLR_ID  255     /* dosFsFat16 - supports FAT 12/16/32 */
                                    /* in a simple manner */
                                    /* ( without any buffering ) */
#define DOS_VDIR_HDLR_ID    1       /* dosVDirLib - supports VDIR */
                                    /* directory structure for all FAT types */
#define DOS_DIROLD_HDLR_ID  2       /* dosDirOldLib - supports DOS4.0 */
                                    /* "8.3" names and vxLong names for */
                                    /* all FAT types */

typedef long long dsize_t;

/* definition of 64-bit type and macro to check for 32-bit overflowing */

#ifdef SIZE64

typedef long long   fsize_t;
#define DOS_IS_VAL_HUGE(val)    (((fsize_t)(val) >> 32) != 0)
                                /* test for 32 bit overflowing */
#define DOS_MAX_FSIZE           (~((fsize_t)1<<(sizeof(fsize_t)*8-1)))
                                /* max disk/file size */

#else   /* ! SIZE64 */

/* typedef u_long  fsize_t; */
typedef uint32_t  fsize_t;
#define DOS_IS_VAL_HUGE(val)    FALSE
#define DOS_MAX_FSIZE           ((fsize_t)(-1)) /* max disk/file size */

#endif /* SIZE64 */

/*
 * processing for dd_cookie field in DIR structure(). (see dirent.h)
 * Current position in directory supposed to be always power of 2
 */
#define POS_TO_DD_COOKIE(pos)   (((u_long)(pos)) | 1)
#define DD_COOKIE_TO_POS(pDir)  (((DIR *)(pDir))->dd_cookie & (~((long)1)))

#define DOS_VOLUME_BIO_SIZE     3 /* 3 bios per volume for the moment. This
                                   * value specify the limit of concurrent
                                   * media accesses
                                   */

#define DOS_VOL_NO_DMA_SET(pVolDesc)                \
    (pVolDesc->volOptions |= DOS_VOLUME_VOL_NO_DMA)

#define DOS_VOL_IS_NO_DMA(pVolDesc)             \
    ((pVolDesc->volOptions & DOS_VOLUME_VOL_NO_DMA) != 0)

/* typedefs */

typedef struct PATH_ARRAY   /* split path */
    {
    u_char *    pName;
    u_short nameLen;
    } PATH_ARRAY;

typedef PATH_ARRAY *    PATH_ARRAY_ID;

/*
 * Directory entry descriptor.
 * This structure is part of file handle and
 * is intended to directory handlers usage.
 */
typedef struct DOS_DIR_HDL
    {
    sector_t    sector;  /* sector containing  alias (short name) */
                         /* directory entry */
    sector_t    lnSector;/* sector containing long name start */
    off_t       offset;  /* alias (short name) directory entry offset */
                         /* in sector */
    off_t       lnOffset;/* long name offset in sector */
    cookie_t    cookie;  /* for cache quick access */
    uint32_t    parDirStartCluster; /* cluster containing parent */
                                    /* directory entry */

    /* implementation private usage */

    uint32_t    dh_Priv1;
    uint32_t    dh_Priv2;
    uint32_t    dh_Priv3;
    uint32_t    dh_Priv4;

    u_char  crc;    /* crcon directory entry (not used) */
    } DOS_DIR_HDL;
typedef DOS_DIR_HDL *   DOS_DIR_HDL_ID;

/*
 * File FAT descriptor.
 * This structure is part of file descriptor and
 * is intended to FAT handlers usage.
 */
typedef struct DOS_FAT_HDL
    {
    uint32_t    lastClust;  /* number of last passed cluster in chain */
    uint32_t    nextClust;  /* contents of <lastClust> entry */
    cookie_t    cbioCookie; /* CBIO dev. cookie for last accessed sector */
    uint32_t    errCode;    /*  */
    } DOS_FAT_HDL;
typedef DOS_FAT_HDL *   DOS_FAT_HDL_ID;

/*
 * File handle.
 * This structure is shared by all file descriptors (see below).
 * that are opened for the same file.
 * Field <pDirHdl> is filled and used by directory handler.
 */
typedef struct DOS_FILE_HDL
    {
    DOS_DIR_HDL dirHdl;     /* directory entry descriptor */
    fsize_t size;           /* recent file size */
    u_int   deleted  : 1,   /* file deleted */
            obsolet  : 1,   /* file was changed, but not closed yet */
            changed  : 1,   /* file was changed, but not closed yet */
            res  : 29;

    /* FAT fields */

    uint32_t    startClust; /* file start cluster */
                            /* ( 0 - not allocated yet ) */
    uint32_t    fatSector;  /* last modified FAT sector */

    u_short nRef;           /* reference count - the number of times */
                            /* file is simultaneously opened */
    u_char  attrib;         /* file attributes */
    u_int useCount;         /* file opened count */
    u_int linkCount;        /* file linked count */
    } DOS_FILE_HDL;

typedef DOS_FILE_HDL *  DOS_FILE_HDL_ID;

/*
 * File descriptor.
 * This structure is allocated every time new file is opened.
 * Fields <curSec>, <nSec>, <cluster> are filled by fat handler
 * via get next cluster operation and then are corrected by other
 * modules in accordance with operation being executed.
 */
typedef struct DOS_FILE_DESC
    {
    DOS_VOLUME_DESC_ID  pVolDesc;   /* volume descriptor ptr */
    DOS_FILE_HDL_ID     pFileHdl;   /* file handle, that is shared */
                                    /* between file descriptors */
                                    /* of the same file */
    fsize_t             pos;        /* current absolute position in file */
                                    /* for directory: absolute offset from */
                                    /* from directory start */
    fsize_t             seekOutPos; /* save position in case seek passes EOF */
                                    /* contains 0, if no such seek occurred */
    sector_t            curSec;     /* current data sector */
    sector_t            startContigSec; /* sector starting contiguous block */
    uint32_t            contigEndPlus1; /* end clust. of contiguous area in file + 1 */
    u_int               nSec;       /* number of contiguous sectors */
    cookie_t            cbioCookie; /* last accessed sector ptr */
                                    /* ( is filled by cbio ) */
    u_char              accessed;   /* file was accessed */
    u_char              changed;    /* file was changed */

    DOS_FAT_HDL         fatHdl;

    u_int               openMode;   /* open mode ( RDONLY/WRONLY/RDWR ) */

    BOOL                busy;
#ifdef _WRS_CONFIG_DOSFS_NAME_LENGTH_COMPAT
    int                 pathLength; /* full-path length */
#endif
    } DOS_FILE_DESC;

typedef DOS_FILE_DESC * DOS_FILE_DESC_ID;

/*
 * FAT handler descriptor.
 * This structure defines generic FAT handler API.
 * It must be start field in every FAT handler
 * descriptor structure.
 */
typedef struct DOS_FAT_DESC
    {
    /* interface functions */

    STATUS (*getNext)(DOS_FILE_DESC_ID pFd, u_int allocatePolicy);
                /* get/allocate next cluster for file */
                /* <allocatePolicy> : FAT_NOT_ALLOC/FAT_ALLOC/ */
                /* FAT_ALLOC_ONE */
    STATUS (*contigChk)(DOS_FILE_DESC_ID pFd);
                /* check file chain for contiguity */
    STATUS (*truncate)(DOS_FILE_DESC_ID pFd, sector_t sector,
                       uint32_t flag);
                /* truncate chain starting from <sector>, */
                /* <sector> = FH_FILE_START - from file start; */
                /* <flag> : FH_INCLUDE/FH_EXCLUDE */
    STATUS (*seek)(DOS_FILE_DESC_ID pFd, sector_t startSec, sector_t nSec);
                /* seek <nSec> sectors starting from */
                /* <startClust>, */
                /* <startClust> = FH_FILE_START - from file start */
    dsize_t (*nFree)(DOS_FILE_DESC_ID pFd);
                /* free bytes on disk */
    STATUS (*contigAlloc)(DOS_FILE_DESC_ID pFd, uint32_t nSec);
                /* allocate <nSec> contiguous first feet chain */
    size_t (*maxContig)(DOS_FILE_DESC_ID pFd);
            /* max free contiguous chain length in sectors */
    void (*volUnmount)(DOS_VOLUME_DESC_ID pVolDesc);
                /* free all resources, that were allocated */
                /* for the volume */
    void (*show)(DOS_VOLUME_DESC_ID pVolDesc);
                /* display handler specific data */
    STATUS (*flush)(DOS_FILE_DESC_ID pFd);
                /* flush all internal FAT handler data that */
                /* belongs to the file */
    void (*syncToggle)(DOS_VOLUME_DESC_ID pVolDesc, BOOL syncEnable);
                /* toggle FAT copies mirroring; synchronize */
                /* FAT copies, when mirror is being enabled */
    STATUS (*clustValueSet)
        (
        DOS_FILE_DESC_ID    pFd,
        uint32_t            fatCopyNum, /* FAT copy to use */
        uint32_t            clustNum,   /* cluster number to set */
        uint32_t            value,      /* DOS_FAT_AVAIL, DOS_FAT_EOF, */
                                        /* DOS_FAT_BAD, DOS_FAT_ALLOC, */
                                        /* DOS_FAT_INVAL, DOS_FAT_RESERV, */
                                        /* DOS_FAT_RAW */
        uint32_t            nextClust   /* next cluster number */
        );
    uint32_t (*clustValueGet)
        (
        DOS_FILE_DESC_ID    pFd,
        uint32_t            fatCopyNum, /* FAT copy to use */
        uint32_t            clustNum,   /* cluster number to check */
        uint32_t *          pNextClust  /* return cluster value */
        );

    /*
     * These are like clustValueSet and clustValueGet but at a much more
     * "raw" level, dealing directly with the raw values and operating
     * on any FAT entry, including FAT[0] and FAT[1].  Most users should
     * use the fully-cooked clustValue functions.  The "half baked"
     * fatEntryRead/fatEntryWrite functions still verify cluster number
     * while the fatRawRead and fatRawWrite functions do not -- and,
     * important internally, do not take a DOS_FILE_DESC_ID.
     */

    uint32_t (*fatEntryRead)
        (
        DOS_FILE_DESC_ID    pFd,        /* open file on volume */
        uint32_t            copyNum,    /* FAT copy to read */
        uint32_t            entry       /* FAT entry to read */
        );
    STATUS (*fatEntryWrite)
        (
        DOS_FILE_DESC_ID    pFd,        /* open file on volume */
        uint32_t            copyNum,    /* FAT copy to write */
        uint32_t            entry,      /* FAT entry to write */
        uint32_t            value       /* value to write there */
        );

    /*
     * These are lower level, with NO CHECKING AND MASKING AT ALL.
     * Use with great caution.  Note that they need a DOS_VOLUME_DESC
     * pointer, not a file descriptor, as they are used when there
     * are no open files.  In order to let the "slightly-more-cooked"
     * routines use them, though, they also take a cookie pointer
     * for cbio.
     */
    STATUS (*rawEntryRead)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume */
        cookie_t *          pCookie,    /* cbio cookie */
        uint32_t            copyNum,    /* copy to read */
        uint32_t            entry,      /* which FAT entry to read */
        uint32_t *          result      /* output from FAT[entry] stored here */
        );

    STATUS (*rawEntryWrite)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume */
        cookie_t *          pCookie,    /* cbio cookie */
        uint32_t            copyNum,    /* FAT copy to write */
        uint32_t            entry,      /* FAT entry to write */
        uint32_t            value,      /* value to write there */
        BOOL                writeThrough/* set to force write-through */
        );

    /*
     * routines to access the underlying XBD. It may be a direct access, or
     * through the dosFs disk cache.
     */
    STATUS (*rawBytesRW)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        sector_t            startBlock, /* starting block of the transfer */
        off_t               offset,     /* offset into block in bytes */
        addr_t              buffer,     /* address of data buffer */
        size_t              nBytes,     /* number of bytes to transfer */
        u_int               operation   /* DOS_READ/DOS_WRITE/WRITE_THROUGH */
        );

    STATUS (*rawBlkCopy)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        sector_t            srcBlock,
        sector_t            dstBlock,
        sector_t            numBlocks
        );

    STATUS (*rawIoctl)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        UINT32              command,
        addr_t              arg
        );

    /* read-only (unchanging) data */

    uint32_t cleanBitMask;              /* clean shutdown bit, 0 for FAT12 */

    /* varying data -- should not be in this data structure (!) */

    uint8_t activeCopyNum;              /* number of active FAT copy */
    } DOS_FAT_DESC;

typedef DOS_FAT_DESC *  DOS_FAT_DESC_ID;

/*
 * "Secret" third argument passed from chkdsk into internal readDir
 * operations.  The chkdsk code tells us whether to repair bad file
 * names, and we tell it how many bad names were encountered (and
 * repaired if "repair" is TRUE).  We also fill in a file descriptor
 * with info about the file, since it is right there in the dir.
 *
 * (Thus, repair is an input, badNames is an output, and *pFd is an
 * output.)
 */
typedef struct CHK_DSK_READDIR_EXTRA
    {
    DOS_FILE_DESC_ID    pFd;        /* file descriptor for just-read file */
    BOOL                repair;     /* flag: fix/remove bad names */
    uint32_t            badNames;   /* count of bad-names encountered */
    } CHK_DSK_READDIR_EXTRA;

/*
 * Directory handler descriptor.
 * This structure defines generic directory handler API.
 * It must be start field in every directory handler
 * descriptor structure.
 */
typedef struct DOS_DIR_DESC
    {
    STATUS (*pathLkup)(DOS_FILE_DESC_ID pFd, void * pPath,
                       u_int fflags, u_int fmode);
                        /* lkup path file in directory hierarchy tree */
    STATUS (*readDir)(DOS_FILE_DESC_ID pFd, DIR * pDir,
                      CHK_DSK_READDIR_EXTRA * pExtra);
                        /* regular readdir; <pExtra> if not NULL, is */
                        /* extra information for chkdsk. */
                        /* on return <pdir->dd_cookie> should contain */
                        /* POS_TO_DD_COOKIE( pFd->pos ) */
    STATUS (*updateEntry)(DOS_FILE_DESC_ID pFd, u_int flags,
                          time_t curTime);
                        /* set directory entry values; */
                        /* size, start cluster, attributes and so on */
                        /* are delivered from file descriptor */
                        /* <flags> can be or-ed of */
                        /* DH_TIME_CREAT, DH_TIME_MODIFY, DH_TIME_ACCESS */
                        /* to encode <curTime> value into correspondence */
                        /* field or DH_DELETE for to delete the entry */
    STATUS (*dateGet)(DOS_FILE_DESC_ID pFd, struct stat * pStat);
                        /* fill in date-time fields in stat structure */
    STATUS (*volLabel)(DOS_VOLUME_DESC_ID pVolDesc, u_char * label,
                       u_int operation);
                        /* get/set volume label */
                        /* <operation> is one of FIOLABELGET/FIOLABELSET */
    STATUS (*nameChk)(DOS_VOLUME_DESC_ID pVolDesc, u_char * name);
                        /* validate name (intended to check disk) */
    void (*volUnmount)(DOS_VOLUME_DESC_ID pVolDesc);
                        /* free all resources, that were allocated */
                        /* for the volume */
    void (*show)(DOS_VOLUME_DESC_ID pVolDesc);
                        /* display handler specific data */

    /*
     * routines to access the underlying XBD. It may be a direct access, or
     * through the dosFs disk cache.
     */
    STATUS (*rawBytesRW)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        sector_t            startBlock, /* starting block of the transfer */
        off_t               offset,     /* offset into block in bytes */
        addr_t              buffer,     /* address of data buffer */
        size_t              nBytes,     /* number of bytes to transfer */
        u_int               operation   /* DOS_READ/DOS_WRITE/WRITE_THROUGH */
        );

    STATUS (*rawIoctl)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        UINT32              command,
        addr_t              arg
        );

    u_int rootStartSec;                 /* root directory start sector: */
                                        /* some value for FAT12/FAT16; */
                                        /* 0 for FAT32; is filled by dir handler */
    u_int rootNSec;                     /* sectors per root directory */
                                        /* some value for FAT12/FAT16; */
                                        /* 0 for FAT32; is filled by dir handler */
    } DOS_DIR_DESC;

typedef DOS_DIR_DESC *  DOS_DIR_DESC_ID;

/* check disk work structure */

typedef struct CHK_DSK_DESC
    {
    UINT32 *    chkFatMap;      /* clusters usage map */
    DIR         chkDir;         /* readdir buffer */
    dsize_t     chkTotalFSize;  /* total bytes in all files */
    dsize_t     chkTotalBytesInLostChains;
    u_int       nErrors;        /* total number of errors detected */
    UINT32      chkNDirs;       /* total directories */
    UINT32      chkNFiles;      /* total files */
    UINT32      chkNLostChains; /* total lost chains */
    UINT32      chkNFreeClusts; /* total # of free clusters */
    UINT32      chkNBadClusts;  /* total # of bad clusters */
    time_t      chkMaxCreatTime;
    time_t      chkMaxModifTime;
    time_t      chkMaxAccTime;
    BOOL        bufToDisk;      /* FAT copy used as tmp buffer */
    struct stat stat;           /* buffer to accept file statistics */
    u_char      chkPath[CHK_MAX_PATH];  /* buffer for path strings */
    u_char      curPathLev;     /* dynamic counter of path levels */
    char        chkCurPath[CHK_MAX_PATH + 256];
    } CHK_DSK_DESC;

typedef CHK_DSK_DESC * CHK_DSK_DESC_ID;

typedef enum dos_rw             /* DOS_RW direction enum */
    {
    DOS_READ = 0,               /* read */
    DOS_WRITE = 1,              /* copy back write */
    DOS_WRITE_THROUGH = 2       /* write through write */
    } DOS_RW;

#define STATE_NOT_SET           (0 << 0)
#define STATE_IN_READING        (1 << 0)
#define STATE_IN_WRITING        (1 << 1)
#define STATE_IN_FLUSHING       (1 << 2)
#define STATE_IN_FREEING        (1 << 3)

#define DIRTY_TRUE              (1)
#define DIRTY_FALSE             (0)
#define DIRTY_FLUSHING          (-1)

typedef struct dosCacheDesc
    {
    DL_NODE                  lruNode;
    struct dosCacheDesc *    pHashNext;
    spinlockTask_t *         stateSpl;
    int                      state;
    u_int                    blkGrp;
    int                      waitingTsks;
    SEM_ID                   waitingBSem;
    int                      isDirty;
    char *                   data;
    struct bio               bio;
    SEM_ID                   bioBSem;
    int                      invlBlks;
    int                      dirtyBlks;
    FS_SET                   validBmp;
    FS_SET                   dirtyBmp;
    TASK_ID                  taskId;
    struct dosCacheDesc *    flushLink;
    } DOS_CACHE_DESC;

typedef struct DOS_BIO
    {
    struct bio bio;
    SEM_ID syncSemId;       /* semId to pend for RW completion */
    UINT16 bioIndex;        /* Index of this DOS_BIO in the volume's
                             * dosBio array */
    UINT16 nextFreeBioIndex;    /* index of the next available DOS_BIO
                                 * in the volume's dosBio array */
    } DOS_BIO;

typedef struct dosCache
    {
    size_t               size;
    caddr_t              base;
    DL_LIST              lruList;
    DL_LIST              dirtyList;
    DOS_CACHE_DESC **    pDosHashTable;
    u_int                hashTblSize;
    BOOL                 alloc;         /* was cache allocated dinamically? */
    atomic_t             dirtyCount;
    u_int                maxDirtyCount;

    /* cache statistics */

    u_int               count;
    u_int               highCount;
    u_int               numBlocks;
    atomic_t            hits;
    atomic_t            misses;

    u_int               blksOrClstsPerGrp;

    sector_t            startBlk;
    int                 blksPerGrp;
    u_int               (*fp_mapBlksToGrps)
                            (
                            struct dosCache *    pCache,
                            sector_t             startBlk,
                            u_int                numBlks,
                            u_int *              fstGrp,
                            u_int *              offInFstGrp,
                            u_int *              blksInFstGrp,
                            u_int *              lastGrp,
                            u_int *              blksInLastGrp
                            );
    sector_t            (*fp_getFstBlkInGrp)
                            (
                            struct dosCache *    pCache,
                            u_int                blkgrp
                            );

    DOS_CACHE_DESC *    (*fp_cacheGrpFind)
                            (
                            struct dosCache *    pCache,
                            u_int                blkGrp,
                            int                  stateSet
                            );
    DOS_CACHE_DESC *    (*fp_cacheGrpAlloc)
                            (
                            DOS_VOLUME_DESC_ID   pVolDesc,
                            DOS_CACHE_TYPE       cacheType,
                            u_int                blkGrp,
                            BOOL                 readData,
                            int                  stateSet
                            );
    void                (*fp_cacheGrpFree)
                            (
                            struct dosCache *    pCache,
                            DOS_CACHE_DESC *     pDesc
                            );

    spinlockTask_t *    hashSpl;
    SEM_ID              cacheAllocMtx;
    DOS_CACHE_DESC *    cacheAllocStart;
    SEM_ID              bunchFlushBSem;
    atomic_t            bunchFlushCnt;
    int                 bunchFlushSts;
#if     1                               /* XXX */
    u_int               startSecToAdj;
    u_int               numSecToAdj;
#endif
    } DOS_CACHE;

#define VOL_MEM_NUM     1

typedef struct vol_Mem
    {
    caddr_t             volMemBase;
    size_t              volMemSize;
    sector_t            volMemBlkNo;
    BOOL                volMemDirty;
    } VOL_MEM;

typedef enum {FAT12, FAT16, FAT32} FAT_TYPE;

/* Volume descriptor */

typedef struct DOS_VOLUME_DESC
    {
    DEV_HDR         devHdr;             /* i/o system device header */
    u_int           magic;              /* control magic number */
                                        /* DOS_FS_MAGIC */
    BOOL            mounted;            /* volume mounted */
    device_t        device;             /* underlying device handle */
    DOS_DIR_DESC_ID pDirDesc;           /* directory handler descriptor ptr */
    DOS_FAT_DESC_ID pFatDesc;           /* FAT handler descriptor ptr */
    SEM_ID          devSem;             /* device mutual semaphore, */
    SEM_ID          shortSem;           /* protect very short operations, */
                                        /* such as allocation of file */
                                        /* descriptor */
    DOS_FILE_DESC_ID pFdList;           /* file descriptors array */
    DOS_FILE_HDL_ID pFhdlList;          /* file handles array */
    SEM_ID *        pFsemList;          /* file semaphores array */

    /* -- boot sector data -- */

    u_int       bootSecNum;             /* number of sector containing boot */
                                        /* information */
    UINT32      volId;                  /* volume Id */
    UINT32      secPerFat;              /* sectors per FAT copy */
    UINT32      nHiddenSecs;            /* hiden sectors (unused tail) */
    UINT32      totalSec;               /* total number of sectors */
    UINT16      bytesPerSec;
    UINT16      secPerClust;
    UINT16      nReservedSecs;          /* reserved sectors (ahead first fat copy) */
    UINT8       nFats;                  /* number of FAT copies */
    UINT32      nFatEnts;               /* number of entries in FAT */
    char        bootVolLab[DOS_VOL_LABEL_LEN + 1];  /* volume label */

    /*     --    --       */

    FAT_TYPE    fatType;

    u_int       dataStartSec;           /* sector number of the start */
                                        /* cluster (DOS_MIN_CLUCT) */
    u_short     maxFiles;               /* maximum open files in a time */
    u_short     nBusyFd;                /* number of fd-s in use */
    u_short     volIdOff;               /* offset of volume Id field */
                                        /* in boot sector */
    u_short     volLabOff;              /* offset of volume label field */
                                        /* in boot sector */
    u_char      secSizeShift;           /* log2( bytesPerSect ) */

    /* check disk fields */

    CHK_DSK_DESC_ID pChkDesc;
    u_char      autoChk;                /* autocheck on mount level */
    u_char      autoChkVerb;            /* autocheck verbosity */
    u_char      chkFlags;               /* check disk flags */
    u_char      chkVerbLevel;           /* check disk verbosity level */

    FUNCPTR     fatVolMount;            /* XXX not used?? */

    /* these fields should probably be combined into generic "flags" word */

    BOOL        updateLastAccessDate;   /* SPR#68203 */
    BOOL        volIsCaseSens;          /* Make SPR#29751 fix switchable */
    UINT32      volWriteOpt;            /* 0 = copyback
                                         * DOS_WRITE_THROUGH_FAT
                                         * DOS_WRITE_THROUGH_DIR
                                         * DOS_WRITE_THROUGH_USR
                                         * DOS_WRITE_THROUGH_ALL
                                         */

    BOOL        volUnicode;             /* use Unicode (UTF-16) file names */
    BOOL        doSecDiscard;           /* device wants discard ioctls */
    BOOL        volWarned16;            /* flag once about UTF-16 high bytes */
    BOOL        volNoDuplicateFat;      /* TRUE to disable FAT copies */

    void (*mountActivate)               /* final callback to "activate" mount */
        (
        struct DOS_VOLUME_DESC *
        );

    STATUS (*dataBytesRW)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        sector_t            startBlock, /* starting block of the transfer */
        off_t               offset,     /* offset into block in bytes */
        addr_t              buffer,     /* address of data buffer */
        size_t              nBytes,     /* number of bytes to transfer */
        u_int               operation   /* DOS_READ/DOS_WRITE/WRITE_THROUGH */
        );

    STATUS (*dataBlkWrite)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        sector_t            startBlock, /* starting block of write */
        sector_t            numBlocks,  /* number of blocks to write */
        addr_t              buffer,     /* address of the memory buffer */
        DOS_RW              operation   /* DOS_WRITE/DOS_WRITE_THROUGH */
        );

    STATUS (*dataBlkRead)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        sector_t            startBlock, /* starting block to read */
        sector_t            numBlocks,  /* number of blocks to read */
        addr_t              buffer      /* address of the memory buffer */
        );

    STATUS (*dataIoctl)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,
        UINT32              command,
        addr_t              arg
        );

    STATUS (*fatBlkRead)
        (
        DOS_VOLUME_DESC_ID  pVolDesc,   /* volume descriptor */
        sector_t            startBlock, /* starting block to read */
        sector_t            numBlocks,  /* number of blocks to read */
        addr_t              buffer      /* address of the memory buffer */
        );
    /* cache management */

    DOS_CACHE   cache[DOS_NUM_CACHE];
    u_int       volOptions;     /* Is media DMA capable? */

    /* fields for managing the tiny cache used during byte RW */

    SEM_ID      volMemSemId;
    VOL_MEM     volMem[VOL_MEM_NUM];
    int         volMemLastHit;  /*volume memory no. for last hit.*/
    u_long      volMemAccess;   /*counter for volume memory access*/
    u_long      volMemHits;     /*counter for volume memory hit*/

    /* Bio management */

    sector_t    nBlocks;        /* underlying XBD device num of blocks */
    uint32_t /* unsigned */ blockSize;  /* underlying XBD device block size */
    SEM_ID      volBioCount;    /* counting semaphore for getting bios */
    SEM_ID      volBioLock;     /* for mutual exclusion accessing this
                                 * volume bio array */
    UINT16      nextFreeBio;
    DOS_BIO     dosBioArray [DOS_VOLUME_BIO_SIZE]; /* may be of variable size
                                                    * in the near future XXX */
    BOOL        readOnly;

    TASK_ID     flushTskId;
    SEM_ID      flushTskBSem;
    SECTOR_RANGE rangeDiscard;   /* range for discard to low level driver */
    SEM_ID       discardSem;     /* use for protect discard */
    BOOL mounting;
    } DOS_VOLUME_DESC;

typedef struct DOS_HDLR_DESC
    {
    u_int   id; /* unique handler Id */
            /* 0 - 256 reserved by implementation */
    STATUS (*mountRtn)( DOS_VOLUME_DESC_ID pVolDesc, void * arg );
    void *  arg;    /* handler dependent argument */
    }   DOS_HDLR_DESC;

typedef DOS_HDLR_DESC * DOS_HDLR_DESC_ID;


/* function pointer to chk handler */
/* check disk routine */
IMPORT STATUS (*dosFsChkRtn)( DOS_FILE_DESC_ID pFd );

/* handler lists for fat and dir handlers */
IMPORT DOS_HDLR_DESC    dosFatHdlrsList[];
IMPORT DOS_HDLR_DESC    dosDirHdlrsList[];

/* forward declarations */

IMPORT STATUS dosFsHdlrInstall( DOS_HDLR_DESC_ID hdlrsList,
                    DOS_HDLR_DESC_ID hdlr );

IMPORT int dosFsVolIsFat12 (u_char * pBootBuf); /* pick fat12 or fat16 */

IMPORT int dosPathParse (u_char *path, PATH_ARRAY *pArray, size_t sizeArray);

IMPORT STATUS dosFsXbdBlkWrite (DOS_VOLUME_DESC * pVolDesc, sector_t startBlock,
                                sector_t numBlocks, addr_t buffer,
                                DOS_RW operation);
IMPORT STATUS dosFsXbdBlkRead (DOS_VOLUME_DESC * pVolDesc, sector_t startBlock,
                               sector_t numBlocks, addr_t buffer);
IMPORT STATUS dosFsXbdBlkCopy (DOS_VOLUME_DESC * pVolDesc, sector_t srcBlock,
                               sector_t dstBlock, sector_t numBlocks);
IMPORT STATUS dosFsXbdBytesRW (DOS_VOLUME_DESC * pVolDesc, sector_t startBlock,
                   off_t offset, addr_t buffer, size_t nBytes,
                               u_int operation);
IMPORT STATUS dosFsXbdIoctl (DOS_VOLUME_DESC * pVolDesc, UINT32 command,
                             addr_t arg);

IMPORT int dosFsDiscard(DOS_VOLUME_DESC * pVolDesc, SECTOR_RANGE * range,
                       BOOL flush);

IMPORT void dosfsHostToDisk32 (uint32_t src, uint8_t * pDest);
IMPORT void dosfsHostToDisk16 (uint16_t src, uint8_t * pDest);
IMPORT uint32_t dosfsDiskToHost32 (uint8_t * pSrc);
IMPORT uint16_t dosfsDiskToHost16 (uint8_t * pSrc);

IMPORT void (*_func_dosDirOldShow) (DOS_VOLUME_DESC_ID pVolDesc);
IMPORT void (*_func_dosVDirShow) (DOS_VOLUME_DESC_ID pVolDesc);
IMPORT void (*_func_dosFsFatShow) (DOS_VOLUME_DESC_ID pVolDesc);
IMPORT void (*_func_dosChkStatPrint) (DOS_FILE_DESC_ID pFd);

IMPORT STATUS dosVDirLibUptDotDot(DOS_FILE_DESC_ID pOldFd, DOS_FILE_DESC_ID pNewFd);
#ifdef __cplusplus
    }
#endif

#endif /* __INCdoFsLibP */

