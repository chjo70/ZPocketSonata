/* 02comp_ipnet_radius.cdf - IPNet Radius Components configuration file */

/*
 * Copyright (c) 2006-2007,2009,2014 Wind River Systems, Inc.
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
24jun14,chm  remove INCLUDE_IPCOM_USE_AUTH_RADIUS. (V7SEC-37)
22sep09,tlu  Correct synopsis and remove INCLUDE_IPCOM_USE_AUTH 
		     for INCLUDE_IPCOM_USE_AUTH_RADIUS
22jan07,kch  Renamed radius client configuration macros for ipcom
             authentication (WIND00083711).
08jan07,kch  Removed duplicate ipcom_config.c configlette from 
             INCLUDE_IPCOM_USE_AUTH_RADIUS.
26sep06,kch  Corrected radius dependencies.
23sep06,kch  Created.
*/

Component INCLUDE_IPRADIUS {
    NAME            Radius client
    SYNOPSIS        Radius client
    REQUIRES        INCLUDE_IPRADIUS_CMD
    MODULES         ipradius.o
    CONFIGLETTES    ipradius_config.c
    INCLUDE_WHEN    INCLUDE_IPRADIUS_CMD
    CFG_PARAMS      RADIUS_NAS_IDENTIFIER
}

Component INCLUDE_IPRADIUS_CMD {
    NAME        IPCOM radius client commands
    SYNOPSIS    IPCOM radius client commands
    MODULES     ipradius_cmd_radiusc.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

/******************** Configuration Parameters *****************************/
/* INCLUDE_IPCOM_USE_AUTH_RADIUS configuration parameters */

Parameter IPCOM_AUTH_RADIUS_SERVER_DOMAIN {
    NAME        RADIUS server domain
    SYNOPSIS    RADIUS server domain for IPCOM authentication, IP_AF_INET=2 \
                or IP_AF_INET6=24.
    TYPE        uint
    DEFAULT     2
}

Parameter IPCOM_AUTH_RADIUS_SERVER_IPV4_ADDRESS {
    NAME        RADIUS server IPv4 address
    SYNOPSIS    RADIUS server IPv4 address for IPCOM authentication.
    TYPE        char *
    DEFAULT     "10.1.2.1"
}

Parameter IPCOM_AUTH_RADIUS_SERVER_IPV6_ADDRESS {
    NAME        RADIUS server IPv6 address
    SYNOPSIS    RADIUS server IPv6 address for IPCOM authentication.
    TYPE        char *
    DEFAULT     "3ffe:300::5"
}

Parameter IPCOM_AUTH_RADIUS_SERVER_PORT {
    NAME        RADIUS server port
    SYNOPSIS    RADIUS server port in host endian for IPCOM authentication.
    TYPE        uint
    DEFAULT     1812
}

Parameter IPCOM_AUTH_RADIUS_SERVER_SHARE_SECRET {
    NAME        RADIUS server shared secret
    SYNOPSIS    RADIUS server shared secret for IPCOM authentication.
    TYPE        char *
    DEFAULT     "kallekula123"
}

Parameter IPCOM_AUTH_RADIUS_SERVER_PASSWD_TYPE {
    NAME        RADIUS server password type
    SYNOPSIS    RADIUS server password type (PAP=1, CHAP=2) for IPCOM \
                authentication.
    TYPE        uint
    DEFAULT     1
}

/******************** Configuration Parameters *****************************/

Parameter RADIUS_NAS_IDENTIFIER {
    NAME        RADIUS client identifier
    SYNOPSIS    Identifier for RADIUS client
    TYPE        char *
    DEFAULT     "Wind River example NAS"
}
