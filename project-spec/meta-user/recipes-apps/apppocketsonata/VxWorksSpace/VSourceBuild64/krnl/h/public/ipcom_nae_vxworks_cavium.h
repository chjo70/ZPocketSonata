/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#define IPCOM_NAE_VXWORKS_CAVIUM_H

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define IPCOM_OCTEON_POW_FORWARDER_GRP (13) /* 14, 15 used by END driver */


IP_PUBLIC void *ipcom_forwarder_attach_nae_netif_cavium(int port, int if_index);


/*
 ******************************************************************************
 * End of file
 ******************************************************************************
*/
