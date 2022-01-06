/* avlLib.h - header file for AVL tree */
  
/*
 * Copyright (c) 1999-2001, 2003-2004, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,01feb12,pcs  Update the copyright information.
01c,03may04,rp   removed avlTreeErase
01b,06apr04,rp   added avlInsertInform, avlRemoveInsert and avlTreeErase
01a,08feb03,zl   moved out uint key version to avlUintLib, replaced 
                 GENERIC_ARGUMENT with void *.
01g,08aug03,zl   resolved avlLib aliasing problem.
01f,24jan01,sn   end file with newline(!) to avoid cpp errors
01e,10feb00,abd  added avlMinimumGet and avlMaximumGet
01d,10feb00,abd  added avlTreeWalk, avlTreePrint, avlTreeErase, avlTreePrintErase
01c,03feb00,abd  added avlInsertInform, avlRemoveInsert
01b,24jan00,abd  added avlSuccessorGet and avlPredecessorGet
01a,08feb99,wkn  created.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCavlLibh
#define __INCavlLibh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* typedefs */

typedef struct avl_node
    {
    struct avl_node *  left;	/* pointer to the left subtree */
    struct avl_node *  right;	/* pointer to the right subtree */
    int    height; 		/* height of the subtree rooted at this node */
    } AVL_NODE;

typedef AVL_NODE * AVL_TREE;	/* points to the root node of the tree */

typedef STATUS (*AVL_COMPARE)(AVL_NODE *pNode, void * pKey);

/* callback routines for avlUintTreeWalk */

typedef STATUS (*AVL_CALLBACK)(AVL_NODE *pNode, void * pArg);

/* function declarations */

STATUS     avlInsert (AVL_TREE * pRoot, AVL_NODE * pNode, void * pKey, 
		      AVL_COMPARE cmpRtn);
AVL_NODE * avlDelete (AVL_TREE * pRoot, void * pKey, AVL_COMPARE cmpRtn);
AVL_NODE * avlSearch (AVL_TREE root, void * pKey, AVL_COMPARE cmpRtn);
AVL_NODE * avlSuccessorGet (AVL_TREE root, void * pKey, AVL_COMPARE cmpRtn);
AVL_NODE * avlPredecessorGet (AVL_TREE root, void * pKey, AVL_COMPARE cmpRtn);
AVL_NODE * avlMinimumGet (AVL_TREE root);
AVL_NODE * avlMaximumGet (AVL_TREE root);
STATUS     avlTreeWalk (AVL_TREE pRoot, AVL_CALLBACK preRtn, void * preArg,
			AVL_CALLBACK inRtn, void * inArg,
			AVL_CALLBACK postRtn, void * postArg);
STATUS     avlInsertInform (AVL_TREE * pRoot, void * pNewNode, void * key,
                            void ** ppKeyHolder, AVL_COMPARE cmpRtn);
void *     avlRemoveInsert (AVL_TREE * pRoot, void * pNewNode, void * key,
                            AVL_COMPARE cmpRtn);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCavlLibh */
