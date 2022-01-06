/* hostLibInt.h - private header for hostLib files */

/*
 * Copyright (c) 2001-2005 Wind River Systems, Inc.
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
01h,09may05,vvv  updated ip6_str2scopeid() prototype
01g,05dec03,vvv  moved HOST_LIST_* definitions from hostLib.c
01f,24nov03,vvv  updated for RTP support
01e,20nov03,niq  Remove copyright_wrs.h file inclusion
01d,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01c,21mar03,ann  moved the definition of _hostconf and MAXHOSTCONF from
                 name6.c
01b,21jan02,ann  adding the prototypes for gethostbyname, gethostbyaddr,
                 hostentAlloc and hostentFree
01a,19sep01,hgo  creation
*/

#ifndef __INChostLibInth
#define __INChostLibInth

#ifdef __cplusplus
extern "C" {
#endif

/* Structure definitions */

struct _hostconf {
    FUNCPTR    hostGetByAddr;
    FUNCPTR    dnsGetByAddr;
};

#define HOST_LIST_SIZE   1
#define HOST_LIST_BUF    2

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

/* external functions that are shared within hostLib */

extern struct addrinfo *hostTblSearchByName2 (char *name, const struct addrinfo *hints);
extern struct hostent *hostTblSearchByAddr2 (const void *addr, int af);
extern struct hostent *getipnodebyaddr (const void *src, size_t len, int af, int *errp);
#ifdef INET6
extern int ip6_str2scopeid (char *scope, struct sockaddr_in6 *sin6, u_int32_t *);
#endif
extern struct hostent * _hpcopy (struct hostent * hp);

extern struct netent *getnetbyname (const char *name);

#else	/* __STDC__ */

extern struct addrinfo *hostTblSearchByName2 ();
extern struct hostent *hostTblSearchByAddr2 ();
extern struct hostent *getipnodebyaddr ();
#ifdef INET6
extern int ip6_str2scopeid ();
#endif
extern struct hostent *_hpcopy ();

extern struct netent *getnetbyname ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INChostLibInth */
