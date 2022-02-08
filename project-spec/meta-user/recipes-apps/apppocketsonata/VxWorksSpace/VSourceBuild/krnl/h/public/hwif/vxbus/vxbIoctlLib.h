/* vxbIoctlLib.h - VxBus subsystem header file */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12feb16,jsv  Added device flags to VXB_DEV_DESC
13oct15,wap  Add inclusion of limits.h
06oct15,wap  Correct C++ protection
02oct15,wap  Add prototype for initialization routine
02oct15,wap  Add support for user-space VxBus interface (F2165)
11jun15,wap  Add device manipulation ioctls (F3973)
11jun15,wap  Correct typo in VXB_IO_TYPE_I2C macro name
09may15,wap  Change key values to VXB_KEY type
             Change class type to UINT32, define device types
19dec14,ggm  US50371 - replaced vxbd_targ with vxbd_func.
02dec14,ggm  US50371 - added to support vxBus device tree walk.
20oct14,wap  written
*/

/*
DESCRIPTION
*/

#ifndef __INCvxbIoctlLibh
#define __INCvxbIoctlLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

#include <hwif/util/vxbAccess.h>
#include <hwif/util/vxbResourceLib.h>
#include <subsys/int/vxbIntLib.h>

#define VXB_KEY_NONE            0

/* Device flags */

#define VXB_IO_FLAG_ATTACHED    0x00000001
#define VXB_IO_FLAG_LOANED      0x00000002

/* Device types */

#define VXB_IO_TYPE_NEXUS    0x00000001
#define VXB_IO_TYPE_FDT      0x00000002
#define VXB_IO_TYPE_SIMPLE   0x00000003
#define VXB_IO_TYPE_PCI      0x00000004
#define VXB_IO_TYPE_GPIO     0x00000005
#define VXB_IO_TYPE_I2C      0x00000006

typedef struct vxb_dev_desc
    {
    VXB_KEY             vxbd_parentkey;         /* Parent device node */
    VXB_KEY             vxbd_nodekey;           /* Child node */
    char                vxbd_name[PATH_MAX];
    UINT32              vxbd_unit;
    char                vxbd_desc[PATH_MAX];
    UINT32              vxbd_bus;               /* bus number */
    UINT32              vxbd_dev;               /* device number */
    UINT32              vxbd_lun;               /* logical unit number */
    UINT32              vxbd_class;             /* class */
    UINT32              vxbd_vid;               /* Vendor ID */
    UINT32              vxbd_did;               /* Device/product ID */
    UINT32              vxbd_flags;             /* VxBus Flags */
    UINT32              vxbd_rsvd0;
    UINT32              vxbd_rsvd1;
    UINT32              vxbd_rsvd2;
    } VXB_DEV_DESC;

/* Compatibility */

#define vxbd_func vxbd_lun

typedef struct vxb_res_desc
    {
    VXB_KEY             vxbd_nodekey;           /* Device ID */
    VXB_KEY             vxbd_reskey;            /* Resource ID */
    UINT32              vxbd_id;
    VXB_RESOURCE_ADR    vxbd_res_adr;
    VXB_RESOURCE_IRQ    vxbd_res_irq;
    } VXB_RES_DESC;

typedef struct vxb_int_desc
    {
    VXB_KEY		vxbd_nodekey;
    VXB_KEY		vxbd_reskey;
    cpuset_t		vxbd_cpuset;
    } VXB_INT_DESC;

typedef struct vxb_reg_desc
    {
    VXB_KEY             vxbd_reskey;
    VXB_KEY             vxbd_devkey;
    UINT32              vxbd_regwidth;
    UINT64              vxbd_regoffset;
    UINT32              vxbd_regval;
    } VXB_REG_DESC;

/*
 * Note: the pointer parameter type is not supported with
 * this interface as pointers can't be passed via ioctl()s.
 * Also, strings must have a fix maximum size to avoid
 * ambiguity when doing scMemValidate().
 */

#define VXB_IO_PARAM_INT32         0x0001
#define VXB_IO_PARAM_INT64         0x0002
#define VXB_IO_PARAM_STRING        0x0003

typedef union vxb_io_param_value
    {
    UINT32		int32Val;
    UINT64		int64Val;
    char		stringVal[PATH_MAX];
    } VXB_IO_PARAM_VALUE;

typedef struct vxb_param_desc
    {
    VXB_KEY		vxbd_nodekey;
    char 		vxbd_paramname[PATH_MAX];
    UINT32              vxbd_paramtype;
    VXB_IO_PARAM_VALUE  vxbd_value;
    } VXB_PARAM_DESC;

/* Get a node using its key */

#define VXBIOCGNODE		_IOWR('v', 128, VXB_DEV_DESC)

/* Get the next child of a parent node */

#define VXBIOCGNEXTNODE		_IOWR('v', 129, VXB_DEV_DESC)

/* Get the next resource of a node */

#define VXBIOCGRESOURCE		_IOWR('v', 130, VXB_RES_DESC)

/* Loan a device node to a guest */

#define VXBIODEVLOAN		_IOW('v', 131, VXB_DEV_DESC *)

/* Reclaim a device node from a guest */

#define VXBIODEVRECLAIM		_IOW('v', 132, VXB_DEV_DESC *)

/* Reset a device node (requires a driver to be present) */

#define VXBIODEVRESET		_IOW('v', 133, VXB_DEV_DESC *)

/* Force a bus rescan */

#define VXBIODEVRESCAN		_IOW('v', 134, VXB_DEV_DESC *)

/* Read device parameters */

#define VXBIODEVSPARAM		_IOW('v', 135, VXB_PARAM_DESC *)

/* Modify device parameters */

#define VXBIODEVGPARAM		_IOR('v', 136, VXB_PARAM_DESC *)

/* Bind interrupt for a node to a specific CPU */

#define VXBIODEVINTBIND		_IOWR('v', 137, VXB_INT_DESC *)

IMPORT void vxbIoctlLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbIoctlLibh */
