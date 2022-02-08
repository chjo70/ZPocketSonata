/* 10spiBusLib.cdf - Component Definition file for SPI bus library */

/*
 * Copyright (c) 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15jun17,mjn  text updates (F8862)
25mar15,y_f  created. (V7PRO-1908)
*/

Folder FOLDER_BUSLIB_SPI {
    NAME        SPI bus support library 
    SYNOPSIS    This folder contains SPI bus support libraries.
    _CHILDREN   FOLDER_SUBSYSTEM
}

Component INCLUDE_SPI_BUS {
    NAME        SPI bus library
    SYNOPSIS    This component provides the SPI bus library.
    LINK_SYMS   vxbSpiDevXfer
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_BUSLIB_SPI
}
