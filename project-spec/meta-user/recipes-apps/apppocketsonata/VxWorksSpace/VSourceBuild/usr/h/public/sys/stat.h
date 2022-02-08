/* stat.h - POSIX definitions for obtaining file characteristics */

/*
 * Copyright (c) 2003-2006, 2010, 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03nov17,ghs  move file system statistics structures and APIs to statfs.h (F9150)
14apr16,dlk  Rename chmod system call for user mode I/O system (F6848).
24jun15,cww  fixed umask() namespace conformance (V7COR-3191)
21apr15,rr   Fixed POSIX conformance issue (V7COR-2353).
20mar15,txu  added umask(). (US55492)
14may14,h_k  added mkfifo(). (US35006)
28jun10,jxu  LP64: cleanup of compiler warnings, added definition of
             structure statfs64 and declaration of API fstatfs64 and
             statfs64.
10may06,pcm  undid changes from version 01i
08may06,pcm  modified stat structure as size of ino_t changed.
05mar06,mil  Hide struct statfs and associated functions from posix.
01mar06,pes  Replace sys/types.h and sys/time.h includes with individual
             required base type includes.
27jan06,mil  Updated for POSIX namespace conformance.
23jan06,act  add fchmod
25oct05,zl   added S_TYPEISMQ(), S_TYPEISSEM() S_TYPEISSHM() macros.
22aug05,hya  made mkdir POSIX compliant.
09aug05,hya  added chmod().
02oct04,mcm  Fixing the prototype for stat and statfs.
11sep03,mcm  Adapted from target/h/sys/stat to allow usage from user
             space
*/

#ifndef __INCstath
#define __INCstath

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <types/vxTypesOld.h>
#endif  /* _POSIX_xxx_SOURCE */

#include <base/b_dev_t.h>
#include <base/b_ino_t.h>
#include <base/b_mode_t.h>
#include <base/b_nlink_t.h>
#include <base/b_uid_t.h>
#include <base/b_gid_t.h>
#include <base/b_off_t.h>
#include <base/b_time_t.h>
#include <base/b_blksize_t.h>
#include <base/b_blkcnt_t.h>

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <sys/statfs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef st_dev
#undef st_ino
#undef st_mode
#undef st_nlink
#undef st_uid
#undef st_gid
#undef st_rdev
#undef st_size
#undef st_atime
#undef st_mtime
#undef st_ctime
#undef st_blksize
#undef st_blocks
#undef st_attrib
#undef st_reserved1
#undef st_reserved2
#undef st_reserved3
#undef st_reserved4
#endif

struct	stat
    {
    dev_t       st_dev;     /* Device ID number */
    ino_t       st_ino;     /* File serial number */
    mode_t      st_mode;    /* Mode of file */
    nlink_t     st_nlink;   /* Number of hard links to file */
    uid_t       st_uid;     /* User ID of file */
    gid_t       st_gid;     /* Group ID of file */
    dev_t       st_rdev;    /* Device ID if special file */
    off_t       st_size;    /* File size in bytes */
    time_t      st_atime;   /* Time of last access */
    time_t      st_mtime;   /* Time of last modification */
    time_t      st_ctime;   /* Time of last status change */
    blksize_t   st_blksize; /* File system block size */
    blkcnt_t    st_blocks;  /* Number of blocks containing file */
    unsigned char st_attrib;  /* DOSFS only - file attributes */
    int         st_reserved1;  /* reserved for future use */
    int         st_reserved2;  /* reserved for future use */
    int         st_reserved3;  /* reserved for future use */
    int         st_reserved4;  /* reserved for future use */
    };


#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef val
#else
#define TIME ULONG
#endif  /* _POSIX_xxx_SOURCE */

/* File mode (st_mode) bit masks */

#define	S_IFMT	 0xf000		/* file type field */
#define	S_IFIFO	 0x1000		/*  fifo */
#define	S_IFCHR	 0x2000		/*  character special */
#define	S_IFDIR	 0x4000		/*  directory */
#define	S_IFBLK	 0x6000		/*  block special */
#define	S_IFREG	 0x8000		/*  regular */
#define	S_IFLNK	 0xa000		/*  symbolic link */
#define	S_IFSHM  0xb000		/*  shared memory object */
#define	S_IFSOCK 0xc000		/*  socket */

#define	S_ISUID	 0x0800		/* set user id on execution */
#define	S_ISGID	 0x0400		/* set group id on execution */
#define	S_ISTXT	 0x0200		/* sticky bit */

#define	S_IRUSR  0x0100		/* read permission, owner */
#define	S_IWUSR  0x0080		/* write permission, owner */
#define	S_IXUSR  0x0040		/* execute/search permission, owner */
#define	S_IRWXU	 0x01c0		/* read/write/execute permission, owner */

#define	S_IRGRP  0x0020		/* read permission, group */
#define	S_IWGRP  0x0010		/* write permission, group */
#define	S_IXGRP  0x0008		/* execute/search permission, group */
#define	S_IRWXG	 0x0038		/* read/write/execute permission, group */

#define	S_IROTH  0x0004		/* read permission, other */
#define	S_IWOTH  0x0002		/* write permission, other */
#define	S_IXOTH  0x0001		/* execute/search permission, other */
#define	S_IRWXO	 0x0007		/* read/write/execute permission, other */


#define	_VX_ACCESSPERMS	(S_IRWXU|S_IRWXG|S_IRWXO)	/* 0777 */
							/* 7777 */
#define	_VX_ALLPERMS	(S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
							/* 0666 */
#define	_VX_DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

/* File type test macros */

#define	S_ISDIR(mode)	((mode & S_IFMT) == S_IFDIR)	/* directory */
#define	S_ISCHR(mode)	((mode & S_IFMT) == S_IFCHR)	/* character special */
#define	S_ISBLK(mode)	((mode & S_IFMT) == S_IFBLK)	/* block special */
#define	S_ISREG(mode)	((mode & S_IFMT) == S_IFREG)	/* regular file */
#define	S_ISFIFO(mode)	((mode & S_IFMT) == S_IFIFO)	/* fifo special */
#define	S_ISLNK(mode)	((mode & S_IFLNK) == S_IFLNK)	/* symbolic link special */

/*
 * POSIX.1b objects.  The macros that evaluate to zero (false) are
 * defined so that they provide syntax checking for the parameter.
 */

#define S_TYPEISMQ(buf)     ((buf)->st_mode - (buf)->st_mode)
#define S_TYPEISSEM(buf)    ((buf)->st_mode - (buf)->st_mode)
#define S_TYPEISSHM(buf)    (((buf)->st_mode & S_IFMT) == S_IFSHM)

/* function declarations */

extern    int          mkdir     (const char *, mode_t);
extern	  int	       chmod     (const char *, mode_t);
extern	  int	       _chmod     (const char *, mode_t);
extern	  int	       fchmod    (int, mode_t);
extern    int          mkfifo    (const char *, mode_t);
extern    mode_t       umask     (mode_t);

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

extern	  STATUS       fstat     (int, struct stat *);
extern	  STATUS       stat      (const char *, struct stat *);

#else   /* _POSIX_xxx_SOURCE */

extern	  int          fstat     (int, struct stat *);
extern	  int          stat      (const char *, struct stat *);

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCstath */
