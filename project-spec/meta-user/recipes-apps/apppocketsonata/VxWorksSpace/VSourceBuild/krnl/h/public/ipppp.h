/* ipppp.h - API of PPP module */

/*
 * Copyright (c) 2006-2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17may16,ljl  added definition of security event IDs (F3805)
*/

#ifndef IPPPP_H
#define IPPPP_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
This library contains the API for IPPPP - PPP module
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
#include <ipcom_auth.h>
#include <ipcom_list.h>
#include <vwModNum.h>

#ifdef IPPPP_USE_PPPL2TP
#include "ipl2tp.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */
 /*security event ID*/
#define SEC_EVENT_PPP_LOGIN_FAILED (M_pppLib | 1)

/*
 *===========================================================================
 *                         IPPPP_RELEASE
 *===========================================================================
 * IPPPP release version.
 */
#define IPPPP_RELEASE 60900

/* PPP packet protocol values (16-bit): */
#define IPPPP_PROTOCOL_LCP      0xc021
#define IPPPP_PROTOCOL_PAP      0xc023
#define IPPPP_PROTOCOL_CHAP     0xc223
#define IPPPP_PROTOCOL_IPCP     0x8021
#define IPPPP_PROTOCOL_IPV6CP   0x8057
#define IPPPP_PROTOCOL_IPV4     0x0021
#define IPPPP_PROTOCOL_IPV6     0x0057
#define IPPPP_PROTOCOL_CCP      0x80fd  /* not supported. */

#ifdef IPPPP_USE_PPPMP
#define IPPPP_PROTOCOL_MP       0x003d  /* Multilink Protocol ID */
#endif /* IPPPP_USE_PPPMP */

#ifdef IPPPP_USE_VJCOMP
#define IPPPP_COMPPROT_VJCOMP             0x002d
#define IPPPP_PROTOCOL_VJC_COMPR_TCP      0x002d
#define IPPPP_PROTOCOL_VJC_UNCOMPR_TCP    0x002f
#endif /* IPPPP_USE_VJCOMP */


#ifdef IPPPP_USE_PPPL2TP
/*
 *===========================================================================
 *      Ipppp_pppl2tp_status
 *===========================================================================
 *
 */
/*lint -e641*/
typedef enum
{
    IPPPP_PPPL2TP_STATUS_OK,                  /* Operation completed with success */
    IPPPP_PPPL2TP_STATUS_OPEN_OPER,           /* Open operation started */
    IPPPP_PPPL2TP_STATUS_CLOSE_OPER,          /* Close operation started */
    IPPPP_PPPL2TP_STATUS_OUTPUT_OPER,         /* Output operation started */
    IPPPP_PPPL2TP_STATUS_ERR,                 /* General error */
    IPPPP_PPPL2TP_STATUS_ERR_NO_V2,           /* L2TPv2 is not enabled */
    IPPPP_PPPL2TP_STATUS_ERR_IF_IN_USE,       /* Interface is already in use */
    IPPPP_PPPL2TP_STATUS_ERR_IFNUM_FAIL,      /* Ifnum does not match any interface */
    IPPPP_PPPL2TP_STATUS_ERR_NO_ADDR,         /* No peer address has been set */
    IPPPP_PPPL2TP_STATUS_ERR_TOPEN_TMO,       /* Tunnel open timed out */
    IPPPP_PPPL2TP_STATUS_ERR_TOPEN_FAIL,      /* Tunnel open failed */
    IPPPP_PPPL2TP_STATUS_ERR_TATTR,           /* Error in tunnel attribute */
    IPPPP_PPPL2TP_STATUS_ERR_TCLOSE_FAIL,     /* Tunnel close failed */
    IPPPP_PPPL2TP_STATUS_ERR_SOPEN_TMO,       /* Session open timed out */
    IPPPP_PPPL2TP_STATUS_ERR_SOPEN_FAIL,      /* Session open failed */
    IPPPP_PPPL2TP_STATUS_ERR_SKEY_FAIL,       /* Session key remove failed */
    IPPPP_PPPL2TP_STATUS_ERR_SCLOSE_FAIL,     /* Session close failed */
    IPPPP_PPPL2TP_STATUS_ERR_DRVUP_FAIL,      /* Unable to bring driver up */
    IPPPP_PPPL2TP_STATUS_ERR_OUTQ_INIT_FAIL,  /* Output queue init failed */
    IPPPP_PPPL2TP_STATUS_ERR_OUTQ_SEND_FAIL,  /* Output queue send failed */
    IPPPP_PPPL2TP_STATUS_ERR_SKEY_NOT_FOUND   /* Session key lookup failed */
}
Ipppp_pppl2tp_status;
#endif /* IPPPP_USE_PPPL2TP */

/*
 *===========================================================================
 *                         PPP specific ioctls
 *===========================================================================
 * IO control commands specific to the PPP protocol.
 */

/* Driver PPP ioctls: */
#define IP_SIOCXPPPGDRVCONF      IP_IOWR(PPP, 1, R, struct Ip_pppreq) /* Ipcom_ppp_drvconf; Get PPP driver config (default). */
#define IP_SIOCXPPPGDRVINFO      IP_IOWR(PPP, 2, R, struct Ip_pppreq) /* Ipcom_ppp_drvconf; Get PPP driver info (current). */

#define IP_SIOCXPPPSDRVBAUDRATE  IP_IOWR(PPP, 3, W, struct Ip_pppreq) /* Ip_u32; Set PPP driver baudrate. */
#define IP_SIOCXPPPSDRVUP        IP_IOWR(PPP, 4, R, struct Ip_pppreq) /* -; Make driver signal up (test ioctl) */
#define IP_SIOCXPPPSDRVDOWN      IP_IOWR(PPP, 5, R, struct Ip_pppreq) /* -; Make driver signal down (test ioctl) */
#define IP_SIOCXPPPSDRVWINCOMPAT IP_IOWR(PPP, 6, R, struct Ip_pppreq) /* int; Enable wincompat mode */

/* Link layer PPP ioctls: */
#define IP_SIOCXPPPGFLAGS    IP_IOWR(PPP, 10, R, struct Ip_pppreq) /* Ip_u32; Get PPP main flags (see IP_PPP_FLAG_xxx) */
#define IP_SIOCXPPPSFLAGS    IP_IOWR(PPP, 11, W, struct Ip_pppreq) /* Ip_u32; Set PPP main flags (in ipcom_netif.h) */
#define IP_SIOCXPPPGCONF     IP_IOWR(PPP, 12, R, struct Ip_pppreq) /* Ipcom_ppp_conf; Get PPP main config. */
#define IP_SIOCXPPPSCONF     IP_IOWR(PPP, 13, W, struct Ip_pppreq) /* Ipcom_ppp_conf; Set PPP main config. */
#define IP_SIOCXPPPGUSER     IP_IOWR(PPP, 14, R, struct Ip_pppreq) /* char [IPCOM_AUTH_USERNAME_MAX]; Get local user. */
#define IP_SIOCXPPPSUSER     IP_IOWR(PPP, 15, W, struct Ip_pppreq) /* char [IPCOM_AUTH_USERNAME_MAX]; Set local user. */
#define IP_SIOCXPPPGPASSWD   IP_IOWR(PPP, 16, R, struct Ip_pppreq) /* char [IPCOM_AUTH_PASSWORD_MAX]; Get local password. */
#define IP_SIOCXPPPSPASSWD   IP_IOWR(PPP, 17, W, struct Ip_pppreq) /* char [IPCOM_AUTH_PASSWORD_MAX]; Set local password. */
#define IP_SIOCXPPPGPEERUSER IP_IOWR(PPP, 18, R, struct Ip_pppreq) /* char [IPCOM_AUTH_USERNAME_MAX]; Get peer user. */

#define IP_SIOCXPPPSETIF     IP_IOWR(PPP, 20, W, struct Ip_pppreq) /* if_name[IP_IFNAMSIZ]; Set pppoe Ethernet interface */

#define IP_SIOCXPPPGDINFO    IP_IOWR(PPP, 22, R, struct Ip_pppreq) /* Ipcom_ppp_debuginfo; Get PPP debug info. */
#define IP_SIOCXPPPLOGIN     IP_IOWR(PPP, 23, R, struct Ip_pppreq) /* Ipcom_ppp_login; Set PPP login info. */
#define IP_SIOCXPPPAUTH      IP_IOWR(PPP, 24, R, struct Ip_pppreq) /* Ipcom_ppp_auth; Set PPP authenticate info. */

#ifdef IPPPP_USE_PPPMP
#define IP_SIOCGPPPIFFLAGS   IP_IOWR(PPP, 25, R, struct Ip_pppreq) /* Flags in Ipppp_netif struct. */
#define IP_SIOCGPPPIFLINKS   IP_IOWR(PPP, 26, R, struct Ip_pppreq) /* Number of open links. */
#endif /* IPPPP_USE_PPPMP */

#ifdef IPPPP_USE_PPPL2TP
#define IP_SIOCSPPPL2TPPADDR IP_IOWR(PPP, 27, W, struct Ip_pppreq) /* Set peer address for L2TP. */
#define IP_SIOCGPPPL2TPDRV   IP_IOWR(PPP, 28, R, struct Ip_pppreq) /* Get L2TP driver info. */
#endif /* IPPPP_USE_PPPL2TP */

#define IP_SIOCXPPPSDRVRCVACCM  IP_IOWR(PPP, 29, W, struct Ip_pppreq) /* Ipcom_ppp_drvconf; Set PPP driver recv ACCM */

/*
 *===========================================================================
 *                         IP_PPP_FLAG_xxx
 *===========================================================================
 * PPP flags used with IP_SIOCXPPP[G|S]FLAGS ioctl().
 */

/* Disable Address/Control compression in both directions (snd/rcv). */
#define IP_PPP_FLAG_NOACCOMP      0x00000001

/* Do not send or ack ACCM confreq. */
#define IP_PPP_FLAG_NOACCM        0x00000002

/* Require the peer to authenticate itself before allowing snd/rcv NCP. */
#define IP_PPP_FLAG_AUTH          0x00000004

/* Do not require the peer to authenticate itself, i.e. do not ask for authentication. */
#define IP_PPP_FLAG_NOAUTH        0x00000008

/* Do not agree to authenticate using PAP. */
#define IP_PPP_FLAG_REFUSE_PAP    0x00000010

/* Do not agree to authenticate using MD5 CHAP. */
#define IP_PPP_FLAG_REFUSE_CHAP   0x00000020

#define IP_PPP_FLAG_NOPCOMP       0x00000040

#ifdef IPPPP_USE_PPPMP
#define IP_PPP_FLAG_MP_SHADOW         0x00000080  /* MP has been negotiated on link */
#define IP_PPP_FLAG_MP_MEMBER         0x00000100  /* MP has been negotiated on link */
#endif /* IPPPP_USE_PPPMP */

#ifdef IPPPP_USE_PPPMP
/* Flags for Ipppp_netif: pppflags */
#define IPPPP_PPPIFFLAG_NEG_MP              0x00000001  /* Try to negotiate MP on this I/F. */
#define IPPPP_PPPIFFLAG_NEG_SSN             0x00000002  /* Try to negotiate Short Sequence Number for MP on this I/F. */
#define IPPPP_PPPIFFLAG_MP_BUNDLE           0x00000004  /* Use MP on this I/F. */
#define IPPPP_PPPIFFLAG_MP_MEMBER           0x00000008  /* Use MP on this I/F. */
#endif /* IPPPP_USE_PPPMP */

/*
 *===========================================================================
 *                   IPPPP action callbacks
 *===========================================================================
 */
typedef int (*Ipppp_action_cb)(Ipcom_netif *netif, int action, void *data);


/* Initialization action is called directly after the PPP/PPPoE interface has
 * been attached, i.e. directly after ipcom_if_attach() has been called.
 * The init action is a good place to configure the interface with static
 * interface configuration like LCP, AUTH, IPCP and/or IPV6CP etc.
 * Note: The init action has replaced the example action callback function
 *       in previous releases.
 */
#define IPPPP_ACTION_INIT              1

/* Called when LCP is starting. Configure LCP here.
 */
#define IPPPP_ACTION_LCP_STARTING      2


/* Called when IPCP is starting.
 * Use this callback to set desired local IPv4 address.
 * The default local IP address is 0, which means we want the peer to suggest
 * an IP address for us.
 */
#define IPPPP_ACTION_IPCP_STARTING     3

/* Called when IPV6CP is starting.
 * Use this callback to set desired peer IPv6 address.
 * The default peer IP address is 0, which means we will refuse to suggest
 * an IP address for the peer.
 */
#define IPPPP_ACTION_IPV6CP_STARTING   4


/* IPv4 / IPv6 up/down actions:
 * Enter code which must be run when PPP comes up/down here.
 */
#define IPPPP_ACTION_IP_UP             5
#define IPPPP_ACTION_IP_DOWN           6
#define IPPPP_ACTION_IPV6_UP           7
#define IPPPP_ACTION_IPV6_DOWN         8


/* Called when peer sends IPv6 Identifier Configure-Request.
 * See RFC274:p6-8 for details.
 * Return -1 if refuse to suggest peer IP identifier, else 0.
 * 'data' = pointer to 128-bit IPv6 identifier.
 */
#define IPPPP_ACTION_PEER_IDENTIFIER   9

/* Called when we need to authenticate ourselves (i.e. login) to the peer.
 * User code must call ioctl(IP_SIOCXPPPLOGIN) with the same 'data',
 * user name and password when ready to login.
 */
#define IPPPP_ACTION_LOGIN             10

/* Called when we must authenticate peer, i.e. peer tries to login.
 * 'data' points to an Ipppp_auth_cookie structure allocated by IPPPP.
 * User code must call ioctl(IP_SIOCXPPPAUTH) once peer is authenticated.
 */
#define IPPPP_ACTION_AUTH              11


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         Ipcom_ppp_conf
 *===========================================================================
 * 'data' structure for IPPP
 */
typedef struct Ipppp_auth_cookie_struct
{
    Ip_u32 ifindex;
    Ip_u32 link_index;

    char   username[IPCOM_AUTH_USERNAME_MAX];
    char   password[IPCOM_AUTH_PASSWORD_MAX];

#ifdef IPPPP_USE_AUTH_CHAP
    Ip_u8  chap_ident;
    int    chap_challenge_size;
    Ip_u8  chap_challenge[48];
    Ip_u8  chap_response[16];
#endif

    Ip_u16 protocol;   /* IPPPP_PROTOCOL_ PAP or _CHAP */
}
Ipppp_auth_cookie;


/*
 *===========================================================================
 *                         Ipcom_ppp_conf
 *===========================================================================
 * ioctl structure for IP_SIOCXPPP[G|S]CONF options.
 */
typedef struct Ipcom_ppp_conf_struct
{
    Ip_u16     restart;          /* Retransmission timeout in seconds. Default 3 */
    Ip_u8      max_failure;      /* Max # ConfNak returned before sending ConfRej. Default 10 */
    Ip_u8      max_configure;    /* Max # ConfReq retransmissions. Default 10 */
    Ip_u8      max_terminate;    /* Max # TermReq retransmissions. Default 2 */
    Ip_u8      max_authreq;      /* Max # auth retransmissions before link terminate. Default 3 */
    Ip_u8      pad[2];
}
Ipcom_ppp_conf;

#ifdef IPPPP_USE_PPPMP

/* EPD Classes: classes 1 (local) and 4 (magic) are deprecated */
#define IPPPPMP_EPD_CLASS_NULL   0
#define IPPPPMP_EPD_CLASS_IP     2
#define IPPPPMP_EPD_CLASS_MAC    3
#define IPPPPMP_EPD_CLASS_PHONE  5
#define IPPPPMP_MAX_LINKS        10

#endif /* IPPPP_USE_PPPMP */


/*
 *===========================================================================
 *                         Ipcom_ppp_drvconf
 *===========================================================================
 * ioctl structure for IP_SIOCXPPPGDRVCONF option.
 */
typedef struct Ipcom_ppp_drvconf_struct
{
    Ip_u32     drv_flags;     /* PPP driver flags. */
    Ip_u32     baudrate;      /* Baudrate. */

    Ip_u32     rcv_accm;      /* Recv asyncmap. Default 0xffffffff */
    Ip_u32     req_rcv_accm;  /* Recv asyncmap request, to negotiate if possible */
    Ip_u32     snd_accm;      /* Send asyncmap. Default 0xffffffff */
    Ip_u16     mru;           /* Maximum Receive Unit. Default 1500. */
    Ip_u16     mtu;           /* Maximum Transmit Unit. Default 1500. */

#ifdef IPPPP_USE_PPPMP
    Ip_u16     local_mrru;
    Ip_u16     peer_mrru;
    Ip_u8      peer_epd_class;                       /* Endpoint discriminator class */
    Ip_u8      peer_epd_data[IPPPPMP_EPD_DATA_MAX];  /* Endpoint discriminator data */
    Ip_u8      peer_epd_datalen;
    Ip_u8      ssn; /*Short Sequence Number usage allowed (1) or not (0)*/
#endif /* IPPPP_USE_PPPMP */
}
Ipcom_ppp_drvconf;

/* PPP driver flags (drv_flags): */
#define IP_DRVPPP_FLAG_NOFLAG      0x00000001  /* No initial/trailing PPP flag (0x7e). */
#define IP_DRVPPP_FLAG_NOESCAPE    0x00000002  /* Do not byte-escape output/input packets. */
#define IP_DRVPPP_FLAG_NOFCS       0x00000004  /* Do not input-check or add output FCS. */
#define IP_DRVPPP_FLAG_NOACFC      0x00000008  /* Do not snd/rcv addr(0xff) ctrl(0x03). */

#ifdef IPPPP_USE_VJCOMP
#define IP_DRVPPP_FLAG_USE_VJCOMP  0x00000010  /* Use Van Jacobson compression */
#endif /* IPPPP_USE_VJCOMP */


#ifdef IPPPP_USE_PPPL2TP
/*
 *===========================================================================
 *                         Ipppp_pppl2tp_pkt_que_entry
 *===========================================================================
 * Structure to hold output packet information 
 */
typedef struct Ipppp_pppl2tp_pkt_que_entry_struct
{
    Ipcom_netif        *netif;
    Ipcom_pkt          *pkt;
} 
Ipppp_pppl2tp_pkt_que_entry;


/*
 *===========================================================================
 *                         Ipppp_pppl2tp_link
 *===========================================================================
 * L2TP PPP link data.
 */
typedef struct Ipppp_pppl2tp_drv_link_struct
{
    Ipcom_netif            *netif;       /* generic interface data */
    Ip_u32                  tid;         /* tunnel ID */
    Ip_u32                  sid;         /* session ID */
    Ipppp_pppl2tp_status    status;      /* Status of current or most recent operation */
    union Ip_sockaddr_union paddr;       /* peer IP address */
} Ipppp_pppl2tp_drv_link;
#endif /* IPPPP_USE_PPPL2TP */

/*
 *===========================================================================
 *                         Ipcom_ppp_debuginfo
 *===========================================================================
 * ioctl structure for IP_SIOCXPPPGDINFO option.
 */
typedef struct Ipcom_ppp_debuginfo_struct
{
    Ip_u32  link_flags;  /* See ipnet_netif.h */
    Ip_u32  pppoe_eth_ifindex;
    Ip_u8   link_state;
    Ip_u8   lcp_state;
    Ip_u8   auth_state;
    Ip_u8   ipcp_state;
    Ip_u8   ipv6cp_state;
}
Ipcom_ppp_debuginfo;


/*
 *===========================================================================
 *                         Ipcom_ppp_login
 *===========================================================================
 * ioctl structure for IP_SIOCXPPPLOGIN. Used to login a user during PPP
 * PAP/CHAP negotiation.
 *
 * Struct members:
 * ifindex      -  PPP interface index
 * link_index   -  PPP link index (currently always 0)
 * login_cookie -  IPPPP specific, do not read/write. Pass the same cookie
 *                 from the action callback to the login function
 * username     -  PPP username, e.g. "bill"
 * password     -  The cleartext password of user 'name'
 */
typedef struct Ipcom_ppp_login_struct
{
    Ip_u32 ifindex;
    Ip_u32 link_index;

    void  *login_cookie;

    char   username[IPCOM_AUTH_USERNAME_MAX];
    char   password[IPCOM_AUTH_PASSWORD_MAX];

}
Ipcom_ppp_login;


/*
 *===========================================================================
 *                         Ipcom_ppp_auth
 *===========================================================================
 * ioctl structure for IP_SIOCXPPPAUTH. Used to authenticate a user during PPP
 * PAP/CHAP negotiation.
 *
 * Struct members:
 */
typedef struct Ipcom_ppp_auth_struct
{
    Ip_u32    ifindex;
    Ip_u32    link_index;

    Ip_bool   success;

    Ipcom_auth_userinfo    userinfo;
}
Ipcom_ppp_auth;


/*
 *===========================================================================
 *                         Ip_pppreq
 *===========================================================================
 * Interface request structure used for PPP ioctl's.  All interface
 * ioctl's must have parameter definitions which begin with ifr_name and
 * link_index. The remainder may be option specific.
 */
struct Ip_pppreq
{
    char    pppr_name[IP_IFNAMSIZ];       /* if name, e.g. "ppp0" */
    int     link_index;   /* link_index, currently unused (for MPPP) */

    union
    {
        Ip_u32               ppp_flags;    /* Get/Set PPP flags. */

        Ipcom_ppp_conf       pppconf;      /* Get/Set PPP protocol configuration. */

        char                 username[IPCOM_AUTH_USERNAME_MAX];
        char                 password[IPCOM_AUTH_PASSWORD_MAX];

        char                 if_name[IP_IFNAMSIZ];

        Ipcom_ppp_drvconf    drvconf;       /* Get PPP driver configuration. */
        Ip_u32               drv_baudrate;  /* Set PPP driver baudrate. */
        int                  drv_wincompat; /* Windows compat mode */
        Ip_u32               drv_rcv_accm;  /* Set PPP driver Recv ACCM. */

        Ipcom_ppp_debuginfo  debuginfo;    /* Get PPP debug info. */
        Ipcom_ppp_login      login;        /* Set PPP login info. */
        Ipcom_ppp_auth       auth;         /* Set PPP authenticate info. */
#ifdef IPPPP_USE_PPPMP
        Ip_u32               pppflags;     /* PPP flags for the I/F (ppp_flags are the link) */
        int                  open_links;   /* Number of links in use by ppp multilink */
#endif

#ifdef IPPPP_USE_PPPL2TP
        char                   *pppl2tp_paddr_str; /* IP address of LNS to request tunnel with */
        Ipppp_pppl2tp_drv_link  pppl2tp_drv_link;
#endif
    }
    pppru;
};


#ifdef IP_PORT_VXWORKS
/*
 *===========================================================================
 *                         Ipppp_action_work
 *===========================================================================
 * Work request structure used by the PPP work task in VxWorks.
 * Ipcom_list member must come first.
 */
struct Ipppp_action_work
{
    Ipcom_list list;
    void      *data;
    char       ifname[IP_IFNAMSIZ];
    Ip_u32     ifindex;
    Ip_u32     link_index;
    int        action;
};

int ipppp_example_action_work_default(struct Ipppp_action_work *w);
#endif /* IP_PORT_VXWORKS */


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
*
* ipppp_example_action_cb - handle PPP actions
*
* In order for PPP to function the user must implement this callback function
* used by the PPP module to handle various PPP actions like initialization,
* startup, peer IPv4 address requests, peer authentication, login etc.
*
* Parameters:
* \is
* \i <netif>
* Pointer to Ipcom_netif interface structure define in ipcom_netif.h
* \i <action>
* An action code identifying the basis for calling the callback action routine.
* The following action codes are available:
* \i 'IPPPP_ACTION_INIT'
* The purpose of this callback is to give the PPP system administrator a chance
* to set various PPP, Driver, LCP and/or Authentication initialization
* configuration options for this interface. The callback is only called once
* per interface and immediately after the PPP interface is attached.
* \i 'IPPPP_ACTION_LCP_STARTING'
* Called when LCP is starting. Configure session specific LCP parameters here.
* \i 'IPPPP_ACTION_IPCP_STARTING'
* Called when IPCP is starting.
* This action callback can contain code to override the sysvar configurations
* of local and peer IPv4 address. More precise. the sysvar addresses can be
* overridden by calling ioctl() with the commands SIOCSIFADDR and/or
* SIOCSIFDSTADDR. If the default local IP address is 0 then we want the peer to
* give us an IP address. If the peer address is 0, we refuse to suggest an IP
* address to the peer.
* \i 'IPPPP_ACTION_IPV6CP_STARTING'
* Called when IPV6CP is starting.
* \i 'IPPPP_ACTION_IP_UP'
* Called when IPv4 is up and ready for traffic on this PPP link.
* \i 'IPPPP_ACTION_IP_DOWN'
* Called when IPv4 goes down on this PPP link.
* \i 'IPPPP_ACTION_IPV6_UP'
* Called when IPv6 is up and ready for traffic on this PPP link.
* \i 'IPPPP_ACTION_IPV6_DOWN'
* Called when IPv6 goes down on this PPP link.
* \i 'IPPPP_ACTION_PEER_IDENTIFIER'
* Called when peer sends IPv6 Identifier Configure-Request. See RFC274:p6-8 for
* details. Return -1 if refuse to suggest peer IP identifier, else 0.
* 'data' = pointer to 128-bit IPv6 identifier.
* \i 'IPPPP_ACTION_LOGIN'
* Called when we need to authenticate ourselves (i.e. login) to the peer.
* User code must call ioctl(IP_SIOCXPPPLOGIN) with the interface and link index,
* 'data' as the cookie, user name & password and the function call context when
* ready to login.
* \i <data>
* Action type specific additional data.
* \ie
*
* EXAMPLE
* \cs
* See components/ip_net2-<MAJOR_VER>.<MINOR_VER>/osconfig/vxworks/src/ipnet/ipppp_example.c for
* an example implementation of PPP action callback.
* \ce
*
* RETURNS: 0 success, -1 failure.
*
* ERRNO:
*
*/
IP_PUBLIC int ipppp_example_action_cb
(
    Ipcom_netif *netif,
    int action,
    void *data
);

#ifdef IPPPP_USE_PPPL2TP
IP_GLOBAL int    ipppp_pppl2tp_create(struct Ip_ifreq *ifreq);
IP_GLOBAL int    ipppp_pppl2tp_input(Ip_u32 ifindex, void *payload, Ip_u16 length);
IP_GLOBAL int    ipppp_pppl2tp_output(Ipcom_netif *netif, Ipcom_pkt *pkt);
IP_GLOBAL Ip_fd  ipppp_pppl2tp_pkt_que_open(void);
IP_GLOBAL int    ipppp_pppl2tp_pkt_que_recv(Ipppp_pppl2tp_pkt_que_entry *que_entry, union Ip_sockaddr_union *ipp);
IP_PUBLIC IP_CONST char * ipppp_pppl2tp_errname(Ipppp_pppl2tp_status status);

#ifdef IPPPP_USE_PPPL2TP_LNS
IP_GLOBAL int    ipppp_pppl2tp_if_create_server(Ipl2tp_key *skey);
#endif
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
