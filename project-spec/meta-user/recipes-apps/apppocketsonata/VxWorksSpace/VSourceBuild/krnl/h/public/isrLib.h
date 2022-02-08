/* isrLib.h - ISR objects header */

/*
 * Copyright (c) 2003, 2006, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,29apr10,pad  Moved extern C statement after include statements.
01e,30oct09,jpb  Updated for LP64 support.
01d,11jul06,zl   moved isrIdCurrent to private header file.
01c,29oct03,kam  ISR Object code inspection mods
01b,04jun03,kam  removed definition of ISR_ID and moved to vxWind.h
01a,03jun03,kam  written.
*/

#ifndef __INCisrLibh
#define __INCisrLibh

/* includes */
    
#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_isrLib_ISR_NOT_INIT			(M_isrLib | 1)
#define S_isrLib_INVALID_PARAM			(M_isrLib | 2)

/* typedefs */

typedef STATUS (*ISR_HANDLER_ROUTINE) (_Vx_usr_arg_t arg);

typedef struct isr_desc
    {
    ISR_ID              isrId;        /* ISR_ID                               */
    char *              name;         /* name                                 */
    ULONG               isrTag;       /* interrupt tag                        */
    UINT                count;        /* # of times this ISR has been invoked */
    UINT    	        serviceCount; /* # of times this ISR has returned OK  */
    UINT64	        cpuTime;      /* cpu time spent in ISR 		      */  
    ISR_HANDLER_ROUTINE handlerRtn;   /* pointer to handler routine           */
    _Vx_usr_arg_t       arg;          /* parameter to be passed to routine    */
    UINT                options;      /* ISR object options                   */
    } ISR_DESC;
    
/* externs */

/* variables */

/* routines */
    
extern ISR_ID isrCreate (char * name, ULONG isrTag, ISR_HANDLER_ROUTINE handler,
        _Vx_usr_arg_t parameter, UINT options);
extern STATUS isrDelete (ISR_ID isrId);
extern STATUS isrInvoke (ISR_ID isrId);
extern ISR_ID isrIdSelf (void);
extern STATUS isrInfoGet (ISR_ID isrId, ISR_DESC * pIsrDesc);

extern STATUS isrShow (ISR_ID isrId);

#ifdef __cplusplus
}
#endif

#endif /* __INCisrLibh */
