/* 10comp_utf.cdf - Unicode Character Set component */

/*
 * Copyright 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17feb14,ghs  move to FOLDER_UTILITIES
24jan14,ghs  create
*/

/*
DESCRIPTION
This file contains the description for the Unicode Character Set component.
*/

Component INCLUDE_UTF 
    {
    NAME            Unicode Character Set
    SYNOPSIS        Unicode Character Set
    MODULES         utfLib.o
    HDR_FILES       utfLib.h
    INIT_RTN        utfLibInit();
    _CHILDREN       FOLDER_UTILITIES
    }

