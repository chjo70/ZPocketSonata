/* avlUintLib.h - header file for AVL tree with unsigned integer sorting key */

/*
 * Copyright (c) 2003, 2012, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06oct15,clt  Added avlUintMinimumGet() for cert (V7SP-537)
10sep14,prk  Disabled avlUintMinimumGet from cert build
01feb12,pcs  Update the copyright information.
02dec03,zl   created based on avlLib.h.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCavlUintLibh
#define __INCavlUintLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* typedefs */

/* 
 * Binary tree node definition that uses an unsigned integer as the sorting 
 * key.
 */

typedef struct avlu_node
    {
    struct avlu_node *  left;	/* pointer to the left subtree */
    struct avlu_node *  right;	/* pointer to the right subtree */
    int    height; 		/* height of the subtree rooted at this node */
    UINT   key;			/* sorting key */
    } AVLU_NODE;

typedef AVLU_NODE * AVLU_TREE;	/* points to the root node of the tree */

/* callback routines for avlUintTreeWalk */

typedef STATUS (*AVLU_CALLBACK)(AVLU_NODE *pNode, void * pArg);

/* function declarations */

STATUS      avlUintInsert (AVLU_TREE * pRoot, AVLU_NODE * pNode);
AVLU_NODE * avlUintDelete (AVLU_TREE * pRoot, UINT key);
AVLU_NODE * avlUintSearch (AVLU_TREE root, UINT key);
AVLU_NODE * avlUintSuccessorGet (AVLU_TREE root, UINT key);
AVLU_NODE * avlUintPredecessorGet (AVLU_TREE root, UINT key);
AVLU_NODE * avlUintMinimumGet (AVLU_TREE root);
AVLU_NODE * avlUintMaximumGet (AVLU_TREE root);
STATUS      avlUintTreeWalk (AVLU_TREE pRoot, AVLU_CALLBACK preRtn, 
			     void * preArg, AVLU_CALLBACK inRtn, void * inArg,
			     AVLU_CALLBACK postRtn, void * postArg);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCavlUintLibh */
