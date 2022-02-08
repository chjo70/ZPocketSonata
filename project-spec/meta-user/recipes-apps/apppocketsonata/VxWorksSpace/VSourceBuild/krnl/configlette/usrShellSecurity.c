/* usrShellSecurity.c - shell security initialization library */

/* Copyright 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
21feb14,rlp  Written
*/

/*
DESCRIPTION
This configlette initializes the shell security feature.
*/

/* includes */

#include <private/loginLibP.h>
#include <errnoLib.h>
#include <string.h>

/* locals */

LOCAL BOOL usrShellSecurityInitialized = FALSE;

/******************************************************************************
*
* usrShellSecurity - initialize the shell security
*
* This routine initializes the shell security feature. Once this feature is
* activated the shell can be accessed only after successful authentication of
* the user attempting to log-in.
*/

void usrShellSecurity (void)
    {
    /* simply return if it is already initialized */

    if (usrShellSecurityInitialized)
        return;

    usrShellSecurityInitialized = TRUE;

    /*
     * Note that even if network servers handle security on their own based on
     * systemSecurityIsEnabled, we need to call shellLoginInstall() as soon as
     * the shell is included. If we did so only when SHELL_SECURE is set, we
     * would lose the ability to request secure sessions with
     * shellGenericInit().
     * 
     * Note that SHELL_SECURE cannot be set without INCLUDE_SECURITY. We have a
     * warning within usrShell() to that end. It is currently hard to do better
     * given that it is not possible to force-include a component when a
     * parameter is defined in a project build (this can be done by means of
     * usrExtra for the BSP build though).
     */

    if (systemSecurityIsEnabled)
	shellLoginInstall ((SHELL_LOGIN_RTN) loginPrompt2, 0);
    }
