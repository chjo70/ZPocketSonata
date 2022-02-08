/* vxbFdtPci.h -  VxBus FDT PCI library*/

/*
 * Copyright (c) 2013-2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
26aug16,y_y  add prefetch memory 64bit space address macro.
31mar14,l_z  change vxbFdtPciIntrGet() interface. (US37630)
25jul13,y_y  written
*/

#ifndef __INCfdtpcih
#define __INCfdtpcih

#define FDT_PCI_SPA_CS         0x00000000
#define FDT_PCI_SPA_IO         0x01000000
#define FDT_PCI_SPA_MEM        0x02000000
#define FDT_PCI_SPA_MEM64      0x03000000
#define FDT_PCI_SPA_MEM_PRE    0x42000000
#define FDT_PCI_SPA_MEM64_PRE  0x43000000

typedef struct fdtPciRange {
    ULONG       basePci;
    PHYS_ADDR   baseParent;
    size_t      len;
}VXB_FDT_PCI_RANGE;

typedef struct fdtPciIntr {
    int       addrCells;
    int       intrCells;
    int       mapLen;
    UINT32 *  map;
    UINT32 *  mask;
}VXB_FDT_PCI_INT;

/* IMPORT */

STATUS vxbFdtPciIntrGet
    (
    struct fdtPciIntr *  intrInfo,
    int                  bus,
    int                  slot,
    int                  func,
    int                  pin,
    UINT8 *              interrupt,
    VXB_INTR_ENTRY   *   pIntrEntry
    );

STATUS vxbFdtPciRanges
    (
    VXB_FDT_DEV * node,
    UINT32        type,
    struct fdtPciRange *space
    );

STATUS vxbFdtPciIntrInfo
    (
    VXB_FDT_DEV *        node,
    struct fdtPciIntr *  intrInfo
    );

STATUS vxbFdtPciGetBusRange
    (
    VXB_FDT_DEV *       node,
    UINT32 *            start,
    UINT32 *            end
    );

#endif /* __INCfdtpcih */
