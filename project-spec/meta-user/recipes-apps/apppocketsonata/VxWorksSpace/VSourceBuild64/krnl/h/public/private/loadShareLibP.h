/* loadShareLibP.h - support for sharing loader code between host and target */

/* 
 * Copyright (c) 2004-2005, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. 
 */

/*
modification history
--------------------
01g,14apr10,v_r  Added ability to load DKMs into the kernel common heap (req
                 CQ:WIND00202013).
01f,06may09,v_r  LP64 adaptation: updated code following adaptation guidelines.
01e,08sep05,v_r  Refined loadShareTgtMemFree() prototype + cleanups.
01d,25jul05,v_r  Updated copyright.
01c,02jun04,jmp  fixed win32 build.
01b,16may04,jn   Finish implementation of loadShareCacheRefresh
01a,14may04,jn   Create
*/

/* DLL encapsulation */

#ifdef HOST
#define EXTERNAL extern DLL_EXPORT
#else
#define EXTERNAL extern
#endif

EXTERNAL void * loadShareTgtMemAlloc (void);
EXTERNAL void * loadShareTgtMemAlign (size_t alignment, size_t size, 
				      UINT32 options);
EXTERNAL void	loadShareTgtMemFree (void * addr, UINT32 options);
EXTERNAL STATUS loadShareTgtMemRead (void);
EXTERNAL void	loadShareTgtMemSet (void * addr, int value, size_t size);
EXTERNAL STATUS loadShareTgtMemWrite (void);
EXTERNAL void	loadShareCacheFlush (void);
EXTERNAL STATUS loadShareCacheRefresh (void);
