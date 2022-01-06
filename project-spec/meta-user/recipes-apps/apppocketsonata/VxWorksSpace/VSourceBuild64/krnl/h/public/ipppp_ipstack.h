/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPPPP_IPSTACK_H
#define IPPPP_IPSTACK_H

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

#include "ipppp_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_sock.h>
#include <ipcom_sock6.h>
#include <ipcom_netif.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */


/*
 *===========================================================================
 *                         PPP I/O events
 *===========================================================================
 * IO events are passed from PPP to -> TCP/IP stack.
 */
#define IPPPP_EIOXBLOCKOK      0x2001    /* IP_NULL; Ok to block? */
#define IPPPP_EIOXDRVIOCTL     0x2002    /* Ipppp_eio_ioctl; Driver ioctl */
#define IPPPP_EIOXOUTPUT_IF    0x2003    /* Ipcom_pkt; Output packet to if. */
#define IPPPP_EIOXINDEXTONETIF 0x2004    /* int; Get Ipcom_netif pointer from index. */
#define IPPPP_EIOXCODE_LOCK    0x2005    /* -; Lock IPNET/IPLITE code. */
#define IPPPP_EIOXCODE_UNLOCK  0x2006    /* -; Unlock IPNET/IPLITE code. */
#define IPPPP_EIOXIF_LOCK      0x2007    /* -; Lock interface. */
#define IPPPP_EIOXIF_UNLOCK    0x2008    /* -; Unlock interface. */

#define IPPPP_EIOXUP_IN        0x2011    /* Ipppp_eio_in;  IPv4 UP */
#define IPPPP_EIOXDOWN_IN      0x2012    /* Ipppp_eio_in;  IPv4 DOWN */
#define IPPPP_EIOXINPUT_IN     0x2013    /* Ipcom_pkt;     IPv4 input packet */
#define IPPPP_EIOXDSTADDR_IN   0x2014    /* struct Ip_in_addr *; Check for IPv4 dstaddr (host endian) */

#define IPPPP_EIOXUP_IN6       0x2021    /* Ipppp_eio_in6; IPv6 UP */
#define IPPPP_EIOXDOWN_IN6     0x2022    /* Ipppp_eio_in6; IPv6 DOWN */
#define IPPPP_EIOXINPUT_IN6    0x2023    /* Ipcom_pkt;     IPv6 input packet */


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

struct Ipppp_link_struct; /* dummy */

/*
 *===========================================================================
 *                         Ipppp_eio_ioctl
 *===========================================================================
 */
typedef struct Ipppp_eio_ioctl_struct
{
    int    command;
    void  *data;
}
Ipppp_eio_ioctl;


/*
 *===========================================================================
 *                         Ipppp_eio_in
 *===========================================================================
 * IO event type used with IPPPP_EIOXUP_IN and IPPPP_EIOXDOWN_IN.
 */
#ifdef IPCOM_USE_INET
typedef struct Ipppp_eio_in_struct
{
    Ip_u32   local_addr_n;
    Ip_u32   peer_addr_n;
}
Ipppp_eio_in;
#endif /* IPCOM_USE_INET */


/*
 *===========================================================================
 *                         Ipppp_eio_in6
 *===========================================================================
 * IO event type used with IPPPP_EIOXUP_IN6 and IPPPP_EIOXDOWN_IN6.
 */
#ifdef IPCOM_USE_INET6
typedef struct Ipppp_eio_in6_struct
{
    struct Ip_in6_addr  local_addr;
    struct Ip_in6_addr  peer_addr;
}
Ipppp_eio_in6;
#endif /* IPCOM_USE_INET6 */


/*
 *===========================================================================
 *                         Ipppp_ipstack_data
 *===========================================================================
 */

typedef int (*Ipppp_if_init)(void *netif);
typedef int (*Ipppp_if_attach)(Ipcom_netif *netif);
typedef int (*Ipppp_if_create)(struct Ip_ifreq *ifreq);
typedef int (*Ipppp_pppoe_create)(struct Ip_ifreq *ifreq);
typedef int (*Ipppp_pppoe_input)(Ipcom_netif *ethif, Ipcom_pkt *pkt);

#ifdef IPPPP_USE_PPPL2TP
typedef int (*Ipppp_pppl2tp_create)(struct Ip_ifreq *ifreq);
typedef int (*Ipppp_pppl2tp_input)(Ip_u32 ifindex, void *payload, Ip_u16 length);
#endif
 
/*
 *===========================================================================
 *                         Ipppp_pppoe_data
 *===========================================================================
 */
/* Secret size. */
#define IPPPP_PPPOE_SECRET_SIZE  16
typedef struct Ipppp_pppoe_data_struct
{
    Ipcom_atomic_t   num_sessions;

#ifdef IPPPP_PPPOE_USE_MD5
    Ip_u8            secret[IPPPP_PPPOE_SECRET_SIZE];
#endif
}
Ipppp_pppoe_data;

/*
 *===========================================================================
 *                         Ipppp_ipstack_data
 *
 * In a system with multiple stack instances, this structure contains all
 * the data that is shared among all stack instances.
 *===========================================================================
 */
typedef struct Ipppp_ipstack_data_struct
{
    Ipppp_if_init        if_init;
    Ipppp_if_attach      if_attach;
    Ipppp_if_create      if_create;

#ifdef IPPPP_USE_PPPOE
    Ipppp_pppoe_create   pppoe_create;
    Ipppp_pppoe_input    pppoe_input;
#endif

#ifdef IPPPP_USE_PPPL2TP
    Ipppp_pppl2tp_create pppl2tp_create;
    Ipppp_pppl2tp_input  pppl2tp_input;
#endif

    Ip_u8                zero[8];
    Ipcom_atomic_t       name_index;

#ifdef IPPPP_USE_PPPOE
    Ipppp_pppoe_data     pppoe;
#endif

#ifdef IPPPP_USE_PPPMP
    Ip_u8                epd_data[IPPPPMP_EPD_DATA_MAX]; /* Default 20 (from RFC 1990) */
    Ip_u8                epd_class;
    Ip_u8                epd_datalen;
#endif

}
Ipppp_ipstack_data;

/*
 *===========================================================================
 *                         Ipppp_stats
 *===========================================================================
 * IPPPP debug statistics useful for debugging the stack if things go wrong.
 */
#if defined(IP_DEBUG) || defined(IPPPP_STATISTICS)
typedef struct Ipppp_stats_struct
{
    int    input;
    int    input_discard;
    int    input_err_notrunning;
    int    input_err_linkdown;
    int    input_err_short;
    int    input_err_long;
    int    input_err_noctrl;
    int    input_err_badfcs;
    int    input_err_esc_enomem;
    int    input_err_truncated;
    int    input_err_noproto;
    int    input_err_lcp;
    int    input_err_ipcp;
    int    input_err_ipv6cp;
    int    input_err_chap;
    int    input_err_pap;
    int    input_lcpdown;
    int    input_ipcpdown;
    int    input_ipv6cpdown;
    int    input_authdown;

    Ip_u32   ipv4_out_discard_small;
    Ip_u32   ipv4_out_discard_down;

    Ip_u32   ipv6_out_discard_small;
    Ip_u32   ipv6_out_discard_down;

    Ip_u32   outputd_discard_linkdown;
    Ip_u32   outputd_discard_netifdown;
    Ip_u32   outputd_discard_drvfail;
}
Ipppp_stats;

#define IPPPP_STATS(xvar)      ipnet_ptr()->ppp.stats.xvar
#else
#define IPPPP_STATS(xvar)      IP_NOOP
#endif

/*
 *===========================================================================
 *                         Ipppp_data
 *
 * In a system with multiple stack instances, this structure contains the
 * per-instance ppp/pppoe data.
 *===========================================================================
 */
#define IPPPP_PIDATA_BUFSIZE 128
typedef struct Ipppp_data_struct
{

#if defined(IP_DEBUG) || defined(IPPPP_STATISTICS)
    Ipppp_stats    stats;
#endif
    char           buf[IPPPP_PIDATA_BUFSIZE];
}
Ipppp_data;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

IP_PUBLIC int  ipppp_if_init(Ipcom_netif *netif);
IP_PUBLIC int  ipppp_if_attach(Ipcom_netif *netif);
IP_PUBLIC int  ipppp_if_create(struct Ip_ifreq *ifreq);

IP_PUBLIC void ipppp_tick(Ipcom_netif *netif);

IP_PUBLIC int  ipppp_ioevent(Ipcom_netif *netif, int command, void *data);
IP_PUBLIC int  ipppp_input(Ipcom_netif *netif, Ipcom_pkt *pkt);
IP_PUBLIC int  ipppp_ioctl(Ipcom_netif *netif, Ip_u32 command, void *data);

IP_PUBLIC long ipcom_ppp_ioevent(Ipcom_netif *netif, int command, void *data);

IP_PUBLIC Ip_bool
ipppp_sysvar_get_conf_string(Ipcom_netif *netif, struct Ipppp_link_struct *link, const char *name, const char *string);

#ifdef IPCOM_USE_INET
IP_PUBLIC int ipppp_ip4_output(Ipcom_netif *netif, Ipcom_pkt *pkt);
#endif

#ifdef IPCOM_USE_INET6
IP_PUBLIC int ipppp_ip6_output(Ipcom_netif *netif, Ipcom_pkt *pkt);
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
