/* 40vxbPpcIntCtlr.cdf - PowerPC CPU interrupt controller */

/*
 * Copyright (c) 2006-2008, 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
19jul17,mjn  	 Folder restructure (F8862)
01e,15oct13,x_z  removed reference to TGT_DIR and added dependency to
                 VXBUS GEN1.
01d,04jun08,h_k  added vxbPpcIntCtlrIsr.o to MODULES attribute.
01c,15aug07,h_k  converted to library build.
01b,10jan07,pch  update for unified vxbPpcIntCtlr.c
01a,04Dec06,tor  created
*/

#ifdef _WRS_CONFIG_VXBUS_LEGACY 
Component DRV_INTCTLR_PPC {
	NAME		PowerPC Interrupt Controller driver
	SYNOPSIS	PowerPC Interrupt Controller driver
	MODULES		vxbPpcIntCtlr.o \
			    vxbPpcIntCtlrIsr.o
	REQUIRES	INCLUDE_VXBUS \
			    INCLUDE_PLB_BUS
	_CHILDREN   FOLDER_DRIVERS_INTERRUPT
	INIT_RTN	ppcIntCtlrRegister();
	PROTOTYPE	void ppcIntCtlrRegister (void);
    INIT_AFTER  INCLUDE_PLB_BUS
    _INIT_ORDER hardWareInterFaceBusInit
}
#endif /*_WRS_CONFIG_VXBUS_LEGACY */
