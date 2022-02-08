/* 10serial.cdf - serial port component description file */

/*
 * Copyright (c) 2013, 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
25apr14,cww  removed unnecessary #ifdef _WRS_CONFIG_VXBUS_LEGACY blocks
28jan14,wap  Adjust previous change so that it only takes effect when
             not using legacy VxBus support
28jan14,wap  Set the initialization order correctly for the INCLUDE_SIO
             component so that it's done at the right time for the new
             style BSPs (must be done after VxBus init).
30dec13,cww  Moved INCLUDE_PC_CONSOLE component to IA layer
	     Removed INCLUDE_CONSOLE
15jan14,x_z  add NUM_TTY for VxBus GEN2.
24oct13,j_l  WIND00440614 - Modify pcConsole.h path for INCLUDE_PC_CONSOLE
16sep13,x_z  created.
*/

Folder FOLDER_SERIAL {
    NAME           Serial port
    SYNOPSIS       This folder contains serial port configuration.
    _CHILDREN      FOLDER_SUBSYSTEM
}

Parameter CONSOLE_TTY {
    NAME           Console serial port
    TYPE           uint
#ifdef _WRS_CONFIG_FDT
    DEFAULT        sysConsolePort
#else /* _WRS_CONFIG_FDT */
    DEFAULT         0
#endif /* !_WRS_CONFIG_FDT */
}

Parameter CONSOLE_BAUD_RATE {
    NAME           Baud rate of console port
    TYPE           uint
#ifdef _WRS_CONFIG_FDT
    DEFAULT        sysConsoleBaudRate
#else /* _WRS_CONFIG_FDT */
    DEFAULT        9600
#endif /* !_WRS_CONFIG_FDT */
}

Parameter NUM_TTY {
     NAME           Number of serial ports
     TYPE           uint
     DEFAULT        2
}

Component INCLUDE_SIO {
    NAME           Serial IO
    SYNOPSIS       This component provides initialization for the Serial I/O component.
    _CHILDREN      FOLDER_SERIAL
    CONFIGLETTES   usrSerial.c
    INIT_RTN       usrSerialInit ();
    INIT_AFTER     INCLUDE_VXBUS
    INIT_BEFORE    usrClkInit
    _INIT_ORDER    usrRoot
    CFG_PARAMS     NUM_TTY CONSOLE_TTY CONSOLE_BAUD_RATE
    HDR_FILES      string.h ttyLib.h ioLib.h
    REQUIRES       INCLUDE_TTY_DEV
}

