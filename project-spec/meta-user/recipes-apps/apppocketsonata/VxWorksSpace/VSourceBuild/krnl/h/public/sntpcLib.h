/* sntpcLib.h - SNTP client backward-compatible APIs library */

/*
 * Copyright (c) 1997-2006, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
Modification history 
--------------------
05may17,rjq  Add new API sntpcTimeGet_ex (V7NET-1331)
07nov06,kch  Cleanup for IPNet integration.
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
04nov03,rlm  Ran batch header path update for header re-org.
03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
25aug99,cno  Add extern "C" definition (SPR21825)
15jul97,spm  code cleanup, documentation, and integration; entered in
                 source code control
20apr97,kyc  written

*/

#ifndef __INCsntpch
#define __INCsntpch


/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Public header file of SNTP client.
 */

/*
DESCRIPTION
This library contains the backward-compatible APIs provided by the WindRiver SNTP client.
INCLUDE FILES: ipcom_type.h, ipcom_time.h
*/


/* includes */

#include <timers.h>

/* defines */

#define S_sntpcLib_INVALID_PARAMETER         (M_sntpcLib | 1)
#define S_sntpcLib_INVALID_ADDRESS           (M_sntpcLib | 2)
#define S_sntpcLib_TIMEOUT                   (M_sntpcLib | 3)
#define S_sntpcLib_VERSION_UNSUPPORTED       (M_sntpcLib | 4)
#define S_sntpcLib_SERVER_UNSYNC             (M_sntpcLib | 5)

#ifdef __cplusplus
extern "C" {
#endif

/* SNTP extend data retrived from SNTP protocol message in SntpcTimeGet */
typedef struct sntp_extend_data_struct
{
    unsigned char     leapVerMode;
    unsigned char     stratum;                 
    char              poll;
    char              precision;
} SNTP_EXTEND_DATA;

#ifdef _WRS_CONFIG_IPNET_SNTP
/*******************************************************************************
*
* sntpcTimeGet_ex - retrieve the current time from a remote source with 
*                            extended data returned
*
* This routine stores the current time as reported by an SNTP/NTP server in
* the location indicated by <pCurrTime> and stores the SNTP_DATA containing
* leapVerMode, stratum, poll and precision fields of NTP message in <sntpData>.  
* The reported time is first converted to the elapsed time since January 1, 1970, 
* 00:00, GMT, which is the base value used by UNIX systems.  If <pServerAddr> 
* is NULL, the routine listens for messages sent by an SNTP/NTP server in 
* broadcast (mulitcast in case of IPv6) mode.  Otherwise, this routine sends a 
* request to the specified SNTP/NTP server and extracts the reported time from
* the reply.  In either case, an error is returned if no message is received within
* the interval specified by <timeout>.  Typically, SNTP/NTP servers operating 
* in broadcast (mulitcast in case of IPv6) mode send update messages every 64
* to 1024 seconds.  An infinite timeout value is specified by WAIT_FOREVER.
*
* Parameters:
* \is
* \i <pServerAddr>
* A pointer to the server IP address or hostname.
* \i <timeout>
* timeout interval in ticks.
* \i <pCurrTime>
* storage for retrieved time value.
* \i <sntpExtendData>
* storage for retrieved sntp extend data.
* \ie
*
* RETURNS: \is
* \i 'OK'.
* successful.
* \i 'ERROR'
* unsuccessful.
* \ie
*
* ERRNO:
*/

STATUS sntpcTimeGet_ex
(
    char *pServerAddr,
    int timeout,
    struct timespec *pCurrTime,
    SNTP_EXTEND_DATA  *sntpExtendData
);

/*******************************************************************************
*
* sntpcTimeGet - retrieve the current time from a remote source
*
* This routine stores the current time as reported by an SNTP/NTP server in
* the location indicated by <pCurrTime>.  The reported time is first converted
* to the elapsed time since January 1, 1970, 00:00, GMT, which is the base value
* used by UNIX systems.  If <pServerAddr> is NULL, the routine listens for 
* messages sent by an SNTP/NTP server in broadcast (mulitcast in case of IPv6) 
* mode.  Otherwise, this routine sends a request to the specified SNTP/NTP 
* server and extracts the reported time from the reply.  In either case, an 
* error is returned if no message is received within the interval specified 
* by <timeout>.  Typically, SNTP/NTP servers operating in broadcast (mulitcast 
* in case of IPv6) mode send update messages every 64 to 1024 seconds.  An 
* infinite timeout value is specified by WAIT_FOREVER.
*
* Parameters:
* \is
* \i <pServerAddr>
* A pointer to the server IP address or hostname.
* \i <timeout>
* timeout interval in ticks.
* \i <pCurrTime>
* storage for retrieved time value.
* \ie
*
* RETURNS: \is
* \i 'OK'.
* successful.
* \i 'ERROR'
* unsuccessful.
* \ie
*
* ERRNO:
*/

STATUS sntpcTimeGet
(
    char *pServerAddr,
    int timeout,
    struct timespec *pCurrTime
);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCsntpch */

