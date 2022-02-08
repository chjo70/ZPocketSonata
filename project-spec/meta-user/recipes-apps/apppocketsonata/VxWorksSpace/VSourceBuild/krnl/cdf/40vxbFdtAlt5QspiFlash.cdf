/* 40vxbFdtAlt5QspiFlash.cdf - Component configuration file */

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
15may14,ywu  added QSPI NOR flash support for Altera SOC Gen 5 (US38998)
*/

Component DRV_FDT_ALT5QSPIFLASH {
    NAME            QSPI flash driver for  Altera SOC Gen 5
    SYNOPSIS        QSPI flash driver for Altera SOC Gen 5
    MODULES         vxbFdtAlt5QspiFlash.o
    LINK_SYMS       vxbFdtAlt5QspiFlashDrv
    _INIT_ORDER     usrRoot
    REQUIRES        INCLUDE_VXBUS
    _CHILDREN       FOLDER_FLASH
}

