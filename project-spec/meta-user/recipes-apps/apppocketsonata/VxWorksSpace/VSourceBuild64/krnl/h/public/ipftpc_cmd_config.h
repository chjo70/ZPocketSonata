/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPFTPC_CMD_CONFIG_H
#define IPFTPC_CMD_CONFIG_H

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

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/* Test system requires 'IPFTPS_USE_TEST' */
#ifdef IPTESTENGINE
#if !defined(IPFTPC_USE_TEST)
#define IPFTPC_USE_TEST
#endif
#endif

/* Command buffer size */
#define IPFTPC_CMDBUFSIZE IP_PATH_MAX

/* Max no of arguments for FTP command */
#define IPFTPC_MAX_ARGS 10

/* Max length of username and password */
#define IPFTPC_MAX_USERNAME 32
#define IPFTPC_MAX_PASSWORD 32

/* Argument delimiters */
#define IPFTPC_WHITESPACE " \t\r\n"

/* Version */
#define IPFTPC_VERSIONSTR "1.1.3"

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
