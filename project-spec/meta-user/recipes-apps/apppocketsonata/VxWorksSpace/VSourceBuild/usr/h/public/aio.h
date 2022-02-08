/* aio.h - asynchronous I/O header file */

/* Copyright 1984-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01l,21jun10,jxu  LP64: add prototype for aioVerboseEnable.
01k,28apr10,pad  Moved extern C statement after include statements.
01j,11aug06,jlk  Fix: WIND0006174 - lio_listio for pse52
01i,15mar06,mil  Updated include quotes.
01h,18jan06,mil  Updated for POSIX namespace conformance (P1).
01g,08jan06,hya  fixed prototype of aio_return.
01f,21nov05,md   fix prototypes for lio_listio and aio_suspend
01f,19apr05,hya  added aio_fsync.
01e,30jan04,dat  Rework for RTP compatibility
01d,18jul96,dbt  added aioPxLibInit() and aioShow() prototypes (SPR #3227).
01c,23jan96,tpr  added ; after lio_listio () prototype definition.
		 added Copyright line.
01b,26jan94,kdl  removed prototype for aio_fsync(); minor cleanup.
01a,04apr93,elh  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCaioh
#define __INCaioh

/* includes */

#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <private/aioPxLibP.h>		/* private APIs, do not use */

#ifdef __cplusplus
extern "C" {
#endif

						
/* defines */
						
/* aio_cancel() return values */

#define	AIO_CANCELED			1	/* operations canceled */
#define	AIO_NOTCANCELED			2	/* operations are in progress */
#define	AIO_ALLDONE			3	/* operations complete */

/* lio_listio()  modes */

#define	LIO_WAIT			4	/* wait for completion */
#define	LIO_NOWAIT			5	/* don't wait for completion */

/* lio_listio() operations */
					 	/* lio op codes */
#define	LIO_READ			0	/* read operation */
#define	LIO_WRITE			1	/* write operation */
#define	LIO_NOP				2	/* no transfer operation*/

/* Asynchronous I/O control block */

struct aiocb
    {
    int			aio_fildes;		/* file descriptor */
    off_t		aio_offset;		/* file offset */
    volatile void *	aio_buf;		/* location of buffer */
    size_t		aio_nbytes;		/* length of transfer */ 
    int			aio_reqprio;		/* request priority offset */
    struct sigevent	aio_sigevent;		/* signal number and value */
    int			aio_lio_opcode;		/* operation to be performed */

    /* WRS addition */
    struct aio_sys	aio_sys;    		/* implementation-specific */
    };

/* forward declarations */

extern int   	aio_read (struct aiocb *);
extern int 	aio_write (struct aiocb *);
#ifdef _WRS_KERNEL
extern int 	lio_listio (int, struct aiocb * const[], int, 
		    	    struct sigevent *);
#else
extern int 	lio_listio (int, struct aiocb * _Restrict const[], int, 
		    	    struct sigevent * _Restrict);
#endif			    
extern int 	aio_error (const struct aiocb *);
extern ssize_t	aio_return (struct aiocb *);
extern int 	aio_cancel (int, struct aiocb *);
extern int 	aio_suspend (const struct aiocb *const[], int , 
		             const struct timespec *);
extern int 	aio_fsync (int, struct aiocb *);

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern STATUS   aioPxLibInit (int lioMax);
extern STATUS   aioShow (int notUsed);
extern int      aioVerboseEnable (void);
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCaioh */
