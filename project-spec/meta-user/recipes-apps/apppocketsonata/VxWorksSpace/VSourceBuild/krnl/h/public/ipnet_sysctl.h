/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPNET_SYSCTL_H
#define IPNET_SYSCTL_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */
/* IPNET sysctl */

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

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    Ipnet_cmd_sysctl
 *===========================================================================
 * Parameter struct used for registering IPNET base table.
 */
typedef struct Ipnet_cmd_sysctl_struct
{
    const char                              *comp;

    int                                     type;
    int                                     argument;

    const struct Ipnet_cmd_sysctl_struct    *ntable;
    int                                     ctl[3];
} Ipnet_cmd_sysctl;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipnet_sysctl_get_base
 *===========================================================================
 * Description: This routine exposes the IPNET sysctl tree root node.
 * Parameters: None.
 * Returns: A pointer to Ipnet_cmd_sysctl
 *
 */
IP_PUBLIC Ipnet_cmd_sysctl * ipnet_sysctl_get_base(void);

#ifdef __cplusplus
}
#endif

#endif /* IPNET_SYSCTL_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
