/* sockLib.h -  UNIX BSD 4.3 compatible socket library header */

/*
* Copyright (c) 1984-2005, 2009, 2011, 2014 Wind River Systems, Inc.
*
* The right to copy, distribute or otherwise make use of this software
* may be licensed only pursuant to the terms of an applicable Wind River
* license agreement.
*/

/*
modification history
--------------------
12apr16,mca  Added user mode sockets (F6564)
31dec14,brk  Move POSIX functions to sys/socket.h so they are available here and
             in standard POSIX location (F972)
05jan11,h_x  Fix WIND00248759
28may09,dlk  Change to Posix-compatible signatures, apart from 'restrict'
                 (LP64 conversion).
17aug05,mcm  Using sys/time.h for RTP space.
14sep04,dlk  Omit kernel APIs when _WRS_KERNEL is not defined.
28may04,dlk  Make all socket back-ends share a single IO system device.
		 Remove fdMax parameter to sockLibInit().
24mar04,mcm  Including time.h instead of sys/time.h.
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5-int/1)
18nov03,nee  adding <sys/time.h> for RTPs
05nov03,cdw  Removal of unnecessary _KERNEL guards.
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
27oct03,cdw  update include statements post header re-org.
24oct03,cdw  update include statements post header re-org.
10jun03,vvv  include netVersion.h
27feb02,ann  correcting the path to sockFunc.h after relocation
02feb02,ham  changed for tornado build.
30oct01,ppp  merging from munich
28aug01,ann  correcting the return value in the prototype for sockLibInit
15aug01,ann  ported to clarinet from AE1.1 version 02l.
*/

#ifndef __INCsockLibh
#define __INCsockLibh

#include <sys/time.h>
#include <sys/socket.h>

#include <version.h>

/* typedefs */

#include <sockFunc.h>

#ifdef __cplusplus
extern "C" {
#endif

struct sockFunc; /* See sockFunc.h */

typedef struct sockFunc * (*SOCK_LIB_INIT_RTN) (void);

/* function declarations */

extern STATUS   sockLibInit (void);
extern STATUS 	sockLibAdd (SOCK_LIB_INIT_RTN sockLibInitRtn, int domainMap,
                            int domainReal);


#if defined(_WRS_KERNEL) ||			\
    defined(RUNTIME_64BIT_NAME)  ||	\
    (_WRS_VXWORKS_MAJOR >= 7)    || \
    (_WRS_VXWORKS_MAJOR == 6 && _WRS_VXWORKS_MINOR >= 9)
extern STATUS 	connectWithTimeout (int sock, const struct sockaddr *adrs,
				    socklen_t adrsLen, const struct timeval *timeVal);
#else
extern STATUS 	connectWithTimeout (int sock, struct sockaddr *adrs,
				    int adrsLen, struct timeval *timeVal);
#endif


#ifdef __cplusplus
}
#endif

#endif /* __INCsockLibh */
