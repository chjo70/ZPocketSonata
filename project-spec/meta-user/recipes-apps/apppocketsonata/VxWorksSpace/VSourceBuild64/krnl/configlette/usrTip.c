/* usrTip.c - initialization code for the tip component */

/*
 * Copyright (c) 2008,2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
21jan14,jpb  Fixed compile error when component that includes shellInOutLibP.h
             is removed (V7COR-2238)
30nov10,jmp  Fixed build warnings (CQ:WIND00243794).
26sep08,v_r  INCLUDE_INETLIB is mandatory to use inet_addr (this fixes a
             BSP build error).
16sep08,v_r  Written. Contains init code for the tip component, allow
	     decoupling from shell and network (CQ:WIND00134830).
*/

/*
DESCRIPTION
This file is used to initialize the VxWorks tip (serial line management)
library.

\NOMANUAL
*/

#include <vsbConfig.h>
#include <string.h>
#include <private/tipLibP.h>
#include <arpa/inet.h>
#include <sockLib.h>
#ifdef _WRS_CONFIG_SHELL
#ifdef  INCLUDE_SHELL
#include <private/shellInOutLibP.h>
#endif  /* INCLUDE_SHELL */
#endif /* _WRS_CONFIG_SHELL */

/******************************************************************************
*
* usrTipInit - initialize the tip component
*
* This routine initializes the tip component. Of particular interest are the
* various function pointers used to decouple it from both the shell and the
* network (as the tool should be usable without any of them).
*
* \NOMANUAL
*/

void usrTipInit 
    (
    char * configString,
    char * escapeCharStr
    )
    {
    TIP_FUNC_PTR tipFuncPtrs;

    /* Set all structure fields to NULL */

    memset ((void *) &tipFuncPtrs, 0, sizeof (TIP_FUNC_PTR));

#ifdef INCLUDE_SHELL
    /* Setup shell function pointers */
    
    tipFuncPtrs.shellFromTaskGetPtr  = shellFromTaskGet;
    tipFuncPtrs.shellHookSetPtr      = shellInOutInputHookSet;
    tipFuncPtrs.shellHookUnsetPtr    = shellInOutInputHookUnset;
#endif /* INCLUDE_SHELL */

#if defined (INCLUDE_NETWORK) && defined (INCLUDE_INETLIB)
    /* 
     * Setup network function pointers. Note that the name resolver could be
     * left out from the network config so we have to handle it separately.
     * INCLUDE_INETLIB is mandatory to use inet_addr.
     */

#ifdef INCLUDE_IPWRAP_GETHOSTBYNAME
    tipFuncPtrs.getHostByNamePtr     = gethostbyname;
    tipFuncPtrs.hostEntFreePtr       = hostentFree;
#endif /* INCLUDE_IPWRAP_GETHOSTBYNAME */

    tipFuncPtrs.inetAddrPtr          = inet_addr;
    tipFuncPtrs.socketPtr            = socket;
    tipFuncPtrs.connectPtr           = connect;
    tipFuncPtrs.setSockOptPtr        = setsockopt;
#endif /* INCLUDE_NETWORK && INCLUDE_INETLIB */

    /* Call library init routine */

    tipLibInit (configString, escapeCharStr, &tipFuncPtrs);
    }
