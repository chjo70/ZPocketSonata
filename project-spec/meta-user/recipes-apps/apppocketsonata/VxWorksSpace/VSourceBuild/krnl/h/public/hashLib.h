/* hashLib.h - hash table library header */

/* Copyright 1989-92, 2001, 2003, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01n,07dec10,pad  Replaced FUNCPTR with fully-qualified function pointer in
                 hashTblEach()'s signature.
01m,28apr10,pad  Moved extern C statement after include statements.
01l,30mar09,jpb  Fixed build error on user side.
01k,06mar09,jpb  Updated for LP64 support.
01j,26jun03,to   merged from AE1.1: de-classified,
		 moved private definitions to private/hashLibP.h.
01i,23oct01,rae  undo 01h
01h,10oct01,rae  merge from truestack ver 01i base 01g
01g,22sep92,rrr  added support for c++
01f,04jul92,jcf  cleaned up.
01e,26may92,rrr  the tree shuffle
01d,04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
01c,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
		 added copyright notice.
01b,26jun90,jcf  remove hash id error status.
01a,17nov89,jcf  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INChashLibh
#define __INChashLibh

#include <vwModNum.h>
#include <sllLib.h>
#ifdef _WRS_KERNEL
#include <vsbConfig.h>  /* for _Vx_usr_arg_t */
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_hashLib_KEY_CLASH		(M_hashLib | 1)

/* type definitions */

typedef SL_NODE HASH_NODE;	/* HASH_NODE */

typedef struct hashtbl * HASH_ID;

/* These hash nodes are used by the hashing functions in hashLib(1) */

typedef struct			/* H_NODE_INT */
    {
    HASH_NODE	  node;			/* linked list node (must be first) */
    _Vx_usr_arg_t key;			/* hash node key */
    _Vx_usr_arg_t data;			/* hash node data */
    } H_NODE_INT;

typedef struct			/* H_NODE_STRING */
    {
    HASH_NODE	node;			/* linked list node (must be first) */
    char *	string;			/* hash node key */
    _Vx_usr_arg_t data;			/* hash node data */
    } H_NODE_STRING;

typedef int (*HASH_FUNC) (int elements, HASH_NODE * pHNode, _Vx_usr_arg_t arg);
typedef BOOL (* HASH_KEY_CMP_FUNC)(HASH_NODE *pNode, HASH_NODE *pHNode, 
	                           _Vx_usr_arg_t arg);

/* function declarations */

extern BOOL		hashKeyCmp (H_NODE_INT * pMatchHNode,
				    H_NODE_INT * pHNode, 
				    _Vx_usr_arg_t keyCmpArg);
extern BOOL		hashKeyStrCmp (H_NODE_STRING * pMatchHNode,
				       H_NODE_STRING * pHNode, 
				       _Vx_usr_arg_t keyCmpArg);
extern HASH_ID		hashTblCreate (int sizeLog2, FUNCPTR keyCmpRtn,
				       FUNCPTR keyRtn, _Vx_usr_arg_t keyArg);
extern HASH_NODE *	hashTblEach (HASH_ID hashId,
				     BOOL (* routine)
					 (
					 HASH_NODE * pNode,
					 _Vx_usr_arg_t routineArg
					 ),
				     _Vx_usr_arg_t routineArg);
extern HASH_NODE *	hashTblFind (HASH_ID hashId, HASH_NODE * pMatchNode,
	                             _Vx_usr_arg_t keyCmpArg);
extern STATUS		hashLibInit (void);
extern STATUS		hashTblDelete (HASH_ID hashId);
extern STATUS		hashTblDestroy (HASH_ID hashId, BOOL dealloc);
extern STATUS		hashTblInit (HASH_ID pHashTbl, SL_LIST * pTblMem,
				     int sizeLog2, FUNCPTR keyCmpRtn,
				     FUNCPTR keyRtn, _Vx_usr_arg_t keyArg);
extern STATUS		hashTblPut (HASH_ID hashId, HASH_NODE * pHashNode);
extern STATUS		hashTblRemove (HASH_ID hashId, HASH_NODE * pHashNode);
extern STATUS		hashTblTerminate (HASH_ID hashId);
extern int		hashFuncIterScale (int elements, H_NODE_STRING * pHNode,
					   _Vx_usr_arg_t seed);
extern int		hashFuncModulo (int elements, H_NODE_INT * pHNode,
			                _Vx_usr_arg_t divisor);
extern int		hashFuncMultiply (int elements, H_NODE_INT * pHNode,
	                                  _Vx_usr_arg_t multiplier);

#ifdef __cplusplus
}
/*
 * Inlined C++ wrapper for the old-style FUNCPTR based hashTblEach function
 * prototype.
 */

extern HASH_NODE * hashTblEach (HASH_ID hashId, FUNCPTR routine,
				_Vx_usr_arg_t routineArg) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline HASH_NODE * hashTblEach
    (
    HASH_ID hashId,
    FUNCPTR routine,
    _Vx_usr_arg_t routineArg
    )
    {
    return hashTblEach (hashId,
			(BOOL (*)(HASH_NODE * pNode,
				  _Vx_usr_arg_t routineArg))routine,
			routineArg);
    }
#endif /* __cplusplus */

#endif /* __INChashLibh */
