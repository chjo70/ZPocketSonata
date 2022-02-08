/* vxbMethod.h - VxBus method header file */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08may15,wap  Move busid definition to vxbBusType.h (F3973)
24sep14,l_z  fix DMA buff memory leak (V7PRO-1090)
17jul13,l_z  Created
*/

#ifndef _INC_VXBMETHOD_H
#define _INC_VXBMETHOD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Type for method ID */

#ifdef _WRS_CONFIG_LP64
typedef ULONG  VXB_METHOD_ID;
#else
typedef UINT32 VXB_METHOD_ID;
#endif

#define VXB_NO_METHOD                     (-2)

/* method related macros, for driver use and method caller use */

#define VXB_DEVMETHOD_END                 { 0, NULL }
#define VXB_DEVMETHOD_DECL(NAME)          IMPORT char NAME##_desc[];
#define VXB_DEVMETHOD_DEF(METHOD, STRING) char METHOD##_desc[]=STRING;
#define VXB_DEVMETHOD_CALL(METHOD)        ((VXB_METHOD_ID)(&METHOD##_desc[0]))


/*
 *  An alternative method for bus controllers to provide the
 *  methods used by downstream devices.  This structure is
 *  provided so that the controller can provide a null-terminated
 *  list of method/handler pairs.
 *
 *  When a driver fetches the access methods, the standard methods
 *  are used first.  If the method is not one of the standard
 *  methods (specified in the vxbAccessList structure), or if the
 *  method specified is NULL in the controller's standard methods,
 *  then the vxbAccessMethodsGet() routine searches through any
 *  methods listed in the pMethods field of the vxbAccessList
 *  structure.
 *
 *  In addition, this structure is used by all devices to provide
 *  services to OS modules such as power management.
 */

typedef struct vxbDrvMethod
    {
    VXB_METHOD_ID     drvMethodId;
    FUNCPTR           handler;
    } VXB_DRV_METHOD;


#ifdef __cplusplus
}
#endif

#endif /* _INC_VXBMETHOD_H */

