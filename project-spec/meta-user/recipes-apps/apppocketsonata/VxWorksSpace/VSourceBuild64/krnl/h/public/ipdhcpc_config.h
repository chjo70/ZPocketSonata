/*
 * Copyright (c) 2006-2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/* 
modification history
--------------------
12mar16,wfl  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
*/ 

#ifndef IPDHCPC_CONFIG_H
#define IPDHCPC_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 *===========================================================================
 *                         IPDHCPC_INCLUDE_CMD
 *===========================================================================
 * Define to include DHCP Client shell command 'dhcpc'.
 */
#define IPDHCPC_INCLUDE_CMD

/*
 *===========================================================================
 *                         DHCP_MAX_MESSAGE_SIZE
 *===========================================================================
 * Maximum DHCP message size the client is willing to accept.
 * Minimum valid value is 576 bytes. Including IP and UDP header length.
 */
#define IPDHCPC_MAX_MESSAGE_SIZE   576

/*
 *===========================================================================
 *                     IPDHCPC_CLIENT_ID_MAXSIZE
 *===========================================================================
 * Maximum size of the DHCP client-identifier size contents (code 61).
 */
#define IPDHCPC_CLIENT_ID_MAXSIZE    32


/*
 *===========================================================================
 *                     IPDHCPC_RFC2131_INIT_DELAY
 *===========================================================================
 * RFC-compliant Congestion Avoidance Initialization Delay.
 * 1 = enabled, 0 = disabled.
 */
#define IPDHCPC_RFC2131_INIT_DELAY    1


/*
 *===========================================================================
 *                     IPDHCPC_RFC2131_EXP_BACKOFF_DELAY
 *===========================================================================
 * RFC-compliant Exponential Back-off Delay between retries.
 * 1 = enabled, 0 = disabled.
 */
#define IPDHCPC_RFC2131_EXP_BACKOFF_DELAY    1


/*
 *===========================================================================
 *                     IPDHCPC_DISCOVER_RETRIES
 *===========================================================================
 * Number of DHCP Client Attempts.
 */
#define IPDHCPC_DISCOVER_RETRIES    4


/*
 *===========================================================================
 *                     IPDHCPC_OFFER_TIMEOUT
 *===========================================================================
 * Number of milliseconds to wait for initial offer from Server. Minimum 200.
 */
#define IPDHCPC_OFFER_TIMEOUT    2000


/*
 *===========================================================================
 *                     IPDHCPC_BOOTP_MODE
 *===========================================================================
 * Operate as BOOTP client only.
 * 1 = enabled, 0 = disabled.
 */
#define IPDHCPC_BOOTP_MODE    0
	

/*
 *===========================================================================
 *                     IPDHCPC_REMOVE_EXISTING_ADDRESSES
 *===========================================================================
 * Delete all unicast addresses from the interface before negotiation begins. 
 * 1 = enabled, 0 = disabled.
 */
#define IPDHCPC_REMOVE_EXISTING_ADDRESSES    1

/*
 *===========================================================================
 *                     IPDHCPC_REMOVE_LEASED_ADDRESS
 *===========================================================================
 * Delete negotiated addresses from interface when lease expires. 
 * 1 = enabled, 0 = disabled.
 */
#define	IPDHCPC_REMOVE_LEASED_ADDRESS    1
	
/*
 *===========================================================================
 *                     IPDHCPC_AUTO_DISABLE
 *===========================================================================
 * Disable DHCP on the interface if a static address is manually applied. 
 * 1 = enabled, 0 = disabled.
 */
#define	IPDHCPC_AUTO_DISABLE    1

/*
 *===========================================================================
 *                     IPDHCPC_TTL
 *===========================================================================
 * IP Time-To-Live Default Setting.  Default is 1.  May be increased to
 * better interoperate with certain DHCP relay agents.
 */

#define IPDHCPC_TTL 1

/*
 *===========================================================================
 *                     IPDHCPC_ASSIGN_IP_TIMEOUT
 *===========================================================================
 * Number of seconds to wait for an address to be assigned to an interface.
 * To allow for address collision detection (if enabled)
 */
#define IPDHCPC_ASSIGN_IP_TIMEOUT    15

/*
 *===========================================================================
 *                     IPDHCPC_FLAGS_BIT_BROADCAST
 *===========================================================================
 * Set the value of flag field:broadcast bit, default is 0. 
 * 1 = enabled, 0 = disabled.
 */
#define	IPDHCPC_FLAGS_BIT_BROADCAST    0

/*
 *===========================================================================
 *                     IPDHCPC_SOCK_MIN_RECV_BUFSIZE
 *===========================================================================
 *  Minimal dhcpc sock recv bufsize
 */
#define	IPDHCPC_SOCK_MIN_RECV_BUFSIZE    16800

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
