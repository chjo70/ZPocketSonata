/* objLibCommon.h - common object management definitions */

/*
 * Copyright (c) 2003-2005, 2010, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04feb16,pcs  added WIND_OBJ_NAME_MAX. (V7COR-4002)
28oct14,h_k  added S_objLib_ACCESS_DENIED. (F2160)
28apr10,pad  Moved extern C statement after include statements.
22jun05,mcm  Moved _WRS_BIT_OR macro definition to vxWorksCommon.h
21jun05,mcm  Added support for ColdFire assembly - using '!' instead of
             '|' for 'bit-or'.
16aug04,dcc  added S_objLib_OBJ_LIB_NOT_INITIALIZED errno.
05mar04,dcc  added OM_DELETE_ON_LAST_CLOSE mode option and removed the
             OM_RECLAIM_DISABLE option. 
02mar04,aeg  changed OBJ_OBJECT_NOT_FOUND errno to OBJ_NOT_FOUND.
01dec03,dcc  added more errno codes.
26aug03,cjj  written based on kernel version 01s of objLib.h
*/

#ifndef __INCobjLibCommonh
#define __INCobjLibCommonh

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* max wind object name length including EOS */

#define WIND_OBJ_NAME_MAX        1024

/* Object creation mode options */

#define OM_CREATE               0x10000000
#define OM_EXCL                 0x20000000
#define OM_DELETE_ON_LAST_CLOSE 0x40000000

/* Error Status codes */

#define S_objLib_OBJ_ID_ERROR                   (M_objLib _WRS_BIT_OR 1)
#define S_objLib_OBJ_UNAVAILABLE                (M_objLib _WRS_BIT_OR 2)
#define S_objLib_OBJ_DELETED                    (M_objLib _WRS_BIT_OR 3)
#define S_objLib_OBJ_TIMEOUT                    (M_objLib _WRS_BIT_OR 4)
#define S_objLib_OBJ_NO_METHOD                  (M_objLib _WRS_BIT_OR 5)
#define S_objLib_OBJ_NO_ACCESS_RIGHTS           (M_objLib _WRS_BIT_OR 6)
#define S_objLib_OBJ_NAME_TRUNCATED             (M_objLib _WRS_BIT_OR 7)
#define S_objLib_OBJ_NAME_CLASH                 (M_objLib _WRS_BIT_OR 8)
#define S_objLib_OBJ_NOT_NAMED                  (M_objLib _WRS_BIT_OR 9)
#define S_objLib_OBJ_ILLEGAL_CLASS_TYPE         (M_objLib _WRS_BIT_OR 10)
#define S_objLib_OBJ_OPERATION_UNSUPPORTED      (M_objLib _WRS_BIT_OR 11)
#define S_objLib_OBJ_INVALID_OWNER              (M_objLib _WRS_BIT_OR 12)
#define S_objLib_OBJ_RENAME_NOT_ALLOWED         (M_objLib _WRS_BIT_OR 13)
#define S_objLib_OBJ_DESTROY_ERROR              (M_objLib _WRS_BIT_OR 14)
#define S_objLib_OBJ_HANDLE_TBL_FULL            (M_objLib _WRS_BIT_OR 15)
#define S_objLib_OBJ_NOT_FOUND                  (M_objLib _WRS_BIT_OR 16)
#define S_objLib_OBJ_INVALID_ARGUMENT           (M_objLib _WRS_BIT_OR 17)
#define S_objLib_OBJ_LIB_NOT_INITIALIZED        (M_objLib _WRS_BIT_OR 18)
#define S_objLib_ACCESS_DENIED                  (M_objLib _WRS_BIT_OR 19)

#ifdef __cplusplus
}
#endif

#endif /* __INCobjLibCommonh */
