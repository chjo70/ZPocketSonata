/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
23feb15,rbc  US54437 - Add additional IA CPUs
10jul14,rjq  Move vrrp. (US36942)
05may14,hax  Fix V7NET-6 remove mip
22arp14,h_x  Remove macsec US35690
21arp14,h_x  remove mip US35691
08apr14,jsh  Correct CPU reference
*/

#ifndef IPCOM_PAUTOCONF_H
#define IPCOM_PAUTOCONF_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 * Create translation from VSB defines in autoconf.h. This is required to
 * make the defines available in a VIP.
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */
#ifdef IP_PORT_VXWORKS
#undef IP_PORT_VXWORKS
#endif
#define IP_PORT_VXWORKS 70

#ifdef WRS_IPNET
#undef WRS_IPNET
#endif
#define WRS_IPNET

/*
 * When building an OPT=-basic system, the VSB defines don't match the
 * included product makefiles (some makefiles are not included). This
 * means that we cannot enable the product defines below since the
 * corresponding include paths may be missing when compiling.
 */
#if defined(_WRS_KERNEL) && !defined(IPBASIC)

#if (defined (_WRS_CONFIG_COMPONENT_IP8021X)  || defined( _WRS_CONFIG_COMPONENT_USR_IP8021X)) && !defined(IP8021X)
#define IP8021X
#endif

#if (defined (_WRS_CONFIG_COMPONENT_IPAPPL) || defined( _WRS_CONFIG_COMPONENT_USR_IPAPPL)) && !defined(IPAPPL)
#define IPAPPL
#endif

#if defined (_WRS_CONFIG_IPFTP_USE_TLS) && !defined(IPFTP_TLS)
#define IPFTP_TLS
#endif

#if ( defined(_WRS_CONFIG_COMPONENT_IPCRYPTO) || defined(_WRS_CONFIG_COMPONENT_USR_IPCRYPTO)) && !defined(IPCRYPTO)
#define IPCRYPTO
# ifndef _WRS_CONFIG_COMPONENT_IPCRYPTO_USE_STDIO
# define IPCRYPTO_NO_STDIO
# endif
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDHCPC6) || defined(_WRS_CONFIG_COMPONENT_USR_IPDHCPC6)) && !defined(IPDHCPC6)
#define IPDHCPC6
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDHCPR) || defined(_WRS_CONFIG_COMPONENT_USR_IPDHCPR)) && !defined(IPDHCPR)
#define IPDHCPR
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDHCPS) ||defined( _WRS_CONFIG_COMPONENT_USR_IPDHCPS)) && !defined(IPDHCPS)
#define IPDHCPS
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDHCPS6) || defined(_WRS_CONFIG_COMPONENT_USR_IPDHCPS6)) && !defined(IPDHCPS6)
#define IPDHCPS6
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDIAMETERC) || defined(_WRS_CONFIG_COMPONENT_USR_IPDIAMETERC)) && !defined(IPDIAMETERC)
#define IPDIAMETERC
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDIAMETERP) ||defined( _WRS_CONFIG_COMPONENT_USR_IPDIAMETERP)) && !defined(IPDIAMETERP)
#define IPDIAMETERP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDIAMETERC) || defined(_WRS_CONFIG_COMPONENT_USR_IPDIAMETERC)) && !defined(IPDIAMETER)
#define IPDIAMETER
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPDIAMETERP) ||defined( _WRS_CONFIG_COMPONENT_USR_IPDIAMETERP)) && !defined(IPDIAMETER)
#define IPDIAMETER
#endif


#if (defined(_WRS_CONFIG_COMPONENT_IPEAP) ||defined(_WRS_CONFIG_COMPONENT_USR_IPEAP)) && !defined(IPEAP)
#define IPEAP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPFIREWALL) || defined(_WRS_CONFIG_COMPONENT_USR_IPFIREWALL)) && !defined(IPFIREWALL)
#define IPFIREWALL
#endif

#if( defined(_WRS_CONFIG_COMPONENT_IPHWCRYPTO) ||defined(_WRS_CONFIG_COMPONENT_USR_IPHWCRYPTO)) && !defined(IPHWCRYPTO)
#define IPHWCRYPTO
#endif

#if( defined(_WRS_CONFIG_COMPONENT_IPIKE) || defined(_WRS_CONFIG_COMPONENT_USR_IPIKE)) && !defined(IPIKE)
#define IPIKE
#endif

#if( defined(_WRS_CONFIG_COMPONENT_IPIPSEC) || defined(_WRS_CONFIG_COMPONENT_USR_IPIPSEC))
#ifndef IPIPSEC
#define IPIPSEC
#endif
#ifndef IPIPSEC2
#define IPIPSEC2
#endif
#endif

#if (defined (_WRS_CONFIG_COMPONENT_IPL2TP) ||defined( _WRS_CONFIG_COMPONENT_USR_IPL2TP))&& !defined(IPL2TP)
#define IPL2TP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_WLAN) ||defined(_WRS_CONFIG_COMPONENT_USR_WLAN) )&& !defined(IPWLAN)
#define IPWLAN
#endif

#if (defined (_WRS_CONFIG_COMPONENT_IPLITE) ||defined (_WRS_CONFIG_COMPONENT_USR_IPLITE)) && !defined(IPLITE)
#define IPLITE
#endif

#if (defined (_WRS_CONFIG_COMPONENT_IPMCP) || defined(_WRS_CONFIG_COMPONENT_USR_IPMCP)) && !defined(IPMCP)
#define IPMCP
#endif

#if( defined(_WRS_CONFIG_COMPONENT_IPNET) ||defined (_WRS_CONFIG_COMPONENT_USR_IPNET)) && !defined(IPNET)
#define IPNET
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPPPP) ||defined( _WRS_CONFIG_COMPONENT_USR_IPPPP)) && !defined(IPPPP)
#define IPPPP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPRADIUS) ||defined( _WRS_CONFIG_COMPONENT_USR_IPRADIUS)) && !defined(IPRADIUS)
#define IPRADIUS
#endif


#if (defined (_WRS_CONFIG_COMPONENT_IPRIP) || defined(_WRS_CONFIG_COMPONENT_USR_IPRIP)) && !defined(IPRIP)
#define IPRIP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPRIPNG) ||defined (_WRS_CONFIG_COMPONENT_USR_IPRIPNG)) && !defined(IPRIPNG)
#define IPRIPNG
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPROHC) ||defined( _WRS_CONFIG_COMPONENT_USR_IPROHC)) && !defined(IPROHC)
#define IPROHC
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPSCTP) ||defined (_WRS_CONFIG_COMPONENT_USR_IPSCTP)) && !defined(IPSCTP)
#define IPSCTP
#endif

#if (defined (_WRS_CONFIG_COMPONENT_IPSNTP) ||defined (_WRS_CONFIG_COMPONENT_USR_IPSNTP)) && !defined(IPSNTP)
#define IPSNTP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPNTP) || defined(_WRS_CONFIG_COMPONENT_USR_IPNTP)) && !defined(IPNTP)
#define IPNTP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPSSH) ||defined (_WRS_CONFIG_COMPONENT_USR_IPSSH)) && !defined(IPSSH)
#define IPSSH
#endif

#if (defined(_WRS_CONFIG_OPENSSL) && !defined(IPSSL))
#define IPSSL
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPTCP) ||defined (_WRS_CONFIG_COMPONENT_USR_IPTCP)) && !defined(IPTCP)
#define IPTCP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPWPS) ||defined (_WRS_CONFIG_COMPONENT_USR_IPWPS)) && !defined(IPWPS)
#define IPWPS
#endif

#if (defined(_WRS_CONFIG_COMPONENT_IPXINC) ||defined( _WRS_CONFIG_COMPONENT_USR_IPXINC)) && !defined(IPXINC)
#define IPXINC
#endif

#if (defined(_WRS_CONFIG_COMPONENT_SECURITY) || defined(_WRS_CONFIG_COMPONENT_USR_SECURITY)) && !defined(SECURITY)
#define SECURITY
#endif

#if (defined(_WRS_CONFIG_COMPONENT_VXCOMPAT) || defined(_WRS_CONFIG_COMPONENT_USR_VXCOMPAT)) && !defined(VXCOMPAT)
#define VXCOMPAT
#endif

#if (defined(_WRS_CONFIG_COMPONENT_VXCOREIP) ||defined (_WRS_CONFIG_COMPONENT_USR_VXCOREIP)) && !defined(VXCOREIP)
#define VXCOREIP
#endif

#if (defined(_WRS_CONFIG_COMPONENT_VXMUX) && !defined(VXMUX))
#define VXMUX
#endif

#if defined(_WRS_CONFIG_COMPONENT_IPBRIDGE) && !defined(IPBRIDGE)
#define IPBRIDGE
#endif

#if defined(_WRS_CONFIG_IPNET_DNSC) && !defined(IPDNSC)
#define IPDNSC
#endif

#if defined(_WRS_CONFIG_IPNET_FTP) && !defined(IPFTPC)
#define IPFTPC
#endif

#if defined(_WRS_CONFIG_IPNET_TFTP) && !defined(IPTFTPC)
#define IPTFTPC
#endif

#if defined(_WRS_CONFIG_IPNET_DHCPC) && !defined(IPDHCPC)
#define IPDHCPC
#endif

#if  (_WRS_CONFIG_IPNET_VRRP) && !defined(IPVRRP)
#define IPVRRP
#endif

#if defined(_WRS_CONFIG_SNMP) && !defined(WRSNMP)
#define WRSNMP
#endif

#if defined(_WRS_CONFIG_OPENSSL_FIPS) && !defined(OPENSSL_FIPS)
#define OPENSSL_FIPS
#endif

#endif /* _WRS_KERNEL && !IPBASIC */

#if (defined(_WRS_CONFIG_FEATURE_IPNET_INET6) || defined(_WRS_CONFIG_FEATURE_IPNET_USR_INET6) || \
     defined(_WRS_CONFIG_FEATURE_IPNET_INET6_ONLY) || defined(_WRS_CONFIG_FEATURE_IPNET_USR_INET6_ONLY) ||\
     defined(_WRS_CONFIG_FEATURE_IPLITE_INET6)) && !defined(IPCOM_USE_INET6)
#define IPCOM_USE_INET6
#ifndef INET6
#define INET6
#endif
#endif

#if defined(_WRS_CONFIG_FEATURE_IPNET_INET6_ONLY) && !defined(IPCOM_EXCLUDE_INET)
#define IPCOM_EXCLUDE_INET
#endif

#ifndef _WRS_CONFIG_FEATURE_IPNET_INET6_ONLY
#ifndef INET
#define INET
#endif
#endif

#if !defined(_WRS_CONFIG_BUILD_MODE_speed) && !defined(_WRS_CONFIG_BUILD_MODE_speed_d) && !defined(IP_DEBUG) && !defined(IPLITE)
#define IP_DEBUG
#endif

#if !defined(_WRS_CONFIG_BUILD_MODE_speed) && !defined(_WRS_CONFIG_BUILD_MODE_speed_d) && !defined(IP_ASSERT) && !defined(IPLITE)
#define IP_ASSERT
#endif


/* This definition is deprecated, please use IPCOM_VXWORKS_USE_MSP */
#if _WRS_CONFIG_MSP_KERNEL && !defined(IPNET_MSP_DISTRIBUTION)
#define IPNET_MSP_DISTRIBUTION
#endif

#if _WRS_CONFIG_MSP_KERNEL && !defined(IPCOM_VXWORKS_USE_MSP)
#define IPCOM_VXWORKS_USE_MSP
#endif

#if defined(_VSB_CONFIG_FILE) && !defined(IP_WB_BUILD)
#define IP_WB_BUILD
#endif

/* Define LITTLE/BIG ENDIAN */
#ifdef IP_LITTLE_ENDIAN
#undef IP_LITTLE_ENDIAN
#endif

#ifdef IP_BIG_ENDIAN
#undef IP_BIG_ENDIAN
#endif

#ifdef _WRS_CONFIG_ENDIAN_little
#define IP_LITTLE_ENDIAN
#elif defined(_WRS_CONFIG_ENDIAN_big)
#define IP_BIG_ENDIAN
#elif defined(_WRS_CONFIG_ARCH_i86)
#define IP_LITTLE_ENDIAN
#elif (CPU == _VX_SIMLINUX) || (CPU == _VX_SIMNT)
#define IP_LITTLE_ENDIAN
#elif (CPU == _VX_PPCE500V2) || (CPU == _VX_PPCE500MC)
#define IP_BIG_ENDIAN
#else
#error UNKNOWN_CPU_YOU_MUST_DEFINE_IP_LITTLE_ENDIAN_OR_IP_BIG_ENDIAN_USING_EXTRA_DEFINE
#endif

#endif /* IPCOM_PAUTOCONF_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
