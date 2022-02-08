/* 00comp_net_mib2_ip.cdf - Component configuration file */

/* Copyright 2001 - 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01i,13sep10,h_x  CQ: WIND00141200
01h,12apr02,zhr  Migrated to ipnet
01g,19sep04,spm  updated virtual stack startup: restored use of published
                 init routine and removed packing/unpacking parameters
01f,12sep03,vvv  updated configlette path
01e,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01d,13may03,ppp  removed inclusion of adv_net.h
01c,01oct02,ham  updated NAME
01b,14jul02,ann  ported to t22
01a,18jun02,ism  created based on Synth CDF
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Component INCLUDE_MIB2_IP
        {
        NAME            MIB2 IP Management APIs
        SYNOPSIS        MIB2 Variables for IP
	CONFIGLETTES	usrNetM2ipLib.c
        INIT_RTN        usrNetM2IpStart ();
        CFG_PARAMS      MIB2IP_MAX_ROUTE_TBL_SIZE
        MODULES         m2IpLib.o
        }

Parameter MIB2IP_MAX_ROUTE_TBL_SIZE {
        NAME            Max size of routing table [obsolete]
        SYNOPSIS        Default size of the MIB-II route table cache
        TYPE            int
        DEFAULT         0
}
#endif
