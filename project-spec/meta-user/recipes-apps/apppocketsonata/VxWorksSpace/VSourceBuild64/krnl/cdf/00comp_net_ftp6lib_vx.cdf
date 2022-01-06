/* 00comp_net_ftp6lib.cdf - Component configuration file */

/*
 * Copyright (c) 2002-2006 Wind River Systems, Inc.
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
01e,28nov06,kch  Updated description for INCLUDE_FTP.
01d,22sep06,tkf  Cleaned up component names
01c,14may03,vvv  removed adv_net.h
01b,06jun02,ant  added INIT_RTN ftp6LibInit and CFG_PARAMS FTP6_REPLYTIMEOUT
01a,25jan02,ger  new 

*/

Component INCLUDE_FTP6 {
    NAME        FTP6 Client Backend
    SYNOPSIS    File Transfer Protocol (FTP6) library
    REQUIRES    INCLUDE_IPCOM_USE_INET6
    HDR_FILES   ftp6Lib.h
    INIT_RTN    ftp6LibInit (FTP6_REPLYTIMEOUT);
    CFG_PARAMS  FTP6_REPLYTIMEOUT
    MODULES     ftp6Lib.o
    LINK_SYMS   ftp6Xfer
}

Parameter  FTP6_REPLYTIMEOUT {
        NAME            FTP6_REPLYTIMEOUT 
        SYNOPSIS        value specifies timeout in sec, while waiting for ftp reply from server
        DEFAULT         10
        TYPE            long
}
