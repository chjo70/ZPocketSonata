/* 01comp_net_end.cdf - Component configuration file */

/*
 * Copyright 2001-2006, 2008, 2012-2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19jan17,mca  Moved INCLUDE_ETHERNET here from 00comp_net_mux.cdf
07dec16,mca  Break hard dependency between END and IPNET (US85582)
20nov14,wap  Allow use of INCLUDE_END_COMMON for VxBus GEN2
05sep14,wap  Add END_NET_JOB_INIT_STRING parameter
25may14,rjq  FOLDER_NET_END should be in
             FOLDER_NETWORK_ADVANCED. (V7NET-365)
05may14,rjq  Decouple COREIP with END. (V7NET-105)
03mar14,fao  Add INCLUDE_NETWORK require for INCLUDE_END
03mar14,l_z  Add FOLDER_NET_END_DRV folder for vxbus
21oct13,x_z  Added dependency for VXBUS GEN1.
07feb12,dlk  Fix defect WIND00331675.
17jun08,dlk  Make configNet.h a HDR_FILE of INCLUDE_END rather than
             INCLUDE_END_COMMON.
06jun08,dlk  Remove usrNetEndLib.c as a configlette of
             INCLUDE_END_ETHER_HDR, INCLUDE_END, and INCLUDE_END2.
             Correct for ipcom_end2.o -> vxmux_end2.o rename.
             Correct MODULES for INCLUDE_END_COMMON and INCLUDE_END.
             Remove unnecessary LINK_SYMS for INCLUDE_END2.
22mar08,dlk  MUX2 redesign and END2 IPNet-native drivers.
14jun06,dlk  Fix typo in INCLUDE_END_POLLED_STATS component.
08aug05,wap  Turn poll stats into separate component
13oct04,ann  merged fixes for SPR 100718, 101616 & 100718.
             updated HDR_FILES for END_POLL_STATS_ROUTINE_HOOK.
18aug04,rec  SPR100718 INCLUDE_END requires INCLUDE_NETWORK
12sep03,vvv  updated configlette path
14may03,vvv  removed adv_net.h
16apr02,rvr  removed entry points and PREF_DOMAIN attribute
26nov01,ham  revised.
*/

Folder FOLDER_NET_END {
    NAME        Network END Components
    SYNOPSIS    Support for network devices driver.
#ifdef _WRS_CONFIG_VXBUS
    CHILDREN    FOLDER_NET_END_DRV \
                FOLDER_NET_END_LIB
#else
    CHILDREN    FOLDER_NET_END_LIB
#endif /*_WRS_CONFIG_VXBUS */
    _CHILDREN   FOLDER_NETWORK
}

Folder FOLDER_NET_END_LIB {
    NAME        Network END library Components
    SYNOPSIS    Support for network end library.
}

#ifdef _WRS_CONFIG_VXBUS
Folder FOLDER_NET_END_DRV {
    NAME        Network END driver Components
    SYNOPSIS    Support for network devices driver.
}
#endif /*_WRS_CONFIG_VXBUS */

Component INCLUDE_END_COMMON {
    NAME            END: common Enhanced Network Device support
    SYNOPSIS        Support for network devices using MUX/END interface.
    CONFIGLETTES    usrNetEndLib.c
    HDR_FILES       endLib.h \
                    private/fioLibP.h
    INIT_RTN        usrNetEndLibInit();
    MODULES         endCommon.o
    REQUIRES        INCLUDE_MUX_COMMON INCLUDE_NETWORK
    _CHILDREN       FOLDER_NET_END_LIB
    _DEFAULTS       FOLDER_NET_END_LIB
}

Component INCLUDE_END {
    NAME            END: END-style interface support
    SYNOPSIS        Support for END-style network devices.
    INIT_RTN        endLibInit();
#ifdef _WRS_CONFIG_VXBUS_LEGACY
    HDR_FILES       endLib.h \
                    configNet.h
    REQUIRES        INCLUDE_END_COMMON
#else /* !_WRS_CONFIG_VXBUS_LEGACY */
 #ifdef _WRS_CONFIG_CERT
    REQUIRES        INCLUDE_END_COMMON
 #else
                    INCLUDE_END_COMMON \
                    INCLUDE_BOOT_LINE_INIT
 #endif
    HDR_FILES       endLib.h
#endif /* _WRS_CONFIG_VXBUS_LEGACY */
    MODULES         endLib.o
    _CHILDREN       FOLDER_NET_END_LIB
    CFG_PARAMS      END_NET_JOB_INIT_STRING
}

Component INCLUDE_END_ETHER_HDR {
    NAME        M_BLK ethernet/802.3 header build and parse
    SYNOPSIS    M_BLK ethernet/802.3 header build and parse
    PROTOTYPE   void endEtherHdrInit (void);
    INIT_RTN    endEtherHdrInit ();
    MODULES     endEtherHdr.o
    _CHILDREN   FOLDER_NET_END_LIB
}

Component INCLUDE_END_POLLED_STATS {
    NAME        END driver polled statistics support
    SYNOPSIS    Enable polled END driver stats gathering
    CFG_PARAMS  END_POLL_STATS_ROUTINE_HOOK
    _CHILDREN   FOLDER_NET_END_LIB
}

Parameter END_POLL_STATS_ROUTINE_HOOK {
    NAME        Polled stats update routine
    SYNOPSIS    Function pointer for reading END driver stats
    TYPE        FUNCPTR
    DEFAULT     m2PollStatsIfPoll
}

Parameter END_NET_JOB_INIT_STRING {
    NAME	Per-interface job queue initialization string
    SYNOPSIS	This string is used in a multi-threaded stack configuration to specify which network task work queue should be used by a given END interface (can be overridden at runtime using the muxEndQnumSet() API)
    TYPE	char *
    DEFAULT	"dummy0:0|dummy1:1"
}

Component INCLUDE_ETHERNET {
	NAME		Ethernet multicast library support
	SYNOPSIS	Ethernet multicast library support
	HDR_FILES	etherMultiLib.h
	MODULES		etherMultiLib.o
	LINK_SYMS	etherMultiAdd
	_CHILDREN	FOLDER_NET_END_LIB
}
