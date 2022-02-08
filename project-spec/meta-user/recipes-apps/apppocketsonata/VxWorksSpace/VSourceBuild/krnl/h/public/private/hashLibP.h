/* hashLibP.h - private hash table library header */

/* Copyright 2003, 2009-2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,28apr10,pad  Moved extern C statement after include statements.
01b,17mar09,jpb  Updated for LP64 support.
01a,26jun03,to   ported form AE1.1.
*/

#ifndef __INChashLibPh
#define __INChashLibPh

#include <hashLib.h>
#include <sllLib.h>
#include <private/handleLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* size of hash table given number of elements in hash table log 2 */

#define HASH_TBL_SIZE(sizeLog2)						\
	(((1 << (sizeLog2)) * sizeof (SL_LIST)) + sizeof (HASH_TBL))

/* type definitions */

typedef struct hashtbl		/* HASH_TBL */
    {
    HANDLE	  handle;	/* handle management */
    HASH_KEY_CMP_FUNC keyCmpRtn;/* comparator function */
    HASH_FUNC     keyRtn;	/* hash function */
    SL_LIST *	  pHashTbl;	/* pointer to hash table array */
    _Vx_usr_arg_t keyArg;	/* hash function argument */
    int		  elements;	/* number of elements in table */
    } HASH_TBL;

#ifdef __cplusplus
}
#endif

#endif /* __INChashLibPh */
