/* aimCacheLib.h - AIM header for Cache Functions */

/*
 * Copyright (c) 2003, 2005, 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01k,27may10,pad  Added 'extern C' statement.
01j,27aug08,jpb  Renamed VSB header file
01i,18jun08,jpb  Added include path for kernel configurations options set in
                 vsb.
01h,08may08,jpb  Modifications for source build.   Renamed INCLUDE_MEM_ALLOT to 
                 _WRS_CONFIG_MEM_ALLOT.
01g,24aug05,h_k  converted INCLUDE_CACHE_xxx to arch feature.
01f,19jul05,mil  Scaled out features for minimal kernel.
01e,19nov03,scm  flush out cache AIM lock/unlock...
01d,22oct03,jb   Incorporating changes from inspection
01d,24sep03,jb   Continuing Development
01c,09jun03,jb   Continue development
01b,01may03,jb   Continue development
01a,04apr03,jb   written
*/

#ifndef __INCaimCacheLibh
#define __INCaimCacheLibh

/* Includes Section */

#include <vsbConfig.h>

#include <cacheLib.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines Section */

/*
 * AIM cache errors
 */

/* temporary until vwModNum.h is updated */

#define M_aimcacheLib (190 << 16)

enum aimCacheErrors {
    S_aimCacheLib_UNKNOWN_CACHE_TYPE	= (M_aimcacheLib + 1 ),
    S_aimCacheLib_UNSUPPORTED_CACHE_FUNC,
    S_aimCacheLib_UNKNOWN_CACHE_OP
};

/* definitions of function argument types */

#define C_FLG_MASK      0xFFFFFF00  /* Extract function types */
#define C_FLG_OP_MASK   0x000000FF  /* Extract cache operation */
#define C_FLG_NOOP      0x00000100  /* Operation not supported */
#define C_FLG_MGMT      0x00000200  /* Management function, enable/disable */
#define C_FLG_VIRT      0x00000400  /* Function takes a Virtual Address */
#ifdef	_WRS_SUPPORT_CACHE_ISPHYSICAL
#define C_FLG_PHYS      0x00000800  /* Function takes a Physical Address */
#endif	/* _WRS_SUPPORT_CACHE_ISPHYSICAL */
#ifdef	_WRS_SUPPORT_CACHE_ISINDEXED
#define C_FLG_IDX_ONED  0x00001000  /* Function operates on a Indexed, */
                                    /* one dimensional array */
#define C_FLG_IDX_TWOD  0x00002000  /* Function operates on a Indexed, */
                                    /* two dimensional array */
#endif	/* _WRS_SUPPORT_CACHE_ISINDEXED */
#define C_FLG_ALL       0x00004000  /* Operates on the entire cache*/
#define C_FLG_DISP      0x00008000  /* Flush uses displacement */
#ifdef	_WRS_SUPPORT_CACHE_LOCK
#define C_FLG_LOCKPRTKT 0x00010000  /* Protect locked areas */
#endif	/* _WRS_SUPPORT_CACHE_LOCK */
#define C_FLG_ORDER_RV  0x00020000  /* Reverse calling order from */
                                    /* Primary, Secondary, Tertiary */
                                    /* when sub caches are */
                                    /* supportable by AIM */
#define C_FLG_FORCE     0x10000000  /* Top level API must call */
                                    /* this directly, this forces a*/
                                    /* passthrough to the architecture */
                                    /* defined routine */

/* Flags used within aimCacheLib.c */

#define CACHE_IS_VTOP       0x00100000  /* Virt to Phys needed */
#define CACHE_IS_PTOV       0x00200000  /* Phys to Virt needed */
#define CACHE_IS_VIRTUAL    0x00400000  /* The cache op is virtual */
#define CACHE_IS_PHYSICAL   0x00800000  /* The cache op is physical */
#define CACHE_IS_INDEXED    0x01000000  /* The cache op is indexed */
#define CACHE_IS_HARVARD    0x02000000
#define CACHE_IS_UNIFIED    0x04000000
#define CACHE_IS_MULTISIZE  0x08000000  /* Different line sizes */

#define CACHE_MODE_MASK  ( CACHE_IS_VIRTUAL | CACHE_IS_PHYSICAL | CACHE_IS_INDEXED)

/* Typedefs Section */

/*
 * enumeration of cache types
 * Note: The initial enumeration is to assure compatibility
 * with vxWorks 5.X
 */

typedef enum
    {
    CACHE_TYPE_I = _INSTRUCTION_CACHE,  /* Instruction Cache */
    CACHE_TYPE_D = _DATA_CACHE,         /* Data Cache */
#ifdef _WRS_SUPPORT_CACHE_EXTRA
    CACHE_TYPE_B = _BRANCH_CACHE,       /* Branch Cache */
    CACHE_TYPE_S,                       /* Secondary Cache */
    CACHE_TYPE_T,                       /* Tertiary Cache */
    CACHE_TYPE_IL,                      /* Instruction TLB Cache */
    CACHE_TYPE_DL,                      /* Data TLB Cache */
    CACHE_TYPE_A,                       /* Alternate Primary Cache */
                                        /* Xscale has a "mini-cache" */
#endif  /* _WRS_SUPPORT_CACHE_EXTRA */

    CACHE_TYPE_MAX_SUPPORTED
    }CACHETYPES;

/* enumeration of Primitive functions */

typedef enum
    {
    CACHE_OP_NOOP,          /* NO OP */
    CACHE_OP_ENABLE,        /* CACHENABLE() */
    CACHE_OP_DISABLE,       /* CACHEDISABLE() */
#ifdef _WRS_SUPPORT_CACHE_LOCK
    CACHE_OP_LOCK,          /* CACHELOCK() */
    CACHE_OP_UNLOCK,        /* CACHEUNLOCK() */
#endif  /* _WRS_SUPPORT_CACHE_LOCK */
    CACHE_OP_FLUSH,         /* CACHEFLUSH() */
    CACHE_OP_INVALIDATE,    /* CACHEINVALIDATE() */
    CACHE_OP_CLEAR,         /* CACHECLEAR() */
    CACHE_OP_TEXTUPDATE,    /* CACHETEXTUPDATE() */
    CACHE_OP_PIPEFLUSH,     /* CACHEPIPEFLUSH() */
#ifdef _WRS_SUPPORT_CACHE_XLATE
    CACHE_OP_DMAVIRTOPHYS,  /* VIRTUAL-TO-PHYSICAL TRANSLATION */
    CACHE_OP_DMAPHYSTOVIRT, /* PHYSICAL-TO-VIRTUAL TRANSLATION */
#endif  /* _WRS_SUPPORT_CACHE_XLATE */
#ifdef _WRS_SUPPORT_CACHE_EXTRA
    CACHE_OP_FENCE,         /* Memory synchronization */
    CACHE_OP_PREFETCH,      /* Prefetch a range of memory */
#endif  /* _WRS_SUPPORT_CACHE_EXTRA */
#ifndef _WRS_CONFIG_MEM_ALLOT
    CACHE_OP_DMAMALLOC,     /* Allocate a dma safe buffer */
    CACHE_OP_DMAFREE,       /* Free buffer allocated via DMAMALLOC */
#endif  /* !_WRS_CONFIG_MEM_ALLOT */
    CACHE_OP_ISON,          /* Is Cache On */
#ifdef _WRS_SUPPORT_CACHE_EXTRA
    CACHE_OP_EXP_0,         /* Architecture specific expansion */
    CACHE_OP_EXP_1,
    CACHE_OP_EXP_2,
    CACHE_OP_LAST = (CACHE_OP_EXP_2 + 3) /* This keeps _ALL functions */
                                         /* from overflowing the array */
#else   /* _WRS_SUPPORT_CACHE_EXTRA */
    CACHE_OP_LAST = (CACHE_OP_ISON + 3)
#endif  /* _WRS_SUPPORT_CACHE_EXTRA */
    } CACHE_OPS;

/* cache Attributes structure */

typedef struct cacheAttributes
    {
    CACHETYPES cacheType;      /* One of CACHETYPES */
    UINT32  cacheModeDefault;  /* copyback, writethrough, etc. */
    UINT32  cacheModeSupported;/* copyback, writethrough, etc. */
    UINT32  cacheSize;         /* 0 for "not present" */
    UINT32  lineSize;          /* in bytes */
    UINT32  lineStep;          /* increment between cache lines */
    UINT32  numWays;           /* number of way in the cache */
    UINT32  wayStep;           /* increment between cache ways */
    UINT32  numSegs;           /* number of segments in a segmented cache */
    UINT32  segStep;           /* increment between segments */
    void *  cacheBase;         /* Index or displacement cache ops */
    } CACHEATTRIBUTES;

/* Description of cache primitive */

typedef struct cacheOp
    {
    UINT32    opType;          /* From C_FLG defines */
    FUNCPTR   opPtr;           /* Pointer to the Primitive */
    } CACHEOP;


/* Description of a cache or portion of a cache */

typedef struct cachePrimitive
    {
    CACHEATTRIBUTES cacheAttr;    /* This could be a pointer */
    CACHEOP         cacheOps[CACHE_OP_LAST];
    }CACHEPRIMITIVE;

/*
 * cacheConfig is the structure that encapsulates a CPU's
 * cache properties.
 */

typedef struct cacheConfig
    {
    UINT32         nCaches;    /* Number of caches described in this struct */
    CACHEPRIMITIVE cachePrimitives[CACHE_TYPE_MAX_SUPPORTED];
    }CACHECONFIG;

/* The following data elements are initialized and maintained */
/* by the cache AIM based on the data passed to it via the */
/* CACHECONFIG structure */

/*
 * Cache attributes structure for use in cacheAimInfo.
 */

typedef struct cacheGlobalAttr
    {
    UINT32 cacheExists;         /* Indicates that this entry in the array is valid */
    UINT32 cacheType;		/* Type of cache, I,D */
    UINT32 cacheSize;		/* Size in bytes of this cache */
    UINT32 cacheLineSize;	/* Line size for this cache */
    UINT32 cacheModes;		/* Modes supported by this cache */
    UINT32 cacheModeCurrent;    /* Current mode of this cache */
    }CACHEGLOBALATTR;

/*
 * Lock database structure.
 * Keeps track of locked areas, facilitating the protection of locked areas
 * from invalidates. The Lock database uses virtual addresses, a flat memory
 * model allows this.
 *
 * Dynamically allocated by the AIM for lock management.
 */

typedef struct cacheLockNode *lockNodePtr;
typedef struct cacheLockNode
    {
    lockNodePtr pNext;
    lockNodePtr pPrev;
    UINT32      cacheLockStart;
    UINT32      cacheLockEnd;
    }CACHELOCKNODE;

/* Globally visible array of attributes */

extern CACHEGLOBALATTR cacheAimInfo[CACHE_TYPE_MAX_SUPPORTED];

extern UINT32 cacheLineSize;       /* Cache line size. Used for alignment */
extern UINT32 cacheAddrAlign;      /* Increment for address alignment */
extern UINT32 cacheLineMask;       /* Mask to align to a cache line */

/* Forward Declarations */

STATUS aimCacheInit ( CACHECONFIG * cacheConfig );

#ifdef __cplusplus
}
#endif

#endif /* __INCaimCacheLibh */
