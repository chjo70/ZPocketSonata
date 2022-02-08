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
17may17,rjq  Add new VIP config parameter FTPS_DATABUF_SIZE. (V7NET-1346)
*/

#ifndef IPFTPS_CONFIG_H
#define IPFTPS_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include <ipcom_config.h>

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Test system requires 'IPFTPS_USE_TEST' */
#ifdef IPTESTENGINE
#if !defined(IPFTPS_USE_TEST)
#define IPFTPS_USE_TEST
#endif
#endif

/* FTP command buffer size */
#define IPFTPS_CMDBUFSIZE 1024

/* Max no of arguments for FTP command */
#define IPFTPS_MAX_ARGS 10

/* Argument delimiters */
#define IPFTPS_DELIMITERS " ,|"

/* PASS cmd argument delimiters */
#define IPFTPS_PASS_DELIMITERS "\r\n"

/* Directory path separators */
#define IPFTPS_DIRSEP "/\\"

/* Attempts to bind data socket when using random ports */
#define IPFTPS_BIND_ATTEMPTS 5

/* Mimic IIS behaviour (send 150 before establishing data connection) */
/*#define IPFTPS_USE_IIS_150*/


/* Transport protocol for FTPS */
#undef IPFTPS_USE_SCTP

#ifdef IPFTP_TLS
#ifdef IPCOM_USE_KEY_DB
#define IPFTPS_USE_PRIVACY
#include <ipcom_key_db.h>
#else
#warning " IPCOM_USE_KEY_DB is not defined  !!"
#endif
#endif

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    FUNCTIONS
 ****************************************************************************
 */


#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
