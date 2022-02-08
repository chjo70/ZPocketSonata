/* ntp_setjmp.h - setjmp/longjmp header */

/*
 * Copyright (c) 1984-2010, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01a,08oct10,rjq  written
*/

#ifndef NTP_SETJMP_H
#define NTP_SETJMP_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _jmp_buf
    {
    int   reg;
    int       excCnt;
    long long extra[3];
    } jmp_buf[1];

typedef struct _sigjmp_buf
    {
    int   regs;
    int       excCnt;
    long long extra[3];
    } sigjmp_buf[1];


/* function declarations */

extern int	setjmp 		(jmp_buf __env);
extern int	sigsetjmp 	(sigjmp_buf __env, int __savemask);

extern void 	longjmp 	(jmp_buf __env, int __val);

extern void 	siglongjmp 	(sigjmp_buf __env, int __val);


#ifdef __cplusplus
}
#endif

#endif /* NTP_SETJMP_H */
