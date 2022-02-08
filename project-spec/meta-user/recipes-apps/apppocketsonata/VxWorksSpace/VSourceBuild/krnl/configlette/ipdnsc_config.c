/*
 * Copyright (c) 2006-2007, 2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
26feb15,ljg  Fix check return defects
20feb15,ed   More robust handling of config file parse errors.
19Nov14,ed   Added capability to read config params from a file (F2848)
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
11sep07,dlk  Change parameter names for tertiary and quaternary name
             servers to match those used in 00comp_ipnet_apps.cdf.
28feb07,dlk  Replace _gethostbyname, _gethostbyaddr function pointers
             with reentrant versions _ipcom_gethostbyname_r,
             _ipcom_gethostbyaddr_r.
03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
01dec06,kch  Added support for additional configuration parameters.
13sep06,kch  Refresh with Sept 08, 2006 code drop
28aug06,kch  Corrected ipcom_gethostbyaddr() prototype declaration.
28aug06,tkf  Remove dependency on hostLib.
23aug06,tkf  Add a call to gethostbynameInit() and gethostbynameInit()
03aug06,kch  Renamed INCLUDE_NSLOOKUP_CMD to INCLUDE_IPNSLOOKUP_CMD.
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * DNS client configuration.
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_err.h>
#include <ipcom_sysvar.h>
#include <ipcom_shell.h>
#include <ipcom_sock2.h>
#include <ipcom_cfgfile.h>
#include <logLib.h>

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

#ifndef CONFIG_FILE_LOGMSG
#define CONFIG_FILE_LOGMSG "Error processing configutation file %s. Errno=%d\n"
#endif

/*
 ****************************************************************************
 * 4                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    EXTERN PROTOTYPES
 ****************************************************************************
 */
#if defined(INCLUDE_IPNSLOOKUP_CMD) || !defined(IP_WB_BUILD)
IP_EXTERN int ipdnsc_cmd_nslookup(int argc, char **argv);
#endif

#if	defined(IP_WB_BUILD)
IP_EXTERN FUNCPTR _ipcom_gethostbyname_r;
IP_EXTERN FUNCPTR _ipcom_gethostbyaddr_r;
#endif

IMPORT FUNCPTR _func_logMsg;

/*
 ****************************************************************************
 * 6                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipdnsc_configure(void);


/*
 ****************************************************************************
 * 7                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         ipdnsc_conf_sysvar
 *===========================================================================
 * DNS Client Configuration Variables
 */
IP_CONST Ipcom_sysvar ipdnsc_conf_sysvar[] =
{
	/* DNS server listening port */
	IP_SYSVAR( "ipdnsc.port", "53", DNSC_SERVER_PORT),

	/* Timeout in seconds when waiting for responses to DNS queries */
	IP_SYSVAR( "ipdnsc.timeout", "3", DNSC_TIMEOUT),

	/* Number of retries for DNS queries */
	IP_SYSVAR( "ipdnsc.retries", "1", DNSC_RETRIES),

	/* DNS domain name */
	IP_SYSVAR( "ipdnsc.domainname", "interpeak.se", DNSC_DOMAIN_NAME),

	/* DNS primary name server */
	IP_SYSVAR( "ipdnsc.primaryns", "", DNSC_PRIMARY_NAME_SERVER),

	/* DNS secondary name server */
	IP_SYSVAR( "ipdnsc.secondaryns", "", DNSC_SECONDARY_NAME_SERVER),

	/* DNS tertiary name server */
	IP_SYSVAR( "ipdnsc.tertiaryns",  "", DNSC_TERTIARY_NAME_SERVER),

	/* DNS quaternary name server */
	IP_SYSVAR( "ipdnsc.quaternaryns", "", DNSC_QUATERNARY_NAME_SERVER),

	/* Zone for ipv4 address to name lookups */
	IP_SYSVAR( "ipdnsc.ip4.zone", "in-addr.arpa",  DNSC_IP4_ZONE),

    /* Zone for ipv6 address to name lookups */
    IP_SYSVAR( "ipdnsc.ip6.zone", "ip6.int",  DNSC_IP6_ZONE),     /* RFC1886: "ip6.int" RFC3152: "ip6.arpa" */

	{ IP_NULL, IP_NULL }
};


/*
 ****************************************************************************
 * 8                   STATIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                   GLOBAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                  PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipdnsc_configure
 *===========================================================================
 * Description: Configure DNS client.
 * Parameters:  None.
 * Returns:     IPCOM_SUCCESS or IPCOM_ERR_XXX if failed.
 */
IP_PUBLIC Ip_err
ipdnsc_configure(void)
{
    Ip_err ret;

    ret = ipcom_sysvar_setv(ipdnsc_conf_sysvar, 0);
    if(ret != IPCOM_SUCCESS)
        return ret;

    /* If there is a target resident config file, process it */
    if (strlen(DNSC_CFGFILE) != 0)
        {
        ret = ipcom_cfgfile_parse(DNSC_CFGFILE, ipdnsc_conf_sysvar,
               (Ipcom_sysvar_ext *)0);
        if (ret != 0)
            {
            if (_func_logMsg)
                {
                char msg[100];
                (void)snprintf(msg, 100, CONFIG_FILE_LOGMSG, DNSC_CFGFILE, errno);
                _func_logMsg(msg, 0,0,0,0,0,0);
                }
            return(ret);
            }
        }


#if	defined(IP_WB_BUILD)
    /* Initialize _gethostby* func pointers */
    _ipcom_gethostbyname_r = (FUNCPTR)ipcom_gethostbyname_r;
    _ipcom_gethostbyaddr_r = (FUNCPTR)ipcom_gethostbyaddr_r;
#endif

#if defined(INCLUDE_IPNSLOOKUP_CMD) || !defined(IP_WB_BUILD)
    ret = ipcom_shell_add_cmd("nslookup", "nslookup [ options ] <modifier...>",
                              "Query Internet name servers interactively",
                               ipdnsc_cmd_nslookup,
                               IPCOM_SHELL_PRIO_SAME, IPCOM_PROC_STACK_DEFAULT);
#endif

    return ret;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
