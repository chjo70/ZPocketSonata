/* 01timex.cdf - timex components */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history            
--------------------
01a,03sep13,rlp  written
*/

/*
DESCRIPTION
This file is used to initialize the VxWorks utility to measure function
execution time.
*/

Component INCLUDE_TIMEX {
        NAME            timex
        SYNOPSIS        utility to measure function execution time
        MODULES         timexLib.o
        INIT_RTN        timexInit ();
        HDR_FILES       timexLib.h
}
