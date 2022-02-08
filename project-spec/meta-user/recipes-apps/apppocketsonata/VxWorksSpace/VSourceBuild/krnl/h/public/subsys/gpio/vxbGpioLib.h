/* vxbGpioLib.h - vxBus GPIO interfaces module */

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
12nov14,pmr  conditionalize show routine with _WRS_CONFIG_DEBUG_FLAG
07may15,jmz  US55875 - Move definitions for INTR_TRIGER and INTR_POLARITY to
             vxbIntLib.h
04jul13,c_t  written
*/

/*
DESCRIPTION

This library provides the GPIO specific interfaces

*/

#ifndef _INC_vxbGpioLibH
#define _INC_vxbGpioLibH

/* includes */
#include <subsys/int/vxbIntLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_DIR_INPUT          (0)
#define GPIO_DIR_OUTPUT         (1)

#define GPIO_VALUE_LOW          (0)
#define GPIO_VALUE_HIGH         (1)
#define GPIO_VALUE_INVALID      (0xff)

/* 
 * Bitmap unit size, controller driver should ensure bitmap memory round up 
 * to bitmap unit size which is 4 bytes.
 */

#define GPIO_BIT_UNIT_SIZE      (32)

typedef struct vxbGpioCtrl {
    SL_NODE gpioNode;    /* this node */
    VXB_DEV_ID  pDev;    /* pointer to the controller instance */
    UINT32  firstPin;    /* the first pin id for this controller */
    UINT32  length;      /* how many gpio in this controller */
    UINT32  *pValidBmp;  /* this is a valid bitmap for this controller.
                                              bit 0 means free, 1 means used. */
    UINT32  gpioCells;   /* parameter numbers when called by other module */
    
    /* allocate a pin. */
    STATUS (*gpioAlloc)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id                   /* pin to allocate */
        );
    /* free a pin */
    STATUS (*gpioFree)  
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id                   /* pin to free */
        );
    /* get direction of a pin */
    UINT32 (*gpioGetDir)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id
        );
    /* set direction of a pin */
    STATUS (*gpioSetDir)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        UINT32 dir
        );
    /* get value of a pin */
    UINT32 (*gpioGetValue)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id
        );
    /* set value to a pin */
    STATUS (*gpioSetValue)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        UINT32 value
        );
    /* set debounce time in micro second (us) */
    STATUS (*gpioSetDebounce)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        UINT32 us
        );
    /* find the global GPIO id for given GPIO arg list */
    int  (*gpioFindByFdt)
        (
        struct vxbGpioCtrl *pCtrl, 
        UINT32* pArgs        
        );
    /* bind the GPIO */
    int  (*gpioBind)
        (
        struct vxbGpioCtrl *pCtrl, 
        UINT32* pArgs
        );
    /* config interrupt trigger mode */
    STATUS (*gpioIntConfig)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        INTR_TRIGER trig,
        INTR_POLARITY pol
        );
    /* connect interrupt to this gpio */
    STATUS (*gpioIntConnect)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        VOIDFUNCPTR     pIsr,       /* ISR */
        void *          pArg        /* parameter */
        );
    /* disconnect interrupt from this gpio */
    STATUS (*gpioIntDisConnect)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        VOIDFUNCPTR     pIsr,       /* ISR */
        void *          pArg        /* parameter */
        );
    /* enable interrupt to this gpio */
    STATUS (*gpioIntEnable)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        VOIDFUNCPTR     pIsr,       /* ISR */
        void *          pArg        /* parameter */
        );
    /* disable interrupt to this gpio */
    STATUS (*gpioIntDisable)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 id,
        VOIDFUNCPTR     pIsr,       /* ISR */
        void *          pArg        /* parameter */
        );

#ifdef _WRS_CONFIG_DEBUG_FLAG
    /* show info */
    VOID (*gpioShow)
        (
        struct vxbGpioCtrl *pCtrl,
        UINT32 verbose
        );
#endif
} VXB_GPIOCTRL;
STATUS vxbGpioLibInit ();
STATUS vxbGpioAddCtlr (VXB_GPIOCTRL *);
STATUS vxbGpioFree (UINT32);
STATUS vxbGpioAlloc (UINT32);
BOOL   vxbGpioIsFree (UINT32);

/* FDT helpers */

#ifdef _WRS_CONFIG_FDT
int    vxbGpioGetByFdtIndex (VXB_DEV_ID, const char*, int);
int    vxbGpioBind (VXB_DEV_ID, const char*, int);
STATUS vxbGpioUnBind (VXB_DEV_ID, const char*, int);
#endif /* _WRS_CONFIG_FDT */

STATUS vxbGpioSetDir (UINT32, UINT32);
UINT32 vxbGpioGetDir (UINT32);
UINT32 vxbGpioGetValue (UINT32);
STATUS vxbGpioSetValue (UINT32, UINT32);
STATUS vxbGpioSetDebounce (UINT32, UINT32);

/* interrupt routines */
STATUS vxbGpioIntConfig (UINT32, INTR_TRIGER, INTR_POLARITY);
STATUS vxbGpioIntConnect (UINT32, VOIDFUNCPTR, void *);
STATUS vxbGpioIntDisconnect (UINT32, VOIDFUNCPTR, void *);
STATUS vxbGpioIntEnable (UINT32, VOIDFUNCPTR, void *);
STATUS vxbGpioIntDisable (UINT32, VOIDFUNCPTR, void *);
#ifdef _WRS_CONFIG_DEBUG_FLAG
VOID   vxbGpioShow (UINT32);
#endif
#ifdef __cplusplus
}
#endif

#endif /* _INC_vxbGpioLibH */

