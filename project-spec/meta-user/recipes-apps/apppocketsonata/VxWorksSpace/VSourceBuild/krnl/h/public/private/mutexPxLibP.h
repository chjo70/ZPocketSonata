/* mutexPxLibP.h - kernel mutex and condition header file */

/*
 * Copyright (c) 1993, 2001, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,26may10,pad  Added 'extern C' statement.
01c,02oct09,zl   replaced qLib.h with qLibP.h
01b,24sep01,gls  removed definition and use of __P() macro (SPR #28330)
01a,18feb93,rrr  written.
*/

#ifndef __INCmutexPxLibPh
#define __INCmutexPxLibPh

#include <vxWorks.h>
#include <private/qLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
    {
    int		m_owner;
    Q_HEAD	m_queue;
    } mutex_t;

typedef struct
    {
    mutex_t	*c_mutex;
    Q_HEAD	c_queue;
    } cond_t;

struct timespec;

extern void mutex_init (mutex_t *, void *);
extern void mutex_destroy (mutex_t *);

extern void cond_init (cond_t *, void *);
extern void cond_destroy (cond_t *);

extern void mutex_lock (mutex_t *);
extern void mutex_unlock (mutex_t *);

extern void cond_signal (cond_t *);
extern int cond_timedwait (cond_t *, mutex_t *, const struct timespec *);

#ifdef __cplusplus
}
#endif

#endif /* __INCmutexPxLibPh */
