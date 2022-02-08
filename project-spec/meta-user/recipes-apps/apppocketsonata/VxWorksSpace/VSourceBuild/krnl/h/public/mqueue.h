/* mqueue.h - POSIX message queue library header */

/*
 * Copyright (c) 1993-1994, 1999, 2003, 2005, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01l,29apr10,pad  Moved extern C statement after include statements.
01k,12may09,pad  Aligned mq_receive()'s prototype on actual routine's
                 signature.
01j,22aug05,kk   moved kernel specific prototypes from mqueueCommon.h
01i,07jul05,kk   moved MQ_PRIO_MAX from mqueueCommon.h to here
01h,05dec03,m_s  code-inspection changes
01g,31oct03,m_s  make mq_des definition public for Base 6
01f,14oct03,pcm  added #include "fcntl.h" (SPR 4649)
01e,22mar99,elg  Erroneous Fix for SPR 20532 (SPR 25989).
01d,12mar99,elg  include private header to get mqPxLibInit() (SPR 20532).
01c,19aug96,dbt  added define of MQ_PRIORITY_MAX (SPR #7039).
		 updated copyright.
01b,05jan94,kdl	 added modhist, added include of sigevent.h, general cleanup.
01a,01dec93,rrr  written.
*/

#ifndef __INCmqueueh
#define __INCmqueueh


/* includes */

#include <mqueueCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/*defines */

#define MQ_PRIO_MAX             32      /* max priority levels */

/* forward declarations */

extern int	mq_send    (mqd_t, const void *, size_t, int);
extern ssize_t	mq_receive (mqd_t, void *, size_t, int *);

#ifdef __cplusplus
}
#endif

#endif	/* INCmqueueh */
