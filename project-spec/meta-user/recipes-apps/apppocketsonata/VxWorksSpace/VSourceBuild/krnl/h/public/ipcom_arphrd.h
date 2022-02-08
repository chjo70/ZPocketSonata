
/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_ARPHRD_H
#define IPCOM_ARPHRD_H

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

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define IP_ARPHRD_ETHER         IP_IFT_ETHER    /* Ethernet 10Mbps              */
#define IP_ARPHRD_TUNNEL        IP_IFT_TUNNEL   /* IPIP tunnel                  */
#define IP_ARPHRD_LOOPBACK      IP_IFT_LOOP     /* Loopback device              */
#define IP_ARPHRD_VOID          IP_IFT_OTHER    /* Void type, nothing is known */
#define IP_ARPHRD_PPP           IP_IFT_PPP
#define IP_ARPHRD_IEEE80211     IP_IFT_IEEE80211

/* Compatible with Linux */
#define IP_ARPHRD_SIT           776             /* sit0 device - IPv6-in-IPv4   */
#define IP_ARPHRD_TUNNEL6       769             /* IP6IP6 tunnel                */
#define IP_ARPHRD_IPGRE         778             /* GRE over IP                  */
#define IP_ARPHRD_NONE          0xfffe

/* Compatible with Linux; WR only */
#define IP_ARPHRD_TUNNEL6TO4    900
#define IP_ARPHRD_TUNNEL6OVER4  901
#define IP_ARPHRD_IPGRE6        902

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
