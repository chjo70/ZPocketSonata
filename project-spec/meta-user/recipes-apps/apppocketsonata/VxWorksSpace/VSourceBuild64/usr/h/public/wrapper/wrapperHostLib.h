/* wrapperHostLib.h - public header for hostlib wrapper files */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
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
01f,24nov10,h_x  Fix WIND00239714
01e,14nov06,tlu  Replace <socket.h> by <sys/socket.h> 
01d,12oct06,kch  Removed freehostent() prototype.
01c,12sep06,tlu  Remove the condition to include socket.h
01b,09sep06,tlu  Added socket.h for RTP build
01a,31jul06,tkf  Written
*/

#ifndef __INCwrapperHostLibh
#define __INCwrapperHostLibh

#include <sys/socket.h>

#ifdef __cplusplus
extern "C" {
#endif

struct addrinfo;

#if defined(__STDC__) || defined(__cplusplus)

IMPORT struct hostent * gethostbyaddr (const char *addr, int len, int type);
IMPORT struct hostent * gethostbyname (const char *name);
IMPORT struct servent *getservbyname (const char *name, const char *proto);
IMPORT struct servent *getservbyport (int port, char *proto);

#ifndef __INCnetdbh
IMPORT int getnameinfo (const struct sockaddr *sa, socklen_t salen, char *host,
                             size_t hostlen, char *serv, size_t servlen, int flags);
IMPORT int getaddrinfo (const char *hostname, const char *servname,
                        const struct addrinfo *hints, struct addrinfo **result);
IMPORT void freeaddrinfo (struct addrinfo *ai);
IMPORT char *gai_strerror (int ecode);
#endif

IMPORT int 	gethostname (char *name, size_t nameLen);
IMPORT int 	sethostname (char *name, int nameLen);
IMPORT struct hostent *_dns_ghbyaddr(const void *addr, int addrlen, int af, int *errp);

#else	/* __STDC__ */

IMPORT int getnameinfo ();
IMPORT struct hostent * gethostbyaddr ();
IMPORT struct hostent * gethostbyname ();
IMPORT struct servent *getservbyname ();
IMPORT struct servent *getservbyport ();
IMPORT int getaddrinfo ();
IMPORT void freeaddrinfo ();
IMPORT char *gai_strerror ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCwrapperHostLibh */
