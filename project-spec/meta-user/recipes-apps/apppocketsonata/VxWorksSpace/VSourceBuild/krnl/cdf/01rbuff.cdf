/* 01rbuff.cdf - Kernel Ring Buffer components */

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
01a,07jul13,wzc  Create.

DESCRIPTION

This file contains the definition for the ring buffer components.
*/

Component INCLUDE_RBUFF {
    NAME        rBuff library
    SYNOPSIS    System Viewer ring of buffers for event logging
    MODULES     rBuffLib.o
    INIT_RTN    rBuffLibInit ();
        CFG_PARAMS      WV_RBUFF_MGR_PRIORITY
    HDR_FILES   rBuffLib.h
    INCLUDE_WHEN    INCLUDE_WINDVIEW
}

Parameter WV_RBUFF_MGR_PRIORITY {
    NAME        rBuff manager priority
    SYNOPSIS    Initial priority of rBuff manager task for System Viewer
    TYPE        int
    DEFAULT     48
}

Component INCLUDE_RBUFF_SHOW {
    NAME        rBuff show routine
    SYNOPSIS    Displays rBuff information and statistics about ring buffer performance. \
			Optional and only available if you include RBUFF.
    MODULES     rBuffShow.o
    INIT_RTN    rBuffShowInit ();
        HDR_FILES       rBuffLib.h
    REQUIRES    INCLUDE_RBUFF
    INCLUDE_WHEN    INCLUDE_RBUFF \
            INCLUDE_SHOW_ROUTINES
}
