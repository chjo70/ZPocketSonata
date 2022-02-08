/* wvBufferP.h - generic buffer definition for buffers used with windview */

/*
 * Copyright (c) 1997-1999, 2007-2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
20feb14,wzc  move from System Viewer package.
01j,29apr10,pad  Moved extern C statement after include statements.
01j,10feb10,tcr  update for 64bit
01i,17jun09,tcr  spinlock type will depend on source build option
01h,10nov08,tcr  change spinlock type to spinlockIsrNd_t (WIND00136245)
01g,02jan07,tcr  add buffer type id, and support for callback
01f,13jul99,aeg  changed OBJ_CORE to HANDLE in BUFFER_DESC.
01e,06may98,cth  added nBytesRtn to BUFFER_DESC
01d,02feb98,nps  Allow inclusion in (68k) assembler source.
01c,18dec97,cth  renamed from buffer.h to wvBufferP.h, added flushRtn, comments
01b,21nov97,nps  added objCore to the start of BUFFER_DESC.
01a,16nov97,cth  written.
*/

/*
This file contains the definition of a structure that should make up the
core of any buffer id that can be passed to wvLib.  Windview uses a
pointer to this type of structure as a buffer id and as a way of 
accessing the buffer's routines.  See wvLib for a detailed description
of how the BUFFER_DESC is used.

INTERNAL
The bufferTypeIdent is used to allow host tools to determine the buffer layout
when reading memory snd structures with no target interaction, e.g. from
corefiles or via OCD

The newBuffCallbackAdd() function allows event log managers (such as evtLogLib)
to specify a function to call when a new buffer is added to the log. This allows
us to record information such as current CPU or current partition. Not all
buffer managers will implement this.
*/
 
#ifndef __INCwvbufferph
#define __INCwvbufferph


#include <private/semLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

#ifndef _ASMLANGUAGE

typedef struct bufferDesc	/* BUFFER_DESC */
    {
    HANDLE    	handle;             /* handle */
    ssize_t    	(*readReserveRtn)();/* request zero-copy read of buffer */
    STATUS      (*readCommitRtn)(); /* commit after zero-copy read of buffer */
    UINT8 *     (*writeRtn)(); 	    /* write (with reserve) to buffer */
    STATUS  	(*flushRtn)();	    /* flush routine of buffer */
    ssize_t  	(*nBytesRtn)();	    /* number readable bytes in buffer */
    void        (*lockRtn)(struct bufferDesc *);   /* lock buffer during update */
    void        (*unlockRtn)(struct bufferDesc *); /* unlock buffer after update */
    void *      spinLock;   /* spinlock used only on SMP */

    /* nominate callback for new buff */
    STATUS      (*newBuffHookAdd)(struct bufferDesc * bufferId,
                 STATUS (*callback)(struct bufferDesc * bufferId));

    char *      bufferTypeIdent;    /* discriminate between implementations */
    SEMAPHORE	threshXSem;	    /* sem given by buf when thresh crossed */
    size_t	threshold;	    /* arbitrary size in bytes set by buffer */
    } BUFFER_DESC;

typedef BUFFER_DESC *BUFFER_ID;

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCwvbufferph*/
