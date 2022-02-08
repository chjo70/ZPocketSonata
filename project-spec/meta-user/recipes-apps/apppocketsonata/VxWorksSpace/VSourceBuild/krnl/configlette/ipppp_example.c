/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Example file of PPP action callback.
 *
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#ifdef IP_PORT_VXWORKS

#ifdef IPCOM_USE_CLIB_PROTO
#undef IPCOM_USE_CLIB_PROTO
#endif

#endif 

#ifndef IPCOM_KERNEL
#define IPCOM_KERNEL
#endif
#include "ipppp_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef IP_PORT_VXWORKS

#ifdef INCLUDE_IPCOM_USE_SYSLOGD
#define IPCOM_USE_SYSLOG
#endif

#include <ipcom_err.h>

/*
 * some internal macro mappings - ugly but necessary for Ipcom_netif
 * structure alignment!
 */
#ifdef INCLUDE_IPPPP
#define IPPPP
#endif

#ifdef INCLUDE_IP_SECURITY
#define IPIPSEC2
#endif

#ifdef INCLUDE_IPNET_USE_WLAN
#define IPWLAN
#endif

#include <ipcom_netif.h>
#include <ipcom_syslog.h>
#include <ipcom_clib.h>
#include <ipcom_err.h>
#include "ipppp.h"

#else

#define IPCOM_USE_CLIB_PROTO
#include <ipcom_clib.h>
#include <ipcom_cstyle.h>
#include <ipcom_list.h>
#include <ipcom_netif.h>
#include <ipcom_syslog.h>
#include <ipcom_type.h>

#include "ipppp_h.h"

#endif /* IP_PORT_VXWORKS */

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if (defined(IP_PORT_VXWORKS) && (defined(INCLUDE_IPPPP) || defined(INCLUDE_IPPPPOE))) || !defined(IP_PORT_VXWORKS)

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

#ifdef IP_PORT_VXWORKS

/* typedef to make compiler happy... */
typedef int (*ipppp_action_cb)(struct Ipppp_action_work *w);

/* prototype user-defined action callback routine */
#if PPP_INSTALL_CALLBACK_HOOK == TRUE
IP_EXTERN int PPP_ACTION_CALLBACK_HOOK (struct Ipppp_action_work *w);
#endif

#else

struct Ipppp_action_work
{
    Ipcom_list list;
    char       ifname[IP_IFNAMSIZ];
    Ip_u32     ifindex;
    Ip_u32     link_index;
    int        action;
    void      *data;
};

#endif
/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

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


#ifdef IP_PORT_VXWORKS

Ipcom_once_t ipppp_work_once = {IPCOM_ONCE_STATE_UNINITIALIZED, 0, IP_NULL};
IP_EXTERN Ipcom_mutex  ipppp_work_lock;
IP_EXTERN Ipcom_sem    ipppp_work_sem;
IP_EXTERN Ipcom_list   ipppp_work_queue;


/*
 *===========================================================================
 *                       ipppp_example_action_work
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_STATIC int
ipppp_example_action_work(struct Ipppp_action_work *w)
{
    ipppp_action_cb  ppp_cb;

#if PPP_INSTALL_CALLBACK_HOOK == TRUE
    ppp_cb = (PPP_ACTION_CALLBACK_HOOK == NULL) ?
        ipppp_example_action_work_default : PPP_ACTION_CALLBACK_HOOK;
#else
    ppp_cb = ipppp_example_action_work_default;
#endif

    return ppp_cb(w);
}

#else /* (not vxWorks) */

Ipcom_once_t ipppp_work_once = IPCOM_ONCE_INIT;
Ipcom_mutex  ipppp_work_lock = IPCOM_MUTEX_INVALID;
Ipcom_sem    ipppp_work_sem = IPCOM_SEM_INVALID;
Ipcom_list   ipppp_work_queue;


/*
 *===========================================================================
 *                    ipppp_auth_login_hook
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
#ifdef IPPPP_USE_AUTH
IP_STATIC void
ipppp_auth_login_hook(Ip_err retval, Ipcom_auth_userinfo *userinfo, void *auth_login_cookie)
{
    struct Ip_pppreq pppreq;
    Ipppp_auth_cookie  *auth_cookie = auth_login_cookie;
    int    ret;
    Ip_fd  fd;

    if (auth_login_cookie == IP_NULL)
        return;

    if (ipcom_if_indextoname(auth_cookie->ifindex, pppreq.pppr_name) == IP_NULL)
    {
        IPCOM_LOG1(WARNING, "<if=%d> :: ipppp_auth_login_hook() :: missing interface",
                   auth_cookie->ifindex);
        goto leave;
    }

#ifdef IPCOM_USE_INET
    fd = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
#else
    fd = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
#endif
    if (fd == IP_INVALID_SOCKET)
    {
        IP_PANIC();
        goto leave;
    }

    pppreq.pppru.auth.ifindex      = auth_cookie->ifindex;
    pppreq.pppru.auth.link_index   = auth_cookie->link_index;
    pppreq.pppru.auth.success      = retval == IPCOM_SUCCESS;
    ipcom_memcpy(&pppreq.pppru.auth.userinfo, userinfo, sizeof(Ipcom_auth_userinfo));

    ret = ipcom_socketioctl(fd, IP_SIOCXPPPAUTH, &pppreq);
    if (ret != 0)
    {
        IPCOM_LOG3(WARNING, "<%s> :: ipppp_auth_login_hook() :: ioctl(AUTH) failed : %s(%d)",
                   pppreq.pppr_name, ipcom_strerror(ipcom_errno), ipcom_errno);
    }

    (void)ipcom_socketclose(fd);
 leave:
    ipcom_free(auth_cookie);
}
#endif /* IPPPP_USE_AUTH */


/*
 *===========================================================================
 *                    ipppp_example_action_work
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_STATIC void
ipppp_example_action_work(struct Ipppp_action_work *w)
{
    struct Ip_pppreq pppreq;
    struct Ip_ifreq  ifreq;
    Ip_fd            fd;
    int              ret;
    int              action = w->action;
    void            *data = w->data;

    ipcom_strcpy(ifreq.ifr_name, w->ifname);
    ipcom_strcpy(pppreq.pppr_name, w->ifname);

#ifdef IPCOM_USE_INET
    fd = ipcom_socket(IP_AF_INET, IP_SOCK_DGRAM, 0);
#else
    fd = ipcom_socket(IP_AF_INET6, IP_SOCK_DGRAM, 0);
#endif
    if (fd == IP_INVALID_SOCKET)
    {
        IP_PANIC();
        return;
    }

    switch(action)
    {

        /********************* ACTION INIT ********************/
    case IPPPP_ACTION_INIT:
        IPCOM_LOG1(INFO, "<%s> :: ACTION init", w->ifname);

        /* Get PPP flags. */
        if (ipcom_socketioctl(fd, IP_SIOCXPPPGFLAGS, &pppreq) == IP_SOCKERR)
        {
            IP_PANIC();
            break;
        }

        /****** PPP Example configuration *****/

        /* Set PPP flags. */
        ipcom_strcpy(pppreq.pppr_name, w->ifname);
        if (ipcom_socketioctl(fd, IP_SIOCXPPPSFLAGS, &pppreq) == IP_SOCKERR)
        {
            IP_PANIC();
            break;
        }
        break;


        /********************* LCP STARTING ********************/
    case IPPPP_ACTION_LCP_STARTING:
        IPCOM_LOG1(INFO, "<%s> :: ACTION LCP starting", w->ifname);
        break;


#ifdef IPCOM_USE_INET
        /********************* IPCP STARTING ********************/
    case IPPPP_ACTION_IPCP_STARTING:
        IPCOM_LOG1(INFO, "<%s> :: ACTION IPCP starting", w->ifname);
        /* Example of how to set local address if "ipppp.addr" sysvar is not used:
           {
           struct Ip_sockaddr_in  *sinaddr;
           sinaddr = (struct Ip_sockaddr_in *)&ifreq.ip_ifr_addr;
           (void)ipcom_inet_pton(IP_AF_INET, "12.0.0.0", &sinaddr->sin_addr);
           sinaddr->sin_family = IP_AF_INET;
           sinaddr->sin_len = sizeof(struct Ip_sockaddr_in);
           sinaddr->sin_addr.s_addr = ip_htonl((ip_ntohl(sinaddr->sin_addr.s_addr) + netif->ifindex));
           (void)ipcom_socketioctl(fd, IP_SIOCSIFADDR, &ifreq);
           }
        */
        break;

        /********************* IP UP ********************/
    case IPPPP_ACTION_IP_UP:
        IPCOM_LOG1(DEBUG, "<%s> :: ACTION IP up", w->ifname);
        break;

        /********************* IP DOWN ********************/
    case IPPPP_ACTION_IP_DOWN:
        IPCOM_LOG1(DEBUG, "<%s> :: ACTION IP down", w->ifname);
        break;
#endif /* IPCOM_USE_INET */


#ifdef IPCOM_USE_INET6
        /********************* IPV6 STARTING ********************/
    case IPPPP_ACTION_IPV6CP_STARTING:
        IPCOM_LOG1(INFO, "<%s> :: ACTION IPV6CP starting", w->ifname);
        break;

        /********************* IPV6 UP ********************/
    case IPPPP_ACTION_IPV6_UP:
        IPCOM_LOG1(DEBUG, "<%s> :: ACTION IPV6 up", w->ifname);
        break;

        /********************* IPV6 DOWN ********************/
    case IPPPP_ACTION_IPV6_DOWN:
        IPCOM_LOG1(DEBUG, "<%s> :: ACTION IPV6 down", w->ifname);
        break;

        /********************* IPV6 PEER ID ********************/
    case IPPPP_ACTION_PEER_IDENTIFIER:
        IPCOM_LOG1(DEBUG, "<%s> :: ACTION PEER ID", w->ifname);
        break;
#endif /* IPCOM_USE_INET6 */


        /********************* ACTION LOGIN ********************/
        /* Called when we need to authenticate ourselves (i.e. login) to the peer.
         * User code must call ioctl(IP_SIOCXPPPLOGIN) with the same 'data',
         * username and password when ready to login.
         */
#ifdef IPPPP_USE_AUTH
    case IPPPP_ACTION_LOGIN:
        {
            Ip_size_t password_size = IPCOM_AUTH_PASSWORD_MAX;
            Ip_size_t username_size = IPCOM_AUTH_USERNAME_MAX;

            IPCOM_LOG1(INFO, "<%s> :: ACTION login", w->ifname);

            if (ipcom_sysvar_get("ipppp.username", pppreq.pppru.login.username, &username_size)
                && username_size > 0
                && ipcom_sysvar_get("ipppp.password", pppreq.pppru.login.password, &password_size)
                && password_size > 0)
            {
                pppreq.pppru.login.ifindex      = w->ifindex;
                pppreq.pppru.login.link_index   = w->link_index;
                pppreq.pppru.login.login_cookie = data;

                ret = ipcom_socketioctl(fd, IP_SIOCXPPPLOGIN, &pppreq);
                if (ret != 0)
                {
                    IPCOM_LOG3(WARNING, "<%s> :: ACTION LOGIN :: ioctl(LOGIN) failed : %s(%d)",
                               w->ifname, ipcom_strerror(ipcom_errno), ipcom_errno);
                }
            }
            else
            {
                IPCOM_LOG1(NOTICE, "<%s> :: ACTION LOGIN :: missing ppp 'client' username or password", w->ifname);
            }
        }
        break;

        /********************* ACTION AUTH ********************/
        /* Called when peer needs to be authenticated
         */
    case IPPPP_ACTION_AUTH:
        {
            Ipcom_auth_userinfo   userinfo;
            Ipppp_auth_cookie    *auth_cookie = data;

            IPCOM_LOG1(INFO, "<%s> :: ACTION authenticate", w->ifname);

            switch(auth_cookie->protocol)
            {
            case IPPPP_PROTOCOL_PAP:
                ret = ipcom_auth_ctx_login(auth_cookie->username,
                                           auth_cookie->password,
                                           &userinfo,
                                           ipppp_auth_login_hook,
                                           auth_cookie,
                                           IPCOM_AUTH_LOGIN_IF_PPP,
                                           IP_INVALID_SOCKET);
                break;
#ifdef IPPPP_USE_AUTH_CHAP
            case IPPPP_PROTOCOL_CHAP:
                {
                    Ipcom_auth_chap   chap;

                    /* Validate user using the name and CHAP response, id and challenge. */
                    chap.response       = auth_cookie->chap_response;
                    chap.ident          = auth_cookie->chap_ident;
                    chap.challenge      = auth_cookie->chap_challenge;
                    chap.challenge_size = auth_cookie->chap_challenge_size;

                    ret = ipcom_auth_chap_login(auth_cookie->username, &chap,
                                                &userinfo, ipppp_auth_login_hook, auth_cookie);
                }
                break;
#endif /* IPPPP_USE_AUTH_CHAP */
            default:
                IP_PANIC2();
                ret = IPCOM_ERR_FAILED;
                ipcom_memset(&userinfo, 0, sizeof(userinfo));
                break;
            }

            switch(ret)
            {
            case IPCOM_ERR_PENDING:
                /* The ipppp_auth_login_hook() will be called later. */
                break;
            default:
                /* login ok/fail. */
                pppreq.pppru.auth.ifindex    = w->ifindex;
                pppreq.pppru.auth.link_index = w->link_index;
                pppreq.pppru.auth.success    = ret == IPCOM_SUCCESS;
                ipcom_memcpy(&pppreq.pppru.auth.userinfo, &userinfo, sizeof(Ipcom_auth_userinfo));
                ret = ipcom_socketioctl(fd, IP_SIOCXPPPAUTH, &pppreq);
                if (ret != 0)
                {
                    IPCOM_LOG3(WARNING, "<%s> :: ACTION AUTH :: ioctl(AUTH) failed : %s(%d)",
                               w->ifname, ipcom_strerror(ipcom_errno), ipcom_errno);
                }
                ipcom_free(auth_cookie);
                break;
            }
            break;
        }
#endif /* IPPPP_USE_AUTH */

    default:
        IP_PANIC();
        break;
    }

    (void)ipcom_socketclose(fd);
}

#endif /* IP_PORT_VXWORKS */

/*
 *===========================================================================
 *                       ipppp_work
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_STATIC
IPCOM_PROCESS(ipppp_work)
{
    ipcom_proc_init();

    for (;;)
    {
        struct Ipppp_action_work *work;

        ipcom_sem_wait(ipppp_work_sem);

        ipcom_mutex_lock(ipppp_work_lock);
        if ((work = IPCOM_LIST_FIRST(&ipppp_work_queue)) == IP_NULL)
        {
            ipcom_mutex_unlock(ipppp_work_lock);
            continue;
        }

        ipcom_list_remove(&work->list);
        ipcom_mutex_unlock(ipppp_work_lock);

        ipppp_example_action_work(work);

        ipcom_free(work);
    }

/*     ipcom_proc_exit(); */
}


/*
 *===========================================================================
 *                       ipppp_work_init
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_STATIC Ip_err
ipppp_work_init(void *unused)
{
    IPCOM_UNUSED_ARG(unused);

    ipcom_list_init(&ipppp_work_queue);
    ipcom_mutex_create(&ipppp_work_lock);
    ipcom_sem_create(&ipppp_work_sem, 0);

    return ipcom_proc_create("ipppp_work",
                             (Ipcom_proc_func)ipppp_work,
                             IPCOM_PROC_STACK_DEFAULT,
                             IP_NULL);
}


/*
 *===========================================================================
 *                       ipppp_work_alloc
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_STATIC struct Ipppp_action_work *
ipppp_work_alloc(Ipcom_netif *netif, int action, void *data)
{
    struct Ipppp_action_work *work;

    work = ipcom_malloc(sizeof(*work));
    if (work)
    {
        ipcom_strcpy(work->ifname, netif->name);
        work->ifindex    = netif->ifindex;
        work->link_index = netif->link_index;
        work->action     = action;
        work->data       = data;
    }

    return work;
}


/*
 *===========================================================================
 *                       ipppp_work_schedule
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_STATIC int
ipppp_work_schedule(struct Ipppp_action_work *work)
{
    if (ipcom_once(&ipppp_work_once,
                   ipppp_work_init,
                   IP_NULL)
        != IPCOM_SUCCESS)
    {
        IP_PANIC();
        return -1;
    }


    ipcom_mutex_lock(ipppp_work_lock);
    ipcom_list_insert_last(&ipppp_work_queue, &work->list);
    ipcom_mutex_unlock(ipppp_work_lock);

    ipcom_sem_post(ipppp_work_sem);
    return 0;
}

#endif /* (defined(IP_PORT_VXWORKS) && (defined(INCLUDE_IPPPP) || defined(INCLUDE_IPPPPOE))) || !defined(IP_PORT_VXWORKS) */


/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 * ipppp_example_action_cb - PPP action callback routine
 *
 * In order for PPP to function, this callback function is called by PPP to
 * handle various PPP actions like initialization, startup, peer IPv4 address
 * requests, peer authentication login etc.
 *
 * .IP <netif>
 * Ipcom_netif pointer to the PPP interface.
 * .IP <action>
 * The action type - IPPPP_ACTION_xxx.
 * .IP <data>
 * Action type specific additional data.
 *
 * RETURNS: Depends on the action type.
 *
 * NOMANUAL
 */
IP_PUBLIC int
ipppp_example_action_cb(Ipcom_netif *netif, int action, void *data)
{
#if (defined(IP_PORT_VXWORKS) && (defined(INCLUDE_IPPPP) || defined(INCLUDE_IPPPPOE))) || !defined(IP_PORT_VXWORKS)
    struct Ipppp_action_work *work;

    work = ipppp_work_alloc(netif, action, data);

    return ipppp_work_schedule(work);
#else
    return 0;
#endif
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

