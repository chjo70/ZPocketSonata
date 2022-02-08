/* sdLibCommon.h - common shared data library header file */

/* 
 * Copyright (c) 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01m,09nov10,zl   added SD_ID_NULL
01l,28apr10,pad  Moved extern C statement after include statements.
01k,22feb10,jpb  Updated for LP64 adaptation.
01j,24nov04,zl   added text coherency option.
01i,14oct04,gls  added SD_CACHE_COHERENCY and SD_CACHE_GUARDED
01h,11oct04,gls  added include of objLibCommon.h
01g,28sep04,gls  moved sdOpen and sdCreate definitions to sdLib.h
01f,24sep04,gls  SD attribute maintenance
01e,19jul04,gls  added hook add/delete routines (SPR #98361)
01d,06apr04,gls  added support for sdInfoGet()
01c,29mar04,gls  added include of vmLibCommon.h (SPR #95051)
01b,17feb04,gls  cleaned up
01a,23jan04,gls  created based on sdLib.h
*/

#ifndef __INCsdLibCommonh
#define __INCsdLibCommonh

#include <vxWorks.h>
#include <vmLibCommon.h>
#include <objLibCommon.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* errno values */

#define S_sdLib_NOT_IMPLEMENTED                      (M_sdLib |  1)
#define S_sdLib_NAME_NOT_VALID                       (M_sdLib |  2)
#define S_sdLib_VIRT_PAGES_NOT_AVAILABLE             (M_sdLib |  3)
#define S_sdLib_PHYS_PAGES_NOT_AVAILABLE             (M_sdLib |  4)
#define S_sdLib_ARG_LIST_IS_NULL                     (M_sdLib |  5)
#define S_sdLib_VIRT_ADDR_PTR_IS_NULL                (M_sdLib |  6)
#define S_sdLib_SIZE_IS_NULL                         (M_sdLib |  7)
#define S_sdLib_INVALID_OPTIONS                      (M_sdLib |  8)
#define S_sdLib_INVALID_MMU_ATTR                     (M_sdLib |  9)
#define S_sdLib_NOT_MAPPED                           (M_sdLib | 10)
#define S_sdLib_ADDR_NOT_ALIGNED                     (M_sdLib | 11)
#define S_sdLib_CLIENT_COUNT_NOT_NULL                (M_sdLib | 12)
#define S_sdLib_INVALID_SD_ID                        (M_sdLib | 13)
#define S_sdLib_SD_IS_PRIVATE                        (M_sdLib | 14)
#define S_sdLib_PHYS_ADDR_OUT_OF_RANGE               (M_sdLib | 15)

/* defines */

#define VX_SD_NAME_LENGTH      31       /* max name length for diplay */

/* return value for unsuccessful sdOpen() and sdCreate() */

#define SD_ID_NULL	       ((SD_ID) 0)

/* SD_ATTR definitions */

#define SD_ATTR_RW            (MMU_ATTR_SUP_RW | MMU_ATTR_USR_RW | \
                               MMU_ATTR_VALID)

#define SD_ATTR_RO            (MMU_ATTR_SUP_RO | MMU_ATTR_USR_RO | \
                               MMU_ATTR_VALID)

#define SD_ATTR_RWX           (MMU_ATTR_SUP_RWX | MMU_ATTR_USR_RWX | \
                               MMU_ATTR_VALID)

#define SD_ATTR_RX            (MMU_ATTR_SUP_EXE | MMU_ATTR_USR_EXE | \
                               MMU_ATTR_SUP_RO | MMU_ATTR_USR_RO | \
                               MMU_ATTR_VALID)

#define SD_CACHE_COPYBACK     (MMU_ATTR_CACHE_COPYBACK)
#define SD_CACHE_WRITETHROUGH (MMU_ATTR_CACHE_WRITETHRU)
#define SD_CACHE_OFF          (MMU_ATTR_CACHE_OFF)
#define SD_CACHE_DEFAULT      (MMU_ATTR_CACHE_DEFAULT)
#define SD_CACHE_COHERENCY    (MMU_ATTR_CACHE_COHERENCY)
#define SD_CACHE_GUARDED      (MMU_ATTR_CACHE_GUARDED)

/* reserved attributes */

#define SD_CACHE_TEXT_UPDATE   0x80000000

/* Options */

#define	SD_LINGER	0x00000001	/* SD stays after last client exits */
#define	SD_PRIVATE	0x00000002	/* SD is private to an application */

typedef struct sd_desc          /* SD_DESC - information structure */
    {
    char        name[VX_SD_NAME_LENGTH+1]; /* name of SD */
    size_t      size;           /* size of SD */ 
    VIRT_ADDR   startAddr;      /* start address of SD */
    int         options;        /* options, e.g. SD_LINGER, SD_PRIVATE */
    MMU_ATTR    defaultAttr;    /* default attributes of SD */
    MMU_ATTR    currentAttr;    /* current attributes of SD */
    } SD_DESC;

/* typedefs for Shared Data hook functions */

typedef void   (* SD_CREATE_HOOK) (const SD_ID);
typedef void   (* SD_DELETE_HOOK) (const SD_ID);
typedef STATUS (* SD_GENERIC_HOOK) (void *, int);

typedef enum sd_routines {
    SD_HOOK_TYPE_MSK    = 0x00000001,
    SD_HOOK_ID          = 0x00000000,
    SD_HOOK_NAME        = 0x00000001,
    SD_HOOK_ROUTINE_MSK = 0x0000000e,
    SD_HOOK_CREATE      = 0x00000002,
    SD_HOOK_OPEN        = 0x00000004,
    SD_HOOK_DELETE      = 0x00000006,
    SD_HOOK_MAP         = 0x00000008,
    SD_HOOK_UNMAP       = 0x0000000a,
    SD_HOOK_PROTECT     = 0x0000000c
} SD_HOOK_OPTIONS;  

/* functional API to the library */

STATUS		sdDelete	(SD_ID		sdId,
				 int 		options);

VIRT_ADDR	sdMap		(SD_ID		sdId,
				 MMU_ATTR	attr,
				 int		options);

STATUS		sdUnmap		(SD_ID		sdId,
				 int		options);

STATUS		sdProtect	(SD_ID		sdId,
				 MMU_ATTR	attr);

STATUS		sdInfoGet	(SD_ID		sdId,
				 SD_DESC *      pSdStruct);

STATUS		sdCreateHookAdd	    (SD_CREATE_HOOK sdCreateHook,
				     BOOL           addToHead);

STATUS		sdCreateHookDelete  (SD_CREATE_HOOK sdCreateHook);

STATUS		sdDeleteHookAdd	    (SD_DELETE_HOOK sdDeleteHook,
				     BOOL           addToHead);

STATUS		sdDeleteHookDelete  (SD_DELETE_HOOK sdDeleteHook);

STATUS		sdGenericHookAdd    (SD_GENERIC_HOOK sdGenericHook,
				     BOOL            addToHead);

STATUS		sdGenericHookDelete (SD_GENERIC_HOOK sdGenericHook);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* __INCsdLibCommonh */
