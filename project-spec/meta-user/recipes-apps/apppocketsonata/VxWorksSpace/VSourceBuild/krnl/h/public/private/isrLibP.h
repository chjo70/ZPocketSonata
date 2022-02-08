/* isrLibP.h - ISR objects private header */

/*
 * Copyright (c) 2003-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01n,29apr10,pad  Moved extern C statement after include statements.
01m,30oct09,jpb  Updated for LP64 support.
01l,27aug08,jpb  Renamed VSB header file
01k,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01j,29oct07,slk  add _func_isrDelete
01i,24oct07,slk  add ISR information function
01h,06apr07,zl   added ISR connect/disconnect function pointers
01g,11jul06,zl   added declaration of isrIdCurrent (moved from public header).
01f,15jul05,md   added SMP support
01e,02jun04,lei  added 4 UINT32 variables to WIND_ISR(SPR 97866)
01d,29apr04,cjj  added isrShowInit() prototype
01c,29oct03,kam  ISR Object code inspection mods
01b,04jun03,kam  updated structure name from windISR to wind_isr
01a,03jun03,kam  written.
*/

#ifndef __INCisrLibPh
#define __INCisrLibPh

/* includes */

#include <vsbConfig.h>
#include <isrLib.h>
#include <private/objLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

    
/* typedefs */

typedef struct wind_isr
    {
    OBJ_CORE      objCore;       /* 0x00/0x00 wind object management struct */
    ULONG         isrTag;        /* 0x40/0x80 interrupt tag                 */
    UINT          count;         /* 0x48/0x88 # of times this ISR has 
                                              been invoked                  */
    UINT    	  serviceCount;	 /* 0x4c/0x8c # of times this ISR has 
                                              returned OK                   */
    UINT64	  cpuTime;	 /* 0x50/0x90 cpu time spent in ISR         */ 
    ISR_HANDLER_ROUTINE handlerRtn; /* 0x58/0x98 pointer to handler routine */
    _Vx_usr_arg_t arg;           /* 0x60/0xa0 parameter to be passed 
                                              to routine                    */
    UINT          options;       /* 0x68/0xa8 ISR object options            */ 
    UINT32	  reserved1;	 /* 0x6c/0xac reserved 1 	            */
    UINT32	  reserved2;	 /* 0x70/0xb0 reserved 2 		    */
    UINT32	  spare1;	 /* 0x74/0xb8 possible user extension       */
    UINT32	  spare2;	 /* 0x78/0xbc possible user extension       */  
    UINT32	  spare3;	 /* 0x7c/0xc0 possible user extension	    */
    UINT32	  spare4;	 /* 0x80/0xc4 possible user extension	    */
    } WIND_ISR;

typedef ISR_ID (*ISR_CREATE_FUNC) (char *              name,
				   ULONG               isrTag,
				   ISR_HANDLER_ROUTINE handlerRtn,
				   _Vx_usr_arg_t       parameter,
				   UINT                options);
typedef STATUS (*ISR_CONNECT_FUNC) (VOIDFUNCPTR * vector, 
				    VOIDFUNCPTR   routine,
				    _Vx_usr_arg_t parameter);
typedef STATUS (*ISR_DISCONNECT_FUNC) (VOIDFUNCPTR * vector, 
				       VOIDFUNCPTR   routine,
				       _Vx_usr_arg_t parameter);
typedef STATUS (*ISR_DISPATCH_FUNC) (ISR_ID  isrId );

typedef STATUS (*ISR_INFO_FUNC) (ISR_ID  isrId,
                                 ISR_DESC *  pIsrDesc );

typedef STATUS (*ISR_DELETE_FUNC) (ISR_ID  isrId);

/* externs */

#ifndef  _WRS_CONFIG_SMP
extern ISR_ID  isrIdCurrent;
#endif

extern CLASS_ID isrClassId;
extern ISR_CONNECT_FUNC    _func_isrConnect;
extern ISR_DISCONNECT_FUNC _func_isrDisconnect;
extern ISR_CREATE_FUNC     _func_isrCreate;
extern ISR_DISPATCH_FUNC   _func_isrDispatcher;
extern ISR_INFO_FUNC       _func_isrInfo;
extern ISR_DELETE_FUNC     _func_isrDelete;

extern STATUS isrLibInit (void);
extern STATUS isrShowInit (void);
extern STATUS isrInit (ISR_ID isrId, char * name, ULONG isrTag, 
                       FUNCPTR handlerRtn, _Vx_usr_arg_t parameter, 
                       UINT options);
extern STATUS isrTerminate (ISR_ID isrId);
extern STATUS isrDestroy (WIND_ISR * isrId, BOOL dealloc);

extern STATUS isrHandlerSet (ISR_ID isrId, ISR_HANDLER_ROUTINE routine, 
                             _Vx_usr_arg_t parameter);
extern STATUS isrCpuTimeGet (ISR_ID isrId, UINT64 * cpuTime);
extern STATUS isrCpuTimeSet (ISR_ID isrId, UINT64 cpuTime);

#ifdef __cplusplus
}
#endif

#endif /* __INCisrLibPh */
