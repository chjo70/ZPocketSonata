/* mount.h - file system mount-point interface */

/*
 * Copyright 2005, 2009-2011, 2013, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
27apr16,zly  add mnt_readonly member for mount structure (V7STO-616)
06sep15,txu  VXW6-82898 - modify the code of mount phase to fix the panic
             issue in SMP mode
31jan13,myt  WIND00401852 - buf hash list performance improvement
29jul11,jxu  add mutex for cross-directory rename (WIND00287328). 
29mar11,jxu  Fix WIND00260468 and WIND00260786: removed the inappropriate 
             fixing for WIND00243584.
20dec10,zhe  WIND00243584 - multi-tasks removing results in missing files
02apr10,lxj  adapted for LP64 support 
01jul09,hui  WIND142041 - HRFS performance improvement
26jul06,act  add "first error" fields to mount point
21nov05,md   make struct vfsops a const
07oct05,md   change f_flags from u_short to u_int
14aug05,jlk  add suspend flag to mountEject
26jul05,act  split commit op into start+end ops
20jul05,act  add mountEject and some internal flags
06may05,jlk  changed some fields in statvs to be 64 bit
21apr05,jlk  filled in statvs structure
10mar05,act  add pointer to mount point to mountCreate
10mar05,act  split buffer creation and deletion out of mountCreate
10mar05,act  add mnt_dev
03mar05,act  add MNT_RDONLY
03mar05,act  remove mount list and some unused mnt_* fields
02mar05,act  add bio fields, and DEV_HDR for coreIO
23feb05,act  add mnt_rootvnode, for lookup code
*/

#ifndef __INCmounth
#define __INCmounth

#include <buf.h>
#include <vnode.h>
#include <ioLib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct vfsops;

/* xxx move this to vnode.h */
LIST_HEAD(vnodelst, vnode);
LIST_HEAD(vhashhdr, vnode);

struct statvfs
    {
    UINT32  f_bsize;    /* File system block size.                                     */
    UINT32  f_frsize;   /* Fundamental file system block size.                         */
    UINT64  f_blocks;   /* Total number of blocks on file system in units of f_frsize. */
    UINT64  f_bfree;    /* Total number of free blocks.                                */
    UINT64  f_bavail;   /* Number of free blocks available to                          */
                        /* non-privileged process.                                     */
    UINT64  f_files;    /* Total number of file serial numbers.                        */
    UINT64  f_ffree;    /* Total number of free file serial numbers.                   */
    UINT64  f_favail;   /* Number of file serial numbers available to                  */
                        /* non-privileged process.                                     */
    UINT32  f_fsid;     /* File system ID.                                             */
    UINT32  f_flag;     /* Bit mask of f_flag values.                                  */
    UINT32  f_namemax;  /* Maximum filename length.                                    */
    };

/*
 * Open-file table, per mount point.  In BSD this is in <sys/file.h>
 * and logically core I/O should do this, but here we have to do it
 * per mount point.
 *
 * At the moment, f_count is not needed... remove it?  (dup() is handled
 * inside core I/O, so that dup()ed fd's point to the same vfile data
 * structure.)
 */
struct vfile
    {
    u_short     f_count;        /* number of dup()s */
    u_int       f_flags;        /* _FREAD and/or _FWRITE */
    struct vnode    *f_vnode;       /* vnode for this file */
    voff_t      f_offset;       /* and current seek pos */
    SLIST_ENTRY(vfile) f_next;      /* list of free files */
    };

struct mount
    {
    DEV_HDR     mnt_devhdr;     /* CoreI/O, MUST BE FIRST */
    device_t    mnt_dev;        /* connected XBD */
    const struct vfsops *mnt_op;        /* operations on fs */
    struct vnode    *mnt_syncer;        /* syncer vnode */
    struct vnode    *mnt_rootvnode;     /* result of VFS_ROOT() */
    struct vnodelst mnt_vnodelist;      /* active vnodes */
#ifdef notyet
    struct lock mnt_lock;       /* mount structure lock */
#else
    SEM_ID      mnt_lock;
#endif
    int     mnt_flag;       /* flags */
    int     mnt_iflag;      /* internal flags */

    /* per-mount file and vnode tables */
    SEM_ID      mnt_filesem;        /* ??? can use mnt_lock? */
    struct vfile    *mnt_filetable;     /* open file table */
    int     mnt_nfiles;     /* # files, for debug/show */
    SLIST_HEAD(, vfile) mnt_freefiles;  /* list of free files */
    char        *mnt_vnodespace;    /* malloc() space for vnodes */
    int     mnt_nvnodes;        /* # vnodes, for debug/show */

    void        *mnt_data;      /* private data */

    BOOL                  mnt_readOnly; /*read only properties*/

    /*
     * When doing I/O on a mounted file system, if buf_done() is
     * given an error, the error number is recoreded in the mount
     * point as well as the buffer.  This error "sticks" until
     * something clears it.  This is mostly for file systems that
     * do async I/O and want to see if some error(s) have occurred
     * since they last checked.  We save the "first" error, rather
     * than the "last", on the theory that the first one is likely
     * the most informative (subsequent errors being due to the
     * first one).
     *
     * (Essentially, the technique is: push out any delayed or
     * async I/O, then check these, then clear them for the next
     * time.)
     */
    int     mnt_read_errno;     /* first read errno */
    int     mnt_write_errno;    /* first write errno */

    /*
     * These items are for buffer management.  Note that there are
     * three semaphores involved: a counting semaphore for "number of
     * unowned buffers", a mutex for hash chain manipulation, and
     * one semaphore per buffer.  If you are taking a buffer semaphore
     * and the hash chain mutex, you must take the buffer semaphore
     * first (to avoid deadlocking).
     *
     * The hash chain mutex is also used to protect the free lists.
     *
     * The buffer getting routines (getblk, bread) return locked
     * buffers (which are no longer on a free list) -- see buf.h.
     */
    struct buf  *mnt_bufspace;      /* for free()ing */
    int     mnt_nbufs;      /* and show()ing */
    SEM_ID      mnt_unowned_bufs;   /* number of unowned buffers */
    SEM_ID      mnt_bufhash_mutex;  /* hash chain mutex */
    struct bhashhdr *mnt_bufhash; /* hash chains */
    struct bfreehdr mnt_bufqueues[BUF_NQUEUES]; /* free lists */

    /*
     * These items are for vnode management, which is done in pretty
     * much the same fashion as buffer management, except that vnodes
     * do not have "priorities" to order the free list.  Also, vnodes
     * can have more than one active user, and can be "held" (by
     * buffer cache references) even when no one is using them.
     */
    SEM_ID      mnt_unowned_vnodes; /* number of unowned vnodes */
    SEM_ID      mnt_vhash_mutex;    /* hash chain mutex */
    struct vhashhdr mnt_vhash[VN_VHSIZE];   /* hash chains */
    TAILQ_HEAD(, vnode) mnt_vhold_list; /* held vnodes */
    TAILQ_HEAD(, vnode) mnt_freevnodes; /* free vnodes */

    /*
     * These keep track of bio space allocated in mountCreate(),
     * for mountDelete() to release.
     */
    struct bio  *mnt_bios;      /* the bios */
    void        *mnt_biomem;        /* device-space RAM for I/O */

    /* mutex used for cross-directory rename to avoid 
     * potential deadlock among multiple renames.
     */
    SEM_ID      mnt_rename_mutex;    /* rename mutex */
    };

struct vfsops
    {
    const char *vfs_name;           /* name of this fs type */
    size_t  vfs_mount_data_size;        /* size of private mount data */
    size_t  vfs_vnode_data_size;        /* size of private vnode data */

    int     (*vfs_start)(struct mount *, int);
    int     (*vfs_unmount)(struct mount *, int);
    int     (*vfs_root)(struct mount *, struct vnode **);
    int     (*vfs_statvfs)(struct mount *, struct statvfs *);
    int     (*vfs_vget)(struct mount *, ino_t, struct vnode **);
    void    (*vfs_init)(void);
    void    (*vfs_reinit)(void);
    void    (*vfs_done)(void);
    };

#define	VFS_START(mp, flags)	((mp)->mnt_op->vfs_start(mp, flags))
#define	VFS_UNMOUNT(mp, force)	((mp)->mnt_op->vfs_unmount(mp, force))
#define	VFS_ROOT(mp, vpp)	((mp)->mnt_op->vfs_root(mp, vpp))
#define	VFS_STATVFS(mp, sbp)	((mp)->mnt_op->vfs_statvfs(mp, sbp))
#define	VFS_VGET(mp, ino, vpp)	((mp)->mnt_op->vfs_vget(mp, ino, vpp))

int  mountCreate(const struct vfsops *, device_t, int, char *, struct mount **);
void mountDelete(struct mount *, int);
void mountEject(struct mount *, BOOL);

int  mountBufAlloc(struct mount *, int, int);
void mountBufFree(struct mount *);
STATUS mountInsDev(struct mount *, char *);

/*
 * Mount flags.
 */
#define	MNT_RDONLY	0x00000001	/* read only filesystem */

/*
 * Internal flags.
 */
#define	MNTI_IN_COREIO	0x00000001	/* entry is in coreIO tables */
#define	MNTI_EJECTING	0x00000002	/* mount point is being ejected */

#ifdef __cplusplus
}
#endif

#endif /* __INCmounth */
