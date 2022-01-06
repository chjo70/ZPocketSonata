/* ipntp.h - Public API of Wind River NTP */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* 
modification history
-------------------------
20jan16,rjq  Upgrade ntp version to 4.2.8p4. (US71091)
15jun15,rjq  Upgrade ntp version to 4.2.8p2. (V7NET-498)
17sep14,rjq  Support for NTP crypto. (V7NET-430)
*/

#ifndef IPNTP_H
#define IPNTP_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Public header file of NTP.
 */

/*
DESCRIPTION
This library contains the APIs provided by the WindRiver NTP.
INCLUDE FILES: ipcom_type.h, ipcom_time.h
*/


/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */
#include <ipcom_type.h>
#include <ipcom_time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#define IPNTP_MAX_NAME     256
#define IPNTP_MAX_HOSTNAME 512
#define IPNTP_MAX_PASSWORD 256
#define IPNTP_PRIVATE_CERT_TYPE     1
#define IPNTP_TRUSTED_CERT_TYPE     2


/*
 *===========================================================================
 *                         release
 *===========================================================================
 */

#define IPNTP_RELEASE 60600


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

typedef struct Ipntp_key_param_struct
{
    char rndfile[IPNTP_MAX_NAME];              /* The rand filename */
    char local_passwd[IPNTP_MAX_PASSWORD];     /* local private password */
    char export_passwd[IPNTP_MAX_PASSWORD];    /* export IFF or GQ group keys with password */
    char group_name[IPNTP_MAX_HOSTNAME];       /* The group name */
    char subject_name[IPNTP_MAX_NAME];         /* The subject name */
    char certificate[IPNTP_MAX_NAME];          /* The certificate scheme */
    char cipher[IPNTP_MAX_NAME];               /* The privatekey cipher */
    char signkey[8];                           /* generate sign key with RSA or DSA */
    int  imbits;                               /* identity modulus bits, must be 256 to 2048 */
    int  modulus;                              /* modulus, must be 256 to 2048 */
    int  md5key;                               /* generate MD5 keys */
    int  iffpar;                               /* generate IFF parameters */
    int  gqpar;                                /* generate GQ parameters */
    int  mvkey;                                /* generate MV parameters and the number of MV parameters */
    int  update_mvkey;                         /* Update MV keys */
    int  writekey;                             /* Write IFF or GQ identity keys */
    int  hostkey;                              /* generate host key with RSA-MD5 */
    int  certtype;                             /* generated cert type,  PC private cert or trusted cert (TC scheme) */
    int  lifetime;                             /* set certificate lifetime */
}
Ipntp_key_param;


/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
*
* ipntp_changetime - change the current target time 
*
* This function changes the target time with <offset> seconds added.
*
* Parameters:
* \is
* \i <offset>
* offset.
* \ie
*
* RETURNS:\is
* \i 'IPCOM_SUCCESS', or one of the following errors:
* \i 'IPCOM_ERR_FAILED'
* General error.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipntp_changetime(
                                  int offset
                                  );

/*******************************************************************************
*
* ipntp_timediff - get the timediff between (S)NTP server and the target
*
* This function gets the time of the target and query the time of (S)NTP server.
* Then comparte the difference between them.
*
* Parameters:
* \is
* \i <pServerAddr>
* Host name or Internet address of the (S)NTP server.
* \i <timeout>
* Timeout in seconds. Specifies how long the function will wait for a response.
* '-1' means that there is no timeout; the routine can wait forever.
* \i <diff>
* Pointer to time difference in seconds between the target and the server.
* \ie
*
* RETURNS:\is
* \i 'IPCOM_SUCCESS', or one of the following errors:
* \i 'IPCOM_TIMEOUT'
* No response within the timeout period.
* \i 'IPCOM_ERR_INVALID_ARG'
* Invalid argument.
* \i 'IPCOM_ERR_SOCKCALLFAILED'
* A socket call failed.
* \i 'IPCOM_ERR_NO_MEMORY'
* Memory error.
* \i 'IPCOM_ERR_FAILED'
* General error.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipntp_timediff(
                                char * pServerAddr,
                                Ip_s32 timeout,
                                double *diff
                                );

/*******************************************************************************
*
* ipntp_updatetime - read time from specified NTP server and update local time 
*
* This routine reads time from specified NTP server and update local time.
*
* Parameters:
* \is
* \i <pServerAddr>
* Host name or Internet address of the (S)NTP server.
* \i <timeout>
* Timeout in seconds. Specifies how long the function will wait for a response.
* '-1' means that there is no timeout; the routine can wait forever.
* \ie
*
* RETURNS:\is
* \i 'IPCOM_SUCCESS', or one of the following errors:
* \i 'IPCOM_TIMEOUT'
* No response within the timeout period.
* \i 'IPCOM_ERR_INVALID_ARG'
* Invalid argument.
* \i 'IPCOM_ERR_SOCKCALLFAILED'
* A socket call failed.
* \i 'IPCOM_ERR_NO_MEMORY'
* Memory error.
* \i 'IPCOM_ERR_FAILED'
* General error.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipntp_updatetime(
                                  char * pServerAddr,
                                  Ip_s32 timeout
                                  );

/*******************************************************************************
*
* ipntp_querytime - read time from specified NTP server 
*
* This routine reads time from specified NTP server.
*
* Parameters:
* \is
* \i <pServerAddr>
* Host name or Internet address of the (S)NTP server.
* \i <timeout>
* Timeout in seconds. Specifies how long the function will wait for a response.
* '-1' means that there is no timeout; the routine can wait forever.
* \i <tv>
* Pointer to an <Ip_timeval> structure for receiving the time returned. The
* definition of the <Ip_timeval> structure is:
* \cs
* struct Ip_timeval
* {
*     long   tv_sec;         /@ Seconds. @/
*     long   tv_usec;        /@ Microseconds. @/
* };
* \ce
*
* The value returned is relative to January 1, 1970. It can be used to update
* the system\'s local clock.
* \ie
*
* RETURNS:\is
* \i 'IPCOM_SUCCESS', or one of the following errors:
* \i 'IPCOM_TIMEOUT'
* No response within the timeout period.
* \i 'IPCOM_ERR_INVALID_ARG'
* Invalid argument.
* \i 'IPCOM_ERR_SOCKCALLFAILED'
* A socket call failed.
* \i 'IPCOM_ERR_NO_MEMORY'
* Memory error.
* \i 'IPCOM_ERR_FAILED'
* General error.
* \ie
*
* ERRNO:
*/
IP_PUBLIC Ip_err ipntp_querytime(
                                 char * pServerAddr,
                                 Ip_s32 timeout,
                                 struct Ip_timeval *tv
                                 );

#ifdef AUTOKEY
/*******************************************************************************
*
* ipntp_keygen - generates cryptographic data files used by the NTPv4 authentication and identification schemes. 
*
* This routine generates cryptographic data files used by the NTPv4 authentication
* and identification schemes.
*
* Parameters:
* \is
* \i <pathfilename>
* The rand filename with path which will be used.
* \ie
*
* RETURNS:
*
* \NOMANUAL
*/
IP_PUBLIC void ipntp_keygen(char *pathfilename);
#endif

/*
 *===========================================================================
 *                    ipntp_exit_callback
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 * \NOMANUAL
 */
IP_GLOBAL void ipntp_exit_callback(Ip_pid_t pid);

/*
 *===========================================================================
 *                    ipntp_getOptServ
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 * \NOMANUAL
 */
IP_GLOBAL Ip_err ipntp_getOptServ(char * ParamString, const char * progName, int *argc, char *argvloc[], int argvlen);


#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
