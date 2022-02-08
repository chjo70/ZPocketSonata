/* 40vxbI2cMux.cdf - Component Definition file for I2C  Mux*/

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
23may13,y_y  created
*/

Component       DRV_I2C_PCA954X {
    NAME        PCA954x I2C mux/switch
    SYNOPSIS    This component provides the PCA954x I2C mux/switch driver. Supported chips are the octal bidirectional\
                translating multiplexers controlled by the I2C-bus. The SCL/SDA upstream pair\
                fans out to several downstream pairs, or channels. Only one SCx/SDx channel\
                can be selected at a time, determined by the contents of the programmable control\
                register. The device powers up with Channel 0 connected, allowing immediate\
                communication between the master and downstream devices on that channel.
    MODULES     vxbI2cPca954xMux.o vxbI2cMuxChan.o
    LINK_SYMS   vxbOfI2cPca954xMuxDrv vxbOfI2cMuxChanDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_OTHER
}


