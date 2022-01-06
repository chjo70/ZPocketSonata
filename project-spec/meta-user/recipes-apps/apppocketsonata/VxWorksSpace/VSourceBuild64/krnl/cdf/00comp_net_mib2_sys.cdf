/* 00comp_net_mib2_sys.cdf - Component configuration file */

/* Copyright 2001 - 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01j,13sep10,h_x  CQ: WIND00141200
01i,12apr02,zhr  Migrated to ipnet
01h,19sep04,spm  updated virtual stack startup: restored use of published
                 init routine and removed packing/unpacking parameters
01g,28apr04,vvv  modified object id parameters (SPR #94509)
01f,12sep03,vvv  updated configlette path
01e,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01d,07jul03,vvv  fixed typo in component NAME field
01c,13may03,ppp  removed inclusion of adv_net.h
01b,01oct02,ham  updated NAME
01a,18jun02,ism  created based on Synth CDF
*/

#ifdef _WRS_CONFIG_COMPONENT_VXCOMPAT

Component INCLUDE_MIB2_SYSTEM
        {
        NAME            MIB2 SYSTEM Management APIs
        SYNOPSIS        MIB2 variables for the system group
	CONFIGLETTES	usrNetM2sysLib.c
        INIT_RTN        usrNetM2SysStart ();
        CFG_PARAMS      MIB2SYS_DESCR \
                        MIB2SYS_CONTACT \
                        MIB2SYS_LOCATION \
                        MIB2SYS_OID_LEN \
                        MIB2SYS_OID
        MODULES         m2SysLib.o
        }

Parameter MIB2SYS_DESCR {
        NAME            Pointer to MIB-2 sysDescr
        SYNOPSIS        Pointer to MIB-2 sysDescr
        TYPE            string
        DEFAULT         "vxWorks-6.6 Target"  
}

Parameter MIB2SYS_CONTACT {
        NAME            Pointer to MIB-2 sysContact
        SYNOPSIS        Pointer to MIB-2 sysContact
        TYPE            string
        DEFAULT         "Wind River System"  
}

Parameter MIB2SYS_LOCATION {
        NAME            Pointer to MIB-2 sysLocation
        SYNOPSIS        Pointer to MIB-2 sysLocation
        TYPE            string
        DEFAULT         "350 Terry Fox Rd. 200 Ottawa"
}

Parameter MIB2SYS_OID_LEN {
        NAME            Length of MIB-2 ObjectId
        SYNOPSIS        Number of elements in MIB-2 ObjectId
        TYPE            int
        DEFAULT         7 
}

Parameter MIB2SYS_OID {
        NAME            MIB-2 ObjectId
        SYNOPSIS        MIB-2 ObjectId
        TYPE            int
        DEFAULT         { 1,3,6,1,2,1,1 }
}
#endif
