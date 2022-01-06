/* sntpsLib.h - SNTP server backward-compatible APIs library */

/*
 * Copyright (c) 1997-2013 Wind River Systems, Inc.
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
01b,13sep13,rjq  Fix for WIND00431901.
01a,13oct09,rjq  written

*/

#ifndef __INCsntpsh
#define __INCsntpsh

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Public header file of SNTP server APIs.
 */

/*
DESCRIPTION
This library contains the backward-compatible APIs provided by the WindRiver SNTP server.
INCLUDE FILES: ipcom_type.h, ipcom_time.h
*/


/* defines */
#define S_sntpsLib_INVALID_PARAMETER         (M_sntpsLib | 1)




#ifdef __cplusplus
extern "C" {
#endif


/* Values for "request" parameter to clock hook routine. */
#define IPSNTPS_ID 		1
#define IPSNTPS_RESOLUTION 	2
#define IPSNTPS_TIME 		3

typedef struct sntpsTimeData
{
    ULONG seconds;
    ULONG fraction;
} SNTP_TIMESTAMP;

IMPORT int ipsntpsGetTime(Ip_u32 *sec, Ip_u32 *frac);


/*******************************************************************************
*
* sntpsClockSet - assign a routine to access the reference clock
*
* This routine installs a hook routine that is called to access the 
* reference clock used by the SNTP server. This hook routine must use the 
* following interface:
* .CS
*     STATUS sntpsClockHook (int request, void *pBuffer);
* .CE 
* The hook routine should copy one of three settings used by the server to
* construct outgoing NTP messages into <pBuffer> according to the value of 
* the <request> parameter.  If the requested setting is available, the 
* installed routine should return OK (or ERROR otherwise).
*
* This routine calls the given hook routine with the <request> parameter 
* set to SNTPS_ID to get the 32-bit reference identifier in the format
* specified in RFC 1769.  It also calls the hook routine with <request> 
* set to SNTPS_RESOLUTION to retrieve a 32-bit value containing the clock 
* resolution in nanoseconds.  That value will be used to determine the 8-bit 
* signed integer indicating the clock precision (according to the format 
* specified in RFC 1769).  Other library routines will set the <request> 
* parameter to SNTPS_TIME to retrieve the current 64-bit NTP timestamp 
* from <pBuffer> in host byte order.  The routine sntpsNsecToFraction() will 
* convert a value in nanoseconds to the format required for the NTP 
* fractional part.
*
* Parameters:
* \is
* \i <pClockHookRtn>
* A pointer to the new interface to reference clock.
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
STATUS sntpsClockSet
(
	FUNCPTR	 pClockHookRtn
);

/*******************************************************************************
*
* sntpsNsecToFraction - convert portions of a second to NTP format
*
* This routine is provided for convenience in fulfilling an SNTPS_TIME request
* to the clock hook.  It converts a value in nanoseconds to the fractional part 
* of the NTP timestamp format.  The routine is not designed to convert 
* non-normalized values greater than or equal to one second.  Although the NTP 
* time format provides a precision of about 200 pico-seconds, rounding errors 
* in the conversion process decrease the accuracy as the input value increases.
* In the worst case, only the 24 most significant bits are valid, which reduces
* the precision to tenths of a micro-second.
*
* INTERNAL
* Floating-point calculations can't be used because some boards (notably
* the SPARC architectures) disable software floating point by default to
* speed up context switching. These boards abort with an exception when
* floating point operations are encountered.
*
* Parameters:
* \is
* \i <nsecs>
* nanoseconds to convert to binary fraction.
* \ie
*
* RETURNS: Value for NTP fractional part in host-byte order.
*
* ERRNO:
*/
ULONG sntpsNsecToFraction
(
	ULONG nsecs
);


#ifdef __cplusplus
}
#endif

#endif /* __INCsntpsh */

