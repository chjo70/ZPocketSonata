/* lockfP.h - POSIX lockf() internals */

/* Copyright 2006 Wind River Systems, Inc */

/*
modification history
--------------------
01b,23apr06,pcm  added extern to _func_lf_advlock and lf_advlock (SPR 120291)
01a,12jan06,act  fix name, it is in fact lockfP.h
*/

/*
 *	NetBSD: lockf.h,v 1.15 2004/04/25 16:42:43 simonb Exp
 *
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Scooter Morris at Genentech Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)lockf.h	8.2 (Berkeley) 10/26/94
 */

#ifndef __INClockfPh
#define __INClockfPh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The lockf structure is a kernel structure which contains the information
 * associated with a byte range lock.  There is one per lock per task.
 * These are linked into the vnode (in several ways, vp->v_lfhead is all
 * locks on the vnode and vp->v_lfbq is all "locks that are currently
 * blocking another lock" on that vnode).
 *
 * Locks are sorted by the starting byte of the lock for efficiency.
 *
 * lf_next is used for two purposes, depending on whether the lock is
 * being held, or is in conflict with an existing lock.  If this lock
 * is held, it indicates the next lock on the same vnode.
 * For pending locks, if lock->lf_next is non-NULL, then lock->lf_block
 * must be queued on the lf_blkhd TAILQ of lock->lf_next.
 */

TAILQ_HEAD(locklist, lockf);

struct lockf {
	SEM_ID	lf_blocksem;	/* semaphore on which to wait for wake */
	short	lf_flags;	/* see below */
	short	lf_type;	/* Lock type: F_RDLCK, F_WRLCK */
	voff_t	lf_start;	/* The byte # of the start of the lock */
	voff_t	lf_end;		/* The byte # of the end of the lock (-1=EOF)*/
	void	*lf_task;	/* task that created this lock */
	void	*lf_id;		/* lock identifier (from VOP_ADVLOCK) */
	struct	lockf **lf_head;/* Back pointer to the head of lockf list */
	struct	lockf *lf_next;	/* Next lock on this vnode, or blocking lock */
	struct  locklist lf_blkhd;  /* List of requests blocked on this lock */
	TAILQ_ENTRY(lockf) lf_block;/* A request waiting for a lock */
	LIST_ENTRY(lockf) lf_bq;/* list of all blocked locks on a vnode */
};

/*
 * Flags for lf_flags.
 * Note that the first several are actually in sys/fcntlcom.h.
 * F_RDLCK, F_WRLCK, and F_UNLCK are arguments to lockf().
 */
/*	F_RDLCK		1	-- shared or read lock */
/*	F_WRLCK		2	-- write lock */
/*	F_UNLCK		3	-- remove lock */
/*	F_UNLKSYS	4	-- remove remote locks for a given system */
#define	F_WAIT		0x10	/* wait until lock is granted */
#define	F_FLOCK		0x20	/* BSD semantics for lock (not used yet) */
#define	F_POSIX		0x40	/* POSIX semantics for lock */

extern int lf_advlock (struct vnode *, void *, int, struct flock *,
                       voff_t, int);

extern int (*_func_lf_advlock) (struct vnode *, void *, int, struct flock *,
                                voff_t, int);

#ifdef __cplusplus
}
#endif

#endif /* __INClockfPh */
