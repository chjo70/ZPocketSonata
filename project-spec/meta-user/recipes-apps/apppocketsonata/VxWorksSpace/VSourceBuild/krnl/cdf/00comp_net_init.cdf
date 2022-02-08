/* 00comp_net_init.cdf - Component and InitGroup configuration file */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07dec16,mca  Break hard dependency between END and IPNET (US85582)
25nov16,mca  created.
*/

Component INCLUDE_NETWORK {
   NAME             Basic network support
   SYNOPSIS         This should always be included for backward compatibility
    _CHILDREN       FOLDER_NETWORK
   REQUIRES         SELECT_NETWORK_STACK \
                    INCLUDE_END
}

/*
 * The INCLUDE_NET_INIT_SKIP component is only used in VxWorks Image
 * project builds, not in the traditional command line BSP build.
 */

Component INCLUDE_NET_INIT_SKIP {
    NAME            Skip network stack initialization
    SYNOPSIS        With this component included, the stack is \
                    present but is not initialized at boot. It may \
                    be initialized later by calling usrNetworkInit().
    INIT_RTN        {                                    \
                        static BOOL networkInit = FALSE; \
                                                         \
                        if (!networkInit)                \
                            {                            \
                            networkInit = TRUE;          \
                            return;                      \
                            }                            \
                    }
    REQUIRES        SELECT_NETWORK_STACK
    _CHILDREN       FOLDER_NETWORK
}

Selection SELECT_NETWORK_STACK {
    NAME            A selection of network stack
    SYNOPSIS        Allows selecting between the IPNET and RTNET stacks.
    COUNT           0-1
    _CHILDREN       FOLDER_NETWORK
    CHILDREN        INCLUDE_IPNET \
                    INCLUDE_RTNET
#if defined(_WRS_CONFIG_IPNET_COREIP)
    DEFAULTS        INCLUDE_IPNET
#elif defined(_WRS_CONFIG_RTNET)
    DEFAULTS        INCLUDE_RTNET
#endif
}

/*
 * Now that the network initialization is split into two pieces,
 * we may need a separate INCLUDE_NET_INIT_SKIP0 for usrNetworkInit0...
 */

InitGroup usrNetworkInit0 {
    SYNOPSIS        Initialize the network subsystem for drivers
    INIT_RTN        usrNetworkInit0 ();
    INIT_ORDER      INCLUDE_NETBUFLIB           \
                    INCLUDE_NETBUFADVLIB        \
                    INCLUDE_NETBUFPOOL          \
                    INCLUDE_LINKBUFPOOL         \
                    INCLUDE_VXMUX_NULLBUFPOOL   \
                    INCLUDE_NET_DAEMON          \
                    INCLUDE_END2_LINKBUFPOOL    \
                    INCLUDE_NET_POOL            \
                    INCLUDE_ROUTE_STORAGE       \
                    usrNetProtoInit             \
                    usrNetMib2Init              \
                    INCLUDE_ROUTE               \
                    INCLUDE_MUX_COMMON          \
                    INCLUDE_MUX                 \
                    INCLUDE_MUX2                \
                    INCLUDE_MUXTK               \
                    INCLUDE_VXMUX_MBLK          \
                    INCLUDE_MUX_OVER_END2       \
                    INCLUDE_MUX2_OVER_END       \
                    INCLUDE_MUXTK_OVER_END      \
                    INCLUDE_MUXTK_OVER_END2     \
                    INCLUDE_MUX_L2              \
                    INCLUDE_END_ETHER_HDR       \
                    INCLUDE_END                 \
                    INCLUDE_END2                \
                    INCLUDE_MUX_IF_FUNC_DBASE
    _INIT_ORDER     usrRoot
#ifdef _WRS_CONFIG_VXBUS_LEGACY
    INIT_AFTER      INCLUDE_USER_PRE_NETWORK_APPL_INIT
#else /* !_WRS_CONFIG_VXBUS_LEGACY */
    INIT_AFTER      usrIosCoreInit
    INIT_BEFORE     INCLUDE_VXBUS
#endif /* _WRS_CONFIG_VXBUS_LEGACY */
}

/* Note, INCLUDE_NET_INIT_SKIP must be first */

InitGroup usrNetworkInit {
    SYNOPSIS        Initialize the reset of the network subsystem
    INIT_RTN        usrNetworkInit ();
    INIT_ORDER      INCLUDE_NET_INIT_SKIP       \
                    INCLUDE_NET_BOOT            \
                    INCLUDE_NETMASK_GET         \
                    INCLUDE_NET_SYSCTL          \
                    usrNetHostInit              \
                    INCLUDE_HOST_TBL_SYSCTL     \
                    INCLUDE_GETADDRINFO_SYSCTL  \
                    INCLUDE_GETNAMEINFO_SYSCTL  \
                    usrNetRemoteInit            \
                    INCLUDE_VXMUX_SLAB          \
                    INCLUDE_VXMUX_CMD_VXSLAB    \
                    INCLUDE_VXMUX_PKT_POOL_MIN  \
                    INCLUDE_END_COMMON          \
                    INCLUDE_IPCOM_USR           \
                    INCLUDE_IPCOM               \
                    INCLUDE_IPNET_SYSCTL        \
                    INCLUDE_NET_BOOT_CONFIG     \
                    INCLUDE_NET_BOOT_IPV6_CFG   \
                    INCLUDE_SM_NET              \
                    usrNetUtilsInit             \
                    usrNetAppInit               \
                    INCLUDE_USE_WAITIF
    _INIT_ORDER     usrRoot
#ifdef _WRS_CONFIG_VXBUS_LEGACY
    INIT_AFTER      usrNetworkInit0 INCLUDE_SMP_INIT
#else /* !_WRS_CONFIG_VXBUS_LEGACY */
    INIT_AFTER      INCLUDE_USER_PRE_NETWORK_APPL_INIT INCLUDE_SMP_INIT
#endif /* _WRS_CONFIG_VXBUS_LEGACY */
    INIT_BEFORE     usrTipcInit
}
