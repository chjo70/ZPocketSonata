/* sockFunc.h - socket function table header */

/*
 * Copyright 1984-2006, 2009-2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
02r,12apr16,mca  Added user mode sockets (F6564)
02q,09oct15,mca  Made socket functions available for userspace build
02p,05jan11,h_x  Fix WIND00248759
02o,17feb10,dlk  Remove FUNCPTR function pointer use entirely.
02n,29may09,dlk  LP64 conversion and POSIXification.
02m,20jun06,jpb  Removed I960 check.
02l,14sep04,dlk  Omit entire contents of this file unless _WRS_KERNEL is
                 defined.
02k,29jun04,dlk  Merged from BASE6_ITER5_FRZ27.
02l,28may04,dlk  Use single socket IO-system device driver with wrappers
                 calling back-end routines.
02k,24mar04,mcm  Including time.h instead of sys/time.h.
02j,15mar04,bwa  added multiple concurrent backends capabalities.
02j,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5-int/2)
02i,08dec03,vvv  updated based on inspection comments
02h,03dec03,asr  Fix compile errors after dinkum libc check-in
02g,14nov03,nee  Adding closeRtn to SOCK_FUNC
02f,05nov03,cdw  Removal of unnecessary _KERNEL guards.
02e,04nov03,rlm  Ran batch header path update for header re-org.
02d,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
02c,10jun03,vvv  include netVersion.h
02b,02feb02,ham  changed for tornado build
02a,15aug01,ann  ported to clarinet from AE1.1 version 01f
*/

#ifndef __INCsockFunch
#define __INCsockFunch

/* includes */
#include <sys/time.h>
#include <sys/socket.h>

#if defined (_WRS_VXWORKS_MAJOR) && (_WRS_VXWORKS_MAJOR >= 6)
#include <ioLib.h> /* For type DEV_HDR */
#else
#include <iosLib.h>
#endif /* defined (_WRS_VXWORKS_MAJOR) && (_WRS_VXWORKS_MAJOR >= 6) */

#ifdef __cplusplus
extern "C" {
#endif

/* HIDDEN */

/* typedefs */

typedef struct sockFunc SOCK_FUNC;

struct socket;  /* defined in net/socketvar.h */

typedef SOCK_FUNC * (*SOCK_FUNC_INIT) (void);

#ifdef __cplusplus
}
#endif

/*
 * sys/socket.h has circular dependencies on this header file, more
 * specifically on type SOCK_FUNC which must be defined. This is why
 * this file must be included after SOCK_FUNC has been defined.
 */
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*SOCK_FUNC_ACCEPT)
    (struct socket **pso,
     struct sockaddr * addr,
     socklen_t * pAddrlen);

typedef STATUS (*SOCK_FUNC_BIND)
    (struct socket * so,
     const struct sockaddr * name,
     socklen_t namelen);

typedef STATUS (*SOCK_FUNC_CONNECT)
    (struct socket * so,
     const struct sockaddr * name,
     socklen_t namelen);

typedef STATUS (*SOCK_FUNC_CONN_TIMEO)
    (struct socket * so,
     const struct sockaddr * name,
     socklen_t namelen,
     const struct timeval * tv);

typedef STATUS (*SOCK_FUNC_GETPEERNAME)
    (struct socket * so,
     struct sockaddr * addr,
     socklen_t * pAddrlen);

typedef STATUS (*SOCK_FUNC_GETSOCKNAME)
    (struct socket * so,
     struct sockaddr * addr,
     socklen_t * pAddrlen);

typedef STATUS (*SOCK_FUNC_LISTEN)
    (struct socket * so,
     int backlog);

typedef ssize_t (*SOCK_FUNC_RECV)
    (struct socket * so,
     void * buf,
     size_t bufLen,
     int flags);

typedef ssize_t (*SOCK_FUNC_RECVFROM)
    (struct socket * so,
     void * buf,
     size_t bufLen,
     int flags,
     struct sockaddr * from,
     socklen_t * pFromLen);

typedef ssize_t (*SOCK_FUNC_RECVMSG)
    (struct socket * so,
     struct msghdr * msg,
     int flags);

typedef ssize_t (*SOCK_FUNC_SEND)
    (struct socket * so,
     const void * buf,
     size_t bufLen,
     int flags);

typedef ssize_t (*SOCK_FUNC_SENDTO)
    (struct socket * so,
     const void * buf,
     size_t bufLen,
     int flags,
     const struct sockaddr * name,
     socklen_t namelen);

typedef ssize_t (*SOCK_FUNC_SENDMSG)
    (struct socket * so,
     const struct msghdr * msg,
     int flags);

typedef STATUS (*SOCK_FUNC_SHUTDOWN)
    (struct socket * so,
     int how);

typedef STATUS (*SOCK_FUNC_SOCKET)
    (int domain,
     int type,
     int protocol,
     struct socket ** pso);

typedef STATUS (*SOCK_FUNC_GETSOCKOPT)
    (struct socket * so,
     int level,
     int optname,
     void * optval,
     socklen_t * optlen);

typedef STATUS (*SOCK_FUNC_SETSOCKOPT)
    (struct socket * so,
     int level,
     int optname,
     const void * optval,
     socklen_t optlen);

typedef BOOL (*SOCK_FUNC_ZBUF) (void);  /* Does the back end support zbufs? */

typedef int (*SOCK_FUNC_CLOSE)
    (struct socket * so);

typedef ssize_t (*SOCK_FUNC_WRITE)
    (struct socket * so,
     const char * buf,
     size_t maxBytes);

typedef ssize_t (*SOCK_FUNC_READ)
    (struct socket * so,
     char * buf,
     size_t maxBytes);

typedef int (*SOCK_FUNC_IOCTL)
    (struct socket *,
     int code,
     _Vx_usr_arg_t arg,
     void * nullForKernel); /* last arg is NULL if from kernel, non-NULL for
			       system call originating in user space. */


struct sockFunc			/* SOCK_FUNC */
    {
    SOCK_FUNC_INIT              libInitRtn; /* Unused */
    SOCK_FUNC_ACCEPT            acceptRtn;
    SOCK_FUNC_BIND              bindRtn;
    SOCK_FUNC_CONNECT           connectRtn;
    SOCK_FUNC_CONN_TIMEO        connectWithTimeoutRtn;
    SOCK_FUNC_GETPEERNAME       getpeernameRtn;
    SOCK_FUNC_GETSOCKNAME       getsocknameRtn;
    SOCK_FUNC_LISTEN            listenRtn;
    SOCK_FUNC_RECV              recvRtn;
    SOCK_FUNC_RECVFROM          recvfromRtn;
    SOCK_FUNC_RECVMSG           recvmsgRtn;
    SOCK_FUNC_SEND              sendRtn;
    SOCK_FUNC_SENDTO            sendtoRtn;
    SOCK_FUNC_SENDMSG           sendmsgRtn;
    SOCK_FUNC_SHUTDOWN          shutdownRtn;
    SOCK_FUNC_SOCKET            socketRtn;
    SOCK_FUNC_GETSOCKOPT        getsockoptRtn;
    SOCK_FUNC_SETSOCKOPT        setsockoptRtn;
    SOCK_FUNC_ZBUF              zbufRtn;

    /*
     * The following IO-system handlers are called via wrappers in
     * sockLib.c:
     */
    SOCK_FUNC_CLOSE             closeRtn;
    SOCK_FUNC_READ              readRtn;
    SOCK_FUNC_WRITE             writeRtn;
    SOCK_FUNC_IOCTL             ioctlRtn;
    };

extern DEV_HDR socketDevHdr;   /* I/O system device driver header */

/* END_HIDDEN */

/* Memory validation function pointers */

#ifdef _WRS_KERNEL
extern int    (*pSockIoctlMemVal) (unsigned int cmd, void * data);
extern STATUS (*pUnixIoctlMemVal) (unsigned int cmd, const void * pData);
#endif

/* Socket map */
extern struct socket **socketMap;

#ifdef __cplusplus
}
#endif

#endif /* __INCsockFunch */
