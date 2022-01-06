/* 01spy.cdf - spy components */

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
This file is used to initialize the VxWorks utility to measure per-task CPU
utilization.
*/

Component INCLUDE_SPY {
        NAME            spy
        SYNOPSIS        utility to measure per-task CPU utilization
        MODULES         spyLib.o
        INIT_RTN        spyLibInit (SPY_TASKS_MAX);
        REQUIRES        INCLUDE_AUX_CLK
        HDR_FILES       spyLib.h
        CFG_PARAMS      SPY_TASKS_MAX
}

Parameter SPY_TASKS_MAX {
        NAME            Number of tasks to spy
        SYNOPSIS        Maximun number of taks that can be spied
        TYPE            int
        DEFAULT         200
}
