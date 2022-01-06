/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_H_H
#define IPCOM_H_H

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

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom_type.h"
#include "ipcom_cstyle.h"
#include "ipcom_syslog.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if !defined(IPCOM_SYSLOG_PRIORITY)
#define IPCOM_SYSLOG_PRIORITY    IPCOM_SYSLOG_IPCOM_PRIORITY
#endif
#if !defined(IPCOM_SYSLOG_FACILITY)
#define IPCOM_SYSLOG_FACILITY    IPCOM_LOG_IPCOM
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

/*
 *===========================================================================
 *                         ipcom_create
 *===========================================================================
 * Description:  Port specific start of IPCOM.
 *               Should call ipcom_start() after initializing port.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipcom_create(void);


/*
 *===========================================================================
 *                         ipcom_start
 *===========================================================================
 * Description:  Create and start all IPCOM modules and Interpeak products.
 * Parameters:
 * Returns:
 *
 */
IP_GLOBAL Ip_err
ipcom_start(void);


/*
 *===========================================================================
 *                         ipcom_usr_create
 *===========================================================================
 * Description:  User specific start of IPCOM.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipcom_usr_create(void);


#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
