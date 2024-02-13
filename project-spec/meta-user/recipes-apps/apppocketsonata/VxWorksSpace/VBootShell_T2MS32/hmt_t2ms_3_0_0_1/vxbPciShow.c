/* vxbPciShow.c - PCI Show file */

/*
 * Copyright (c) 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
29sep17,cat  This file was taken from SR0500 (March 2017 Vx7 time base) 
             os\drv\vxbus-1.0.5.0\buslib-2.1.3.1 layer to overide the 
             os\drv\vxbus-1.0.5.0\buslib-2.1.3.2 layer file (SR0510)
             since the older version displays the entire PCI tree
             when vxbPciTopoShow() is invoked, and the newer version does not
22oct16,jsp  extend vxbPciFuncBarShow() to output 64-bit BARs (V7PRO-3366)
06feb15,y_y  rewrite the vxbPciTopoShow(). (V7PRO-1661)
18aug14,l_z  fix static analysis issue. (V7PRO-1181)
28mar14,l_z  add vxbPciCtrlShow() to list all PCI controller. (US37630)
25apr14,y_y  remove useless routine.
09apr14,ylu  removed the VXBUS GEN1 function.
07jan14,y_y  code clean
10oct13,x_z  Removed unused FDT header file.
17apr13,j_z  Created, copy from vxbPci.bc
*/

/*
DESCRIPTION
*/

#include <vxWorks.h>
#include <hwif/vxBus.h>
#include <hwif/buslib/vxbPciLib.h>
#include <hwif/buslib/pciDefines.h>
#include <hwif/vxbus/vxbBusType.h>
#include <subsys/int/vxbIntLib.h>

#include <errnoLib.h>
#include <iv.h>
#include <taskLib.h>
#include <string.h>
#include <stdio.h>
#include <logLib.h>
#include <intLib.h>

IMPORT SL_LIST vxbPciCtrlList;
IMPORT BOOL vxbPciCtrlListInited;

/*********************************************************************
*
* latL0s - return string for latency levels
*
* RETURNS: string for latency levels
*
* ERRNO
*/

LOCAL const char *latL0s
    (
    int latVal
    )
    {
      static const char *lat[] =
          {
          "<64ns",
          "<128ns",
          "<256ns",
          "<512ns",
          "<1us",
          "<2us",
          "<4us",
          ">4us"
           };
      return lat[latVal];
    }

/*********************************************************************
*
* latL1 - return string for latency levels
*
* RETURNS: string for latency levels
*
* ERRNO
*/

LOCAL const char *latL1
    (
    int latVal
    )
    {
    static const char *lat[] =
        {
        "<1us",
        "<2us",
        "<4us",
        "<8us",
        "<16us",
        "<32us",
        "<64us",
        ">64us"
        };
    return lat[latVal];
    }

/*********************************************************************
*
* limScale - returns scaling value from negative power
*
* RETURNS:  scaling value from negative power
*
* ERRNO
*/

LOCAL int limScale
    (
    int scaleVal
    )
    {
    static const int scale[4] =
    {
    0,
   -1,
   -2,
   -3
    };
    return scale[scaleVal];
    }

/*********************************************************************
*
* limSpeed - returns string for speed
*
* RETURNS:   string for speed
*
* ERRNO
*/

LOCAL char *linkSpeed
    (
    UINT speed
    )
    {
    switch (speed)
        {
        case 1:
            return "2.5Gb/s";
        case 2:
            return "5.0Gb/s";
        case 4:
            return "8.0Gb/s";
        default:
            return "unknown";
        }
    }

/*********************************************************************
*
* aspm - returns string for latency level
*
* RETURNS:   string for latency level
*
* ERRNO
*/

LOCAL char *aspm
    (
    int val
    )
    {
    switch (val)
        {
        case 1:
            return "L0s";
        case 3:
            return "L0s & L1";
        default:
            return "unknown";
        }
    }

/*********************************************************************
*
* aspmEnable - returns string for which level is enabled
*
* RETURNS:  string for which level is enabled
*
* ERRNO
*/

LOCAL const char *aspmEnable
    (
    int val
    )
    {
    static const char *enab[] =
        {
        "Disabled",
        "L0s",
        "L1",
        "L0s & L1"
        };
    return enab[val];
    }

/*********************************************************************
*
* indicator - returns string for incator state
*
* RETURNS:  string for indicator state
*
* ERRNO
*/

LOCAL const char *indicator
    (
    int val
    )
    {
    static const char *state[] =
        {
        "Unknown",
        "On",
        "Blink",
        "Off"
        };
    return state[val];
    }

/*******************************************************************************
*
* vxbPciConfigInByte - read one byte from the PCI configuration space
*
* This routine reads one byte from the PCI configuration space
*
* RETURNS: OK, or ERROR if this library is not initialized
*
* ERRNO
*
*/

LOCAL STATUS vxbPciConfigInByte
    (
    VXB_DEV_ID busCtrlID,
    UINT8      busNo,    /* bus number */
    UINT8      deviceNo, /* device number */
    UINT8      funcNo,   /* function number */
    int        offset,   /* offset into the configuration space */
    UINT8 *    pData     /* data read from the offset */
    )
    {
    PCI_HARDWARE phard;

    phard.pciBus = busNo;
    phard.pciDev = deviceNo;
    phard.pciFunc = funcNo;

    return VXB_PCI_CFG_READ(busCtrlID, &phard, offset, 1, pData);
    }

/*******************************************************************************
*
* vxbPciConfigInWord - read one word from the PCI configuration space
*
* This routine reads one word from the PCI configuration space
*
* RETURNS: OK, or ERROR if this library is not initialized
*
* ERRNO
*
*/

LOCAL STATUS vxbPciConfigInWord
    (
    VXB_DEV_ID busCtrlID,
    UINT8      busNo,    /* bus number */
    UINT8      deviceNo, /* device number */
    UINT8      funcNo,   /* function number */
    int        offset,     /* offset into the configuration space */
    UINT16 *   pData       /* data read from the offset */
    )
    {
    PCI_HARDWARE phard;

    phard.pciBus = busNo;
    phard.pciDev = deviceNo;
    phard.pciFunc = funcNo;

    return VXB_PCI_CFG_READ(busCtrlID, &phard, offset, 2, pData);
    }

/*******************************************************************************
*
* vxbPciConfigInLong - read one longword from the PCI configuration space
*
* This routine reads one longword from the PCI configuration space
*
* RETURNS: OK, or ERROR if this library is not initialized
*
* ERRNO
*
*/

LOCAL STATUS vxbPciConfigInLong
    (
    VXB_DEV_ID  busCtrlID,
    UINT8      busNo,    /* bus number */
    UINT8      deviceNo, /* device number */
    UINT8      funcNo,   /* function number */
    int         offset,    /* offset into the configuration space */
    UINT32 *    pData      /* data read from the offset */
    )
    {
    PCI_HARDWARE phard;

    phard.pciBus = busNo;
    phard.pciDev = deviceNo;
    phard.pciFunc = funcNo;

    return VXB_PCI_CFG_READ(busCtrlID, &phard, offset, 4, pData);
    }

/*******************************************************************************
*
* vxbPciDheaderPrint - print a PCI device header
*
* This routine prints a PCI device header.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPciDheaderPrint
    (
    PCI_HEADER_DEVICE * pD
    )
    {
    (void) printf ("vendor ID =                   0x%.4x\n", (ushort_t)pD->vendorId);
    (void) printf ("device ID =                   0x%.4x\n", (ushort_t)pD->deviceId);
    (void) printf ("command register =            0x%.4x\n", (ushort_t)pD->command);
    (void) printf ("status register =             0x%.4x\n", (ushort_t)pD->status);
    (void) printf ("revision ID =                 0x%.2x\n", (uchar_t)pD->revisionId);
    (void) printf ("class code =                  0x%.2x\n", (uchar_t)pD->classCode);
    (void) printf ("sub class code =              0x%.2x\n", (uchar_t)pD->subClass);
    (void) printf ("programming interface =       0x%.2x\n", (uchar_t)pD->progIf);
    (void) printf ("cache line =                  0x%.2x\n", (uchar_t)pD->cacheLine);
    (void) printf ("latency time =                0x%.2x\n", (uchar_t)pD->latency);
    (void) printf ("header type =                 0x%.2x\n", (uchar_t)pD->headerType);
    (void) printf ("BIST =                        0x%.2x\n", (uchar_t)pD->bist);
    (void) printf ("base address 0 =              0x%.8x\n", pD->base0);
    (void) printf ("base address 1 =              0x%.8x\n", pD->base1);
    (void) printf ("base address 2 =              0x%.8x\n", pD->base2);
    (void) printf ("base address 3 =              0x%.8x\n", pD->base3);
    (void) printf ("base address 4 =              0x%.8x\n", pD->base4);
    (void) printf ("base address 5 =              0x%.8x\n", pD->base5);
    (void) printf ("cardBus CIS pointer =         0x%.8x\n", pD->cis);
    (void) printf ("sub system vendor ID =        0x%.4x\n", (ushort_t)pD->subVendorId);
    (void) printf ("sub system ID =               0x%.4x\n", (ushort_t)pD->subSystemId);
    (void) printf ("expansion ROM base address =  0x%.8x\n", pD->romBase);
    (void) printf ("interrupt line =              0x%.2x\n", (uchar_t)pD->intLine);
    (void) printf ("interrupt pin =               0x%.2x\n", (uchar_t)pD->intPin);
    (void) printf ("min Grant =                   0x%.2x\n", (uchar_t)pD->minGrant);
    (void) printf ("max Latency =                 0x%.2x\n", (uchar_t)pD->maxLatency);
    }

/*******************************************************************************
*
* vxbPciBheaderPrint - print a PCI-to-PCI bridge header
*
* This routine prints a PCI-to-PCI bridge header.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPciBheaderPrint
    (
    PCI_HEADER_BRIDGE * pB
    )
    {
    (void) printf ("vendor ID =                   0x%.4x\n", (ushort_t)pB->vendorId);
    (void) printf ("device ID =                   0x%.4x\n", (ushort_t)pB->deviceId);
    (void) printf ("command register =            0x%.4x\n", (ushort_t)pB->command);
    (void) printf ("status register =             0x%.4x\n", (ushort_t)pB->status);
    (void) printf ("revision ID =                 0x%.2x\n", (uchar_t)pB->revisionId);
    (void) printf ("class code =                  0x%.2x\n", (uchar_t)pB->classCode);
    (void) printf ("sub class code =              0x%.2x\n", (uchar_t)pB->subClass);
    (void) printf ("programming interface =       0x%.2x\n", (uchar_t)pB->progIf);
    (void) printf ("cache line =                  0x%.2x\n", (uchar_t)pB->cacheLine);
    (void) printf ("latency time =                0x%.2x\n", (uchar_t)pB->latency);
    (void) printf ("header type =                 0x%.2x\n", (uchar_t)pB->headerType);
    (void) printf ("BIST =                        0x%.2x\n", (uchar_t)pB->bist);
    (void) printf ("base address 0 =              0x%.8x\n", pB->base0);
    (void) printf ("base address 1 =              0x%.8x\n", pB->base1);
    (void) printf ("primary bus number =          0x%.2x\n", (uchar_t)pB->priBus);
    (void) printf ("secondary bus number =        0x%.2x\n", (uchar_t)pB->secBus);
    (void) printf ("subordinate bus number =      0x%.2x\n", (uchar_t)pB->subBus);
    (void) printf ("secondary latency timer =     0x%.2x\n", (uchar_t)pB->secLatency);
    (void) printf ("IO base =                     0x%.2x\n", (uchar_t)pB->ioBase);
    (void) printf ("IO limit =                    0x%.2x\n", (uchar_t)pB->ioLimit);
    (void) printf ("secondary status =            0x%.4x\n", (ushort_t)pB->secStatus);
    (void) printf ("memory base =                 0x%.4x\n", (ushort_t)pB->memBase);
    (void) printf ("memory limit =                0x%.4x\n", (ushort_t)pB->memLimit);
    (void) printf ("prefetch memory base =        0x%.4x\n", (ushort_t)pB->preBase);
    (void) printf ("prefetch memory limit =       0x%.4x\n", (ushort_t)pB->preLimit);
    (void) printf ("prefetch memory base upper =  0x%.8x\n", pB->preBaseUpper);
    (void) printf ("prefetch memory limit upper = 0x%.8x\n", pB->preLimitUpper);
    (void) printf ("IO base upper 16 bits =       0x%.4x\n", (ushort_t)pB->ioBaseUpper);
    (void) printf ("IO limit upper 16 bits =      0x%.4x\n", (ushort_t)pB->ioLimitUpper);
    (void) printf ("expansion ROM base address =  0x%.8x\n", pB->romBase);
    (void) printf ("interrupt line =              0x%.2x\n", (uchar_t)pB->intLine);
    (void) printf ("interrupt pin =               0x%.2x\n", (uchar_t)pB->intPin);
    (void) printf ("bridge control =              0x%.4x\n", (ushort_t)pB->control);
    }

/*******************************************************************************
*
* vxbPciCBheaderPrint - print a PCI-to-CardBus bridge header
*
* This routine prints a PCI-to-CardBus bridge header.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPciCBheaderPrint
    (
    PCI_HEADER_CB_BRIDGE * pCB
    )
    {
    (void) printf ("vendor ID =                   0x%.4x\n", (ushort_t)pCB->vendorId);
    (void) printf ("device ID =                   0x%.4x\n", (ushort_t)pCB->deviceId);
    (void) printf ("command register =            0x%.4x\n", (ushort_t)pCB->command);
    (void) printf ("status register =             0x%.4x\n", (ushort_t)pCB->status);
    (void) printf ("revision ID =                 0x%.2x\n", (uchar_t)pCB->revisionId);
    (void) printf ("class code =                  0x%.2x\n", (uchar_t)pCB->classCode);
    (void) printf ("sub class code =              0x%.2x\n", (uchar_t)pCB->subClass);
    (void) printf ("programming interface =       0x%.2x\n", (uchar_t)pCB->progIf);
    (void) printf ("cache line =                  0x%.2x\n", (uchar_t)pCB->cacheLine);
    (void) printf ("latency time =                0x%.2x\n", (uchar_t)pCB->latency);
    (void) printf ("header type =                 0x%.2x\n", (uchar_t)pCB->headerType);
    (void) printf ("BIST =                        0x%.2x\n", (uchar_t)pCB->bist);
    (void) printf ("base address 0 =              0x%.8x\n", pCB->base0);
    (void) printf ("capabilities pointer =        0x%.2x\n", (uchar_t)pCB->capPtr);
    (void) printf ("secondary status =            0x%.4x\n", (ushort_t)pCB->secStatus);
    (void) printf ("primary bus number =          0x%.2x\n", (uchar_t)pCB->priBus);
    (void) printf ("secondary bus number =        0x%.2x\n", (uchar_t)pCB->secBus);
    (void) printf ("subordinate bus number =      0x%.2x\n", (uchar_t)pCB->subBus);
    (void) printf ("secondary latency timer =     0x%.2x\n", (uchar_t)pCB->secLatency);
    (void) printf ("memory base 0 =               0x%.8x\n", pCB->memBase0);
    (void) printf ("memory limit 0 =              0x%.8x\n", pCB->memLimit0);
    (void) printf ("memory base 1 =               0x%.8x\n", pCB->memBase1);
    (void) printf ("memory limit 1 =              0x%.8x\n", pCB->memLimit1);
    (void) printf ("IO base 0 =                   0x%.8x\n", pCB->ioBase0);
    (void) printf ("IO limit 0 =                  0x%.8x\n", pCB->ioLimit0);
    (void) printf ("IO base 1 =                   0x%.8x\n", pCB->ioBase1);
    (void) printf ("IO limit 1 =                  0x%.8x\n", pCB->ioLimit1);
    (void) printf ("interrupt line =              0x%.2x\n", (uchar_t)pCB->intLine);
    (void) printf ("interrupt pin =               0x%.2x\n", (uchar_t)pCB->intPin);
    (void) printf ("bridge control =              0x%.4x\n", (ushort_t)pCB->control);
    (void) printf ("sub system vendor ID =        0x%.4x\n", (ushort_t)pCB->subVendorId);
    (void) printf ("sub system ID =               0x%.4x\n", (ushort_t)pCB->subSystemId);
    (void) printf ("16 bit legacy mode base =     0x%.8x\n", pCB->legacyBase);
    }

/*********************************************************************
*
* vxbPciFuncBarShow - show the values contained in all BARs
*
* This function decodes the value of all BARs on a single
* bus, device, function, and displays the information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPciFuncBarShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    int        numBars     /* number of BARs */
    )
    {
    UINT32 barVal;
    UINT32 barValUpper;
    int space;
    int prefetch;
    int offset;
    int barNo;
    int i;

    if ( busCtrlID == NULL )
        return;

    for (i = 0; i < numBars; ++i)
	{
	barNo = i;
	offset = (barNo * 4) + PCI_CFG_BASE_ADDRESS_0;
	barValUpper = 0;

	(void) vxbPciConfigInLong(busCtrlID,bus, device, function,
			offset, &barVal);

	/* check if BAR implemented */

	if ( barVal == 0 || barVal == 0xffffffff )
	    return;

	if ( ( barVal & 0x01 ) == 0x01 )
	    {
	    (void) printf("\tbar%d in I/O space @ 0x%08x\n",
		    barNo, barVal & (~0x00000001));
	    }
	else
	    {
	    prefetch = ( barVal >> 3 ) & 0x01;
	    space = (barVal >> 1 ) & 0x03;
	    barVal = barVal & ~ 0x0f;
	    if ( space == 0x02 )
		{
		
		/* grab the upper 32-bits */

		(void) vxbPciConfigInLong(busCtrlID,bus, device, function,
				offset + 4, &barValUpper);
		++i;
		}
	    (void) printf("\tbar%d in %s%s mem space @ 0x%08x%08x\n",
		   barNo,
		   prefetch ? "prefetchable " : "",
		   ( space == 0x00 ) ? "32-bit" :
		   ( space == 0x02) ? "64-bit" :
		   "reserved",
		   barValUpper, barVal);
	    }
	}
    }

/*********************************************************************
*
* vxbPciStatusWordShow - show the decoded value of the status word
*
* This routine reads the status word from the specified
* bus, device, function, and displays the information.
*
* RETURNS: OK, always.
*
* ERRNO
*/

LOCAL STATUS vxbPciStatusWordShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function    /* function */
    )
    {
    UINT16 status;

    if(busCtrlID == NULL)
        return(ERROR);

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, PCI_CFG_STATUS, &status);

    (void) printf("\tstatus=0x%04x (", status);

    if ( status & PCI_STATUS_NEW_CAP )
        (void) printf(" CAP");

    if ( status & PCI_STATUS_66_MHZ )
        (void) printf(" 66MHZ");

    if ( status & PCI_STATUS_UDF )
        (void) printf(" UDF");

    if ( status & PCI_STATUS_FAST_BB )
        (void) printf(" FBTB");

    if ( status & PCI_STATUS_DATA_PARITY_ERR )
        (void) printf(" DATA_PARITY_ERR");

    (void) printf(" DEVSEL=%x", ((status & 0x0600) >> 9 ));

    if ( status & PCI_STATUS_TARGET_ABORT_GEN )
        (void) printf(" TGT_ABORT_GEN");

    if ( status & PCI_STATUS_TARGET_ABORT_RCV )
        (void) printf(" TGT_ABORT_RCV");

    if ( status & PCI_STATUS_MASTER_ABORT_RCV )
        (void) printf(" MSTR_ABORT_RCV");

    if ( status & PCI_STATUS_ASSERT_SERR )
        (void) printf(" ASSERT_SERR");

    if ( status & PCI_STATUS_PARITY_ERROR )
        (void) printf(" PARITY_ERR");

    (void) printf(" )\n");

    return(OK);
    }

/*********************************************************************
*
* vxbPciCmdWordShow - show the decoded value of the command word
*
* This routine reads the command word from the specified
* bus, device, function, and displays the information.
*
* RETURNS: OK, always.
*
* ERRNO
*/

LOCAL STATUS vxbPciCmdWordShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function    /* function */
    )
    {
    UINT16 command;

    if(busCtrlID == NULL)
        return(ERROR);

    (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                     PCI_CFG_COMMAND, &command);

    (void) printf("\tcommand=0x%04x (", command);

    if ( command & PCI_CMD_IO_ENABLE )
        (void) printf(" IO_ENABLE");

    if ( command & PCI_CMD_MEM_ENABLE )
        (void) printf(" MEM_ENABLE");

    if ( command & PCI_CMD_MASTER_ENABLE )
        (void) printf(" MASTER_ENABLE");

    if ( command & PCI_CMD_MON_ENABLE )
        (void) printf(" MON_ENABLE");

    if ( command & PCI_CMD_WI_ENABLE )
        (void) printf(" WI_ENABLE");

    if ( command & PCI_CMD_SNOOP_ENABLE )
        (void) printf(" SNOOP_ENABLE");

    if ( command & PCI_CMD_PERR_ENABLE )
        (void) printf(" PERR_ENABLE");

    if ( command & PCI_CMD_WC_ENABLE )
        (void) printf(" WC_ENABLE");

    if ( command & PCI_CMD_SERR_ENABLE )
        (void) printf(" SERR_ENABLE");

    if ( command & PCI_CMD_FBTB_ENABLE )
        (void) printf(" FBTB_ENABLE");

    (void) printf(" )\n");
    return(OK);
    }

/*********************************************************************
*
* vxbPcixCapabShow - show the PCI-X capabilities
*
* This routine displays the PCI-X specific information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPcixCapabShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,    /* bus number */
    UINT8      device, /* device number */
    UINT8      function,   /* function number */
    UINT       offset         /* offset of capability */
    )
    {
    UINT8 headerType;
    UINT16 cmd, status, secStat;
    UINT32 stat, upstr, dwnstr;

    if(busCtrlID == NULL)
        return;

    (void) vxbPciConfigInByte (busCtrlID, bus, device, function, PCI_CFG_HEADER_TYPE,
                     &headerType);

    switch (headerType)
        {
        case PCI_HEADER_TYPE0: /* Regular Device */
            {
            (void) printf("PCI-X \n");
            (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_X_CMD, &cmd);
            (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_X_STATUS, &stat);

            (void) printf("\tCommand: 0x%04x\n", cmd);
            (void) printf("\tStatus:  0x%08x\n", stat);
            break;
            }
        case PCI_HEADER_TYPE_BRIDGE:
            {
            (void) printf("PCI-X bridge \n");
            (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_X_SECSTAT, &secStat);
            (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_X_PRISTAT, &status);
            (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_X_UP_SXACTION_CTRL, &upstr);
            (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_X_DWN_SXACTION_CTRL, &dwnstr);

            (void) printf("\tSecondary Status:   0x%04x\n", secStat);
            (void) printf("\tPrimary Status:     0x%08x\n", status);
            (void) printf("\tUpstream Control:   0x%08x\n", upstr);
            (void) printf("\tDownstream Control: 0x%08x\n", dwnstr);
            break;
            }
        }
    }

/*********************************************************************
*
* vxbPcieMsixCapabShow - show the MSI-X capabilities
*
* This routine displays the MSI-X specific information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPcieMsixCapabShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       offset         /* offset of capability */
    )
    {
    (void) printf ("MSI-X\n");
    }

/*********************************************************************
*
* vxbPciMsiCapabShow - show the MSI capabilities
*
* This routine displays the MSI specific information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPciMsiCapabShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       offset         /* offset of capability */
    )
    {
    UINT16 ctlReg;
    UINT16 data;
    UINT32 addr;
    UINT32 maskBit, maskOffset;
    UINT32 pendBit;

    if(busCtrlID == NULL)
        return;

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_MSI_CTL, &ctlReg);

    (void) printf("Message Signaled Interrupts: 0x%x control 0x%x %s, %s, MME: %d MMC: %d\n", offset, ctlReg,
           (ctlReg & PCI_MSI_CTL_ENABLE) == 0x00  ? "Disabled" : "Enabled",
           (ctlReg & PCI_MSI_CTL_64BIT)  == 0x00  ? "32-bit" : "64-bit",
           (ctlReg & PCI_MSI_CTL_MSG_ALLOC) >> 4,
           (ctlReg & PCI_MSI_CTL_MSG_MAX) >> 1);

        (void) printf("\tAddress: ");
        if (ctlReg & PCI_MSI_CTL_64BIT)
            {
            maskOffset = PCI_MSI_MASK_64;
            (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_MSI_ADDR_HI, &addr);
            (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_MSI_DATA_64, &data);
            (void) printf("%08x", addr);
            }
        else
            {
            maskOffset = PCI_MSI_MASK_32;
            (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_MSI_DATA_32, &data);
            }
        (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_MSI_ADDR_LO, &addr);
        (void) printf("%08x  Data: 0x%04x\n", addr, data);
        (void) printf("\tPer-vector Mask: %s ", (ctlReg & PCI_MSI_CTL_MASK) ? "Support" : "Unsupported");
        if (ctlReg & PCI_MSI_CTL_MASK)
            {
            (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + maskOffset, &maskBit);
            (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + maskOffset + 4, &pendBit);
            (void) printf ("Mask Bit: 0x%x, Pending Bit: 0x%x \n", maskBit, pendBit);
            }
        (void) printf ("\n");
    }

/*********************************************************************
*
* vxbPcieLinkCap - show the PCIe Link capabilities
*
* This routine displays the PCI Express Link capabilities
* information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPcieLinkCap
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       offset,        /* offset of capability */
    UINT       type           /* device type */
    )
    {
    UINT32 lnkCap;
    UINT16 lnkVal;

    if(busCtrlID == NULL)
        return;

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_EXP_LNKCAP_REG, &lnkCap);

    (void) printf("\tLink: MAX Speed - %s, MAX Width - by %d Port - %d ASPM - %s\n",
           linkSpeed(lnkCap & PCI_EXP_LNKCAP_LNK_SPD),
           (lnkCap & PCI_EXP_LNKCAP_LNK_WDTH) >> 4,
           lnkCap >> 24,
           aspm((lnkCap & PCI_EXP_LNKCAP_ASPM)>>10) );

    (void) printf("\t\tLatency: L0s - %s, L1 - %s\n",
           latL0s((lnkCap & PCI_EXP_LNKCAP_L0S_LAT) >> 12),
           latL1((lnkCap & PCI_EXP_LNKCAP_L1_LAT) >> 15));

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_EXP_LNKCTL_REG, &lnkVal);

    (void) printf("\t\tASPM - %s,", aspmEnable(lnkVal & PCI_EXP_LNKCTL_ASPM));

    if ((type == PCI_EXP_TYPE_ROOT_PORT) ||
        (type == PCI_EXP_TYPE_ENDPOINT)  ||
        (type == PCI_EXP_TYPE_LEG_END))

        (void) printf(" RCB - %dbytes", lnkVal & PCI_EXP_LNKCTL_RCB ? 128 : 64);

    if (lnkVal & PCI_EXP_LNKCTL_LNK_DIS)
        (void) printf(" Link Disabled");

    if (lnkVal & PCI_EXP_LNKCTL_CCC)
        (void) printf(" Common Clock");

    if (lnkVal & PCI_EXP_LNKCTL_EXT_SYNC)
        (void) printf(" Extended Sync");

    (void) printf("\n");

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_EXP_LNKSTA_REG, &lnkVal);
    (void) printf("\t\tSpeed - %s, Width - by %d\n",
           linkSpeed(lnkVal & PCI_EXP_LNKSTA_LNK_SPD),
           (lnkVal & PCI_EXP_LNKSTA_LNK_WDTH) >> 4);
    }


/*********************************************************************
*
* vxbPcieSlotCap - displays the PCI express slot capabilities
*
* RETURNS:  N/A
*
* ERRNO
*/

LOCAL void vxbPcieSlotCap
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       offset         /* offset of capability */
    )
    {
    UINT32 sltCap;
    UINT16 sltCtl;
    UINT16 sltSts;

    if(busCtrlID == NULL)
        return;

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_EXP_SLTCAP_REG, &sltCap);

    (void) printf("\tSlot:");
    if (sltCap & PCI_EXP_SLTCAP_ATTN_BUT)
        (void) printf(" Attn Button");
    if (sltCap & PCI_EXP_SLTCAP_PWR_CTL)
        (void) printf(" Power Controller");
    if (sltCap & PCI_EXP_SLTCAP_MRL)
        (void) printf(" MRL Sensor");
    if (sltCap & PCI_EXP_SLTCAP_PWR_IND)
        (void) printf(" Pwr Indicator");
    if (sltCap & PCI_EXP_SLTCAP_HPL_CAP)
        (void) printf(" Hot-Plug");
    if (sltCap & PCI_EXP_SLTCAP_HPL_SUP)
        (void) printf(" Hot-Plug Surprise");

    (void) printf("\t\tSlot #%d, MAX Slot Power Limit (Watts) %d e%d\n",
           sltCap >> 19,
           ((sltCap & PCI_EXP_SLTCAP_PWR_VAL_LIMIT) >> 7),
           limScale((sltCap & PCI_EXP_SLTCAP_PWR_SCL_LIMIT) >> 15));

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_EXP_SLTCTL_REG, &sltCtl);

    (void) printf("\tEnabled:");
    if (sltCtl & PCI_EXP_SLTCTL_ATTN_BUT_ENB)
        (void) printf(" Attn Button Pressed");
    if (sltCtl & PCI_EXP_SLTCTL_PWRFLT_DET_ENB)
        (void) printf(" Power Fault Detected");
    if (sltCtl & PCI_EXP_SLTCTL_MRLSNSR_ENB)
        (void) printf(" MRL Sensor Changed");
    if (sltCtl & PCI_EXP_SLTCTL_PRES_DET_ENB)
        (void) printf(" Presence Detect");
    if (sltCtl & PCI_EXP_SLTCTL_CCMPLT_ENB)
        (void) printf(" Cmd Complete Int");
    if (sltCtl & PCI_EXP_SLTCTL_HPLINT_ENB)
        (void) printf(" Hot-Plug Int");

    (void) printf("\n");

    if (sltCtl & PCI_EXP_SLTCTL_ATTN_INDCTL)
        (void) printf("\t\tAttn Indicator %s",
               indicator((sltCtl & PCI_EXP_SLTCTL_ATTN_INDCTL) >> 6));
    if (sltCtl & PCI_EXP_SLTCTL_PWR_INDCTL)
        (void) printf(" Power Indicator %s",
               indicator((sltCtl & PCI_EXP_SLTCTL_PWR_INDCTL) >> 8));
    if (sltCtl & PCI_EXP_SLTCTL_PWR_CTLRCTL)
        (void) printf(" Power Controller %s",
               (sltCtl & PCI_EXP_SLTCTL_PWR_CTLRCTL) >> 10 == 0 ?
               "on":"off");

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_EXP_SLTSTA_REG, &sltSts);

    (void) printf("\tSlot Status:");
    if (sltSts & PCI_EXP_SLTSTA_ATTN_BUT)
        (void) printf(" Attn Button Pressed");
    if (sltSts & PCI_EXP_SLTSTA_PWRFLT_DET)
        (void) printf(" Power Fault Detected");
    if (sltSts & PCI_EXP_SLTSTA_MRLSNSR)
        (void) printf(" MRL Sensor Changed: (%s)",
            sltSts & PCI_EXP_SLTSTA_MRLSNSR_STAT ? "MRL open":"MRL close");
    if (sltSts & PCI_EXP_SLTSTA_PRES_DET)
        (void) printf(" Presence Detect Changed:(%s)",
            sltSts & PCI_EXP_SLTSTA_PRES_DET_STAT ?"Card Present":"Slot empty");
    if (sltSts & PCI_EXP_SLTSTA_CCMPLT)
        (void) printf(" Command Complete Int");

    if (sltCap & PCI_EXP_SLTCAP_EIP)
        (void) printf(" Electromechanical Interlock (%s)",
            sltSts & 0x80?"DisEngaged":"Engaged");

    if (sltSts & 0x100)
        (void) printf(" Data Link Layer Status Changed");

    (void) printf ("\n");
    }

/*********************************************************************
*
* vxbPcieExtCapAerShow - show the PCIe EXT AER capabilities
*
* This routine displays the PCIe EXT AER specific information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPcieExtCapAerShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       pos,        /* cap offset */
    UINT       type
    )
    {
    UINT32 i;
    UINT32 uncErrStatus, uncErrMask, uncErrSeverity, rootErrCmd;
    UINT32 rootErrSts = 0;
    UINT32 cErrStatus, cErrMask;
    UINT8 aerLog[16];
    UINT32 tempValue,aerControl;

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_CONTROL, &aerControl);

    (void) printf ("AER Control: 0x%x \n", aerControl);

    (void) printf ("   Uncorrectable : ");

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_UNCRERR_MASK, &uncErrMask);

    (void) printf ("Mask 0x%X. ", uncErrMask);

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_UNCRERR_SEVERITY, &uncErrSeverity);

    (void) printf ("Severity 0x%X \n", uncErrSeverity);

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_UNCRERR_STATUS, &uncErrStatus);

    (void) printf ("   Uncorrectable Status: ");

    if (uncErrStatus & (1<<4))
        (void) printf ("         - Data Link Protocol Error \n");
    if (uncErrStatus & (1<<5))
        (void) printf ("         - Surprise Down Error \n");
    if (uncErrStatus & (1<<12))
        (void) printf ("         - Poisoned TLP \n");
    if (uncErrStatus & (1<<13))
        (void) printf ("         - Flow Control Protocol Error \n");
    if (uncErrStatus & (1<<14))
        (void) printf ("         - Completion Timeout \n");
    if (uncErrStatus & (1<<15))
        (void) printf ("         - Completer Abort \n");
    if (uncErrStatus & (1<<16))
        (void) printf ("         - Unexpected Completion \n");
    if (uncErrStatus & (1<<17))
        (void) printf ("         - Receiver Overflow \n");
    if (uncErrStatus & (1<<18))
        (void) printf ("         - Malformed TLP \n");
    if (uncErrStatus & (1<<19))
        (void) printf ("         - ECRC Error \n");
    if (uncErrStatus & (1<<20))
        (void) printf ("         - Unsupported Request Error \n");
    if (uncErrStatus & (1<<21))
        (void) printf ("         - ACS Violation \n");
    if (uncErrStatus & (1<<22))
        (void) printf ("         - Uncorrectable Internal Error \n");
    if (uncErrStatus & (1<<23))
        (void) printf ("         - MC Blocked TLP \n");
    if (uncErrStatus & (1<<24))
        (void) printf ("         - AtomicOp Egress Blocked \n");
    if (uncErrStatus & (1<<25))
        (void) printf ("         - TLP Prefix Blocked Error \n");

    (void) printf ("   Correctable : ");

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_CRERR_MASK, &cErrMask);

    (void) printf ("Mask 0x%X. \n", cErrMask);

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_CRERR_STATUS, &cErrStatus);

    (void) printf ("   Correctable Status: ");

    if (cErrStatus & (1<<0))
        (void) printf ("         - Receiver Error \n");
    if (cErrStatus & (1<<6))
        (void) printf ("         - Bad TLP \n");
    if (cErrStatus & (1<<7))
        (void) printf ("         - Bad DLLP \n");
    if (cErrStatus & (1<<8))
        (void) printf ("         - REPLAY_NUM Rollover \n");
    if (cErrStatus & (1<<12))
        (void) printf ("         - Replay Timer Timeout \n");
    if (cErrStatus & (1<<13))
        (void) printf ("         - Advisory Non-Fatal Error \n");
    if (cErrStatus & (1<<14))
        (void) printf ("         - Corrected Internal Error \n");
    if (cErrStatus & (1<<15))
        (void) printf ("         - Header Log Overflow \n");

    (void) printf ("\n");

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_HEADER_LOG, (UINT32 *)&aerLog[0]);
    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_HEADER_LOG + 4, (UINT32 *)&aerLog[4]);
    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_HEADER_LOG + 8, (UINT32 *)&aerLog[8]);
    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_HEADER_LOG + 12, (UINT32 *)&aerLog[12]);

    (void) printf ("   HeaderLog: ");
    if (uncErrStatus != 0)
        {
        for (i = 0; i < 15; i++)
            (void) printf ("0x%x ", aerLog[i]);
        }

    (void) printf ("\n");

    if ((type == PCI_EXP_TYPE_RC_INTR_EP) || (type == PCI_EXP_TYPE_RC_EVEN_COLE))
        {
        (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_ROOT_ERR_COMMAND, &rootErrCmd);
        (void) printf ("       Root Error Enable: ");

        if (rootErrCmd & 0x1)
            (void) printf ("Correctable Error Reporting Enable, ");
        if (rootErrCmd & 0x2)
            (void) printf ("Non-Fatal Error Reporting Enable, ");
        if (rootErrCmd & 0x4)
            (void) printf ("Fatal Error Reporting Enable, ");
        (void) printf ("\n");

        (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_ROOT_ERR_STATUS, &rootErrSts);

        (void) printf ("       Message Index: %d\n", (rootErrSts >> 27) & 0x1f);

        (void) printf ("       Root Error Status: \n");

        if (rootErrSts & (1 << 0))
            (void) printf ("     - ERR_COR Received, ");
        if (rootErrSts & (1 << 1))
            (void) printf ("     - Multiple ERR_COR Received, ");
        if (rootErrSts & (1 << 2))
            (void) printf ("     - ERR_FATAL/NONFATAL Received, ");
        if (rootErrSts & (1 << 3))
            (void) printf ("     - Multiple ERR_FATAL/NONFATAL Received, ");
        if (rootErrSts & (1 << 4))
            (void) printf ("     - First Uncorrectable Fatal, ");
        if (rootErrSts & (1 << 5))
            (void) printf ("     - Non-Fatal Error Messages Received, ");
        if (rootErrSts & (1 << 6))
            (void) printf ("     - Fatal Error Messages Received, ");

        (void) printf ("\n");
        }

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_ROOT_CESIR, &tempValue);

    (void) printf ("   Error Source Identification: 0x%x 0x%x \n", tempValue & 0xffff, (tempValue >> 15) & 0xffff);

    if (aerControl & (1<<11))
        {
        (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_TLP_LOG, (UINT32 *)&aerLog[0]);
        (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_TLP_LOG + 4, (UINT32 *)&aerLog[4]);
        (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_TLP_LOG + 8, (UINT32 *)&aerLog[8]);
        (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + PCIE_AER_TLP_LOG + 12, (UINT32 *)&aerLog[12]);

        (void) printf ("       TLP Prefix HeaderLog: ");

        if (rootErrSts != 0)
            {
            for (i = 0; i < 15; i++)
                (void) printf ("0x%x ", aerLog[i]);
            }

            (void) printf ("\n");
        }
    }

/*********************************************************************
*
* vxbPcieExtCapShow - show the PCIe EXT capabilities
*
* This routine displays the PCIe extend capabilities specific information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPcieExtCapShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       type
    )
    {
    UINT16 capId = 0, nextCap = 0, version;
    UINT16 pos = PCI_EXT_CAP_BASE;
    UINT8 serialNum [8];
    UINT32 i;
    UINT32 valueTemp;
    UINT32 latencyScale [] = {1, 32, 1024, 32768, 1048576, 33554432}; /* ns */
    UINT64 latencyTime;

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, pos, &capId);

    /* invalid data */

    if (capId > 0xFF)
        return;

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, pos + 2 , &nextCap);
    version = nextCap & 0xf;
    nextCap = nextCap >> 4;

    while (capId)
        {
        (void) printf("Ext Capabilities - ");

        switch(capId)
            {
            case  PCIE_EXT_CAP_ID_ERR:
                (void) printf ("Advanced Error Reporting. 0x%x. Version %d. ", pos, version);
                vxbPcieExtCapAerShow (busCtrlID, bus, device, function, pos, type);
                break;
            case  PCIE_EXT_CAP_ID_VC2:
            case  PCIE_EXT_CAP_ID_VC:
                (void) printf ("Virtual Channel. 0x%x. Version %d \n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_DSN:
                (void) printf ("Device Serial Number. 0x%x. Version %d \n", pos, version);

                (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + 4 ,
                    (UINT32 *)&serialNum[0]);
                (void) vxbPciConfigInLong (busCtrlID, bus, device, function, pos + 8 ,
                    (UINT32 *)&serialNum[4]);

                (void) printf ("       Serial Number:");
                for (i = 0; i < 8; i++)
                    (void) printf (" 0x%x ", serialNum[i]);
                (void) printf ("\n");
                break;
            case  PCIE_EXT_CAP_ID_RC_LINKD:
                (void) printf ("RC Link Declaration. 0x%x. Version %d \n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_RCI_LINKD:
                (void) printf ("RC Internal Declaration. 0x%x. Version %d \n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_PWR:
                (void) printf ("Power Budgeting. 0x%x. Version %d \n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_RC_ECEA:
                (void) printf ("Root Complex Event Collector Endpoint Association. 0x%x. Version %d\n", pos, version);
                break;
            case PCIE_EXT_CAP_ID_MFVC:
                (void) printf ("MFVC. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_VNDR:
                (void) printf ("Vendor-Specific. 0x%x. Version %d\n", pos, version);
                break;
            case PCIE_EXT_CAP_ID_RCRB:
                (void) printf ("RCRB. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_ACS:
                (void) printf ("ACS. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_ARI:
                (void) printf ("ARI. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_ATS:
                (void) printf ("ATS. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_SRIOV:
                (void) printf ("SRIOV. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_MULCAST:
                (void) printf ("Multicast. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_RSIZEBAR:
                (void) printf ("Resizable BAR. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_DPA:
                (void) printf ("Dynamic Power Allocation. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_TPH:
                (void) printf ("TPH. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_LTR:
                (void) printf ("Latency Tolerance Reporting. 0x%x. Version %d\n", pos, version);

                (void) vxbPciConfigInWord (busCtrlID, bus, device, function, pos + 4 , (UINT16 *)&valueTemp);

                latencyTime = (valueTemp & 0x2ff) * latencyScale[(valueTemp >> 10) & 0x7];

                (void) printf("        Max Snoop Latency: %lld ns, ", latencyTime);

                (void) vxbPciConfigInWord (busCtrlID, bus, device, function, pos + 6 , (UINT16 *)&valueTemp);
                latencyTime = (valueTemp & 0x2ff) * latencyScale[(valueTemp >> 10) & 0x7];
                (void) printf("Max No-Snoop Latency: %lld ns \n", latencyTime);
                break;

            case  PCIE_EXT_CAP_ID_SECOND_EXT:
                (void) printf ("Secondary PCI Express Extended Capability. 0x%x. Version %d\n", pos, version);
                break;
            case  PCIE_EXT_CAP_ID_PMUX:
                (void) printf ("PMUX Extended Capability. 0x%x. Version %d\n", pos, version);
                break;
            default:
                (void) printf ("%d unKnown\n", capId);
                break;
            }

        if (nextCap == 0)
            return;

        (void) vxbPciConfigInWord (busCtrlID, bus, device, function, nextCap , &capId);

        if (nextCap != 0)
           pos = nextCap;

        (void) vxbPciConfigInWord (busCtrlID, bus, device, function, nextCap + 2, &nextCap);

        version = nextCap & 0xf;
        nextCap = nextCap >> 4;

        }
    }

/*********************************************************************
*
* vxbPcieDevCap - show the PCIe Device capabilities
*
* This routine displays the PCI Express Device capabilities
* information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPcieDevCap
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       offset,        /* offset of capability */
    UINT       type           /* device type */
    )
    {
    UINT32 devCap;
    UINT16 devCtl;

    if(busCtrlID == NULL)
        return;

    (void) vxbPciConfigInLong (busCtrlID, bus, device, function, offset + PCI_EXP_DEVCAP_REG, &devCap);

    (void) printf("\tDevice: Max Payload: %d bytes",
           128 << (devCap & PCI_EXP_DEVCAP_PAYLOAD));
    if (devCap & PCI_EXP_DEVCAP_PHANTOM)
        (void) printf(", Phantom Funcs %d msb",
               (devCap & PCI_EXP_DEVCAP_PHANTOM) >> 3);
    (void) printf(", Extended Tag: %d-bit\n",
           ((devCap & PCI_EXP_DEVCAP_EXT_TAG) >> 5) == 0 ? 5:8);

    (void) printf("\t\tAcceptable Latency: L0 - %s, L1 - %s\n",
           latL0s((devCap & PCI_EXP_DEVCAP_L0S) >> 6),
           latL1((devCap & PCI_EXP_DEVCAP_L1) >> 9));

    if ((type == PCI_EXP_TYPE_ENDPOINT) ||
        (type == PCI_EXP_TYPE_LEG_END)  ||
        (type == PCI_EXP_TYPE_UPSTREAM) ||
        (type == PCI_EXP_TYPE_PCI2EXP))
        {
        if (devCap & PCI_EXP_DEVCAP_ATTN_BUTTON)
            (void) printf("\tAttn Button");
        if (devCap & PCI_EXP_DEVCAP_ATTN_IND)
            (void) printf(", Attn Indicator");
        if (devCap & PCI_EXP_DEVCAP_PWR_IND)
            (void) printf(", Pwr Indicator\n");
        }

    if (type == PCI_EXP_TYPE_UPSTREAM)
        (void) printf("\tSlot Power Limit (Watts) %d e%d\n",
               ((devCap & PCI_EXP_DEVCAP_PWR_VAL_LIMIT) >> 18),
                limScale((devCap & PCI_EXP_DEVCAP_PWR_SCL_LIMIT) >> 26));

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_EXP_DEVCTL_REG, &devCtl);

    (void) printf("\t\tErrors Enabled: ");
    if (devCtl &  PCI_EXP_DEVCTL_CERR_ENB)
        (void) printf(" Correctable");
    if (devCtl &  PCI_EXP_DEVCTL_NFERR_ENB)
        (void) printf(" Non-Fatal");
    if (devCtl &  PCI_EXP_DEVCTL_FERR_ENB)
        (void) printf(" Fatal");
    if (devCtl &  PCI_EXP_DEVCTL_URREP_ENB)
        (void) printf(" Unsupported Request");
    if (devCtl &  PCI_EXP_DEVCTL_RLX_ORD_ENB)
        (void) printf("Relaxed Ordering");
    if (devCtl &  PCI_EXP_DEVCTL_EXT_TAG)
        (void) printf(" Extended Tag");
    if (devCtl &  PCI_EXP_DEVCTL_PHANTOM)
        (void) printf(" Phantom Funcs");
    if (devCtl &  PCI_EXP_DEVCTL_AUX_PM_ENB)
        (void) printf(" AUX Pwr PM");
    if (devCtl &  PCI_EXP_DEVCTL_NOSNOOP_ENB)
        (void) printf(" No Snoop");

    (void) printf("\n\r\t");

    if (devCtl & PCI_EXP_DEVCTL_PAYLOAD)
        (void) printf("Max Payload %d bytes ",
               128 << ((devCtl & PCI_EXP_DEVCTL_PAYLOAD) >> 5));
    if (devCtl & PCI_EXP_DEVCTL_READ_REQ)
        (void) printf("Max Read Request %d bytes\n",
               128 << ((devCtl & PCI_EXP_DEVCTL_READ_REQ) >> 12));

    }

/*********************************************************************
*
* vxbPcieCapabShow - show the MSI capabilities
*
* This routine displays the MSI specific information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPcieCapabShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function,   /* function */
    UINT       offset      /* offset of capability */
    )
    {
    UINT16 capReg, type, slot = 0;

    (void) printf("PCIe: ");

    if(busCtrlID == NULL)
        return;

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_EXP_CAP_REG, &capReg);

    type = (UINT16)((capReg & PCI_EXP_CAP_PORT_TYPE) >> 4);

        switch (type)
          {
          case PCI_EXP_TYPE_ENDPOINT:
            (void) printf("Endpoint");
            break;
          case PCI_EXP_TYPE_LEG_END:
            (void) printf("Legacy Endpoint");
            break;
          case PCI_EXP_TYPE_ROOT_PORT:
            slot = capReg & PCI_EXP_CAP_SLOT_ADDON;
            (void) printf("Root Port");
            if (slot)
               (void) printf("- Slot");
            break;
          case PCI_EXP_TYPE_UPSTREAM:
            (void) printf("Upstream Port");
            break;
          case PCI_EXP_TYPE_DOWNSTREAM:
             slot = capReg & PCI_EXP_CAP_SLOT_ADDON;
            (void) printf("Downstream Port");
            if (slot)
               (void) printf("- Slot");
            break;
          case PCI_EXP_TYPE_PCI2EXP:
            (void) printf("PCI/PCI-X to Express Bridge");
            break;
          case PCI_EXP_TYPE_RC_INTR_EP:
            (void) printf("Root Complex Integrated Endpoint");
            break;
          case PCI_EXP_TYPE_RC_EVEN_COLE:
            (void) printf("Root Complex Event Collector");
            break;
          default:
            (void) printf("Unknown");
        }
        (void) printf(", IRQ %d\n", (capReg & PCI_EXP_CAP_IRQ) >> 9);

        vxbPcieDevCap(busCtrlID, bus, device, function, offset, type);

        vxbPcieLinkCap(busCtrlID, bus, device, function, offset, type);

        if (slot)
          vxbPcieSlotCap(busCtrlID, bus, device, function, offset);

    if (type == PCI_EXP_TYPE_ROOT_PORT)
        {
        (void) vxbPciConfigInWord (busCtrlID, bus, device, function, offset + PCI_EXP_RTCTL_REG, &capReg);

        (void) printf("\tRoot Control Enabled: ");
        if (capReg & PCI_EXP_RTCTL_SECE_ENB)
            (void) printf("Correctable ");
        if (capReg & PCI_EXP_RTCTL_SENFE_ENB)
            (void) printf("System Error (NF) ");
        if (capReg & PCI_EXP_RTCTL_SEFE_ENB)
            (void) printf("System Error (F) ");
        if (capReg & PCI_EXP_RTCTL_PMEI_ENB)
            (void) printf("PME Interrupt ");
        (void) printf("\n");
        }

    vxbPcieExtCapShow (busCtrlID, bus, device, function, type);
    }

/*********************************************************************
*
* vxbPciCapabShow - show the PCI capabilities
*
* This routine reads the capabilities pointer ID, traverses the
* capability linked list till the pointer is null, and prints the
* information.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void vxbPciCapabShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,            /* bus number */
    UINT8      device,         /* device number */
    UINT8      function,       /* function number */
    UINT8      capOffset       /* Capabilities Ptr Offset */
    )
    {
    UINT8 devCapID, cap_id, cap_id_next;

    if(busCtrlID == NULL)
        return;

    /* Capabilities List Implemented: Get first capability ID */

    (void) vxbPciConfigInByte (busCtrlID, bus, device, function, capOffset, &devCapID);

    /* Longword Align */

    devCapID = devCapID & (UINT8)(~0x03);

    while (devCapID)
        {
        (void) printf("Capabilities - ");
        (void) vxbPciConfigInByte (busCtrlID, bus, device, function, devCapID, &cap_id);
        (void) vxbPciConfigInByte (busCtrlID, bus, device, function, devCapID+1, &cap_id_next);

        /* longword align */
        cap_id_next = cap_id_next & (UINT8)(~0x03);

        /* Enhancement: Dump specific capabilities regs */
        if (cap_id == 0xff)
            /* Get Out - something is wrong */
            break;

        switch (cap_id)
            {
            case PCI_EXT_CAP_PCI_PM:
                (void) printf("Power Management \n");
                break;
            case PCI_EXT_CAP_AGP:
                (void) printf("AGP ");
                break;
            case PCI_EXT_CAP_VPD:
                (void) printf("Vital Product Data \n");
                break;
            case PCI_EXT_CAP_SLOTID:
                (void) printf("Slot ID \n");
                break;
            case PCI_EXT_CAP_MSI:
                vxbPciMsiCapabShow(busCtrlID, bus, device, function, devCapID);
                break;
            case PCI_EXT_CAP_HOT_SWAP:
                (void) printf("cPCI Hot Swap \n");
                break;
            case PCI_EXT_CAP_PCIX:
                vxbPcixCapabShow(busCtrlID, bus, device, function, devCapID);
                break;
            case PCI_EXT_CAP_DBG_PORT:
                (void) printf("Debug Port \n");
                break;
            case PCI_EXT_CAP_CPCI_RES:
                (void) printf("cPCI Resource \n");
                break;
            case PCI_EXT_CAP_HPC:
                (void) printf("PCI Hot Plug \n");
                break;
            case PCI_EXT_CAP_EXP:
                vxbPcieCapabShow (busCtrlID,bus, device, function, devCapID);
                break;
            case PCI_EXT_CAP_MSIX:
                vxbPcieMsixCapabShow (busCtrlID, bus, device, function, devCapID);
                break;
            default:
                (void) printf("%02x Unknown\n", cap_id);
            }
        devCapID = cap_id_next;
        }
    (void) printf("\n");
    }

/*******************************************************************************
*
* vxbPciShowInit - initialize the show routines
*
* This routine is used to pull in all routines in this library.
*
* \NOMANUAL
*
* RETURNS: N/A
*
* ERRNO
*/

void vxbPciShowInit (void)
    {
    return;
    }

/*******************************************************************************
*
* vxbPciCtrlShow - list all registered PCI/PCIe controller device ID
*
* This routine lists all registered PCI/PCIe controller device ID, then it could
* be used to call other vxbPciXXXShow() routine.
*
* RETURNS: N/A
*
* ERRNO
*/

void vxbPciCtrlShow (void)
    {
    VXB_PCI_CTRL * pPciCtrl = NULL;
    SL_NODE *      pNode;
    char           buf[128];

    if (!vxbPciCtrlListInited)
        return;

    pNode = SLL_FIRST (&vxbPciCtrlList);

    while (pNode != NULL)
        {
        pPciCtrl = (VXB_PCI_CTRL *)pNode;

        vxbDevGetNameUnit(pPciCtrl->pDev, buf, 128);

        (void) printf("Pci controller (%s) devId=%p\n", buf, pPciCtrl->pDev);

        pNode = SLL_NEXT(pNode);
        }
    }

/*******************************************************************************
*
* vxbPciDeviceShow - print PCI device information under PCI bus
*
* This routine prints information about the PCI devices on a given PCI bus
* segment (specified by <busNo>).
*
* RETURNS: OK, or ERROR if the library is not initialized.
*
* ERRNO
*/

STATUS vxbPciDeviceShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      busNo       /* bus number */
    )
    {
    UINT8 deviceNo;
    UINT16 vendorId = 0;
    UINT16 deviceId = 0;
    UINT32 classCode = 0;
    UINT8 headerType = 0;
    UINT8 func=0;

    if(busCtrlID == NULL)
        return(ERROR);

    (void) printf ("Scanning functions of each PCI device on bus %d\n", busNo);
    (void) printf ("bus       device    function  vendorID  deviceID  class/rev\n");

    for (deviceNo=0; deviceNo < PCI_MAX_DEV; deviceNo++)
        {
        for (func = 0; func < 8; func++)
            {
            /* avoid a special bus cycle */
            vendorId = 0xffff;

            if ((deviceNo == 0x1f) && (func == 0x07))
                continue;

            (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, func, PCI_CFG_VENDOR_ID,
                             (UINT16 *)&vendorId);

            /*
             * There are two ways to find out an empty device.
             * 1. check Master Abort bit after the access.
             * 2. check whether the read value is 0xffff.
             * Since I didn't see the Master Abort bit of the host/PCI bridge
             * changing, I use the second method.
             */

            if (vendorId == 0xffff)
                {
                if (func == 0)
                    break; /* next device */
                continue;  /* next function */
                }

            deviceId = 0xffff;
            (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, func, PCI_CFG_DEVICE_ID,
                             (UINT16 *)&deviceId);

            (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, func, PCI_CFG_REVISION,
                             &classCode);

            (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, func, PCI_CFG_HEADER_TYPE,
                             &headerType);

            (void) printf ("%7d   %6d    %8d   0x%04x    0x%04x  0x%08x\n",
                    busNo, deviceNo, func, vendorId, deviceId, classCode);

            if (func == 0 && (headerType & PCI_HEADER_MULTI_FUNC) == 0)
                break; /* next device */
            }
        }

    return (OK);
    }


/*******************************************************************************
*
* vxbPciHeaderShow - print a header of the specified PCI device
*
* This routine prints a header of the PCI device specified by busNo, deviceNo,
* and funcNo.
*
* RETURNS: OK, or ERROR if this library is not initialized.
*
* ERRNO
*/

STATUS vxbPciHeaderShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      busNo,    /* bus number */
    UINT8      deviceNo, /* device number */
    UINT8      funcNo   /* function number */
    )
    {
    PCI_HEADER_DEVICE headerDevice;
    PCI_HEADER_BRIDGE headerBridge;
    PCI_HEADER_CB_BRIDGE headerCBBridge;
    PCI_HEADER_DEVICE * pD = &headerDevice;
    PCI_HEADER_BRIDGE * pB = &headerBridge;
    PCI_HEADER_CB_BRIDGE * pCB = &headerCBBridge;

    if(busCtrlID == NULL)
        return(ERROR);

    (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_HEADER_TYPE,
                     (UINT8 *)&pD->headerType);

    if (pD->headerType & 0x01)      /* PCI-to-PCI bridge */
        {
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_VENDOR_ID,
                         (UINT16 *)&pB->vendorId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_DEVICE_ID,
                         (UINT16 *)&pB->deviceId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_COMMAND,
                         (UINT16 *)&pB->command);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_STATUS,
                         (UINT16 *)&pB->status);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_REVISION,
                         (UINT8 *)&pB->revisionId);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PROGRAMMING_IF,
                         (UINT8 *)&pB->progIf);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SUBCLASS,
                         (UINT8 *)&pB->subClass);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CLASS,
                         (UINT8 *)&pB->classCode);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CACHE_LINE_SIZE,
                         (UINT8 *)&pB->cacheLine);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_LATENCY_TIMER,
                         (UINT8 *)&pB->latency);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_HEADER_TYPE,
                         (UINT8 *)&pB->headerType);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BIST,
                         (UINT8 *)&pB->bist);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_0,
                         (UINT32 *)&pB->base0);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_1,
                         (UINT32 *)&pB->base1);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PRIMARY_BUS,
                         (UINT8 *)&pB->priBus);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SECONDARY_BUS,
                         (UINT8 *)&pB->secBus);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SUBORDINATE_BUS,
                         (UINT8 *)&pB->subBus);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SEC_LATENCY,
                         (UINT8 *)&pB->secLatency);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_IO_BASE,
                         (UINT8 *)&pB->ioBase);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_IO_LIMIT,
                         (UINT8 *)&pB->ioLimit);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SEC_STATUS,
                         (UINT16 *)&pB->secStatus);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_MEM_BASE,
                         (UINT16 *)&pB->memBase);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_MEM_LIMIT,
                         (UINT16 *)&pB->memLimit);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PRE_MEM_BASE,
                         (UINT16 *)&pB->preBase);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PRE_MEM_LIMIT,
                         (UINT16 *)&pB->preLimit);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PRE_MEM_BASE_U,
                         (UINT32 *)&pB->preBaseUpper);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PRE_MEM_LIMIT_U,
                         (UINT32 *)&pB->preLimitUpper);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_IO_BASE_U,
                         (UINT16 *)&pB->ioBaseUpper);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_IO_LIMIT_U,
                         (UINT16 *)&pB->ioLimitUpper);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_ROM_BASE,
                         (UINT32 *)&pB->romBase);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BRG_INT_LINE,
                         (UINT8 *)&pB->intLine);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BRG_INT_PIN,
                         (UINT8 *)&pB->intPin);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BRIDGE_CONTROL,
                         (UINT16 *)&pB->control);
        vxbPciBheaderPrint (pB);

        if (pB->status & PCI_STATUS_NEW_CAP)
            vxbPciCapabShow (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CAP_PTR);

        }
    else if ((pD->headerType & PCI_HEADER_TYPE_MASK) == PCI_HEADER_PCI_CARDBUS)
        {
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_VENDOR_ID,
                         (UINT16 *)&pCB->vendorId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_DEVICE_ID,
                         (UINT16 *)&pCB->deviceId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_COMMAND,
                         (UINT16 *)&pCB->command);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_STATUS,
                         (UINT16 *)&pCB->status);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_REVISION,
                         (UINT8 *)&pCB->revisionId);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PROGRAMMING_IF,
                         (UINT8 *)&pCB->progIf);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SUBCLASS,
                         (UINT8 *)&pCB->subClass);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CLASS,
                         (UINT8 *)&pCB->classCode);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CACHE_LINE_SIZE,
                         (UINT8 *)&pCB->cacheLine);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_LATENCY_TIMER,
                         (UINT8 *)&pCB->latency);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_HEADER_TYPE,
                         (UINT8 *)&pCB->headerType);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BIST,
                         (UINT8 *)&pCB->bist);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_0,
                         (UINT32 *)&pCB->base0);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_CAP_PTR,
                         (UINT8 *)&pCB->capPtr);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_SEC_STATUS,
                         (UINT16 *)&pCB->secStatus);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PRIMARY_BUS,
                         (UINT8 *)&pCB->priBus);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SECONDARY_BUS,
                         (UINT8 *)&pCB->secBus);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SUBORDINATE_BUS,
                         (UINT8 *)&pCB->subBus);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SEC_LATENCY,
                         (UINT8 *)&pCB->secLatency);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_MEM_BASE_0,
                         (UINT32 *)&pCB->memBase0);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_MEM_LIMIT_0,
                         (UINT32 *)&pCB->memLimit0);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_MEM_BASE_1,
                         (UINT32 *)&pCB->memBase1);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_MEM_LIMIT_1,
                         (UINT32 *)&pCB->memLimit1);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_IO_BASE_0,
                         (UINT32 *)&pCB->ioBase0);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_IO_LIMIT_0,
                         (UINT32 *)&pCB->ioLimit0);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_IO_BASE_1,
                         (UINT32 *)&pCB->ioBase1);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_IO_LIMIT_1,
                         (UINT32 *)&pCB->ioLimit1);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BRG_INT_LINE,
                         (UINT8 *)&pCB->intLine);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BRG_INT_PIN,
                         (UINT8 *)&pCB->intPin);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BRIDGE_CONTROL,
                         (UINT16 *)&pCB->control);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_SUB_VENDOR_ID,
                         (UINT16 *)&pCB->subVendorId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_SUB_SYSTEM_ID,
                         (UINT16 *)&pCB->subSystemId);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_16BIT_LEGACY,
                         (UINT32 *)&pCB->legacyBase);
        vxbPciCBheaderPrint (pCB);

        if (pCB->status & PCI_STATUS_NEW_CAP)
            vxbPciCapabShow (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CB_CAP_PTR);

        }
    else                    /* PCI device */
        {
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_VENDOR_ID,
                         (UINT16 *)&pD->vendorId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_DEVICE_ID,
                         (UINT16 *)&pD->deviceId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_COMMAND,
                         (UINT16 *)&pD->command);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_STATUS,
                         (UINT16 *)&pD->status);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_REVISION,
                         (UINT8 *)&pD->revisionId);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_PROGRAMMING_IF,
                         (UINT8 *)&pD->progIf);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SUBCLASS,
                         (UINT8 *)&pD->subClass);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CLASS,
                         (UINT8 *)&pD->classCode);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CACHE_LINE_SIZE,
                         (UINT8 *)&pD->cacheLine);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_LATENCY_TIMER,
                         (UINT8 *)&pD->latency);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_HEADER_TYPE,
                         (UINT8 *)&pD->headerType);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BIST,
                         (UINT8 *)&pD->bist);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_0,
                         (UINT32 *)&pD->base0);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_1,
                         (UINT32 *)&pD->base1);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_2,
                         (UINT32 *)&pD->base2);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_3,
                         (UINT32 *)&pD->base3);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_4,
                         (UINT32 *)&pD->base4);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_BASE_ADDRESS_5,
                         (UINT32 *)&pD->base5);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CIS,
                         (UINT32 *)&pD->cis);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SUB_VENDER_ID,
                         (UINT16 *)&pD->subVendorId);
        (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_SUB_SYSTEM_ID,
                         (UINT16 *)&pD->subSystemId);
        (void) vxbPciConfigInLong (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_EXPANSION_ROM,
                         (UINT32 *)&pD->romBase);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_DEV_INT_LINE,
                         (UINT8 *)&pD->intLine);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_DEV_INT_PIN,
                         (UINT8 *)&pD->intPin);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_MIN_GRANT,
                         (UINT8 *)&pD->minGrant);
        (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_MAX_LATENCY,
                         (UINT8 *)&pD->maxLatency);
        vxbPciDheaderPrint (pD);

        if (pD->status & PCI_STATUS_NEW_CAP)
            vxbPciCapabShow (busCtrlID, busNo, deviceNo, funcNo, PCI_CFG_CAP_PTR);
        }

    return (OK);
    }

/*********************************************************************
*
* vxbPciFuncShow - show configuration details about a function
*
* This routine reads various information from the specified
* bus, device, function, and displays the information.
*
* RETURNS: OK, always.
*
* ERRNO
*/

STATUS vxbPciFuncShow
    (
    VXB_DEV_ID busCtrlID,
    UINT8      bus,        /* bus */
    UINT8      device,     /* device */
    UINT8      function    /* function */
    )
    {
    UINT8  clsCode;
    UINT8  subClass;
    UINT8  secBus;
    int    numBars = 6; /* most devices have 6, but not bridges */
    UINT16 memBase;
    UINT16 memLimit;
    UINT16 vendorId;
    UINT16 deviceId;
    UINT32 memBaseU;
    UINT32 memLimitU;
    UINT8  ioBase;
    UINT8  ioLimit;
    UINT16 ioBaseU;
    UINT16 ioLimitU;
    UINT8  headerType;
    UINT16 cmdReg;
    int i;

    if(busCtrlID == NULL)
        return(ERROR);

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, PCI_CFG_VENDOR_ID,
                     (UINT16 *)&vendorId);

    (void) vxbPciConfigInWord (busCtrlID, bus, device, function, PCI_CFG_DEVICE_ID,
                     (UINT16 *)&deviceId);

    (void) printf("[%d,%d,%d] - (%04x %04x) type=",bus,device,function, vendorId, deviceId);

    (void) vxbPciConfigInByte (busCtrlID, bus, device, function,
                     PCI_CFG_CLASS, &clsCode);

    (void) vxbPciConfigInByte (busCtrlID, bus,device,function,
                    PCI_CFG_HEADER_TYPE, &headerType);

    if ( ( headerType & PCI_HEADER_TYPE_MASK ) == 1 )
        {
        /* type 1 header has only 2 BARs */
        numBars = 2;
        }

    if ((headerType & PCI_HEADER_TYPE_MASK) == PCI_HEADER_PCI_CARDBUS)
        {
        /* CardBus bridge header has 1 BAR */
        numBars = 1;
        }

    switch (clsCode)
        {
        case PCI_CLASS_PRE_PCI20:     (void) printf("BEFORE_STD\n"); break;
        case PCI_CLASS_MASS_STORAGE:  (void) printf("MASS STORAGE\n"); break;
        case PCI_CLASS_NETWORK_CTLR:  (void) printf("NET_CNTLR\n"); break;
        case PCI_CLASS_DISPLAY_CTLR:  (void) printf("DISP_CNTLR\n"); break;
        case PCI_CLASS_MMEDIA_DEVICE: (void) printf("MULTI_MEDIA\n"); break;
        case PCI_CLASS_MEM_CTLR:      (void) printf("MEM_CNTLR\n"); break;
        case PCI_CLASS_COMM_CTLR:     (void) printf("COMMUNICATION\n"); break;
        case PCI_CLASS_BASE_PERIPH:   (void) printf("PERIPHERAL\n"); break;
        case PCI_CLASS_INPUT_DEVICE:  (void) printf("INPUT\n"); break;
        case PCI_CLASS_DOCK_DEVICE:   (void) printf("DOCKING STATION\n"); break;
        case PCI_CLASS_PROCESSOR:     (void) printf("PROCESSOR\n"); break;
        case PCI_CLASS_SERIAL_BUS:    (void) printf("SERIAL BUS\n"); break;
        case PCI_CLASS_WIRELESS:      (void) printf("WIRELESS\n"); break;
        case PCI_CLASS_INTLGNT_IO:    (void) printf("INTELLIGENT_IO\n"); break;
        case PCI_CLASS_SAT_COMM:      (void) printf("SATELLITE\n"); break;
        case PCI_CLASS_EN_DECRYPTION: (void) printf("ENCRYPTION DEV\n"); break;
        case PCI_CLASS_DAQ_DSP:       (void) printf("DATA ACQUISITION DEV\n"); break;
        case PCI_CLASS_UNDEFINED:     (void) printf("OTHER DEVICE\n"); break;

        case PCI_CLASS_BRIDGE_CTLR:
            secBus = 0;
            (void) vxbPciConfigInByte (busCtrlID, bus, device, function,
                             PCI_CFG_SUBCLASS, &subClass);

            switch (subClass)
                {
                case PCI_SUBCLASS_HOST_PCI_BRIDGE:
                    (void) printf("HOST");
                    break;

                case PCI_SUBCLASS_ISA_BRIDGE:
                    (void) printf("ISA");
                    break;

                case PCI_SUBCLASS_EISA_BRIDGE:
                    (void) printf("EISA");
                    break;

                case PCI_SUBCLASS_MCA_BRIDGE:
                    (void) printf("MC");
                    break;

                case PCI_SUBCLASS_P2P_BRIDGE:
                    (void) printf("P2P");
                    (void) vxbPciConfigInByte (busCtrlID, bus, device, function,
                                     PCI_CFG_SECONDARY_BUS, &secBus);
                    break;

                case PCI_SUBCLASS_PCMCIA_BRIDGE:
                    (void) printf("PCMCIA");
                    break;

                case PCI_SUBCLASS_CARDBUS_BRIDGE:
                    (void) printf("CARDBUS");
                    (void) vxbPciConfigInByte (busCtrlID, bus, device, function,
                                     PCI_CFG_SECONDARY_BUS, &secBus);
                    break;

                case PCI_SUBCLASS_RACEWAY_BRIDGE:
                    (void) printf("RACEWAY");
                    break;

                default:
                    (void) printf("UNKNOWN (0x%02x)", subClass);
                    break;
                }

            (void) printf(" BRIDGE");
            if ( secBus != 0 )
                {
                (void) printf(" to [%d,0,0]", secBus);
                (void) printf("\n");

                (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                                PCI_CFG_COMMAND, &cmdReg);

                if (subClass == PCI_SUBCLASS_CARDBUS_BRIDGE)
                    {
                    UINT32 memBase;
                    UINT32 memLimit;
                    UINT32 ioBase;
                    UINT32 ioLimit;

                    (void) printf ("\tbase/limit:\n");

                    if (cmdReg & PCI_CMD_MEM_ENABLE)
                        {
                        for (i = 0; i < 2; i++)
                            {
                            (void) vxbPciConfigInLong (busCtrlID, bus, device, function,
                                             PCI_CFG_CB_MEM_BASE_0 + i * 8,
                                             &memBase);
                            (void) vxbPciConfigInLong (busCtrlID, bus, device, function,
                                             PCI_CFG_CB_MEM_LIMIT_0 + i * 8,
                                             &memLimit);
                            (void) printf ("\t  mem%d=0x%08x/0x%08x\n", i,
                                    memBase, memLimit | 0x0fff);
                            }
                        }

                    if (cmdReg & PCI_CMD_IO_ENABLE)
                        {
                        for (i = 0; i < 2; i++)
                            {
                            (void) vxbPciConfigInLong (busCtrlID, bus, device, function,
                                             PCI_CFG_CB_IO_BASE_0 + i * 8,
                                             &ioBase);
                            (void) vxbPciConfigInLong (busCtrlID, bus, device, function,
                                             PCI_CFG_CB_IO_LIMIT_0 + i * 8,
                                             &ioLimit);
                            (void) printf ("\t  I/O%d=0x%08x/0x%08x\n", i,
                                    ioBase, ioLimit);
                            }
                        }

                    break;
                    }

                if ( cmdReg & PCI_CMD_MEM_ENABLE )
                    {
                    (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                                    PCI_CFG_MEM_BASE, &memBase);
                    (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                                    PCI_CFG_MEM_LIMIT, &memLimit);
                    (void) printf("\tbase/limit:\n");
                    (void) printf("\t  mem=   0x%04x0000/0x%04xffff\n",
                           memBase & 0xfff0, memLimit | 0x000f);

                    (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                                    PCI_CFG_PRE_MEM_BASE, &memBase);
                    (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                                    PCI_CFG_PRE_MEM_LIMIT, &memLimit);
                    if ( ( memBase & 0x000f ) == 0x0001 )
                        {
                        /* 64-bit memory */
                        (void) vxbPciConfigInLong (busCtrlID, bus,device,function,
                                        PCI_CFG_PRE_MEM_BASE_U,
                                        &memBaseU);
                        (void) vxbPciConfigInLong (busCtrlID, bus,device,function,
                                        PCI_CFG_PRE_MEM_LIMIT_U,
                                        &memLimitU);
                        (void) printf("\t  preMem=0x%08x%04x0000/"
                               "0x%08x%04xffff\n",
                               memBaseU, memBase & 0xfff0,
                               memLimitU, memLimit | 0x000f);
                        }
                    else
                        (void) printf("\t  preMem=0x%04x0000/0x%04xffff\n",
                               memBase & 0xfff0, memLimit | 0x000f);
                    }

                if ( cmdReg & PCI_CMD_IO_ENABLE )
                    {
                    (void) vxbPciConfigInByte (busCtrlID, bus,device,function,
                                    PCI_CFG_IO_BASE, &ioBase);
                    (void) vxbPciConfigInByte (busCtrlID, bus,device,function,
                                    PCI_CFG_IO_LIMIT, &ioLimit);
                    if ( ( ioBase & 0x0f ) == 0x01 )
                        {
                        /* 32-bit I/O */
                        (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                                        PCI_CFG_IO_BASE_U, &ioBaseU);
                        (void) vxbPciConfigInWord (busCtrlID, bus,device,function,
                                        PCI_CFG_IO_LIMIT_U, &ioLimitU);
                        (void) printf("\t  I/O=   0x%04x%02x00/0x%04x%02xff\n",
                               ioBaseU, (ioBase & 0xf0),
                               ioLimitU, (ioLimit | 0x0f));
                        }
                    else
                        (void) printf("\t  I/O=   0x%02x00/0x%02xff\n",
                               (ioBase & 0xf0), (ioLimit | 0x0f));
                    }
                }
            else
                (void) printf("\n");

            break;

        default:
            (void) printf("UNKNOWN!\n");
        }

    (void) vxbPciStatusWordShow(busCtrlID,bus, device, function);
    (void) vxbPciCmdWordShow(busCtrlID,bus, device, function);

    vxbPciFuncBarShow(busCtrlID,bus, device, function, numBars);

    return(OK);
    }

/*********************************************************************
*
* vxbPciTopoShow - show PCI topology
*
* This routine traverses the PCI bus and prints assorted information
* about every device found.  The information is intended to present
* the topology of the PCI bus.  In includes: (1) the device type, (2)
* the command and status words, (3) for PCI to PCI bridges the memory
* and I/O space configuration, and (4) the values of all implemented
* BARs.
*
* RETURNS: N/A
*
* ERRNO
*/

void vxbPciTopoShow
    (
    VXB_DEV_ID busCtrlID
    )
    {
    UINT8 deviceNo;
    UINT8  busNo = 0;
    UINT16 vendorId = 0;
    UINT8 func=0;
    UINT8 headerType=0;
    
    if(busCtrlID == NULL)
        return;

    for (busNo = 0; busNo < PCI_MAX_BUS; busNo++)
        {
        for (deviceNo=0; deviceNo < PCI_MAX_DEV; deviceNo++)
            {
            for (func = 0; func < 8; func++)
                {
                /* avoid a special bus cycle */
                vendorId = 0xffff;

                if ((deviceNo == 0x1f) && (func == 0x07))
                    continue;

                (void) vxbPciConfigInWord (busCtrlID, busNo, deviceNo, func, PCI_CFG_VENDOR_ID,
                                 (UINT16 *)&vendorId);

                /*
                 * There are two ways to find out an empty device.
                 * 1. check Master Abort bit after the access.
                 * 2. check whether the read value is 0xffff.
                 * Since I didn't see the Master Abort bit of the host/PCI bridge
                 * changing, I use the second method.
                 */

                if (((vendorId & 0x0000ffff) == PCI_CONFIG_ABSENT_F) ||
                    ((vendorId & 0x0000ffff) == PCI_CONFIG_ABSENT_0) )
                    {
                    if (func == 0)
                        {
                        break;     /* non-existent device, goto next device */
                        }
                    else
                        continue;  /* function empty, try the next function */
                    }
                
                (void) vxbPciFuncShow (busCtrlID, busNo, deviceNo, func);

                (void) vxbPciConfigInByte (busCtrlID, busNo, deviceNo, func, PCI_CFG_HEADER_TYPE,
                             &headerType);

                if (func == 0 && (headerType & PCI_HEADER_MULTI_FUNC) == 0)
                    break; /* next device */
                }
            }
        }

    return;
    }
