/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPNET_LOOPBACK_H
#define IPNET_LOOPBACK_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Loopback interface declarations.
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

#include "ipnet_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#ifdef IP_PORT_LKM
#define IPNET_IF_LOOPBACK_NAME       "lo"  /* Loopback name */
#else
#define IPNET_IF_LOOPBACK_NAME       "lo0" /* Loopback name */
#endif


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

IP_PUBLIC int ipnet_loopback_if_init(struct Ipnet_netif_struct *netif);
IP_GLOBAL int ipnet_loopback_attach(Ip_u16 vr, char *name);
IP_GLOBAL struct Ipnet_netif_struct *ipnet_loopback_get_netif(Ip_u16 vr);
IP_GLOBAL Ip_bool ipnet_is_loopback(Ip_u16 vr, Ip_u32 ifindex);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
