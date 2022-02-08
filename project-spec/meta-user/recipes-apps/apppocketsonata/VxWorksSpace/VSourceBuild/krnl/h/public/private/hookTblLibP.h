/* hookTblLibP.h - Private generic hook management library header */

/*
 * Copyright (c) 2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
09sep14,cww  fixed static analysis errors
27nov12,jpb  fixed value of HOOK_TABLE_STATUS_BITS (WIND00392252)
27apr12,cww  written
*/

#ifndef __INChookTblLibPh
#define __INChookTblLibPh

#include <vxWorks.h>
#include <private/qLibP.h>
#include <hookLib.h>
#include <semLib.h>
#include <vxAtomicLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

typedef struct
    {
    VX_SEMAPHORE (lockSem);
    int		 maxEntries;
    int		 execCnt;
    Q_HEAD	 updatePendQ;
    void *	 pActiveTable;
    void **	 hookTableA;
    void **	 hookTableB;
    } HOOK_TBL;

#define HOOK_TBL_DECL(name, maxEntries)					\
    void *	name##ArrayA[maxEntries+1];				\
    void *	name##ArrayB[maxEntries+1];				\
    HOOK_TBL name = {{},maxEntries,0,{},name##ArrayA,name##ArrayA,	\
		     name##ArrayB};

/*
 * Notes on the protection mechanisms used:
 *
 * Table updaters use a mutex (lockSem) to protect the table from simultaneous
 * updates. Two copies of the actual hooks are maintained, one of which is
 * always active and referenced by pActiveTable. Updating the hooks involves
 * first updating the inactive table, flipping pActiveTable, then updating the
 * other (now inactive) table.
 *
 * The mutex is not used for walking the table as we cannot pend when
 * invoking hooks. Instead, bit manipulation of pActiveTable is used to mark
 * when the table is being traversed, also serving to prevent pActiveTable
 * from being swapped during hook invokation.  A count (execCnt) is used to
 * track nested and concurrent execution.
 *
 * The following status bits are stored in the least significant bits of
 * pActiveTable and are used to protect the table from updates while it is
 * being traversed. Setting HOOK_TABLE_IN_USE indicates that the table is
 * reserved, while setting HOOK_TABLE_RESERVING indicates that the most recent
 * operation is a reservation.  The latter is required to detect the situation
 * where the table is being reserved while an unreserve operation has already
 * decremented execCnt to 0, but before the HOOK_TABLE_IN_USE bit is cleared,
 * in which case the table should stay reserved. 
 */

#define HOOK_TABLE_IN_USE	0x01L
#define HOOK_TABLE_RESERVING	0x02L
#define HOOK_TABLE_STATUS_BITS	(HOOK_TABLE_IN_USE | HOOK_TABLE_RESERVING)

/******************************************************************************
*
* HOOK_TBL_READ_RESERVE - Reserve the active hook table for walking
*
* Marks the given HOOK_TBL as in use and returns a pointer to the active
* table via <pReservedTable>.
*
* \NOMANUAL
*/

#define HOOK_TBL_READ_RESERVE(pReservedTable,pHookTable)		    \
    {									    \
    pReservedTable = (void *) vxAtomicOr (				    \
				(atomic_t *) &(pHookTable)->pActiveTable,   \
				HOOK_TABLE_STATUS_BITS);		    \
    (void) vxAtomic32Inc (&(pHookTable)->execCnt);			    \
    pReservedTable = (void *)((ULONG) pReservedTable &			    \
			      ~HOOK_TABLE_STATUS_BITS);			    \
    }

/******************************************************************************
*
* HOOK_TBL_READ_UNRESERVE - Unreserve the active hook table
*
* Marks the given HOOK_TBL as not in use and potentially unpends any task
* waiting to update the table.  Note that the CAS only fails if either another
* task sets the reserving bit, or we were preempted just before the CAS and
* someone else has unreserved already; in both cases, there is nothing more
* to do.
*
* \NOMANUAL
*/

#define HOOK_TBL_READ_UNRESERVE(pHookTable)				\
    {									\
    atomic_t tempVal;							\
									\
    tempVal = vxAtomicAnd ((atomic_t *) &(pHookTable)->pActiveTable,	\
		~HOOK_TABLE_RESERVING);					\
    tempVal &= ~HOOK_TABLE_RESERVING;					\
									\
    if (vxAtomic32Dec (&(pHookTable)->execCnt) == 1)			\
	{								\
	if (vxAtomicCas ((atomic_t *) &(pHookTable)->pActiveTable,	\
			 tempVal,					\
			 tempVal & ~(HOOK_TABLE_STATUS_BITS)))		\
	    hookTblUpdatersUnpend (pHookTable);				\
	}								\
    }

/******************************************************************************
*
* HOOK_TBL_READ_UNRESERVE_NO_UNPEND - Unreserve the active hook table
*
* Marks the given HOOK_TBL as not in use but does not unpend any waiting task.
* Used only in special cases where we cannot enter the kernel, such as when
* running reboot hooks.  We skip the reserving bit check since in these
* special cases we either don't care or no concurrent reserve is possible.
*
* \NOMANUAL
*/

#define HOOK_TBL_READ_UNRESERVE_NO_UNPEND(pHookTable)			\
    {									\
    if (vxAtomic32Dec (&(pHookTable)->execCnt) == 1)			\
	{								\
	(void) vxAtomicAnd ((atomic_t *) &(pHookTable)->pActiveTable,	\
			    ~HOOK_TABLE_STATUS_BITS);			\
	}								\
    }

/******************************************************************************
*
* HOOK_TBL_INVOKE_VOID_RETURN - Invoke all hooks in the given table.
*
* This macro calls all hook functions added into the given hook table <tbl>.
* The called functions are not expected to return anything (return values
* are not checked). The <type> argument is a typecast that is applied to
* all function pointers in the table. This is done for type checking
* purposes. The <arglist> argument is a parenthesis-enclosed
* argument list that is passed verbatim to each hook function called.
*
* \NOMANUAL
*/

#define HOOK_TBL_INVOKE_VOID_RETURN(pTbl,type,arglist)			\
    {									\
    int		ix;							\
    void **	pTableCurrent;						\
									\
    HOOK_TBL_READ_RESERVE (pTableCurrent,pTbl);			\
									\
    for (ix = 0; ix < (pTbl)->maxEntries; ix++)				\
	{								\
	if (pTableCurrent[ix] != NULL)					\
	    (*(type) pTableCurrent[ix]) arglist;			\
	else								\
	    break;							\
	}								\
									\
    HOOK_TBL_READ_UNRESERVE (pTbl);				\
    }

/******************************************************************************
*
* HOOK_TBL_INVOKE_CHECK_RETURN - Invoke all hooks in a table, performing
* 				 return value checking.
*
* This macro calls all hook functions added into the given hook table <tbl>.
* The return value from each called function is saved to <pRetval> and
* compared with <keepGoing>, and hook execution stops if they differ. In that
* case, any remaining hooks are not executed. The <type> argument is a
* typecast that is applied to all function pointers in the table. This is
* done for type checking purposes. The <arglist> must be a parenthesis-enclosed
* argument list that is passed verbatim to each hook function called.
*
* \NOMANUAL
*/

#define HOOK_TBL_INVOKE_CHECK_RETURN(pTbl,type,keepGoing,pRetval,arglist)  \
    {									   \
    int		ix;				  		           \
    void **	pTableCurrent;						   \
									   \
    HOOK_TBL_READ_RESERVE (pTableCurrent,pTbl);				   \
							  		   \
    for (ix = 0; ix < (pTbl)->maxEntries; ix++)				   \
	{						 		   \
	if (pTableCurrent[ix] != NULL)	 				   \
	    {								   \
	    *(pRetval) = (type) pTableCurrent[ix] arglist;		   \
	    if (*(pRetval) != keepGoing) 	     			   \
		{					  		   \
		break;					  		   \
		}					  		   \
	    }								   \
	else								   \
	    break;							   \
	}						  		   \
									   \
    HOOK_TBL_READ_UNRESERVE (pTbl);					   \
    }

/* function declarations */

STATUS hookTblInit		(HOOK_TBL * pTable);
STATUS hookTblAddToTail 	(HOOK_TBL * pTable, void * hook);
STATUS hookTblAddToHead 	(HOOK_TBL * pTable, void * hook);
STATUS hookTblDelete		(HOOK_TBL * pTable, void * hook);
BOOL   hookTblFind		(HOOK_TBL * pTable, void * hook);
void   hookTblUpdatersUnpend	(HOOK_TBL * pTable);

void   hookTblShow		(HOOK_TBL * pHookTable);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INChookTblLibPh */

