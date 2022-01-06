/* dllLib.h - doubly linked list library header */

/*
* Copyright (c) 1984-2006, 2009-2010, 2016 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
10mar16,wfl   Avoid compilation errors when certain header files are used in C++ (V7COR-3972)
04dec10,pad  Replaced FUNCPTR with fully-qualified function pointer in
                 dllEach()'s signature.
28apr10,pad  Moved extern C statement after include statements.
26jan09,pcs  Updated to add support for LP64 data model.
24jul06,jpb  Removal of duplicate definition of DL_LIST and DL_NODE.
26jan06,mil  Updated for POSIX namespace conformance (P2).
03jun05,yvp  Added #ifndef	_ASMLANGUAGE. 
                 Updated copyright. #include now with angle-brackets.
19jan05,vvv  moved some macros here from osdep.h
05may04,cjj  removed non-standard prototypes.
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
08apr91,jdi  added NOMANUAL to prevent mangen.
20dec90,gae  fixed declaration of dllRemove.
05oct90,shl  added ANSI function prototypes.
		 added copyright notice.
07aug89,jcf  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCdllLibh
#define __INCdllLibh

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <vxWorks.h>
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* type definitions */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef next
#undef previous
#endif

typedef struct _Vx_dlnode	/* Node of a linked list. */
    {
    struct _Vx_dlnode *next;	/* Points at the next node in the list */
    struct _Vx_dlnode *previous;/* Points at the previous node in the list */
    } _Vx_DL_NODE;

/* HIDDEN */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef head
#undef tail
#endif

typedef struct			/* Header for a linked list. */
    {
    _Vx_DL_NODE *head;	/* header of list */
    _Vx_DL_NODE *tail;	/* tail of list */
    } _Vx_DL_LIST;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef _Vx_DL_NODE DL_NODE;
typedef _Vx_DL_LIST DL_LIST;
typedef BOOL (*DLL_EACH_FUNC) (DL_NODE * pNode, _Vx_usr_arg_t arg);
#endif

/* END_HIDDEN */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/******************************************************************************
*
* DLL_INIT - initialize doubly linked list descriptor
*
* Initialize the specified list to an empty list.
*
* NOMANUAL
*/

#define DLL_INIT(list)                                                      \
    {                                                                       \
    ((DL_LIST *)(list))->head = NULL;                                       \
    ((DL_LIST *)(list))->tail = NULL;                                       \
    }

/*******************************************************************************
*
* dllFirst - find first node in list
*
* DESCRIPTION
* Finds the first node in a doubly linked list.
*
* RETURNS
*	Pointer to the first node in a list, or
*	NULL if the list is empty.
*
* NOMANUAL
*/

#define DLL_FIRST(pList)		\
    (					\
    (((DL_LIST *)(pList))->head)	\
    )

/*******************************************************************************
*
* dllLast - find last node in list
*
* Finds the last node in a doubly linked list.
*
* RETURNS
*  pointer to the last node in list, or
*  NULL if the list is empty.
*
* NOMANUAL
*/

#define DLL_LAST(pList)			\
    (					\
    (((DL_LIST *)(pList))->tail)	\
    )

/*******************************************************************************
*
* dllNext - find next node in list
*
* Locates the node immediately after the node pointed to by the pNode.
*
* RETURNS:
* 	Pointer to the next node in the list, or
*	NULL if there is no next node.
*
* NOMANUAL
*/

#define DLL_NEXT(pNode)			\
    (					\
    (((DL_NODE *)(pNode))->next)	\
    )

/*******************************************************************************
*
* dllPrevious - find preceding node in list
*
* Locates the node immediately before the node pointed to by the pNode.
*
* RETURNS:
* 	Pointer to the preceding node in the list, or
*	NULL if there is no next node.
*
* NOMANUAL
*/

#define DLL_PREVIOUS(pNode)		\
    (					\
    (((DL_NODE *)(pNode))->previous)	\
    )

/*******************************************************************************
*
* dllEmpty - boolean function to check for empty list
*
* RETURNS:
* 	TRUE if list is empty
*	FALSE otherwise
*
* NOMANUAL
*/

#define DLL_EMPTY(pList)			\
    (						\
    (((DL_LIST *)pList)->head == NULL)		\
    )

/******************************************************************************
*
* DLL_INSERT - insert node in list after specified node
*
* This macro inserts the specified node in the specified list.
* The new node is placed following the specified 'previous' node in the list.
* If the specified previous node is NULL, the node is inserted at the head
* of the list.
*
* NOMANUAL
*/

#define DLL_INSERT(list, previousNode, node)                                \
    {                                                                       \
    DL_NODE *temp;                                                          \
    if ((previousNode) == NULL)                                             \
        {                                                                   \
        temp = ((DL_LIST *)(list))->head;                                   \
        ((DL_LIST *)(list))->head = (DL_NODE *)(node);                      \
        }                                                                   \
    else                                                                    \
        {                                                                   \
        temp = ((DL_NODE *)(previousNode))->next;                           \
        ((DL_NODE *)(previousNode))->next = (DL_NODE *)(node);              \
        }                                                                   \
    if (temp == NULL)                                                       \
        ((DL_LIST *)(list))->tail = (DL_NODE *)(node);                      \
    else                                                                    \
       temp->previous = (DL_NODE *)(node);                                  \
    ((DL_NODE *)(node))->next = temp;                                       \
    ((DL_NODE *)(node))->previous = (DL_NODE *)(previousNode);              \
    }

/******************************************************************************
*
* DLL_ADD - add node to end of list
*
* This macro adds the specified node to the end of the specified list.
*
* NOMANUAL
*/

#define DLL_ADD(list, node)                                                 \
    {                                                                       \
    DL_NODE *listTail = (list)->tail;                                       \
    DLL_INSERT ((list), listTail, (node));                                  \
    } 

/******************************************************************************
*
* DLL_REMOVE - remove specified node in list
*
* Remove the specified node in the doubly linked list.
*
* NOMANUAL
*/

#define DLL_REMOVE(list, node)                                               \
    {                                                                        \
    if (((DL_NODE *)(node))->previous == NULL)                               \
        ((DL_LIST *)(list))->head = ((DL_NODE *)(node))->next;               \
    else                                                                     \
        ((DL_NODE *)(node))->previous->next = ((DL_NODE *)(node))->next;     \
    if (((DL_NODE *)(node))->next == NULL)                                   \
        ((DL_LIST *)(list))->tail = ((DL_NODE *)(node))->previous;           \
    else                                                                     \
        ((DL_NODE *)(node))->next->previous = ((DL_NODE *)(node))->previous; \
    }

/******************************************************************************
*
* DLL_GET - get (delete and return) first node from list
*
* This macro gets the first node from the specified list, deletes the node
* from the list, and returns a pointer to the node gotten.
*
* NOMANUAL
*/

#define DLL_GET(list, node)                                                 \
    {                                                                       \
    (node) = (void *)((DL_LIST *)(list))->head;                             \
    if ((node) != NULL)                                                     \
        {                                                                   \
        ((DL_LIST *)(list))->head = ((DL_NODE *)(node))->next;              \
        if (((DL_NODE *)(node))->next == NULL)                              \
            ((DL_LIST *)(list))->tail = NULL;                               \
        else                                                                \
            ((DL_NODE *)(node))->next->previous = NULL;                     \
        }                                                                   \
    }

/* function declarations */

extern DL_LIST *dllCreate (void);
extern DL_NODE *dllEach (DL_LIST *pList, 
                         DLL_EACH_FUNC routine,
                         _Vx_usr_arg_t routineArg);
extern DL_NODE *dllGet (DL_LIST *pList);
extern STATUS 	dllDelete (DL_LIST *pList);
extern STATUS 	dllInit (DL_LIST *pList);
extern STATUS 	dllTerminate (DL_LIST *pList);
extern int 	dllCount (DL_LIST *pList);
extern void 	dllAdd (DL_LIST *pList, DL_NODE *pNode);
extern void 	dllInsert (DL_LIST *pList, DL_NODE *pPrev, DL_NODE *pNode);
extern void 	dllRemove (DL_LIST *pList, DL_NODE *pNode);

#endif  /* _POSIX_xxx_SOURCE */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}

/*
 * Inlined C++ wrapper for the old-style FUNCPTR based dllEach function
 * prototype.
 */

extern DL_NODE * dllEach (DL_LIST * pList, FUNCPTR routine,
			 _Vx_usr_arg_t routineArg) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
inline DL_NODE * dllEach
    (
    DL_LIST * pList,
    FUNCPTR routine,
    _Vx_usr_arg_t routineArg
    )
    {
    return dllEach (pList,
		    (DLL_EACH_FUNC)routine,
		    routineArg);
    }
#endif /* _POSIX_xxx_SOURCE */
#endif /* __cplusplus */

#endif /* __INCdllLibh */
