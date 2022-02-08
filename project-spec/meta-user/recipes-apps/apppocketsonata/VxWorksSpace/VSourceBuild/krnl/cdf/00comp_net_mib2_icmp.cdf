/* 00comp_net_mib2_icmp.cdf - Component configuration file */

/* Copyright 2001 - 2002 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,13sep10,h_x  CQ: WIND00141200
01e,12apr02,zhr  Migrated to ipnet
01d,13may03,ppp  removed inclusion of adv_net.h
01c,01oct02,ham  updated NAME
01b,14jul02,ann  ported to t22
01a,18Jun01,ism  created based on Synth CDF
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Component INCLUDE_MIB2_ICMP
        {
        NAME            MIB2 ICMP Management APIs
        SYNOPSIS        MIB2 Variables for ICMP
        INIT_RTN        m2IcmpInit ();
        MODULES         m2IcmpLib.o
        }
#endif
