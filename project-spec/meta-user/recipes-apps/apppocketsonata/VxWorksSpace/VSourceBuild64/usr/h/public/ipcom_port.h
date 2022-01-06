/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_PORT_H
#define IPCOM_PORT_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Interpeak VxWorks port.
 */


/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"
#include "ipcom_vx32.h"


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

/*
 *===========================================================================
 *                         Ipcom_ipc
 *===========================================================================
 * typedef struct Ipcom_ipc
 * {
 *     Ip_u32     magic;
 *     Ip_pid_t   peer_pid;
 * }
 * Ipcom_ipc;
 */
#define IPCOM_IPC_TYPE_SIZE   2


/*
 *===========================================================================
 *                         process declaration
 *===========================================================================
 */

/* Process prototype: */
#ifdef __cplusplus
#define IPCOM_PROCESS(xname) extern "C" void xname(void)
#else
#define IPCOM_PROCESS(xname) void xname(void)
#endif


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

#ifdef _WRS_CONFIG_LP64
# define IP_S32     int
# define IP_U32     unsigned int
# define IP_SIZE_T  unsigned long
# define IP_SSIZE_T long
# define IP_PID_T   Ip_u64
#else
# define IP_S32     long
# define IP_U32     unsigned long
# define IP_SIZE_T  unsigned int
# define IP_SSIZE_T int
# define IP_PID_T   Ip_u32
#endif

#if defined(__RTP__)
# define IP_OFF_T long long
#else
# define IP_OFF_T long
#endif

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
