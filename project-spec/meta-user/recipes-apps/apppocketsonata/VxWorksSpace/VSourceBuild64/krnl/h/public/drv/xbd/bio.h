/* bio.h - Block I/O Transaction Header File */

/*
 * Copyright (c) 2004-2006, 2008-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01l,08oct13,ghs  Remove incorrect definition (WIND00437841)
01k,30nov12,w_x  add code to support xbd sched policy 
01j,15aug11,zly  fix for WIND00201989:xbd priority inversion issue. 
01i,29apr10,pad  Moved extern C statement after include statements.
01h,24jul09,lyc  Romove warning for LP64 support
01g,10jul09,lyc  LP64 support
01f,10jul08,hui  fixed WIND126983 - VX_TO_DISK_32 define error
01e,12apr06,dee  SPR 119990, WIND00037359 - add cplusplus construct
01d,07mar05,rfr  Added NULLSECTOR constant
01c,10feb05,rfr  Added bio_alloc and bio_free.
01b,10feb05,rfr  Changed block_t to sector_t
01a,03feb05,rfr  Added global initialization function.
*/

#ifndef __INCbioh
#define __INCbioh

#include <drv/manager/device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef long long sector_t;             /* a block index */
typedef	unsigned long block_t ;	        /* block number */
typedef	unsigned long cookie_t ;        /* opaque cookie */


#define NULLSECTOR -1L

#define BIO_READ 0x0001
#define BIO_WRITE 0x0002
#define BIO_CACHE_BYPASS 0x0004
#define BIO_CACHE_FLUSH  0x0008

/* Move from cbioLib.h to bio.h for compatibility */
/* Will be moved to new location in future */
#define	CBIO_RESET              0xcb100000      /* Reset device */
#define	CBIO_STATUS_CHK         0xcb100001      /* check device status */
#define	CBIO_DEVICE_LOCK        0xcb100002      /* Prevent disk removal */
#define	CBIO_DEVICE_UNLOCK      0xcb100003      /* Allow disk removal */
#define	CBIO_DEVICE_EJECT       0xcb100004      /* Dismount device */
#define	CBIO_CACHE_FLUSH        0xcb100010      /* Flush dirty caches */
#define	CBIO_CACHE_INVAL        0xcb100030      /* Flush & Invalidate all */
#define	CBIO_CACHE_NEWBLK       0xcb100050      /* Allocate scratch block */

#define CBIO_DELETE             0xcb100060      /* Delete a Block from underlying layers */

#define CBIO_TRANS_COMMIT       0xcb100070      /* Commit a transaction */
#define CBIO_TRANS_FORMAT       0xcb100071      /* Format a transaction device */
#define CBIO_TRANS_DEFRAG       0xcb100072      /* defrag a transaction device for use as DOS FAT */
#define CBIO_TRANS_ROLLBACK     0xcb100073      /* rollback to last transaction point */

/* endian swap */

#define DISK_TO_VX_32( pSrc )    (UINT32)(                     \
                     ( *((u_char *)(pSrc)+3)<<24 ) |           \
                     ( *((u_char *)(pSrc)+2)<<16 ) |           \
                     ( *((u_char *)(pSrc)+1)<< 8 ) |           \
                     ( *(u_char *)(pSrc)         ) )

#define VX_TO_DISK_16( src, pDst )                             \
            ( * (u_char *)(pDst)       = (src)       & 0xff,   \
              *((u_char *)(pDst) + 1)  = ((src)>> 8) & 0xff )

#define VX_TO_DISK_32( src, pDst )                             \
            ( * (u_char *)(pDst)       = (u_char)((src)        & 0xff),  \
              *((u_char *)(pDst) + 1)  = (u_char)(((src)>> 8)  & 0xff),  \
              *((u_char *)(pDst) + 2)  = (u_char)(((src)>> 16) & 0xff),  \
              *((u_char *)(pDst) + 3)  = (u_char)(((src)>> 24) & 0xff) ) 

struct xbd;
struct bio;

#define BIO_IOSCHED_DIRECTIO (1 << 1)
#define BIO_IOSCHED_ALLOWED  (1 << 2)
#define BIO_IOSCHED_QUEUABLE (1 << 3)

struct bio {
    device_t bio_dev;		/* The allocator of this bio */
    sector_t bio_blkno;		/* The Block Number of this bio */
    unsigned bio_bcount;	/* Total number of bytes in this segment */
    void *bio_data;		    /* bio_bcount bytes of data */
    unsigned bio_resid;		/* Residual count for this segment */
    unsigned bio_error;		/* Error code for this segment */
    unsigned bio_flags;		/* Flags. At least BIO_READ and BIO_WRITE */
	int bio_priority;       /* priority of the task which inserted the bio */
    void (*bio_done)(struct bio *); /* Completion function for this segment */
    void *bio_caller1;		/* Caller supplied data */
    struct bio *bio_chain;	/* The next segment or NULL */
    void * bio_context;     /* Xfer Context */
};

STATUS bioInit(void);

void bio_done(struct bio *, int);

void *bio_alloc(device_t, int);
void bio_free(void *);

#ifdef __cplusplus
}
#endif

#endif /* __INCbioh */
