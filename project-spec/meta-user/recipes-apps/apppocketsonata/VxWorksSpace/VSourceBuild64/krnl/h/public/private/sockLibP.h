/* sockLibP.h -  Private socket library header file */

/*
* Copyright (c) 2016 Wind River Systems, Inc.
*
* The right to copy, distribute or otherwise make use of this software
* may be licensed only pursuant to the terms of an applicable Wind River
* license agreement.
*/

/*
modification history
--------------------
12apr16,mca  created
*/

#ifndef __INCsockLibPh
#define __INCsockLibPh

/* includes */

#include <sys/types.h>
#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

/* function declarations */

extern int 	_accept (int s, struct sockaddr *addr, socklen_t *addrlen);
extern STATUS 	_bind (int s, const struct sockaddr *name, socklen_t namelen);
extern STATUS 	_connect (int s, const struct sockaddr *name,
                          socklen_t namelen);
extern STATUS 	_getpeername (int s, struct sockaddr *name, socklen_t *namelen);
extern STATUS 	_getsockname (int s, struct sockaddr *name, socklen_t *namelen);
extern STATUS 	_getsockopt (int s, int level, int optname, void *optval,
			    socklen_t *optlen);
extern STATUS 	_listen (int s, int backlog);
extern ssize_t 	_recv (int s, void *buf, size_t bufLen, int flags);
extern ssize_t 	_recvfrom (int s, void *buf, size_t bufLen, int flags,
                           struct sockaddr *from, socklen_t *pFromLen);
extern ssize_t	_recvmsg (int sd, struct msghdr *mp, int flags);
extern ssize_t 	_send (int s, const void *buf, size_t bufLen, int flags);
extern ssize_t 	_sendmsg (int sd, const struct msghdr *mp, int flags);
extern ssize_t 	_sendto (int s, const void *buf, size_t bufLen, int flags,
                         const struct sockaddr *to, socklen_t tolen);
extern int 	_setsockopt (int s, int level, int optname, const void *optval,
                             socklen_t optlen);
extern STATUS 	_shutdown (int s, int how);
extern int 	_socket (int domain, int type, int protocol);

#ifdef __cplusplus
}
#endif

#endif /* __INCsockLibPh */
