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
01h,03Aug10,rjq  New file for Networking Configuration VSB restructuring.
01g,04sep09,h_s  Fix the callback compile error when using gnu.
01f,02oct09,spw  Declare option, reply callback only if param not null.
01e,02dec08,spw  Fix WIND00146283 and add REPLY_CB_EVENT_OFFER case
01d,04jun08,spw  Change Syslog facility, cleanup
01c,11oct07,uol  Defect WIND00107491, add DHCP capabilities in bootrom.
01b,03jan07,kch  Updated CVS revision log entry for Jan 03 code drop.
01a,11dec06,kch  Integrated to VxWorks build infrastructure.
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

#include "ipdhcpc_config.h"
#include "ipcom_config.h"

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef IPCOM_USE_CLIB_PROTO
#undef IPCOM_USE_CLIB_PROTO
#endif
#include <ipcom_type.h>
#include <ipcom_cstyle.h>
#include <ipcom_err.h>
#include <ipcom_shell.h>
#include <ipcom_syslog.h>
#include <ipdhcpc.h>


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if defined(IP_WB_BUILD) || defined(INCLUDE_BOOT_DHCPC)
IP_EXTERN FUNCPTR _ipdhcpc_callback_hook;
#endif

/* typedef to make compiler happy... */
typedef Ip_err (*ipdhcpc_option_cb)(Ipdhcpc_handle *handle, Ip_u8 *option);

#if DHCPC_INSTALL_OPTION_CALLBACK_HOOK == TRUE
    /*
     * forward declarations for the user-defined dhcp client callback hooks
     * to satisfy the compiler.
     */
    #ifdef DHCPC_OPTION_CALLBACK_HOOK
    Ip_err DHCPC_OPTION_CALLBACK_HOOK (Ipdhcpc_handle *, Ip_u8 *);
    #endif
#else
    /*
     * DHCPC_OPTION_CALLBACK_HOOK is applicable only if
     * DHCPC_INSTALL_OPTION_CALLBACK_HOOK is set to TRUE. Explicitly re-define
     * these hooks to NULL so that we don't get compiler errors
     */
    #undef DHCPC_OPTION_CALLBACK_HOOK
    #define DHCPC_OPTION_CALLBACK_HOOK IP_NULL
#endif /* DHCPC_INSTALL_OPTION_CALLBACK_HOOK */

#if DHCPC_INSTALL_REPLY_CALLBACK_HOOK == TRUE
    /*
     * forward declarations for the user-defined dhcp client callback hooks
     * to satisfy the compiler.
     */
	#ifdef DHCPC_REPLY_CALLBACK_HOOK
    Ip_err DHCPC_REPLY_CALLBACK_HOOK (Ipdhcpc_handle *, int);
	#endif
#else
    /*
     * DHCPC_REPLY_CALLBACK_HOOK is applicable only if
     * DHCPC_INSTALL_REPLY_CALLBACK_HOOK is set to TRUE. Explicitly re-define
     * these hooks to NULL so that we don't get compiler errors
     */
    #undef DHCPC_REPLY_CALLBACK_HOOK
#endif /* DHCPC_INSTALL_REPLY_CALLBACK_HOOK */


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

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

Ip_err
ipdhcpc_option_default_callback(Ipdhcpc_handle *handle, Ip_u8 *option);


Ip_err
ipdhcpc_reply_default_callback(Ipdhcpc_handle *handle, int event);

/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                    LOCAL FUNCTIONS
 ****************************************************************************
 */

/*
 *****************************************************************************
 *
 * ipdhcpc_option_default_callback - default dhcp client callback routine
 *
 * This is an example implementation of the dhcp client option callback
 * routine. It is called if no dhcp client option callback routine is
 * assigned to the macro DHCPC_OPTION_CALLBACK_HOOK.
 *
 * NOMANUAL
 */
Ip_err
ipdhcpc_option_default_callback(Ipdhcpc_handle *handle, Ip_u8 *option)
{
    (void)handle;

    switch (*option)
    {
    case IPDHCPC_OPTCODE_VENDOR_ENCAPSULATED_OPTIONS:
        break;
    default:
        break;
    }

    /* Let IPDHCPC act on option */
    return IP_TRUE;
}



/*
 *****************************************************************************
 *
 * ipdhcpc_reply_default_callback - default dhcp client callback routine
 *
 * This is an example implementation of the dhcp client reply callback
 * routine. It is called if no dhcp client option callback routine is
 * assigned to the macro DHCPC_REPLY_CALLBACK_HOOK.
 *
 * NOMANUAL
 */

Ip_err
ipdhcpc_reply_default_callback(Ipdhcpc_handle *handle, int event)
{

    /* Informational only in this implementation. */

    if (handle == IP_NULL)
    	goto fail;

    switch(event)
    {
    case IPDHCPC_REPLY_CB_EVENT_OFFER:

        break;

    case IPDHCPC_REPLY_CB_EVENT_ACK:

        break;
    
    default:
        break;
    }

    return IPCOM_SUCCESS;

fail:
   return IPCOM_ERR_FAILED;
}


/*****************************************************************************
 *
 * ipdhcpc_option_callback - dhcp client option callback routine
 *
 * This routine called once for each option prior to IPDHCPC is acting on the
 * option, i.e. this callback can be used to change the contents of the DHCP
 * server reply (caution!)
 *
 * .IP <option>
 * Pointer to start of option, i.e. option[0] = Code; option[1] = Len;
 * option[2-i] = Optional option data
 * .IP <handle>
 * Pointer to request handle
 *
 * RETURNS:
 * IP_TRUE to let IPDHCPC act on the option (recommended) or IP_FALSE if
 * option should be ignored by IPDHCPC.
 *
 * NOMANUAL
 */
IP_PUBLIC Ip_err
ipdhcpc_option_callback(Ipdhcpc_handle *handle, Ip_u8 *option)
{
    ipdhcpc_option_cb dhcpc_cb;
	/*eliminate warning when compiling with gnu*/
#if defined(IP_WB_BUILD) || defined(INCLUDE_BOOT_DHCPC)
    dhcpc_cb = (NULL!=DHCPC_OPTION_CALLBACK_HOOK) ? DHCPC_OPTION_CALLBACK_HOOK :
               _ipdhcpc_callback_hook ? _ipdhcpc_callback_hook :
               ipdhcpc_option_default_callback;
#else
    dhcpc_cb = ipdhcpc_option_default_callback;
#endif

    return dhcpc_cb(handle, option);
}

/*****************************************************************************
 *
 * ipdhcpc_reply_callback - dhcp client reply callback routine
 *
 * this callback can be used to change the contents of the DHCP
 * server reply (caution!)
 *
 * .IP <handle>
 * Pointer to ipdhcpc handle object, containing, i.e. option[0] = Code; option[1] = Len;
 * option[2-i] = Optional option data
 *
 * .IP <event>
 * The reply type (ACK, NACK, etc)
 *
 * RETURNS:
 * IPCOM_SUCCESS to let IPDHCPC act on the reply (recommended) or !IPCOM_SUCCESS if
 * reply should be declined by IPDHCPC.
 *
 * NOMANUAL
 */
IP_PUBLIC Ip_err
ipdhcpc_reply_callback(Ipdhcpc_handle *handle, int event)
{
    Ipdhcpc_reply_cb dhcpc_cb;
    /*eliminate warning when compiling with gnu*/
#if defined(IP_WB_BUILD) && defined (DHCPC_REPLY_CALLBACK_HOOK)
    dhcpc_cb = DHCPC_REPLY_CALLBACK_HOOK;
#else
    dhcpc_cb = ipdhcpc_reply_default_callback;
#endif
    if(dhcpc_cb != IP_NULL)
        return dhcpc_cb(handle, event);
    else
        return IPCOM_SUCCESS;
}


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
