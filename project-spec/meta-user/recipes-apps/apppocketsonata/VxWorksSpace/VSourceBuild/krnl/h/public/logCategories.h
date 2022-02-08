/* logCategories.h */

/*
 * Copyright (c) 2004-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
01g,20sep10,h_x  Add a new marco (QOS) for log.
01f,06sep06,kch  Cleanup for IPNet integration.
01e,08feb06,kch  Added ALTQ log entry.
01d,15jun05,tlu  Add an entry for MIP6
01c,19apr05,rp   merged from comp_wn_ipv6_mld_interim-dev
01b,28oct04,ann  changed default log level for FTP client to 0 (SPR# 103249)
01a,07sep04,dlk  written
*/


/*
 * This header file forms the database of logging facilities used
 * by applLogLib and syslog.h. It is meant to be included multiple
 * times, with varying definitions of the LOG_DB() and LOG_DB_LAST()
 * macros, so it is not protected against multiple inclusion.
 *
 *                      Default   Default
 *      Facility        Dest. FD  Logging Decoration and Level
 *      --------        --------  ------------------------------
 */

LOG_DB (PING_V6,	STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (TELNET,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (TELNETD,	STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (TFTPD,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (TFTP,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (FTP,		STD_OUT,  (_LOG_DEC_DFLT |       0      ))
LOG_DB (FTPD,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (SYSCTL,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (RLOGIN,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (REMLIB,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (KERN,		KERN_LOG_FD,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (NETDRV,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))
LOG_DB (QOS,		STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))

/* must be last */
LOG_DB_LAST (GENERAL,	STD_OUT,  (_LOG_DEC_DFLT | _LOG_LVL_DFLT))

