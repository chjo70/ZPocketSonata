/* mman.h - memory management library header file */

/* 
 * Copyright (c) 1993-2006, 2010-2012 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01o,18jun12,pcs  Fix POSIX Conformance: mman header testing
                 error.(WIND00344892)
01n,14jun11,pcs  add mtranslate()
01m,28apr10,pad  Moved extern C statement after include statements.
01l,19feb10,zl   enabled SHM API in kernel
01k,27jan06,mil  Updated for POSIX namespace conformance.
01j,25jan06,zl   fixed msync() flag definitions
01i,14dec05,zl   added MCTL_MPROBE.
01h,28oct05,zl   added shm_open() and shm_unlink() declarations
01g,08jul05,zl   added MAP_CONTIG and msync() definitions.
01f,06jan05,zl   added _mctrl support. reversed previous change.
01e,01oct04,gls  made <off> type off_t64
01d,14jun04,gls  added MAP_ANON_FD and MAP_ANONYMOUS
01c,11jun04,gls  added MAP_ANON
01b,09sep03,zl   added mmap(), mmunmap(), mprotect()
01a,05nov93,dvs  written
*/

#ifndef __INCmmanh
#define __INCmmanh

/* includes */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <vxWorks.h>
#else   /* _POSIX_xxx_SOURCE */
#include <sys/types.h>
#endif  /* _POSIX_xxx_SOURCE */
#include <base/b_phys_addr_t.h>

#ifdef __cplusplus
extern "C" {
#endif

/* memory locking flags */

#define MCL_CURRENT 	0x1		/* lock current mappings */
#define MCL_FUTURE	0x2		/* lock future mappings */

/* mmap protections */

#define PROT_NONE	0x0000		/* Page cannot be accessed */
#define PROT_READ	0x0001		/* Page can be read */
#define PROT_WRITE	0x0002		/* Page can be written */
#define PROT_EXEC	0x0004		/* Page can be executed */

/* map flags */

#define MAP_SHARED	0x0001		/* Share changes */
#define MAP_PRIVATE	0x0002		/* Changes are private */
#define MAP_ANON	0x0004		/* Use anonymous memory */
#define MAP_ANONYMOUS	MAP_ANON	/* compatibility with Linux */
#define MAP_FIXED	0x0010		/* Interpret addr exactly */
#define MAP_CONTIG	0x0020		/* map contiguous phys pages */

/* msync flags */

#define	MS_SYNC		0x0001		/* msync synchronously */
#define MS_ASYNC	0x0002		/* return immediately */
#define MS_INVALIDATE	0x0004		/* invalidate all cached data */

/* map fail */

#define MAP_FAILED	((void *) -1)	/* mmap() error return value */

/* anonymous fd */

#define MAP_ANON_FD     -1              /* required fd value for mmap */


#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
/* 
 * function definitions for _mctrl(); these should not be used directly, 
 * but via the wrapper functions, such as the ones in cacheLib and mmanLib.
 */

#define MCTL_CACHE_FLUSH	1	/* cache flush */
#define MCTL_CACHE_INVALIDATE	2	/* cache invalidate */
#define MCTL_CACHE_CLEAR	3	/* cache clear*/
#define MCTL_CACHE_TEXT_UPDATE	4	/* cache text update */
#define MCTL_MSYNC		5	/* perform msync() */
#define MCTL_MPROBE		6	/* probe memory */
#define MCTL_MTRANSLATE		7	/* translate virt addr to phys addr */
#endif  /* _POSIX_xxx_SOURCE */

#ifndef _ASMLANGUAGE

/* Function declarations */

extern int	mlockall (int);
extern int	munlockall (void);
extern int	mlock (const void * , size_t);
extern int	munlock (const void * , size_t);
extern void *	mmap (void * , size_t , int , int , int , off_t);
extern int	mprotect (void * , size_t , int);
extern int 	munmap (void * , size_t);
extern int	msync (void * , size_t , int);
extern int	shm_open (const char * , int , mode_t);
extern int	shm_unlink (const char *);

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int	mtranslate (void * addr, _Vx_phys_addr_t * pPhysAddr);
#endif  /* _POSIX_xxx_SOURCE */

#ifdef _WRS_KERNEL
extern void *	mmap64 (void * addr, size_t len, int prot, int flags, int fildes,
			off64_t off);
#else
extern int	_mctl (void * , size_t , int , void *);
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int	mprobe (void * addr, size_t len, int prot);
#endif  /* _POSIX_xxx_SOURCE */
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmanh */
