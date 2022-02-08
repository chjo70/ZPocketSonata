/* dirent.h - POSIX directory handling definitions */

/*
 * Copyright 1990-1992, 2004-2007, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01y,24jun11,y_t  req WIND00236547: improve nfs ls performance.
01x,14jan11,pad  Include base/b_ino_t.h instead of types/vxTypes.h (defect
                 218143).
01w,28apr10,pad  Moved extern C statement after include statements.
01v,07may09,lyc  LP64 support
01u,09aug07,pad  Used the new _Vx_BOOL type instead of _Bool (different size,
                 defect 100623).
01t,10may06,pcm  undid changes from version 01s
01s,08may06,pcm  modified dirent and DIR structures
01r,28feb06,pes  Remove parameter names in function prototypes (per POSIX).
01q,13feb06,dcc  added POSIX naming compliance when in user space.
01p,18jan06,mil  Updated for POSIX namespace conformance (P1).
01o,17jan06,md   added readdir_r
01n,01oct05,md   changed d_name to use _PARM_NAME_MAX
01m,28jul05,act  add an "end of dir" flag to a DIR for FIOREADDIR ops
01l,20jul05,jlk  added d_ino field to dirent struct for POSIX.
01k,09apr04,dat  adding const to char ptrs
01j,22sep92,rrr  added support for c++
01i,04jul92,jcf  cleaned up.
01h,26may92,rrr  the tree shuffle
01g,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01f,10jun91.del  added pragma for gnu960 alignment.
01e,05oct90,dnw  added rewinddir() and closedir().
01d,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01c,07aug90,shl  added IMPORT type to function declarations.
01b,25may90,dnw  moved NAME_MAX to limits.h
		 added copyright
01a,17apr90,kdl  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCdirenth
#define __INCdirenth

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#include <limits.h>			/* indirectly for _PARM_NAME_MAX */
#include <vxWorks.h>			/* for SEM_ID, BOOL, STATUS */

#else   /* _POSIX_xxx_SOURCE */

#include <types/vxParams.h>		/* for _PARM_NAME_MAX */
#include <base/b_ino_t.h>
#include <types/vxWind.h>		/* for _Vx_SEM_ID */
#include <base/b_BOOL.h>		/* for _Vx_BOOL */

#endif  /* _POSIX_xxx_SOURCE */

#include <sys/stat.h>


#ifdef __cplusplus
extern "C" {
#endif

/* Directory entry */

struct dirent		/* dirent */
    {
    ino_t	d_ino;                  /* file serial number */
    char	d_name [_PARM_NAME_MAX + 1]; /* file name, null-terminated */
    };

/* Directory descriptor */
/* NOTE: implementation specific members of DIR subject to future changes */

#ifdef _WRS_KERNEL

typedef struct		/* DIR */
    {
    long 	  dd_cookie;		/* filesys-specific marker within dir */
    int		  dd_fd;		/* file descriptor for open directory */
    BOOL	  dd_eof;		/* readdir EOF flag */
    struct dirent dd_dirent;		/* obtained directory entry */
    SEM_ID	  dd_lock;		/* lock for readdir_r */
    } DIR;

#else  /* !_WRS_KERNEL */

typedef struct		/* DIR */
    {
    long	  d_cookie;		/* filesys-specific marker within dir */
    int		  d_fd;			/* file descriptor for open directory */
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
    BOOL	  d_eof;		/* readdir EOF flag */
    struct dirent d_dirent;		/* obtained directory entry */
    SEM_ID	  d_lock;		/* lock for readdir_r */
#else   /* _POSIX_xxx_SOURCE */
    _Vx_BOOL	  d_eof;		/* readdir EOF flag */
    struct dirent d_dirent;		/* obtained directory entry */
    _Vx_SEM_ID	  d_lock;		/* lock for readdir_r */
#endif  /* _POSIX_xxx_SOURCE */
    } DIR;

#endif /* _WRS_KERNEL */

#ifdef _WRS_KERNEL

typedef struct		/* DIRPLUS */
    {
	long	  dd_cookie;	/* filesys-specific marker within dir */
    int		  dd_fd;		/* file descriptor for open directory */
    BOOL	  dd_eof;		/* readdir EOF flag */
    struct dirent dd_dirent;		/* obtained directory entry */
    SEM_ID	  dd_lock;		/* lock for readdir_r */
	struct stat dd_stat;
    } DIRPLUS;

#else  /* _WRS_KERNEL */

typedef struct		/* DIRPLUS */
    {
	long	  d_cookie;		/* filesys-specific marker within dir */
    int		  d_fd;			/* file descriptor for open directory */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
    BOOL	  d_eof;		/* readdir EOF flag */
    struct dirent d_dirent;		/* obtained directory entry */
    SEM_ID	  d_lock;		/* lock for readdir_r */
#else   /* _POSIX_xxx_SOURCE */
    _Vx_BOOL	  d_eof;		/* readdir EOF flag */
    struct dirent d_dirent;		/* obtained directory entry */
    _Vx_SEM_ID	  d_lock;		/* lock for readdir_r */
#endif  /* _POSIX_xxx_SOURCE */
	struct stat d_stat;
    } DIRPLUS;

#endif /* _WRS_KERNEL */
/* function declarations */

extern DIR *		opendir   (const char *);
extern struct dirent *	readdir   (DIR *);
extern int 		readdir_r (DIR *, struct dirent  *,
				   struct dirent **);
extern void 		rewinddir (DIR *);

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern STATUS		closedir  (DIR *);
#else   /* _POSIX_xxx_SOURCE */
extern int		closedir  (DIR *);
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdirenth */
