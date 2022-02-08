/* usrSerialSma.c - serial configuration file for Stop Mode Agent support */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21oct14,vhe  Added configuration string 
18aug14,elp  Written
*/

/*
DESCRIPTION

This library initializes serial support for the Stop Mode Agent.
*/

/* Includes */

#include <smaSerialLib.h>

/* Defines */

/* Static */

/******************************************************************************
*
* usrSmaDevInit - configure and initialize the Stop Mode Agent support
*
*/

STATUS usrSmaDevInit 
    (
    char * config       /* configuration string */ 
    )
    {
    return (smaSerialInit (STOP_MODE_AGENT_TTY_CHANNEL,
                           STOP_MODE_AGENT_TTY_BAUD_RATE));
    }
