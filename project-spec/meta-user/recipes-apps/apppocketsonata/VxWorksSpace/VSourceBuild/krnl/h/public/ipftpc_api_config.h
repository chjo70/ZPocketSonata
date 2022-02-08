/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPFTPC_API_CONFIG_H
#define IPFTPC_API_CONFIG_H

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

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Define this to enable verbatim console output */
/*#define IPFTPC_USE_VERBATIM_CONOUT*/

/* Define this to remove partially transferred files */
/*#define IPFTPC_USE_REMOVE_FILE_ON_ERROR*/
  
/* Data transfer buffer size */    
#define IPFTPC_DATABUFSIZE 4096

/* FTP command buffer size */    
#define IPFTPC_SINBUFSIZE 1024

/* Max no of simultaneous sessions */
#define IPFTPC_MAX_SESSIONS 8

/* Max no of arguments for FTP command */
#define IPFTPC_MAX_ARGS 10

/* Argument delimiters */
#define IPFTPC_DELIMITERS " ,|\r\n"

/* Directory path separators */
#define IPFTPC_DIRSEP "/\\"

/* Timeout when sending data to socket */
#define IPFTPC_SEND_TIMEOUT 30

/* Timeout when receiving data to socket */
#define IPFTPC_RECEIVE_TIMEOUT 30

/* Attempts to bind data socket when using random ports */
#define IPFTPC_BIND_ATTEMPTS 5

/* Version */
#define IPFTPC_VERSION_API 1

/* Transport protocol for FTPC */
#undef IPFTPC_USE_SCTP

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

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
