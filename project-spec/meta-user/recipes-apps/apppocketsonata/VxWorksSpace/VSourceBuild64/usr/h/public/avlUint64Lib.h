/* avlUint64Lib.h - header file for AVL tree with UINT64 sorting key */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,17sep10,pcs  change key from long to UINT64.
01a,28jul10,pcs   created based on avlUintLib.h.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCavlUint64Libh
#define __INCavlUint64Libh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* typedefs */

/* 
 * Binary tree node definition that uses an unsigned long as the sorting 
 * key.
 */

typedef struct avlUint64_node
    {
    struct avlUint64_node *  left;	/* pointer to the left subtree */
    struct avlUint64_node *  right;	/* pointer to the right subtree */
    UINT64 key;	              		/* sorting key */
    int    height; 		/* height of the subtree rooted at this node */
    } AVLUINT64_NODE;

typedef AVLUINT64_NODE * AVLUINT64_TREE;	/* points to the root node of the tree */

/* callback routines for avlUint64TreeWalk */

typedef STATUS (*AVLUINT64_CALLBACK)(AVLUINT64_NODE *pNode, void * pArg);

/* function declarations */

STATUS           avlUint64Insert (AVLUINT64_TREE * pRoot, 
                                  AVLUINT64_NODE * pNode);
AVLUINT64_NODE * avlUint64Delete (AVLUINT64_TREE * pRoot, UINT64 key);
AVLUINT64_NODE * avlUint64Search (AVLUINT64_TREE root, UINT64 key);
AVLUINT64_NODE * avlUint64SuccessorGet (AVLUINT64_TREE root, UINT64 key);
AVLUINT64_NODE * avlUint64PredecessorGet (AVLUINT64_TREE root, UINT64 key);
AVLUINT64_NODE * avlUint64MinimumGet (AVLUINT64_TREE root);
AVLUINT64_NODE * avlUint64MaximumGet (AVLUINT64_TREE root);
STATUS           avlUint64TreeWalk (AVLUINT64_TREE pRoot, 
                                    AVLUINT64_CALLBACK preRtn, void * preArg, 
                                    AVLUINT64_CALLBACK inRtn, void * inArg, 
                                    AVLUINT64_CALLBACK postRtn, void * postArg);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCavlUint64Libh */
