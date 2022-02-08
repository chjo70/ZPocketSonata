/* usrVxdbg.c - configuration file for VxDBG support */

/*
 * Copyright (c) 2010,2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,23may13,rlp  Added VxDBG exception handling initialization.
01d,13apr10,rlp  Added VxDBG runcontrol component.
01c,25feb10,rlp  Added VxDBG module component.
01b,23feb10,rlp  Installed a hook to remove breakpoints when unloading a
		 DKM (WIND00201223).
01a,29jan10,rlp  Written
*/

/*
DESCRIPTION

This library configures and initializes the VxDBG support
*/

/* Includes */

/******************************************************************************
*
* usrVxdbgInit - configure and initialize the VxDBG support
*
*/

void usrVxdbgInit
    (
    int		priority,
    int		options,
    size_t	stackSize
    )
    {
    vxdbgLibInit ();

    /* Initialize the events support of runtime debug library */

    (void) vxdbgEventLibInit (priority, options, stackSize);

#ifdef	INCLUDE_VXDBG_RUNCTRL
    /* Initialize the exception support of runtime debug library */

    (void) vxdbgExcLibInit ();

    vxdbgRunCtrlLibInit ();
#endif	/* INCLUDE_VXDBG_RUNCTRL */

#ifdef	INCLUDE_VXDBG_MODULE
    vxdbgModuleLibInit ();
#endif	/* INCLUDE_VXDBG_MODULE */
    }

