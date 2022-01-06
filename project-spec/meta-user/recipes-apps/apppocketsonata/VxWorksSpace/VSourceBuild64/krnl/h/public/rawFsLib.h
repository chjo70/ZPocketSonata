/* rawFsLib.h - header for raw block device file system library */

/*
 * Copyright 1984 - 2008, 2010, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jul17,ghs  integrate file system type magic number (F9150)
22apr16,yjl  dosFsVolFormat() in usrAppInit() sometimes fails. (V7STO-619)
29apr10,pad  Moved extern C statement after include statements.
21nov08,hps  fix defect WIND00141563: Rawfs does not check validity
             of file descriptor pointers
25aug05,jlk  Added S_rawFsLib_WRITE_ONLY errno.
09feb05,rfr  Modified to use the XBD interface.
30apr02,jkf  SPR#75255, corrected unneeded API change.
20sep01,jkf  SPR#69031, common code for both AE & 5.x.
29feb00,jkf  T3 cleanup
30dec99,jkf  rawFsDevInit() changed from void* to CBIO_DEV_ID
31jul99,jkf  changes for CBIO API.
31jul99,jkf  T2 merge, tidiness & spelling.
15oct98,lrn  moved 64-bit extended ioctl codes to ioLib.h
08oct98,vld  added definition of RAWFS_DEF_MAX_FILES
08oct98,vld  driver interface changed to CBIO_DEV.
 		     replaced rawvd_pBlkDev with CBIO_DEV * rawVdCbio
    	     changed prototype of rawFsDevInit().
23jul98,vld  added ioctl codes for 64-bit ioctl requests; new error codes.
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
		     -changed VOID to void
		     -changed copyright notice
05oct90,shl  added ANSI function prototypes.
             added copyright notice.
02oct90,kdl  written
*/

#ifndef __INCrawFsLibh
#define __INCrawFsLibh

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

/* rawFsLib Status Codes */

#define S_rawFsLib_VOLUME_NOT_AVAILABLE		(M_rawFsLib | 1)
#define S_rawFsLib_END_OF_DEVICE		(M_rawFsLib | 2)
#define S_rawFsLib_NO_FREE_FILE_DESCRIPTORS	(M_rawFsLib | 3)
#define S_rawFsLib_INVALID_NUMBER_OF_BYTES	(M_rawFsLib | 4)
#define S_rawFsLib_ILLEGAL_NAME			(M_rawFsLib | 5)
#define S_rawFsLib_NOT_FILE			(M_rawFsLib | 6)
#define S_rawFsLib_READ_ONLY			(M_rawFsLib | 7)
#define S_rawFsLib_FD_OBSOLETE			(M_rawFsLib | 8)
#define S_rawFsLib_NO_BLOCK_DEVICE		(M_rawFsLib | 9)
#define S_rawFsLib_BAD_SEEK			(M_rawFsLib | 10)
#define S_rawFsLib_INVALID_PARAMETER		(M_rawFsLib | 11)
#define S_rawFsLib_32BIT_OVERFLOW		(M_rawFsLib | 12)
#define S_rawFsLib_WRITE_ONLY			(M_rawFsLib | 13)

#define RAWFS_DEF_MAX_FILES	10	/* default max number of open files */

/* Volume descriptor */

typedef struct		/* RAW_VOL_DESC */
    {
    DEV_HDR	rawVdDevHdr;		/* std. I/O system device header */
    u_int       magic;                  /* RAW_FS_MAGIC */
    int		rawVdStatus;		/* (OK | ERROR) */
    SEM_ID	rawVdSemId;		/* volume descriptor semaphore id */
    device_t	rawVdXbd;		/* Backing block device */
    int		rawVdRetry;		/* current retry count for I/O errors */
    struct bio  rawVdBio;		/* The Block I/O transaction */
    unsigned	rawVdBlkSize;
    sector_t	rawVdNBlocks;
    SEM_ID	rawVdBioSem;		/* The Bio Counting Semaphore */
    BOOL         mounting;
} RAW_VOL_DESC;

/* Volume states */

#define RAW_VD_READY_CHANGED	0	/* vol not accessed since rdy change */
#define RAW_VD_RESET		1	/* volume reset but not mounted */
#define RAW_VD_MOUNTED		2	/* volume mounted */
#define RAW_VD_CANT_RESET	3	/* volume reset failed */
#define RAW_VD_CANT_MOUNT	4	/* volume mount failed */

/* Function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern RAW_VOL_DESC *rawFsDevInit (char *pVolName, device_t xbd);
extern STATUS 	rawFsInit (int maxFiles);
extern STATUS 	rawFsVolUnmount (RAW_VOL_DESC *pVd);

#else	/* __STDC__ */

extern RAW_VOL_DESC *	rawFsDevInit ();
extern STATUS 	rawFsInit ();
extern STATUS 	rawFsVolUnmount ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCrawFsLibh */

