/* ipsntp.h - Wind River SNTP library */

/*
 * Copyright (c) 2006-2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05may17,rjq  Add new API (V7NET-1331)
*/

#ifndef IPSNTP_H
#define IPSNTP_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Public header file of SNTP.
 */

/*
DESCRIPTION
This library contains the APIs provided by the WindRiver SNTP.
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

/*
 *===========================================================================
 *                         release
 *===========================================================================
 */

#define IPSNTP_RELEASE 60600


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/* SNTP packet data retrived from SNTP protocol message */
typedef struct Ipsntp_packet_data_struct
{
    Ip_u8     leapVerMode;
    Ip_u8     stratum;                 
    Ip_u8     poll;
    Ip_u8     precision;
} Ipsntp_packet_data;

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
*
* ipsntp_query_time - query an SNTP server for a time value
*
* This routine queries an SNTP server for a time value. The value can be used
* to update the local time and date. The routine queries the SNTP server until
* a response is received or a timeout expires.
*
* Parameters:
* \is
* \i <server>
* Host name or Internet address of the SNTP server.
* \i <port>
* The server's listening port.
* \i <tmo>
* Timeout in seconds. Specifies how long the function will wait for a response.
* '-1' means that there is no timeout; the routine can wait forever.
* \i <sntp_time>
* Pointer to an <Ip_timespec> structure for receiving the time returned. The
* definition of the <Ip_timespec> structure is:
* \cs
* struct Ip_timespec
* {
*     long   tv_sec;         /@ Seconds. @/
*     long   tv_nsec;        /@ Nanoseconds. @/
* };
* \ce
*
* The value returned is relative to January 1, 1970. It can be used to update
* the system\'s local clock.
* \ie
*
* RETURNS: \is
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
IP_PUBLIC Ip_err ipsntp_query_time
(
    const char *server,
    Ip_u16 port,
    Ip_s32 tmo,
    struct Ip_timespec *sntp_time
);

/*******************************************************************************
*
* ipsntp_query_time_ex - query an SNTP server for a time value and with 
*                                   Ipsntp_packet_data returned
*
* This routine queries an SNTP server for a time value. The value can be used
* to update the local time and date. The routine queries the SNTP server until
* a response is received or a timeout expires. This routine could return the
* Ipsntp_packet_data from server.
*
* Parameters:
* \is
* \i <server>
* Host name or Internet address of the SNTP server.
* \i <port>
* The server's listening port.
* \i <tmo>
* Timeout in seconds. Specifies how long the function will wait for a response.
* '-1' means that there is no timeout; the routine can wait forever.
* \i <sntp_time>
* Pointer to an <Ip_timespec> structure for receiving the time returned. The
* definition of the <Ip_timespec> structure is:
* \cs
* struct Ip_timespec
* {
*     long   tv_sec;         /@ Seconds. @/
*     long   tv_nsec;        /@ Nanoseconds. @/
* };
* \ce
*
* The value returned is relative to January 1, 1970. It can be used to update
* the system\'s local clock.
* \i <pkt_data>
* Including Ipsntp_packet_data returned from server.
* \ie
*
* RETURNS: \is
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
IP_PUBLIC Ip_err ipsntp_query_time_ex
(
    const char *server,
    Ip_u16 port,
    Ip_s32 tmo,
    struct Ip_timespec *sntp_time,
    Ipsntp_packet_data   *pkt_data
);


/*******************************************************************************
*
* ipsntp_wait_time - wait for an SNTP server to send a time value
*
* This function waits for an SNTP server to multicast or
* broadcast the time. The 'maddr' argument must be a valid IPv4
* or IPv6 multicast address or IP_NULL to listen for IPv4 broadcasts
* The 'ifname' argument must specify the interface name on which to join
* the multicast group or IP_NULL if IPv4 broadcast is used.
*
* Parameters:
* \is
* \i <maddr>
* The multicast address to listen on. Set to IP_NULL
* to wait for IPv4 broadcasts.
* \i <ifname>
* The interface name to join the multicast group on.
* \i <port>
* The port to listen on.
* \i <tmo>
* Timeout in seconds. Specifies how long the function will wait for the time.
* '-1' means that there is no timeout; the routine can wait forever.
* \i <sntp_time>
* Pointer to an <Ip_timespec> structure for receiving the time returned. The
* definition of the <Ip_timespec> structure is:
* \cs
* struct Ip_timespec
* {
*     long   tv_sec;         /@ Seconds. @/
*     long   tv_nsec;        /@ Nanoseconds. @/
* };
* \ce
*
* The value returned is relative to January 1, 1970. It can be used to update
* the system\'s local clock.
* \ie
*
* RETURNS: \is
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
IP_PUBLIC Ip_err ipsntp_wait_time
(
    char *maddr,
    char *ifname,
    Ip_u16 port,
    Ip_s32 tmo,
    struct Ip_timespec *sntp_time
);

/*******************************************************************************
*
* ipsntp_wait_time_ex - wait for an SNTP server to send a time value 
*                                  and with Ipsntp_packet_data returned
*
* This function waits for an SNTP server to multicast or
* broadcast the time. The 'maddr' argument must be a valid IPv4
* or IPv6 multicast address or IP_NULL to listen for IPv4 broadcasts
* The 'ifname' argument must specify the interface name on which to join
* the multicast group or IP_NULL if IPv4 broadcast is used. This routine
* could return the Ipsntp_packet_data from server.
*
* Parameters:
* \is
* \i <maddr>
* The multicast address to listen on. Set to IP_NULL
* to wait for IPv4 broadcasts.
* \i <ifname>
* The interface name to join the multicast group on.
* \i <port>
* The port to listen on.
* \i <tmo>
* Timeout in seconds. Specifies how long the function will wait for the time.
* '-1' means that there is no timeout; the routine can wait forever.
* \i <sntp_time>
* Pointer to an <Ip_timespec> structure for receiving the time returned. The
* definition of the <Ip_timespec> structure is:
* \cs
* struct Ip_timespec
* {
*     long   tv_sec;         /@ Seconds. @/
*     long   tv_nsec;        /@ Nanoseconds. @/
* };
* \ce
*
* The value returned is relative to January 1, 1970. It can be used to update
* the system\'s local clock.
* \i <pkt_data>
* Including Ipsntp_packet_data returned from server.
* \ie
*
* RETURNS: \is
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
IP_PUBLIC Ip_err ipsntp_wait_time_ex
(
    char *maddr,
    char *ifname,
    Ip_u16 port,
    Ip_s32 tmo,
    struct Ip_timespec *sntp_time,
    Ipsntp_packet_data *pkt_data
);


/*******************************************************************************
*
* ipsntp_set_reference - set SNTP server reference timestamp
*
* This function sets the reference timestamp and reference identifier
* for the SNTP server. These fields will be copied directly
* into every SNTP server message.
*
* Parameters:
* \is
* \i <ref_time>
* A pointer to a structure with the reference time.
* \i <ref_id>
* Reference identifier.
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC void ipsntp_set_reference
(
    struct Ip_timespec *ref_time,
    Ip_u32 ref_id
);


/*******************************************************************************
*
* ipsntp_register_server_time_hook - register server time function hook
*
* The default is to use the system time returned by gettimeofday() as server time.
* This function registers a pointer to a custom function that will be called instead
* of the default. The time returned by the function will be used by the SNTP server
* in the receive and transmit time stamp fields of the SNTP message.
*
* The server function hook must return 0 for success and -1 for failure and
* must accept two arguments of pointer to unsigned 32-bit type. In the location
* referenced by the first argument the hook must place the number of seconds since
* Jan 1, 1900 and in the other the number of nanoseconds left over.
*
* Parameters:
* \is
* \i <servtime>
* A pointer to a function that returns the current server time.
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC void ipsntp_register_server_time_hook
(
    int (*servtime)(Ip_u32 *, Ip_u32 *)
);

/*******************************************************************************
*
* ipsntp_client_fraction_to_nsec - convert time from the NTP format to POSIX time format
*
* This routine converts the fractional part of the NTP timestamp format to a 
* value in nanoseconds compliant with the POSIX clock.	While the NTP time 
* format provides a precision of about 200 pico-seconds, rounding error in the 
* conversion routine reduces the precision to tenths of a micro-second.
*
* Parameters:
* \is
* \i <fraction>
* NTP time fraction.
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC Ip_u32 ipsntp_client_fraction_to_nsec
(
	Ip_u32 fraction
);

/*******************************************************************************
*
* ipsntp_server_nsec_to_fraction - Convert portions of a second to NTP format
*
* The routine converts a value in nanoseconds to the fractional part of the NTP 
* timestamp format. The routine is not designed to convert non-normalized values
* greater than or equal to one second.  Although the NTP time format provides a
* precision of about 200 pico-seconds, rounding errors in the conversion process
* decrease the accuracy as the input value increases.In the worst case, only the
* 24 most significant bits are valid, which reduces the precision to tenths of 
* a micro-second.
*
* Parameters:
* \is
* \i <nsecs>
* Nanoseconds.
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC Ip_u32 ipsntp_server_nsec_to_fraction
(
	Ip_u32 nsecs
);

/*******************************************************************************
*
* ipsntp_set_precision - set SNTP server time precision
*
* This function sets the time precision for the SNTP server. These fields will be
* copied directly into every SNTP server message.
*
* Parameters:
* \is
* \i <precision>
* Time precision.
* \ie
*
* RETURNS:
*
* ERRNO:
*/
IP_PUBLIC void ipsntp_set_precision
(
    Ip_s32 precision
);



#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
