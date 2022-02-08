/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_WAITIF_H
#define IPCOM_WAITIF_H

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
 * 5                    FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_waitif_address
 *===========================================================================
 * Description: check interface enabled dhcp to get an IP address assigned.
 * Parameters: 
 * Returns:     0 = success, -1 = error, and sets errno.
 *
 */
IP_PUBLIC int
ipcom_waitif_address();

/*
 *===========================================================================
 *                    ipcom_waitif
 *===========================================================================
 * Description: Wait for interface to get an IP address assigned.
 * Parameters:  ifindex - Index of the interface to wait for.
 *                        0 = any interface except loopback.
 *              domain - The address domain.
 * Returns:     0 = success, -1 = error, and sets errno.
 *
 */
IP_PUBLIC int
ipcom_waitif(int ifindex, int domain);

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

