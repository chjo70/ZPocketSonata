/* vxbDmaBufLib.h - buffer and DMA system for VxBus drivers */

/*
 * Copyright (c) 2005-2010, 2012-2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
30nov17,mw1  add the definition of VXB_DMABUF_FORCED_BOUNCE (V7STO-974)
23jan17,mw1  update VXB_SPACE_MAXADDR for IA32_PAE mode  (V7STO-764)
21jun16,wap  Add prototype for library initialization routine
07apr16,wap  Temporarily add cacheDmaMalloc()/cacheDmaFree() APIs for
             user-mode drivers
22jan14,r_y  add VXB_DMABUF_MAPLOAD_CONTINUE flag.(VXW7-1251)
11jun12,sye  Removed duplicate method declaration. (WIND00353762)
29apr10,pad  Moved extern C statement after include statements.
26feb10,h_k  added mapSyncPartFunc member in vxbDmaBufMap structure.
             added vxbDmaBufFragFill().
             added VXB_DMABUF_CACHESNOOP_BUS and
             VXB_DMABUF_MEMALLOC_CLEAR_BUF.
10feb10,h_k  added pBounceSaved in vxbDmaBufMap.
             added new options related to bounce buffer.
             added new options for vxbDmaBufSync() to correct the pre-
             post- DMA sync operations.
             added vxbDmaBufMapSync().
04jan10,h_k  replaced FUNCPTR with fully qualified function pointer
             parameters for mapXxx funcs.
21sep09,h_k  added VXB_SPACE_MAXADDR macros.
01sep09,h_k  added fragVirt to vxbDmaBufFrag.
             changed the type of frag to UINT64.
25mar09,h_k  added prototype for vxbDmaBufInit().
30may08,dlk  Access headers under wrn/coreip directly.
27mar08,dlk  Add mapLoadIpcomFunc member to vxbDmaBufMap, and
             vxbDmaBufMapIpcomLoad() prototype.
31oct07,wap  Cache pointer to parent bus controller in DMA map
             (WIND00104927)
21feb07,mil  Fixed missing include file vxBus.h.
30jan07,wap  Use method declaration macros
19jul06,wap  Refine bounce buffer support
18jul06,wap  Add some includes to fix project build
14jul06,wap  Add bounce buffer memory pointer to DMA map structure, move
             DMA tag structure definition here from vxbDmaBufLib.c
29jun06,wap  Add support for address translation
25may06,wap  Add fragment count to map structure
30jan06,pdg  Updated review comments
02Dec05,tor  created from FreeBSD DMA system
*/

/*
DESCRIPTION

This file defines the macros, structures and interfaces which can be used
by the device drivers to support DMA operations.
*/

#ifndef __INCvxbDmaBufBufLibh
#define __INCvxbDmaBufBufLibh

/* includes */
#include <cacheLib.h>
#include <hwif/vxBus.h>

#include <sys/uio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* vxbDmaBufTagCreate flags */

#define VXB_DMABUF_ALLOCNOW		0x00000001  /* (currently no effect) */
#define VXB_DMABUF_NOCACHE		0x00000002  /* uncacheable buffer */
#define VXB_DMABUF_CACHESNOOP_BUS	0x00000004  /* cache-snoop mode bus
						     * This flag is set by
						     * bus controller driver.
						     */
#define VXB_DMABUF_FORCED_BOUNCE 0x00000008  /* forced to use bounce buffer */

/* vxbDmaBufTagCreate flags for VxBus 5.0.0 or later driver */

#define VXB_DMABUF_CACHEALIGNCHECK	0x00000010  /* create a bounce buffer
						     * to be used in
						     * cache-unaligned case
						     */

/* vxbDmaBufMapCreate flags for VxBus 5.0.0 or later driver */

#define VXB_DMABUF_MAPCREATE_NOBOUNCE_BUF \
					0x00000100  /* (internal use by
						     *  vxbDmaBufMemAlloc)
						     */

/*
 * vxbDmaBufMapLoad, vxbDmaBufMapMblkLoad, vxbDmaBufMapIoVecLoad flags
 * for VxBus 5.0.0 or later driver
 */

#define VXB_DMABUF_MAPLOAD_CACHEALIGNCHECK \
					0x00001000  /* enable bounce buffering
						     * in cache-unaligned case
						     */
#define VXB_DMABUF_MAPLOAD_CONTINUE 0x00002000 

/* vxbDmaBufMemAlloc flags */

#define VXB_DMABUF_MEMALLOC_CLEAR_BUF	0x00010000  /* zero clear allocated
						     * buffer
						     */

/* vxbDmaBufSync and vxbDmaBufMapSync options */

#define _VXB_DMABUFSYNC_DMA_PREREAD	0x00000001
#define _VXB_DMABUFSYNC_DMA_POSTREAD	0x00000002
#define _VXB_DMABUFSYNC_DMA_PREWRITE	0x00000004
#define _VXB_DMABUFSYNC_DMA_POSTWRITE	0x00000008

/*
 * vxbDmaBufSync options for backward compatibility
 *
 * The names of the PRE and POST were not correctly defined nor used.
 * New macros above (_VXB_DMABUFSYNC_DMA_XXX) are introduced in VxWorks 6.9
 * as their replacements.
 * Please use the new options for further development.
 */

#define VXB_DMABUFSYNC_PREREAD          (_VXB_DMABUFSYNC_DMA_PREREAD | \
					 _VXB_DMABUFSYNC_DMA_POSTREAD)
#define VXB_DMABUFSYNC_POSTWRITE        _VXB_DMABUFSYNC_DMA_PREWRITE

/* not supported */
#define VXB_DMABUFSYNC_POSTREAD         0x00010000  /* (no effect) */
#define VXB_DMABUFSYNC_PREWRITE         0x00080000  /* (no effect) */

#define VXB_SPACE_MAXADDR_24BIT		0xFFFFFF
#define VXB_SPACE_MAXADDR_32BIT		0xFFFFFFFF
#define VXB_SPACE_MAXADDR_64BIT		0xFFFFFFFFFFFFFFFFULL

#define VXB_SPACE_MAXSIZE_24BIT		VXB_SPACE_MAXADDR_24BIT
#define VXB_SPACE_MAXSIZE_32BIT		VXB_SPACE_MAXADDR_32BIT
#define VXB_SPACE_MAXSIZE_64BIT		VXB_SPACE_MAXADDR_64BIT

#define VXB_SPACE_UNRESTRICTED		(~0)
#define VXB_SPACE_MAXSIZE		VXB_SPACE_UNRESTRICTED

#if defined (_WRS_CONFIG_LP64) || defined (_WRS_CONFIG_IA32_PAE)
#define VXB_SPACE_MAXADDR		VXB_SPACE_MAXADDR_64BIT
#else
#define VXB_SPACE_MAXADDR		VXB_SPACE_MAXADDR_32BIT
#endif /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */

#define VXB_DMA_VIRT_TO_PHYS(adrs) \
	(bus_addr_t) ((ULONG)CACHE_DRV_VIRT_TO_PHYS(&cacheDmaFuncs, adrs))

/* typedefs */

typedef unsigned long		bus_size_t;
typedef UINT64			bus_addr_t;
typedef unsigned long           bus_dmasync_op_t;
typedef void			(bus_dma_filter_t)();
typedef void			(bus_dma_lock_t)();

typedef struct vxbDmaBufTag
    {
    struct vxbDmaBufTag *       pNext;          /* pointer to next tag */
    VXB_DEV_ID                  pInst;          /* instance id */
    struct vxbDmaBufTag *       parent;         /* parent tag */
    BOOL                        vxbTagValid;    /* tag validity flag */
    bus_size_t                  alignment;      /* alignment for segments */
    bus_size_t                  boundary;       /* boundary for segments */
    bus_addr_t                  lowAddr;        /* low restricted address */
    bus_addr_t                  highAddr;       /* high restricted address */
    bus_dma_filter_t *          filter;         /* optional filter function */
    void *                      filterArg;      /* filter function argument */
    bus_size_t                  maxSize;        /* maximum mapping size */
    u_int                       nSegments;      /* number of segments */
    bus_size_t                  maxSegSz;       /* maximum segment size */
    int                         flags;          /* flags */
    int                         refCount;       /* reference count */
    int                         mapCount;       /* map count */
    bus_dma_lock_t *            lockFunc;       /* lock Function */
    void *                      lockFuncArg;    /* lock function argument */
    } VXB_DMA_TAG;

typedef VXB_DMA_TAG * VXB_DMA_TAG_ID;

typedef struct vxbDmaBufFrag VXB_DMA_FRAG;

struct vxbDmaBufFrag
    {
    bus_addr_t		frag;		/* fragment pointer physical address */
    void *		fragVirt;	/* fragment pointer virtual address */
    bus_size_t		fragLen;	/* fragment length */
    };

typedef struct vxbDmaBufMap VXB_DMA_MAP;
typedef struct vxbDmaBufMap * VXB_DMA_MAP_ID;

struct Ipcom_pkt_struct;

struct vxbDmaBufMap
    {
    VXB_DMA_TAG_ID   	dmaTagID;
    VXB_DEV_ID	pParent;	/* Parent device */
    VXB_DEV_ID	pDev;		/* map owner */
    STATUS (*mapLoadFunc)(VXB_DEV_ID,
			  VXB_DMA_TAG_ID,
			  VXB_DMA_MAP_ID,
			  void *,
			  bus_size_t,
			  int);		/* parent bus load func */
    STATUS (*mapUnloadFunc)(VXB_DEV_ID,
			    VXB_DMA_TAG_ID,
			    VXB_DMA_MAP_ID);
					/* parent bus unload func */
    STATUS (*mapSyncFunc)(VXB_DEV_ID,
			  VXB_DMA_TAG_ID,
			  VXB_DMA_MAP_ID,
			  bus_dmasync_op_t);
    STATUS (*mapSyncPartFunc)(VXB_DEV_ID,
			      VXB_DMA_TAG_ID,
			      VXB_DMA_MAP_ID,
                              off_t,
                              size_t,
			      bus_dmasync_op_t);
					/* parent bus sync func */
    void		*pMem;		/* for alignment fixups */
    void		*pMemBounce;	/* for bounce buffering */
    void		*pBounceSaved;	/* for alignment fixups */
    int			nFrags;		/* number of valid frags */
    VXB_DMA_FRAG	fragList[1]; /* list of buffer fragments */
    };

/* globals */

/* function pointers available to be filled in by BSP */

IMPORT void * (*vxbDmaBufBspAlloc)
    (
    VXB_DEV_ID	pInst,
    size_t		size
    );
IMPORT STATUS (*vxbDmaBufBspFree)
    (
    VXB_DEV_ID	pInst,
    void *		vaddr
    );

/* function pointers available to be filled in by arch code */

IMPORT STATUS (*vxbDmaBufArchInvalidate)
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    int			index,
    off_t		offset,
    size_t		length
    );
IMPORT STATUS (*vxbDmaBufArchFlush)
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    int			index,
    off_t		offset,
    size_t		length
    );
IMPORT STATUS (*vxbDmaBufMapArchInvalidate)
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map
    );
IMPORT STATUS (*vxbDmaBufMapArchFlush)
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map
    );

/* locals */

/* forward declarations */

IMPORT void vxbDmaBufInit();

IMPORT VXB_DMA_TAG_ID vxbDmaBufTagParentGet
    (
    VXB_DEV_ID	pInst,
    UINT32 		pRegBaseIndex
    );

IMPORT VXB_DMA_TAG_ID vxbDmaBufTagCreate
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID	parent,
    bus_size_t		alignment,
    bus_size_t		boundary,
    bus_addr_t		lowAddr,
    bus_addr_t		highAddr,
    bus_dma_filter_t *	filter,
    void *		filterArg,
    bus_size_t 		maxSize,
    int 		nSegments,
    bus_size_t 		maxSegSz,
    int 		flags,
    bus_dma_lock_t *	lockFunc,
    void *		lockFuncArg,
    VXB_DMA_TAG_ID *	ppDmaTag
    );

IMPORT STATUS vxbDmaBufTagDestroy
    (
    VXB_DMA_TAG_ID 	dmaTagID
    );

IMPORT VXB_DMA_MAP_ID vxbDmaBufMapCreate
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    int 		flags,
    VXB_DMA_MAP_ID *	pMap
    );

IMPORT STATUS vxbDmaBufMapDestroy
    (
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map
    );

IMPORT void * vxbDmaBufMemAlloc
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    void ** 		vaddr,
    int 		flags,
    VXB_DMA_MAP_ID *	pMap
    );

IMPORT STATUS vxbDmaBufMemFree
    (
    VXB_DMA_TAG_ID 	dmaTagID,
    void *		vaddr,
    VXB_DMA_MAP_ID 	map
    );

IMPORT STATUS vxbDmaBufMapLoad
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    void *		buf,
    bus_size_t 		bufLen,
    int 		flags
    );

IMPORT STATUS vxbDmaBufMapIoVecLoad
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    struct uio *	uio,
    int 		flags
    );

IMPORT STATUS vxbDmaBufMapUnload
    (
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map
    );

IMPORT STATUS vxbDmaBufMapFlush
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map
    );

IMPORT STATUS vxbDmaBufMapInvalidate
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map
    );

IMPORT STATUS vxbDmaBufFlush
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    int			index,
    off_t		offset,
    size_t		length
    );

IMPORT STATUS vxbDmaBufInvalidate
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    int			index,
    off_t		offset,
    size_t		length
    );

IMPORT STATUS vxbDmaBufSync
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    bus_dmasync_op_t 	op
    );

IMPORT STATUS vxbDmaBufMapSync
    (
    VXB_DEV_ID	pInst,
    VXB_DMA_TAG_ID 	dmaTagID,
    VXB_DMA_MAP_ID 	map,
    off_t		offset,
    size_t		length,
    bus_dmasync_op_t 	op
    );

IMPORT STATUS vxbDmaBufFragFill
    (
    VXB_DMA_TAG_ID      dmaTagID,
    VXB_DMA_MAP_ID      map,
    void *              buf,
    bus_size_t          bufLen,
    int                 flags,
    int *               pNSegs,
    void **             ppBounceBufCur
    );

IMPORT void vxbDmaBufInit (void);

#ifndef _WRS_KERNEL
IMPORT void *   cacheDmaMalloc (size_t bytes);
IMPORT STATUS   cacheDmaFree (void * pBuf);
#endif

IMPORT void vxbDmaBufLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbDmaBufBufLibh */
