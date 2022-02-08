/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01a,30nov06,kch  Created.
*/

#ifndef __INCppp_varh
#define __INCppp_varh

/* includes */
#include "net/if.h"
#include "ipnet/ipioctl.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The following must not be changed unless equivalent changes are made to
 * IPCOM_AUTH_USERNAME_MAX and IPCOM_AUTH_PASSWORD_MAX as well.
 */ 
#define PPP_AUTH_USERNAME_MAX   32  /* Max user name length. */
#define PPP_AUTH_PASSWORD_MAX   32  /* Max user password length. */

/*
 * IO control commands specific to the PPP protocol.
 */

/* Driver PPP ioctls: */

/* ppp_drvconf; Get PPP driver config (default). */
#define SIOCXPPPGDRVCONF      VX_IOWR(PPP, 1, R, struct pppreq)

/* ppp_drvconf; Get PPP driver info (current). */
#define SIOCXPPPGDRVINFO      VX_IOWR(PPP, 2, R, struct pppreq)

/* u_int32_t; Set PPP driver baudrate. */
#define SIOCXPPPSDRVBAUDRATE  VX_IOWR(PPP, 3, W, struct pppreq)

/* -; Make driver signal up (test ioctl) */
#define SIOCXPPPSDRVUP        VX_IOWR(PPP, 4, R, struct pppreq)

/* -; Make driver signal down (test ioctl) */
#define SIOCXPPPSDRVDOWN      VX_IOWR(PPP, 5, R, struct pppreq)

/* int; Enable wincompat mode */
#define SIOCXPPPSDRVWINCOMPAT VX_IOWR(PPP, 6, R, struct pppreq)

/* Link layer PPP ioctls: */
/* u_int32_t; Get PPP main flags (see PPP_FLAG_xxx) */
#define SIOCXPPPGFLAGS    VX_IOWR(PPP, 10, R, struct pppreq)

/* u_int32_t; Set PPP main flags (in ipcom_netif.h) */
#define SIOCXPPPSFLAGS    VX_IOWR(PPP, 11, W, struct pppreq)

/* ppp_conf; Get PPP main config. */
#define SIOCXPPPGCONF     VX_IOWR(PPP, 12, R, struct pppreq)

/* ppp_conf; Set PPP main config. */
#define SIOCXPPPSCONF     VX_IOWR(PPP, 13, W, struct pppreq)

/* char [AUTH_USERNAME_MAX]; Get local user. */
#define SIOCXPPPGUSER     VX_IOWR(PPP, 14, R, struct pppreq)

/* char [AUTH_USERNAME_MAX]; Set local user. */ 
#define SIOCXPPPSUSER     VX_IOWR(PPP, 15, W, struct pppreq)

/* char [PPP_AUTH_PASSWORD_MAX]; Get local password. */ 
#define SIOCXPPPGPASSWD   VX_IOWR(PPP, 16, R, struct pppreq)

/* char [PPP_AUTH_PASSWORD_MAX]; Set local password. */
#define SIOCXPPPSPASSWD   VX_IOWR(PPP, 17, W, struct pppreq)

/* char [PPP_AUTH_USERNAME_MAX]; Get peer user. */
#define SIOCXPPPGPEERUSER VX_IOWR(PPP, 18, R, struct pppreq)

/* if_name[IFNAMSIZ]; Set pppoe Ethernet interface */
#define SIOCXPPPSETIF     VX_IOWR(PPP, 20, W, struct pppreq)

/* ppp_debuginfo; Get PPP debug info. */
#define SIOCXPPPGDINFO    VX_IOWR(PPP, 22, R, struct pppreq)


/*
 * PPP flags used with SIOCXPPP[G|S]FLAGS ioctl().
 */

/* Disable Address/Control compression in both directions (snd/rcv). */
#define PPP_FLAG_NOACCOMP      0x00000001

/* Do not send or ack ACCM confreq. */
#define PPP_FLAG_NOACCM        0x00000002

/* Require the peer to authenticate itself before allowing snd/rcv NCP. */
#define PPP_FLAG_AUTH          0x00000004

/* Do not require the peer to authenticate itself, i.e. do not ask for 
 * authentication. 
 */
#define PPP_FLAG_NOAUTH        0x00000008

/* Do not agree to authenticate using PAP. */
#define PPP_FLAG_REFUSE_PAP    0x00000010

/* Do not agree to authenticate using MD5 CHAP. */
#define PPP_FLAG_REFUSE_CHAP   0x00000020


/* Initialization action is called directly after the PPP/PPPoE interface has
 * been attached, i.e. directly after ipcom_if_attach() has been called.
 * The init action is a good place to configure the interface with static
 * interface configuration like LCP, AUTH, IPCP and/or IPV6CP etc.
 * Note: The init action has replaced the example action callback function
 *       in previous releases.
 */
#define PPP_ACTION_INIT              1

/* Called when LCP is starting. Configure LCP here.
 */
#define PPP_ACTION_LCP_STARTING      2


/* Called when IPCP is starting.
 * Use this callback to set desired local IPv4 address.
 * The default local IP address is 0, which means we want the peer to suggest
 * an IP address for us.
 */
#define PPP_ACTION_IPCP_STARTING     3

/* Called when IPV6CP is starting.
 * Use this callback to set desired peer IPv6 address.
 * The default peer IP address is 0, which means we will refuse to suggest
 * an IP address for the peer.
 */
#define PPP_ACTION_IPV6CP_STARTING   4


/* IPv4 / IPv6 up/down actions:
 * Enter code which must be run when PPP comes up/down here.
 */
#define PPP_ACTION_IP_UP             5
#define PPP_ACTION_IP_DOWN           6
#define PPP_ACTION_IPV6_UP           7
#define PPP_ACTION_IPV6_DOWN         8


/* 
 * Called when peer sends IPv6 Identifier Configure-Request.
 * See RFC274:p6-8 for details.
 * Return -1 if refuse to suggest peer IP identifier, else 0.
 * 'data' = pointer to 128-bit IPv6 identifier.
 */
#define PPP_ACTION_PEER_IDENTIFIER   9

/* 
 * Called when we need to authenticate ourselves (i.e. login) to the peer.
 * User code must call ipppp_login() with the same 'data',
 * user name and password when ready to login.
 */
#define PPP_ACTION_LOGIN             10


/*
 * ioctl structure for SIOCXPPP[G|S]CONF options.
 */
typedef struct ppp_conf_struct
{
    u_int16_t  restart;    /* Retransmission timeout in seconds. Default 3 */

    /* Max # ConfNak returned before sending ConfRej. Default 10 */
    u_int8_t   max_failure;   

    u_int8_t   max_configure;  /* Max # ConfReq retransmissions. Default 10 */
    u_int8_t   max_terminate;  /* Max # TermReq retransmissions. Default 2 */

    /* Max # auth retransmissions before link terminate. Default 3 */
    u_int8_t   max_authreq;
    u_int8_t      pad[2];
} ppp_conf;


/*
 * ioctl structure for SIOCXPPPGDRVCONF option.
 */
typedef struct ppp_drvconf_struct
{
    u_int32_t  drv_flags;     /* PPP driver flags. */
    u_int32_t  baudrate;      /* Baudrate. */

    u_int32_t  rcv_accm;      /* Recv asyncmap. Default 0xffffffff */
    u_int32_t  snd_accm;      /* Send asyncmap. Default 0xffffffff */
    u_int16_t  mru;           /* Maximum Receive Unit. Default 1500. */
    u_int16_t  mtu;           /* Maximum Transmit Unit. Default 1500. */
} ppp_drvconf;


/* 
 * PPP driver flags (drv_flags): 
 */

/* No initial/trailing PPP flag (0x7e). */
#define DRVPPP_FLAG_NOFLAG      0x00000001

/* Do not byte-escape output/input packets. */
#define DRVPPP_FLAG_NOESCAPE    0x00000002

/* Do not input-check or add output FCS. */
#define DRVPPP_FLAG_NOFCS       0x00000004

/* Do not snd/rcv addr(0xff) ctrl(0x03). */
#define DRVPPP_FLAG_NOACFC      0x00000008


/*
 * ioctl structure for SIOCXPPPGDEBUGINFO option.
 */
typedef struct ppp_debuginfo_struct
{
    u_int32_t  link_flags;  /* See ipnet_netif.h */
    u_int32_t  pppoe_eth_ifindex;
    u_int8_t   link_state;
    u_int8_t   lcp_state;
    u_int8_t   ipcp_state;
    u_int8_t   ipv6cp_state;
} ppp_debuginfo;


/*
 * Interface request structure used for PPP ioctl's.  All interface
 * ioctl's must have parameter definitions which begin with ifr_name and
 * link_index. The remainder may be option specific.
 */
struct pppreq
{
    char    pppr_name[IFNAMSIZ];       /* if name, e.g. "ppp0" */
    int     link_index;   /* link_index, currently unused (for MPPP) */

    union
    {
        u_int32_t  ppp_flags;    /* Get/Set PPP flags. */
        ppp_conf   pppconf;      /* Get/Set PPP protocol configuration. */
        char username[PPP_AUTH_USERNAME_MAX];
        char password[PPP_AUTH_PASSWORD_MAX];
        char if_name[IFNAMSIZ];
        ppp_drvconf  drvconf;       /* Get PPP driver configuration. */
        u_int32_t    drv_baudrate;  /* Set PPP driver baudrate. */
        int          drv_wincompat; /* Windows compat mode */
        ppp_debuginfo  debuginfo;    /* Get PPP debug info. */
    } pppru;
};

#ifdef __cplusplus
}
#endif

#endif /* __INCppp_varh */
