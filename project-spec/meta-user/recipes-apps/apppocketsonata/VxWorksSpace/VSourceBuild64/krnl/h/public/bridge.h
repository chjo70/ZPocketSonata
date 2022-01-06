/* bridge.h - simple learning bridge declarations */

/* Copyright (c)  2000, 2003-2007, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
22apr14,hax fix defect V7NET-3 for bridge building issue
21nov07,tlu  Move BRIDGE_PORT_INFO structure here
07sep06,tlu  Increment version number
21jul05,svk  Increment version number for Service Pack 1
07feb05,svk  Increment version number
19jul04,svk  Increment version number
07may03,svk  Add support for static mac addresses in bridge station cache
17apr03,svk  Implement version number, update copyright
27sep00,jhl  created
*/


#ifndef __INCbridgeh
#define __INCbridgeh


#ifdef INCLUDE_IPFIREWALL_SUPPORT
#include <ipnet_netif.h>
#endif

#include <etherMultiLib.h>
#include "endLib.h"
#include "endMedia.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define BRIDGE_VERSION	"1.3.3"

#define BRIDGE_STATIC_FLAG  0x00000001  /* Station cache entry is static */

#ifdef _WRS_CONFIG_BRIDGE_DEBUG
#ifndef BRIDGE_DEBUG
#define BRIDGE_DEBUG
#endif
#endif

#ifdef INCLUDE_DHCP_RELAY_AGENT
typedef struct
{
    NODE        node;      /* for list */
    char       *circuitID; /* circuit identifier */
    char       *remoteID;  /* remote identifier */

    /* statistics */
    int         giaddrZeroWithOption82;

    /* list for relay identifier */
    char       *shareKey;  /* share key for AUTH */
    int         relayID;   /* relay identifier */
    /* current send Replay Detection count value */
    UINT        curSendRDCount;
    /* current received Replay Detection count value */
    UINT        lastRecvRDCount;
    BOOL        notFirstPacket;
} BRIDGE_DHCPR_INFO;
#endif

/* bridge port information */
typedef struct
    {
    NODE        node;               /* must be first member in the structure */
    char        name[END_NAME_MAX];
    int         unitNum;
#ifdef INCLUDE_IPFIREWALL_SUPPORT
    Ipnet_netif *netif;
#endif
    void*       pMuxBindCookie;
    char        portType;
#ifdef INCLUDE_DHCP_RELAY_AGENT
    BOOL        trustFlag;
    BRIDGE_DHCPR_INFO DhcpR;
#endif
    struct ifqueue errSndq;
#ifdef INCLUDE_IPFIREWALL_SUPPORT
    Ipcom_pkt *firewallPkt;
#endif
    } BRIDGE_PORT_INFO;


IMPORT const char * bridgeVersion;

IMPORT STATUS   bridgeInit(void);
IMPORT STATUS   bridgePortAdd(char* pDevName, int unitNum);
IMPORT STATUS   bridgePortRemove(char* pDevName, int unitNum);
IMPORT STATUS   bridgeMacAdd(char* pDevName, int unitNum, char* pMacAddr,
			     UINT32 flags);
IMPORT STATUS   bridgeMacRemove(char* pMacAddr);

#ifdef  __cplusplus
}
#endif

#endif  /* __INCbridgeh */


/***************************************************************************
 * END OF FILE
 ***************************************************************************/

