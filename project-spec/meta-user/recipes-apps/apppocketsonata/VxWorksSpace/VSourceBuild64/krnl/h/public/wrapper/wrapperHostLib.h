/* wrapperHostLib.h - public header for hostlib wrapper files */

/*
 * Copyright (c) 2006, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
19sep16,brk  removed ifdef here and duplicate definition in netdb.h
24nov10,h_x  Fix WIND00239714
14nov06,tlu  Replace <socket.h> by <sys/socket.h> 
12oct06,kch  Removed freehostent() prototype.
12sep06,tlu  Remove the condition to include socket.h
09sep06,tlu  Added socket.h for RTP build
31jul06,tkf  Written
*/

#ifndef __INCwrapperHostLibh
#define __INCwrapperHostLibh

#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

struct addrinfo;

IMPORT struct hostent * gethostbyaddr (const char *addr, int len, int type);
IMPORT struct hostent * gethostbyname (const char *name);
IMPORT struct servent *getservbyname (const char *name, const char *proto);
IMPORT struct servent *getservbyport (int port, char *proto);

IMPORT int getnameinfo (const struct sockaddr *sa, socklen_t salen, char *host,
                             size_t hostlen, char *serv, size_t servlen, int flags);
IMPORT int getaddrinfo (const char *hostname, const char *servname,
                        const struct addrinfo *hints, struct addrinfo **result);
IMPORT void freeaddrinfo (struct addrinfo *ai);
IMPORT char *gai_strerror (int ecode);

IMPORT int 	gethostname (char *name, size_t nameLen);
IMPORT int 	sethostname (char *name, int nameLen);
IMPORT struct hostent *_dns_ghbyaddr(const void *addr, int addrlen, int af, int *errp);

#ifdef __cplusplus
}
#endif

#endif /* __INCwrapperHostLibh */
