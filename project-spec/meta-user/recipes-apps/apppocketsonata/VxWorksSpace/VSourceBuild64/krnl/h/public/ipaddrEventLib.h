/* ipaddrEventLib.h - ip address event library header */

/*
 * Copyright (c) 2015,  Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23sep15,wfl  written
*/

#ifndef __INCipaddrEventLibh
#define __INCipaddrEventLibh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* For ip/ipv6 address event type */
typedef enum ipaddrEvent
{
    IP_ADDREVENT_BASE  = 0, /* not use */ 
    IP_ADDREVENT_INET_DADBEGIN,
    IP_ADDREVENT_INET_DADFAILED,
    IP_ADDREVENT_INET_DADSUCCESS,
    IP_ADDREVENT_INET_DADABORTED,
    IP_ADDREVENT_INET6_DADBEGIN,
    IP_ADDREVENT_INET6_DADFAILED,
    IP_ADDREVENT_INET6_DADSUCCESS,
    IP_ADDREVENT_INET6_DADABORTED,
    /* add new type  here */
    IP_ADDREVENT_MAX
} IPADDR_EVENT;

#define MAX_IPADDREVT_HOOKS 1

typedef void (* IPADDREVENT_HOOK)(IPADDR_EVENT eventType, unsigned int ifindex, void *address, void *mac);

/* externals */
extern IPADDREVENT_HOOK			ipAddressEventHookTbl[];
extern IPADDREVENT_HOOK* pIpAddressEventHookTbl;
extern int ipAddressEventHookTblSize;

/* function declarations */

extern int 	ipAddressEventHookAdd    (IPADDREVENT_HOOK ipaddreventHook);
extern int 	ipAddressEventHookDelete (IPADDREVENT_HOOK ipaddreventHook);
void ipAddressEventHookProcess(enum ipaddrEvent eventType, unsigned int ifindex, void *address, void *mac);
void ipv4AddressEventHookProcess(enum ipaddrEvent eventType, unsigned int ifindex, unsigned int address, void *mac);

#ifdef __cplusplus
}
#endif

#endif /* __INCftpLibh */
