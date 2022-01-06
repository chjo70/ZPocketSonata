/* cpcLibP.h - cross processor call header file */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
01e,13may10,cww  LP64 adaptation
01d,15nov06,mmi  cpcInvoke turned to void function
01c,12jun06,mmi  remove cpcIntHandler() and initOk. rename CPC_IPI_INVOKE_FUNC
01b,06jun06,mmi  Add CPC_ALL_CPUS, CPC_SYNC_MANUAL and cpcSync(), added cpuset_t
01a,05may06,mig  written
*/

#ifndef __INCpcLibPh
#define __INCpcLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* Synchronization flags */

#define VX_CPC_SYNC        1  /* wait untill the cpc call is complete */
#define VX_CPC_ASYNC       2  /* send ack before cpc call is complete */

/*
 * When VX_CPC_SYNC_MANUAL is specified the CPC call function handles the
 * synchronization between the caller and target processors.
 * This flag is used in cases where the CPC call function needs to synchronize
 * the communication between the different processors. For example if the CPC
 * call function task is to lock remote processor interrupts then the callee 
 * must send an ACK within the CPC call function execution. This implies that
 * cpcSync() is embedded in the CPC call function. Otherwise the caller
 * processor will spin waiting for an ACK untill interrupts are unlocked in
 * every target processor. To prevent such scenario this flag is specified and
 * the ACK is sent by executing cpcSync(). Therefore the callee processors will
 * not send an ACK when VX_CPC_SYNC_MANUAL flag is specified. Note that an ACK
 * is sent by updating cpcCpuCount.  
 */

#define VX_CPC_SYNC_MANUAL 3  

/* typedefs */

/* CPC handler function */

typedef void   (*CPC_FUNC)	       (void * param, size_t paramSize);

typedef STATUS (*CPC_IPI_CONNECT_FUNC) (VOIDFUNCPTR * vector, 
					VOIDFUNCPTR handler, 
					int param);	/* Enable IPI INT    */
typedef STATUS (*CPC_IPI_ENABLE_FUNC)  (int vector);	/* Enable IPI INT    */
typedef STATUS (*CPC_IPI_DISABLE_FUNC) (int vector);	/* Disable IPI INT   */
typedef STATUS (*CPC_IPI_EMIT_FUNC)    (cpuset_t cpus); /* Invoke IPI INT    */

/* Structure used to initialize the IPI control functions */

typedef struct ipiCntrlInit
    {
    CPC_IPI_EMIT_FUNC        ipiEmitFunc;    /* Trigger an IPI int         */
    CPC_IPI_CONNECT_FUNC     ipiConnectFunc; /* Install an IPI int handler */
    CPC_IPI_ENABLE_FUNC      ipiEnableFunc;  /* Enable int                 */
    CPC_IPI_DISABLE_FUNC     ipiDisableFunc; /* Disable int                */
    int                      ipiVector;      /* interrupt vector to use    */
    } IPI_CTRL_INIT, * IPI_CTRL_INIT_PTR;

/* Forward declarations */

/* 
 * This structure is populated by the BSP interrupt controller driver
 * and passed to cpcInit() in usrCpcInit.c
 */

extern IPI_CTRL_INIT   ipiCtrlInit;

/* Init CPC library */

extern STATUS cpcInit (void);

/* Trigger an IPI on a remote/local processor. Target CPU are passed in */

extern void cpcInvoke (cpuset_t cpus,       /* target CPU bit mask          */ 
       		       CPC_FUNC func,       /* CPC call function            */
                       void *   param,      /* CPC call function parameters */
                       size_t   paramSize,  /* Size of Parameters           */
                       int      flags);     /* sync mode: ASYNC, SYNC or    */
					    /* 		  MANUAL 	    */

/*
 * Synchronization function called with CPC_SYNC_MANUAL within a CPC call 
 * function. 
 */

extern void cpcSync (void); 

#ifdef __cplusplus
}
#endif

#endif /* __INCpcLibPh */

