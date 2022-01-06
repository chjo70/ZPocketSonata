/* vxbLib.h - VxBus library header file */

/*
 * Copyright (c) 2013-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08nov17,syt  Added an new API declaration for vxbDrvGet().(V7PRO-3971)
16jun17,msx  Redefined vxbMemAlloc and vxbMemFree for unit test.
16dec16,cfm  update PHYS_ADDR to 64 bit for IA32 PAE (F7142)
09nov16,mca  silenced a 'declared implictly' warning for vxbDevRemove
23sep16,wap  Add vxbDevAcquireByPath()
20sep16,wap  Add vxbDevNameAddrSet()/vxbDevNameAddrGet(),
             VXB_FLAG_NAMEADDRALLOCED flag (F7769)
16may16,wap  Break explicit linker dependencies with vxbParamLib
             and vxbRtpIoctlLib
12apr16,wap  Add vxbDevAcquireBySerial()
29oct15,wap  Correct the size of VIRT_ADDR for IA32 builds
02oct15,wap  Fix missing vxbDevSerialGet()/vxbDevSerialSet()
29sep15,wap  Add support for user-space VxBus interface (F2165)
03aug15,gws  resolve compiler warnings (US64063)
19nov15,mmi  remove unused function prototype
03nov15,mmi  add device inclusion methods (HYP-10775)
23jul15,wap  Add missing vxbDevClassGet() prototype
12jun15,wap  Add device manipulation ioctls (F3973)
11may15,wap  Add default parameter pointer to driver structure
             Also add vxbClassAdd()/vxbClassRemove() prototypes
08may15,wap  Add support for loaning devices to RTPs (F3973)
             Add vxbDevAcquireByName(), vxbDevUnitSet() and
             vxbDevSerialGet()/vxbDevSerialSet() accessor APIs
28nov14,l_z  add vxbDevUnit/NameGet(). (V7PRO-1523)
07jan14,y_y  code clean
18dec13,cww  made dataset header private
01a,17jul13,l_z  Created
*/

#ifndef __INCvxbLibh
#define __INCvxbLibh

#include <stdlib.h>
#include <sllLib.h>
#ifdef _WRS_KERNEL
#include <spinLockLib.h>
#include <private/datasetP.h>
#endif /* _WRS_KERNEL */
#include <hwif/vxbus/vxbMethod.h>
#include <hwif/vxbus/vxbBusType.h>
#include <hwif/vxbus/vxbLockLib.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* pName: device name */

#define MAX_DEV_NAME_LEN        31  /* 31-byte device names */
#define MAX_DRV_NAME_LEN        31
#define VXB_MAXBARS             10

/* Serial number/identifier type */

typedef UINT64 VXB_KEY;

/* VxBus driver structure */

typedef struct vxbDrv
    {
    SL_NODE           vxbNode; /* must always be first element */
    char *            pVxbName;
    char *            pVxbDesc;
    VXB_BUSTYPE_ID    vxbClass;
    UINT32            vxbFlags;
    int               vxbRefCnt;
    VXB_DRV_METHOD *  pVxbMethods;
    void *            pVxbParamDefaults;
    } VXB_DRV;

typedef struct vxbDev * VXB_DEV_ID;

#define VXB_FLAG_DYNAMIC     0x00000001U /* VXB_DEV_ID was malloc()ed */
#define VXB_FLAG_PROBED      0x00000002U /* Successfully probed, but not
                              yet attached (set by vxbDevProbe(),
                              cleared by vxbDevAttach()) */
#define VXB_FLAG_ATTACHING   0x00000004U /* The device is attaching */
#define VXB_FLAG_ATTACHED    0x00000008U /* Successfully attached (set by
                              vxbDevAttach(), cleared by
                              vxbDevDetach()) */
#define VXB_FLAG_NAMEALLOCED 0x00000010U /* the name is allocated */

#define VXB_FLAG_LOANED      0x00000020U /* Loaned to guest */
#define VXB_FLAG_RESETTING   0x00000040U /* Reset in progress */
#define VXB_FLAG_RECLAIMING  0x00000080U /* Reclaim in progress */
#define VXB_FLAG_NAMEADDRALLOCED 0x00000100U /* the unit/address is allocated */

/* VxBus driver flag */

#define VXB_DRVFLAG_RESET    0x00000001U /* Driver supports reset */
#define VXB_DRVFLAG_PARAM    0x00000002U /* Driver has default parameter */

#ifndef _WRS_KERNEL

/* Linker set feature is not supported in RTPs. */

#define DATA_SET(x,y,z)

#if (CPU_FAMILY == I80X86)
#if defined (_WRS_CONFIG_LP64) || defined (_WRS_CONFIG_IA32_PAE)
typedef UINT64 PHYS_ADDR;
#else /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */
typedef UINT32 PHYS_ADDR;
#endif /* _WRS_CONFIG_LP64 || _WRS_CONFIG_IA32_PAE */
#else /* CPU_FAMILY == I80X86 */
typedef UINT64 PHYS_ADDR;
#endif /* CPU_FAMILY == I80X86 */

#endif /* _WRS_KERNEL */

#ifndef LKM
#define VXB_DRV_DEF(vxbDrv)                 \
    DATA_SET(driver, 0, vxbDrv);

#define VXB_NEXUS_DEV_DEF(vxbDev)           \
    DATA_SET(device, 0, vxbDev);

#else
#define VXB_DRV_DEF(vxbDrv)                 \
    void vxLkmInit()                        \
        {                                   \
        (void *)vxbDrvAdd(vxbDrv);          \
        }
#endif

#ifdef _WRS_UNIT_TEST
IMPORT void * vxbMemAlloc(size_t size);
IMPORT void   vxbMemFree(void * ptr);
#else
#define vxbMemAlloc(size) calloc(1,size)
#define vxbMemFree(ptr) free(ptr)
#endif

IMPORT STATUS vxbLibInit (void);

/* VxBus device tree management APIs */

IMPORT STATUS vxbDevCreate (VXB_DEV_ID *);
IMPORT STATUS vxbDevDestroy (VXB_DEV_ID);

IMPORT STATUS vxbDevAdd (VXB_DEV_ID, VXB_DEV_ID);
IMPORT STATUS vxbDevRemove (VXB_DEV_ID);

IMPORT VXB_DEV_ID vxbDevParent (struct vxbDev * pDev);
IMPORT void   vxbDevClassSet (VXB_DEV_ID pDev, VXB_BUSTYPE_ID vxbClass);
IMPORT VXB_BUSTYPE_ID vxbDevClassGet (VXB_DEV_ID pDev);
IMPORT void   vxbDevNameSet (VXB_DEV_ID pDev, char * pName, BOOL copy);
IMPORT char * vxbDevNameGet (VXB_DEV_ID pDev);
IMPORT void   vxbDevNameAddrSet (VXB_DEV_ID pDev, char * pName, BOOL copy);
IMPORT char * vxbDevNameAddrGet (VXB_DEV_ID pDev);
IMPORT void   vxbDevGetNameUnit (VXB_DEV_ID pDev, char * buf, size_t len);
IMPORT void   vxbDevIvarsSet (VXB_DEV_ID pDev, void * pIvar);
IMPORT void * vxbDevIvarsGet (VXB_DEV_ID pDev);
IMPORT void   vxbDevSoftcSet (VXB_DEV_ID pDev,void * pSoftc);
IMPORT void * vxbDevSoftcGet(VXB_DEV_ID pDev);
IMPORT void   vxbDevDrvDataSet (VXB_DEV_ID pDev, void * pDrvData);
IMPORT void * vxbDevDrvDataGet (VXB_DEV_ID pDev);
IMPORT UINT32 vxbDevUnitGet (VXB_DEV_ID pDev);
IMPORT void   vxbDevUnitSet (VXB_DEV_ID pDev, UINT32 unit);
IMPORT VXB_DEV_ID vxbDevAcquireByName (char * pName, UINT32 unit);
IMPORT VXB_DEV_ID vxbDevAcquireBySerial (VXB_KEY);
IMPORT VXB_DEV_ID vxbDevAcquireByPath (char *);
IMPORT void   vxbDevAcquire (VXB_DEV_ID pDev);
IMPORT void   vxbDevRelease (VXB_DEV_ID pDev);
IMPORT VXB_KEY vxbDevSerialGet (VXB_DEV_ID pDev);
IMPORT void   vxbDevSerialSet (VXB_DEV_ID pDev, VXB_KEY);
#ifndef _WRS_CONFIG_VXBUS_BASIC
IMPORT STATUS vxbDevLoan (VXB_DEV_ID pDev);
IMPORT STATUS vxbDevReclaim (VXB_DEV_ID pDev);
IMPORT STATUS vxbDevReset (VXB_DEV_ID pDev);
#endif /* _WRS_CONFIG_VXBUS_BASIC */
IMPORT UINT32 vxbDevFlagsGet (VXB_DEV_ID pDev);
void   vxbDevFlagsSet (VXB_DEV_ID pDev, UINT32 vxbFlags);
IMPORT VXB_DEV_ID vxbDevFirstChildGet (VXB_DEV_ID pParent);
IMPORT VXB_DEV_ID vxbDevNextChildGet (VXB_DEV_ID pChild);
IMPORT STATUS vxbDevMatch (VXB_DEV_ID pDev);
IMPORT STATUS vxbDevPathGet (VXB_DEV_ID pDev, char * pBuf, size_t len);

/* VxBus driver list management APIs */

IMPORT VXB_DRV * vxbDrvGet (VXB_DEV_ID);
IMPORT STATUS vxbDrvAdd (VXB_DRV *);
#ifndef _WRS_CONFIG_VXBUS_BASIC
IMPORT STATUS vxbDrvRemove (VXB_DRV *);
#endif /* _WRS_CONFIG_VXBUS_BASIC */

/* VxBus class list management APIs */

IMPORT STATUS vxbClassAdd (VXB_BUSTYPE *);
IMPORT STATUS vxbClassRemove (VXB_BUSTYPE *);

/* Method handling routines */

IMPORT FUNCPTR vxbDevMethodFind (VXB_DEV_ID, VXB_METHOD_ID);

#ifndef _WRS_CONFIG_VXBUS_BASIC
/* Ioctl helper routine */

IMPORT STATUS vxbDevIoctlHelper (VXB_DEV_ID, int, void *);
#endif /* _WRS_CONFIG_VXBUS_BASIC */

/* Exclusion list management */

IMPORT void vxbExcludeInit (void);
IMPORT STATUS vxbExcludeAdd (char *);
IMPORT STATUS vxbExcludeDelete (char *);
IMPORT BOOL vxbExcludeMatch (char *);

/* vxbParamLib callouts */

typedef STATUS (*VXBPARAMTABLECREATEFUNC)(VXB_DEV_ID);
typedef void (*VXBPARAMTABLEDESTROYFUNC)(VXB_DEV_ID);
IMPORT VXBPARAMTABLECREATEFUNC _func_vxbParamTableCreateFunc;
IMPORT VXBPARAMTABLEDESTROYFUNC _func_vxbParamTableDestroyFunc;

/* vxbRtpIoctlLib callouts */

#if defined(_WRS_KERNEL) && defined(_WRS_CONFIG_VXBUS_USER)
typedef STATUS (*VXBRTPDEVCREATEFUNC)(VXB_DEV_ID);
typedef STATUS (*VXBRTPDEVDELETEFUNC)(VXB_DEV_ID);
IMPORT VXBRTPDEVCREATEFUNC _func_vxbRtpDevCreateFunc;
IMPORT VXBRTPDEVDELETEFUNC _func_vxbRtpDevDeleteFunc;
#endif /* _WRS_KERNEL && _WRS_CONFIG_VXBUS_USER */

#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbDevMethod.h>

#endif /* __INCvxbLibh */
