/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPDNSC_CONFIG_H
#define IPDNSC_CONFIG_H

#include <ipcom_config.h>

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * DNS Client compile time configuration.
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

#ifdef IPTESTENGINE
#if !defined(IPDNSC_USE_TEST)
#define IPDNSC_USE_TEST
#endif
#endif

/* Define to include support for gated-style MD5 authentication. */
#ifdef IPCOM_USE_MD5
#define IPDNSC_INCLUDE_MD5
#endif


/*
 *===========================================================================
 *                         IPDNSC_CONF_DNS_HOSTS
 *===========================================================================
 * A list of known hosts.
 *
 */
#define IPDNSC_CONF_DNS_HOSTS   { "127.0.0.1", "localhost" }, \
                                { "::1", "localhost6" }, \
                                { IP_NULL, IP_NULL }


/*
 *===========================================================================
 *                         IPDNSC_CONF_MAX_CACHE_ENTRIES
 *===========================================================================
 * The maximum number of entries in the DNS cache.
 *
 */
#define IPDNSC_CONF_MAX_CACHE_ENTRIES       32


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
