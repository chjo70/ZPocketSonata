/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPRADIUS_CONFIG_H
#define IPRADIUS_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

/* Maximum size of access request attribute field. 2048 required for EAP (EAPoL over ethernet) + additional attributes. */
#define IPRADIUS_access_request_attribute_size       2048


/* Maximum size of accounting request attribute field. */
#define IPRADIUS_accounting_request_attribute_size   500

/* Initial system priority. */
#if defined(_WRS_CONFIG_IPRADIUS_SYSLOG_PRIORITY)
#define IPRADIUS_SYSTEM_PRIORITY        _WRS_CONFIG_IPRADIUS_SYSLOG_PRIORITY
#else
#define IPRADIUS_SYSTEM_PRIORITY   	IPCOM_LOG_WARNING
#endif


/* Max poll delay in seconds. */
#define IPRADIUS_MAX_POLL_DELAY         600

/* Minium accounting interval in seconds */
#if defined(IP_DEBUG) || defined(IPTESTENGINE)
#define IPRADIUS_MIN_ACCT_INTERVAL      3
#else
#define IPRADIUS_MIN_ACCT_INTERVAL      60
#endif

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
