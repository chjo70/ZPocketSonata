/* namei.h - vnode/AFF lookup interface */

/* Copyright 2005, 2013  Wind River Systems, Inc */

/*
modification history
--------------------
01a,20jun05,act  add vnCheckPath() and vnReLookup() prototypes
*/

/*	$NetBSD: namei.h,v 1.37 2004/06/27 08:50:44 yamt Exp $	*/
/*	BSDI $Id: namei.h,v 2.5 2001/11/13 22:43:19 fmayhar Exp $	*/

/*
 * Copyright (c) 1985, 1989, 1991, 1993
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
 *	@(#)namei.h	8.5 (Berkeley) 8/20/94
 */

#ifndef __INCnameih
#define __INCnameih


#include "sys/queue.h"
#include "vnode.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * XXX should be in errno.h
 */
#define EJUSTRETURN (-2)

/*
 * Lookup parameters: this structure describes the subset of
 * information from the nameidata structure that is passed
 * through the VOP interface.
 */
struct componentname {
	/*
	 * Arguments to lookup.
	 */
	int	cn_nameiop;		/* operation */
	ULONG	cn_flags;		/* and flags */
	struct	ucred *cn_cred;		/* credentials */
	/*
	 * Shared between lookup and commit routines.
	 */
	char	*cn_pnbuf;		/* pathname buffer */
	char	*cn_nameptr;		/* pointer to looked up name */
	long	cn_namelen;		/* length of looked up component */
	ULONG	cn_hash;		/* hash value of looked up name */
	long	cn_consume;		/* chars to consume in lookup() */
};

/*
 * Encapsulation of namei parameters.
 */
struct nameidata {
	/*
	 * Arguments to namei/lookup.
	 */
	char	*ni_dirp;		/* pathname pointer */
	struct	mount *ni_mp;		/* mount point (from core I/O) */

	/*
	 * Arguments to lookup.
	 *
	 * Note that unlike BSD, we always have "absolute" path names
	 * and the "rootdir" is based on the mount point.
	 */
	struct	vnode *ni_startdir;	/* starting directory */
	struct	vnode *ni_rootdir;	/* logical root directory */

	/*
	 * Results: returned from/manipulated by lookup
	 */
	struct	vnode *ni_vp;
	struct	vnode *ni_dvp;

	/*
	 * Shared between namei and lookup/commit routines.
	 */
	size_t	ni_pathlen;		/* remaining chars in path */
	char	*ni_next;		/* next location in path */

	struct	componentname ni_cnd;
};

/*
 * namei operations
 */
#define	LOOKUP		0	/* perform name lookup only */
#define	CREATE		1	/* setup for file creation */
#define	DELETE		2	/* setup for file deletion */
#define	RENAME		3	/* setup for file renaming */
/*
 * namei operational modifiers, stored in ni_cnd.cn_flags
 */
#define	LOCKLEAF	0x0004	/* lock inode on return */
#define	LOCKPARENT	0x0008	/* want parent vnode returned locked */
#define	WANTPARENT	0x0010	/* want parent vnode returned unlocked */
#define	NOCACHE		0x0020	/* name must not be left in cache */
#define	FOLLOW		0x0040	/* follow symbolic links */
#define	NOSYMLINK	0x0080	/* symbolic links are an error */
#define	NOFOLLOW	0x0000	/* do not follow symbolic links (pseudo) */
#define	MODMASK		0x00fc	/* mask of operational modifiers */
/*
 * Namei parameter descriptors.
 *
 * SAVENAME may be set by VOP_LOOKUP().
 * In vxWorks, we never copy the name to a malloc()ed buffer, so
 * the flag has no real meaning -- when we are called from Core I/O we
 * already have the name in a buffer, which we just use.
 *
 * SAVESTART is set only by the callers of namei.  It implies SAVENAME
 * plus the addition of saving the parent directory that contains the
 * name in ni_startdir.  This allows repeated calls to lookup for the
 * name being sought.  The caller is responsible for vrele'ing ni_startdir.
 *
 * NOCROSSMOUNT is for NFS and is not used in vxWorks anyway, as we
 * never cross mount points in namei().
 */
#define	NOCROSSMOUNT	0x0000100	/* do not cross mount points */
#define	RDONLY		0x0000200	/* lookup with read-only semantics */
/*	HASBUF		0x0000400	-- we malloc'ed a pathname buffer */
#define	SAVENAME	0x0000800	/* save pathname buffer [N/A] */
#define	SAVESTART	0x0001000	/* save starting directory */
#define	ISDOTDOT	0x0002000	/* current component name is .. */
#define	MAKEENTRY	0x0004000	/* entry is to be added to name cache */
#define	ISLASTCN	0x0008000	/* this is last component of pathname */
#define	ISSYMLINK	0x0010000	/* symlink needs interpretation */
/*	ISWHITEOUT	0x0020000	-- found whiteout */
/*	DOWHITEOUT	0x0040000	-- do whiteouts */
/*	REQUIREDIR	0x0080000	-- must be a directory */
#define	PDIRUNLOCK	0x0100000	/* vop_lookup unlocked parent dir */
/*	CREATEDIR	0x0200000	-- creating entry is a directory */

/*
 * Initializtion of a nameidata structure.
 */
#define	NDINIT(ndp, op, flags, mp, namep, cred) do { \
	(ndp)->ni_cnd.cn_nameiop = op; \
	(ndp)->ni_cnd.cn_flags = flags; \
	(ndp)->ni_mp = mp; \
	(ndp)->ni_dirp = namep; \
	(ndp)->ni_cnd.cn_cred = cred; \
} while (0)

#ifdef notyet
/*
 * This structure describes the elements in the cache of recent
 * names looked up by namei.  Names longer than NCHNAMLEN are not
 * stored in the cache.
 */
#define	NCHNAMLEN	31	/* maximum name segment length we bother with */

struct	namecache {
	LIST_ENTRY(namecache) nc_hash;	/* hash chain */
	TAILQ_ENTRY(namecache) nc_lru;	/* LRU chain */
	LIST_ENTRY(namecache) nc_vhash;	/* directory hash chain */
	LIST_ENTRY(namecache) nc_dvlist;
	struct	vnode *nc_dvp;		/* vnode of parent of name */
	LIST_ENTRY(namecache) nc_vlist;
	struct	vnode *nc_vp;		/* vnode the name refers to */
	uchar	nc_len;			/* length of name */
	char	nc_name[NCHNAMLEN];	/* segment name */
};

/*
 * Stats on usefulness of namei caches.
 */
struct	nchstats {
	ULONG	ncs_goodhits;		/* hits that we can really use */
	ULONG	ncs_neghits;		/* negative hits that we can use */
	ULONG	ncs_badhits;		/* hits we must drop */
	ULONG	ncs_falsehits;		/* hits with id mismatch */
	ULONG	ncs_miss;		/* misses */
	ULONG	ncs_long;		/* long names that ignore cache */
	ULONG	ncs_pass2;		/* names found with passes == 2 */
	ULONG	ncs_2passes;		/* number of times we attempt it */
};
#endif /* notyet */

/*
 * Pathname-related functions.
 *
 * Currently, namei() is not exported at all (is local to vnodeAff.c);
 * if we export it we should declare it here, but perhaps also change
 * its name.
 */
/* int namei(struct nameidata *); */
int vnCheckPath(struct vnode *, struct vnode *, struct componentname *);
int vnReLookup(struct vnode *, struct vnode **, struct componentname *, int);

#ifdef __cplusplus
}
#endif

#endif /* __INCnameih */
