/* syscallLib.h - System Call Infrastructure library header */

/* 
 * Copyright (c) 2003, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01i,24feb10,cww  Added SYSCALL_DESC_ENTRY macro
01h,15dec09,cww  Fixed type mismatch in SYSCALL_RTN_TBL_ENTRY
01g,03dec09,cww  LP64 adaptation
01f,12nov03,yvp  Changed syscallLibInit to take hook tbl size param.
01e,31oct03,yvp  Added S_syscallLib_VECTOR_INIT_FAILED.
01d,29sep03,yvp  Added errno S_syscallLib_INVALID_USER_SP.
01c,15sep03,yvp  Moved syscallDispatch prototype to syscallLibP.h
01b,03sep03,yvp  Added extern for syscallGroupTbl.
01a,26aug03,yvp	 written.
*/

#ifndef __INCsyscallLibh
#define __INCsyscallLibh

/* includes */

#include <vxWorks.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* generic status codes for syscallLib */

#define S_syscallLib_UNKNOWN_GROUP          (M_syscallLib | 1)
#define S_syscallLib_GROUP_EXISTS           (M_syscallLib | 2)
#define S_syscallLib_INVALID_ROUTINE_COUNT  (M_syscallLib | 3)
#define S_syscallLib_NO_ROUTINES_TBL        (M_syscallLib | 4)
#define S_syscallLib_INVALID_USER_SP        (M_syscallLib | 5)
#define S_syscallLib_VECTOR_INIT_FAILED     (M_syscallLib | 6)

#ifndef _ASMLANGUAGE

/* typedefs */

#ifdef _WRS_CONFIG_LP64

/* 
 * The system call table entries are defined differently in ILP32 and LP64.
 * More specifically, the order of the members methodName and numArgs have been
 * swapped for LP64.  This was done to avoid padding the structure to meet
 * alignment constraints.  However, the ILP32 version must stay the same for
 * backward compatibility, and so the SYSCALL_DESC_ENTRY macro was introduced
 * to allow the same code to work in both environment.
 */

typedef long _syscall_return_t;
typedef _syscall_return_t (*SYSCALL_RTN)(void *);

typedef struct syscall_rtn_tbl_entry
    {
    SYSCALL_RTN	pMethod;
    char *      methodName;
    int         numArgs;    /* numArgs should be the total number of native */
			    /* words that the argument list takes (max = 8) */
			    /* including 64-bit arguments & alignment pad   */
    UINT32      spare;	    
    } SYSCALL_RTN_TBL_ENTRY;

#define SYSCALL_DESC_ENTRY(pMethod,name,numArgs) 			\
				{(SYSCALL_RTN) pMethod, name, numArgs, 0}
    
#else /* !_WRS_CONFIG_LP64 */

typedef int _syscall_return_t;
typedef FUNCPTR SYSCALL_RTN;

typedef struct syscall_rtn_tbl_entry
    {
    SYSCALL_RTN	pMethod;
    int         numArgs;    /* numArgs should be the total number of native */
			    /* words that the argument list takes (max = 8) */
			    /* including 64-bit arguments & alignment pad   */
    char *	methodName;
    UINT32      spare;	    
    } SYSCALL_RTN_TBL_ENTRY;

#define SYSCALL_DESC_ENTRY(pMethod,name,numArgs)			\
				{(SYSCALL_RTN) pMethod, numArgs, name, 0}

#endif /* _WRS_CONFIG_LP64 */
    
/* externals */

extern char * syscallGroupName [];

/* function declarations */

extern STATUS syscallGroupRegister (int groupNum, char * groupName,
				    int numRoutines,
				    SYSCALL_RTN_TBL_ENTRY * pRoutineTbl,
				    BOOL force);
extern void syscallShow 	   (int grp, int level);
extern void syscallHookShow 	   (void);
extern void syscallMonitor 	   (int level, RTP_ID rtpId);

#ifdef __cplusplus
}
#endif

#endif	/* _ASMLANGUAGE */

#endif /* __INCsyscallLibh */
