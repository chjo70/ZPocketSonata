/* buf.h - file system buffer cache interface */

/*
 * Copyright 2005-2006, 2009, 2013 Wind River Systems, Inc
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
01k,02jul13,myt  WIND00424679 - restore all operation to atomic semantic
                 in default mode
01i,19feb13,myt  WIND00402683 - fix incorrect variable type of macro BUFHASH
01h,31jan13,myt  WIND00401852 - buf hash list performance improvement
01g,01jul09,hui  WIND142041 - HRFS performance improvement
01f,23jul06,act  add b_pblkno and file system flags; turn on breadn
01e,27jun06,act  add buf_rebusy (for vnode routines); turn on bdwrite
01d,21jul05,jlk  added BUF_USED_ONCE priority macro
01c,12apr05,act  add a field to hold errors; change buf_done to take a buf and
                 an error
01b,17mar05,act  export buf_done() function
01a,16mar05,act  add buf_initmountpoint prototype
 */

#ifndef __INCbufh
#define __INCbufh

#include "sys/queue.h"
#include "semLib.h"
#include "drv/xbd/bio.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Type-name for "logical block number".  Buffers are named by
 * <vnode, logical block number> pairs, so that a file system that
 * wants to get "block 3" of a file (vnode), you just get <vp,3>.
 * (The block size is up to the user of the buffer code.)
 *
 * This type is also used for "post translation" block numbers
 * (optional, up to the file system) so the name is a little misleading.
 * Note that for BSD compatibility, initially bp->b_pblkno == bp->b_lblkno,
 * so one can use that as a test for "has this been translated yet", but
 * it is better to use the file-system flags.
 */
typedef unsigned long long lblkno_t;	/* ??? signed? */

struct ucred;
struct mount;

LIST_HEAD(bhashhdr, buf);
TAILQ_HEAD(bfreehdr, buf);

/*
 * Note that a buffer can be both free and on a vnode.  This occurs when
 * the buffer is cacheing valid data.
 *
 * Buffers are taken off their free list while "owned", but are always
 * on a hash chain (kept in the mount point) based on their buffer hash
 * value.
 *
 * Each buffer also has an I/O semaphore that is taken when I/O is
 * started, and given only when the I/O is finished.  Thus, if you
 * can get the I/O semaphore, I/O is done (or was never started).
 * The code to start the I/O should always be able to get the semaphore
 * without waiting (otherwise it is a repeated start w/o first finishing).
 *
 * Each buffer has an "availability semaphore.  This semaphore is taken
 * when the buffer is allocated to a task, and given when the buffer is
 * released for other tasks to use.
 *
 * The B_BUSY bit is essentially the same information as in b_avail
 * (it is documented as "I/O in progress", but this is a white lie).
 * Taking b_avail allows a task to wait for B_BUSY to clear.
 *
 * There is some subtlety with async I/O; see bufSubr.c.
 *
 * The b_fsflags field is cleared whenever a buffer is first associated
 * with a vnode, at which point b_pblkno is set equal to b_lblkno.  A
 * file system typically translates b_lblkno to a different underlying
 * physical block number, and is allowed to use b_pblkno as a cache for
 * the resulting translation, with or without a flag in b_fsflags to
 * indicate that the translation has been done:
 *
 *	if ((bp->b_fsflags & FS_DEFINED_VALUE) == 0)
 *	    {
 *	    bp->b_pblkno = SOME_FUNCTION(bp->b_lblkno);
 *	    bp->b_fsflags |= FS_DEFINED_VALUE;
 *	    }
 *
 * or the traditional BSD file system method:
 *
 *	if (bp->b_pblkno == bp->b_lblkno)
 *	    bp->b_pblkno = SOME_FUNCTION(bp->b_lblkno);
 *
 * The former has the advantage of handling the (unusual but possible)
 * case where pblkno==f(lblkno), e.g., logical block 10041 of some
 * vnode just happens to map to physical block 10041 in the file system.
 * The latter still works, it just does "too much" work.
 *
 * The fsflags field can be used for other purposes as well; the file
 * system can "know" that these flags will be zeroed out when the buffer
 * is dis-associated from its old vnode and re-associated with a new one.
 */
struct buf
    {
    SEM_ID           b_mutex;    /* mutex to lock buffer while owned */
    SEM_ID           b_iosem;    /* I/O semaphore (binary sem) */
    SEM_ID           b_avail;    /* availability semaphore */
    int              b_flags;    /* see below */
    int              b_fsflags;  /* reserved to file system */

    /* don't need b_size yet - HRFS buffers are all one size per mount */

    int              b_bsize;    /* size of data */
                                 
    void            *b_data;     /* this buffer's data (shared w/bio) */
    struct bio      *b_bio;      /* ### need more, eventually? */
    int              b_error;    /* error for buf_wait */

    struct vnode    *b_vp;       /* this buffer's vnode */
    lblkno_t         b_lblkno;   /* and its logical block number */
    lblkno_t         b_pblkno;   /* physical (translated) blkno */
                                 
    int              b_priority; /* cache priority */
    LIST_ENTRY(buf)  b_hash;     /* hash chain */
    LIST_ENTRY(buf)  b_vnbufs;   /* chain of buffers on this vnode */
    TAILQ_ENTRY(buf) b_freelist; /* chain if free */
    void            *b_priv;
    };

/*
 * Flags for b_flags.
 *
 * The names are from NetBSD; the bit-value numbers do not match though.
 */
/*	B_AGE				-- move to age queue when I/O done */
#define	B_ASYNC		0x00000001	/* Start I/O, do not wait */
/*	B_BAD				-- bad block revectoring in progress */
#define	B_BUSY		0x00000002	/* I/O in progress */
/*	B_SCANNED			-- already pushed during sync */
/*	B_CALL		0x00000004	-- call b_iodone from buf_done */
#define	B_DELWRI	0x00000008	/* buffer has delayed-write data */
/*	B_DIRTY				-- dirty page (VM system info, n/a) */
#define	B_DONE		0x00000010	/* I/O completed */
#define	B_EINTR		0x00000020	/* I/O was interrupted (for NFS) */
#define	B_ERROR		0x00000040	/* I/O error occurred */
/*	B_GATHERED	0x00000080	-- LFS: already in a segment */
#define	B_INVAL		0x00000100	/* does not contain valid info */
/*	B_LOCKED			-- locked in core (not reusable) */
/*	B_NOCACHE			-- do not cache block after use */
/*	B_CACHE				-- bread() found us in the cache */
/*	B_PHYS				-- I/O to user space */
/*	B_RAW				-- set by physio() for raw transfers */
#define	B_READ		0x00000200	/* read buffer */
/*	B_TAPE				-- magnetic tape I/O */
/*	B_WANTED			-- process wants this buffer */
#define	B_WRITE		0x00000400	/* write buffer */
/*	B_XXX				-- debugging flag */
/*	B_VFLUSH			-- buffer is being synced */
#define B_PRIVATE   0x00000800   /* this buffer has private data */
#define B_INTRANS   0x00001000 /* HRFS: already in the transaction */

/*
 * Buffer caching "levels" (priorities).  A buffer that contains some
 * valid data goes on one of the "higher-level" queues, in LRU fashion,
 * by putting released buffers at the end of the queue and taking
 * buffers off the front of the queue.
 *
 * The ones in the "trash" queue by definition have no valid data
 * (the code itself does not really need this distinction at the
 * moment, but it seems reasonable to keep it).
 */
#define	BUF_TRASH	0	/* "trash" queue: no valid data */
#define	BUF_USED_ONCE	1	/* blocks that are used just once */
#define	BUF_ORDINARY	2	/* ordinary data/transactions */
#define	BUF_META_LOW	3	/* low priority metadata */
#define	BUF_META_HIGH	4	/* high priority metadata */
#define	BUF_TRANS	    5	/* high priority metadata */
#define BUF_NQUEUES	    6	/* number of free-list queues */

#define	buf_setpriority(bp, pri) ((bp)->b_priority = (pri))

/*
 * Buffer hashing, per mount-point.  This hash function probably needs
 * tuning.  Note that the current BUFHASH definition depends on BHSIZE
 * being a power of two.
 */
#define BUF_BHSIZE 32
#define BUFHASHSIZE(nbuf)  (((nbuf) < BUF_BHSIZE) ? BUF_BHSIZE : (nbuf))
#define BUFHASH(vp, lbn) \
	(((((ULONG)(vp) >> 8) + (UINT)(lbn))) % vp->v_mount->mnt_nbufs)
	

void	buf_initmountpoint(struct mount *, int numBufs);
int	buf_makebuffers(struct mount *, int, int, struct bio *);
void	buf_deletebuffers(struct mount *, int numBufs);

/*
 * getblk() is BSD-compatible, except that we ignore the two "unused"s
 * (so they had better always be 0!  in BSD they control sleep() behavior).
 *
 * bread() does a getblk() and then reads the underlying data if the
 * block was not already in cache.  bwrite() writes the data, and there
 * are several variations on the theme.  In general, once you getblk()
 * or bread(), you own that <vnode,lbn> pair until you brelse() or
 * bwrite() it to give it back.
 *
 * For file systems that move underlying data, we provide buf_moveblk(),
 * to move a buffer (which you must own) from one <vp,lbn> pair to
 * another.  The new vnode may be the same as the old one.  It is OK to
 * move the lbn to a cached LBN (this just invalidates the old cached
 * copy) -- it has to be, since the caller can't tell which LBNs are
 * cached -- but it is an error to move it to a <vp,lbn> pair that is
 * currently both cached and owned.  (This means you have a bug in your
 * file system, since you think you are working with that <vp,lbn> pair
 * on behalf of this task or some other task.)  In this case you will
 * get EBUSY as a return value.  (??? maybe we should just panic?)
 *
 * Both vnodes must be on the same mount point (if not, you get an
 * error, again).
 *
 * We also provide buf_swapdata, which simply swaps the underlying
 * data of two buffers (you must own both) without even looking at
 * anything else.
 */
struct buf *buf_getblk(struct vnode *, lblkno_t, int);
int	buf_rebusy(struct buf *, struct vnode *);
int	buf_moveblk(struct buf *, struct vnode *, lblkno_t);
void	buf_swapdata(struct buf *, struct buf *);

#define getblk(vp, lbn, size, unused1, unused2) buf_getblk(vp, lbn, size)

int	bread(struct vnode *, lblkno_t, int, struct ucred *, struct buf **);
#ifdef notyet
int	breada(struct vnode *, lblkno_t, int, lblkno_t, int,
		struct ucred *, struct buf **);
#endif
int	breadn(struct vnode *, lblkno_t, int, lblkno_t *, int *, int,
		struct ucred *, struct buf **);
int	bwrite(struct buf *);	/* write block, wait for result */
void	buf_startwrite(struct buf *); /* begin write; caller still owns buf */
void	bdwrite(struct buf *);	/* delayed write: write after timeout */
void	bawrite(struct buf *);	/* async write: start write but don't wait */
void	brelse(struct buf *);	/* release buffer to free list, no I/O */
int	buf_wait(struct buf *);	/* wait for I/O, and return errno (0=OK) */
void	buf_done(struct buf *, int);
void	buf_invalid(struct vnode *vp);

#ifdef __cplusplus
}
#endif

#endif /* __INCbufh */
