/* hostLib.h - public header for hostLib files */

/*
 * Copyright (c) 1984-2007, 2012, 2014 Wind River Systems, Inc.
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
09jan12,h_x  Move extern "C" after last header file include.
23aug07,tkf  Add scopeStr field to ADDR6 as part of the fix for
                 CQ:WIND00102553
07jun07,tkf  Remove #ifdef INET from around ADDR4 (WIND00095796)
24apr07,tkf  Add IPv6-Only build support.
27feb07,dlk  Remove freehostent() prototype.  Add HOSTENT_ALLOC_* defines.
12feb07,dlk  Add rtpHostLibInit() prototype.
21nov06,tlu  Remove errCode from structure addrinfoArgs
08nov06,tkf  Corrected misplacement of freehostent declaration. Also added
                 wrapperHostLib.h for backwards compatibility.
16oct06,kch  Added addrinfoArgs definition for passing arguments to sysctl.
28sep06,kch  Restore freehostent() prototype.
16sep06,tlu  Remove getservbyport(), getservbyname(), getnameinfo(),
                 getaddrinfo(), gethostbyaddr(), gethostbyname(), 
                 freeaddrinfo(), freehostent(), gethostname(), sethostname(), 
                 gai_strerror(), those function prototyping were moved to 
                 wrapper/wrapperHostLib.h
24aug06,tkf  Remove gethostbynameInit() and gethostbyaddrInit()
                 prototypes.
19jun06,jpb  Removed I960 check.
28jun05,vvv  updated gethostbynameInit() prototype
07feb05,vvv  _KERNEL cleanup
14jan05,vvv  osdep.h cleanup
22sep04,dlk  Added declaration for hostTblSetup().
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
07dec03,vvv  moved definition of struct hostArgs from hostLib.c; moved
		 definition of getnameinfoArgs from getnameinfo.c
24nov03,vvv  updated for RTP support
20nov03,niq  Remove copyright_wrs.h file inclusion
05nov03,cdw  Removal of unnecessary _KERNEL guards.
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
23oct03,rlm  updated #includes for header re-org
06aug03,nee  Accordion Base6 merge from ACCORDION_BASE6_MERGE_BASELINE
                 label
09may03,vvv  included vwModNum.h and in6.h
20feb03,ann  added prototypes for gethostbyaddrInit and gethostbynameInit
06sep01,hgo  modifications and extensions for IPv6
20aug97,jag  added function declations for hostTblSearchByAddr(),
                 hostTblSearchByName() (SPR #9175)
19may97,spm  added S_hostLib_INVALID_PARAMETER error value
22sep92,rrr  added support for c++
27jul92,elh  Moved hostShow to netShow.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
13apr89,shl  added MAXHOSTNAMELEN.
04jun88,gae  changed S_remLib_* to S_hostLib_*.
28may88,dnw  extracted from remLib.h
*/

#ifndef __INChostLibh
#define __INChostLibh

#include <wrapper/wrapperHostLib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <lstLib.h>
#include <vwModNum.h>
#include <net/if.h>

#ifdef INET6
#include <netinet6/in6.h>
#endif /* INET6 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 	64
#endif

#define HOST_INET6_ADDR_LEN (USR_NET_IP6ADDR_LEN + IFNAMESIZ)

/* status messages */

#define S_hostLib_UNKNOWN_HOST			(M_hostLib | 1)
#define S_hostLib_HOST_ALREADY_ENTERED		(M_hostLib | 2)
#define S_hostLib_INVALID_PARAMETER             (M_hostLib | 3)
/* former h_errno values */
#define S_hostLib_NETDB_INTERNAL                (M_hostLib | 4)  /* see errno */
/* Authoritative Answer Host not found */
#define S_hostLib_HOST_NOT_FOUND                (M_hostLib | 5)
/* Non-Authoritative Host not found, or SERVERFAIL */
#define S_hostLib_TRY_AGAIN                     (M_hostLib | 6)
/* Valid name, no data record of requested type */
#define S_hostLib_NO_RECOVERY                   (M_hostLib | 7)

/* Definitions for sysctl nodes under CTL_NET */

#define HOSTLIB    3
#define NAMEINFO   4
#define ADDRINFO   5    

/* Options for the host library sysctl handler */

#define HOSTADD          1
#define HOSTDELETE       2
#define HOSTADDRSEARCH   3
#define HOSTNAMESEARCH   4
#define HOSTNAMESEARCH2  5

/* Current hostentAlloc() limits: */

/* space allocated for address in hostent::h_addr_list[0] */
#define HOSTENT_ALLOC_MAXADDRS	24
/* space allocated for name in hostent::h_name */
#define HOSTENT_ALLOC_MAXNAME	(NI_MAXHOST + 1)
/* Reentrant implementation, requiring hostentFree() of result? */
#define GETHOSTBYNAME_REENTRANT
#define GETHOSTBYADDR_REENTRANT

/*
 * Structure shared by hostAdd, hostDelete and hostTblSearchByName2
 * for passing arguments to sysctl.
 */

struct hostArgs
    {
    char * hostName;
    int    hostNameLen;
    char * hostAddr;
    int    hostAddrLen;
    const struct addrinfo * pHints;
    };

/*
 * This structure is used to pass the getnameinfo arguments from user-space
 * to the kernel using sysctl.
 */

struct nameinfoArgs
    {
    const struct sockaddr * sa;
    socklen_t               salen;
    char *                  host;
    size_t                  hostlen;
    char *                  serv;
    size_t                  servlen;
    int                     flags;
    };

/*
 * This structure is used to pass the getaddrinfo arguments from user-space
 * to the kernel using sysctl.
 */

struct addrinfoArgs
    {
    const char 		   * hostname;
    int			     hostnamelen;
    const char             * servname;
    int			     servnamelen;
    const struct addrinfo  * hints;
    };

#ifdef _WRS_KERNEL
/* typdef's for hosttable access */

typedef struct hostname_struct
    {
    struct hostname_struct *link;
    char *name;
    } HOSTNAME;

typedef struct addr4_struct
    {
    struct in_addr addr;
    } ADDR4;

#ifdef INET6
typedef struct addr6_struct
    {
    struct in6_addr addr;
    uint32_t scopeId;
    char scopeStr [IFNAMSIZ];
    } ADDR6;
#endif

typedef union addr_union
    {
    ADDR4 addr4;
#ifdef INET6
    ADDR6 addr6;
#endif
    } ADDRU;

typedef struct
    {
    NODE node;
    HOSTNAME hostName;
    int family;                   /* AF_INET or AF_INET6 */
    ADDRU netAddr;                /* ADDR4 or ADDR6 */
    } HOSTENTRY;
#endif  /* _WRS_KERNEL */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	hostAdd (char *hostName, char *hostAddr);
extern STATUS 	hostDelete (char *name, char *addr);
extern STATUS 	hostGetByAddr (int addr, char *name);
extern int 	hostGetByName (char *name);
extern struct hostent * hostentAlloc (void);
extern void hostentFree (struct hostent *);

#ifdef _WRS_KERNEL
extern STATUS 	hostTblInit (void);
extern STATUS   hostTblSetup (char * pRemoteName, char * pRemoteAddr,
			      char * pLocalName, char * pLocalAddr);
extern int      hostTblSearchByName (char *name);
extern STATUS   hostTblSearchByAddr (int addr, char *name);
extern STATUS   rtpHostLibInit (void);
#endif /* _WRS_KERNEL */

#else	/* __STDC__ */

extern STATUS 	hostAdd ();
extern STATUS 	hostDelete ();
extern STATUS 	hostGetByAddr ();
extern int 	hostGetByName ();
extern struct hostent * hostentAlloc ();
extern void hostentFree ();

#ifdef _WRS_KERNEL
extern STATUS 	hostTblInit ();
extern STATUS   hostTblSetup ();
extern int      hostTblSearchByName ();
extern STATUS   hostTblSearchByAddr ();
extern STATUS   rtpHostLibInit ();
#endif /* _WRS_KERNEL */

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INChostLibh */
