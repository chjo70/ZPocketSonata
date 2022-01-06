/* vnode.h - vnode interface */

/*
 * Copyright 2005-2007, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16jun15,yjl  Updated FIOPATHCONF handling for Big Endian LP64 (V7RAD-155)
11jun07,jlk  SMP work
25jul06,act  add vinvalbuf() prototype; vflushbuf() now returns an errno
06jul06,act  add vflushbuf() prototype
27jun06,act  add vpurgebufs
05may06,pcm  removed commented out ino_t typedef
08nov05,jlk  SPR 113295 fixed race condition during lookup
04jan06,act  add POSIX file locking
21nov05,md   make struct vnode_ops a const
08nov05,jlk  SPR 113295 fixed race condition during lookup
07oct05,md   add defines for POSIX
22jul05,jlk  removed IO_* macros. Updated readdir macros, prototypes to use
             struct dirent * instead of struct uio *.
21jul05,act  change IO_* to VNIO_* to avoid clashes with ioQLib.h
20jul05,act  add vaccess()
04jul05,jlk  added macros to upgrade and downgrade vnode locks
13jun05,act  add VRENAME vnode flag
16apr05,act  don't need vop_error_link_eisdir
16apr05,act  add vopErrorENOTDIR and vopErrorEISDIR functions
15apr05,act  rm v_size, which is not being used
13apr05,act  add struct ucred
12apr05,act  vop_strategy and vop_print should return void
12apr05,act  can't have a generic "error rename", supply a specific one
             instead
05apr05,act  put one cookie back into readdir vop
04apr05,act  remove cookies args from VOP_READDIR
30mar05,act  simplify various vnode ops by not requiring unlocking
30mar05,act  VOP_CREATE is simpler if it leaves dvp locked
25feb05,act fixed several VOP macros; added prototype for vattr_null
23feb05,pcm added vop_error_open()
*/

#ifndef __INCvnodeh
#define __INCvnodeh

/* from	$NetBSD: vnode.h,v 1.126 2004/09/21 03:10:35 thorpej Exp $	*/

/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	@(#)vnode.h	8.17 (Berkeley) 5/20/95
 */

#include <vxWorks.h>
#include <sys/queue.h>
#include <semLib.h>
#include <time.h>
#include <dirent.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef notyet
struct namecache;
#endif
struct componentname;
struct uio;
struct ucred;
struct vattr;
struct flock;
struct lockf;

typedef int64_t voff_t;

/*
 * The vnode is the focus of all file activity.  There is a
 * unique vnode allocated for each active file (plus one for
 * file-system-metadata).
 *
 * Unlike the BSDs, vnodes are allocated per mount, so vnodes never
 * need to move from one file system type to another.
 */

/*
 * Vnode hashing, per mount-point.  This hash function probably needs
 * tuning.  Note that the current VN_HASH definition depends on VN_VHSIZE
 * being a power of two.
 */
#define VN_VHSIZE 32
#define VN_HASH(ino) ((ino) & (VN_VHSIZE - 1))

/*
 * Vnode types.  VNON means no type.  We may not need VBAD, and
 * the block, character, link, socket, and fifo types are named
 * only for BSD compatibility.
 */
enum vtype { VNON, VREG, VDIR, VBLK, VCHR, VLNK, VSOCK, VFIFO, VMETA, VBAD };

LIST_HEAD(buflists, buf);

/*
 * Reading or writing any of these items requires holding the appropriate lock.
 * v_freelist is locked by the mount point's vnode hash chain lock
 * v_flag, v_usecount, v_holdcount and v_writecount are
 *	locked by the v_interlock simple lock
 *
 * Each underlying filesystem has its own private area for v_data.
 *
 * Unlike BSD vnodes, ours have an inode number attached at all times.
 * This is the same as the number that will be used in the vfs_vget operation
 * (see mount.h).  Vnodes can cache inode data by inode number.  For a
 * vnode that does not correspond to an ordinary file in the file system,
 * use VNOINODE.
 *
 * Similarly, all vnodes always have a working vnode lock, locked
 * with VN_EXLOCK (exclusive lock) or VN_SHLOCK (shared lock) and
 * unlocked with VN_UNLOCK.  (Upgrade/downgrade is not yet implemented
 * and VN_SHLOCK is currently an exclusive lock.)  There is no VOP_LOCK
 * nor VOP_UNLOCK as vnodes do not stack.
 */
struct vnode {
	SEM_ID		v_interlock;
	SEM_ID		v_alloclock;
	int		v_flag;			/* flags */
	atomic_t	v_numoutput;		/* number of pending writes */
	SEM_ID		v_output_active;	/* binary sem for numout==0 */
	long		v_usecount;		/* reference count of users */
	long		v_writecount;		/* reference count of writers */
	long		v_holdcnt;		/* page & buffer references */
	ino_t		v_inode;		/* inode number, or 0 */
	struct mount	*v_mount;		/* ptr to vfs we are in */
	const struct vnode_ops *v_ops;		/* vnode operations */
	TAILQ_ENTRY(vnode) v_freelist;		/* vnode freelist */
	LIST_ENTRY(vnode) v_hash;		/* hash chain */
	struct buflists v_cleanblkhd;		/* clean blocklist head */
	struct buflists v_dirtyblkhd;		/* dirty blocklist head */
	LIST_ENTRY(vnode) v_synclist;		/* vnodes with dirty buffers */
#ifdef notyet
	LIST_HEAD(, namecache) v_dnclist;	/* namecaches for children */
	LIST_HEAD(, namecache) v_nclist;	/* namecaches for parent */
#endif
	enum vtype	v_type;			/* vnode type */
#ifdef notyet /* don't have read/writer locks yet */
	struct lock	v_lock;			/* lock for this vnode */
#else
	SEM_ID		v_lock;
#endif
	struct lockf	*v_lfhead;		/* lockf() list head */
	LIST_HEAD(, lockf) v_lfbq;		/* lcokf() blocked-locks */

	/*
	 * Per-file-system data.  This is actually variable length,
	 * allocated when you instantiate a file system and its
	 * "struct mount" and so forth, according to the size you
	 * give for the file system module.
	 */
	union {
		char	v_data[1];		/* vnode data */
		/* these merely force v_data to be aligned */
		long	v_un_long;
		long long v_un_llong;
		void	*v_un_ptr;
	} v_data_un;
};
#define VTODATA(type, vp) ((type *)((vp)->v_data_un.v_data))

/* inode number for "not a file" vnodes */
#define VNOINODE ((ino_t)0)

/*
 * Vnode flags.
 * 
 * Many of these (commented out) are not used in vxWorks.
 * We add VRUNNING to distinguish between "vnode that is being
 * initialized" and "vnode that has finished initializing".
 * We add VRENAME to mark a directory that is being renamed
 * (it cannot be held locked, but only one rename should be
 * allowed to proceed at a time).
 */
#define	VROOT		0x0001	/* root of its file system */
/*	VTEXT		0x0002	-- vnode is a pure text prototype */
#define	VRUNNING	0x0002	/* vnode is up and running */
	/* VSYSTEM only used to skip vflush()ing quota files */
/*	VSYSTEM		0x0004	-- vnode being used by kernel */
	/* VISTTY used when reading dead vnodes */
/*	VISTTY		0x0008	-- vnode represents a tty */
/*	VEXECMAP	0x0010	-- vnode has PROT_EXEC mappings */
/*	VLOCKSWORK	0x0080	-- FS supports locking discipline */
/*	VXLOCK		0x0100	-- vnode is locked to change underlying type */
#define	VRENAME		0x0100	/* vnode is being rename()d */
/*	VXWANT		0x0200	-- process is waiting for vnode */
/*	VBWAIT		0x0400	-- waiting for output to complete */
/*	VALIASED	0x0800	-- vnode has an alias */
/*	VDIROP		0x1000	-- LFS: vnode is involved in a directory op */
/*	VLAYER		0x2000	-- vnode is on a layer filesystem */
#define	VONWORKLST	0x4000	/* On syncer work-list */
/*	VDIRTY		0x8000	-- vnode possibly has dirty pages */

/*
 * Vnode operations.
 *
 * BSD computes the set of operations at boot time; we do not need this
 * and just have this fixed set.
 * 
 * For each op's vnodes, we include a specification of the locking
 * protocol for that operation.  The three columns are in, out, and error
 * respectively.  The "in" column defines the lock state on input, the
 * "out" column defines the state on successful return, and the "error"
 * column defines the state on error exit.
 *
 * The locking value can take the following values:
 * 	L: locked
 * 	U: unlocked
 * 	-: not applicable, vnode does not yet (or no longer) exists
 * 	=: the same on input and output, may be either L or U
 * 	X: locked if not nil.
 *
 * The lookup operation defies simple description, however.  Its lock
 * state depends on the flags and operations fields in the (cnp) structure.
 * Note especially that *vpp may equal dvp and both may be locked.
 *
 * There are three types of lookups: ".", ".." (ISDOTDOT), and other.
 * On successful lookup of ".", a reference is added to dvp, and it
 * 	is returned in *vpp.
 * To look up ISDOTDOT, dvp is unlocked, the ".." node is locked, and
 * 	then dvp is relocked iff LOCKPARENT is set and this is the last
 * 	component name (ISLASTCN set).  This preserves the protocol of
 * 	always locking nodes from the root ("/") downward and prevents
 * 	deadlock.
 * Other lookups find the named node (creating the vnode if needed) and
 * 	return it, locked, in *vpp.
 * For non-"." lookups, if LOCKPARENT is not set or this was not the
 * 	last component name, dvp is returned unlocked on a successful
 * 	lookup.
 * On failure, *vpp is NULL, and *dvp is left locked or unlocked (as
 * 	desired by the file system).
 *
 * All of this is relaxed inside actual file systems, which merely need
 * to return successful new vnodes locked in *vpp (handling "." by increasing
 * the reference count), or setting the PDIRUNLOCK flag if dvp has been
 * unlocked.  If the file system leaves dvp locked but the lookup operation
 * does not need dvp locked, the lookup code will unlock it; if the file
 * system has unlocked dvp for ISDOTDOT purposes, it can leave it unlocked
 * and just set PDIRUNLOCK.
 * 
 * In other words: if you are implementing a file system, you must handle
 * "." and ".." specially (by returning with *vpp = dvp in the first case,
 * after increasing the reference count, and by unlocking dvp before going
 * up the tree in the second case).  You must also set PDIRUNLOCK if you
 * return with dvp unlocked.  Other than that, you should just leave dvp
 * locked.
 */
struct vnode_ops {
	int (*vop_lookup)(
		struct vnode *dvp,	/* L ? ? */
		struct vnode **vpp,	/* - L - */
		struct componentname *cnp
	);
	int (*vop_create)(
		struct vnode *dvp,	/* L L L */
		struct vnode **vpp,	/* - L - */
		struct componentname *cnp, /* cnp flags: CREATE, LOCKPARENT */
		struct vattr *vap
	);
	int (*vop_open)(
		struct vnode *vp,	/* L L L */
		int mode,
		struct ucred *cred
	);
	int (*vop_close)(
		struct vnode *vp,	/* L L L */
		int fflag,
		struct ucred *cred
	);
	int (*vop_access)(
		struct vnode *vp,	/* L L L */
		int mode,
		struct ucred *cred
	);
	int (*vop_getattr)(
		struct vnode *vp,	/* = = = */
		struct vattr *vap,
		struct ucred *cred
	);
	int (*vop_setattr)(
		struct vnode *vp,	/* L L L */
		struct vattr *vap,
		struct ucred *cred
	);
	int (*vop_read)(
		struct vnode *vp,	/* L L L */
		struct uio *uio,
		int ioflag,
		struct ucred *cred
	);
	int (*vop_write)(
		struct vnode *vp,	/* L L L */
		struct uio *uio,
		int ioflag,
		struct ucred *cred
	);
	int (*vop_ioctl)(
		struct vnode *vp,	/* L L L */
		u_long command,
		void *data,
		int fflag,
		struct ucred *cred
	);
	int (*vop_fcntl)(
		struct vnode *vp,	/* L L L */
		u_int command,
		void *data,
		int fflag,
		struct ucred *cred
	);
	int (*vop_fsync)(
		struct vnode *vp,	/* L L L */
		struct ucred *cred,
		int flags
	);
	int (*vop_seek)(
		struct vnode *vp,	/* ? ? ? */
		voff_t oldoff,
		voff_t newoff,
		struct ucred *cred
	);
	int (*vop_remove)(
		struct vnode *dvp,	/* L L L */
		struct vnode *vp,	/* L L L */
		struct componentname *cnp /* DELETE, LOCKPARENT | LOCKLEAF */
	);
	int (*vop_link)(
		struct vnode *dvp,	/* L L L */
		struct vnode *vp,	/* U U U */
		struct componentname *cnp /* CREATE, LOCKPARENT */
	);
	int (*vop_rename)(
		struct vnode *fdvp,	/* U U U */
		struct vnode *fvp,	/* U U U */
		struct componentname *fcnp, /* DELETE, WANTPARENT | SAVESTART */
		struct vnode *tdvp,	/* L U U */
		struct vnode *tvp,	/* X U U */
		struct componentname *tcnp /* RENAME, LOCKPARENT | LOCKLEAF | NOCACHE | SAVESTART */
		/* XXX the vop_rename routines should REALLY NOT be depending on SAVESTART! */
	);
	int (*vop_mkdir)(
		struct vnode *dvp,	/* L L L */
		struct vnode **vpp,	/* - L - */
		struct componentname *cnp, /* CREATE, LOCKPARENT */
		struct vattr *vap
	);
	int (*vop_rmdir)(
		struct vnode *dvp,	/* L L L */
		struct vnode *vp,	/* L L L */
		struct componentname *cnp /* DELETE, LOCKPARENT | LOCKLEAF */
	);
	int (*vop_symlink)(
		struct vnode *dvp,	/* L L L */
		struct vnode **vpp,	/* - L - */
		struct componentname *cnp, /* CREATE, LOCKPARENT */
		struct vattr *vap,
		char *target
	);
	int (*vop_readdir)(
		struct vnode *vp,	/* L L L */
		struct dirent *direntp,
		struct ucred *cred,
		int *eofflag,
		int *cookie		/* really, FS-level seek offset */
	);
	int (*vop_readlink)(
		struct vnode *vp,	/* L L L */
		struct uio *uio,
		struct ucred *cred
	);
	int (*vop_abortop)(
		struct vnode *dvp,	/* = = = */
		struct componentname *cnp /* flags per op being aborted */
	);
	int (*vop_activate)(
		struct vnode *vp	/* L L L */
	);
	int (*vop_inactive)(
		struct vnode *vp	/* L L L */
	);
#if 0
	int (*vop_lock)(
		struct vnode *vp	/* U L U */
	);
	int (*vop_unlock)(
		struct vnode *vp	/* L U L */
	);
#endif
	void (*vop_strategy)(
		struct vnode *vp,	/* = = = */
		struct buf *bp
	);
	void (*vop_print)(
		struct vnode *vp	/* = = = */
	);
	int (*vop_pathconf)(
		struct vnode *vp,	/* L L L */
		long name,
		long *retval
	);
	int (*vop_advlock)(
		struct vnode *vp,	/* U U U */
		void *id,
		int op,
		struct flock *fl,
		int flags
	);
	int (*vop_truncate)(
		struct vnode *vp,	/* L L L */
		voff_t length,
		int flags,
		struct ucred *ucred
	);
};

/*
 * Vnode attributes.  A field value of VNOVAL represents a field whose value
 * is unavailable (getattr) or which is not to be changed (setattr).
 */
struct vattr {
	enum vtype	va_type;	/* vnode type (for create) */
	mode_t		va_mode;	/* file access mode and type */
	nlink_t		va_nlink;	/* number of references to file */
	uid_t		va_uid;		/* owner user id */
	gid_t		va_gid;		/* owner group id */
	long		va_fsid;	/* file system id (dev for now) */
	uint64_t	va_fileid;	/* file id */
	uint64_t	va_size;	/* file size in bytes */
	long		va_blocksize;	/* blocksize preferred for i/o */
	struct timespec	va_atime;	/* time of last access */
	struct timespec va_mtime;	/* time of last modification */
	struct timespec va_ctime;	/* time file changed */
	struct timespec va_birthtime;	/* time file created */
	u_long		va_gen;		/* generation number of file */
	u_long		va_flags;	/* flags defined for file */
	dev_t		va_rdev;	/* device the special file represents */
	uint64_t	va_bytes;	/* bytes of disk space held by file */
	uint64_t	va_filerev;	/* file modification number */
	u_int		va_vaflags;	/* operations flags, see below */
	long		va_spare;	/* remain quad aligned */
};

/*
 * Flags for va_vaflags.
 */
#define	VA_UTIMES_NULL	0x01		/* utimes argument was NULL */
#define	VA_EXCLUSIVE	0x02		/* exclusive create request */

/*
 * Flags for ioflag (read/write vnode ops).
 */
#define	VNIO_UNIT	0x01		/* do I/O as atomic unit */
#define	VNIO_APPEND	0x02		/* append write to end */
#define	VNIO_SYNC   (0x04|VNIO_DSYNC)	/* sync I/O file integrity completion */
#define	VNIO_NODELOCKED	0x08		/* underlying node already locked */
#define	VNIO_NDELAY	0x10		/* FNDELAY flag set in file table */
#define	VNIO_DSYNC	0x20		/* sync I/O data integrity completion */
#define	VNIO_RSYNC	0x40		/* sync read operations at same level */
#define	VNIO_ALTSEMANTICS 0x80		/* use alternate i/o semantics */

/*
 * Modes for vaccess() (fifth argument).
 */
#define	VREAD	0004		/* read, write, execute permissions */
#define	VWRITE	0002
#define	VEXEC	0001

/*
 * Token indicating no attribute value yet assigned.
 */
#define	VNOVAL	(-1)

/*
 * Flags to various vnode functions.
 *	XXX DON'T KNOW IF WE NEED MOST OF THESE
 */
/*efine	SKIPSYSTEM	0x0001		-- vflush: skip vnodes marked VSYSTEM */
#define	FORCECLOSE	0x0002		/* vflush: force file closeure */
#define	WRITECLOSE	0x0004		/* vflush: only close writeable file */
#define	DOCLOSE		0x0004		/* vclean: close active files */
#define	V_SAVE		0x0001		/* vinvalbuf: sync file first */

/*
 * Flags to various vnode operations.
 */
#define	FSYNC_WAIT	0x0001		/* fsync: wait for completion */
#define	FSYNC_DATAONLY	0x0002		/* fsync: hint: sync file data only */
#define	FSYNC_RECLAIM	0x0004		/* fsync: hint: vnode is being reclaimed */
#define	FSYNC_LAZY	0x0008		/* fsync: lazy sync (trickle) */

#define	UPDATE_WAIT	0x0001		/* update: wait for completion */
#define	UPDATE_DIROP	0x0002		/* update: hint for fs to wait or not */
#define	UPDATE_CLOSE	0x0004		/* update: clean up on close */

#define	VPURGE_CLEAN	1		/* vpurge: purge clean buffers */
#define	VPURGE_DIRTY	2		/* vpurge: purge dirty buffers */

/* hold/holdrele should not appear outside vnodeSubr.c */
/* #define	HOLDRELE(vp)	holdrele(vp) */
/* #define	VHOLD(vp)	vhold(vp) */

#define	VREF(vp)	vref(vp)

/*
 * Get shared or exclusive lock on vnode.  Currently shared locks are
 * actually exclusive.
 */
#define	VN_SHLOCK(vp)	semTake((vp)->v_lock, WAIT_FOREVER)
#define	VN_EXLOCK(vp)	semTake((vp)->v_lock, WAIT_FOREVER)
#define	VN_UNLOCK(vp)	semGive((vp)->v_lock)
/*
 * These macros upgrade from a shared lock to an exclusive locks and downgrade
 * from an exclusive lock to a shared lock. Currently, as there's no difference
 * in lock types they do nothing.
 */
#define	VN_UPLOCK(vp)
#define	VN_DOWNLOCK(vp)

/*
 * File system operations.
 */
#define	VOP_LOOKUP(dvp, vpp, cnp) \
		((dvp)->v_ops->vop_lookup(dvp, vpp, cnp))
#define	VOP_CREATE(dvp, vpp, cnp, vap) \
		((dvp)->v_ops->vop_create(dvp, vpp, cnp, vap))
#define	VOP_OPEN(vp, mode, cred) \
		((vp)->v_ops->vop_open(vp, mode, cred))
#define	VOP_CLOSE(vp, fflag, cred) \
		((vp)->v_ops->vop_close(vp, fflag, cred))
#define	VOP_ACCESS(vp, mode, cred) \
		((vp)->v_ops->vop_access(vp, mode, cred))
#define	VOP_GETATTR(vp, vap, cred) \
		((vp)->v_ops->vop_getattr(vp, vap, cred))
#define	VOP_SETATTR(vp, vap, cred) \
		((vp)->v_ops->vop_setattr(vp, vap, cred))
#define	VOP_READ(vp, uio, ioflag, cred) \
		((vp)->v_ops->vop_read(vp, uio, ioflag, cred))
#define	VOP_WRITE(vp, uio, ioflag, cred) \
		((vp)->v_ops->vop_write(vp, uio, ioflag, cred))
#define	VOP_IOCTL(vp, cmd, data, fflag, cred) \
		((vp)->v_ops->vop_ioctl(vp, cmd, data, fflag, cred))
#define	VOP_FCNTL(vp, cmd, data, fflag, cred) \
		((vp)->v_ops->vop_fcntl(vp, cmd, data, fflag, cred))
#define	VOP_FSYNC(vp, cred, flags) \
		((vp)->v_ops->vop_fsync(vp, cred, flags))
#define	VOP_SEEK(vp, oldoff, newoff, cred) \
		((vp)->v_ops->vop_seek(vp, oldoff, newoff, cred))
#define	VOP_REMOVE(dvp, vp, cnp) \
		((dvp)->v_ops->vop_remove(dvp, vp, cnp))
#define	VOP_LINK(dvp, vp, cnp) \
		((dvp)->v_ops->vop_link(dvp, vp, cnp))
#define	VOP_RENAME(fdvp, fvp, fcnp, tdvp, tvp, tcnp) \
		((fdvp)->v_ops->vop_rename(fdvp, fvp, fcnp, tdvp, tvp, tcnp))
#define	VOP_MKDIR(dvp, vpp, cnp, vap) \
		((dvp)->v_ops->vop_mkdir(dvp, vpp, cnp, vap))
#define	VOP_RMDIR(dvp, vp, cnp) \
		((dvp)->v_ops->vop_rmdir(dvp, vp, cnp))
#define	VOP_SYMLINK(dvp, vpp, cnp, vap, target) \
		((dvp)->v_ops->vop_symlink(dvp, vpp, cnp, vap, target))
#define	VOP_READDIR(vp, direntp, cred, eofflag, cookie) \
		((vp)->v_ops->vop_readdir(vp, direntp, cred, eofflag, cookie))
#define	VOP_READLINK(vp, uio, cred) \
		((vp)->v_ops->vop_readlink(vp, uio, cred))

#define	VOP_PATHCONF(vp, name, retval) \
		((vp)->v_ops->vop_pathconf(vp, name, retval))
#define	VOP_ADVLOCK(vp, id, op, fl, flags) \
		((vp)->v_ops->vop_advlock(vp, id, op, fl, flags))
#define	VOP_TRUNCATE(vp, length, flags, ucred) \
		((vp)->v_ops->vop_truncate(vp, length, flags, ucred))

/*
 * Housekeeping and other internals.  Note: VOP_ACTIVATE is not in BSD.
 */
#define	VOP_ABORTOP(vp, cnp)	((vp)->v_ops->vop_abortop(vp, cnp))
#define	VOP_ACTIVATE(vp)	((vp)->v_ops->vop_activate(vp))
#define	VOP_INACTIVE(vp)	((vp)->v_ops->vop_inactive(vp))
#if 0
#define	VOP_LOCK(vp)		((vp)->v_ops->vop_lock(vp))
#define	VOP_UNLOCK(vp)		((vp)->v_ops->vop_unlock(vp))
#endif
#define	VOP_STRATEGY(vp, bp)	((vp)->v_ops->vop_strategy(vp, bp))
#define	VOP_PRINT(vp)		((vp)->v_ops->vop_print(vp))

extern int enosys(void);
extern int vopErrorENOTDIR(void);
extern int vopErrorEISDIR(void);
extern int vop_error_rename(struct vnode *, struct vnode *,
	struct componentname *,
	struct vnode *, struct vnode *, struct componentname *);
#define vop_error_lookup \
	((int (*)(struct vnode *, struct vnode **, \
		  struct componentname *))enosys)
#define vop_error_lookup_enotdir \
	((int (*)(struct vnode *, struct vnode **, \
		  struct componentname *))vopErrorENOTDIR)
#define vop_error_create \
	((int (*)(struct vnode *, struct vnode **, struct componentname *, \
		  struct vattr *))enosys)
#define vop_error_open \
	((int (*)(struct vnode *, int, struct ucred *))enosys)
#define vop_error_close \
	((int (*)(struct vnode *, int, struct ucred *))enosys)
#define vop_error_access \
	((int (*)(struct vnode *, int, struct ucred *))enosys)
#define vop_error_getattr \
	((int (*)(struct vnode *, struct vattr *, struct ucred *))enosys)
#define vop_error_setattr \
	((int (*)(struct vnode *, struct vattr *, struct ucred *))enosys)
#define vop_error_read \
	((int (*)(struct vnode *, struct uio *, int, struct ucred *))enosys)
#define vop_error_write \
	((int (*)(struct vnode *, struct uio *, int, struct ucred *))enosys)
#define vop_error_ioctl \
	((int (*)(struct vnode *, u_long, void *, int, struct ucred *))enosys)
#define vop_error_fcntl \
	((int (*)(struct vnode *, u_int, void *, int, struct ucred *))enosys)
#define vop_error_fsync \
	((int (*)(struct vnode *, struct ucred *, int))enosys)
#define vop_error_seek \
	((int (*)(struct vnode *, voff_t, voff_t, struct ucred *))enosys)
#define vop_error_remove \
	((int (*)(struct vnode *, struct vnode *, \
		  struct componentname *))enosys)
#define vop_error_link \
	((int (*)(struct vnode *, struct vnode *, \
		  struct componentname *))enosys)
#define vop_error_mkdir \
	((int (*)(struct vnode *, struct vnode **, struct componentname *, \
		  struct vattr *))enosys)
#define vop_error_rmdir \
	((int (*)(struct vnode *, struct vnode *, \
		  struct componentname *))enosys)
#define	vop_error_rmdir_enotdir \
	((int (*)(struct vnode *, struct vnode *, \
		  struct componentname *))vopErrorENOTDIR)
#define vop_error_symlink \
	((int (*)(struct vnode *, struct vnode **, struct componentname *, \
		  struct vattr *, char *))enosys)
#define vop_error_readdir \
	((int (*)(struct vnode *, struct dirent *, struct ucred *, int *, \
		  int *))enosys)
#define vop_error_readdir_enotdir \
	((int (*)(struct vnode *, struct dirent *, struct ucred *, int *, \
		  int *))vopErrorENOTDIR)
#define vop_error_readlink \
	((int (*)(struct vnode *, struct uio *, struct ucred *))enosys)
#define vop_error_abortop \
	((int (*)(struct vnode *, struct componentname *))enosys)
/* NOTE: THERE IS NO "error" FUNCTION FOR inactive OR print */
void	vop_error_strategy(struct vnode *, struct buf *);
#define vop_error_pathconf \
	((int (*)(struct vnode *, long, long *))enosys)
#define vop_error_advlock \
	((int (*)(struct vnode *, void *, int, struct flock *, int))enosys)
#define vop_error_truncate \
	((int (*)(struct vnode *, voff_t, int, struct ucred *))enosys)

int	vn_makevnodes(struct mount *, int);
void	vn_deletevnodes(struct mount *);
void	vattr_null(struct vattr *);

void	bgetvp(struct vnode *, struct buf *);
void	brelvp(struct buf *);
void	vreassignbuf(struct buf *);
int	vflushbuf(struct vnode *, BOOL);
int	vinvalbuf(struct vnode *, int, struct ucred *);
void	vpurgebufs(struct vnode *, int,
		BOOL (*)(struct vnode *, struct buf *, void *), void *);

void	vn_incr_numoutput(struct vnode *);
void	vn_decr_numoutput(struct vnode *);

int	getnewvnode(struct mount *, struct vnode_ops *, struct vnode **);
int	vgetino(struct mount *, ino_t, const struct vnode_ops *,
		struct vnode **);
void	vref(struct vnode *);
void	vput(struct vnode *);
void	vrele(struct vnode *);

int	vaccess(enum vtype, mode_t, uid_t, gid_t, int, struct ucred *);

void	vprint(const char *, struct vnode *);

void	vn_panic(const char *, int, const char *, ...);

/*
 * vn_start_write and vn_finished_write are intended to allow
 * mount points to be "downgraded" from r/w to r/o: if the mount
 * point is waiting for a downgrade, the "start" calls will pause
 * or return an error (depending on supplied flags).
 *
 * We do not implement this yet so we just define this away to 0
 * for now.
 */
#define	vn_start_write(vp, mp, flags) (0)
#define vn_finished_write(mp, flags)

/*
 * This perhaps belongs elsewhere (BSD has a separate ucred.h) but
 * will serve for now.  Note that we only have one gid, rather than
 * a group-array and number-of-groups - this may eventually change
 * (for NFS)...
 */
struct ucred {
	uid_t	cr_uid;
	gid_t	cr_gid;
};

#ifdef __cplusplus
}
#endif

#endif /* __INCvnodeh */
