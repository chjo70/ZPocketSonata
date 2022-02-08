/* trgLib.h - event triggers header */

/* Copyright 1998-1999, 2003, 2006, 2010  Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,15jul10,wzc  Porting to 64Bit.
01i,29apr10,pad  Moved extern C statement after include statements.
01i,04feb10,tcr  update for 64bit
01h,27apr06,tcr  add trgEvent prototype
01g,10nov03,cpd  Add declarations for trgReset
01f,23sep03,tcr  move TRIGGER_ID def'n
01e,15sep03,tcr  tidy up
01d,16mar99,spm  recovered orphaned code from tor1_0_1.sens1_1 (SPR #25770)
01c,16dec98,nps  fix last change(!)
01b,14dec98,nps  added prototype for trgShowInit.
01a,27jan98,pr   written

*/

#ifndef __INCtrglibh
#define __INCtrglibh

/* This file contains event triggering elements. */

#define TRIGGER_COND_NO 	0
#define TRIGGER_COND_YES 	1

#define TRIGGER_COND_FUNC 	0
#define TRIGGER_COND_VAR 	1
#define TRIGGER_COND_LIB        2

#define TRG_DISABLE  	        0  
#define TRG_ENABLE   	        1

#define TRIGGER_EQ 	0
#define TRIGGER_NEQ 	1
#define TRIGGER_LSS 	2
#define TRIGGER_LEQ 	3
#define TRIGGER_GRT 	4
#define TRIGGER_GEQ 	5
#define TRIGGER_OR 	6
#define TRIGGER_AND 	7

#define TRG_CTX_ANY      0
#define TRG_CTX_ANY_TASK 1
#define TRG_CTX_TASK     2
#define TRG_CTX_ANY_ISR  3
#define TRG_CTX_ISR      4
#define TRG_CTX_SYSTEM   5

#define TRG_ACT_NONE     0
#define TRG_ACT_WV_START 1
#define TRG_ACT_WV_STOP  2
#define TRG_ACT_FUNC     3
#define TRG_ACT_NOTIFY   4
#define	TRG_ACT_STOP	 5
#define	TRG_ACT_LIB	 6

#ifndef _ASMLANGUAGE

typedef struct trigger *        TRIGGER_ID;    

#include <private/trgLibP.h>

#ifdef __cplusplus
extern "C" {
#endif


extern STATUS   	trgLibInit (void);
extern TRIGGER_ID   	trgAdd (
			       event_t event,
			       int status,
			       int contextType,
			       TASK_ID contextId,
			       OBJ_ID objId,
			       int conditional,
			       int condType,
			       _Vx_usr_arg_t * condEx1,
			       int condOp,
			       _Vx_usr_arg_t condEx2,
			       BOOL disable,
			       TRIGGER_ID chain,
			       int actionType,
			       FUNCPTR actionFunc,
			       BOOL actionDef,
			       _Vx_usr_arg_t actionArg
			       );
extern STATUS   	trgDelete (TRIGGER_ID trgId);
extern STATUS 		trgWorkQReset (void);
extern STATUS   	trgReset (TRIGGER_ID trgId);
extern STATUS   	trgOn (void);
extern void   	        trgOff (void);
extern STATUS   	trgEnable (TRIGGER_ID trgId);
extern STATUS   	trgDisable (TRIGGER_ID trgId);
extern STATUS   	trgChainSet (TRIGGER_ID fromId, TRIGGER_ID toId);
extern STATUS   	trgShow (TRIGGER_ID trgId, int options);
extern void	   	trgShowInit (void);
extern void             trgEvent (event_t event);
    
#endif /* _ASMLANGUAGE */ 

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCtrglibph*/
