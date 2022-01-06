/* 00comp_ipnet_shell_cmd.cdf - IPCom Shell Commands configuration file */

/*
 * Copyright (c) 2006-2007, 2014, 2017 Wind River Systems, Inc.
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
17jan17,jbm  NAME and SYNOPSIS editorial clean up
15nov14,dlk  Added IPCOM_NETSMP_CMD.
18feb14,zan  move INCLUDE_IPNSLOOKUP_CMD to 02comp_ipnet_appl_dnsc.cdf (DNSC layer)
22nov10,xhs  support arp command for iplite
15sep10,xhs  support IPLITE
09aug10,kxr  Added INCLUDE_IPSVCONFIG_CMD for NAP VLAN stacking cmds
25jun10,rjq  Added INCLUDE_IPNTP for NTP
23sep09,tlu  Added INCLUDE_IPVCONFIG_CMD for VLAN stacking cmds
07sep07,rme  Replaced SELECTION_IPCOM_FS with SELECT_IPCOM_FS in INCLUDE_IPCOM_SYSLOGD_USE_LOG_FILE
27jun07,mcarlste Added INCLUDE_IPCOM_USE_MIB2_CMD
27feb07,kch  Added INCLUDE_IPCOM_USE_TIME_CMD (WIND00089286).
29jan07,tkf  Corrected MODULES list of INCLUDE_IPCOM_SYSLOGD_CMD and
             INCLUDE_IPIFCONFIG_CMD
21jan07,kch  Corrected INCLUDE_IPSNTP_CMD dependencies.
19jan07,tkf  Added INCLUDE_IPCOM_SYSLOGD_USE_LOG_FILE (WIND00085813).
06dec06,kch  Moved INCLUDE_IPSYSCTL_CMD from FOLDER_IPCOM_SHELL_CMD to
             FOLDER_NET_SYSCTL.
310ct06,kch  Corrected typo for ipecho components.
23sep06,kch  Fixed IPCOM shell commands description. Relocate IPPPP,
             IPRADIUS, IPRIP, IPRIPNG and IPMCAST components to different
             folder.
22sep06,tkf  Cleaned up component names.
21sep06,kch  Moved INCLUDE_IPFIREWALL_CMD to 00comp_ipnet_firewall.cdf.
             Also moved INCLUDE_IPQOS_CMD to 00comp_ipnet_qos.cdf.
18sep06,kch  Added INCLUDE_IPPPP_CMD.
01sep06,tlu  Rename IPRIPNG to RIPNG for the backward compatiblity
28aug06,kch  Added INCLUDE_IPSYSCTL_CMD.
12aug06,kch  Corrected INCLUDE_IPSNTP_CMD dependency.
10aug06,kch  Added INCLUDE_IPCOM_SYSLOGD_CMD and INCLUDE_IPCOM_SYSVAR_CMD.
03aug06,kch  Renamed INCLUDE_Xxx_CMD to INCLUDE_IPXxx_CMD for consistency.
28jul06,tlu  Added INCLUDE_IPRIPNG_CTRL_CMD
22jul06,kch  Added INCLUDE_IPRIP_CTRL_CMD.
17jul06,kch  Renamed IPNET_ROUTE_CMD to INCLUDE_ROUTE_CMD and
             IPNET_SCALETEST_CMD to INCLUDE_IPNET_SCALETEST_CMD. Also
             changed to use the shell command executable name as the
             displayed component name.
29jun06,kch  Fixed INCLUDE_MCAST_PROXY_CMD dependencies.
22may06,kch  created.
*/

Component INCLUDE_IPARP_CMD {
    NAME        IPCOM arp commands
    SYNOPSIS    This component includes the IPCOM Address Resolution Protocol \
                (ARP) commands.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_arp.o
    LINK_SYMS   iplite_cmd_arp
#else
    MODULES     ipnet_cmd_arp.o
    LINK_SYMS   ipnet_cmd_arp
#endif
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPCOM_USE_INET
}

Component INCLUDE_IPCOM_SHELL_CMD {
    NAME        IPCOM shell command interface
    SYNOPSIS    This component includes the IPCOM shell command interface.
    MODULES     ipcom_cmd_shellcmds.o
    REQUIRES    SELECT_IPCOM_SHELL
}

Component INCLUDE_IPCOM_SYSLOGD_CMD {
    NAME        IPCOM syslog commands
    SYNOPSIS    This component includes the IPCOM system logging daemon \
                commands.
    MODULES     ipcom_cmd_syslog.o
    CFG_PARAMS  IPCOM_SYSLOGD_DEFAULT_PRIORITY \
                IPCOM_SYSLOGD_QUEUE_MAX
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPCOM_SYSLOGD_USE_LOG_FILE {
    NAME        IPCOM syslogd log file
    SYNOPSIS    This component includes the IPCOM syslogd log file.
    CFG_PARAMS  IPCOM_SYSLOGD_LOG_FILE
    REQUIRES    INCLUDE_IPCOM_SYSLOGD_CMD \
                SELECT_IPCOM_FS
}

Component INCLUDE_IPCOM_SYSVAR_CMD {
    NAME        IPCOM sysvar commands
    SYNOPSIS    This component includes the IPCOM system variable (sysvar) tool \
                commands.
    MODULES     ipcom_cmd_sysvar.o
    LINK_SYMS   ipcom_cmd_sysvar
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPECHO_CLIENT_CMD {
    NAME        IPCOM echoclient commands
    SYNOPSIS    This component includes the TCP/UDP echo client commands.
    MODULES     ipcom_cmd_echo.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPECHO_SERVER_CMD {
    NAME        IPCOM echoserver commands
    SYNOPSIS    This component includes the Transmission Control Protocol (TCP) \
                and User Datagram Protocol (UDP) echo server commands.
    MODULES     ipcom_cmd_echo.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPFTP_CMD {
    NAME        IPCOM FTP client commands
    SYNOPSIS    This component includes the IPCOM FTP client commands.
    MODULES     ipftpc_cmd_ftp.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPFTPC
}

Component INCLUDE_IPIFCONFIG_CMD {
    NAME        IPCOM ifconfig commands
    SYNOPSIS    This component includes the IPCOM interface configuration \
                (ifconfig) commands.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_ifconfig.o
#else
    MODULES     ipnet_cmd_ifconfig.o
#endif
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_SHELL
}

Component INCLUDE_IPD_CMD {
    NAME        IPCOM ipd commands
    SYNOPSIS    This component includes the IPCOM shell commands for IPD daemon \
                control.
    MODULES     ipcom_cmd_ipd.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPNET_CTRL_CMD {
    NAME        IPCOM ipnet_ctrl commands
    SYNOPSIS    This component includes IPCOM shell commands for the IPNET \
                run-time debugger utility.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_ctrl.o
    LINK_SYMS   iplite_cmd_ctrl
#else
    MODULES     ipnet_cmd_ctrl.o
    LINK_SYMS   ipnet_cmd_ctrl
#endif
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPMEM_DEBUG_CMD {
    NAME        IPCOM mem commands
    SYNOPSIS    This component includes the IPCOM memory debug tool commands.
    MODULES     ipcom_dmalloc.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPNAT_CMD {
    NAME        IPCOM nat commands
    SYNOPSIS    This component includes the IPCOM nat commands to configure \
                Network Address Translation (NAT).
    MODULES     ipnet_cmd_nat.o
    LINK_SYMS   ipnet_cmd_nat
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPNET_USE_NAT SELECT_IPCOM_FS
}

Component INCLUDE_IPNDP_CMD {
    NAME        IPCOM ndp commands
    SYNOPSIS    This component includes the IPCOM ndp commands to configure the \
                Neighbor Discovery Protocol (NDP).
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_ndp.o
    LINK_SYMS   iplite_cmd_ndp
#else
    MODULES     ipnet_cmd_ndp.o
    LINK_SYMS   ipnet_cmd_ndp
#endif
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPCOM_USE_INET6
}

Component INCLUDE_IPNETSTAT_CMD {
    NAME        IPCOM netstat command
    SYNOPSIS    This component includes the IPCOM netstat command to display \
                network statistics and configuration data.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_netstat.o
#else
    MODULES     ipnet_cmd_netstat.o
#endif
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPPING_CMD {
    NAME        IPCOM ping command
    SYNOPSIS    This component includes support for the IPCOM ping command. 
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_ping.o
    LINK_SYMS   iplite_cmd_ping
#else
    MODULES     ipnet_cmd_ping.o
    LINK_SYMS   ipnet_cmd_ping
#endif
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPCOM_USE_INET
}

Component INCLUDE_IPPING6_CMD {
    NAME        IPCOM ping6 command
    SYNOPSIS    This component includes support for the IPCOM ping6 command.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_ping6.o
    LINK_SYMS   iplite_cmd_ping6
#else
    MODULES     ipnet_cmd_ping6.o
    LINK_SYMS   ipnet_cmd_ping6
#endif
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPCOM_USE_INET6
}

Component INCLUDE_IPRADVD_CMD {
    NAME        IPCOM radvd commands
    SYNOPSIS    This component includes support for the IPCOM router advertisement \
                daemon (radvd) configuration utility
    MODULES     ipnet_cmd_radvd.o
    LINK_SYMS   ipnet_cmd_radvd
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPCOM_USE_INET6 \
                INCLUDE_IPRADVD
}

Component INCLUDE_IPROUTE_CMD {
    NAME        IPCOM route commands
    SYNOPSIS    This component includes the IPCOM shell commands for the IPNET \
                route table control.
#ifdef _WRS_CONFIG_COMPONENT_IPLITE
    MODULES     iplite_cmd_route.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPLITE
#else
    MODULES     ipnet_cmd_route.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPNET_USE_ROUTESOCK \
                INCLUDE_IPNET
#endif
}

#ifndef _WRS_CONFIG_COMPONENT_IPLITE
Component INCLUDE_IPIP_CMD {
    NAME        IPCOM ip command
    SYNOPSIS    This component includes the IPCOM shell command for viewing and \
                manipulating IPNET. 
    MODULES     ipnet_cmd_ip.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPNET_USE_NETLINKSOCK \
                INCLUDE_IPNET
}
#endif

Component INCLUDE_IPNET_PCAP_CMD {
    NAME        IPNET pcap control commands
    SYNOPSIS    This component includes the IPNET shell commands for capturing \
                packets on an interface and storing them in a PCAP-compatible \
                format.
    MODULES     ipnet_cmd_pcap.o
    LINK_SYMS   ipnet_cmd_pcap
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPVCONFIG_CMD {
    NAME        IPCOM vconfig commands
    SYNOPSIS    This component includes the IPCOM virtual LAN (VLAN) stacking \
                commands.
    MODULES     ipnet_cmd_vconfig.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPSNTP_CMD {
    NAME        IPCOM SNTP commands
    SYNOPSIS    This component includes the IPCOM Simple Network Time Protocol \
                (SNTP) commands.
    MODULES     ipsntp_cmd_sntp.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPSNTPC_API
}

Component INCLUDE_IPNTP_CMD {
    NAME        IPCOM NTP commands
    SYNOPSIS    This component includes the IPCOM Network Time Protocol (NTP) \
                commands.
    MODULES     ipntp_cmd_ntp.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPNTP
}

Component INCLUDE_IPSOCKPERF_CMD {
    NAME        IPCOM sockperf commands
    SYNOPSIS    This component includes the IPCOM shell commands for the socket \
                performance test tool.
    MODULES     ipcom_cmd_sockperf.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPSOCKTEST_CMD {
    NAME        IPCOM socktest commands
    SYNOPSIS    This component includes the IPCOM socket test tool commands. 
    MODULES     ipcom_cmd_socktest.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPSVCONFIG_CMD {
    NAME        IPCOM svconfig commands
    SYNOPSIS    This component includes the IPCOM virtual LAN (VLAN) stacking \
                configuration commands executed on the NAP VxWorks management \
                OS.
    MODULES     ipnet_cmd_svconfig.o
    LINK_SYMS   ipnet_cmd_svconfig
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_TASK_LIST
}

Component INCLUDE_IPSYSCTL_CMD {
    NAME        IPCOM sysctl commands
    SYNOPSIS    This component includes the IPCOM shell commands for the \
                IPNET sysctl configuration.
    MODULES     ipnet_cmd_sysctl.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_SHELL
    _CHILDREN   FOLDER_NET_SYSCTL
}

Component INCLUDE_IPTRACE_ROUTE_CMD {
    NAME        IPCOM traceroute commands
    SYNOPSIS    This component includes the IPCOM traceroute commands.
    MODULES     ipcom_cmd_tracert.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPTCP_TEST_CMD {
    NAME        IPCOM ttcp commands
    SYNOPSIS    This component includes the IPCOM shell commands for the TCP \
                standard performance test tool.
    MODULES     ipcom_cmd_ttcp.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPTFTP_CLIENT_CMD {
    NAME        IPCOM tftp commands
    SYNOPSIS    This component includes the IPCOM Trivial File Transfer Protocol \
                (TFTP) commands.
    MODULES     iptftpc_cmd_tftp.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD INCLUDE_IPTFTPC
}

Component INCLUDE_IPCOM_USE_TIME_CMD {
    NAME        IPCOM time commands
    SYNOPSIS    This component includes the IPCOM time commands to show and set \
                the current date and time.
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_ERRNOS_CMD {
    NAME        Dump generic errno strings.
    SYNOPSIS    This component includes support to show errno strings that \
                correspond to UNIX-style generic errnos. 
    MODULES     ipcom_cmd_errno.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPVERSION_CMD {
    NAME        IPCOM version commands
    SYNOPSIS    This component includes IPCOM shell commands for the IPNet \
                product version.
    MODULES     ipcom_cmd_version.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

Component INCLUDE_IPCOM_USE_MIB2_CMD {
    NAME        IPCOM mib2 command
    SYNOPSIS    This component includes the IPCOM shell command for testing \
                IPNET mib2 instrumentation.
    MODULES     ipcom_cmd_mib2.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
    LINK_SYMS   ipcom_mib2_clear
}

Component INCLUDE_IPCOM_CPU_CMD {
    NAME        IPCOM cpu command
    SYNOPSIS    This component includes the IPCOM shell command to set and \
                get CPU affinity.
    MODULES     ipcom_cmd_cpu.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
    LINK_SYMS   ipcom_cmd_cpu
}

Component INCLUDE_NETSMP_CMD {
    NAME        IPCOM netsmp command
    SYNOPSIS    This component includes a shell command to show multi-threaded \
                network stack and SMP-related information.
    MODULES     ipcom_cmd_netsmp.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
    LINK_SYMS   ipcom_cmd_netsmp
}

Component INCLUDE_USER_CMD {
    NAME        IPCOM auth commands
    SYNOPSIS    This component includes IPCOM auth commands for the user \
                administrator.
    MODULES     ipcom_cmd_user.o
    REQUIRES    INCLUDE_IPCOM_SHELL_CMD
}

/******************** Configuration Parameters *****************************/

/* INCLUDE_IPCOM_SYSLOGD_CMD configuration parameters */
Parameter IPCOM_SYSLOGD_DEFAULT_PRIORITY {
    NAME        Default priority for system logging
    SYNOPSIS    Choose one of the following: IPCOM_LOG_EMERG, \
                IPCOM_LOG_CRIT, IPCOM_LOG_ERR, IPCOM_LOG_WARNING, \
                IPCOM_LOG_NOTICE, IPCOM_LOG_INFO, \
                IPCOM_LOG_DEBUG, IPCOM_LOG_DEBUG2
    TYPE        int
    DEFAULT     IPCOM_LOG_ERR
}

Parameter IPCOM_SYSLOGD_QUEUE_MAX {
    NAME        Maximum queue depth for ipcom_syslog()
    SYNOPSIS    This parameter specifies the maximum queue depth for the \
                ipcom_syslog() logging facility
    TYPE        int
    DEFAULT     256
}

Parameter IPCOM_SYSLOGD_LOG_FILE {
    NAME        Log file for IPCOM system logging.
    SYNOPSIS    This parameter specifies a log file for IPCOM system logging. \
                To disable logging, set the value to IP_NULL.
    TYPE        string
    DEFAULT     IPCOM_FILE_ROOT"syslog"
}
