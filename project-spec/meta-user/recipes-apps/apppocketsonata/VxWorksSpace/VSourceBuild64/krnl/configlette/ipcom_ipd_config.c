/*
 * Copyright (c) 2014-2015,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* modification history
-------------------------
19may16,ply  Port TSR defect fix forward from vxworks6.9 into vx7. (F6988)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
20feb15,ed  Fixed issue which prevented TFTP server from starting
11dec14,ed  added ability to delay starting FTPS, TFTPS, and TELNETS
            based on CDF settings (F2848)
25aug14,ljl Move IPCRYPTO,IPSSL,IPHWCRYPTO and IPFREESCALE to security layer, US44321
05may14,hax fix V7NET-6 to remove mip code
24apr14,h_x Remove secure NDP and CGA US35689
22apr14,h_x Remove macsec US35690
*/

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

#include "ipcom_config.h"
#ifdef IPNET
#include <ipnet_config.h>
#endif

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */


#include "ipcom_type.h"
#include "ipcom_cstyle.h"
#include "ipcom_err.h"
#include "ipcom_ipd.h"
#include "ipcom_syslog.h"


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if !defined(IP_PORT_VXWORKS) && defined(IPBRIDGE)
#define INCLUDE_BRIDGE
#endif
 
#ifdef IP_PORT_VXWORKS

#ifdef IPTELNETS
#undef IPTELNETS
#endif
#ifdef INCLUDE_IPTELNETS
#define IPTELNETS
#endif

#ifdef IPLITE
#undef IPLITE
#endif
#ifdef INCLUDE_IPLITE
#define IPLITE
#endif

#ifdef IPNET
#undef IPNET
#endif
#ifdef INCLUDE_IPNET
#define IPNET
#endif

#ifdef IPVRRP
#undef IPVRRP
#endif
#ifdef INCLUDE_IPVRRPD
#define IPVRRP
#endif

#ifdef IPTCP
#undef IPTCP
#endif
#ifdef INCLUDE_IPTCP
#define IPTCP
#endif

#ifdef IPPPP
#undef IPPPP
#endif
#ifdef INCLUDE_IPPPP
#define IPPPP
#endif

#ifdef IPL2TP
#undef IPL2TP
#endif
#ifdef INCLUDE_IPL2TP
#define IPL2TP
#endif


#ifdef IPTFTPS
#undef IPTFTPS
#endif
#ifdef INCLUDE_IPTFTPS
#define IPTFTPS
#endif

#ifdef IPFTPS
#undef IPFTPS
#endif
#ifdef INCLUDE_IPFTPS
#define IPFTPS
#endif

#ifdef IPRADIUS
#undef IPRADIUS
#endif
#ifdef INCLUDE_IPRADIUS
#define IPRADIUS
#endif



#ifdef IPIPSEC2
#undef IPIPSEC2
#endif
#ifdef INCLUDE_IP_SECURITY
#define IPIPSEC2
#endif

#ifdef IPIKE
#undef IPIKE
#endif
#ifdef INCLUDE_INTERNET_KEY_EXCHANGE
#define IPIKE
#endif

#ifdef IPSSH
#undef IPSSH
#endif
#ifdef INCLUDE_SSH
#define IPSSH
#endif

#ifdef IPFIREWALL
#undef IPFIREWALL
#endif
#ifdef INCLUDE_IPFIREWALL
#define IPFIREWALL
#endif

#ifdef IPDHCPS
#undef IPDHCPS
#endif
#ifdef INCLUDE_IPDHCPS
#define IPDHCPS
#endif

#ifdef IPDHCPC6
#undef IPDHCPC6
#endif
#ifdef INCLUDE_IPDHCPC6
#define IPDHCPC6
#endif

#ifdef IPDHCPS6
#undef IPDHCPS6
#endif
#ifdef INCLUDE_IPDHCPS6
#define IPDHCPS6
#endif

#ifdef IPDHCPR
#undef IPDHCPR
#endif
#ifdef INCLUDE_IPDHCPR
#define IPDHCPR
#endif

#ifdef IPRIP
#undef IPRIP
#endif
#ifdef INCLUDE_IPRIP
#define IPRIP
#endif

#ifdef IPRIPNG
#undef IPRIPNG
#endif
#ifdef INCLUDE_RIPNG
#define IPRIPNG
#endif

#ifdef IPSNTP
#undef IPSNTP
#endif
#if defined(INCLUDE_IPSNTPS) || defined(INCLUDE_IPSNTPC)
#define IPSNTP
#endif

#ifdef IPDHCPC
#undef IPDHCPC
#endif
#ifdef INCLUDE_IPDHCPC
#define IPDHCPC
#endif

#ifdef IPDNSC
#undef IPDNSC
#endif
#ifdef INCLUDE_IPDNSC
#define IPDNSC
#endif

#ifdef IPTFTPC
#undef IPTFTPC
#endif
#ifdef INCLUDE_IPTFTPC
#define IPTFTPC
#endif

#ifdef IPFTPC
#undef IPFTPC
#endif
#ifdef INCLUDE_IPFTPC
#define IPFTPC
#endif

#ifdef IPMCP
#undef IPMCP
#endif
#ifdef INCLUDE_IPMCP
#define IPMCP
#endif

#ifdef IP8021X
#undef IP8021X
#endif
#ifdef INCLUDE_IP8021X_SUPPLICANT
#define IP8021X
#endif

#ifdef IPEAP
#undef IPEAP
#endif
#ifdef INCLUDE_IPEAP
#define IPEAP
#endif

#ifdef IPWPS
#undef IPWPS
#endif
#ifdef INCLUDE_IPWPS
#define IPWPS
#endif


#ifdef IPROHC
#undef IPROHC
#endif
#ifdef INCLUDE_IPROHC
#define IPROHC
#endif

#ifdef IPSCTP
#undef IPSCTP
#endif
#ifdef INCLUDE_IPSCTP
#define IPSCTP
#endif

#ifdef IPNTP
#undef IPNTP
#endif
#ifdef INCLUDE_IPNTP
#define IPNTP
#endif

#endif /* PRJ_BUILD */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

#ifdef IPTELNETS
IP_PUBLIC Ip_err iptelnets_start(void);
IP_PUBLIC Ip_err iptelnets_create(void);
IP_PUBLIC const char *iptelnets_version(void);
IP_PUBLIC Ip_err iptelnets_configure(void);
#endif

#ifdef IPLITE
IP_PUBLIC Ip_err iplite_create(void);
IP_PUBLIC Ip_err iplite_configure(void);
IP_PUBLIC Ip_err iplite_start(void);
IP_PUBLIC const char *iplite_version(void);
#endif

#ifdef IPNET
#include <ipnet_config.h>
IP_PUBLIC Ip_err ipnet_create(void);
IP_PUBLIC Ip_err ipnet_configure(void);
IP_PUBLIC Ip_err ipnet_start(void);
IP_PUBLIC const char *ipnet_version(void);

#ifdef IPVRRP
IP_PUBLIC Ip_err ipnet_vrrpd_create(void);
IP_PUBLIC Ip_err ipnet_vrrpd_configure(void);
IP_PUBLIC Ip_err ipnet_vrrpd_start(void);
IP_PUBLIC const char *ipnet_vrrpd_version(void);
#endif

#if defined(INCLUDE_IPRADVD) || !defined(PRJ_BUILD) && defined(IPCOM_USE_INET6)
IP_PUBLIC Ip_err ipnet_radvd_create(void);
IP_PUBLIC Ip_err ipnet_radvd_configure(void);
IP_PUBLIC Ip_err ipnet_radvd_start(void);
IP_PUBLIC const char *ipnet_radvd_version(void);
#endif /* IPCOM_USE_INET6 */
#endif /* IPNET */

#ifdef IPTCP
IP_PUBLIC Ip_err iptcp_create(void);
IP_PUBLIC Ip_err iptcp_configure(void);
IP_PUBLIC Ip_err iptcp_start(void);
IP_PUBLIC const char *iptcp_version(void);
#endif

#ifdef IPPPP
IP_PUBLIC Ip_err ipppp_create(void);
IP_PUBLIC Ip_err ipppp_configure(void);
IP_PUBLIC Ip_err ipppp_start(void);
IP_PUBLIC const char *ipppp_version(void);
#endif

#ifdef IPPPPOE
IP_PUBLIC Ip_err ippppoe_create(void);
IP_PUBLIC Ip_err ippppoe_configure(void);
IP_PUBLIC Ip_err ippppoe_start(void);
IP_PUBLIC const char *ippppoe_version(void);
#endif



#ifdef IPMIP6CN
IP_PUBLIC Ip_err ipmip6cn_start(void);
IP_PUBLIC const char *ipmip6cn_version(void);
#endif

#ifdef IPMLDS
IP_PUBLIC Ip_err ipmlds_create(void);
IP_PUBLIC Ip_err ipmlds_configure(void);
IP_PUBLIC Ip_err ipmlds_start(void);
IP_PUBLIC const char *ipmlds_version(void);
#endif

#ifdef IPTFTPS
IP_PUBLIC Ip_err iptftps_create(void);
IP_PUBLIC Ip_err iptftps_configure(void);
IP_PUBLIC Ip_err iptftps_start(void);
IP_PUBLIC const char *iptftps_version(void);
#endif

#ifdef IPFTPS
IP_PUBLIC Ip_err ipftps_create(void);
IP_PUBLIC Ip_err ipftps_configure(void);
IP_PUBLIC Ip_err ipftps_start(void);
IP_PUBLIC const char *ipftps_version(void);
#endif

#ifdef IPRADIUS
IP_PUBLIC Ip_err ipradius_create(void);
IP_PUBLIC Ip_err ipradius_configure(void);
IP_PUBLIC Ip_err ipradius_start(void);
IP_PUBLIC const char *ipradius_version(void);
#endif

#ifdef IPL2TP
IP_PUBLIC Ip_err ipl2tp_create(void);
IP_PUBLIC Ip_err ipl2tp_configure(void);
IP_PUBLIC Ip_err ipl2tp_start(void);
IP_PUBLIC const char *ipl2tp_version(void);
#endif

#ifdef IPNAT
IP_PUBLIC Ip_err ipnat_create(void);
IP_PUBLIC Ip_err ipnat_configure(void);
IP_PUBLIC Ip_err ipnat_start(void);
IP_PUBLIC const char *ipnat_version(void);
#endif

#if defined(IPIPSEC) || defined(IPIPSEC2)
IP_PUBLIC Ip_err ipipsec_create(void);
IP_PUBLIC Ip_err ipipsec_configure(void);
IP_PUBLIC Ip_err ipipsec_start(void);
IP_PUBLIC const char *ipipsec_version(void);
#endif

#ifdef IPCCI
IP_PUBLIC Ip_err ipcci_create(void);
IP_PUBLIC Ip_err ipcci_configure(void);
IP_PUBLIC Ip_err ipcci_start(void);
IP_PUBLIC const char *ipcci_version(void);
#endif

#ifdef IPLDAPC
IP_PUBLIC Ip_err ipldapc_create(void);
IP_PUBLIC Ip_err ipldapc_configure(void);
IP_PUBLIC Ip_err ipldapc_start(void);
IP_PUBLIC const char *ipldapc_version(void);
#endif

#ifdef IPIKE
IP_PUBLIC Ip_err ipike_create(void);
IP_PUBLIC Ip_err ipike_configure(void);
IP_PUBLIC Ip_err ipike_start(void);
IP_PUBLIC const char *ipike_version(void);
#endif

#ifdef IPSSLPROXY
IP_PUBLIC Ip_err ipsslproxy_create(void);
IP_PUBLIC Ip_err ipsslproxy_configure(void);
IP_PUBLIC Ip_err ipsslproxy_start(void);
IP_PUBLIC const char *ipsslproxy_version(void);
#endif

#ifdef IPSSH
IP_PUBLIC Ip_err ipssh_create(void);
IP_PUBLIC Ip_err ipssh_configure(void);
IP_PUBLIC Ip_err ipssh_start(void);
IP_PUBLIC const char *ipssh_version(void);
#endif

#ifdef IPFIREWALL
IP_PUBLIC Ip_err ipfirewall_create(void);
IP_PUBLIC Ip_err ipfirewall_configure(void);
IP_PUBLIC Ip_err ipfirewall_start(void);
IP_PUBLIC const char *ipfirewall_version(void);
#endif

#ifdef IPDHCPS
IP_PUBLIC Ip_err ipdhcps_create(void);
IP_PUBLIC Ip_err ipdhcps_configure(void);
IP_PUBLIC Ip_err ipdhcps_start(void);
IP_PUBLIC const char *ipdhcps_version(void);
#endif

#ifdef IPDHCPC6
IP_PUBLIC Ip_err ipdhcpc6_create(void);
IP_PUBLIC Ip_err ipdhcpc6_configure(void);
IP_PUBLIC Ip_err ipdhcpc6_start(void);
IP_PUBLIC const char *ipdhcpc6_version(void);
#endif

#ifdef IPDHCPS6
IP_PUBLIC Ip_err ipdhcps6_create(void);
IP_PUBLIC Ip_err ipdhcps6_configure(void);
IP_PUBLIC Ip_err ipdhcps6_start(void);
IP_PUBLIC const char *ipdhcps6_version(void);
#endif

#ifdef IPDHCPR
IP_PUBLIC Ip_err ipdhcpr_create(void);
IP_PUBLIC Ip_err ipdhcpr_configure(void);
IP_PUBLIC Ip_err ipdhcpr_start(void);
IP_PUBLIC const char *ipdhcpr_version(void);
#endif

#ifdef IPWEBS
IP_PUBLIC Ip_err ipwebs_create(void);
IP_PUBLIC Ip_err ipwebs_configure(void);
IP_PUBLIC Ip_err ipwebs_start(void);
IP_PUBLIC const char *ipwebs_version(void);
#endif

#ifdef IPRIP
IP_PUBLIC Ip_err iprip_create(void);
IP_PUBLIC Ip_err iprip_configure(void);
IP_PUBLIC Ip_err iprip_start(void);
IP_PUBLIC const char *iprip_version(void);
#endif

#ifdef IPRIPNG
IP_EXTERN Ip_err ipripng_create(void);
IP_EXTERN Ip_err ipripng_configure(void);
IP_EXTERN Ip_err ipripng_start(void);
IP_EXTERN const char *ipripng_version(void);
#endif

#ifdef IPSNTP
IP_PUBLIC Ip_err ipsntp_create(void);
IP_PUBLIC Ip_err ipsntp_configure(void);
IP_PUBLIC Ip_err ipsntp_start(void);
IP_PUBLIC const char *ipsntp_version(void);
#endif

#ifdef IPSNMP
IP_PUBLIC Ip_err ipsnmp_create(void);
IP_PUBLIC Ip_err ipsnmp_configure(void);
IP_PUBLIC Ip_err ipsnmp_start(void);
IP_PUBLIC const char *ipsnmp_version(void);
#endif

#ifdef IPEMANATE
IP_PUBLIC Ip_err ipemanate_create(void);
IP_PUBLIC Ip_err ipemanate_configure(void);
IP_PUBLIC Ip_err ipemanate_start(void);
IP_PUBLIC const char *ipemanate_version(void);
#endif


#ifdef ZEBOS
IP_PUBLIC Ip_err ipzebos_create(void);
IP_PUBLIC Ip_err ipzebos_configure(void);
IP_PUBLIC Ip_err ipzebos_start(void);
IP_PUBLIC const char *ipzebos_version(void);
#endif

#ifdef IPDC
IP_PUBLIC Ip_err ipdc_create(void);
IP_PUBLIC Ip_err ipdc_configure(void);
IP_PUBLIC Ip_err ipdc_start(void);
IP_PUBLIC const char *ipdc_version(void);
#endif

#ifdef IPNGC
IP_PUBLIC Ip_err ipngc_create(void);
IP_PUBLIC Ip_err ipngc_configure(void);
IP_PUBLIC Ip_err ipngc_start(void);
IP_PUBLIC const char *ipngc_version(void);
#endif

#ifdef IPQUAGGA
IP_PUBLIC Ip_err ipquagga_create(void);
IP_PUBLIC Ip_err ipquagga_configure(void);
IP_PUBLIC Ip_err ipquagga_start(void);
IP_PUBLIC const char *ipquagga_version(void);
#endif

#if defined(IPDHCPC) && defined(IPCOM_SOCK)
IP_PUBLIC Ip_err ipdhcpc_create(void);
IP_PUBLIC Ip_err ipdhcpc_configure(void);
IP_PUBLIC Ip_err ipdhcpc_start(void);
IP_PUBLIC const char *ipdhcpc_version(void);
#endif

#ifdef IPDNSC
IP_PUBLIC Ip_err ipdnsc_create(void);
IP_PUBLIC Ip_err ipdnsc_configure(void);
IP_PUBLIC Ip_err ipdnsc_start(void);
IP_PUBLIC const char *ipdnsc_version(void);
#endif

#ifdef IPTFTPC
IP_PUBLIC Ip_err iptftpc_create(void);
IP_PUBLIC Ip_err iptftpc_configure(void);
IP_PUBLIC Ip_err iptftpc_start(void);
IP_PUBLIC const char *iptftpc_version(void);
#endif

#ifdef IPFTPC
IP_PUBLIC Ip_err ipftpc_create(void);
IP_PUBLIC Ip_err ipftpc_configure(void);
IP_PUBLIC Ip_err ipftpc_start(void);
IP_PUBLIC const char *ipftpc_version(void);
#endif

#ifdef IPMCP
IP_PUBLIC Ip_err ipmcp_create(void);
IP_PUBLIC Ip_err ipmcp_configure(void);
IP_PUBLIC Ip_err ipmcp_start(void);
IP_PUBLIC const char *ipmcp_version(void);
#endif

#ifdef IPPRISM
IP_PUBLIC Ip_err ipprism_create(void);
IP_PUBLIC Ip_err ipprism_configure(void);
IP_PUBLIC Ip_err ipprism_start(void);
IP_PUBLIC const char *ipprism_version(void);
#endif

#ifdef IP8021X
IP_PUBLIC Ip_err ip8021x_create(void);
IP_PUBLIC Ip_err ip8021x_configure(void);
IP_PUBLIC Ip_err ip8021x_start(void);
IP_PUBLIC const char *ip8021x_version(void);
#endif

#ifdef IPEAP
IP_PUBLIC Ip_err ipeap_create(void);
IP_PUBLIC Ip_err ipeap_configure(void);
IP_PUBLIC Ip_err ipeap_start(void);
IP_PUBLIC const char *ipeap_version(void);
#endif

#ifdef IPWPS
IP_PUBLIC Ip_err ipwps_create(void);
IP_PUBLIC Ip_err ipwps_configure(void);
IP_PUBLIC Ip_err ipwps_start(void);
IP_PUBLIC const char *ipwps_version(void);
#endif

#ifdef IPSAFENET
IP_PUBLIC Ip_err ipsafenet_create(void);
IP_PUBLIC Ip_err ipsafenet_configure(void);
IP_PUBLIC Ip_err ipsafenet_start(void);
IP_PUBLIC const char *ipsafenet_version(void);
#endif


#ifdef IPNETPERF
IP_PUBLIC Ip_err ipnetperf_create(void);
IP_PUBLIC Ip_err ipnetperf_configure(void);
IP_PUBLIC Ip_err ipnetperf_start(void);
IP_PUBLIC const char *ipnetperf_version(void);
#endif

#ifdef IPNETSNMP
IP_PUBLIC Ip_err ipnetsnmp_create(void);
IP_PUBLIC Ip_err ipnetsnmp_configure(void);
IP_PUBLIC Ip_err ipnetsnmp_start(void);
IP_PUBLIC const char *ipnetsnmp_version(void);
#endif

#ifdef IPMARVELL
IP_PUBLIC Ip_err ipmarvell_create(void);
IP_PUBLIC Ip_err ipmarvell_configure(void);
IP_PUBLIC Ip_err ipmarvell_start(void);
IP_PUBLIC const char *ipmarvell_version(void);
#endif

#ifdef IPANVL
IP_PUBLIC Ip_err ipanvl_create(void);
IP_PUBLIC Ip_err ipanvl_configure(void);
IP_PUBLIC Ip_err ipanvl_start(void);
IP_PUBLIC const char *ipanvl_version(void);
#endif

#ifdef IP_PORT_OSE5
IP_PUBLIC Ip_err ipcom_ipd_isinstalled_ose5(const char *name);
IP_PUBLIC Ip_err ipcom_ipd_start_ose5(const char *name);
#endif


#ifdef INCLUDE_IPDIAMETERC
IP_EXTERN Ip_err ipdiameterc_create(void);
IP_EXTERN Ip_err ipdiameterc_configure(void);
IP_EXTERN Ip_err ipdiameterc_start(void);
IP_EXTERN const char *ipdiameter_version(void);
#endif

#ifdef INCLUDE_IPDIAMETERP
IP_EXTERN Ip_err ipdiameterp_create(void);
IP_EXTERN Ip_err ipdiameterp_configure(void);
IP_EXTERN Ip_err ipdiameterp_start(void);
IP_EXTERN const char *ipdiameter_version(void);
#endif

#ifdef IPSCTP
IP_PUBLIC Ip_err ipsctp_create(void);
IP_PUBLIC Ip_err ipsctp_configure(void);
IP_PUBLIC Ip_err ipsctp_start(void);
IP_PUBLIC const char *ipsctp_version(void);
#endif

#ifdef IPIFPROXY
IP_PUBLIC Ip_err ipifproxy_create(void);
IP_PUBLIC Ip_err ipifproxy_configure(void);
IP_PUBLIC Ip_err ipifproxy_start(void);
IP_PUBLIC const char *ipifproxy_version(void);
#endif

#ifdef INCLUDE_IPWLAN_BROADCOM
IP_EXTERN Ip_err ipwlan_broadcom_create(void);
IP_EXTERN Ip_err ipwlan_broadcom_configure(void);
IP_EXTERN Ip_err ipwlan_broadcom_start(void);
IP_EXTERN const char *ipwlan_broadcom_version(void);
#endif

#ifdef INCLUDE_IPWLAN_ATHEROS
IP_EXTERN Ip_err ipwlan_atheros_create(void);
IP_EXTERN Ip_err ipwlan_atheros_configure(void);
IP_EXTERN Ip_err ipwlan_atheros_start(void);
IP_EXTERN const char *ipwlan_atheros_version(void);
#endif

#ifdef IPROHC
IP_EXTERN Ip_err iprohc_create(void);
IP_EXTERN Ip_err iprohc_configure(void);
IP_EXTERN Ip_err iprohc_start(void);
IP_EXTERN const char *iprohc_version(void);
#endif

#ifdef REMOVE_THIS_IFDEF_WHEN_SUPPORTING_IPBRIDGE
#ifdef INCLUDE_BRIDGE
IP_PUBLIC Ip_err ipbridge_create(void);
IP_PUBLIC Ip_err ipbridge_configure(void);
IP_PUBLIC Ip_err ipbridge_start(void);
IP_PUBLIC const char *ipbridge_version(void);
#endif
#endif

#ifdef IPNTP
IP_PUBLIC Ip_err ipntp_create(void);
IP_PUBLIC Ip_err ipntp_configure(void);
IP_PUBLIC Ip_err ipntp_start(void);
IP_PUBLIC const char *ipntp_version(void);
#endif

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

IP_GLOBAL const Ipcom_ipd_product ipcom_ipd_products[] =
{
#ifdef IPLITE
    { "iplite", iplite_create, iplite_configure, iplite_start, iplite_version, IPCOM_IPD_ID_IPLITE, IPCOM_LOG_IPLITE, 0},
#elif defined(IP_PORT_OSE5)
    { "iplite", 0, 0, 0, 0, IPCOM_IPD_ID_IPLITE, IPCOM_LOG_IPLITE, 0},
#endif

#ifdef IPNET
    { "ipnet", ipnet_create, ipnet_configure, ipnet_start, ipnet_version, IPCOM_IPD_ID_IPNET, IPCOM_LOG_IPNET, 0},
#ifdef IPVRRP
    { "ipnet_vrrpd", ipnet_vrrpd_create, ipnet_vrrpd_configure, ipnet_vrrpd_start, ipnet_vrrpd_version, IPCOM_IPD_ID_IPNET_VRRPD, IPCOM_LOG_NONE, IPCOM_IPD_FLAG_IPD_START | IPCOM_IPD_FLAG_HALTED},
#endif

#ifdef REMOVE_THIS_IFDEF_WHEN_SUPPORTING_IPBRIDGE
#ifdef INCLUDE_BRIDGE
	{ "ipbridged", ipbridge_create, ipbridge_configure, ipbridge_start, ipbridge_version, IPCOM_IPD_ID_IPBRIDGE, IPCOM_LOG_IPBRIDGE, IPCOM_IPD_FLAG_IPD_START},
#endif
#endif
	
#if defined(INCLUDE_IPRADVD) || !defined(PRJ_BUILD) && defined(IPCOM_USE_INET6)
    { "ipnet_radvd", ipnet_radvd_create, ipnet_radvd_configure, ipnet_radvd_start, ipnet_radvd_version, IPCOM_IPD_ID_IPNET_RADVD, IPCOM_LOG_NONE, IPCOM_IPD_FLAG_IPD_START | IPCOM_IPD_FLAG_HALTED},
#endif
#elif defined(IP_PORT_OSE5)  /* IPNET */
    { "ipnet", 0, 0, 0, 0, IPCOM_IPD_ID_IPNET, IPCOM_LOG_IPNET, 0},
#ifdef IPVRRP
    { "ipnet_vrrpd", 0, 0, 0, 0, IPCOM_IPD_ID_IPNET_VRRPD, IPCOM_LOG_NONE, IPCOM_IPD_FLAG_IPD_START | IPCOM_IPD_FLAG_HALTED},
#endif
#ifdef IPCOM_USE_INET6
    { "ipnet_radvd", IP_NULL, IP_NULL, IP_NULL, IP_NULL, 0, IPCOM_IPD_ID_IPNET_RADVD, IPCOM_LOG_NONE, IPCOM_IPD_FLAG_HALTED},
#endif
#endif /* IPNET */

#ifdef IPNET
#ifdef IPTCP
    { "iptcp", iptcp_create, iptcp_configure, iptcp_start, iptcp_version, IPCOM_IPD_ID_IPTCP, IPCOM_LOG_IPTCP, 0},
#elif defined(IP_PORT_OSE5)
    { "iptcp", 0, 0, 0, 0, IPCOM_IPD_ID_IPTCP, IPCOM_LOG_IPTCP, 0},
#endif
#endif

#ifdef IPSCTP
    { "ipsctp", ipsctp_create, ipsctp_configure, ipsctp_start, ipsctp_version, IPCOM_IPD_ID_IPSCTP, IPCOM_LOG_IPSCTP, 0},
#endif

#if defined(IPTELNETS)
#if IPCOM_TELNET_DELAYEDSTART
    { "iptelnets", iptelnets_create, iptelnets_configure, iptelnets_start, iptelnets_version, IPCOM_IPD_ID_IPTELNETS, IPCOM_LOG_IPCOM_TELNET, IPCOM_IPD_FLAG_HALTED | IPCOM_IPD_FLAG_IPD_START},
#else
    { "iptelnets", iptelnets_create, iptelnets_configure, iptelnets_start, iptelnets_version, IPCOM_IPD_ID_IPTELNETS, IPCOM_LOG_IPCOM_TELNET, IPCOM_IPD_FLAG_IPD_START},
#endif
#elif defined(IP_PORT_OSE5)
    { "iptelnets", IP_NULL, IP_NULL, IP_NULL, IP_NULL, IPCOM_IPD_ID_IPTELNETS, IPCOM_LOG_IPCOM_TELNET, IPCOM_IPD_FLAG_IPD_START},
#endif


#ifdef IPRADIUS
    { "ipradius", ipradius_create, ipradius_configure, ipradius_start, ipradius_version, IPCOM_IPD_ID_IPRADIUS, IPCOM_LOG_IPRADIUS, 0},
#elif defined(IP_PORT_OSE5)
    { "ipradius", 0, 0, 0, 0, IPCOM_IPD_ID_IPRADIUS, IPCOM_LOG_IPRADIUS, 0},
#endif

#ifdef IPPPP
    { "ipppp", ipppp_create, ipppp_configure, ipppp_start, ipppp_version, IPCOM_IPD_ID_IPPPP, IPCOM_LOG_IPPPP, 0},
#endif

#ifdef IPPPPOE
    { "ippppoe", ippppoe_create, ippppoe_configure, ippppoe_start, ippppoe_version, IPCOM_IPD_ID_IPPPPOE, IPCOM_LOG_IPPPPOE, 0},
#endif


#ifdef IPMIP6CN
    { "ipmip6cn", IP_NULL, IP_NULL, ipmip6cn_start, ipmip6cn_version, IPCOM_IPD_ID_IPMIP6CN, IPCOM_LOG_NONE, IPCOM_IPD_FLAG_IPD_START},
#endif





#ifdef IPMLDS
    { "ipmlds", ipmlds_create, ipmlds_configure, ipmlds_start, ipmlds_version, IPCOM_IPD_ID_IPMLDS, IPCOM_LOG_IPMLDS, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)
    { "ipmlds", 0, 0, 0, 0, IPCOM_IPD_ID_IPMLDS, IPCOM_LOG_IPMLDS, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPTFTPS
#if TFTPS_DELAYEDSTART
    { "iptftps", iptftps_create, iptftps_configure, iptftps_start, iptftps_version, IPCOM_IPD_ID_IPTFTPS, IPCOM_LOG_IPTFTP, IPCOM_IPD_FLAG_HALTED | IPCOM_IPD_FLAG_IPD_START},
#else
    { "iptftps", iptftps_create, iptftps_configure, iptftps_start, iptftps_version, IPCOM_IPD_ID_IPTFTPS, IPCOM_LOG_IPTFTP, IPCOM_IPD_FLAG_IPD_START},
#endif

#elif defined(IP_PORT_OSE5)
    { "iptftps", 0, 0, 0, 0, IPCOM_IPD_ID_IPTFTPS, IPCOM_LOG_IPTFTP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPFTPS

#if FTPS_DELAYEDSTART 
    { "ipftps", ipftps_create, ipftps_configure, ipftps_start, ipftps_version, IPCOM_IPD_ID_IPFTPS, IPCOM_LOG_IPFTP, IPCOM_IPD_FLAG_HALTED | IPCOM_IPD_FLAG_IPD_START},
#else
    { "ipftps", ipftps_create, ipftps_configure, ipftps_start, ipftps_version, IPCOM_IPD_ID_IPFTPS, IPCOM_LOG_IPFTP, IPCOM_IPD_FLAG_IPD_START},
#endif

#elif defined(IP_PORT_OSE5)
    { "ipftps", 0, 0, 0, 0, IPCOM_IPD_ID_IPFTPS, IPCOM_LOG_IPFTP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPL2TP
    { "ipl2tp", ipl2tp_create, ipl2tp_configure, ipl2tp_start, ipl2tp_version, IPCOM_IPD_ID_IPL2TP, IPCOM_LOG_IPL2TP, 0},
#elif defined(IP_PORT_OSE5)
    { "ipl2tp", 0, 0, 0, 0, IPCOM_IPD_ID_IPL2TP, IPCOM_LOG_IPL2TP, 0},
#endif

#ifdef IPNAT
    { "ipnat", ipnat_create, ipnat_configure, ipnat_start, ipnat_version, IPCOM_IPD_ID_IPNAT, IPCOM_LOG_IPNAT, 0},
#endif


#ifdef IPLDAPC
    { "ipldapc", ipldapc_create, ipldapc_configure, ipldapc_start, ipldapc_version, IPCOM_IPD_ID_IPLDAPC, IPCOM_LOG_IPLDAPC, 0},
#elif defined(IP_PORT_OSE5)
    { "ipldapc", 0, 0, 0, 0, IPCOM_IPD_ID_IPLDAPC, IPCOM_LOG_IPLDAPC, 0},
#endif

#ifdef IPSSH
    { "ipssh", ipssh_create, ipssh_configure, ipssh_start, ipssh_version, IPCOM_IPD_ID_IPSSH, IPCOM_LOG_IPSSH, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)
    { "ipssh", 0, 0, 0, 0, IPCOM_IPD_ID_IPSSH, IPCOM_LOG_IPSSH, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPFIREWALL
    { "ipfirewall", ipfirewall_create, ipfirewall_configure, ipfirewall_start, ipfirewall_version, IPCOM_IPD_ID_IPFIREWALL, IPCOM_LOG_IPFIREWALL, 0},
#elif defined(IP_PORT_OSE5)
    { "ipfirewall", 0, 0, 0, 0, IPCOM_IPD_ID_IPFIREWALL, IPCOM_LOG_IPFIREWALL, 0},
#endif

#ifdef IPDHCPS
    { "ipdhcps", ipdhcps_create, ipdhcps_configure, ipdhcps_start, ipdhcps_version, IPCOM_IPD_ID_IPDHCPS, IPCOM_LOG_IPDHCPS, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)
    { "ipdhcps", 0, 0, 0, 0, IPCOM_IPD_ID_IPDHCPS, IPCOM_LOG_IPDHCPS, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPDHCPC6
    { "ipdhcpc6", ipdhcpc6_create, ipdhcpc6_configure, ipdhcpc6_start, ipdhcpc6_version, IPCOM_IPD_ID_IPDHCPC6, IPCOM_LOG_IPDHCPC6, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)
    { "ipdhcpc6", 0, 0, 0, 0, IPCOM_IPD_ID_IPDHCPC6, IPCOM_LOG_IPDHCPC6, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPDHCPS6
    { "ipdhcps6", ipdhcps6_create, ipdhcps6_configure, ipdhcps6_start, ipdhcps6_version, IPCOM_IPD_ID_IPDHCPS6, IPCOM_LOG_IPDHCPS6, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)
    { "ipdhcps6", 0, 0, 0, 0, IPCOM_IPD_ID_IPDHCPS6, IPCOM_LOG_IPDHCPS6, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPDHCPR
    { "ipdhcpr", ipdhcpr_create, ipdhcpr_configure, ipdhcpr_start, ipdhcpr_version, IPCOM_IPD_ID_IPDHCPR, IPCOM_LOG_IPDHCPR, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)
    { "ipdhcpr", 0, 0, 0, 0, IPCOM_IPD_ID_IPDHCPR, IPCOM_LOG_IPDHCPR, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPWEBS
    { "ipwebs", ipwebs_create, ipwebs_configure, ipwebs_start, ipwebs_version, IPCOM_IPD_ID_IPWEBS, IPCOM_LOG_IPWEBS, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "ipwebs", 0, 0, 0, 0, IPCOM_IPD_ID_IPWEBS, IPCOM_LOG_IPWEBS, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPRIP
    { "iprip", iprip_create, iprip_configure, iprip_start, iprip_version, IPCOM_IPD_ID_IPRIP, IPCOM_LOG_IPRIP, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "iprip", 0, 0, 0, 0, IPCOM_IPD_ID_IPRIP, IPCOM_LOG_IPRIP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPRIPNG
    { "ipripng", ipripng_create, ipripng_configure, ipripng_start, ipripng_version, IPCOM_IPD_ID_IPRIPNG, IPCOM_LOG_IPRIP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPSNTP
    { "ipsntp", ipsntp_create, ipsntp_configure, ipsntp_start, ipsntp_version, IPCOM_IPD_ID_IPSNTP, IPCOM_LOG_IPSNTP, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)
    { "ipsntp", 0, 0, 0, 0, IPCOM_IPD_ID_IPSNTP, IPCOM_LOG_IPSNTP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPSNMP
    { "ipsnmp", ipsnmp_create, ipsnmp_configure, ipsnmp_start, ipsnmp_version, IPCOM_IPD_ID_IPSNMP, IPCOM_LOG_IPSNMP, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "ipsnmp", 0, 0, 0, 0, IPCOM_IPD_ID_IPSNMP, IPCOM_LOG_IPSNMP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPEMANATE
    { "ipemanate", ipemanate_create, ipemanate_configure, ipemanate_start, ipemanate_version, IPCOM_IPD_ID_IPEMANATE, IPCOM_LOG_IPEMANATE, 0},
#elif defined(IP_PORT_OSE5)
    { "ipemanate", 0, 0, 0, 0, IPCOM_IPD_ID_IPEMANATE, IPCOM_LOG_IPEMANATE, 0},
#endif

#ifdef ZEBOS
    { "ipzebos", ipzebos_create, ipzebos_configure, ipzebos_start, ipzebos_version, IPCOM_IPD_ID_ZEBOS, IPCOM_LOG_NONE, 0},
#elif defined(IP_PORT_OSE5)

    { "ipzebos", 0, 0, 0, 0, IPCOM_IPD_ID_ZEBOS, IPCOM_LOG_NONE, 0},
#endif

#ifdef IPDC
    { "ipdc", ipdc_create, ipdc_configure, ipdc_start, ipdc_version, IPCOM_IPD_ID_IPDC, IPCOM_LOG_NONE, 0},
#elif defined(IP_PORT_OSE5)

    { "ipdc", 0, 0, 0, 0, IPCOM_IPD_ID_IPDC, IPCOM_LOG_NONE, 0},
#endif

#ifdef IPNGC
    { "ipngc", ipngc_create, ipngc_configure, ipngc_start, ipngc_version, IPCOM_IPD_ID_IPNGC, IPCOM_LOG_NONE, IPCOM_IPD_FLAG_IPD_START /* | IPCOM_IPD_FLAG_HALTED*/},
#elif defined(IP_PORT_OSE5)

    { "ipngc", 0, 0, 0, 0, IPCOM_IPD_ID_IPNGC, IPCOM_LOG_NONE, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPQUAGGA
    { "ipquagga", ipquagga_create, ipquagga_configure, ipquagga_start, ipquagga_version, IPCOM_IPD_ID_IPQUAGGA, IPCOM_LOG_IPQUAGGA, IPCOM_IPD_FLAG_IPD_START /* | IPCOM_IPD_FLAG_HALTED*/},
#elif defined(IP_PORT_OSE5)

    { "ipquagga", 0, 0, 0, 0, IPCOM_IPD_ID_IPQUAGGA, IPCOM_LOG_IPQUAGGA, IPCOM_IPD_FLAG_IPD_START},
#endif

#if defined(IPDHCPC) && defined(IPCOM_SOCK)
    { "ipdhcpc", ipdhcpc_create, ipdhcpc_configure, ipdhcpc_start, ipdhcpc_version, IPCOM_IPD_ID_IPDHCPC, IPCOM_LOG_IPDHCPC,IPCOM_IPD_FLAG_IPD_START | IPCOM_IPD_FLAG_IPD_EXCEPTION},
#elif defined(IP_PORT_OSE5)

    { "ipdhcpc", 0, 0, 0, 0, IPCOM_IPD_ID_IPDHCPC, IPCOM_LOG_IPDHCPC, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPDNSC
    { "ipdnsc", ipdnsc_create, ipdnsc_configure, ipdnsc_start, ipdnsc_version, IPCOM_IPD_ID_IPDNSC, IPCOM_LOG_NONE, 0},
#elif defined(IP_PORT_OSE5)

    { "ipdnsc", 0, 0, 0, 0, IPCOM_IPD_ID_IPDNSC, IPCOM_LOG_NONE, 0},
#endif

#ifdef IPTFTPC
    { "iptftpc", iptftpc_create, iptftpc_configure, iptftpc_start, iptftpc_version, IPCOM_IPD_ID_IPTFTPC, IPCOM_LOG_IPTFTP, 0},
#elif defined(IP_PORT_OSE5)

    { "iptftpc", 0, 0, 0, 0, IPCOM_IPD_ID_IPTFTPC, IPCOM_LOG_IPTFTP, 0},
#endif

#ifdef IPFTPC
    { "ipftpc", ipftpc_create, ipftpc_configure, ipftpc_start, ipftpc_version, IPCOM_IPD_ID_IPFTPC, IPCOM_LOG_IPFTP, 0},
#elif defined(IP_PORT_OSE5)

    { "ipftpc", 0, 0, 0, 0, IPCOM_IPD_ID_IPFTPC, IPCOM_LOG_IPFTP, 0},
#endif

#ifdef IPNTP
    { "ipntp", ipntp_create, ipntp_configure, ipntp_start, ipntp_version, IPCOM_IPD_ID_IPNTP, IPCOM_LOG_IPNTP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPMCP
    { "ipmcp", ipmcp_create, ipmcp_configure, ipmcp_start, ipmcp_version, IPCOM_IPD_ID_IPMCP, IPCOM_LOG_IPMCP, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "ipmcp", 0, 0, 0, 0, IPCOM_IPD_ID_IPMCP, IPCOM_LOG_IPMCP, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPPRISM
    { "ipprism", ipprism_create, ipprism_configure, ipprism_start, ipprism_version, IPCOM_IPD_ID_IPPRISM, IPCOM_LOG_IPPRISM, 0},
#elif defined(IP_PORT_OSE5)

    { "ipprism", 0, 0, 0, 0, IPCOM_IPD_ID_IPPRISM, IPCOM_LOG_IPPRISM, 0},
#endif

#ifdef IPEAP
    { "ipeap", ipeap_create, ipeap_configure, ipeap_start, ipeap_version, IPCOM_IPD_ID_IPEAP, IPCOM_LOG_IPEAP, 0},
#elif defined(IP_PORT_OSE5)

    { "ipeap", 0, 0, 0, 0, IPCOM_IPD_ID_IPEAP, IPCOM_LOG_IPEAP, 0},
#endif


#ifdef IPSAFENET
    { "ipsafenet", ipsafenet_create, ipsafenet_configure, ipsafenet_start, ipsafenet_version, IPCOM_IPD_ID_IPSAFENET, IPCOM_LOG_IPSAFENET, 0},
#elif defined(IP_PORT_OSE5)

    { "ipsafenet", 0, 0, 0, 0, IPCOM_IPD_ID_IPSAFENET, IPCOM_LOG_IPSAFENET, 0},
#endif


#ifdef IPCCI
    { "ipcci", ipcci_create, ipcci_configure, ipcci_start, ipcci_version, IPCOM_IPD_ID_IPCCI, IPCOM_LOG_IPCCI, 0},
#elif defined(IP_PORT_OSE5)

    { "ipcci", 0, 0, 0, 0, IPCOM_IPD_ID_IPCCI, IPCOM_LOG_IPCCI, 0},
#endif

#ifdef IPNETPERF
    { "ipnetperf", ipnetperf_create, ipnetperf_configure, ipnetperf_start, ipnetperf_version, IPCOM_IPD_ID_IPNETPERF, IPCOM_LOG_NONE, 0},
#elif defined(IP_PORT_OSE5)

    { "ipnetperf", 0, 0, 0, 0, IPCOM_IPD_ID_IPNETPERF, IPCOM_LOG_NONE, 0},
#endif

#ifdef IPNETSNMP
    { "ipnetsnmp", ipnetsnmp_create, ipnetsnmp_configure, ipnetsnmp_start, ipnetsnmp_version, IPCOM_IPD_ID_IPNETSNMP, IPCOM_LOG_IPNETSNMP, 0},
#elif defined(IP_PORT_OSE5)

    { "ipnetsnmp", 0, 0, 0, 0, IPCOM_IPD_ID_IPNETSNMP, IPCOM_LOG_IPNETSNMP, 0},
#endif

#if defined(IPIPSEC) || defined(IPIPSEC2)
    { "ipipsec", ipipsec_create, ipipsec_configure, ipipsec_start, ipipsec_version, IPCOM_IPD_ID_IPIPSEC, IPCOM_LOG_IPIPSEC, 0},
#elif defined(IP_PORT_OSE5)

    { "ipipsec", 0, 0, 0, 0, IPCOM_IPD_ID_IPIPSEC, IPCOM_LOG_IPIPSEC, 0},
#endif

#ifdef IPIKE
    { "ipike", ipike_create, ipike_configure, ipike_start, ipike_version, IPCOM_IPD_ID_IPIKE, IPCOM_LOG_IPIKE, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "ipike", 0, 0, 0, 0, IPCOM_IPD_ID_IPIKE, IPCOM_LOG_IPIKE, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPMARVELL
    { "ipmarvell", ipmarvell_create, ipmarvell_configure, ipmarvell_start, ipmarvell_version, IPCOM_IPD_ID_IPMARVELL, IPCOM_LOG_NONE, 0},
#elif defined(IP_PORT_OSE5)

    { "ipmarvell", 0, 0, 0, 0, IPCOM_IPD_ID_IPMARVELL, IPCOM_LOG_NONE, 0},
#endif

#ifdef IPANVL
    { "ipanvl", ipanvl_create, ipanvl_configure, ipanvl_start, ipanvl_version, IPCOM_IPD_ID_IPANVL, IPCOM_LOG_NONE, 0},
#elif defined(IP_PORT_OSE5)

    { "ipanvl", 0, 0, 0, 0, IPCOM_IPD_ID_IPANVL, IPCOM_LOG_NONE, 0},
#endif

#ifdef INCLUDE_IPDIAMETERP

#ifdef INCLUDE_IPDIAMETERC
	/* as diameter client and proxy both are defined but they can not run at the same time , keep the proxy in halt state */
    { "ipdiameterp", ipdiameterp_create, ipdiameterp_configure, ipdiameterp_start, ipdiameter_version, IPCOM_IPD_ID_IPDIAMETERP, IPCOM_LOG_IPDIAMETER, IPCOM_IPD_FLAG_HALTED},
#else
    { "ipdiameterp", ipdiameterp_create, ipdiameterp_configure, ipdiameterp_start, ipdiameter_version, IPCOM_IPD_ID_IPDIAMETERP, IPCOM_LOG_IPDIAMETER, IPCOM_IPD_FLAG_IPD_START},
#endif
#endif /*INCLUDE_IPDIAMETERP*/

#ifdef INCLUDE_IPDIAMETERC
    { "ipdiameterc", ipdiameterc_create, ipdiameterc_configure, ipdiameterc_start, ipdiameter_version, IPCOM_IPD_ID_IPDIAMETERC, IPCOM_LOG_IPDIAMETER, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "ipdiameterc", 0, 0, 0, 0, IPCOM_IPD_ID_IPDIAMETERC, IPCOM_LOG_IPDIAMETER, 0},
#endif

#ifdef IPIFPROXY
    { "ipifproxy", ipifproxy_create, ipifproxy_configure, ipifproxy_start, ipifproxy_version, IPCOM_IPD_ID_IPIFPROXY, IPCOM_LOG_IPIFPROXY, 0},
#endif

#ifdef INCLUDE_IPWLAN_BROADCOM
    { "ipwlan_broadcom", ipwlan_broadcom_create, ipwlan_broadcom_configure, ipwlan_broadcom_start, ipwlan_broadcom_version, IPCOM_IPD_ID_IPWLAN, IPCOM_LOG_NONE, 0},
#endif

#ifdef INCLUDE_IPWLAN_ATHEROS
	{ "ipwlan_atheros", ipwlan_atheros_create, ipwlan_atheros_configure, ipwlan_atheros_start, ipwlan_atheros_version, IPCOM_IPD_ID_IPWLAN, IPCOM_LOG_NONE, 0},
#endif

#ifdef IP8021X
    { "ip8021x", ip8021x_create, ip8021x_configure, ip8021x_start, ip8021x_version, IPCOM_IPD_ID_IP8021X, IPCOM_LOG_IP8021X, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "ip8021x", 0, 0, 0, 0, IPCOM_IPD_ID_IP8021X, IPCOM_LOG_IP8021X, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPWPS
    { "ipwps", ipwps_create, ipwps_configure, ipwps_start, ipwps_version, IPCOM_IPD_ID_IPWPS, IPCOM_LOG_IPWPS, IPCOM_IPD_FLAG_IPD_START},
#elif defined(IP_PORT_OSE5)

    { "ipwps", 0, 0, 0, 0, IPCOM_IPD_ID_IPWPS, IPCOM_LOG_IPWPS, IPCOM_IPD_FLAG_IPD_START},
#endif

#ifdef IPROHC
    { "iprohc", iprohc_create, iprohc_configure, iprohc_start, iprohc_version, IPCOM_IPD_ID_IPROHC, IPCOM_LOG_IPROHC, 0},
#endif

    { IP_NULL, IP_NULL, IP_NULL, IP_NULL, IP_NULL, -1, IPCOM_LOG_NONE, 0 }  /* end entry. */
};




/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
