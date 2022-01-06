/* 00comp_ipnet_apps_dnsc.cdf - IPNet Applications configuration file */

/*
 * Copyright (c) 2010, 2014, 2018 Wind River Systems, Inc.
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
22Jan18,rjq  Correct SubProject errors. (V7NET-1518)
19nov14,ed   Added the ability to configure DNSC from a file (F2848)
18feb14,zan  move INCLUDE_IPNSLOOKUP_CMD to here
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
*/

#ifdef _WRS_CONFIG_COMPONENT_IPAPPL_DNSC

SubProject DNSC_CFGFILE_EXAMPLE {
    NAME        DNS Client Configuration File Example
    SYNOPSIS    DNS Client Configuration File Example
    DIRECTORY   dnsc_etc
}

Component INCLUDE_IPDNSC {
    NAME            DNS Client
    SYNOPSIS        DNS Client
    MODULES         ipdnsc.o
    REQUIRES        INCLUDE_IPCOM DNSC_CFGFILE_EXAMPLE
    CONFIGLETTES    ipdnsc_config.c
    CFG_PARAMS      DNSC_SERVER_PORT DNSC_TIMEOUT DNSC_RETRIES \
                    DNSC_DOMAIN_NAME DNSC_PRIMARY_NAME_SERVER \
                    DNSC_SECONDARY_NAME_SERVER DNSC_TERTIARY_NAME_SERVER \
                    DNSC_QUATERNARY_NAME_SERVER DNSC_IP4_ZONE \
                    DNSC_IP6_ZONE DNSC_CFGFILE
    _CHILDREN       FOLDER_NET_L5_APPLICATIONS
}

Component INCLUDE_IPNSLOOKUP_CMD {
    NAME        IPCOM nslookup commands
    SYNOPSIS    IPCOM Query Internet name servers interactively.
    MODULES     ipdnsc_cmd_nslookup.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPDNSC
    _CHILDREN   FOLDER_IPCOM_SHELL_CMD
}

/* INCLUDE_IPDNSC configuration parameters */
Parameter DNSC_SERVER_PORT {
    NAME        DNS server listening port
    SYNOPSIS    Specifies the port used by IPDNSC for DNS queries, e.g. "53"
    TYPE        char *
    DEFAULT     "53"
}

Parameter DNSC_TIMEOUT {
    NAME        Timeout in seconds when waiting for responses to DNS queries
    SYNOPSIS    Defines the number of seconds before a retry if the DNS \
                server fails to answer, e.g. "10"
    TYPE        char *
    DEFAULT     "10"
}

Parameter DNSC_RETRIES {
    NAME        Number of retries for DNS queries
    SYNOPSIS    Defines the number of retries on each name server, e.g. "2"
    TYPE        char *
    DEFAULT     "2"
}

Parameter DNSC_DOMAIN_NAME {
    NAME        DNS domain name
    SYNOPSIS    Defines the domain where the local host is located. \
                If this system variable is not defined, no local domain \
                is used and the user must provide fully qualified domain \
                names in address lookups for hosts in the same domain as \
                the local host.
    TYPE        char *
    DEFAULT     "windriver.com"
}

Parameter DNSC_PRIMARY_NAME_SERVER {
    NAME        DNS primary name server
    SYNOPSIS    Defines the address to the primary name server. If this \
                system variable is not defined no primary name server is used.
    TYPE        char *
    DEFAULT     ""
}

Parameter DNSC_SECONDARY_NAME_SERVER {
    NAME        DNS secondary name server
    SYNOPSIS    Defines the address to the secondary name server. If this \
                system variable is not defined no secondary name server is used.
    TYPE        char *
    DEFAULT     ""
}

Parameter DNSC_TERTIARY_NAME_SERVER {
    NAME        DNS tertiary name server
    SYNOPSIS    Defines the address to the tertiary name server. If this \
                system variable is not defined no tertiary name server is used.
    TYPE        char *
    DEFAULT     ""
}

Parameter DNSC_QUATERNARY_NAME_SERVER {
    NAME        DNS quaternary name server
    SYNOPSIS    Defines the address to the quaternary name server. If this \
                system variable is not defined no quaternary name server is used.
    TYPE        char *
    DEFAULT     ""
}

Parameter DNSC_IP4_ZONE {
    NAME        Zone for IPv4 address to name lookups
    SYNOPSIS    Defines the zone to use for address to name lookups of IPv4 \
                addresses.
    TYPE        char *
    DEFAULT     "in-addr.arpa"
}

Parameter DNSC_IP6_ZONE {
    NAME        Zone for IPv6 address to name lookups
    SYNOPSIS    Defines the zone to use for address to name lookups of IPv6 \
                addresses. Set to "ip6.int" to support RFC1886 or to \
                "ip6.arpa" to support RC3152.
    TYPE        char *
    DEFAULT     "ip6.int"
}

Parameter DNSC_CFGFILE {
    NAME        DNS Client Library Configuratrion File
    SYNOPSIS    The full pathname to a target resident file containing DNS Client \
                configuration parameters to be processed during system boot or an \
                empty string to disable this capability.
    TYPE        char *
    DEFAULT     ""
}

#endif
