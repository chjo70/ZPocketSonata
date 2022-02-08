/* setjmp.h - setjmp/longjmp header */

/*
 * Copyright (c) 1984-2004, 2006, 2010, 2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
31jan14,to   include vxWorks.h for _WRS_FUNC_NORETURN
14feb12,zl   jmp_buf to use fully qualified types (WIND00311945)
29apr10,pad  Moved extern C statement after include statements.
21dec06,aeg  added _WRS_FUNC_NORETURN attribute to longjmp/siglongjmp.
12jan06,gls  updated to support 64 bit sigset_t
16feb04,m_s  added excCnt to jump buffer
09jul96,ms   fixed prototype of sigsetjmp (SPR 7002).
27dec95,mem  removed macros for VxSim hppa
27mar95,kkk  fixed multiple definition of jmp_buf & sigjmp_buf (SPR 4051)
31mar94,cd   modified jmp_buf and sigjmp_buf structures for use
             with 32/64 bit processors.
12may94,ms   added macros for VxSim hppa
22sep92,rrr  added support for c++
31aug92,rrr  added setjmp
10jul92,rrr  set it up to use the new signal code. One more pass is needed
             to make it ANSI.
09jul92,jwt  removed structure version of jmp_buf for SPARC - merge error.
09jul92,rrr  fixed sparc from having two typedefs for jmp_buf
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
09jan92,jwt  converted CPU==SPARC to CPU_FAMILY==SPARC.
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed ASMLANGUAGE to _ASMLANGUAGE
             -changed copyright notice
20jul91,jwt  modified jmp_buf for SPARC; added #ifndef _ASMLANGUAGE.
02aug91,ajm  added defines and macros for MIPS architecture.
29apr91,hdn  added defines and macros for TRON architecture.
20apr91,del  added I960 specifics.
19oct90,shl  changed IMPORT to extern for ANSI compatibility,
             fixed wrong type definition for longjmp().
05oct90,shl  added ANSI function prototypes.
             added copyright notice.
             made #endif ANSI style.
25aug88,ecs  added SPARC version of jmp_buf.
01jul88,rdc  changed order of stuff in jmp_buf.
22jun88,dnw  written
*/

#ifndef __INCsetjmph
#define __INCsetjmph

#include <vxWorks.h>    /* for _WRS_FUNC_NORETURN */
#include <regs.h>
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _jmp_buf
    {
    REG_SET          reg;		/* saved task register set */
    int              excCnt;		/* saved tasks exception count */
    BOOL             sigmaskIsValid;	/* TRUE when sigmask is saved */
    sigset_t         sigmask;		/* saved task signal mask */
    struct windTcb * pTcb;		/* task identifier for verification */
    } jmp_buf[1];

typedef struct _sigjmp_buf
    {
    REG_SET          regs;		/* saved task register set */
    int              excCnt;		/* saved tasks exception count */
    BOOL             sigmaskIsValid;	/* TRUE when sigmask is saved */
    sigset_t         sigmask;		/* saved task signal mask */
    struct windTcb * pTcb;		/* task identifier for verification */
    } sigjmp_buf[1];

/* function declarations */

extern int	setjmp 		(jmp_buf __env);
extern int	sigsetjmp 	(sigjmp_buf __env, int __savemask);

extern _WRS_FUNC_NORETURN
	void 	longjmp 	(jmp_buf __env, int __val);

extern _WRS_FUNC_NORETURN
	void 	siglongjmp 	(sigjmp_buf __env, int __val);

#ifdef __cplusplus
}
#endif

#endif /* __INCsetjmph */
