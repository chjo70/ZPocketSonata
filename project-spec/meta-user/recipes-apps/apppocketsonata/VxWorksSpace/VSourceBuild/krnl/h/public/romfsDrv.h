/* romfsDrv.h - header file for romfsDrv.c */

/* Copyright 2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
29apr10,pad  Moved extern C statement after include statements.
14may03,md  created.
*/

#ifndef __INCromfsDrvh
#define __INCromfsDrvh

#include "blkIo.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ROMFS_BLOCK_SIZE	512	/* block size for I/O operations */

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern BLK_DEV *romfsBlkDevCreate (char *addr, int size, int offset);

#else

extern BLK_DEV *romBlkDevCreate ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCromfsDrvh */
