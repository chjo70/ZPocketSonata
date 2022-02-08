/* 00comp_net_mib2_tcp.cdf - Component configuration file */

/* Copyright 2001 - 2002 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,13sep10,h_x  CQ: WIND00141200
01d,12apr02,zhr  Migrated to ipnet
01c,13may03,ppp  removed inclusion of adv_net.h
01b,01oct02,ham  updated NAME
01a,18jun02,ism  created based on Synth CDF
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Component INCLUDE_MIB2_TCP
        {
        NAME            MIB2 TCP Management APIs
        SYNOPSIS        MIB2 Variables for TCP
        INIT_RTN        m2TcpInit ();
        MODULES         m2TcpLib.o
        }
#endif
