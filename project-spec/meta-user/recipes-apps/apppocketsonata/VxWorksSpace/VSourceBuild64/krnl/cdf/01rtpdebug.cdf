/* 01rtpdebug.cdf - RTP debug component configuration file */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
29apr15,elp  created (V7COR-2668)
*/

Component INCLUDE_RTP_DEBUG_COMMAND {
        NAME            RTP debug command facility
        SYNOPSIS        Allows to send commands to perform operations in a RTP context
        INIT_RTN        rtpDbgCmdLibInit ();
        HDR_FILES       private/rtpDbgCmdLibP.h
        _CHILDREN       FOLDER_NOT_VISIBLE
        INCLUDE_WHEN    INCLUDE_RTP INCLUDE_SHELL
        REQUIRES        INCLUDE_RTP
}
