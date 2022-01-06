/* 40vxbFslEspi.cdf - Component Definition file for Freescale ESPI */

/*
 * Copyright (c) 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
01a,23may13,y_y  created
*/

Component       DRV_FSL_ESPI {
    NAME        Freescale eSPI controller
    SYNOPSIS    This component provides the driver for the eSPI controller present on many Freescale PPC processors.\
                The controller is capable of acting as a master, and each eSPI module instance\
                usually has four completely independent chipSelect.\
                \
                This driver supports working on interrupt mode, and implements\
                vxbSpiFuncGet method for SPI LIB used, meanwhile, the driver can dynamically\
                switch the SPI mode, frequency and chipSelect according to the device's\
                requirements.

    MODULES     vxbFslEspi.o
    LINK_SYMS   vxbOfFslEspiCtlrDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_BUS
}
