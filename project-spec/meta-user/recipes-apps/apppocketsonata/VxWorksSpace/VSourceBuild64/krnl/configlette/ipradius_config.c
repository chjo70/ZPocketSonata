/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,17sep10,tlu  Consolidate RADIUS configllete
01d,03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
01c,23nov06,kkz  Removed ipradius_cmd_radiusc_init
01b,22nov06,kch  Refresh with Nov. 15 code drop - added RADIUS_NAS_IDENTIFIER
                 sysvar and updated ipradius_configure().
01a,24sep06,kch  Integrated to VxWorks build mechanism.
*/

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
#include "ipradius_config.h"

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom_cstyle.h"
#include "ipcom_err.h"
#include "ipcom_sysvar.h"
#include "ipcom_shell.h"


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if !defined(WRS_IPNET) && !defined(PRJ_BUILD)
#define INCLUDE_IPRADIUS_CMD
#endif

#ifndef RADIUS_NAS_IDENTIFIER
#define RADIUS_NAS_IDENTIFIER 		"Interpeak example NAS"
#endif


/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

#ifdef INCLUDE_IPRADIUS_CMD
IP_PUBLIC int ipradius_cmd_radiusc(int argc, char **argv);
#endif /* INCLUDE_IPRADIUS_CMD */

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipradius_configure(void);


/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         SYSVAR CONFIGURATION
 *===========================================================================
 */

IP_STATIC IP_CONST Ipcom_sysvar ipradius_conf_sysvar[] =
{
    { "ipradius.nas.identifier", RADIUS_NAS_IDENTIFIER},
	{ IP_NULL, IP_NULL }
};


/*
 ****************************************************************************
 * 9                    PUBLIC FUNCTIONS
 ****************************************************************************
 */


/*
 *===========================================================================
 *                    ipradius_configure
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipradius_configure(void)
{
	/* Initialize IPRADIUS system variables. */
    (void)ipcom_sysvar_setv(ipradius_conf_sysvar, 0);

#ifdef INCLUDE_IPRADIUS_CMD    
    /* Add the radiusc command */
    (void)ipcom_shell_add_cmd("radiusc", "radiusc [command] <modifier...>", "Radius client",
                              ipradius_cmd_radiusc,
                              IPCOM_SHELL_PRIO_SAME, 2048);
#endif /* INCLUDE_IPRADIUS_CMD */

    return IPCOM_SUCCESS;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

