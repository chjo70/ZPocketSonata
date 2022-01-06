/* ftlUtilP.h - generic ftl utility private header */

/*
 * Copyright (c) 2012-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,txu  fix V7STO-358 : wrong include after extern "C"
04sep13,jxu  adapted path of includes for vx7 
04sep13,jxu  turned off debug. 
20jun13,jxu  supported finer control over the debug log 
30nov12,jxu  added endian conversion macros.
10aug12,jxu  written.
*/

#ifndef __INCftlUtilPh
#define __INCftlUtilPh


/* includes */

#include <private/ftlOsIf.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* defines */

/* 
 * as a convention, ftl saves data on flash in little endian order becuase
 * the first platform it get ready to run is little endian.
 */

#define SWAP16(var16)   ((((var16) & 0x00FF) << 8) | \
                        (((var16) & 0xFF00) >> 8))
#define SWAP32(var32)   ((SWAP16((var32) & 0x0000FFFF) << 16) | \
                         (SWAP16(((var32) & 0xFFFF0000) >> 16)))
#define SWAP64(var64)   ((SWAP32((var64) & 0x00000000FFFFFFFF) << 32) | \
                         (SWAP32(((var64) & 0xFFFFFFFF00000000) >> 32)))
#if _BYTE_ORDER ==_LITTLE_ENDIAN
#define FTL_TO_FLASH_LE16(var)  (var)   /* nothing to do */
#define FTL_TO_FLASH_LE32(var)  (var)   /* nothing to do */
#define FTL_TO_FLASH_LE64(var)  (var)   /* nothing to do */
#define FLASH_LE16_TO_FTL(var)  (var)   /* nothing to do */
#define FLASH_LE32_TO_FTL(var)  (var)   /* nothing to do */
#define FLASH_LE64_TO_FTL(var)  (var)   /* nothing to do */
#else
#define FTL_TO_FLASH_LE16(var)  SWAP16(var)
#define FTL_TO_FLASH_LE32(var)  SWAP32(var)
#define FTL_TO_FLASH_LE64(var)  SWAP64(var)
#define FLASH_LE16_TO_FTL(var)  SWAP16(var)
#define FLASH_LE32_TO_FTL(var)  SWAP32(var)
#define FLASH_LE64_TO_FTL(var)  SWAP64(var)
#endif /* #if _BYTE_ORDER ==_LITTLE_ENDIAN */

#define FTL16(var) FLASH_LE16_TO_FTL(var)
#define FTL32(var) FLASH_LE32_TO_FTL(var)
#define FTL64(var) FLASH_LE64_TO_FTL(var)
#define FLASH16(var) FTL_TO_FLASH_LE16(var)
#define FLASH32(var) FTL_TO_FLASH_LE32(var)
#define FLASH64(var) FTL_TO_FLASH_LE64(var)

/* CRC */

#define FTL_INITIAL_CRC32       0xffffffff  /* Initial 32 bit FCS value */
#define FTL_GOOD_CRC32          0xdebb20e3  /* Good final 32 bit FCS value */

/* fbio bitmap related helper definitions */

#define BPB             8       /* bits per byte */
#define BMP_SHIFT       3       /* shift of a byte */
#define BMP_MASK        ((BPB)- 1)

#ifdef notyet
#define RAW_TO_FTL_ADDR(addr64, ftlAddr) do {           \
        ftlAddr.offset = (addr64) & 0xFFFF;             \
        ftlAddr.pageno = ((addr64) >> 16) & 0xFFFF;     \
        ftlAddr.blkNo  = ((addr64) >> 32 & 0xFFFFFFFF); \
        }while(0)
#define FTL_TO_RAW_ADDR(addr64, ftlAddr) do {           \
        addr64 = (ftlAddr.offset & 0xFFFF) |            \
                 ((ftlAddr.pageNo & 0xFFFF) << 16) |    \
                 ((ftlAddr.blkNo & 0xFFFFFFFF) << 32);  \
        }while(0)
#endif

/* 
 * the size of bitmap which tracks the status of each page of a cached
 * block, whether the page presents in cache or not.
 */

#define BLK_BMP_SIZE(nPages)    ((nPages) >> BMP_SHIFT) 

/* AVL library does not provide the function for initializing a avl tree */ 

#define AVL_INIT(pTree)  do {   \
            pTree = NULL;       \
        }while(0)

/* helper macros for operating flags */

#define IS_FLAG_SET(flags, flag)  (((flags) & (flag)) == (flag))
#define SET_FLAG(flags, flag)     ((flags) |= (flag))
#define CLEAR_FLAG(flags, flag)   ((flags) &= (~(flag)))

/*
 * helper macro for iterating a doubly linked list. Note it is not
 * circular linked list.
 */

#define FTL_DLL_FOREACH(pNode, list)                    \
        for (((pNode) = (DLL_FIRST ((list))));          \
             ((pNode) != NULL);                         \
             ((pNode) = (DLL_NEXT ((pNode)))))

#define FTL_DLL_FOREACH_INVERSE(pNode, list)            \
        for (((pNode) = (DLL_LAST ((list))));           \
             ((pNode) != NULL);                         \
             ((pNode) = (DLL_PREVIOUS ((pNode)))))

#define FTL_TEST

/* #define FTL_DEBUG */

#ifdef FTL_DEBUG

#define DBG_QUIET       0x1    /* quiet */
#define DBG_MUST        0x2    /* always print */
#define DBG_BUG         0x4    /* fatal error */
#define DBG_FATAL       0x8    /* fatal error */
#define DBG_ERROR       0x10   /* normal error */
#define DBG_WARN        0x20   /* warning */
#define DBG_FLOW        0x40   /* monitor where i am */
#define DBG_INFO        0x80   /* informative message for debug */
#define DBG_MASK        0x7F   /* */

#define DEBUG_MON       (DBG_BUG | DBG_FATAL | DBG_ERROR | DBG_WARN) 
					/* monitored debug set */
#define DEBUG_DEF       (DBG_MUST | DBG_FATAL | DBG_ERROR | DBG_WARN) 
					/* default debug set */
#define DEBUG_CFG       (DBG_INFO)
					/* configurable debug set */
#define DEBUG_SET       (DEBUG_DEF | DEBUG_CFG)

/* 
 * the highest bit the level controls whether to print the msg for a
 * module, and the lower bits gives the type of the msg
 */
#define DEBUG_ON        (0x1U << 31)
#define DBG_LEVEL(dbgOn, level) (((dbgOn != 0)? DEBUG_ON : 0) | (level))
#define DEBUG_ENABLED(level) (((((level) & DEBUG_ON) != 0) &&   \
                         (((level) & (DEBUG_SET)) != 0)) ||     \
                         (((level) & DEBUG_DEF) != 0))

#ifdef obsolete
#define FTL_DBG_PRINTF(level, format, args...)  do {                    \
        if(DEBUG_ENABLED(level))                                        \
            {                                                           \
            dbgLogMonitor (level);                                   \
            printf ("TID(0x%lx): %d: %s:" format,                       \
                    (long)taskIdCurrent, __LINE__, __FUNCTION__,        \
                    ## args);                                           \
            }                                                           \
        }while(0)
#else
#define FTL_DBG_PRINTF(level, format, args...)  do {                    \
        if(DEBUG_ENABLED(level))                                        \
            {                                                           \
            dbgPrintf (level, "TID(0x%lx): %d: %s:" format,             \
                    (long)taskIdCurrent, __LINE__, __FUNCTION__,        \
                    ## args);                                           \
            }                                                           \
        }while(0)
#endif

/* logMsg is preferred to avoid msg interveling */

#define FTL_DBG_MSG (level, msg, a1, a2, a3, a4, a5, a6)  do {  \
            if(DEBUG_ENABLED (level)) {         \
                dbgLogMonitor (level);       \
                logMsg("%d:%s: "msg,            \
                (_Vx_usr_arg_t)__LINE__,        \
                (_Vx_usr_arg_t)__FUNCTION__,    \
                (_Vx_usr_arg_t)var1,            \
                (_Vx_usr_arg_t)var2,            \
                (_Vx_usr_arg_t)var3,            \
                (_Vx_usr_arg_t)var4);           \
            }                                   \
        }while(0)

#define FTL_DBG(level, format, args...)         \
            FTL_DBG_PRINTF(DEBUG_ON | level, format, ## args)

#define  FTL_DBG_I_AM_HERE()   FTL_DBG_PRINTF(DBG_FLOW, "I'm here!\n")

#define FTL_PARAM_CHECK_RETURN(var, value, retVal) do { \
        if ((var) == (value)) return ((retVal));        \
        }while(0)

#define FTL_DBG_ATOMIC32_SET(cnt, value)  FTL_ATOMIC32_SET(cnt, value)
#define FTL_DBG_ATOMIC32_ADD(cnt, value)  FTL_ATOMIC32_ADD(cnt, value)
#define FTL_DBG_ATOMIC32_SUB(cnt, value)  FTL_ATOMIC32_SUB(cnt, value)
#define FTL_DBG_ATOMIC64_SET(cnt, value)  FTL_ATOMIC64_SET(cnt, value)
#define FTL_DBG_ATOMIC64_ADD(cnt, value)  FTL_ATOMIC64_ADD(cnt, value)
#define FTL_DBG_ATOMIC64_SUB(cnt, value)  FTL_ATOMIC64_SUB(cnt, value)
#define FTL_DBG_VAR_SET(var, value)  ((var) = (value)) 
#define FTL_DBG_VAR_ADD(var, value)  ((var) += (value)) 
#define FTL_DBG_VAR_SUB(var, value)  ((var) -= (value)) 

#else /* !FTL_DEBUG */

#define FTL_PARAM_CHECK_RETURN(var, value, retVal)      /* nothing */
#define FTL_DBG_I_AM_HERE()                             /* nothing */ 
#define FTL_DBG_MSG(level, format, a1, a2, a3, a4, a5, a6) /* nothing */ 
#define FTL_DBG_PRINTF(level, format, args...)          /* nothing */ 
#define FTL_DBG FTL_DBG_PRINTF
#define FTL_DBG_ATOMIC32_SET(cnt, value)        /* nothing */ 
#define FTL_DBG_ATOMIC32_ADD(cnt, value)        /* nothing */ 
#define FTL_DBG_ATOMIC32_SUB(cnt, value)        /* nothing */ 
#define FTL_DBG_ATOMIC64_SET(cnt, value)        /* nothing */ 
#define FTL_DBG_ATOMIC64_ADD(cnt, value)        /* nothing */ 
#define FTL_DBG_ATOMIC64_SUB(cnt, value)        /* nothing */ 
#define FTL_DBG_VAR_SET(var, value)     /* nothing */
#define FTL_DBG_VAR_ADD(var, value)     /* nothing */ 
#define FTL_DBG_VAR_SUB(var, value)     /* nothing */  

#endif /* #ifdef FTL_DEBUG */

/* forward declarations */

BOOL bmpTest (UINT8 * addr, UINT32 bitPos); 
BOOL bmpIsAllClear (UINT8 * addr, UINT32 length); 
void bmpSet (UINT8 * addr, UINT32 bitPos); 
void bmpClear (UINT8 * addr, UINT32 bitPos); 
int bmpFfsLsb (UINT8 * addr, UINT32 length); 
int bmpFfsLsbHint (UINT8 * addr, UINT32 length, UINT32 hintPos); 

UINT32 ftlChkSum (const char * data, UINT32 crcIn, size_t size);
UINT32 ftlCrc32 (const char * data, UINT32 crcIn, size_t size);
UINT8 ftlCrc8 (const char * data, size_t size);

#ifdef FTL_DEBUG
int dbgLogMonitor (unsigned logLevel);
int dbgPrintf (unsigned logLevel, const char * fmt, ...);
int dbgLogDump (const char * pFileName);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCftlUtilPh */

