/* 00comp_ipnet.cdf - IPNet configuration file */

/*
 * Copyright (c) 2006-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

Selection SELECT_IPNET_ETHERNET_IFCONFIG {
    NAME            IPNet ethernet interface configurations
    SYNOPSIS        IPNet ethernet interface configurations
    COUNT           0-
    CHILDREN        INCLUDE_IPNET_IFCONFIG_1 \
                    INCLUDE_IPNET_IFCONFIG_2 \
                    INCLUDE_IPNET_IFCONFIG_3 \
                    INCLUDE_IPNET_IFCONFIG_4
    DEFAULTS        INCLUDE_IPNET_IFCONFIG_1
}

Component INCLUDE_IPNET_IFCONFIG_1
{
    NAME            Interface #1 configuration
    SYNOPSIS        Interface #1 configuration
    REQUIRES        INCLUDE_IPCOM_USE_ETHERNET INCLUDE_IPNET
    CFG_PARAMS      IFCONFIG_1
}

Component INCLUDE_IPNET_IFCONFIG_2
{
    NAME            Interface #2 configuration
    SYNOPSIS        Interface #2 configuration
    REQUIRES        INCLUDE_IPCOM_USE_ETHERNET INCLUDE_IPNET
    CFG_PARAMS      IFCONFIG_2
}

Component INCLUDE_IPNET_IFCONFIG_3
{
    NAME            Interface #3 configuration
    SYNOPSIS        Interface #3 configuration
    REQUIRES        INCLUDE_IPCOM_USE_ETHERNET INCLUDE_IPNET
    CFG_PARAMS      IFCONFIG_3
}

Component INCLUDE_IPNET_IFCONFIG_4
{
    NAME            Interface #4 configuration
    SYNOPSIS        Interface #4 configuration
    REQUIRES        INCLUDE_IPCOM_USE_ETHERNET INCLUDE_IPNET
    CFG_PARAMS      IFCONFIG_4
}

Component INCLUDE_IPNET_LOOPBACK_CONFIG {
    NAME            IPNet loopback configuration
    SYNOPSIS        IPnet loopback configuration
    REQUIRES        INCLUDE_IPNET INCLUDE_IPNET_USE_LOOPBACK
    CFG_PARAMS      IFCONFIG_LOOPBACK
}

/******************** Configuration Parameters *****************************/
/* INCLUDE_IPNET_ETHERNET_IFCONFIG configuration paramters */
Parameter IFCONFIG_1 {
    NAME        Interface configuration.
    SYNOPSIS    Specifies the interface parameters to be configured when \
                the stack is initialized, as a list of attribute-value strings, \
                for example: "ifname eth0","devname fei0", "gateway driver", \
                "inet 10.1.2.100/24","inet6 3ffe:1:2:3::4/64". \
                The following keywords are recognized. \
                (1) "ifname" - specifies the name of the ethernet interface, \
                e.g. "ifname eth0". If the interface name is missing after \
                "ifname", then the END device name will be used. \
                (2) "devname" - specifies which driver this interface should \
                attach itself, "fei0". \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (3) "inet" - specifies the interface IPv4 address and subnet, \
                e.g. "inet 10.1.2.100/24". Instead of IPv4 address, there also \
                exists a few special syntaxes: "inet driver" means address and \
                mask should be read from the BSP. "inet dhcp" means address \
                and mask should be received from a DHCP server. The gateway \
                might also be received from that server (depends on the DHCP \
                server configuration). "inet rarp" means address and mask \
                should be received from a RARP server. \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (4) "gateway" - specifies the default gateway used for IPv4, \
                e.g. "gateway 10.1.2.1". Only ONE default gateway can be \
                specified. "gateway driver" may be used to take the gateway \
                from the boot parameters. \
                (5) "inet6" - specifies the interface IPv6 address and subnet, \
                e.g. "inet6 3ffe:1:2:3::4/64". The 'tentative' keyword can be \
                inserted before the address if the stack should do duplicate \
                address detection on the address before assigning it to the \
                interface, e.g. "tentative 3ffe:1:2:3::4/64". \
                (6) "gateway6" - specifies the default gateway used for IPv6. \
                Only ONE default gateway can be specified.
    TYPE        char *
    DEFAULT     "ifname","devname driver","inet driver", "gateway driver"
}

Parameter IFCONFIG_2 {
    NAME        Interface configuration.
    SYNOPSIS    Specifies the interface parameters to be configured when \
                the stack is initialized, as a list of attribute-value strings, \
                for example: "ifname eth0","devname fei0", "gateway driver", \
                "inet 10.1.2.100/24","inet6 3ffe:1:2:3::4/64". \
                The following keywords are recognized. \
                (1) "ifname" - specifies the name of the ethernet interface, \
                e.g. "ifname eth0". If the interface name is missing after \
                "ifname", then the END device name will be used. \
                (2) "devname" - specifies which driver this interface should \
                attach itself, "fei0". \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (3) "inet" - specifies the interface IPv4 address and subnet, \
                e.g. "inet 10.1.2.100/24". Instead of IPv4 address, there also \
                exists a few special syntaxes: "inet driver" means address and \
                mask should be read from the BSP. "inet dhcp" means address \
                and mask should be received from a DHCP server. The gateway \
                might also be received from that server (depends on the DHCP \
                server configuration). "inet rarp" means address and mask \
                should be received from a RARP server. \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (4) "gateway" - specifies the default gateway used for IPv4, \
                e.g. "gateway 10.1.2.1". Only ONE default gateway can be \
                specified. "gateway driver" may be used to take the gateway \
                from the boot parameters. \
                (5) "inet6" - specifies the interface IPv6 address and subnet, \
                e.g. "inet6 3ffe:1:2:3::4/64". The 'tentative' keyword can be \
                inserted before the address if the stack should do duplicate \
                address detection on the address before assigning it to the \
                interface, e.g. "tentative 3ffe:1:2:3::4/64". \
                (6) "gateway6" - specifies the default gateway used for IPv6. \
                Only ONE default gateway can be specified.
    TYPE        char *
    DEFAULT     NULL
}

Parameter IFCONFIG_3 {
    NAME        Interface configuration.
    SYNOPSIS    Specifies the interface parameters to be configured when \
                the stack is initialized, as a list of attribute-value strings, \
                for example: "ifname eth0","devname fei0", "gateway driver", \
                "inet 10.1.2.100/24","inet6 3ffe:1:2:3::4/64". \
                The following keywords are recognized. \
                (1) "ifname" - specifies the name of the ethernet interface, \
                e.g. "ifname eth0". If the interface name is missing after \
                "ifname", then the END device name will be used. \
                (2) "devname" - specifies which driver this interface should \
                attach itself, "fei0". \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (3) "inet" - specifies the interface IPv4 address and subnet, \
                e.g. "inet 10.1.2.100/24". Instead of IPv4 address, there also \
                exists a few special syntaxes: "inet driver" means address and \
                mask should be read from the BSP. "inet dhcp" means address \
                and mask should be received from a DHCP server. The gateway \
                might also be received from that server (depends on the DHCP \
                server configuration). "inet rarp" means address and mask \
                should be received from a RARP server. \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (4) "gateway" - specifies the default gateway used for IPv4, \
                e.g. "gateway 10.1.2.1". Only ONE default gateway can be \
                specified. "gateway driver" may be used to take the gateway \
                from the boot parameters. \
                (5) "inet6" - specifies the interface IPv6 address and subnet, \
                e.g. "inet6 3ffe:1:2:3::4/64". The 'tentative' keyword can be \
                inserted before the address if the stack should do duplicate \
                address detection on the address before assigning it to the \
                interface, e.g. "tentative 3ffe:1:2:3::4/64". \
                (6) "gateway6" - specifies the default gateway used for IPv6. \
                Only ONE default gateway can be specified.
    TYPE        char *
    DEFAULT     NULL
}

Parameter IFCONFIG_4 {
    NAME        Interface configuration.
    SYNOPSIS    Specifies the interface parameters to be configured when \
                the stack is initialized, as a list of attribute-value strings, \
                for example: "ifname eth0","devname fei0", "gateway driver", \
                "inet 10.1.2.100/24","inet6 3ffe:1:2:3::4/64". \
                The following keywords are recognized. \
                (1) "ifname" - specifies the name of the ethernet interface, \
                e.g. "ifname eth0". If the interface name is missing after \
                "ifname", then the END device name will be used. \
                (2) "devname" - specifies which driver this interface should \
                attach itself, "fei0". \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (3) "inet" - specifies the interface IPv4 address and subnet, \
                e.g. "inet 10.1.2.100/24". Instead of IPv4 address, there also \
                exists a few special syntaxes: "inet driver" means address and \
                mask should be read from the BSP. "inet dhcp" means address \
                and mask should be received from a DHCP server. The gateway \
                might also be received from that server (depends on the DHCP \
                server configuration). "inet rarp" means address and mask \
                should be received from a RARP server. \
                The default is set to "driver" so that device name is \
                retrieved from device boot parameters. \
                (4) "gateway" - specifies the default gateway used for IPv4, \
                e.g. "gateway 10.1.2.1". Only ONE default gateway can be \
                specified. "gateway driver" may be used to take the gateway \
                from the boot parameters. \
                (5) "inet6" - specifies the interface IPv6 address and subnet, \
                e.g. "inet6 3ffe:1:2:3::4/64". The 'tentative' keyword can be \
                inserted before the address if the stack should do duplicate \
                address detection on the address before assigning it to the \
                interface, e.g. "tentative 3ffe:1:2:3::4/64". \
                (6) "gateway6" - specifies the default gateway used for IPv6. \
                Only ONE default gateway can be specified.
    TYPE        char *
    DEFAULT     NULL
}

/* INCLUDE_IPNET_LOOPBACK configuration parameters */
Parameter IFCONFIG_LOOPBACK {
    NAME        Loopback interface configuration
    SYNOPSIS    Specifies the loopback interface parameters to be configured \
                when the stack is initialized, e.g. "ifname lo0",\
                "inet 127.0.0.1/32","inet6 ::1/128","inet6 FF01::1/16". \
                The following keywords are recognized. \
                (1) "ifname" - specifies the name of loopback interface, \
                e.g. "ifname eth0" \
                (2) "inet" - specifies loopback IPv4 address and subnet, \
                e.g. "inet 127.0.0.1/32". \
                (3) "inet6" - specifies loopback IPv6 address and subnet, \
                e.g. "inet6 ::1/128".
    TYPE        char *
    DEFAULT     "ifname lo0","inet 127.0.0.1/32","inet6 ::1/128","inet6 FF01::1/16"
}
