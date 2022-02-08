/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
24jul14,jxy  Networking: PPP CHAP support. (US40661) 
*/


#ifndef IPPPP_CONFIG_H
#define IPPPP_CONFIG_H

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

#include <ipcom_config.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 3                    GENERAL
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         IPPPP_SYSLOG_PRIORITY
 *===========================================================================
 * Initial PPP syslog system priority.
 */
#ifdef IP_DEBUG
#define IPPPP_SYSLOG_PRIORITY        IPCOM_LOG_DEBUG
#else
#define IPPPP_SYSLOG_PRIORITY        IPCOM_LOG_WARNING
#endif


/*
 *===========================================================================
 *                         IPPPP_USE_AUTH_XXX
 *===========================================================================
 * Define for PPP Authentication PAP and/or CHAP support.
 */
#ifdef IPCOM_USE_AUTH
#define IPPPP_USE_AUTH_PAP
#if defined(IPCOM_USE_MD5) && defined(IPCOM_USE_KEY_DB)
#define IPPPP_USE_AUTH_CHAP
#endif
#endif


/*
 *===========================================================================
 *                         IPPPP_USE_RFC1877_XXX
 *===========================================================================
 * Define for PPP RFC1877 client/server support (Primary & secondary DNS/NBNS)
 */
#ifndef IPLITE
/*#define IPPPP_USE_RFC1877_SERVER*/
#define IPPPP_USE_RFC1877_CLIENT
#endif


/*
 ****************************************************************************
 * 4                       PPPOE
 ****************************************************************************
 */


/*
 *===========================================================================
 *                         IPPPP_USE_PPPOE
 *===========================================================================
 * Define to support PPPoE (in 'server' mode only)
 */
#define IPPPP_USE_PPPOE


/*
 *===========================================================================
 *                         IPPPP_USE_PPPMP
 *===========================================================================
 * Define to support PPPMP
 */
#if defined(IP_PORT_VXWORKS) && (_WRS_CONFIG_IPPPP_MP)
#define IPPPP_USE_PPPMP
#else
/*
#define IPPPP_USE_PPPMP
*/
#endif

/*
 *===========================================================================
 *                         IPPPP_MAX_LINKS
 *===========================================================================
 * If PPPMP is not being used, this macro must always be set to 1.
 */
#if defined(IPPPP_USE_PPPMP)

/*
 * Maximum bundle size
 */
#define IPPPP_MAX_LINKS   3

/*
 * Maximum receive reconstructed unit
 */
#define IPPPP_PPPMP_MRRU_MAX                3000

/*
 * Size of endpoint discriminator
 */
#define IPPPPMP_EPD_DATA_MAX 20  /* RFC 1990 sec. 5.1.3 */

/*
 * Enable multilink fragment timer
 * default timeout 20 seconds.
 */
/*
#define IPPPP_PPPMP_FRAGMENT_TIMER
#define IPPPP_PPPMP_TIMEOUT_LENGTH         20000
*/

#else /* not IPPPP_USE_PPPMP */
#define IPPPP_MAX_LINKS   1
#endif


/*
 *===========================================================================
 *                         IPPPP_USE_VJCOMP
 *===========================================================================
 * Define to support Van Jacobson compression of TCP/IP headers
 * (for TCP/IP only)
 */
/*
#ifdef IPCOM_USE_INET
#define IPPPP_USE_VJCOMP
#endif
*/

#ifdef IPPPP_USE_VJCOMP
/*
 * Maximum number of simultaneous connections
 * (see dicussion of MAX_STATES in rfc1144.c)
 */
#define IPPPP_VJCOMP_MAX_SLOTS             16

/*
 * Allow slot ID to be compressed in VJC compressed
 * packet? (0 means NO, 1 means OK)
 */
#define IPPPP_VJCOMP_COMP_SLOT_ID          0
#endif

/*
 *===========================================================================
 *                         IPPPP_PPPOE_USE_MD5
 *===========================================================================
 * Define if you want to use the PPPoE AC_Cookie to better protect vs DOS attacks.
 */
#if defined(IPPPP_USE_PPPOE) && !defined(IPLITE)
#define IPPPP_PPPOE_USE_MD5
#endif

/*
 *===========================================================================
 *                         IPPPP_USE_PPPL2TP
 *===========================================================================
 * Define to support PPP over L2TPv2
 */
/*
#ifdef IPL2TP
#define IPPPP_USE_PPPL2TP
#endif
*/

/*
#ifdef IPPPP_USE_PPPL2TP
#define IPPPP_USE_PPPL2TP_LNS
#endif
*/

/*
 ****************************************************************************
 * 5                       DO NOT EDIT
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         IPPPP_USE_AUTH
 *===========================================================================
 * NO NOT EDIT!
 */
#if defined(IPPPP_USE_AUTH_PAP) || defined(IPPPP_USE_AUTH_CHAP)
#define IPPPP_USE_AUTH
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
