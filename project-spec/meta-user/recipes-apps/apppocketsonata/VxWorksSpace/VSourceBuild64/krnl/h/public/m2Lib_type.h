/* m2Lib_type.h - VxWorks MIB-II type define */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may14,rjq   Created. (V7NET-105)
*/

#ifndef __INCm2LibTypeh
#define __INCm2LibTypeh


#include <cfgDefs.h>
#include <sys/socket.h>        /* needed by sockaddr usage in if.h */
#include <avlUintLib.h>

#ifdef _WRS_KERNEL /* Clairnet 01h */
#ifdef INET6
#include <netinet/in.h>
#endif    /* INET6 */
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char      Mib_u8;

#ifdef _WRS_CONFIG_LP64
typedef int                Mib_s32;
typedef unsigned int       Mib_u32;
#else
typedef long               Mib_s32;
typedef unsigned long      Mib_u32;
#endif


typedef Mib_u8     Mib2_OctetString;
typedef Mib_s32    Mib2_Integer, Mib2_Integer32;
typedef Mib_u32    Mib2_Unsigned, Mib2_Unsigned32;
typedef Mib_u32    Mib2_Counter, Mib2_Counter32;
typedef Mib_u32    Mib2_Gauge, Mib2_Gauge32;
typedef Mib_u32    Mib2_TimeTicks;
typedef Mib_s32    Mib2_TruthValue;


typedef Mib2_TimeTicks  Mib2_TimeStamp;
typedef Mib2_Unsigned   Mib2_IpAddress;
typedef Mib2_Integer    Mib2_RowStatus;
typedef Mib2_Integer32  Mib2_InterfaceIndex, Mib2_IfIndexOrZero;
	
/* simple type used for imitating 64 bit integers */
typedef struct ui64
    {
    Mib_u32 high;
    Mib_u32 low;
    } UI64;

typedef UI64 Mib2_Counter64;

/* m2Lib.c Error Codes */
struct socket;

#define S_m2Lib_INVALID_PARAMETER               (M_m2Lib | 1)
#define S_m2Lib_ENTRY_NOT_FOUND			(M_m2Lib | 2)
#define S_m2Lib_TCPCONN_FD_NOT_FOUND		(M_m2Lib | 3)
#define S_m2Lib_INVALID_VAR_TO_SET		(M_m2Lib | 4)
#define S_m2Lib_CANT_CREATE_SYS_SEM		(M_m2Lib | 5)
#define S_m2Lib_CANT_CREATE_IF_SEM		(M_m2Lib | 6)
#define S_m2Lib_CANT_CREATE_ROUTE_SEM		(M_m2Lib | 7)
#define S_m2Lib_ARP_PHYSADDR_NOT_SPECIFIED	(M_m2Lib | 8)
#define S_m2Lib_IF_TBL_IS_EMPTY			(M_m2Lib | 9)
#define S_m2Lib_IF_CNFG_CHANGED			(M_m2Lib | 10)
#define S_m2Lib_TOO_BIG                         (M_m2Lib | 11)
#define S_m2Lib_BAD_VALUE                       (M_m2Lib | 12)
#define S_m2Lib_READ_ONLY                       (M_m2Lib | 13)
#define S_m2Lib_GEN_ERR                         (M_m2Lib | 14)

#define   ETHERADDRLEN            6
#define   M2DISPLAYSTRSIZE	256
#define   MAXOIDLENGTH           40
#define   MAXIFPHYADDR		 16

/* defines for enumerated types as specified by RFC 1213 */

/* possible values for ifType (found in IANA-MIB) */

#define M2_ifType_other                  1   /* none of the following */
#define M2_ifType_regular1822            2
#define M2_ifType_hdh1822                3
#define M2_ifType_ddnX25                 4
#define M2_ifType_rfc877x25              5
#define M2_ifType_ethernetCsmacd         6
#define M2_ifType_ethernet_csmacd        M2_ifType_ethernetCsmacd
#define M2_ifType_iso88023Csmacd         7
#define M2_ifType_iso88023_csmacd        M2_ifType_iso88023Csmacd
#define M2_ifType_iso88024TokenBus       8
#define M2_ifType_iso88024_tokenBus      M2_ifType_iso88024TokenBus
#define M2_ifType_iso88025TokenRing      9
#define M2_ifType_iso88025_tokenRing     M2_ifType_iso88025TokenRing
#define M2_ifType_iso88026Man            10
#define M2_ifType_iso88026_man           M2_ifType_iso88026Man
#define M2_ifType_starLan                11
#define M2_ifType_proteon10Mbit          12
#define M2_ifType_proteon80Mbit          13
#define M2_ifType_hyperchannel           14
#define M2_ifType_fddi                   15
#define M2_ifType_lapb                   16
#define M2_ifType_sdlc                   17
#define M2_ifType_ds1                    18  /* DS1-MIB */
#define M2_ifType_e1                     19  /* Obsolete see DS1-MIB */
#define M2_ifType_basicISDN              20
#define M2_ifType_primaryISDN            21
#define M2_ifType_propPointToPointSerial 22  /* proprietary serial */
#define M2_ifType_ppp                    23
#define M2_ifType_softwareLoopback       24
#define M2_ifType_eon                    25  /* CLNP over IP */
#define M2_ifType_ethernet3Mbit          26
#define M2_ifType_nsip                   27  /* XNS over IP */
#define M2_ifType_slip                   28  /* generic SLIP */
#define M2_ifType_ultra                  29  /* ULTRA technologies */
#define M2_ifType_ds3                    30  /* DS3-MIB */
#define M2_ifType_sip                    31  /* SMDS, coffee */
#define M2_ifType_frameRelay             32  /* DTE only. */
#define M2_ifType_rs232                  33
#define M2_ifType_para                   34  /* parallel-port */
#define M2_ifType_arcnet                 35  /* arcnet */
#define M2_ifType_arcnetPlus             36  /* arcnet plus */
#define M2_ifType_atm                    37  /* ATM cells */
#define M2_ifType_miox25                 38
#define M2_ifType_sonet                  39  /* SONET or SDH */
#define M2_ifType_x25ple                 40
#define M2_ifType_iso88022llc            41
#define M2_ifType_localTalk              42
#define M2_ifType_smdsDxi                43
#define M2_ifType_frameRelayService      44  /* FRNETSERV-MIB */
#define M2_ifType_v35                    45
#define M2_ifType_hssi                   46
#define M2_ifType_hippi                  47
#define M2_ifType_modem                  48  /* Generic modem */
#define M2_ifType_aal5                   49  /* AAL5 over ATM */
#define M2_ifType_sonetPath              50
#define M2_ifType_sonetVT                51
#define M2_ifType_smdsIcip               52  /* SMDS InterCarrier Interface */
#define M2_ifType_propVirtual            53  /* proprietary virtual/internal */
#define M2_ifType_propMultiplexor        54  /* proprietary multiplexing */
#define M2_ifType_ieee80212              55  /* 100BaseVG */
#define M2_ifType_fibreChannel           56  /* Fibre Channel */
#define M2_ifType_hippiInterface         57  /* HIPPI interfaces */
#define M2_ifType_frameRelayInterconnect 58  /* Obsolete use either 32 or 44 */
#define M2_ifType_aflane8023             59  /* ATM Emulated LAN for 802.3 */
#define M2_ifType_aflane8025             60  /* ATM Emulated LAN for 802.5 */
#define M2_ifType_cctEmul                61  /* ATM Emulated circuit */
#define M2_ifType_fastEther              62  /* Fast Ethernet (100BaseT) */
#define M2_ifType_isdn                   63  /* ISDN and X.25 */
#define M2_ifType_v11                    64  /* CCITT V.11/X.21 */
#define M2_ifType_v36                    65  /* CCITT V.36 */
#define M2_ifType_g703at64k              66  /* CCITT G703 at 64Kbps */
#define M2_ifType_g703at2mb              67  /* Obsolete see DS1-MIB */
#define M2_ifType_qllc                   68  /* SNA QLLC */
#define M2_ifType_fastEtherFX            69  /* Fast Ethernet (100BaseFX) */
#define M2_ifType_channel                70  /* channel */
#define M2_ifType_ieee80211              71  /* radio spread spectrum */
#define M2_ifType_ibm370parChan          72  /* IBM 360/370 OEMI Channel */
#define M2_ifType_escon                  73  /* IBM Enterprise Systems Cnx */
#define M2_ifType_dlsw                   74  /* Data Link Switching */
#define M2_ifType_isdns                  75  /* ISDN S/T interface */
#define M2_ifType_isdnu                  76  /* ISDN U interface */
#define M2_ifType_lapd                   77  /* Link Access Protocol D */
#define M2_ifType_ipSwitch               78  /* IP Switching Objects */
#define M2_ifType_rsrb                   79  /* Remote Source Route Bridging */
#define M2_ifType_atmLogical             80  /* ATM Logical Port */
#define M2_ifType_ds0                    81  /* Digital Signal Level 0 */
#define M2_ifType_ds0Bundle              82  /* ds0s on the same ds1 */
#define M2_ifType_bsc                    83  /* Bisynchronous Protocol */
#define M2_ifType_async                  84  /* Asynchronous Protocol */
#define M2_ifType_cnr                    85  /* Combat Net Radio */
#define M2_ifType_iso88025Dtr            86  /* ISO 802.5r DTR */
#define M2_ifType_eplrs                  87  /* Ext Pos Loc Report Sys */
#define M2_ifType_arap                   88  /* Appletalk Remote Access Proto */
#define M2_ifType_propCnls               89  /* Proprietary Cnx-less Proto */
#define M2_ifType_hostPad                90  /* CCITT-ITU X.29 PAD Protocol */
#define M2_ifType_termPad                91  /* CCITT-ITU X.3 PAD Facility */
#define M2_ifType_frameRelayMPI          92  /* Multiproto Interconnect FR */
#define M2_ifType_x213                   93  /* CCITT-ITU X213 */
#define M2_ifType_adsl                   94  /* Asymmetric DSL */
#define M2_ifType_radsl                  95  /* Rate-Adapt. DSL */
#define M2_ifType_sdsl                   96  /* Symmetric DSL */
#define M2_ifType_vdsl                   97  /* Very H-Speed DSL */
#define M2_ifType_iso88025CRFPInt        98  /* ISO 802.5 CRFP */
#define M2_ifType_myrinet                99  /* Myricom Myrinet */
#define M2_ifType_voiceEM                100 /* voice recEive and transMit */
#define M2_ifType_voiceFXO               101 /* voice Foreign Exchg Office */
#define M2_ifType_voiceFXS               102 /* voice Foreign Exchg Station */
#define M2_ifType_voiceEncap             103 /* voice encapsulation */
#define M2_ifType_voiceOverIp            104 /* voice over IP encapsulation */
#define M2_ifType_atmDxi                 105 /* ATM DXI */
#define M2_ifType_atmFuni                106 /* ATM FUNI */
#define M2_ifType_atmIma                 107 /* ATM IMA */
#define M2_ifType_pppMultilinkBundle     108 /* PPP Multilink Bundle */
#define M2_ifType_ipOverCdlc             109 /* IBM ipOverCdlc */
#define M2_ifType_ipOverClaw             110 /* IBM Common Link Access */
#define M2_ifType_stackToStack           111 /* IBM stackToStack */
#define M2_ifType_virtualIpAddress       112 /* IBM VIPA */
#define M2_ifType_mpc                    113 /* IBM multi-protocol channel */
#define M2_ifType_ipOverAtm              114 /* IBM ipOverAtm */
#define M2_ifType_iso88025Fiber          115 /* ISO 802.5j Fiber Token Ring */
#define M2_ifType_tdlc                   116 /* IBM twinaxial data link */
#define M2_ifType_gigabitEthernet        117 /* Gigabit Ethernet */
#define M2_ifType_hdlc                   118 /* HDLC */
#define M2_ifType_lapf                   119 /* LAP F */
#define M2_ifType_v37                    120 /* V.37 */
#define M2_ifType_x25mlp                 121 /* Multi-Link Protocol */
#define M2_ifType_x25huntGroup           122 /* X25 Hunt Group */
#define M2_ifType_trasnpHdlc             123 /* Transp HDLC */
#define M2_ifType_interleave             124 /* Interleave channel */
#define M2_ifType_fast                   125 /* Fast channel */
#define M2_ifType_ip                     126 /* IP (APPN HPR in IP networks) */
#define M2_ifType_docsCableMaclayer      127 /* CATV Mac Layer */
#define M2_ifType_docsCableDownstream    128 /* CATV Downstream interface */
#define M2_ifType_docsCableUpstream      129 /* CATV Upstream interface */
#define M2_ifType_a12MppSwitch           130 /* Avalon Parallel Processor */
#define M2_ifType_tunnel                 131 /* Encapsulation interface */
#define M2_ifType_coffee                 132 /* coffee pot */
#define M2_ifType_ces                    133 /* Circuit Emulation Service */
#define M2_ifType_atmSubInterface        134 /* ATM Sub Interface */
#define M2_ifType_l2vlan                 135 /* Layer 2 V-LAN using 802.1Q */
#define M2_ifType_l3ipvlan               136 /* Layer 3 V-LAN using IP */
#define M2_ifType_l3ipxvlan              137 /* Layer 3 V-LAN using IPX */
#define M2_ifType_digitalPowerline       138 /* IP over Power Lines */
#define M2_ifType_mediaMailOverIp        139 /* Multimedia Mail over IP */
#define M2_ifType_dtm                    140 /* Dynamic sync Transfer Mode */
#define M2_ifType_dcn                    141 /* Data Communications Network */
#define M2_ifType_ipForward              142 /* IP Forwarding Interface */
#define M2_ifType_msdsl                  143 /* Multi-rate Symmetric DSL */
#define M2_ifType_ieee1394               144 /* IEEE1394 High Perf Serial Bus */
#define M2_ifType_if_gsn                 145 /* HIPPI-6400 */
#define M2_ifType_dvbRccMacLayer         146 /* DVB-RCC MAC Layer */
#define M2_ifType_dvbRccDownstream       147 /* DVB-RCC Downstream Channel */
#define M2_ifType_dvbRccUpstream         148 /* DVB-RCC Upstream Channel */
#define M2_ifType_atmVirtual             149 /* ATM Virtual Interface */
#define M2_ifType_srp                    151 /* Spatial Reuse Protocol */
#define M2_ifType_voiceOverAtm           152 /* Voice Over ATM */
#define M2_ifType_voiceOverFrameRelay    153 /* Voice Over Frame Relay */
#define M2_ifType_idsl                   154 /* DSL over ISDN */
#define M2_ifType_compositeLink          155 /* Avici Composite Link */
#define M2_ifType_ss7SigLink             156 /* SS7 Signaling Link */
#define M2_ifType_pmp                    157 /* Point to Multipoint */

/* interface attach/insert and detach/remove */

#define M2_IF_TABLE_INSERT             1
#define M2_IF_TABLE_REMOVE             2

#define M2_STACK_TABLE_INSERT          1
#define M2_STACK_TABLE_REMOVE          2

/* 
 * values for the mibStyle variable in M2_IFINDEX
 * Do not use 0x10000 as this has been defined for END_MIB_2233
 * in end.h which is shared
 */

#define IF_MIB_2233                    0x1 
#define IF_MIB_IPV4                    0x2
#define IF_MIB_IPV6                    0x4

/*
 * The following flag fields are used by the interfaces code protocol 
 * to keep track of the IPv4 - IPv6 attach detach issue.
 */

#define IPV4_IF_ATTACHED               0x1
#define IPV6_IF_ATTACHED               0x2

#if 0
/* interface mib styles used by the MUX/drivers */

#define MIB_STYLE_1213 1
#define MIB_STYLE_2233 2

#endif

/* interface counter IDs */

#define M2_ctrId_ifInOctets            1
#define M2_ctrId_ifInUcastPkts         2
#define M2_ctrId_ifInNUcastPkts        3
#define M2_ctrId_ifInDiscards          4
#define M2_ctrId_ifInErrors            5
#define M2_ctrId_ifInUnknownProtos     6
#define M2_ctrId_ifOutOctets           7
#define M2_ctrId_ifOutUcastPkts        8
#define M2_ctrId_ifOutNUcastPkts       9
#define M2_ctrId_ifOutDiscards         10
#define M2_ctrId_ifOutErrors           11
#define M2_ctrId_ifInMulticastPkts     12
#define M2_ctrId_ifInBroadcastPkts     13
#define M2_ctrId_ifOutMulticastPkts    14
#define M2_ctrId_ifOutBroadcastPkts    15
#define M2_ctrId_ifHCInOctets          16
#define M2_ctrId_ifHCInUcastPkts       17
#define M2_ctrId_ifHCInMulticastPkts   18
#define M2_ctrId_ifHCInBroadcastPkts   19
#define M2_ctrId_ifHCOutOctets         20
#define M2_ctrId_ifHCOutUcastPkts      21
#define M2_ctrId_ifHCOutMulticastPkts  22
#define M2_ctrId_ifHCOutBroadcastPkts  23
/* packet control used for stat counting routines (in or out) */
#define M2_PACKET_IN                   24 
#define M2_PACKET_OUT                  25
#define M2_PACKET_IN_ERROR             26
#define M2_PACKET_OUT_ERROR            27
#define M2_PACKET_IN_DISCARD           28
#define M2_PACKET_OUT_DISCARD          29 

/* interface variable IDs */

#define M2_varId_ifAdminStatus               1
#define M2_varId_ifLinkUpDownTrapEnable      2
#define M2_varId_ifMtu                       3
#define M2_varId_ifPromiscuousMode           4
#define M2_varId_ifPhysAddress               5
#define M2_varId_ifDescr                     6
#define M2_varId_ifOperStatus                7
#define M2_varId_ifAlias                     8
#define M2_varId_ifOutQLen                   9
#define M2_varId_ifSpecific                  10
#define M2_varId_ifName                      11
#define M2_varId_ifType                      12
#define M2_varId_ifHighSpeed                 13
#define M2_varId_ifSpeed                     14
#define M2_varId_ifConnectorPresent          15
#define M2_varId_ifLastChange                16

/* possible values for ifAdminStatus */

#define M2_ifAdminStatus_up           			1
#define M2_ifAdminStatus_down				2
#define M2_ifAdminStatus_testing        		3

/* possible values for ifOperStatus */

#define M2_ifOperStatus_up              		1
#define M2_ifOperStatus_down            		2
#define M2_ifOperStatus_testing         		3

/* possible values for ifPromiscuousMode */

#define M2_ifPromiscuousMode_on                         1
#define M2_ifPromiscuousMode_off                        2

/* Row Status defines */

#define ROW_ACTIVE                                      1
#define ROW_NOTINSERVICE                                2
#define ROW_NOTREADY                                    3
#define ROW_CREATEANDGO                                 4
#define ROW_CREATEANDWAIT                               5
#define ROW_DESTROY                                     6

/* Storage type defines */

#define STORAGE_OTHER                                   1
#define STORAGE_VOLATILE                                2
#define STORAGE_NONVOLATILE                             3    

/* Boolean Values */

#define M2_TRUE                                         1
#define M2_FALSE                                        2

/* defines for all the objects in the interface table */

#define M2_IFLASTCHANGE                                 1
#define M2_IFINOCTETS                                   2
#define M2_IFINUCASTPKTS                                3
#define M2_IFINNUCASTPKTS                               4
#define M2_IFINDISCARDS                                 5
#define M2_IFINERRORS                                   6
#define M2_IFINUNKNOWNPROTOS                            7
#define M2_IFOUTOCTETS                                  8
#define M2_IFOUTUCASTPKTS                               9
#define M2_IFOUTNUCASTPKTS                              10
#define M2_IFOUTDISCARDS                                11
#define M2_IFOUTERRORS                                  12
#define M2_IFOUTQLEN                                    13
#define M2_IFINMULTICASTPKTS                            14
#define M2_IFINBROADCASTPKTS                            15
#define M2_IFOUTMULTICASTPKTS                           16
#define M2_IFOUTBROADCASTPKTS                           17
#define M2_IFHCINOCTETS                                 18
#define M2_IFHCINUCASTPKTS                              19
#define M2_IFHCINMULTICASTPKTS                          20
#define M2_IFHCINBROADCASTPKTS                          21
#define M2_IFHCOUTOCTETS                                22
#define M2_IFHCOUTUCASTPKTS                             23
#define M2_IFHCOUTMULTICASTPKTS                         24
#define M2_IFHCOUTBROADCASTPKTS                         25
#define M2_IFLINKUPDOWNTRAPENABLE                       26
#define M2_IFHIGHSPEED                                  27
#define M2_IFPROMISCUOUSMODE                            28
#define M2_IFCONNECTORPRESENT                           29

/* defines for rcvAddr table entries */
#define M2_IFRCVADDRSTATUS                              1
#define M2_IFRCVADDRTYPE                                2

/* possible values for  ipForwarding */

#define M2_ipForwarding_forwarding      		1
#define M2_ipForwarding_not_forwarding  		2

/* possible values for ipRouteType */

#define M2_ipRouteType_other            		1
#define M2_ipRouteType_invalid          		2
#define M2_ipRouteType_direct           		3
#define M2_ipRouteType_indirect         		4

/* possible values for ipRouteProto */

#define M2_ipRouteProto_other           		1
#define M2_ipRouteProto_local           		2
#define M2_ipRouteProto_netmgmt         		3
#define M2_ipRouteProto_icmp            		4
#define M2_ipRouteProto_egp             		5
#define M2_ipRouteProto_ggp             		6
#define M2_ipRouteProto_hello           		7
#define M2_ipRouteProto_rip             		8
#define M2_ipRouteProto_is_is           		9
#define M2_ipRouteProto_es_is				10
#define M2_ipRouteProto_ciscoIgrp			11
#define M2_ipRouteProto_bbnSpfIgp			12
#define M2_ipRouteProto_ospf				13
#define M2_ipRouteProto_bgp     			14

/* possible values for ipNetToMediaType */

#define M2_ipNetToMediaType_other			1
#define M2_ipNetToMediaType_invalid     		2
#define M2_ipNetToMediaType_dynamic     		3
#define M2_ipNetToMediaType_static      		4

/* possible values for tcpRtoAlgorithm */

#define M2_tcpRtoAlgorithm_other        		1
#define M2_tcpRtoAlgorithm_constant     		2
#define M2_tcpRtoAlgorithm_rsre         		3
#define M2_tcpRtoAlgorithm_vanj         		4

/* possible values for tcpConnState */

#define M2_tcpConnState_closed          		1
#define M2_tcpConnState_listen          		2
#define M2_tcpConnState_synSent         		3
#define M2_tcpConnState_synReceived     		4
#define M2_tcpConnState_established     		5
#define M2_tcpConnState_finWait1        		6
#define M2_tcpConnState_finWait2        		7
#define M2_tcpConnState_closeWait       		8
#define M2_tcpConnState_lastAck         		9
#define M2_tcpConnState_closing         		10
#define M2_tcpConnState_timeWait        		11
#define M2_tcpConnState_deleteTCB       		12

/*
 * When using vxWorks SNMP this constants must have the same value as NEXT and
 * EXACT
 */

#define M2_EXACT_VALUE      	0xA0
#define M2_NEXT_VALUE           0xA1 

                                             /* defines for IGMP varToSet */
#define M2_var_igmpInterfaceQueryInterval                1
#define M2_var_igmpInterfaceStatus                       2
#define M2_var_igmpInterfaceVersion                      4
#define M2_var_igmpInterfaceQueryMaxResponseTime         8
#define M2_var_igmpInterfaceRobustness                  16 
#define M2_var_igmpInterfaceLastMembQueryIntvl          32


/* IGMP defines from leaf.h generated file */

#define LEAF_igmpInterfaceIfIndex	1
#define MIN_igmpInterfaceIfIndex	1L
#define MAX_igmpInterfaceIfIndex	2147483647L
#define LEAF_igmpInterfaceQueryInterval	2
#define LEAF_igmpInterfaceStatus	3
#define VAL_igmpInterfaceStatus_active	1L
#define VAL_igmpInterfaceStatus_notInService	2L
#define VAL_igmpInterfaceStatus_notReady	3L
#define VAL_igmpInterfaceStatus_createAndGo	4L
#define VAL_igmpInterfaceStatus_createAndWait	5L
#define VAL_igmpInterfaceStatus_destroy	6L
#define LEAF_igmpInterfaceVersion	4
#define LEAF_igmpInterfaceQuerier	5
#define LEAF_igmpInterfaceQueryMaxResponseTime	6
#define MIN_igmpInterfaceQueryMaxResponseTime   0L
#define MAX_igmpInterfaceQueryMaxResponseTime   255L
#define LEAF_igmpInterfaceQuerierUpTime 7
#define LEAF_igmpInterfaceQuerierExpiryTime     8
#define LEAF_igmpInterfaceVersion1QuerierTimer	9
#define LEAF_igmpInterfaceWrongVersionQueries	10
#define LEAF_igmpInterfaceJoins	11
#define LEAF_igmpInterfaceProxyIfIndex  12
#define MIN_igmpInterfaceProxyIfIndex   0L
#define MAX_igmpInterfaceProxyIfIndex   2147483647L
#define LEAF_igmpInterfaceGroups	13
#define LEAF_igmpInterfaceRobustness	14
#define MIN_igmpInterfaceRobustness     1L
#define MAX_igmpInterfaceRobustness     255L
#define LEAF_igmpInterfaceLastMembQueryIntvl	15
#define MIN_igmpInterfaceLastMembQueryIntvl     0L
#define MAX_igmpInterfaceLastMembQueryIntvl     255L
#define LEAF_igmpCacheAddress	1
#define LEAF_igmpCacheIfIndex	2
#define MIN_igmpCacheIfIndex	1L
#define MAX_igmpCacheIfIndex	2147483647L
#define LEAF_igmpCacheSelf	3
#define VAL_igmpCacheSelf_true	1L
#define VAL_igmpCacheSelf_false	2L
#define LEAF_igmpCacheLastReporter	4
#define LEAF_igmpCacheUpTime	5
#define LEAF_igmpCacheExpiryTime	6
#define LEAF_igmpCacheStatus	7
#define VAL_igmpCacheStatus_active	1L
#define VAL_igmpCacheStatus_notInService	2L
#define VAL_igmpCacheStatus_notReady	3L
#define VAL_igmpCacheStatus_createAndGo	4L
#define VAL_igmpCacheStatus_createAndWait	5L
#define VAL_igmpCacheStatus_destroy	6L
#define LEAF_igmpCacheVersion1HostTimer	8


/*
 * UI64_ZERO - Zero a UI64 struct
 *
 * PARAMETERS:  UI64 * Pointer to the object to be zeroed.
 */
#define UI64_ZERO(N) (N)->high = (N)->low = 0L

/*
 * UI64_ADD32 - Add a UINT to a UI64
 * 
 * PARAMETERS:  UI64 * pointer to the object to be updated
 *              UINT   the quantity to add in.
 * 
 * RESTRICTIONS: This routine will wrap the object if necessary and not give
 *               any warning about having done so.
 */
#define UI64_ADD32(N, I) (N)->low =(N)->low + ((Mib2_Counter)I); if ((N)->low < ((Mib2_Counter)I)) (N)->high++

/*
 * UI64_SUB64 - Subtract two UI64s
 *
 * PARAMETERS:  UI64 * the result goes here
 *              UI64 * Subtract from this object
 *              UI64 * the object to subtract
 *
 * RESTRICTIONS: This routine will wrap the object if necessary and not give
 *               any warning about having done so.
 */
#define UI64_SUB64(X, Y, Z)  (X)->low = (Y)->low - (Z)->low; \
                                   (X)->high = (Y)->high - (Z)->high; \
                                   if ((X)->low > (Y)->low) (X)->high-- 

/*
 * UI64_COPY - Copy one UI64 to another
 *
 * PARAMETERS:  UI64 * the result goes here
 *              UI64 * copy from this object
 */
#define UI64_COPY(X, Y)  (X)->low = (Y)->low; (X)->high = (Y)->high

/*
 * UI64_COMP - Compare two UI64s
 *
 * PARAMETERS:  UI64 * The two objects to compare
 *              UI64 * 
 *
 * RETURNS:  < 0 if the first is smaller than the second
 *           > 0 if the first is greater than the second
 *             0 if they are equal.
 */
#define UI64_COMP(X, Y) \
  (((X)->high == (Y)->high) ? \
   (((X)->low == (Y)->low)  ? (0) : (((X)->low > (Y)->low) ? (1) : (-1))) : \
   (((X)->high > (Y)->high) ? (1) : (-1)))

typedef struct
    {
    Mib2_Integer idLength;			        /* Length of the object identifier */
    Mib2_Integer idArray [MAXOIDLENGTH];	/* Object Id numbers */
    } M2_OBJECTID;

typedef struct
    {
    Mib2_Integer            addrLength;			/* Length of address */
    Mib2_OctetString        phyAddress [MAXIFPHYADDR];   /* physical address value */
    } M2_PHYADDR;

/* 
 * The only difference between M2_PHYADDR and the following structure is
 * that the former has a static field for the physical address string, 
 * whereas the latter has a pointer that helps in a set opertaion. It 
 * prevents an un-necessary bcopy.
 */

typedef struct
    {
    Mib2_Integer    addrLength;	        /* Length of address */
    unsigned char * pAddress;           /* physical address pointer */
    } M2_PHYADDRSET;

/*
 * The structures that follow are based on the MIB-II RFC-1213.  Each field in
 * each of the structures has the same name as the name specified in by the RFC.
 * Please refer to the RFC for a complete description of the variable and its
 * semantics.
 */

/* System Group bit fields that map to variables that can be set */

#define    M2SYSNAME    	0x01
#define    M2SYSCONTACT 	0x02
#define	   M2SYSLOCATION	0x04

/*From rfc1213*/
typedef struct
    {
    Mib2_OctetString   	sysDescr     [M2DISPLAYSTRSIZE];
    M2_OBJECTID        	sysObjectID;
    Mib2_TimeTicks      sysUpTime;
    Mib2_OctetString   	sysContact   [M2DISPLAYSTRSIZE];
    Mib2_OctetString   	sysName      [M2DISPLAYSTRSIZE];
    Mib2_OctetString   	sysLocation  [M2DISPLAYSTRSIZE];
    Mib2_Integer        sysServices;
    Mib2_TimeTicks      sysORLastChange;
    }  M2_SYSTEM;
/* sysOrEntry */
typedef struct sysOrEntry
    {
    char OR_descr[256];
    M2_OBJECTID OR_oid;
    Mib2_TimeTicks OR_uptime;
    struct sysOrEntry *next;
    }SYS_ORENTRY;


/* Interface group variables from rfc1213,rfc2233*/
typedef struct
    {
    Mib2_Integer   ifNumber;          /* Number of Interfaces in the System */
    Mib2_TimeTicks ifTableLastChange; /* Time the ifTable was last changed */
    Mib2_TimeTicks ifStackLastChange; /* Time the stackTable was last changed */
    }  M2_INTERFACE;

/* values as per RFC 1215 */

#define M2_LINK_DOWN_TRAP	2
#define M2_LINK_UP_TRAP		3

#define M2_LINK_UP_DOWN_TRAP_ENABLED   1
#define M2_LINK_UP_DOWN_TRAP_DISABLED  2

#define M2_PROMISCUOUS_MODE_ON   1
#define M2_PROMISCUOUS_MODE_OFF  2

#define M2_CONNECTOR_PRESENT      1
#define M2_CONNECTOR_NOT_PRESENT  2

typedef struct
    {
    Mib2_Integer	 ifIndex;			 /* Unique value for each interface */
    Mib2_OctetString ifDescr  [M2DISPLAYSTRSIZE]; /* Information about the interface */
    Mib2_Integer   	 ifType;            /* Type of interface */
    Mib2_Integer   	 ifMtu;             /* Max size of datagram for the interface */
    Mib2_Gauge       ifSpeed;           /* Interface's current bandwidth in bits/sec */
    M2_PHYADDR       ifPhysAddress;     /* Mac layer address of the interface */
    Mib2_Integer     ifAdminStatus;     /* Desired state for the interface */
    Mib2_Integer     ifOperStatus;      /* Current operational status of the interface */
    Mib2_TimeTicks   ifLastChange;      /* Value of sysUpTime when interface entered 
                                                                               its current operational state */
    Mib2_Counter     ifInOctets;        /* Number of octets received on the interface */
    Mib2_Counter     ifInUcastPkts;     /* Number of subnetwork-unicast packets
                                                                               delivered to a higher-layer protocol */
    Mib2_Counter     ifInNUcastPkts;    /* Number of non-unicast packets delivered
                                                                               to a higher layer protocol */
    Mib2_Counter     ifInDiscards;      /* Number of inbound packets discarded */
    Mib2_Counter     ifInErrors;        /* Inbound packets that contained errors */
    Mib2_Counter     ifInUnknownProtos; /* Inbound packets discarded due to unknown 
                                                                               or unsupported protocol */
    Mib2_Counter     ifOutOctets;       /* Number of octets transmitted on the interface */
    Mib2_Counter     ifOutUcastPkts;    /* Number of packets transmitted to subnet 
                                                                               unicast address */
    Mib2_Counter     ifOutNUcastPkts;   /* Number of packets sent to non-unicast
                                                                               address */
    Mib2_Counter     ifOutDiscards;     /* Number of outbound packets discarded */
    Mib2_Counter     ifOutErrors;       /* Number of outbound packets that could not
                                                                               be transmitted due to errors */
    Mib2_Counter     ifOutQLen;         /* Length of output packet queue */
    M2_OBJECTID      ifSpecific;        /* Reference to MIB definitions specific to
                                                                               particular media being used */
	}  M2_INTERFACETBL;

/* The RFC 2233 additions to the ifTable */

typedef struct 
    {
    Mib2_OctetString     ifName [M2DISPLAYSTRSIZE];
    Mib2_Counter32       ifInMulticastPkts;
    Mib2_Counter32       ifInBroadcastPkts;
    Mib2_Counter32       ifOutMulticastPkts;
    Mib2_Counter32       ifOutBroadcastPkts;
    Mib2_Counter64       ifHCInOctets;
    Mib2_Counter64       ifHCInUcastPkts;
    Mib2_Counter64       ifHCInMulticastPkts;
    Mib2_Counter64       ifHCInBroadcastPkts;
    Mib2_Counter64       ifHCOutOctets;
    Mib2_Counter64       ifHCOutUcastPkts;
    Mib2_Counter64       ifHCOutMulticastPkts;
    Mib2_Counter64       ifHCOutBroadcastPkts;
    Mib2_Integer         ifLinkUpDownTrapEnable;
    Mib2_Gauge32         ifHighSpeed;
    Mib2_TruthValue      ifPromiscuousMode;
    Mib2_TruthValue      ifConnectorPresent;
    Mib2_OctetString     ifAlias [M2DISPLAYSTRSIZE];
    Mib2_TimeStamp       ifCounterDiscontinuityTime;
    } M2_2233TBL;

/* Update Routines */

typedef struct M2_ID_S M2_ID;
typedef struct M2_IFSTACKTBL_S M2_IFSTACKTBL;
typedef STATUS (* M2_PKT_COUNT_RTN) (M2_ID *, UINT, UCHAR *, UINT);
typedef STATUS (* M2_CTR_UPDATE_RTN) (M2_ID *, UINT, UINT);
typedef STATUS (* M2_VAR_UPDATE_RTN) (M2_ID *, UINT, caddr_t);

/* Combination of the above interface structs */

typedef struct
    {
    M2_INTERFACETBL     mibIfTbl;         /* the RFC 1213 objects */
    M2_2233TBL          mibXIfTbl;        /* the RFC 2233 extension */
    } M2_DATA;

/* The interface table struct for RFC 2233 compliance */

struct M2_ID_S
    {
    M2_DATA           m2Data;           /* the interface table */
    M2_PKT_COUNT_RTN  m2PktCountRtn;    /* packet counter function */
    M2_CTR_UPDATE_RTN m2CtrUpdateRtn;   /* counter increment function */
    M2_VAR_UPDATE_RTN m2VarUpdateRtn;   /* variable update routine */
    void *            m2UsrCounter;     /* pointer to additional counters */
    };

/* The structure for the ifStack table as described in RFC 2233 */

struct M2_IFSTACKTBL_S
    {
    struct M2_IFSTACKTBL_S * pNextLower; /* Pointer to the next relation */
    Mib2_Integer             index;      /* The ifIndex */ 
    Mib2_RowStatus           status;     /* status of relationship */
    };

/* The structure for the ifRcv address table as described in RFC 2233 */

typedef struct M2_IFRCVADDRTBL_S 
    {
    M2_PHYADDR                 ifRcvAddrAddr;/* The physical address for which
                                              * system will accept pkts/frames
                                              */
    struct M2_IFRCVADDRTBL_S * pNextEntry;      /* Next pointer */
    Mib2_RowStatus             ifRcvAddrStatus; /* The rowStatus */
    Mib2_Integer               ifRcvAddrType;   /* The address type */
    
    } M2_IFRCVADDRTBL;
    
/* The structure for the ifIndex value and corresponding ifnet pointer */
    
typedef struct M2_IFINDEX_S
    {
    AVLU_NODE          ifNode;       /* Node representing an if in AVL tree */ 
    M2_OBJECTID        ifOid;        /* I/F Object Id */
    void *             pIfStats;     /* Pointer to the driver specific
                                     * structure
                                     */
    M2_IFSTACKTBL *    pNextLower;   /* List of lower sub-layers */
    M2_IFRCVADDRTBL *  pRcvAddr;     /* rcvAddr list */

		       /* Ioctl to munge interface flags */
		       /* Called from m2IfTblEntrySet to change the values in */
		       /* the ifnet structure in a non-protocol-specific way. */
		       /* Callbacks are bad for tor3 (so I've heard). */
    int                (*ifIoctl) (struct socket*, u_long, caddr_t);

#if 0    
    STATUS             (*rcvAddrGet) (struct ifnet *, struct M2_IFINDEX_S *);
#endif    
    /* struct in6_ifdata *pIn6IfData; */ /* defunct ! */
    struct in6_ifinfo *pIn6IfInfo;   /* IPv6 MIB data */
    Mib2_Integer       ifType;       /* Interface type */
    Mib2_Integer       ifIndex;      /* Unique value for each interface */
    short              mibStyle;     /* MIBs supported */
    } M2_IFINDEX;

/* Structure to perform the set operation for if table */
    
typedef struct ifSetentry
    {
    Mib2_Integer     ifAdminStatus;
    Mib2_TruthValue  ifPromiscuousMode;
    Mib2_Integer     ifLinkUpDownTrapEnable;
    Mib2_OctetString ifAlias[M2DISPLAYSTRSIZE];
    Mib2_Unsigned    varToSet;
    Mib2_Integer     ifIndex;
    } IF_SETENTRY;

/* IP group bit fields that map to variables that can be set  from rfc1213*/

#define M2_IPFORWARDING		0x01
#define M2_IPDEFAULTTTL		0x02

typedef struct
    {
    Mib2_Integer   ipForwarding;
    Mib2_Integer   ipDefaultTTL;
    Mib2_Counter   ipInReceives;
    Mib2_Counter   ipInHdrErrors;
    Mib2_Counter   ipInAddrErrors;
    Mib2_Counter   ipForwDatagrams;
    Mib2_Counter   ipInUnknownProtos;
    Mib2_Counter   ipInDiscards;
    Mib2_Counter   ipInDelivers;
    Mib2_Counter   ipOutRequests;
    Mib2_Counter   ipOutDiscards;
    Mib2_Counter   ipOutNoRoutes;
    Mib2_Integer   ipReasmTimeout;
    Mib2_Counter   ipReasmReqds;
    Mib2_Counter   ipReasmOKs;
    Mib2_Counter   ipReasmFails;
    Mib2_Counter   ipFragOKs;
    Mib2_Counter   ipFragFails;
    Mib2_Counter   ipFragCreates;
    Mib2_Counter   ipRoutingDiscards;
    } M2_IP;

/* IP Address Table group */

typedef struct
{
    Mib2_IpAddress   ipAdEntAddr;
    Mib2_Integer     ipAdEntIfIndex;
    Mib2_IpAddress   ipAdEntNetMask;
    Mib2_Integer     ipAdEntBcastAddr;
    Mib2_Integer     ipAdEntReasmMaxSize;
} M2_IPADDRTBL;

/* IP Routing Table group */

typedef struct
{
    Mib2_IpAddress   		ipRouteDest;
    Mib2_Integer            ipRouteIfIndex;
    Mib2_Integer            ipRouteMetric1;
    Mib2_Integer            ipRouteMetric2;
    Mib2_Integer            ipRouteMetric3;
    Mib2_Integer            ipRouteMetric4;
    Mib2_Integer   			ipRouteNextHop;
    Mib2_Integer            ipRouteType;   
    Mib2_Integer            ipRouteProto;
    Mib2_Integer            ipRouteAge;
    Mib2_IpAddress   		ipRouteMask;
    Mib2_Integer            ipRouteMetric5;
    M2_OBJECTID     		ipRouteInfo;
} M2_IPROUTETBL;

/* IP route table entry bit fields that map to variables that can be set */

#define M2_IP_ROUTE_DEST 		1
#define M2_IP_ROUTE_NEXT_HOP		2
#define M2_IP_ROUTE_TYPE		4
#define M2_IP_ROUTE_MASK                8

/* IP Address Translation Table group */

typedef struct
{
    Mib2_Integer    ipNetToMediaIfIndex;
    M2_PHYADDR 	    ipNetToMediaPhysAddress;
    Mib2_IpAddress  ipNetToMediaNetAddress;
    Mib2_Integer    ipNetToMediaType; 
} M2_IPATRANSTBL;

/* ICMP group from rfc1213*/

typedef struct
{
    Mib2_Counter   icmpInMsgs;
    Mib2_Counter   icmpInErrors;
    Mib2_Counter   icmpInDestUnreachs;
    Mib2_Counter   icmpInTimeExcds;
    Mib2_Counter   icmpInParmProbs;
    Mib2_Counter   icmpInSrcQuenchs;
    Mib2_Counter   icmpInRedirects;
    Mib2_Counter   icmpInEchos;
    Mib2_Counter   icmpInEchoReps;
    Mib2_Counter   icmpInTimestamps;
    Mib2_Counter   icmpInTimestampReps;
    Mib2_Counter   icmpInAddrMasks;
    Mib2_Counter   icmpInAddrMaskReps;
    Mib2_Counter   icmpOutMsgs;
    Mib2_Counter   icmpOutErrors;
    Mib2_Counter   icmpOutDestUnreachs;
    Mib2_Counter   icmpOutTimeExcds;
    Mib2_Counter   icmpOutParmProbs;
    Mib2_Counter   icmpOutSrcQuenchs;
    Mib2_Counter   icmpOutRedirects;
    Mib2_Counter   icmpOutEchos;
    Mib2_Counter   icmpOutEchoReps;
    Mib2_Counter   icmpOutTimestamps;
    Mib2_Counter   icmpOutTimestampReps;
    Mib2_Counter   icmpOutAddrMasks;
    Mib2_Counter   icmpOutAddrMaskReps;
}M2_ICMP;

/* TCP Group */

typedef struct 
{
    Mib2_Integer   tcpRtoAlgorithm;
    Mib2_Integer   tcpRtoMin;
    Mib2_Integer   tcpRtoMax;
    Mib2_Integer   tcpMaxConn;
    Mib2_Counter   tcpActiveOpens;
    Mib2_Counter   tcpPassiveOpens;
    Mib2_Counter   tcpAttemptFails;
    Mib2_Counter   tcpEstabResets;
    Mib2_Gauge     tcpCurrEstab;
    Mib2_Counter   tcpInSegs;
    Mib2_Counter   tcpOutSegs;
    Mib2_Counter   tcpRetransSegs;
    Mib2_Counter   tcpInErrs;
    Mib2_Counter   tcpOutRsts;
} M2_TCPINFO;

/* TCP Connection Table Entry */

typedef struct
{
    Mib2_Integer     tcpConnState;
    Mib2_IpAddress   tcpConnLocalAddress;
    Mib2_Integer     tcpConnLocalPort;
    Mib2_IpAddress   tcpConnRemAddress;
    Mib2_Integer     tcpConnRemPort;
} M2_TCPCONNTBL;

/* User Datagram Protocol Group */

typedef struct
{
    Mib2_Counter   udpInDatagrams;
    Mib2_Counter   udpNoPorts;
    Mib2_Counter   udpInErrors;
    Mib2_Counter   udpOutDatagrams;
} M2_UDP;

/* UDP Connection Table Entry */

typedef struct
{
    Mib2_IpAddress   udpLocalAddress;
    Mib2_Integer     udpLocalPort;
} M2_UDPTBL;

/* IGMP  from rfc2933*/
typedef struct
{
    Mib2_InterfaceIndex  igmpInterfaceIfIndex; 
    Mib2_Unsigned32      igmpInterfaceQueryInterval; 
    Mib2_RowStatus       igmpInterfaceStatus; 
    Mib2_Unsigned32      igmpInterfaceVersion;
    Mib2_IpAddress       igmpInterfaceQuerier;
    Mib2_Unsigned32      igmpInterfaceQueryMaxResponseTime;
    Mib2_TimeTicks       igmpInterfaceQuerierPresentTimeout;
    Mib2_TimeTicks       igmpInterfaceLeaveEnabled;
    Mib2_TimeTicks       igmpInterfaceVersion1QuerierTimer;
    Mib2_Counter32       igmpInterfaceWrongVersionQueries;
    Mib2_Counter32       igmpInterfaceJoins;
    Mib2_Counter32       igmpInterfaceLeaves;
    Mib2_Gauge32		 igmpInterfaceGroups;
    Mib2_Unsigned32      igmpInterfaceRobustness;
    Mib2_TimeTicks       igmpInterfaceQuerierUpTime;
    Mib2_Unsigned32      igmpInterfaceLastMembQueryIntvl;
} M2_IGMP;
    
typedef struct 
{
    Mib2_IpAddress       igmpCacheAddress;
    Mib2_InterfaceIndex  igmpCacheIfIndex;
    Mib2_TruthValue      igmpCacheSelf;               /* was BOOLEAN */
    Mib2_IpAddress       igmpCacheLastReporter;
    Mib2_TimeTicks       igmpCacheUpTime;
    Mib2_TimeTicks       igmpCacheExpiryTime;
    Mib2_RowStatus       igmpCacheStatus;
    Mib2_TimeTicks       igmpCacheVersion1HostTimer;
} M2_IGMP_CACHE;



#ifdef __cplusplus
}
#endif

#endif /* __INCm2LibTypeh */
