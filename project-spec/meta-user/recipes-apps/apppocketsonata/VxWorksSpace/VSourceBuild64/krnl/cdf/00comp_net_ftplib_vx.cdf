/* 00comp_net_ftplib.cdf - Component configuration file */

/*
 * Copyright (c) 1999-2006 Wind River Systems, Inc.
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
01n,14sep10,h_x CQ:WIND00141200
01m,26dec06,kch  Changed INCLUDE_FTP init routine to usrFtpInit.
01l,28nov06,kch  Updated description for INCLUDE_FTP.
01k,22sep06,tkf  Cleaned up component names.
01j,21jul04,spm  removed extra initialization routine
01i,25mar04,asr  added a parameter for FTP timeout
01h,12sep03,vvv  updated configlette path
01g,19jul02,ppp  taking the updated version from veloce
01f,06jun02,ant  added INIT_RTN ftpLibInit and CFG_PARAMS FTP_REPLYTIMEOUT
01e,25jan02,ger  new firectory of header file
01d,31aug00,sbs  Added missing header file
01c,04jun00,pad  Addition of PREF_DOMAIN attribute
01b,17apr00,ham  revised.
01a,01nov99,ham  wrote.
*/

Component INCLUDE_FTP {
    NAME            FTP Client Backend
    SYNOPSIS        File Transfer Protocol (FTP) library
    REQUIRES        INCLUDE_IPCOM_USE_INET
    HDR_FILES       ftpLib.h private/ftpLibP.h
    CONFIGLETTES    usrFtp.c
    MODULES         ftpLib.o
    LINK_SYMS       ftpCommand
    INIT_RTN        usrFtpInit();
    CFG_PARAMS      FTP_TRANSIENT_MAX_RETRY_COUNT \
                    FTP_TRANSIENT_RETRY_INTERVAL  \
                    FTP_TRANSIENT_FATAL           \
                    FTP_DEBUG_OPTIONS             \
                    FTP_TIMEOUT
}

Parameter FTP_DEBUG_OPTIONS {
    NAME        Debug logging facilities in ftpLib
    SYNOPSIS    Enable various debugging facilities within ftpLib
    TYPE        int
    DEFAULT     0
}

Parameter FTP_TRANSIENT_MAX_RETRY_COUNT {
    NAME        FTP Transient response maximum retry limit
    SYNOPSIS    Maximum number of retries when FTP_TRANSIENT response encountered
    TYPE        int
    DEFAULT     100
}

Parameter FTP_TRANSIENT_RETRY_INTERVAL {
    NAME        Time delay between retries after FTP_TRANSIENT encountered
    SYNOPSIS    The time interval (in clock ticks) between reissuing a command
    TYPE        int
    DEFAULT     0
}

Parameter FTP_TRANSIENT_FATAL {
    NAME        FTP transient fatal function
    SYNOPSIS    Should a transient response be retried or aborted
    DEFAULT     ftpTransientFatal
}

Parameter FTP_TIMEOUT {
    NAME        FTP timeout
    SYNOPSIS    Specifies timeout in sec, while waiting for FTP reply from server
    TYPE        long
    DEFAULT     0
}

