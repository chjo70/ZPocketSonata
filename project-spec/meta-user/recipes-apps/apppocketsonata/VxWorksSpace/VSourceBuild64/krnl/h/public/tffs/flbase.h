/* flbase.h - True Flash File System */

/*
 * Copyright (c) 1984-2005, 2009-2010, 2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/* FAT-FTL Lite Software Development Kit
 * Copyright (C) M-Systems Ltd. 1995-1997	*/

/*
modification history
--------------------
21nov16,ffu  add LP64 support in TFFS layer (F4496)
24sep13,jxu  fixed crc16 symbol conflict with btstack component
07may13,jxu  eTFFS: added declaration of crc16() and dbgMsg
10dec12,xwu  Coverity issue of tffs.
21sep10,jxu  Cleanup of warning: added UNAL4_ARG_TYPE for type casting. 
29jul10,pad  Moved extern C statement after include statements.
11dec09,zly  fix defect190947: added erroe codes for TFFS 
23sep09,zly  make checkStatus()`s logmsg controlled.
             default no logmsg.
02feb05,aeg  added include of logLib.h (SPR #106381).
16nov04,mil  removed deprecated __FUNCTION__ for GNU.
29jul04,alr  modified file header, restarted history
*/

#ifndef FLBASE_H
#define FLBASE_H

#include "flsystem.h"
#include "flcustom.h"
#include "logLib.h"

#ifdef __cplusplus
extern "C" {
#endif

/* control logmsg in checkStatus()*/
#undef DEBUG_CHECKSTATUS

/* standard type definitions */
typedef int 		FLBoolean;

/* Boolean constants */

#ifndef FALSE
#define FALSE	0
#endif
#ifndef TRUE
#define	TRUE	1
#endif

#ifndef TFFS_ON
#define	TFFS_ON		1
#endif
#ifndef TFFS_OFF
#define	TFFS_OFF	0
#endif

#define SECTOR_SIZE		(1 << SECTOR_SIZE_BITS)

/* define SectorNo range according to media maximum size */
#if (MAX_VOLUME_MBYTES * 0x100000l) / SECTOR_SIZE > 0x10000l
typedef unsigned int SectorNo;
#define	UNASSIGNED_SECTOR 0xffffffffl
#else
typedef unsigned short SectorNo;
#define UNASSIGNED_SECTOR 0xffff
#endif

#if FAR_LEVEL > 0
  #define FAR0	far
#else
  #define FAR0
#endif

#if FAR_LEVEL > 1
  #define FAR1	far
#else
  #define FAR1
#endif

#if FAR_LEVEL > 2
  #define FAR2	far
#else
  #define FAR2
#endif


#define vol (*pVol)


#ifndef TFFS_BIG_ENDIAN

typedef unsigned short LEushort;
typedef unsigned int LEulong;

#define LE2(arg)	arg
#define	toLE2(to,arg)	(to) = ((LEushort)(arg))
#define LE4(arg)	arg
#define	toLE4(to,arg)	(to) = (arg)
#define COPY2(to,arg)	(to) = (arg)
#define COPY4(to,arg)	(to) = (arg)

typedef unsigned char Unaligned[2];
typedef Unaligned Unaligned4[2];
typedef Unaligned const FAR0 *  UNAL4_ARG_TYPE;	
			    /* for type casting when using UNAL4*/

#define UNAL2(arg)	fromUNAL(arg)
#define toUNAL2(to,arg)	toUNAL(to,arg)

#define UNAL4(arg)	fromUNALLONG(arg)
#define toUNAL4(to,arg)	toUNALLONG(to,arg)

extern void toUNAL(unsigned char FAR0 *unal, unsigned n);

extern unsigned short fromUNAL(unsigned char const FAR0 *unal);

extern void toUNALLONG(Unaligned FAR0 *unal, unsigned int n);

extern unsigned int fromUNALLONG(Unaligned const FAR0 *unal);

#else

typedef unsigned char LEushort[2];
typedef unsigned char LEulong[4];
typedef unsigned char const FAR0 *      UNAL4_ARG_TYPE;
			    /* for type casting when using UNAL4*/

#define LE2(arg)	fromLEushort(arg)
#define	toLE2(to,arg)	toLEushort(to,(unsigned)(arg))
#define LE4(arg)	fromLEulong(arg)
#define	toLE4(to,arg)	toLEulong(to,arg)
#define COPY2(to,arg)	copyShort(to,arg)
#define COPY4(to,arg)	copyLong(to,arg)

#define	Unaligned	LEushort
#define	Unaligned4	LEulong

extern void toLEushort(unsigned char FAR0 *le, unsigned n);

extern unsigned short fromLEushort(unsigned char const FAR0 *le);

extern void toLEulong(unsigned char FAR0 *le, unsigned int n);

extern unsigned int fromLEulong(unsigned char const FAR0 *le);

extern void copyShort(unsigned char FAR0 *to,
		      unsigned char const FAR0 *from);

extern void copyLong(unsigned char FAR0 *to,
		     unsigned char const FAR0 *from);

#define	UNAL2		LE2
#define	toUNAL2		toLE2

#define	UNAL4		LE4
#define	toUNAL4		toLE4

#endif /* TFFS_BIG_ENDIAN */

/* error codes*/

#define S_tffsLib_BAD_FUNCTION        (M_tffsLib | 1)
#define S_tffsLib_FILE_NOT_FOUND      (M_tffsLib | 2)
#define S_tffsLib_PATH_NOT_FOUND      (M_tffsLib | 3)
#define S_tffsLib_TOO_MANY_OPEN_FILES (M_tffsLib |4)
#define S_tffsLib_NO_WRITE_ACCESS     (M_tffsLib | 5)
#define S_tffsLib_BAD_FILE_HANDLE     (M_tffsLib | 6)
#define S_tffsLib_DRIVE_NOT_AVAILABLE (M_tffsLib | 9)
#define S_tffsLib_NON_FAT_FORMAT      (M_tffsLib | 10)
#define S_tffsLib_FORMAT_NOT_SUPPORTED (M_tffsLib | 11)
#define S_tffsLib_NO_MORE_FILES       (M_tffsLib | 18)
#define S_tffsLib_WRITE_PROTECT       (M_tffsLib | 19)
#define S_tffsLib_BAD_DRIVE_HANDLE    (M_tffsLib | 20)
#define S_tffsLib_DRIVE_NOT_READY     (M_tffsLib | 21)
#define S_tffsLib_UNKNOWN_CMD         (M_tffsLib | 22)
#define S_tffsLib_BAD_FORMAT          (M_tffsLib | 23)
#define S_tffsLib_BAD_LENGTH          (M_tffsLib | 24)
#define S_tffsLib_DATA_ERROR          (M_tffsLib | 25)
#define S_tffsLib_UNKNOWN_MEDIA       (M_tffsLib | 26)
#define S_tffsLib_SECTOR_NOT_FOUND    (M_tffsLib | 27)
#define S_tffsLib_OUT_OF_PAPER        (M_tffsLib | 28)
#define S_tffsLib_WRITE_FAULT         (M_tffsLib | 29)
#define S_tffsLib_READ_FAULT          (M_tffsLib | 30)
#define S_tffsLib_GENERAL_FAILURE     (M_tffsLib | 31)
#define S_tffsLib_DISK_CHANGE         (M_tffsLib | 34)
#define S_tffsLib_VPP_FAILURE         (M_tffsLib | 50)
#define S_tffsLib_BAD_PARAMETER       (M_tffsLib | 51)
#define S_tffsLib_NO_SPACE_IN_VOLUME  (M_tffsLib | 52)
#define S_tffsLib_INVALID_FAT_CHAIN   (M_tffsLib | 53)
#define S_tffsLib_ROOT_DIR_FULL       (M_tffsLib | 54)
#define S_tffsLib_NOT_MOUNTED         (M_tffsLib | 55)
#define S_tffsLib_PATH_IS_ROOTDIR     (M_tffsLib | 56)
#define S_tffsLib_NOT_A_DIR           (M_tffsLib | 57)
#define S_tffsLib_DIR_NOT_EMPTY       (M_tffsLib | 58)
#define S_tffsLib_FILE_IS_A_DIR       (M_tffsLib | 59)
#define S_tffsLib_ADAPTER_NOT_FOUND   (M_tffsLib | 60)
#define S_tffsLib_FORMATTING_ERROR    (M_tffsLib | 62)
#define S_tffsLib_NOT_ENOUGH_MEMORY   (M_tffsLib | 63)
#define S_tffsLib_VOLUME_TOO_SMALL    (M_tffsLib | 64)
#define S_tffsLib_BUFFERING_ERROR     (M_tffsLib | 65)
#define S_tffsLib_FILE_ALREADY_EXISTS (M_tffsLib | 80)
#define S_tffsLib_INCOMPLETE          (M_tffsLib | 100)
#define S_tffsLib_TIMED_OUT           (M_tffsLib | 101)
#define S_tffsLib_TOO_MANY_COMPONENTS (M_tffsLib | 102)

#ifdef __cplusplus
}
#endif

#ifndef IFLITE_ERROR_CODES

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {flOK 		= 0,	/* Status code for operation.
					   A zero value indicates success,
					   other codes are the extended
					   DOS codes. */
	     flBadFunction	= 1,
	     flFileNotFound	= 2,
	     flPathNotFound	= 3,
	     flTooManyOpenFiles = 4,
	     flNoWriteAccess	= 5,
	     flBadFileHandle	= 6,
	     flDriveNotAvailable = 9,
	     flNonFATformat	= 10,
	     flFormatNotSupported = 11,
	     flNoMoreFiles	= 18,
	     flWriteProtect 	= 19,
	     flBadDriveHandle	= 20,
	     flDriveNotReady 	= 21,
	     flUnknownCmd 	= 22,
	     flBadFormat	= 23,
	     flBadLength	= 24,
	     flDataError	= 25,
	     flUnknownMedia 	= 26,
	     flSectorNotFound 	= 27,
	     flOutOfPaper 	= 28,
	     flWriteFault 	= 29,
	     flReadFault	= 30,
	     flGeneralFailure 	= 31,
	     flDiskChange 	= 34,
	     flVppFailure	= 50,
	     flBadParameter	= 51,
	     flNoSpaceInVolume	= 52,
	     flInvalidFATchain	= 53,
	     flRootDirectoryFull = 54,
	     flNotMounted	= 55,
	     flPathIsRootDirectory = 56,
	     flNotADirectory	= 57,
	     flDirectoryNotEmpty = 58,
	     flFileIsADirectory	= 59,
	     flAdapterNotFound	= 60,
	     flFormattingError	= 62,
	     flNotEnoughMemory	= 63,
	     flVolumeTooSmall	= 64,
	     flBufferingError	= 65,
	     flFileAlreadyExists = 80,

	     flIncomplete	= 100,
	     flTimedOut		= 101,
	     flTooManyComponents = 102
	     } FLStatus;
#else /* IFLITE_ERROR_CODES */

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {flOK 		= ERR_NONE,
					/* Status code for operation.
					   A zero value indicates success,
					   other codes are the extended
					   DOS codes. */
	     flBadFunction	= ERR_SW_HW,
	     flFileNotFound	= ERR_NOTEXISTS,
	     flPathNotFound	= ERR_NOTEXISTS,
	     flTooManyOpenFiles	= ERR_MAX_FILES,
	     flNoWriteAccess	= ERR_WRITE,
	     flBadFileHandle	= ERR_NOTOPEN,
	     flDriveNotAvailable = ERR_SW_HW,
	     flNonFATformat	= ERR_PARTITION,
	     flFormatNotSupported = ERR_PARTITION,
	     flNoMoreFiles	= ERR_NOTEXISTS,
	     flWriteProtect 	= ERR_WRITE,
	     flBadDriveHandle	= ERR_SW_HW,
	     flDriveNotReady 	= ERR_PARTITION,
	     flUnknownCmd 	= ERR_PARAM,
	     flBadFormat	= ERR_PARTITION,
	     flBadLength	= ERR_SW_HW,
	     flDataError	= ERR_READ,
	     flUnknownMedia 	= ERR_PARTITION,
	     flSectorNotFound 	= ERR_READ,
	     flOutOfPaper 	= ERR_SW_HW,
	     flWriteFault 	= ERR_WRITE,
	     flReadFault	= ERR_READ,
	     flGeneralFailure 	= ERR_SW_HW,
	     flDiskChange 	= ERR_PARTITION,
	     flVppFailure	= ERR_WRITE,
	     flBadParameter	= ERR_PARAM,
	     flNoSpaceInVolume	= ERR_SPACE,
	     flInvalidFATchain	= ERR_PARTITION,
	     flRootDirectoryFull = ERR_DIRECTORY,
	     flNotMounted	= ERR_PARTITION,
	     flPathIsRootDirectory = ERR_DIRECTORY,
	     flNotADirectory	= ERR_DIRECTORY,
	     flDirectoryNotEmpty = ERR_NOT_EMPTY,
	     flFileIsADirectory	= ERR_DIRECTORY,
	     flAdapterNotFound	= ERR_DETECT,
	     flFormattingError	= ERR_FORMAT,
	     flNotEnoughMemory	= ERR_SW_HW,
	     flVolumeTooSmall	= ERR_FORMAT,
	     flBufferingError	= ERR_SW_HW,
	     flFileAlreadyExists = ERR_EXISTS,

	     flIncomplete	= ERR_DETECT,
	     flTimedOut		= ERR_SW_HW,
	     flTooManyComponents = ERR_PARAM
	     } FLStatus;
#endif /* IFLITE_ERROR_CODES */

/* call a procedure returning status and fail if it fails. This works only in
   routines that return Status */

#ifdef DEBUG_CHECKSTATUS
#define checkStatus(exp)      {	FLStatus status = (exp); \
				if (status != flOK){ \
					logMsg("checkStatus() ERROR line %i\n",__LINE__,2,3,4,5,6);	 \
				  return status; } }
#else
#define checkStatus(exp)      { FLStatus status = (exp); \
                if (status != flOK){ \
                  return status; } }
#endif

/* better debug routines.  EAN */

#define DBG_MUST        0x1	/* always print */
#define DBG_FATAL       0x2     /* fatal error */
#define DBG_ERROR       0x4     /* normal error */
#define DBG_WARNING     0x8     /* warning */
#define DBG_FLOW        0x10     /* monitor where i am */

#define DEBUG_MASK 	(DBG_MUST | DBG_FATAL | DBG_ERROR | DBG_WARNING) 
					/* set debug level */

/* #define DEBUG_FTL */       /* turn on/off debug messages */

#ifdef DEBUG_FTL

/* sjk changed printf to logMsg */

#define dbgMsg(num,msg,var1,var2,var3,var4,var5,var6) do {      \
            if(num & DEBUG_MASK)                                \
                logMsg("%s:%d: "msg,            \
                (_Vx_usr_arg_t)__FUNCTION__,    \
                (_Vx_usr_arg_t)__LINE__,        \
                (_Vx_usr_arg_t)var1,            \
                (_Vx_usr_arg_t)var2,            \
                (_Vx_usr_arg_t)var3,            \
                (_Vx_usr_arg_t)var4);           \
        }while(0)

#else

#define dbgMsg(num,msg,var1,var2,var3,var4,var5,var6)   /* nothing */

#endif /* #ifdef DEBUG_FTL */

#define CRC16_SEED      0xFFFF
#define CRC16_GOOD      0xF0B8

unsigned short flCrc16 (unsigned short seed, const unsigned char * pBuf, 
        unsigned int len);

#ifdef __cplusplus
}
#endif

#include "flsysfun.h"

#endif /* FLBASE_H */
