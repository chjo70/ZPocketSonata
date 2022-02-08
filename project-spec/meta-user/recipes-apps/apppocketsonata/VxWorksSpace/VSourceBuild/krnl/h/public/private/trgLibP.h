/* trgLibP.h - event triggers header */

/*
 * Copyright (c) 1997-1998, 2003, 2006, 2008, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01o,17may11,wzc  Enlarge stack size of trgActDef.(WIND00276074)
01n,15jul10,wzc  Porting to 64Bit.
01m,29apr10,pad  Moved extern C statement after include statements.
01m,10feb10,tcr  update for 64bit
01l,12may08,tcr  add eventId back
01k,24apr08,tcr  triggering to use eventpoints
01j,16dec06,tcr  update for SMP
01i,10nov03,cpd  Add initialState to trigger structure
01h,23sep03,tcr  move TRIGGER_ID def'n
01g,15sep03,tcr  tidy up
01f,07sep98,pr   Replaced LIST_MAX_LENGTH with TRG_MAX_REQUESTS
01e,12feb98,pr   Added hitCnt field in struct trigger. 
		 Moved some definitions in ../trgLib.h. Cleanup.
01d,15dec97,nps  Added 'library' conditional type.
01c,20nov97,pr   added several triggering macros, reworked triggering
                 structure, added trgActionDefPerform 
01b,27oct97,pr   modified the struct trigger into an object. cleanup
01a,18jul97,pr   written

*/

#ifndef __INCtrglibph
#define __INCtrglibph


/* This file contains event triggering information. See also eventP.h */

#define TRIGGER_MASK   0x0000ffff

#define TRG_MSGQ_MAX_MSGS 	50
#define TRG_MSGQ_OPTIONS  	(MSG_Q_FIFO)
#define TRG_MSG_LEN       	4
#define TRG_ACT_PRIORITY        100
#define TRG_ACT_OPTIONS         VX_UNBREAKABLE
#ifdef _WRS_CONFIG_LP64
#define TRG_ACT_SIZE            8192
#else
#define TRG_ACT_SIZE            4096
#endif

#ifndef _ASMLANGUAGE

#include <private/eventP.h>
#include <msgQLib.h>
#include <trgLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TRG_MAX_REQUESTS 50

typedef struct trigger
    {
    OBJ_CORE		objCore;	/* trigger object core */
    event_t             eventId;        /* event type */
    UINT16              status;    	/* status of the trigger, */
					/* i.e. enabled, disabled, etc */
    BOOL                disable;	/* check if trigger needs to be */
					/* disabled after use */
    int                 contextType;    /* type of the context where the event occurs */
    TASK_ID             contextId;      /* id of the context where the event occurs */
    OBJ_ID		objId;     	/* object type */
    struct trigger      *chain;         /* pointer to chained trigger */
    int 		conditional;  	/* check if a condition is set */
    int 		condType;  	/* check the expression type (var/fn) */
    _Vx_usr_arg_t *	condEx1;  	/* pointer to conditional expression */
    int			condOp;  	/* conditional operator (==, !=, ...) */
    _Vx_usr_arg_t 	condEx2;  	/* second operand (constant) */
    int         	actionType; 	/* type of action (none, fn, lib) */
    FUNCPTR     	actionFunc; 	/* pointer to the action */
    _Vx_usr_arg_t   actionArg;    	/* argument passed to the action */
    BOOL         	actionDef; 	/* defer the action */
    int			hitCnt;
    int                 initialState;   /* initial state of the trigger*/
    struct data_collector * pDataCollector;     /* associated collector */
    } TRIGGER;

extern STATUS   	trgInit (void);
extern TRIGGER_ID    	trgAddTcl (char * buff);
extern void    		trgCheck (TRIGGER_ID trigId, OBJ_ID objId);

#endif /* _ASMLANGUAGE */ 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCtrglibph*/
