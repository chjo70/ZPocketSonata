/* wvNetDLib.h - header file for WindView WindNet IPv6/IPv4 Dual stack events */

/* Copyright 2003,2004,2005,2008,2010, 2012, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12apr16,gxu  VSB build fail with minimal VSB and IPC feature
17feb14,jsh  Fix SYSTEMVIEWER dependency
09jan12,h_x  Move extern "C" after last header file include.
30dec10,vhe  Moved pWvNetEvtMap to other file. (CQ:WIND00237112)
17jul08,tcr  add eventpoint support
20jan05,sar  Removal of divert, dummynet and fw code.
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
             /main/vdt/base6_itn5_networking-int/2)
25feb04,syy  Change wvNetDConfigure() return value to int
23jan04,syy  Reduce the event ID span
08jan04,syy  Move the index of files to become "0" based.
15dec03,syy  Added some more def's for INFO subtype.
08dec03,syy  Networking WindView instrumentation merge
10nov03,rlm  2nd pass of include update for header re-org.
04sep03,tar  windview instrumentation codereview changes
06aug03,tar  written
*/

#ifndef __INCwvNetDLibh
#define __INCwvNetDLibh

#ifdef _WRS_CONFIG_SYSTEMVIEWER
#include "private/eventP.h"        /* Macros for testing WindView status. */
#endif

#include <private/wvNetDEventP.h>  /* Macros to generate networking events. */

#ifdef __cplusplus
extern "C" {
#endif

IMPORT UCHAR wvNetDLevel;
IMPORT UCHAR wvNetDFilterId;

#define WV_NET_DUAL_ID 	0x2     /*  
                                 * Arbitrary 2-bit prefix for 
                                 * WindNet IPv6/IPv4 Dual stack events.
                                 */

/* 
 * Class definitions 
 */

#define WV_NETD_IP4_DATAPATH_CLASS 0x00000008 /* IPv4 Data Path Events */
#define WV_NETD_IP6_DATAPATH_CLASS 0x00000010 /* IPv6 Data Path Events */
#define WV_NETD_IP4_CTRLPATH_CLASS 0x00000018 /* IPv4 Control Path Events */
#define WV_NETD_IP6_CTRLPATH_CLASS 0x00000020 /* IPv6 Control Path Events */

#define NETD_IP4_DATAPATH_EVENT WV_NETD_IP4_DATAPATH_CLASS
#define NETD_IP6_DATAPATH_EVENT WV_NETD_IP6_DATAPATH_CLASS
#define NETD_IP4_CTRLPATH_EVENT WV_NETD_IP4_CTRLPATH_CLASS
#define NETD_IP6_CTRLPATH_EVENT WV_NETD_IP6_CTRLPATH_CLASS 

/* 
 * The WV_NETD_ADDR_FILTER_TEST and WV_NETD_PORT_FILTER_TEST macros will check 
 * the given data against predefined address or port numbers by calling the
 * appropriate routine. Each macro is only valid within a test conditional.
 */

#define WV_NETD_ADDR_FILTER_TEST(filterType,targetType,srcAddr,dstAddr) \
    wvNetDAddressFilterTest (filterType, targetType, srcAddr, dstAddr)

#define WV_NETD_PORT_FILTER_TEST(filterType, srcPort, dstPort) \
    wvNetDPortFilterTest (filterType, srcPort, dstPort)

#define WV_NETD_NONE 	0 	/* Placeholder for any unused event fields. */

/* 
 * 4-bit level identifiers for event priority. The user can block
 * all event reporting even if WindView is active and a network class
 * is set by specifying the WV_NETD_NONE constant in a call to the
 * wvNetDConfigure() routine. That "priority" is not used by any events.
 */

#define WV_NETD_FATAL           1
#define WV_NETD_CRITICAL        2
#define WV_NETD_WARNING         3
#define WV_NETD_INFO            4
#define WV_NETD_VERBOSE         5


/*
 * Data transfer status. Represented by a 2-bit field in wvNetDEventInfo.
 * WV_NETD_NONE is used if not applicable.
 */

#define WV_NETD_SEND 		1
#define WV_NETD_RECV 		2

/*
 * Packet filter for event. Represented by a 4-bit field in wvNetDEventInfo.
 * WV_NETD_NONE is used if unfiltered.
 */

#define WV_NETD_SADDR_FILTER 	1	/* Source address comparison */
#define WV_NETD_DADDR_FILTER 	2 	/* Destination address comparison */
#define WV_NETD_SPORT_FILTER 	3 	/* Source port comparison */
#define WV_NETD_DPORT_FILTER 	4 	/* Destination port comparison */
#define WV_NETD_SOCK_FILTER 	5 	/* Socket value comparison */

/* Entity. Represented by an 8-bit field in wvNetDEventInfo. */

#define WV_NETD_ARP             1
#define WV_NETD_ICMP4           2
#define WV_NETD_ICMP6           3
#define WV_NETD_IP4             4
#define WV_NETD_IP6             5
#define WV_NETD_RAWIP           6
#define WV_NETD_ROUTE           7
#define WV_NETD_TCP4            8
#define WV_NETD_TCP6            9
#define WV_NETD_UDP4            10
#define WV_NETD_UDP6            11
#define WV_NETD_IF              12
#define WV_NETD_SOCKET          13
#define WV_NETD_IGMP            14
#define WV_NETD_NETBUF          15
#define WV_NETD_MEMBUF          16
#define WV_NETD_PACKET          17
#define WV_NETD_RAW_SOCKET      18 
#define WV_NETD_IP_REASSEMBLE   19
#define WV_NETD_TCP_REASSMBLE   20
#define WV_NETD_DLINK           21
#define WV_NETD_ND              22

/* Module identifiers. Represented by an 8-bit field in wvNetDEventInfo. */
/* We no longer include the divert, dummynet, ip_fw or ip6_fw modules but have
 * retained these tags for consistency.
 */

#define WV_NETD_UNKNOWN                 0   /* Unknown (default) */

#define WV_NETD_IF_MODULE               1   /* if.c source file */
#define WV_NETD_IF_ETHERSUBR_MODULE     2   /* if_ethersubr.c source file */
#define WV_NETD_IF_FAITH_MODULE         3   /* if_faith.c source file */
#define WV_NETD_IF_LOOP_MODULE          4   /* if_loop.c source file */
#define WV_NETD_IF_MEDIA_MODULE         5   /* if_media.c source file */

#define WV_NETD_IP_ICMP_MODULE          6   /* ip_icmp.c source file */

#define WV_NETD_ICMP6_MODULE            7   /* icmp6.c source file */

#define WV_NETD_IN_MODULE               8    /* in.c source file */
#define WV_NETD_IN_PCB_MODULE           9    /* in_pcb.c source file */
#define WV_NETD_IN_RMX_MODULE           10   /* in_rmx.c source file */
#define WV_NETD_IP_DIVERT_MODULE        11   /* ip_divert.c source file */
#define WV_NETD_IP_DUMMYNET_MODULE      12   /* ip_dummynet.c source file */
#define WV_NETD_IP_ECN_MODULE           13   /* ip_ecn.c source file */
#define WV_NETD_IP_FW_MODULE            14   /* ip_fw.c source file */
#define WV_NETD_IP_INPUT_MODULE         15   /* ip_input.c source file */
#define WV_NETD_IP_OUTPUT_MODULE        16   /* ip_output.c source file */
#define WV_NETD_RAW_IP_MODULE           17   /* raw_ip.c source file */
#define WV_NETD_UIPC_DOMAIN_MODULE      18   /* uipc_domain.c source file */

#define WV_NETD_IP6_INPUT_MODULE        19   /* ip6_input.c source file */
#define WV_NETD_RAW_IP6_MODULE          20   /* raw_ip6.c source file */
#define WV_NETD_ROUTE6_MODULE           21   /* route6.c source file */
#define WV_NETD_DEST6_MODULE            22   /* dest6.c source file */
#define WV_NETD_FRAG6_MODULE            23   /* frag6.c source file */
#define WV_NETD_IN6_MODULE              24   /* in6.c source file */
#define WV_NETD_IN6_CKSUM_MODULE        25   /* in6_cksum.c source file */
#define WV_NETD_IN6_IFATTACH_MODULE     26   /* in6_ifattach.c source file */
#define WV_NETD_IN6_PCB_MODULE          27   /* in6_pcb.c source file */
#define WV_NETD_IN6_PREFIX_MODULE       28   /* in6_prefix.c source file */
#define WV_NETD_IN6_RMX_MODULE          29   /* in6_rmx.c source file */
#define WV_NETD_IN6_SRC_MODULE          30   /* in6_src.c source file */
#define WV_NETD_IP6_FORWARD_MODULE      31   /* ip6_forward.c source file */
#define WV_NETD_IP6_FW_MODULE           32   /* ip6_fw.c source file */
#define WV_NETD_IP6_OUTPUT_MODULE       33   /* ip6_output.c source file */
#define WV_NETD_SCOPE6_MODULE           34   /* scope6.c source file */
#define WV_NETD_RTHDR_MODULE            35   /* rthdr.c source file */
#define WV_NETD_IP6OPT_MODULE           36   /* ip6opt.c source file */

#define WV_NETD_ND6_MODULE              37   /* nd6.c source file */
#define WV_NETD_ND6_NBR_MODULE          38   /* nd6_nbr.c source file */

#define WV_NETD_UDP_USRREQ_MODULE       39   /* udp_usrreq.c source file */

#define WV_NETD_UDP6_OUTPUT_MODULE      40   /* udp6_output.c source file */
#define WV_NETD_UDP6_USRREQ_MODULE      41   /* udp6_usrreq.c source file */

#define WV_NETD_TCP_INPUT_MODULE        42   /* tcp_input.c source file */
#define WV_NETD_TCP_OUTPUT_MODULE       43   /* tcp_output.c source file */
#define WV_NETD_TCP_SUBR_MODULE         44   /* tcp_subr.c source file */
#define WV_NETD_TCP_TIMER_MODULE        45   /* tcp_timer.c source file */
#define WV_NETD_TCP_USRREQ_MODULE       46   /* tcp_usrreq.c source file */

#define WV_NETD_RAW_CB_MODULE           47   /* raw_cb.c source file */
#define WV_NETD_RAW_USRREQ_MODULE       48   /* raw_usrreq.c source file */

#define WV_NETD_IF_ETHER_MODULE         49   /* if_ether.c source file */

#define WV_NETD_IGMP_MODULE             50   /* igmp.c source file */

#define WV_NETD_IP_MROUTE_MODULE        51   /* ip_mroute.c source file */

#define WV_NETD_IP6_MROUTE_MODULE       52   /* ip6_mroute.c source file */

#define WV_NETD_RADIX_MODULE            53   /* radix.c source file */
#define WV_NETD_ROUTE_MODULE            54   /* route.c source file */
#define WV_NETD_RTSOCK_MODULE           55   /* rtsock.c source file */
#define WV_NETD_IPROUTELIB_MODULE       56   /* ipRouteLib.c source file */

#define WV_NETD_IF_SUBR_MODULE          57   /* if_subr.c source file */

#define WV_NETD_UNIXLIB_MODULE          58   /* unixLib.c source file */

#define WV_NETD_SYS_SOCKET_MODULE       59   /* sys_socket.c source file */
#define WV_NETD_UIPC_SOCKET_MODULE      60   /* uipc_socket.c source file */
#define WV_NETD_UIPC_SOCKET2_MODULE     61   /* uipc_socket2.c source file */

#define WV_NETD_BPFDRV_MODULE           62   /* bpfDrv.c source file */
#define WV_NETD_IF_ETHERPMP_MODULE      63   /* if_etherpmp.c source file */
#define WV_NETD_DSI_MODULE              64   /* dsiSockLib.c source file */
#define WV_NETD_UNCOMP_USRREQ_MODULE    65   /* uncomp_usrreq.c source file */

/* Qualifier. Represented by an Intereger type in event log API. */

#define WV_NETD_BADLEN          1
#define WV_NETD_BADSUM          2
#define WV_NETD_BADADDR         3
#define WV_NETD_BADSOCK         4
#define WV_NETD_BADSIZE         5
#define WV_NETD_BADHLEN         6
#define WV_NETD_BADWIDTH        7
#define WV_NETD_BADOPT          8
#define WV_NETD_BADVERS         9
#define WV_NETD_BADMBLK         10
#define WV_NETD_BADLEVEL        11
#define WV_NETD_BADROUTE        12
#define WV_NETD_BADREFCNT       13
#define WV_NETD_BADSYNC         14
#define WV_NETD_NOROUTEKEY      15
#define WV_NETD_NOROUTE         16
#define WV_NETD_NOPCB           17
#define WV_NETD_NOPROTO         18
#define WV_NETD_SHORTMSG        19
#define WV_NETD_BADFLAGS        20
#define WV_NETD_NOMEM           21
#define WV_NETD_NOSOCK          22
#define WV_NETD_BADBUF          23
#define WV_NETD_SEMTKFAILED     24
#define WV_NETD_NOFDREF         25
#define WV_NETD_BADGATEWAY      26
#define WV_NETD_UNREACH         27
#define WV_NETD_BADTYPE         28
#define WV_NETD_BADRULE         29
#define WV_NETD_SHORTBUF        30
#define WV_NETD_NOHDR           31
#define WV_NETD_INVALIDPARENT   32
#define WV_NETD_NOUSRREQS       33
#define WV_NETD_BADARG          34
#define WV_NETD_OUTOFDATA       35
#define WV_NETD_BADCHAIN        36
#define WV_NETD_INVAL           37
#define WV_NETD_RETRANSMITPENDING 38
#define WV_NETD_NOGATEWAY       39
#define WV_NETD_NOBUFS          40
#define WV_NETD_BADOFFSET       41
#define WV_NETD_AFNOSUPPORT     42
#define WV_NETD_ADDRNOTAVAIL    43
#define WV_NETD_ADDRINUSE       44
#define WV_NETD_NXIO            45
#define WV_NETD_OPNOTSUPP       46
#define WV_NETD_NETDOWN         47
#define WV_NETD_HOSTUNREACH     48
#define WV_NETD_NETUNREACH      49
#define WV_NETD_ACCES           50
#define WV_NETD_MSGSIZE         51
#define WV_NETD_NOPROTOOPT      52
#define WV_NETD_PKTLOST         53
#define WV_NETD_NOPORT          54
#define WV_NETD_FULLSOCK        55
#define WV_NETD_RTCLONE         56
#define WV_NETD_RTSEARCHGOOD    57
#define WV_NETD_SEARCHFAILED    58
#define WV_NETD_BADQUERY        59
#define WV_NETD_BADREPORT       60
#define WV_NETD_DUPLICATED      61
#define WV_NETD_OPSFAILED       62
#define WV_NETD_LOCKFAILED      63
#define WV_NETD_UNLOCKFAILED    64
#define WV_NETD_BADMASK         65
#define WV_NETD_ADDFAILED       66

/* Info event subtypes. Represented by an Intereger type in event log API. */
#define WV_NETD_INFO_UP            1
#define WV_NETD_INFO_DOWN          2
#define WV_NETD_INFO_OPEN          3
#define WV_NETD_INFO_CLOSE         4
#define WV_NETD_INFO_SEND          5
#define WV_NETD_INFO_RECEIVE       6
#define WV_NETD_INFO_ALLOC         7
#define WV_NETD_INFO_FREE          8
#define WV_NETD_INFO_CONNECT       9
#define WV_NETD_INFO_DISCONNECT    10
#define WV_NETD_INFO_CREATE        11
#define WV_NETD_INFO_DELETE        12
#define WV_NETD_INFO_DROPPED       13
#define WV_NETD_INFO_RETRANSMIT    14
#define WV_NETD_INFO_TIMEOUT       15
#define WV_NETD_INFO_EXPIRED       16
#define WV_NETD_INFO_UPDATED       17
#define WV_NETD_INFO_QUEUE_FULL    18
#define WV_NETD_INFO_PKT_SEND      19
#define WV_NETD_INFO_PKT_RECV      20
#define WV_NETD_INFO_RESET         21
#define WV_NETD_INFO_WAIT          22
#define WV_NETD_INFO_NODEADD       23
#define WV_NETD_INFO_RTADDED       24
#define WV_NETD_INFO_RTCLONE       25
#define WV_NETD_INFO_RTALLOC       26
    
#define WV_NETD_INFO_CUSTOM_1      27
#define WV_NETD_INFO_CUSTOM_2      28
#define WV_NETD_INFO_CUSTOM_3      29
#define WV_NETD_INFO_CUSTOM_4      30
#define WV_NETD_INFO_CUSTOM_5      31
#define WV_NETD_INFO_CUSTOM_6      32

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern void	wvNetDInit (void);
extern int      wvNetDConfigure (int, int, int);

#else	/* __STDC__ */

extern void	wvNetDInit ();
extern int      wvNetDConfigure (int, int, int);

#endif	/* __STDC__ */

/* 
 * Individual Events. All events contain the integer parameter 
 * wvNetDEventId as their first argument. Additional parameters, 
 * if any, are listed with each event.
 */

/* This is the base of the event range */

#define WV_NETD_BASE_EVENT WV_NETDEVENT_FATAL

/* Fatal Events */

#define WV_NETDEVENT_FATAL           20400

/* Critical Events */

#define WV_NETDEVENT_CRITICAL        20415 

/* Warning Events */

#define	WV_NETDEVENT_WARNING         20430

/* Information Events */

#define WV_NETDEVENT_INFO            20445

/* Verbose Events */

#define WV_NETDEVENT_START           20460
#define WV_NETDEVENT_FINISH          20475

 
/* end of VxWorks WindNet IPv6/IPv4 Dual Stack events */

#ifdef __cplusplus
}
#endif
#endif /* __INCwvNetDLibh */
