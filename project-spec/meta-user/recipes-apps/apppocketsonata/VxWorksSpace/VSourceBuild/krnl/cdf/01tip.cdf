/* 01tip.cdf - tip components */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history            
--------------------
24dec15,jmp  Fixed SHELL dependency (V7COR-3911).
17jan15,elp  Fixed SOCKET dependency (V7COR-2457).
29apr14,rlp  Fixed IPNET dependency (V7COR-1073).
03sep13,rlp  Written
*/

/*
DESCRIPTION
This file is used to initialize the VxWorks tip (serial line management)
library.
*/

#if defined(_WRS_CONFIG_IPNET_COREIP) && defined(_WRS_CONFIG_SOCKET) && defined(_WRS_CONFIG_SHELL)
Component INCLUDE_TIP {
        NAME            tip serial line connection utility
        SYNOPSIS        interactive utility to connect to and manage multiple serial lines
        CONFIGLETTES    usrTip.c
        MODULES         tipLib.o
        INIT_RTN        usrTipInit (TIP_CONFIG_STRING, TIP_ESCAPE_CHARACTER);
        HDR_FILES       private/tipLibP.h
        LINK_SYMS       tipStart
        INCLUDE_WHEN    INCLUDE_SHELL
        CFG_PARAMS      TIP_CONFIG_STRING\
                        TIP_ESCAPE_CHARACTER
        HELP            tip
}

Parameter TIP_CONFIG_STRING {
        NAME            Tip global configuration string
        SYNOPSIS        Used to define connection lines attributes
        TYPE            string
        DEFAULT         ""
}

Parameter TIP_ESCAPE_CHARACTER {
        NAME            Tip escape character
        SYNOPSIS        Character toggling command mode
        TYPE            string
        DEFAULT         "~"
}
#endif
