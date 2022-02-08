/* dosFsLib.h - DOS file system header file */

/*
 * Copyright (c) 1999-2006, 2009-2010, 2012-2013,
   2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
14jul16,yjl  Cannot format ram device or NAND flash with DOS_OPT_FAT32=0x20 
             option (V7STO-613)
15mar16,dee  add new enum in DOS_CACHE_TYPE to eliminate 4188 warnings
31dec13,ghs  Modify format routine function type (US29308)
26jun12,zly  Fix WIND00342075: Add new API dosFsVolFormatWithLabel(). 
29jul10,jxu  Add C++ inline wrappers for dosFsVolFormat() and 
             dosFsVolFormatFd() API.
07jun10,jxu  Removed usage of FUNCPTR.
27may10,pad  Moved extern C statement after include statements.
08apr10,sjz  Fix WIND00090292: add const to the prototype of dosFsVolFormat
17mar10,yjl  use different funtion pointer between 32bit and 64bit
04nov09,yjl  change name of dosFsFmtRtn to _func_dosFsFmtRtn
04aug09,yjl  adapt for 64bit
03aug09,hps  group cache with background flush
22jul09,yjl  requirement WIND00142043
26sep08,zly  changed maxRootEnts from M(modifiable) to C(calculated)
03nov06,pcm  added routines to tune DosFS Cache
22aug06,pcm  added dosFsShowInit()
17aug06,kuo  added macro DOS_WRITE_THROUGH_MASK
10apr06,pcm  changed dosFsDevCreate() <dosDevCreateOptions> parameter type
04oct05,dcc  added miselaneous cache routines.
05aug05,dcc  added dosFsCacheLibInit() declaration.
04aug05,jlk  moved formatter function pointer, dosFsFmtRtn, from dosFsLibP.h
03aug05,pcm  changed parameters to dosFsLibInit()
20jun05,dcc  updated formatter API.
25may05,dcc  added cache support.
18may05,dcc  added API to plug into the removability framework.
18apr05,dcc  updated dosFs formatter to work over rawFs.
31jan05,dcc  updated dosFs to use XBD interface.
23sep04,act  back out changes for SPR#90008
03may04,jkf  SPR#90008, adding device deletion routine
27apr04,act  add DOS_FILENAMES_UNICODE option
09apr04,dat  creating dosFsCommon.h
21mar04,act  add DOS_CHK_FORCE and DOS_CHK_FLAGS_MASK for clean bit
02sep03,jkf  rename autoChkLevel to dosDevCreateOptions, more generic.
             added DOS_WRITE_THROUGH_[ALL,FAT,DIR] options.
04mar02,jkf  Adding dosSetVolCaseSens(),SPR#29751, orig by chn.
30nov01,jkf  SPR#68203, adding dosFsLastAccessDateEnable().
14nov01,jkf  SPR#71720, avoiding unaligned pointer accesses.
             added leading underscore to _WRS_PACK_ALIGN ifndef 
11nov01,jkf  added WRS_PACK_ALIGN ifndef for AE 1.1 support, this 
             allows same dosFs2 files to build in AE 1.1 environment.
10nov01,jkf  SPR#32178, made dosFsVolDescGet public
             Added WRS_PACK_ALIGN (2) to legacy struct for MIPS.
21sep01,jkf  SPR#69031, common code for both AE & 5.x.
21sep01,jkf  changed error codes to WRS standard.
29feb00,jkf  T3 changes
31aug99,jkf  changes for new CBIO API.
31jul99,jkf  T2 merge, tidiness & spelling.
15oct98,lrn  moved 64-bit extended ioctl codes to ioLib.h
11sep98,vld  prototype of dosFsDevCreate() to accept arbitrary
	     block device ptr.
09jul98,lrn  added more defines for back compatibility
30jun98,lrn  moved ERRNO_PX_FLAG to errno.h, renamed dosFsInit to
             dosFsLibI added b.c., cosmetics
28jun98,vld  tested and checked in
22jan98,vld  written,
*/

#ifndef __INCdoFsLib
#define __INCdoFsLib

#include <dosFsCommon.h>
#include <drv/manager/device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* dosDevCreateOptions - data and meta data handling options */

/* dosDevCreateOptions - coupled, write through metadata operations */

#define DOS_WRITE_THROUGH_MASK  0x000f0000  /* write through mask */
#define DOS_WRITE_THROUGH_DIR   0x00010000 /* write through dirents */
#define DOS_WRITE_THROUGH_FAT  	0x00020000 /* write through FAT ops */
#define DOS_WRITE_THROUGH_USR  	0x00040000 /* write through user data */
/* dosDevCreateOptions - coupled, immediate write through of all IO */
#define DOS_WRITE_THROUGH_ALL 	0x00080000

/* dosDevCreateOptions - file name format (VxWorks 5.5 style vs UTF16) */

#define	DOS_FILENAMES_UNICODE	0x00100000 /* use Unicode filenames */

#define DOS_DUPLICATE_FAT_DISABLE  0x00200000 /* Disables duplicate FAT's */

/* volume format definitions */

/* data types */
/* Volume configuration data */

typedef struct          /* DOS_VOL_CONFIG */
    {                           /* Legend: M- modifiable, C- Calculated */
    enum
        { _AUTO=0, _FAT12=12, _FAT16=16, _FAT32=32 }
                fatType;        /* M- Fat format Type */
    int         secPerClust;    /* M- sectors per cluster (minimum 1) */
    const char * sysId ;        /* M- sys ID string */
    short       nResrvd;        /* M- number of reserved sectors (min 1) */
    short       maxRootEnts;    /* C- max number of entries in root dir */
    uint32_t    secPerFat;      /* C- number of sectors per FAT copy */
    uint32_t    nClust;         /* C- # of clusters on disk */
    uint32_t    nHidden;        /* C- number of hidden sectors */
    uint32_t    volSerial ;     /* M- disk serial number */
    int         secPerTrack;    /* M- sectors per track */
    char        nFats;          /* M- number of FAT copies (minimum 1) */
    char        nHeads;         /* M- number of heads */
    char        mediaByte;      /* M- media descriptor byte */
    char        volLabel[ DOS_VOL_LABEL_LEN + 1 ]; /* X- disk volume label */
    } DOS_VOL_CONFIG;

typedef enum
    {
    DOS_CACHE_NONE = -1,
    DOS_DATA_DIR_CACHE = 0,
    DOS_FAT_CACHE = 1,
    DOS_NUM_CACHE = 2
    } DOS_CACHE_TYPE;


/* 
 * A DOS_VOLUME_DESC_ID is pointer to DOS_VOLUME_DESC. For details
 * see h/private/dosFsLibP.h.  Note: That is a WRS private header file.
 */ 

typedef struct DOS_VOLUME_DESC *        DOS_VOLUME_DESC_ID;

/* dosFsVolFormat() options: */
#define DOS_OPT_DEFAULT         0x0000  /* format with default options */
#define DOS_OPT_PRESERVE        0x0001  /* preserve boot block if possible */
#define DOS_OPT_BLANK           0x0002  /* create a clean boot block */
#define DOS_OPT_QUIET           0x0004  /* dont produce any output */
#define DOS_OPT_FAT16           0x0010  /* format with FAT16 file system */
#define DOS_OPT_FAT32           0x0020  /* format with FAT32 file system */
#define DOS_OPT_VXLONGNAMES     0x0100  /* format with VxLong file names */
#define DOS_OPT_FSTYPE          0x1000  /* format with file system type, which must 
                                        be set along with DOS_OPT_FAT16 or DOS_OPT_FAT32 */


#define DOS_CACHE_VOL_NO_DMA	0x01   
#define DOS_VOLUME_VOL_NO_DMA	0x01   /* This replaces DOS_CACHE_VOL_NO_DMA */

/* macros */

/* typedefs */
typedef int (*FORMAT_PTR) (DOS_VOL_CONFIG *);

/* interface functions prototypes */

IMPORT STATUS dosFsLibInit (int maxFiles, int options);
IMPORT STATUS dosFsDevCreate ( char * pDevName, device_t device,
			       u_int maxFiles, int dosDevCreateOptions );
IMPORT STATUS dosFsVolUnmount ( void * pDev );
IMPORT STATUS dosFsShow( void * dev, u_int level );

IMPORT STATUS dosFsVolFormat( const char * path, int opt, 
                              FORMAT_PTR func_FormatPrompt);
IMPORT STATUS dosFsVolFormatWithLabel( const char * path, int opt,
                                       const char * labelName,
                                       FORMAT_PTR func_FormatPrompt);

IMPORT STATUS dosFsVolFormatFd ( int fd, int opt, 
                                 FORMAT_PTR func_FormatPrompt);

IMPORT void dosFsFmtLibInit( void );
IMPORT void dosChkLibInit( void );
IMPORT STATUS dosDirOldLibInit( void );
IMPORT STATUS dosVDirLibInit ( void );
IMPORT STATUS dosFsFatInit ( void );
IMPORT DOS_VOLUME_DESC_ID dosFsVolDescGet (void * pDevNameOrPVolDesc, 
                                           u_char **   ppTail);
IMPORT STATUS dosFsLastAccessDateEnable (DOS_VOLUME_DESC_ID dosVolDescId, 
                                         BOOL enable);
IMPORT STATUS dosFsDiskProbe (device_t xbdDevice);
IMPORT STATUS dosFsMonitorDevCreate (device_t xbdId, char * pDevName);
IMPORT STATUS dosFsDevDelete (DOS_VOLUME_DESC_ID pVolDesc);
IMPORT UINT dosFsVolumeOptionsSet (char * volName, UINT options);
IMPORT UINT dosFsVolumeOptionsGet (char * volName);
IMPORT STATUS dosFsCacheCreate (
                               char *     volName, 
                               char *     dataDirCacheAddr, 
                               u_int      dataDirCacheSize,
                               char *     fatCacheAddr,
                               u_int      fatCacheSize
                               );
IMPORT STATUS dosFsCacheDelete (const char * volName);
IMPORT UINT dosFsDefaultDataDirCacheSizeGet (void);
IMPORT UINT dosFsDefaultFatCacheSizeGet (void);
IMPORT void dosFsDefaultCacheSizeSet (
                                     UINT newDataDirDefaultSize,
                                     UINT newFatDefaultSize
                                     );
IMPORT void dosFsCacheLibInit (
                              UINT defaultDataDirCacheSize,
                              UINT defaultFatCacheSize,
                              BOOL backgrndFlushTskEnable
                              );
IMPORT UINT dosFsCacheOptionsSet (char * volName, UINT options);
IMPORT UINT dosFsCacheOptionsGet (char * volName);
IMPORT STATUS dosFsCacheTune (
                             char * volName,
                             UINT clustsPerDataDirCacheGroup,
                             UINT blocksPerFatCacheGroup
                             );

IMPORT STATUS dosFsCacheInfo (char * volName,
                             UINT * pClustsPerDataDirCacheGroup,
                             UINT * pBlocksPerFatCacheGroup
                             );

IMPORT void dosFsCacheShow (const char * volName, u_int level);
IMPORT void dosFsShowInit (void);

IMPORT STATUS dosSetVolCaseSens /* set rename case sens */
    (
    DOS_VOLUME_DESC_ID pVolDesc,
    BOOL sensitivity /* TRUE == case sens */
    );

/* OS Macro's */

#ifndef _WRS_PACK_ALIGN
#    define _WRS_PACK_ALIGN(x) __attribute__((packed, aligned(x)))
#endif /* _WRS_PACK_ALIGN */


#if TRUE /* SPR#71720, avoiding unaligned pointer accesses. */

/* GNU versions of new OS macros */

#ifndef _WRS_ALIGNOF
/*
 * _WRS_ALIGNOF - return the alignment of an item, in bytes
 *
 * Returns the byte alignment for an item.  The returned value
 * is the alignment in units of bytes.
 */

#    define _WRS_ALIGNOF(x) \
            __alignof__(x)

#endif /* ifndef _WRS_ALIGNOF */

#ifndef _WRS_ALIGN_CHECK
/*
 * _WRS_ALIGN_CHECK - test a pointer for a particular alignment
 *
 * Returns TRUE if the pointer is aligned sufficiently to be a 
 * pointer to a specified data type.  Returns FALSE if the pointer
 * value is not aligned to be a valid pointer to the data type.
 */

#    define _WRS_ALIGN_CHECK(ptr, type) \
            (((long)(ptr) & ( _WRS_ALIGNOF(type) - 1)) == 0)

#endif /* ifndef _WRS_ALIGN_CHECK */

#endif /* TRUE/FALSE - SPR#71720, avoiding unaligned pointer accesses. */

#ifdef __cplusplus
    }
/*
 * Inlined C++ wrapper for the old-style FUNCPTR based dosFsVolFormat() and
 * dosFsVolFormatFd() functions prototype.
 */

IMPORT STATUS dosFsVolFormat( const char * path, int opt, 
                  FUNCPTR func_FormatPrompt) \
       _WRS_DEPRECATED ("please use fully qualified function pointer "
                "version of API");
inline STATUS dosFsVolFormat
    (
    const char *    path,       /* path for volume to format */
    int             opt,        /* bit-wise or'ed options */
    FUNCPTR         _func_FormatPrompt
                                /* interactive parameter change callback */
    )
    {
    return dosFsVolFormat(path, opt, (FORMAT_PTR)_func_FormatPrompt);
    }

IMPORT STATUS dosFsVolFormatFd ( int fd, int opt, 
                  FUNCPTR func_FormatPrompt) \
       _WRS_DEPRECATED ("please use fully qualified function pointer "
                "version of API");

inline STATUS dosFsVolFormatFd
    (
    int       fd,      /* rawFs file descriptor */
    int       opt,     /* bit-wise or'ed options */
    FUNCPTR   func_FormatPrompt
                       /* interactive parameter change callback */
    )
    {
    return dosFsVolFormatFd(fd, opt, (FORMAT_PTR)func_FormatPrompt);
    }

#endif

#ifdef	DOS_FS_COMPAT
/* types for backwards compatibility, should be discontinued */
#include <blkIo.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef	void * DOS_VOL_DESC ;

/* DOS_PART_TBL is obsolete: use dpartCbio/usrFdiskPartLib instead */

typedef struct		/* DOS_PART_TBL */
    {
    UINT8		dospt_status;		/* partition status */
    UINT8		dospt_startHead;	/* starting head */
    short		dospt_startSec;		/* starting sector/cylinder */
    UINT8		dospt_type;		    /* partition type */
    UINT8		dospt_endHead;		/* ending head */
    short		dospt_endSec;		/* ending sector/cylinder */
    uint32_t    dospt_absSec;		/* starting absolute sector */
    uint32_t	dospt_nSectors;		/* number of sectors in part */
    } _WRS_PACK_ALIGN (2) DOS_PART_TBL;


/* dosFs Date and Time Structure - should be replaced with ANSI time */
 
typedef struct          /* DOS_DATE_TIME */
    {
    int         dosdt_year;             /* current year */
    int         dosdt_month;            /* current month */
    int         dosdt_day;              /* current day */
    int         dosdt_hour;             /* current hour */
    int         dosdt_minute;           /* current minute */
    int         dosdt_second;           /* current second */
    } DOS_DATE_TIME;

/* old defines */
#define	DOS_BOOT_SYS_ID		0x03	/* system ID string          (8 bytes)*/
#define	DOS_SYS_ID_LEN		8       /* length of system ID string */
#define	DOS_BOOT_PART_TBL	0x1be	/* first disk partition tbl (16 bytes)*/

/* old proprietary long file names, now renamed VXLONGNAMES */
#define DOS_OPT_LONGNAMES       0x4    

/* All other old options are non applicable anymore, defined for compiles */
#define DOS_OPT_CHANGENOWARN    0x1     /* disk may be changed w/out warning */
#define DOS_OPT_AUTOSYNC        0x2     /* autoSync mode enabled */
#define DOS_OPT_EXPORT          0x8     /* file system export enabled */
#define DOS_OPT_LOWERCASE       0x40    /* filenames use lower-case chars */

/* old prototypes */
extern DOS_VOL_DESC *	dosFsDevInit (char *pDevName, BLK_DEV *pBlkDev,
		                      DOS_VOL_CONFIG *pConfig);
extern DOS_VOL_DESC *	dosFsMkfs (char *pVolName, BLK_DEV *pBlkDev);

/* function pointers to fmt handler */
/* format routine */

IMPORT STATUS (*_func_dosFsFmtRtn)(char *path, int opt,
                                   void * func_FormatPrompt); 

#ifdef __cplusplus
    }
#endif

/* end of backward compatibility types */
#endif	/* DOS_FS_COMPAT */

#endif /* __INCdoFsLib */
