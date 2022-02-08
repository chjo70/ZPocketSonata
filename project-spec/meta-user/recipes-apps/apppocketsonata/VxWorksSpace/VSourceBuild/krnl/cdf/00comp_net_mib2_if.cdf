/* 00comp_mib2_if.cdf - Component configuration file */

/* Copyright 1984 - 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01n,13sep10,h_x  CQ: WIND00141200
01m,12apr02,zhr  Migrated to ipnet
01l,19sep04,spm  updated virtual stack startup: restored use of published
                 init routine and removed packing/unpacking parameters
01k,12sep03,vvv  updated configlette path
01j,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01i,13may03,ppp  removed inclusion of adv_net.h
01h,01may03,spm  added parameter from Tornado 2.2 CP1 merge
01g,01oct02,ham  updated NAME
01f,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01e,07may01,ham  fixed initialization misorder (SPR #66853). 
01d,04jun00,pad  Addition of PREF_DOMAIN attribute
01c,17apr00,ham  revised.
01b,14jan00,ham  added missing stuffs.
01a,05may99,cym  re-organized.
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Component INCLUDE_MIB2_IF {
	NAME		MIB2 IF Counter Instrumentation
	SYNOPSIS	MIB2 Variables for Interface Layer
	CONFIGLETTES	usrNetM2ifLib.c
        INIT_RTN	usrNetM2IfStart ();
	MODULES		m2IfLib.o 
	CFG_PARAMS	MIB2IF_TRAP_RTN \
                        MIB2IF_TRAP_ARG \
			MIB2IF_LONG_COUNTERS
}

Parameter MIB2IF_TRAP_RTN {
        NAME            Pointer to user trap generator
        SYNOPSIS        Pointer to a user-supplied SNMP trap generator
        TYPE            FUNCPTR
        DEFAULT         NULL
}

Parameter MIB2IF_TRAP_ARG {
        NAME            Pointer to user trap generator argument
        SYNOPSIS        Pointer to a user-supplied SNMP trap generator argument
        TYPE            int
        DEFAULT         NULL
}

Parameter MIB2IF_LONG_COUNTERS {
        NAME            Configuration setting for RFC 2233 statistics
        SYNOPSIS        Enable or disable 64-bit counters from RFC 2233
        TYPE            BOOL
        DEFAULT         FALSE
        }
#endif
