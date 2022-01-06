/*
 * Copyright (c) 2006-2013, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23aug16,kjn  Enable selective ACK, the default configuration must be able to
             pass conformance tests like ANVL and robustness tests like
             Achilles.
09mar15,zan  Disable Selective ACK option
08jan15,ljl  Add support for rfc6528 secure sequence number, V7NET-499
*/

#ifndef IPTCP_CONFIG_H
#define IPTCP_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
 * Configuration for IPTCP. Parameters that are macros can only be changed
 * before compiling, variables can be changed before compiling and linking.
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_config.h>

#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#ifdef IPCRYPTO
#include <ipcrypto_config.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 * 3                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 4                       CONFIGURATION
 ****************************************************************************
 */

#ifdef IPLITE
IP_EXTERN IP_CONST int iptcp_conf_connection_timeout;
IP_EXTERN IP_CONST int iptcp_conf_msl;
IP_EXTERN IP_CONST int iptcp_conf_max_mss;
#endif /* IPLITE */

IP_EXTERN IP_CONST int iptcp_conf_default_backlog;


/*
 *===========================================================================
 *                      IPTCP_USE_TIMESTAMP_OPT
 *===========================================================================
 * Define to include support for TCP Timestamp Options as described in
 * in RFC 1323.
 */
#define IPTCP_USE_TIMESTAMP_OPT

/*
 *===========================================================================
 *                      IPTCP_USE_SACK_OPT
 *===========================================================================
 * Define to include support for TCP Selective Acknowledgment Options
 * as described in RFC 2018.
 */
#define IPTCP_USE_SACK_OPT

/*
 *===========================================================================
 *                      IPTCP_USE_MD5_SIGNATURE_OPT
 *===========================================================================
 * Define to include support for MD5 signatures on TCP segments as described
 * in RFC 2385.
 */
#ifdef IPCOM_USE_MD5
#define IPTCP_USE_MD5_SIGNATURE_OPT
#endif

/*
 * Define to include support for secure Initial Sequence Number as described
 * in RFC 6528
 */
#if defined(IPNET) && defined(IPCOM_USE_MD5)
#define IPTCP_USE_SECURE_ISN
#endif


/* RFC5925 8
 *    >> TCP implementations that support TCP MD5 MUST support TCP-AO.
 */
#ifdef IPTCP_USE_MD5_SIGNATURE_OPT
/*
 *===========================================================================
 *                      IPTCP_USE_AO
 *===========================================================================
 * Define to include support for TCP Authentication Option on TCP segments as
 * described in RFC 5925.
 */
#define IPTCP_USE_AO
/*
 *===========================================================================
 *                      IPTCP_USE_AO_CMD
 *===========================================================================
 * Define to include support for the manegement of MKT(Master Key Tuple) in
 * TCP Authentication Option, if disable this, you can use "set/getsockopt"
 * to set the information that AO needed, this will ONLY affect the current
 * socket, the socket pairs(5 tuple) can be treated as special MKT.
 */
#define IPTCP_USE_AO_CMD
#endif

#ifdef IPTCP_USE_AO
#ifndef OPENSSL_NO_SHA
#define IPTCP_USE_AO_SHA
#endif

#if !defined(OPENSSL_NO_AES) && defined(_WRS_CONFIG_OPENSSL)
#define IPTCP_USE_AO_AESCMAC
#endif
#endif

/*
 *===========================================================================
 *                         IPCOM_SYSLOG_PRIORITY
 *===========================================================================
 * Default syslog priority.
 */
#ifdef IP_DEBUG
#define IPTCP_SYSLOG_PRIORITY  IPCOM_LOG_INFO /* (see ipcom_syslog.h) */
#else
#define IPTCP_SYSLOG_PRIORITY  IPCOM_LOG_WARNING
#endif


/*
 *===========================================================================
 *                         IPTCP DEBUG/ASSERT
 *===========================================================================
 * Define IPTCP_ASSERT and/or IPTCP_DEBUG to debug IPTCP.
 */

#ifdef IP_ASSERT
#define IPTCP_ASSERT
#endif

#ifdef IP_DEBUG
#define IPTCP_DEBUG
#endif



#ifdef __cplusplus
}
#endif

#endif /* IPTCP_CONFIG_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

