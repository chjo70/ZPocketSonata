/* vxbPcieAer.h - PCIe AER capability driver header file */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01jan1,y_y  created. (F4655)
*/

#ifndef __INCvxbPcieAerH
#define __INCvxbPcieAerH

#ifdef __cplusplus
extern "C" {
#endif

#include <hwif/vxBus.h>
#include <hwif/util/vxbIsrDeferLib.h>

/* Defines */

#define CORRECTABLE             0
#define NONFATAL                1
#define FATAL                   2

#define EDR_TEXT_MSG_LEN        0x1000
#define IS_ENABLE_ST            TRUE

#define EDR_PCIE_AER_COR_INJECT(trace, msg) \
    EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_INTERRUPT , 0, trace, msg)

#define EDR_PCIE_AER_NON_FATAL_INJECT(trace, msg) \
    EDR_INJECT_TRACE(EDR_SEVERITY_WARNING, EDR_FACILITY_INTERRUPT , 0, trace, msg)

#define EDR_PCIE_AER_FATAL_INJECT(trace, msg) \
    EDR_INJECT_TRACE(EDR_SEVERITY_FATAL, EDR_FACILITY_INTERRUPT , 0, trace, msg)

#define PCIE_BDF_ID(b, d, f) ((((UINT16)(b)) << 8) |(((d) & 0x1f) << 3) | ((f) & 0x07))

#define AER_ERR_MSG_PRE "<<<<<PCIE Advanced Error Reporting >>>>>\r\n\nROOT PORT\n=========\r\n"

#define ERR_COR_SOURCE_ID(n)            ((n) & 0xffff)
#define ERR_UNCOR_SOURCE_ID(n)          ((n) >> 16)
#define PCI_BUS_GET(n)                  (((n)>> 8) & 0xff)

#define AER_LOG_TLP_MASKS   (PCI_AER_UNC_POISON_TLP|\
                             PCI_AER_UNC_ECRC|\
                             PCI_AER_UNC_UNSUP|\
                             PCI_AER_UNC_COMP_ABORT|\
                             PCI_AER_UNC_UNX_COMP|\
                             PCI_AER_UNC_MALF_TLP)

/* Typedef */

typedef struct vxbPcieAerInfo
    {
    VXB_DEV_ID pDev;
    UINT16     aerOffset;
    UINT32     uncorSts;
    UINT32     uncorMask;
    UINT32     corMask;
    UINT32     corSts;
    UINT32     headerLog0;
    UINT32     headerLog1;
    UINT32     headerLog2;
    UINT32     headerLog3;
    UINT32     rootSts;
    UINT32     id;
    UINT8      severity;	/* 0:NONFATAL | 1:FATAL | 2:COR */
    }AER_INFO;

/* LOCAL */
/* AER error strings */

LOCAL const char * aerErrMessageString[] = {
    "Correctable Error Message Received",
    "Multiple Correctable Error Message Received",
    "Fatal/Non-fatal Error Message Received",
    "Multiple Fatal/Non-fatal Error Message Received",
    "First Uncorrectable Fatal Error Message Received",
    "Non-Fatal Uncorrectable Error Message Received",
    "Fatal Uncorrectable Error Message Received",
};

LOCAL const char *aerCorErrString[] = {
    "Receiver Error",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "Bad TLP",
    "Bad DLLP",
    "RELAY_NUM Rollover",
    NULL,
    NULL,
    NULL,
    "Replay Timer Timeout",
    "Advisory Non-Fatal Error",
    "Corrected Internal Error",
    "Header Log Overflow",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

LOCAL const char *aerUnCorErrString[] = {
    "Undefined",
    NULL,
    NULL,
    NULL,
    "Data Link Protocol Error",
    "Surprise Down Error",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "Poisoned TLP",
    "Flow Control Protocol Error",
    "Completion Timeout Error",
    "Completer Abort Error",
    "Unexpected Completion Error",
    "Receiver Overflow Error",
    "Malformed TLP",
    "ECRC Error",
    "Unsupported Request Error",
    "ACS Violation",
    "Uncorrectable Internal Error",
    "MC Blocked TLP",
    "AtomicOp Egress Blocked",
    "TLP Prefix Blocked Error",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

IMPORT void vxbRpAerRegister (VXB_DEV_ID pDev);
IMPORT void vxbPcieAerRpIntEnable (VXB_DEV_ID pDev);
IMPORT STATUS vxbPcieAerCapEnable (VXB_DEV_ID pDev);
IMPORT void vxbPcieAerCapDisable (VXB_DEV_ID pDev);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbPcieAerH */
