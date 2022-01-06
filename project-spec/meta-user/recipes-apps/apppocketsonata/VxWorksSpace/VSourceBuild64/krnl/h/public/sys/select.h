/* sys/select.h */

/*
 * Copyright (c) 2005, 2009-2010, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
*/
/*
modification history
--------------------
11nov16,i_l  included strings.h to remove warnings. (V7COR-4528)
13jul16,dlk  Include <sys/types.h> instead of <base/e_vxTypesOld.h>.
18feb16,zl   updated for shared kernel/user space
17mar10,lxj  fixed defect WIND00200304
21may09,zly  LP64 support
18aug05,mcm  Initial version
*/

#ifndef _SYS_SELECT_H_
#define _SYS_SELECT_H_

#include <sys/types.h>   /* _VX_FD_SETSIZE, etc. */
#include <sys/time.h>            /* timeval */
#include <signal.h>              /* sigset_t */
#include <time.h>                /* timespec */
#include <strings.h> 

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef FD_SETSIZE
#define FD_SETSIZE      _VX_FD_SETSIZE
#endif  /* FD_SETSIZE */

#ifndef _FD_MASK_DEFINED
#define _FD_MASK_DEFINED
typedef long    fd_mask;
#endif /* _FD_MASK_DEFINED */

#ifndef NBBY
#define NBBY		8
#endif

#ifndef NFDBITS
#define NFDBITS 	(sizeof(fd_mask) * NBBY)        /* bits per mask */
#endif

#ifndef howmany
#define howmany(x, y)   ((unsigned int)(((x)+((y)-1)))/(unsigned int)(y))
#endif

#ifndef _FD_SET_DEFINED
#define _FD_SET_DEFINED
typedef struct fd_set
    {
    fd_mask     fds_bits[howmany(FD_SETSIZE, NFDBITS)];
    } fd_set;
#endif /* _FD_SET_DEFINED */

#ifndef _FD_FUNC_DEFINED
#define _FD_FUNC_DEFINED
#define FD_CLR(n, p)    ((p)->fds_bits[(n)/NFDBITS] &= ~((fd_mask)1 << ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & ((fd_mask)1 << ((n) % NFDBITS)))
#define FD_SET(n, p)    ((p)->fds_bits[(n)/NFDBITS] |= ((fd_mask)1 << ((n) % NFDBITS)))
#define FD_ZERO(p)      bzero((char *)(p), sizeof(*(p)))
#endif /* _FD_FUNC_DEFINED */

#ifdef _WRS_KERNEL
extern int select (int width, fd_set * pReadFds, fd_set * pWriteFds,
		   fd_set * pExceptFds, struct timeval * pTimeOut);
#else
extern int select(int, fd_set *_Restrict, fd_set *_Restrict, fd_set *_Restrict,
	          struct timeval *_Restrict);
#endif

#if FALSE /* pselect not implemented */
extern int pselect(int, fd_set *_Restrict, fd_set *_Restrict, fd_set *_Restrict,
	           const struct timespec *_Restrict, const sigset_t *_Restrict);
#endif

#ifdef  __cplusplus
}
#endif

#endif /* _SYS_SELECT_H_ */
