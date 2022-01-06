/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_AUTOCONF_H
#define IPCOM_AUTOCONF_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * IPCOM AUTO Configuration. Do NOT modify this file!
 *
 * Also see config/ipcom_config.[ch].
 * Also see port/<rtos>/config/ipcom_pconfig.h for RTOS port specific config.
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
 * 3                    FEATURES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         release
 *===========================================================================
 */

#define IPCOM_RELEASE 60900


/*
 *===========================================================================
 *                         misc
 *===========================================================================
 */

#if !defined(__FUNCTION__) && !defined(__GNUC__) && !defined(__DCC__)
/* Define if your compiler does not support the __FUNCTION__ macro. */
#define __FUNCTION__  ""
#endif


/*
 *===========================================================================
 *                         IPCOM_FILE_ROOT
 *===========================================================================
 */
#if IPCOM_USE_FILE == IPCOM_FILE_IPCOM
#define IPCOM_FILE_ROOT   "/ram/"
#elif IPCOM_USE_FILE == IPCOM_FILE_NATIVE && defined(IPCOM_FILE_NATIVE_ROOT)
#define IPCOM_FILE_ROOT   IPCOM_FILE_NATIVE_ROOT
#else
#define IPCOM_FILE_ROOT   "."
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_DMALLOC
 *===========================================================================
 * Use IPCOM debug malloc/free functions on top of the normal malloc/free.
 */
#if defined(IP_DEBUG) && \
   !defined(IPCOM_USE_DMALLOC) &&              \
   !defined(IPBOUNDS) && \
   !defined(IP_PORT_OSE5) && \
   !defined(IP_PORT_LKM) && \
   !defined(IP_PORT_VXWORKS) && \
   !defined(OSE_REFSYS) && \
   !defined(NETSNMP_INTERPEAK) && \
   !defined(IPEMANATE) && /*&& !defined(GATED_INTERPEAK)*/ \
   !defined(IPVALGRIND)
#define IPCOM_USE_DMALLOC
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_TCP
 *===========================================================================
 * Define if you want to include TCP support.
 */
#if IPCOM_USE_SOCK == IPCOM_SOCK_NATIVE || defined(IPTCP) || \
    defined(IP_PORT_OSE5) || defined(OSE_REFSYS) || defined(IPLITE)
#define IPCOM_USE_TCP
#endif

#if !defined(IPCOM_USE_TCP) && IPCOM_USE_SHELL != IPCOM_SHELL_NONE && !defined(IPNGC)
#error TCP support is required for shell. Maybe you are missing IPTCP?
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_ETHERNET
 *===========================================================================
 * Define if your stack supports Ethernet.
 */
#ifndef IP_TARGET_SC8102
#define IPCOM_USE_ETHERNET
#endif


/*
 *===========================================================================
 *                         IPCOM_USE_PACKET
 *===========================================================================
 * Define to support the IP_AF_PACKET domain.
 */
#if !defined(IPCOM_FORWARDER_NAE) && (defined(IPNET) || (defined(IP_PORT_VXWORKS) && defined(IPLITE)) || defined(IPPRISM) || defined(IP8021X) || defined(IPMACSEC))
#define IPCOM_USE_PACKET
#endif


/*
 *===========================================================================
 *                         IPCOM_USRLIB
 *===========================================================================
 */
#if (defined(IP_PORT_OSE5) || defined(IPCOM_USE_USRLIB)) && !defined(IPCOM_USRLIB)
#define IPCOM_USRLIB
#endif


/*
 *===========================================================================
 *                         IPCOM_SOCK
 *===========================================================================
 * IPCOM_SOCK is set with IPLITE, IPNET or either.
 */
#if IPCOM_USE_SOCK == IPCOM_SOCK_IPNET \
 || IPCOM_USE_SOCK == IPCOM_SOCK_IPLITE \
 || IPCOM_USE_SOCK == IPCOM_SOCK_IPCOM
#define IPCOM_SOCK
#endif

#if IPCOM_USE_SOCK != IPCOM_SOCK_NONE && \
    !defined(IPCOM_USE_INET) && !defined(IPCOM_USE_INET6)
#error must_define_at_least_one_of_IPCOM_USE_INET_and_IPCOM_USE_INET6
#endif


#ifdef IPCOM_USE_HW_CHECKSUM
#define IPCOM_USE_HW_CHECKSUM_RX
#endif /* IPCOM_USE_HW_CHECKSUM */



#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
