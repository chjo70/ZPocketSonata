/*
 * Copyright (c) 2006-2007, 2009-2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
28jan16,wjf  update version for DHCP support uuid type clientid (US71086)
30Mar15,lzq  Modify file for task priority and debug.V7NET-509 VXW6-43757.
26feb15,ljg  Fix check return defects
20feb15,ed   More robust handling of config file parse errors.
29dec14,ljg  Return when ipcom_sysvar_ext_setv failed.
15dec14,ed   Added DHCPC config file parsing (F2848)
03Aug10,rjq  New file for Networking Configuration VSB restructuring.
04jul09,ggz  Added DHCPC ip address lease time
11oct07,uol  Defect WIND00107491, add DHCP capabilities in bootrom.
22jan07,kch  Added rfc2131_init_delay, rfc2131_exponential_backoff,
             discover_retries and offer_timeout sysvars (WIND00086146).
03jan07,kch  Renamed DHCPC_IFLIST_REQ_OPTS and DHCPC_IFLIST_CLIENT_ID
             macros to DHCPC_IF_REQ_OPTS_LIST and DHCPC_IF_CLIENT_ID_LIST.
01dec06,kch  Updated CVS revision log entry.
13sep06,kch  Refresh with Sept 08, 2006 code drop
28aug06,kch  Update based on Aug 22, 2006 code drop.
07aug06,kch  Added ipdhcpc_conf_sysvar_ext[] to support per-interface
             sysvar configurations.
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
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

#if defined(BOOTAPP_DHCPC_REQ_OPTS)
#undef DHCPC_REQ_OPTS
#define DHCPC_REQ_OPTS BOOTAPP_DHCPC_REQ_OPTS
#endif

#if defined(BOOTAPP_DHCPC_IF_REQ_OPTS_LIST)
#undef DHCPC_IF_REQ_OPTS_LIST
#define DHCPC_IF_REQ_OPTS_LIST BOOTAPP_DHCPC_IF_REQ_OPTS_LIST
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

IMPORT FUNCPTR _func_logMsg;

/*
 ****************************************************************************
 * 6                    LOCAL PROTOTYPES
 ****************************************************************************
 */

IP_PUBLIC Ip_err ipdhcpc_configure(void);

/*
 ****************************************************************************
 * 7                    DATA
 ****************************************************************************
 */

/*
 *===========================================================================
 *                         SYSTEM VARIABLES
 *===========================================================================
 */

/*
 *===========================================================================
 *                         ipdhcpc_conf_sysvar
 *===========================================================================
 * DHCP Client Configuration Variables
 */

IP_CONST Ipcom_sysvar ipdhcpc_conf_sysvar[] =
{
#if defined(IP_WB_BUILD)
    /* DHCP client port (default 68) */
    {"ipdhcpc.client_port", DHCPC_CLIENT_PORT},

    /* DHCP server port (default 67) */
    {"ipdhcpc.server_port", DHCPC_SERVER_PORT},

    /* RFC2131 Initialization Delay identifier                  */
    /* 1 enabled          , 0 disabled                          */
    {"ipdhcpc.rfc2131_init_delay", DHCPC_RFC2131_INIT_DELAY},

    /* RFC2131 Exponential Back-off Delay                       */
    /* 1 enabled, 0 disabled                                    */
    {"ipdhcpc.rfc2131_exponential_backoff", DHCPC_RFC2131_EXP_BACKOFF},

    /* Number of DHCP client retries                            */
    {"ipdhcpc.discover_retries", DHCPC_DISCOVER_RETRIES},

    /* DHCP offer time-out in milliseconds                      */
    {"ipdhcpc.offer_timeout", DHCPC_OFFER_TIMEOUT},
    
    /* DHCP bootp mode                                          */
    /* 1 enabled, 0 disabled                                    */
    {"ipdhcpc.bootp_mode", DHCPC_BOOTP_MODE},

    /* DHCP boot filename                                       */
    {"ipdhcpc.boot_filename", DHCPC_BOOT_FILENAME},    
    
    /* Global server hostname                                   */
    {"ipdhcpc.server_hostname", DHCPC_SERVER_HOSTNAME},    
    {"ipdhcpc.client_identifier_uuid", DHCPC_CLIENT_UUID},
    
    /* Global hostname option                                   */
    {"ipdhcpc.option.hostname", DHCPC_OPTION_HOSTNAME}, 
    
    /* Global netmask option                                    */
    {"ipdhcpc.option.netmask", DHCPC_OPTION_NETMASK}, 
    
    /* IP address lease time option                             */
    {"ipdhcpc.option.lease_time", DHCPC_OPTION_IPADDRESS_LEASE_TIME}, 

    /* Global vendor class identifier option                    */
    {"ipdhcpc.option.vendor_class_id", DHCPC_OPTION_VENDOR_CLASS_ID}, 
    
    /* Global vendor identifying vendor options option          */
    {"ipdhcpc.option.vendor_identifying_vendor_class", DHCPC_OPTION_VI_VENDOR_CLASS}, 
    
    /* Global list of requested DHCP options  */
    {"ipdhcpc.option.requested_options", DHCPC_REQ_OPTS},

    /* Global client identifier */
    {"ipdhcpc.option.client_identifier", DHCPC_CLIENT_ID},
	
    /* Global user specified options */
    {"ipdhcpc.option.user_specified", DHCPC_OPTION_USER_SPECIFIED},
	
    /* Remove existing unicast addresses before negotiation begins */
    {"ipdhcpc.remove_existing_addresses", DHCPC_REMOVE_EXISTING_ADDRESSES},
	
    /* Remove negotiated addresses from interface when lease expires */
    {"ipdhcpc.remove_leased_address", DHCPC_REMOVE_LEASED_ADDRESS},
	
    /* Disable DHCP on the interface if a static address is manually applied */
    {"ipdhcpc.auto_disable", DHCPC_AUTO_DISABLE},
	
    /* Global DHCP maximum message size */
    {"ipdhcpc.option.max_message_size", DHCPC_OPTION_MAX_MESSAGE_SIZE},
	
    /* Global Time To Live (TTL) for DHCP packets */
    {"ipdhcpc.ttl", DHCPC_TTL},
    /* Set the priority of the task */
    {"ipdhcpc.priority", DHCPC_TASK_PRIORITY},

	/*enable debugging or not*/
   	{"ipdhcpc.debug", DHCPC_DEBUG_ENABLE},

    /* Set the value of flag field:broadcast bit */
    {"ipdhcpc.flags.bit.broadcast", DHCPC_FLAGS_BIT_BROADCAST},
	
    
    /*
     * Interface specific list of sysvar configurations are defined in
     * ipdhcpc_conf_sysvar_ext[]
     */
#endif
    { IP_NULL, IP_NULL }
};

#if defined(IP_WB_BUILD)
/* Interface specific list configurations */
IP_CONST Ipcom_sysvar_ext ipdhcpc_conf_sysvar_ext[] =
{
    /* 
     * Interface specific list of requested DHCP options with interface name
     * followed by comma separated list of DHCP options numbers that the
     * DHCP client wants the server to provide in the format <ifparam>=<opts>.
     * Each pair of <ifparam>=<opts> is semicolon separated, e.g.
     * "eth0=1,2,3,4;eth1=2,3,4,5".
     */
    {"ipdhcpc", "option.requested_options", DHCPC_IF_REQ_OPTS_LIST},
    
    /* 
     * Interface specific client identifier with a string of characters that
     * the DHCP client wants the server to identify it by in the format
     * <ifparam>=<id>. Each pair of <ifparam>=<id> is semicolon separated, e.g.
     * "eth0=my_red_computer_eth0" or 
     * "eth0=my_red_computer_eth0;eth1=my_blue_computer_eth1".
     */
    {"ipdhcpc", "option.client_identifier", DHCPC_IF_CLIENT_ID_LIST},


    /* Interfaces that only receive information 
     * list eth0=enable, or eth0=enable;eth1=enable*/
    {"ipdhcpc.if", "information_only", DHCPC_IF_INFORMATION_ONLY_LIST},
    
    { IP_NULL, IP_NULL, IP_NULL }
};
#endif

/*
 ****************************************************************************
 * 8                    STATIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                   GLOBAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipdhcpc_configure
 *===========================================================================
 * Description: Configure DHCP client.
 * Parameters:
 * Returns:
 *
 */
IP_PUBLIC Ip_err
ipdhcpc_configure(void)
{
    Ip_err ret;

    ret = ipcom_sysvar_setv(ipdhcpc_conf_sysvar, 0);

#if defined(IP_WB_BUILD)
    if (ret == IPCOM_SUCCESS)
    {
        /* now configure the interface-specific sysvars */
        ret = ipcom_sysvar_ext_setv (ipdhcpc_conf_sysvar_ext, 0);
        if(ret != IPCOM_SUCCESS)
            return ret;
    }
#endif

  /* If there is a config file, process it */
    if (strlen(DHCPC_CFGFILE) != 0)
        {
        int rval;
        rval = ipcom_cfgfile_parse(DHCPC_CFGFILE, ipdhcpc_conf_sysvar,
               ipdhcpc_conf_sysvar_ext);
        if (rval != 0)
            {
            if (_func_logMsg)
                {
                char msg[100];
                (void)snprintf(msg, 100, CONFIG_FILE_LOGMSG, DHCPC_CFGFILE, errno);
                _func_logMsg(msg, 0,0,0,0,0,0);
                }
            }
           return(rval);
        }

    return IPCOM_SUCCESS;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
