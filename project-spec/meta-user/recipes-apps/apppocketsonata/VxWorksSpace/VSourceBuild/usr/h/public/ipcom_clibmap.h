/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_CLIBMAP_H
#define IPCOM_CLIBMAP_H

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

#include "ipcom_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if defined(IP_DEBUG) || defined(WRS_IPLITE)
#define IPCOM_MALLOC 1
#define IPCOM_CALLOC 1
#define IPCOM_REALLOC 1
#define IPCOM_FREE 1
#ifdef WRS_IPLITE
#define IPCOM_STRDUP 1
#endif
#endif /* IP_DEBUG */

#define IPCOM_RANDOM 1
#define IPCOM_SRANDOM 1
#define IPCOM_RAND 1
#define IPCOM_SRAND 1

#define IPCOM_EXIT 1
#define IPCOM_ABORT 1
#define IPCOM_SIGNAL 1

#define IPCOM_GETUID 1

#define IPCOM_PERROR 1
#define IPCOM_STRERROR_R 1

#define IPCOM_STRCASECMP 1
#define IPCOM_STRNCASECMP 1

#define IPCOM_QSORT 1
#define IPCOM_BSEARCH 1
#define IPCOM_ISASCII 1

#define IPCOM_MICROTIME 1
#define IPCOM_TIMES 1
#define IPCOM_GETTIMEOFDAY 1
#define IPCOM_SETTIMEOFDAY 1
#define IPCOM_ASCTIME_R ipcom_asctime_r_vxworks
#define IPCOM_CTIME_R ipcom_ctime_r_vxworks

#define IPCOM_TZSET 1

#define IPCOM_NORMPATH 1

#if IP_PORT_VXWORKS <= 60
#define IPCOM_SNPRINTF 1
#define IPCOM_VSNPRINTF 1
#endif

#ifdef IPCOM_FORWARDER_NAE

#ifdef IPCOM_USE_OCTEON_FORWARDER
#define IPCOM_PRINTF ipcom_mipc_printf
#define IPCOM_SYSLOG ipcom_mipc_syslog
#endif

#endif

#ifdef IPCOM_USE_P4080_FORWARDER
      /* For now, only use hv printf on p4080 */
#if defined(IPCOM_USE_FORWARDER) && defined(_WRS_CONFIG_WRHV_GUEST)
    /* use hypervisor printf */
#define IPCOM_PRINTF ipcom_hv_printf
#define IPCOM_SYSLOG ipcom_hv_syslog
#endif
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

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

