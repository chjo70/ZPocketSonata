/* ftlOsIf.h - FTl OS-dependent definitions */ 

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
11oct13,ghs  Correct compile error (WIND00438400)
29feb12,jxu  written.
*/

#ifndef __INCftlOsIfh
#define __INCftlOsIfh


/* includes */

#include <vxWorks.h>
#include <stdio.h>
#include <stdarg.h>
#include <vsbConfig.h>
#include <sys/types.h>
#include <types/vxTypes.h>
#include <memLib.h>
#include <ioLib.h>
#include <string.h>
#include <errnoLib.h>
#include <unistd.h>
#include <taskLib.h>
#include <taskLibCommon.h>
#include <semLib.h>
#include <semLibCommon.h>
#include <avlLib.h>
#include <private/memPartLibP.h>
#include <dllLib.h>
#include <edrLib.h>
#include <edrLibCommon.h>       
#include <private/sigLibP.h>    /* _sigCtxSave */
#include <cacheLib.h>           /* cacheDmaMalloc/Free */
#include <vxAtomicLib.h>         
#include <private/vxAtomicLibP.h>       /* _WRS_ATOMIC_XXX() */
#include <private/vxPortableP.h>        /* vxAtomic64Xxx */
#include <tickLib.h>            /* tickGet() */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

#define FTL_LOCK_NULL           SEM_ID_NULL 
#define FTL_LOCK_RW_NULL        SEM_ID_NULL 
#define FTL_SEM_NULL            SEM_ID_NULL 
#define FTL_TASK_NULL           TASK_ID_NULL

/* additional flag for semaphore taking */

#define FTL_SEM_TAKE_FAIL_PANIC 0x1

/* memory allocation and free */

#define FTL_MEM_ALLOC(nBytes)       ftlMemAlloc(nBytes)
#define FTL_MEM_FREE(pChar)         ftlMemFree((char *)pChar)
#define FTL_CACHE_DMA_ALLOC(nBytes) ftlCacheDmaMalloc(nBytes)
#define FTL_CACHE_DMA_FREE(pChar)   ftlCacheDmaFree((char *)pChar)

/* atomic variable operations */

#define FTL_ATOMIC32_INC(atomicVar)     ftlAtomic32Inc(atomicVar)
#define FTL_ATOMIC32_DEC(atomicVar)     ftlAtomic32Dec(atomicVar)
#define FTL_ATOMIC32_GET(atomicVar)     ftlAtomic32Get(atomicVar)
#define FTL_ATOMIC32_CLEAR(atomicVar)   ftlAtomic32Clear(atomicVar)
#define FTL_ATOMIC32_SET(atomicVar, value) ftlAtomic32Set(atomicVar, value)
#define FTL_ATOMIC32_ADD(atomicVar, value) ftlAtomic32Add(atomicVar, value)
#define FTL_ATOMIC32_SUB(atomicVar, value) ftlAtomic32Sub(atomicVar, value)

#define FTL_ATOMIC64_GET(atomicVar)     ftlAtomic64Get(atomicVar)
#define FTL_ATOMIC64_SET(atomicVar, value) ftlAtomic64Set(atomicVar, value)
#define FTL_ATOMIC64_ADD(atomicVar, value) ftlAtomic64Add(atomicVar, value)
#define FTL_ATOMIC64_SUB(atomicVar, value) ftlAtomic64Sub(atomicVar, value)

/* task creation and deletion */

#define FTL_TASK_CREATE(name, prio, option, stackSize, func, pArg)      \
                ftlTaskCreate (name, prio, option, stackSize, func, pArg) 
#define FTL_TASK_DELETE(taskId)       ftlTaskDelete(taskId)

/* maximum readers for reader/writer lock */

#define FTL_RW_SEM_MAX_READERS  8

/* semaphore operations */

#define FTL_SEM_C_CREATE(initCnt) ftlSemCCreate( \
                SEM_Q_PRIORITY, initCnt)
#define FTL_SEM_B_CREATE(option, initStat) ftlSemBCreate( \
                option, initStat)

#define FTL_SEM_TAKE_TRY(semId) ftlSemTakeTry (semId)
#define FTL_SEM_TAKE_TIMEOUT (semId, ticks)     \
                ftlSemTake(semId, ticks, 0) 
#define FTL_SEM_TAKE(semId)     \
                ftlSemTake(semId, WAIT_FOREVER, FTL_SEM_TAKE_FAIL_PANIC) 
#define FTL_SEM_TAKE_NO_PANIC(semId, ticks) \
                ftlSemTake(semId, ticks, 0)
#define FTL_SEM_GIVE(semId)     ftlSemGive(semId)

#ifdef notyet 
#define FTL_LOCK_RW_CREATE()    ftlSemRWCreate( \
                SEM_Q_PRIORITY | SEM_DELETE_SAFE | SEM_INVERSION_SAFE, \
                FTL_RW_SEM_MAX_READERS)
#define FTL_LOCK_R(rwLock)      ftlSemRTake(rwLock, WAIT_FOREVER)
#define FTL_LOCK_W(rwLock)      ftlSemWTake(rwLock, WAIT_FOREVER)
#define FTL_TRY_LOCK_R(rwLock)  ftlSemRTake(rwLock, NO_WAIT)
#define FTL_TRY_LOCK_W(rwLock)  ftlSemWTake(rwLock, NO_WAIT)
#define FTL_UNLOCK_RW(rwLock)   ftlSemRWGive(rwLock)
#define FTL_LOCK_RW_DELETE(rwLock) ftlSemDelete(rwLock)
#else   /* !notyet */
#define FTL_LOCK_RW_CREATE()    FTL_LOCK_CREATE() 
#define FTL_LOCK_R(rwLock)      FTL_LOCK(rwLock) 
#define FTL_LOCK_W(rwLock)      FTL_LOCK(rwLock) 
#define FTL_TRY_LOCK_R(rwLock)  FTL_TRY_LOCK(rwLock) 
#define FTL_TRY_LOCK_W(rwLock)  FTL_TRY_LOCK(rwLock) 
#define FTL_UNLOCK_RW(rwLock)   FTL_UNLOCK(rwLock) 
#define FTL_LOCK_RW_DELETE(rwLock) FTL_LOCK_DELETE(rwLock) 
#endif  /* notyet */

/* mutual exclusive lock */

#define FTL_LOCK_CREATE()       ftlSemMCreate( \
                SEM_Q_PRIORITY | SEM_DELETE_SAFE | SEM_INVERSION_SAFE)
#define FTL_LOCK(lock)          ftlSemTake(lock, WAIT_FOREVER,\
                FTL_SEM_TAKE_FAIL_PANIC)
#define FTL_TRY_LOCK(lock)      ftlSemTake(lock, NO_WAIT, 0)
#define FTL_UNLOCK(lock)        ftlSemGive(lock)
#define FTL_LOCK_DELETE(lock)   ftlSemDelete(lock)

#define FTL_SEM_DELETE(semId)   ftlSemDelete(semId)

#define FTL_DIAGNOSTIC
#ifdef FTL_DIAGNOSTIC
#define FTL_PANIC(...) ftlPanic(__FILE__, __LINE__, __VA_ARGS__)
#else
#define FTL_PANIC(...)    /* nothing */
#endif /* FTL_DIAGNOSTIC */

#define FTL_TICK_GET()          ftlTickGet()
#define FTL_SYS_CLK_RATE_GET()  ftlSysClkRateGet()

#define FTL_SET_ERRNO(errNo)    ftlSetErrno(errNo)

/* typedefs */

typedef SEM_ID          FTL_LOCK_RW_T;  /* reader/writer lock type */
typedef SEM_ID          FTL_LOCK_T;     /* mutual exclusive lock */
typedef SEM_ID          FTL_SEM_T;      /* mutual exclusive lock */
typedef TASK_ID         FTL_TASK_T;     /* task type */

typedef atomic32_t      FTL_ATOMIC32_T; /* atomic variable */

#ifdef _WRS_PORTABLE_vxAtomicLib       
typedef atomic64_t      FTL_ATOMIC64_T; /* atomic variable */
#else
typedef atomic32_t      FTL_ATOMIC64_T; /* atomic variable */
#endif

typedef _Vx_ticks_t     FTL_TICK_T;

typedef _Vx_usr_arg_t   FTL_USR_ARG_T;

/* function declarations */

IMPORT void * ftlMemAlloc (size_t nBytes);
IMPORT int ftlMemFree (char * pMem);
IMPORT void * ftlCacheDmaMalloc (size_t nBytes);
IMPORT int ftlCacheDmaFree (char * pMem);
IMPORT FTL_ATOMIC32_T ftlAtomic32Inc (FTL_ATOMIC32_T * pVar);
IMPORT FTL_ATOMIC32_T ftlAtomic32Dec (FTL_ATOMIC32_T * pVar);
IMPORT FTL_ATOMIC32_T ftlAtomic32Clear (FTL_ATOMIC32_T * pVar);
IMPORT FTL_ATOMIC32_T ftlAtomic32Get (FTL_ATOMIC32_T * pVar);
IMPORT FTL_ATOMIC32_T ftlAtomic32Set (FTL_ATOMIC32_T * pVar, 
            FTL_ATOMIC32_T value);
IMPORT FTL_ATOMIC32_T ftlAtomic32Add (FTL_ATOMIC32_T * pVar, 
            FTL_ATOMIC32_T value);
IMPORT FTL_ATOMIC32_T ftlAtomic32Sub (FTL_ATOMIC32_T * pVar, 
            FTL_ATOMIC32_T value);
IMPORT FTL_ATOMIC64_T ftlAtomic64Get (FTL_ATOMIC64_T * pVar); 
IMPORT FTL_ATOMIC64_T ftlAtomic64Set (FTL_ATOMIC64_T * pVar, 
            FTL_ATOMIC64_T value);
IMPORT FTL_ATOMIC64_T ftlAtomic64Add (FTL_ATOMIC64_T * pVar, 
            FTL_ATOMIC64_T value);
IMPORT FTL_ATOMIC64_T ftlAtomic64Sub (FTL_ATOMIC64_T * pVar, 
            FTL_ATOMIC64_T value);
IMPORT FTL_TASK_T ftlTaskCreate (char * name, int priority,
            int options, size_t stackSize, FUNCPTR entryPt,
            FTL_USR_ARG_T pArg);
IMPORT int ftlTaskDelete (FTL_TASK_T taskId);
IMPORT FTL_SEM_T ftlSemMCreate (int options);
IMPORT FTL_SEM_T ftlSemCCreate (int options, int initCnt);
IMPORT FTL_SEM_T ftlSemBCreate (int options, int initStat);
IMPORT int ftlSemDelete (FTL_SEM_T semId);
IMPORT int ftlSemTakeTry (FTL_SEM_T semId);
IMPORT int ftlSemTake (FTL_SEM_T semId, FTL_TICK_T ticks, int flags);
IMPORT int ftlSemGive (FTL_SEM_T semId);
IMPORT int ftlSysClkRateGet (void);
IMPORT FTL_TICK_T ftlTickGet (void);
IMPORT int ftlSetErrno (int errNo);
void ftlPanic (const char * file, int line, const char * fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCftlOsIfh */

