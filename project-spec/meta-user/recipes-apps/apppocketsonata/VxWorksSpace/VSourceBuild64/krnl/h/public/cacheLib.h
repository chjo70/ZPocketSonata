/* cacheLib.h - cache library header file */

/*
 * Copyright (c) 1990-1998, 2000-2001, 2003-2004, 2007, 2009-2010, 2014-2016
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23nov16,lz1  support IA Arch L2 Cache QoS (F7283)
25apr15,ymz  removed cacheDrvPhysToVirt, and cacheForeign* related
             prototypes from CERT (V7SP-110)
25feb14,pcs  VXW7-1903 - INCLUDE_CACHE_DMA32_LIB could only be used for LP64
11feb14,h_k  added cacheArchLibInit() prototype to ARM.
27oct10,scm  WIND00238295 Macro CACHE_DRV_PHYS_TO_VIRT and API
             cacheDrvPhysToVirt() must be removed from VxWorks 64-bit
27may10,pad  Moved extern C statement after include statements.
07apr10,jpb  Added function declarations.
09dec09,h_k  changed cacheDma32Malloc and cacheDma32Free aliases from
             macros in ILP32. fixed the return value for cacheDma32Free().
29oct09,h_k  fixed cacheDma32Malloc and Free macros for ILP32.
06nov09,pcs  Resolve build issue with macro CACHE_TEXT_UPDATE on UP.
22jun09,x_s  use _WRS_CONFIG_SMP VSB option to update CACHE_TEXT_UPDATE
16sep09,h_k  added cacheDma32Malloc and cacheDma32Free.
19jun09,mze  replacing PAD64
05may09,h_k  replaced FUNCPTR with fully qualified function pointer
             parameters.
20jan09,jb   Adding 64-bit support
13jul07,sru  update CACHE_TEXT_UPDATE for SMP
11jan07,scm  rename S_cacheLib_FUNCTION_UNSUPPORTED... to
             S_cacheLib_UNSUPPORTED.
10jan07,scm  add S_cacheLib_FUNCTION_UNSUPPORTED...
05may04,sru  add cacheForeign* API; remove non-ANSI prototypes.
09may03,pes  Move definition of numeric values for cache types out of
             #ifndef _ASMLANGUAGE.
29apr03,pes  PAL conditional compilation cleanup.
22oct01,dee  merge from T2.1.0 coldfire release
10sep00,hk   extended CACHE_TYPE for SH7729.
01mar00,frf  Add SH4 support for T2
23apr97,hk   added SH support.
05nov98.jpd  removed cacheArchLibInit definition for ARM.
28nov96,cdp  added ARM support.
26may94,yao  added PPC support.
19mar95,dvs  removed #ifdef TRON - tron no longer supported.
08jun94,tpr  added branch cache used by MC68060 cpu.
02dec93,pme  Added Am29K family support.
09jun93,hdn  added support for I80X86
19oct92,jcf  reordered xxLibInit params.  made CACHE_TYPE v5.0 compatible.
29sep92,jwt  merged cacheLibInit(), cacheReset(), and cacheModeSet().
22sep92,rrr  added support for c++
20aug92,wmd  added #include for i960.
13aug92,rdc  removed instances of cacheLib functions and CACHE_FUNCS
             structures and conditional compilation of corresponding
             IMPORTS.
30jul92,dnw  added cacheLib functions and CACHE_FUNCS structures.
15jul92,jwt  added more CACHE_MODEs.
09jul92,jwt  added virtual-to-physical and physical-to-virtual stuff.
07jul92,ajm  added support for mips
06jul92,jwt  cleaned up cacheDrvXxx() macros by stressing pointers.
04jul92,jcf  cleaned up.
03jul92,jwt  cache library header for 5.1; moved '040 stuff to arch/mc68k.
16jun92,jwt  made safe for assembly language files.
26may92,rrr  the tree shuffle
              -changed includes to have absolute path from h/
20jan92,shl  added cache68kLib.h.
09jan92,jwt  created cacheSPARCLib.h;
             cleaned up ANSI compiler warning messages.
04oct91,rrr  passed through the ansification filter
              -fixed #else and #endif
              -changed copyright notice
27aug91,shl  added scope type for MC68040 caches.
19jul91,gae  renamed architecture specific include file to be xx<arch>.h.
23jan91,jwt  added SPARC cache commands.
01mar91,hdn  added TRON related stuff.
05oct90,shl  added copyright notice; made #endif ANSI style.
15jul90,jcf  written.
*/

#ifndef __INCcacheLibh
#define __INCcacheLibh

#include <vxWorks.h>
#include <vwModNum.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Cache mode soft bit masks */

#define	CACHE_DISABLED		0x00	/* No cache or disabled */

#define	CACHE_WRITETHROUGH	0x01	/* Write-through Mode */
#define	CACHE_COPYBACK		0x02	/* Copyback Mode */
#define	CACHE_WRITEALLOCATE	0x04	/* Write Allocate Mode */
#define	CACHE_NO_WRITEALLOCATE	0x08
#define	CACHE_SNOOP_ENABLE	0x10	/* Bus Snooping */
#define	CACHE_SNOOP_DISABLE	0x20
#define	CACHE_BURST_ENABLE	0x40	/* Cache Burst Cycles */
#define	CACHE_BURST_DISABLE	0x80

/* Errno values */

#define S_cacheLib_INVALID_CACHE	(M_cacheLib | 1)
#define S_cacheLib_UNSUPPORTED 		(M_cacheLib | 2)

#ifndef	_WRS_CONFIG_COMPAT69_ADR_SPACE
#define S_cacheLib_DMA32_RAM_UNSUPPORTED (M_cacheLib | 3)
#endif	/* _WRS_CONFIG_COMPAT69_ADR_SPACE */

#define S_cacheLib_QOS_CACHE_LEVEL_ERROR (M_cacheLib | 4)
#define S_cacheLib_QOS_NOT_INITIALIZED   (M_cacheLib | 5)
#define S_cacheLib_QOS_CPUSET_ERROR      (M_cacheLib | 6)
#define S_cacheLib_QOS_OVERALLOCATION    (M_cacheLib | 7)
#define S_cacheLib_QOS_MASK_UNAVAILABLE  (M_cacheLib | 8)
#define S_cacheLib_QOS_NO_FREE_COSID     (M_cacheLib | 9)
#define S_cacheLib_QOS_INVALID_BITMASK   (M_cacheLib | 10)
#define S_cacheLib_QOS_INVALID_COSID     (M_cacheLib | 11)
#define S_cacheLib_QOS_UNSUPPORTED       (M_cacheLib | 12)

/* Value for "entire cache" in length arguments */

#define	ENTIRE_CACHE		ULONG_MAX

/* explicit names of the cache types */

#define	_INSTRUCTION_CACHE 	0	/* Instruction Cache(s) */
#define	_DATA_CACHE		1	/* Data Cache(s) */
#define	_BRANCH_CACHE		2	/* Branch Cache(s) */

/*
 * Cache Level
 */

#define _CACHE_L1           0
#define _CACHE_L2           1
#define _CACHE_L3           2

#ifndef	_ASMLANGUAGE

#if !defined (_WRS_CACHE_TYPE)
typedef enum				/* CACHE_TYPE */
    {
    INSTRUCTION_CACHE = _INSTRUCTION_CACHE,
    DATA_CACHE        = _DATA_CACHE
    } CACHE_TYPE;
#endif /* _WRS_CACHE_TYPE */

typedef enum cache_level
    {
    CACHE_L1 = _CACHE_L1,
    CACHE_L2 = _CACHE_L2,
    CACHE_L3 = _CACHE_L3
    } cache_level_t;

typedef	UINT	CACHE_MODE;		/* CACHE_MODE */
typedef STATUS	(*CACHEFOREIGNFUNC)(CACHE_TYPE, VIRT_ADDR, 
				    PHYS_ADDR, size_t);

typedef	struct				/* Cache Routine Pointers */
    {
    STATUS (*enableRtn)(CACHE_TYPE);			/* cacheEnable() */
    STATUS (*disableRtn)(CACHE_TYPE);			/* cacheDisable() */
    STATUS (*lockRtn)(CACHE_TYPE, void *, size_t);	/* cacheLock() */
    STATUS (*unlockRtn)(CACHE_TYPE, void *, size_t);	/* cacheUnlock() */
    STATUS (*flushRtn)(CACHE_TYPE, void *, size_t);	/* cacheFlush() */
    STATUS (*invalidateRtn)(CACHE_TYPE, void *, size_t);/* cacheInvalidate() */
    STATUS (*clearRtn)(CACHE_TYPE, void *, size_t);	/* cacheClear() */

    STATUS (*textUpdateRtn)(void *, size_t);		/* cacheTextUpdate() */
    STATUS (*pipeFlushRtn)(void);			/* cachePipeFlush() */
    void * (*dmaMallocRtn)(size_t);			/* cacheDmaMalloc() */
    STATUS (*dmaFreeRtn)(void *);			/* cacheDmaFree() */
    void * (*dmaVirtToPhysRtn)(void *);
					/* virtual-to-Physical Translation */
    void * (*dmaPhysToVirtRtn)(void *);
					/* physical-to-Virtual Translation */

    /* explicit prototypes required due to PHYS_ADDR datatype */

    CACHEFOREIGNFUNC foreignFlushRtn;	   /* cacheForeignFlush() */
    CACHEFOREIGNFUNC foreignInvalidateRtn; /* cacheForeignInvalidate() */
    CACHEFOREIGNFUNC foreignClearRtn;	   /* cacheForeignClear() */
    } CACHE_LIB;

/* Cache flush and invalidate support for general use and drivers */

typedef	struct				/* Driver Cache Routine Pointers */
    {
    STATUS (*flushRtn)(CACHE_TYPE, void *, size_t);	/* cacheFlush() */
    STATUS (*invalidateRtn)(CACHE_TYPE, void *, size_t);/* cacheInvalidate() */
    void * (*virtToPhysRtn)(void *);	/* Virtual-to-Physical Translation */
    void * (*physToVirtRtn)(void *);	/* Physical-to-Virtual Translation */
    } CACHE_FUNCS;


/* Cache macros */

/*
 * SMP requires cacheTextUpdate functionality to be enabled so we can
 * call the function directly.  But this functionality is not required
 * for all configurations of UP so we only call it if the textUpdate routine
 * has been initialized.
 */

#ifdef _WRS_CONFIG_SMP
#define	CACHE_TEXT_UPDATE(adrs, bytes)	\
	cacheTextUpdate ((void *) (adrs), (size_t) (bytes))

#define	CACHE_TEXT_LOCAL_UPDATE(adrs, bytes)	\
	cacheTextLocalUpdate ((void *) (adrs), (size_t) (bytes))
#else
#define CACHE_TEXT_UPDATE(adrs, bytes)  \
        ((cacheLib.textUpdateRtn == NULL) ? OK : \
         (cacheLib.textUpdateRtn) ((void *) (adrs), (size_t) (bytes)))
 
#define CACHE_TEXT_LOCAL_UPDATE(adrs, bytes)    \
        CACHE_TEXT_UPDATE(adrs, (size_t) bytes)
#endif /* _WRS_CONFIG_SMP */

#define	CACHE_PIPE_FLUSH()	\
        ((cacheLib.pipeFlushRtn == NULL) ? OK :	\
	 (cacheLib.pipeFlushRtn) ())


#define	CACHE_DRV_FLUSH(pFuncs, adrs, bytes)	\
        (((pFuncs)->flushRtn == NULL) ? OK :	\
         ((pFuncs)->flushRtn) (DATA_CACHE, (void *) (adrs), (size_t) (bytes)))

#define	CACHE_DRV_INVALIDATE(pFuncs, adrs, bytes)	\
        (((pFuncs)->invalidateRtn == NULL) ? OK :	\
         ((pFuncs)->invalidateRtn) (DATA_CACHE,		\
				    (void *) (adrs), (size_t) (bytes)))

#define	CACHE_DRV_VIRT_TO_PHYS(pFuncs, adrs)	\
        (((pFuncs)->virtToPhysRtn == NULL) ? (void *) (adrs) :	\
	 (((pFuncs)->virtToPhysRtn) ((void *) (adrs))))

#ifndef _WRS_CONFIG_LP64
#define	CACHE_DRV_PHYS_TO_VIRT(pFuncs, adrs)	\
        (((pFuncs)->physToVirtRtn == NULL) ? (void *) (adrs) :	\
	 (((pFuncs)->physToVirtRtn) ((void *) (adrs))))
#endif /* !_WRS_CONFIG_LP64 */

#define	CACHE_DRV_IS_WRITE_COHERENT(pFuncs)	\
	((pFuncs)->flushRtn == NULL)

#define	CACHE_DRV_IS_READ_COHERENT(pFuncs)	\
	((pFuncs)->invalidateRtn == NULL)


#define	CACHE_DMA_FLUSH(adrs, bytes)		\
	CACHE_DRV_FLUSH (&cacheDmaFuncs, (adrs), (bytes))

#define	CACHE_DMA_INVALIDATE(adrs, bytes)	\
	CACHE_DRV_INVALIDATE (&cacheDmaFuncs, (adrs), (bytes))

#define	CACHE_DMA_VIRT_TO_PHYS(adrs)	\
	CACHE_DRV_VIRT_TO_PHYS (&cacheDmaFuncs, (adrs))

#ifndef _WRS_CONFIG_LP64
#define	CACHE_DMA_PHYS_TO_VIRT(adrs)	\
	CACHE_DRV_PHYS_TO_VIRT (&cacheDmaFuncs, (adrs))
#endif /* !_WRS_CONFIG_LP64 */

#define	CACHE_DMA_IS_WRITE_COHERENT()	\
	CACHE_DRV_IS_WRITE_COHERENT (&cacheDmaFuncs)

#define	CACHE_DMA_IS_READ_COHERENT()	\
	CACHE_DRV_IS_READ_COHERENT (&cacheDmaFuncs)


#define	CACHE_USER_FLUSH(adrs, bytes)	\
	CACHE_DRV_FLUSH (&cacheUserFuncs, (adrs), (bytes))

#define	CACHE_USER_INVALIDATE(adrs, bytes)	\
	CACHE_DRV_INVALIDATE (&cacheUserFuncs, (adrs), (bytes))

#define	CACHE_USER_IS_WRITE_COHERENT()	\
	CACHE_DRV_IS_WRITE_COHERENT (&cacheUserFuncs)

#define	CACHE_USER_IS_READ_COHERENT()	\
	CACHE_DRV_IS_READ_COHERENT (&cacheUserFuncs)



/* variable declarations */

IMPORT CACHE_LIB	cacheLib;
IMPORT CACHE_FUNCS	cacheNullFuncs;	/* functions for non-cached memory */
IMPORT CACHE_FUNCS	cacheDmaFuncs;	/* functions for dma memory */
IMPORT CACHE_FUNCS	cacheUserFuncs;	/* functions for user memory */

IMPORT void *		(*cacheDmaMallocRtn)(size_t);
IMPORT STATUS		(*cacheDmaFreeRtn)(void *);
IMPORT CACHE_MODE	cacheDataMode;	/* data cache modes for funcptrs */
IMPORT BOOL		cacheDataEnabled;
IMPORT BOOL		cacheMmuAvailable;

/* function declarations */

extern STATUS	cacheLibInit (CACHE_MODE inst, CACHE_MODE data);
extern STATUS	cacheArchLibInit (CACHE_MODE inst, CACHE_MODE data);
extern STATUS	cacheEnable (CACHE_TYPE cache);
extern STATUS	cacheDisable (CACHE_TYPE cache);
extern STATUS	cacheLock (CACHE_TYPE cache, void * adrs, size_t bytes);
extern STATUS	cacheUnlock (CACHE_TYPE cache, void * adrs, size_t bytes);
extern STATUS	cacheFlush (CACHE_TYPE cache, void * adrs, size_t bytes);
extern STATUS	cacheInvalidate (CACHE_TYPE cache, void *adrs, size_t bytes);
extern STATUS	cacheClear (CACHE_TYPE cache, void * adrs, size_t bytes);
extern STATUS	cacheTextUpdate (void * adrs, size_t bytes);
extern STATUS	cacheTextLocalUpdate (void * adrs, size_t bytes);
extern STATUS	cachePipeFlush (void);
extern STATUS   cacheDmaPoolAlloc (UINT32 initialPageCount, UINT32 pageIncrement);
extern void *	cacheDmaMalloc (size_t bytes);
extern STATUS	cacheDmaFree (void * pBuf);
extern STATUS   cacheDma32PartInit (void);
extern void *	cacheDma32Malloc (size_t nBytes);
extern STATUS	cacheDma32Free (void * pBfr);

extern STATUS	cacheDrvFlush (CACHE_FUNCS * pFuncs, void * adrs, size_t bytes);
extern STATUS	cacheDrvInvalidate (CACHE_FUNCS * pFuncs, void * adrs,
				    size_t bytes);
extern void *   cacheDrvVirtToPhys (CACHE_FUNCS * pFuncs, void * adrs);

#ifndef _WRS_CONFIG_CERT
#ifndef _WRS_CONFIG_LP64
extern void *   cacheDrvPhysToVirt (CACHE_FUNCS * pFuncs, void * adrs);
#endif /* !_WRS_CONFIG_LP64 */

extern STATUS   cacheForeignFlush (CACHE_TYPE cache, VIRT_ADDR virtAdrs, 
				   PHYS_ADDR physAdrs, size_t bytes);
extern STATUS   cacheForeignInvalidate (CACHE_TYPE cache, VIRT_ADDR virtAdrs, 
					PHYS_ADDR physAdrs, size_t bytes);
extern STATUS   cacheForeignClear (CACHE_TYPE cache, VIRT_ADDR virtAdrs, 
				   PHYS_ADDR physAdrs , size_t bytes);
#endif /* !_WRS_CONFIG_CERT */

extern void	cacheFuncsSet (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

/*
 * Architecture-specific cache headers.
 *
 * Note: those need the CACHE_TYPE type defined further above.
 */

#if	(CPU_FAMILY == MC680X0)
#include "arch/mc68k/cacheMc68kLib.h"
#endif  /* (CPU_FAMILY == MC680X0) */

#if	(CPU_FAMILY == COLDFIRE)
#include "arch/coldfire/cacheColdfireLib.h"
#endif  /* (CPU_FAMILY == COLDFIRE) */

#if	(CPU_FAMILY == SPARC)
#include "arch/sparc/cacheSparcLib.h"
#endif

#if	(CPU_FAMILY == MIPS)
#include "arch/mips/cacheMipsLib.h"
#endif  /* (CPU_FAMILY == MIPS) */

#if	(CPU_FAMILY == PPC)
#include "arch/ppc/cachePpcLib.h"
#endif	/* CPU_FAMILY == PPC */

#if	(CPU_FAMILY == I960)
#include "arch/i960/vxI960Lib.h"
#endif  /* CPU_FAMILY == I960 */

#if	(CPU_FAMILY == I80X86)
#ifndef _WRS_CONFIG_LP64
#include "arch/i86/cacheI86Lib.h"
#else
#include "arch/i86/x86_64/cacheX86_64.h"
#endif  /* CPU==LP64 */
#endif  /* CPU_FAMILY == I80X86 */

#if	(CPU_FAMILY == AM29XXX)
#include "arch/am29k/cacheAm29kLib.h"
#endif  /* CPU_FAMILY == AM29XXX */

#if	(CPU_FAMILY == SH)
#include "arch/sh/cacheShLib.h"
#endif	/* CPU_FAMILY == SH */

#if     (CPU_FAMILY == ARM)
#include "arch/arm/cacheArmLib.h"
#endif  /* CPU_FAMILY == ARM */

#endif /* __INCcacheLibh */
