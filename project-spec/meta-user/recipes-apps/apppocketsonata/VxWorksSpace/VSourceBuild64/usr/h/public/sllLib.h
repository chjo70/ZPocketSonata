/* sllLib.h - singly linked list library header */

/*
 * Copyright (c) 1989-1992, 2005, 2009-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement.
 */

/*
modification history
--------------------
02f,13jun12,jpb  Defect WIND00352633.  Fixed SLL_GET.
02e,04dec10,pad  Replaced FUNCPTR with fully-qualified function pointer in
                 sllEach()'s signature.
02d,15jun10,v_r  Fixed SLL_PREVIOUS (def CQ:WIND00196676, merged from
		 iter14_bsp_cortex_a9be8).
02e,28apr10,pad  Moved extern C statement after include statements.
02d,26jan09,pcs  Updated to add support for LP64 data model.
02c,19jan05,vvv  moved some macros from osdep.h
02b,22sep92,rrr  added support for c++
02a,04jul92,jcf  cleaned up.
01f,26may92,rrr  the tree shuffle
01e,04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
01d,08apr91,jdi  added NOMANUAL to prevent mangen.
01c,05oct90,shl  added ANSI function prototypes.
		 added copyright notice.
01b,10aug90,dnw  changed declaration of sllRemove() from STATUS to void.
01a,03jun89,jcf  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCsllLibh
#define __INCsllLibh

#include <types/vxTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* type definitions */

typedef struct slnode		/* Node of a linked list. */
    {
    struct slnode *next;	/* Points at the next node in the list */
    } SL_NODE;

/* HIDDEN */

typedef struct			/* Header for a linked list. */
    {
    SL_NODE *head;	/* header of list */
    SL_NODE *tail;	/* tail of list */
    } SL_LIST;

/* END_HIDDEN */

/*******************************************************************************
*
* SLL_INIT - initialize singly linked list head
*
* Initialize the specified list to an empty list.
*
* NOMANUAL
*/

#define SLL_INIT(list)                                                    \
    {                                                                     \
    ((SL_LIST *)(list))->head    = NULL;                                  \
    ((SL_LIST *)(list))->tail    = NULL;                                  \
    }

/*******************************************************************************
*
* SLL_PUT_AT_HEAD - add node to beginning of list
*
* This macro adds the specified node to the end of the specified list.
*
* NOMANUAL
*/

#define  SLL_PUT_AT_HEAD(list, node)                                     \
{                                                                        \
    if ((((SL_NODE *)(node))->next = ((SL_LIST *)(list))->head) == NULL) \
        {                                                                \
        ((SL_LIST *)(list))->head = ((SL_NODE *)(node));                 \
        ((SL_LIST *)(list))->tail = ((SL_NODE *)(node));                 \
        }                                                                \
    else                                                                 \
        ((SL_LIST *)(list))->head = (node);                              \
    }

/*******************************************************************************
*
* SLL_PUT_AT_TAIL - add node to end of list
*
* This macro adds the specified node to the end of the specified singly
* linked list.
*
* NOMANUAL
*/

#define  SLL_PUT_AT_TAIL(list, node)                                    \
    {                                                                   \
    ((SL_NODE *)(node))->next = NULL;                                    \
    if (((SL_LIST *)(list))->head == NULL)                              \
        {                                                               \
        ((SL_LIST *)(list))->head = (SL_NODE *)(node);                  \
        ((SL_LIST *)(list))->tail = (SL_NODE *)(node);                  \
        }                                                               \
    else                                                                \
        ((SL_LIST *)(list))->tail->next = (SL_NODE *)(node);            \
        ((SL_LIST *)(list))->tail = (SL_NODE *)(node);                  \
    }

/*******************************************************************************
*
* SLL_GET - get (delete and return) first node from list
*
* This macro gets the first node from the specified singly linked list,
* deletes the node from the list, and returns a pointer to the node gotten.
*
* NOMANUAL
*/

#define SLL_GET(list, node)						\
    {									\
    if (((node) = (void *)((SL_LIST *)(list))->head) != NULL)		\
        {							   	\
        ((SL_LIST *)(list))->head = ((SL_NODE *)(node))->next;		\
        if (((SL_LIST *)(list))->tail == ((SL_NODE *)(node)))		\
            ((SL_LIST *)(list))->tail = NULL;				\
        }								\
    }

/*******************************************************************************
*
* SLL_REMOVE - remove specified node in list
*
* Remove the specified node in a singly linked list.
*
* NOMANUAL
*/

#define SLL_REMOVE(list, deleteNode, previousNode)                           \
    {                                                                        \
    if (((SL_NODE *)(previousNode)) == NULL)                                 \
        {                                                                    \
        ((SL_LIST *)(list))->head = ((SL_NODE *)(deleteNode))->next;         \
        if (((SL_LIST *)(list))->tail == ((SL_NODE *)(deleteNode)))          \
            ((SL_LIST *)(list))->tail = NULL;                                \
        }                                                                    \
    else                                                                     \
        {                                                                    \
        ((SL_NODE *)(previousNode))->next = ((SL_NODE *)(deleteNode))->next; \
        if (((SL_LIST *)(list))->tail == ((SL_NODE *)(deleteNode)))          \
            ((SL_LIST *)(list))->tail = ((SL_NODE *)(previousNode));         \
        }                                                                    \
    }

/*******************************************************************************
*
* SLL_PREVIOUS - find and return previous node in list
*
* Find and return the previous node in a singly linked list.
*
* NOMANUAL
*/

#define SLL_PREVIOUS(list, node, previousNode)                              \
    {                                                                       \
    SL_NODE *temp;                                                          \
    (previousNode) = NULL;						    \
    temp = ((SL_LIST *)(list))->head;                                       \
    if ((temp != NULL) && (temp != (node)))                                 \
	{								    \
        while (temp->next != NULL)                                          \
            {                                                               \
            if (temp->next == (node))                                       \
                {                                                           \
		(previousNode) = temp;					    \
                break;                                                      \
                }                                                           \
            temp = temp->next;                                              \
            }                                                               \
	}								    \
    }

/************************************************************************
*
* sllFirst - find first node in list
*
* DESCRIPTION
* Finds the first node in a singly linked list.
*
* RETURNS
*	Pointer to the first node in a list, or
*	NULL if the list is empty.
*
* NOMANUAL
*/

#define SLL_FIRST(pList)	\
    (				\
    (((SL_LIST *)pList)->head)	\
    )

/************************************************************************
*
* sllLast - find last node in list
*
* This routine finds the last node in a singly linked list.
*
* RETURNS
*  pointer to the last node in list, or
*  NULL if the list is empty.
*
* NOMANUAL
*/

#define SLL_LAST(pList)		\
    (				\
    (((SL_LIST *)pList)->tail)	\
    )

/************************************************************************
*
* sllNext - find next node in list
*
* Locates the node immediately after the node pointed to by the pNode.
*
* RETURNS:
* 	Pointer to the next node in the list, or
*	NULL if there is no next node.
*
* NOMANUAL
*/

#define SLL_NEXT(pNode)		\
    (				\
    (((SL_NODE *)pNode)->next)	\
    )

/************************************************************************
*
* sllEmpty - boolean function to check for empty list
*
* RETURNS:
* 	TRUE if list is empty
*	FALSE otherwise
*
* NOMANUAL
*/

#define SLL_EMPTY(pList)			\
    (						\
    (((SL_LIST *)pList)->head == NULL)		\
    )

/* function declarations */

extern SL_LIST *sllCreate (void);
extern SL_NODE *sllEach (SL_LIST *pList, 
			 BOOL (* routine)
			     (
			     SL_NODE * pNode,
			     _Vx_usr_arg_t arg
			     ),
                         _Vx_usr_arg_t routineArg);
extern SL_NODE *sllGet (SL_LIST *pList);
extern SL_NODE *sllPrevious (SL_LIST *pList, SL_NODE *pNode);
extern STATUS 	sllDelete (SL_LIST *pList);
extern STATUS 	sllInit (SL_LIST *pList);
extern STATUS 	sllTerminate (SL_LIST *pList);
extern int 	sllCount (SL_LIST *pList);
extern void 	sllPutAtHead (SL_LIST *pList, SL_NODE *pNode);
extern void 	sllPutAtTail (SL_LIST *pList, SL_NODE *pNode);
extern void 	sllRemove (SL_LIST *pList, SL_NODE *pDeleteNode,
                           SL_NODE *pPrevNode);

#ifdef __cplusplus
}

/*
 * Inlined C++ wrapper for the old-style FUNCPTR based sllEach function
 * prototype.
 */

extern SL_NODE * sllEach (SL_LIST * pList, FUNCPTR routine,
			  _Vx_usr_arg_t routineArg) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline SL_NODE * sllEach 
    (
    SL_LIST * pList,
    FUNCPTR routine,
    _Vx_usr_arg_t routineArg
    )
    {
    return sllEach (pList,
		    (BOOL (*)(SL_NODE * pNode, _Vx_usr_arg_t arg))routine,
		    routineArg);
    }
#endif /* __cplusplus */

#endif /* __INCsllLibh */
