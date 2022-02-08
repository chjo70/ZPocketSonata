/* usrSyslog.c - syslog configlette file */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24mar15,h_k  created. (F2865)
*/

/*
DESCRIPTION
This file is used to declare a global variable and array for syslog.

NOMANUAL
*/

/* includes */

#include <vxWorks.h>
#include <private/syslogLibP.h>

/* globals */

UINT syslogEarlyMsgNum =  NUM_EARLY_SYSLOG_MSGS;

SYSLOG_MSG syslogEarlyMsgs [NUM_EARLY_SYSLOG_MSGS];
