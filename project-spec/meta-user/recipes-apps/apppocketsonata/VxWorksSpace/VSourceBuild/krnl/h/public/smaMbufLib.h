/* smaMbufLib.h - header file for SMA I/O buffer handling */

/* Copyright 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
18aug14,elp  created from WDB.
*/

#ifndef __INCsmaMbufLibh
#define __INCsmaMbufLibh

/* includes */

#include "net/mbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* macros */

#define smaMbufClusterInit(pMbuf, addr, nBytes, callBackRtn, callBackArg) \
    {									\
    (pMbuf)->m_next       = NULL;					\
    (pMbuf)->m_nextpkt    = NULL;					\
    (pMbuf)->m_data       = (caddr_t)(addr);				\
    (pMbuf)->m_len        = nBytes;					\
    (pMbuf)->m_type       = MT_DATA;					\
    (pMbuf)->m_flags      |= M_EXT;					\
    (pMbuf)->m_extBuf     = (caddr_t)(addr);				\
    (pMbuf)->m_extSize    = nBytes;					\
    (pMbuf)->m_extFreeRtn = callBackRtn;				\
    (pMbuf)->m_extRefCnt = 1;						\
    (pMbuf)->m_extArg1    = callBackArg;				\
    (pMbuf)->m_extArg2    = 0;						\
    (pMbuf)->m_extArg3    = 0;						\
    }

#define smaMbufChainFree(pMbuf)						\
    {									\
    struct mbuf *__pNextMbuf;						\
    struct mbuf *__pThisMbuf;						\
    __pThisMbuf = pMbuf;						\
    while (__pThisMbuf != NULL)						\
	{								\
	__pNextMbuf = __pThisMbuf->m_next;				\
	smaMbufFree (__pThisMbuf);					\
	__pThisMbuf = __pNextMbuf;					\
	}								\
    }

#define smaMbufDataGet(__pMbuf, __pDest, __len, __pLen)			\
    {									\
    int __nBytes;							\
    struct mbuf * __pThisMbuf;						\
									\
    __nBytes = 0;							\
    for (__pThisMbuf = __pMbuf;						\
         __pThisMbuf != NULL;						\
         __pThisMbuf = __pThisMbuf->m_next)				\
        {								\
        int __moreBytes = MIN (__pThisMbuf->m_len, __len - __nBytes);	\
        bcopy (mtod (__pThisMbuf, char *), __pDest + __nBytes, __moreBytes); \
        __nBytes += __moreBytes;					\
        if (__nBytes >= __len)						\
            break;							\
        }								\
									\
    *(__pLen) = __nBytes;						\
    }

/* function prototypes */

extern struct mbuf *	smaMbufAlloc     (void);
extern void             smaMbufFree      (struct mbuf * segId);
extern void             smaMbufInit (struct mbuf *, UINT32, CL_BLK *, UINT32);

#ifdef __cplusplus
}
#endif

#endif	/* __INCsmaMbufLibh */

