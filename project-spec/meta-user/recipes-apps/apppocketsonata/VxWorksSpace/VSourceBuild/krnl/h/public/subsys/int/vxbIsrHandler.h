/* vxbIsrHandler.h - VxWorks interrupt handler library */

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
06aug16,wap  Add IMPORT keyword to function prototypes
03mar16,wap  Remove unused macros and prototypes
29feb16,wap  Correct type of 'node' element in VXB_INTR_LIST structure
17feb16,wap  Change vxbIsrEnable() and vxbIsrDisable() to both return
             BOOL rather than STATUS
02feb16,wap  Add extra argument to vxbIsrHandlerInit()
26jan16,wap  Update API, modify chaining support to use sllLib (F6448)
14may15,wap  Add support for vxbIntReroute(), stop requiring callback
             for vxbIsrAdd() (F3973)
25apr14,b_m  make VXB_INT_ISR_CALL macro more robust. (US#37631)
09apr14,ylu  added vxbIsrHandlerInit function.
14aug13,l_z  created
*/

#ifndef __INCvxbIsrHandlerbh
#define __INCvxbIsrHandlerbh

#ifdef _WRS_CONFIG_FDT
#include <hwif/buslib/vxbFdtLib.h>
#endif /* _WRS_CONFIG_FDT */

#include <sllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VXB_INTR_VEC_MASK         0x0000ffff
#define VXB_INTR_VEC_CONNECT      0x00010000
#define VXB_INTR_VEC_ENABLE       0x00020000

#define VXB_NAME_UNIT_SIZE        63

#define VXB_ISR_BASE_ANY	0xFFFFFFFF

#define VXB_INT_ISR_CALL(vec)                               \
    {                                                       \
    if (vxbIntrVecs[(vec)] == NULL)                         \
        vxbIsrStray((void *)(vec));                         \
    else                                                    \
        {                                                   \
        void (*pIsr)(void *) = vxbIntrVecs[(vec)]->isr;     \
        FAST void * pArg = vxbIntrVecs[(vec)]->pArg;        \
        (*pIsr)(pArg);                                      \
        }                                                   \
    }

typedef struct vxbIntrVec {
    void        (*isr)(void * pArg);
    void *      pArg;
    char        nameUnit[VXB_NAME_UNIT_SIZE + 1];
    void *      pic;
    cpuset_t    cpu;
    UINT32      flag;
    void *      pRes;
} VXB_INTR_VEC;

typedef struct vxbIntrList {
    SL_NODE		node;
    VXB_INTR_VEC 	pVec;
} VXB_INTR_LIST;

IMPORT VXB_INTR_VEC  ** vxbIntrVecs;
IMPORT UINT32 vxbMaxIntrVec;
IMPORT STATUS vxbIsrHandlerInit (UINT32 numVec, UINT32 numChain);
IMPORT void   vxbIsrStray (void * pArg);
IMPORT void   vxbIsrChain (void * pArg);
IMPORT UINT32 vxbIsrAlloc (UINT32 count);
IMPORT STATUS vxbIsrReserve (UINT32 base, UINT32 count);
IMPORT STATUS vxbIsrRelease (UINT32 base, UINT32 count);
IMPORT BOOL   vxbIsrAllocated (int vec);
IMPORT BOOL   vxbIsrConnected (int vec);
IMPORT void * vxbIsrPicGet (int vec);
IMPORT void   vxbIsrPicSet (int vec, void *pic);
IMPORT cpuset_t vxbIsrCpuGet (int vec);
IMPORT void   vxbIsrCpuSet (int vec, cpuset_t cpu);
IMPORT BOOL   vxbIsrEnabled (int vec);
IMPORT void   vxbIsrSetIntrEntry (int vec, void * pVxbIntrEntry);
IMPORT STATUS vxbIsrGetIntrEntry (int vec, void ** ppVxbIntrEntry);
IMPORT STATUS vxbIsrCreate (int vec);
IMPORT STATUS vxbIsrAdd
    (
    char *      nameUnit,
    void *      pRes,
    int         vec,
    VOIDFUNCPTR isr,
    void *      pArg
    );
IMPORT STATUS vxbIsrRemove (void * pRes, int vec, VOIDFUNCPTR isr, void * pArg);
IMPORT BOOL vxbIsrEnable (void * pRes, int vec, VOIDFUNCPTR isr, void * pArg);
IMPORT BOOL vxbIsrDisable (void * pRes, int vec, VOIDFUNCPTR isr, void * pArg);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbIsrHandlerbh */
