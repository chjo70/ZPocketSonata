/* taskUtilLibP.h - private kernel interface header */

/*
 * Copyright (c) 2005-2006, 2009-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
01g,14jan11,cww  Fix compiler warnings (WIND00241209)
01f,05may10,cww  64-bit SMP update
01e,29apr10,pad  Moved extern C statement after include statements.
01d,22apr09,pcs  Updated to add support for LP64 data model.
01c,08nov06,jln  comment out intLock/intUnlock for SMP safe
01b,31aug05,gls  updated for checkin
01a,04mar05,kk   written 
*/

#ifndef __INCtaskUtilLibPh
#define __INCtaskUtilLibPh

#include <vxWorks.h>
#include <taskLib.h>
#include <taskUtilLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef UINT32	RESERVED_NUM;	/* SPARE_NUM in h/taskUtilLib.h */

/* defines */

#define SPARE_MASK		0x000F
#define RESERVED_MASK		0x0003

/* update this if more fields are added to the TCB */

#define NUM_SPARE_FIELDS 	4
#define NUM_RESERVED_FIELDS 	2

/* 
 * bitmaps for the reserved and spare fields. 
 * Using two variables instead of one to allow these to grow up to 15 fields. 
 * Currently: Reserved has first 2 bits. Spare has first 4 bits.
 */

extern UINT16 tcbReserveBitmap;	/* initialize in taskUtilLib.c */
extern UINT16 tcbSpareBitmap;	/* initialize in taskUtilLib.c */

/******************************************************************************
*
* TASK_RESERVED_NUM_ALLOT - get the first available reserved field in the TCB
*
* This macro returns the first available reserved field in the TCB. If
* a reserved field is not available, ERROR or -1 is returned. If an available
* reserved field exist, that RESERVED_NUM will be returned in numAllotted.
* numAllotted starts from 1. 
*
* Currently there are only 2 reserved fields. If more reserved fields
* are added to the TCB, then the macro NUM_RESERVED_FIELDS in this file
* must be updated.
* 
* This macro will be used by the taskReserveNumAllot() routine.
* 
* PROTOTYPE: void TASK_RESERVED_NUM_ALLOT 
*                ( 
*                TASK_ID        tid, 
*                RESERVED_NUM * numAllotted
*                )
*
* RETURNS: RESERVED_NUM, or ERROR if no available field
*
* \NOMANUAL
*/

#define TASK_RESERVED_NUM_ALLOT(tid, numAllotted)			      \
    {									      \
    UINT16 num = 0;							      \
    while ((num < NUM_RESERVED_FIELDS) && 				      \
           ((tcbReserveBitmap & (1 << (num % NUM_RESERVED_FIELDS))) != 0))    \
	   num++;							      \
    if (num >= NUM_RESERVED_FIELDS)					      \
        *numAllotted = (RESERVED_NUM) ERROR;				      \
    else								      \
        {								      \
	*numAllotted = ++num;						      \
	tcbReserveBitmap |= (UINT16) (1 << (num-1) % NUM_RESERVED_FIELDS);    \
	}								      \
    }									      \

/******************************************************************************
*
* TASK_RESERVED_FIELD_GET - get the value of a reserved field
*
* This macro retrieves the value of a reserved field. The num parameter, 
* allotted from using the TASK_RESERVED_NUM_ALLOT() macro, indicates which 
* reserved field to get the value from.
*
* PROTOTYPE: long TASK_RESERVED_FIELD_GET 
*                (
*                TASK_ID      tid, 
*                RESERVED_NUM num
*                )
*
* RETURNS: value in the reserved field 
*
* \NOMANUAL
*/

#define TASK_RESERVED_FIELD_GET(tid, num)				     \
	(								     \
        *(long *)(&(((WIND_TCB *)(tid))->reserved1) + (num-1))		     \
	)

/******************************************************************************
*
* TASK_RESERVED_FIELD_SET - set the value of a reserved field
*
* This macro sets the value of a reserved field. The num parameter,
* gotten from TASK_RESERVED_NUM_ALLOT() macro, indicates
* which reserved field to set.
*
* PROTOTYPE: void TASK_RESERVED_FIELD_SET
*                (
*                TASK_ID      tid,
*                RESERVED_NUM num, 
*                long         value
*                )
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define TASK_RESERVED_FIELD_SET(tid, num, value)			     \
	(								     \
        *(long *)(&(((WIND_TCB *)(tid))->reserved1) + (num-1)) = value	     \
	)

/******************************************************************************
*
* TASK_SPARE_NUM_ALLOT - get the first available spare field in the TCB
*
* This macro returns the first available spare field in the TCB. If
* a spare field is not available, ERROR or -1 is returned. If an available
* spare field exist, that SPARE_NUM will be returned in numAllotted.
* numAllotted starts from 1. 
*
* Currently there are only 4 spare fields. If more spare fields
* are added to the TCB, then the macro NUM_SPARE_FIELDS in this file
* must be updated.
* 
* This macro will be used by the taskSpareNumAllot() routine.
* This macro returns the first available spare field in the TCB. If
* a spare field is not available, ERROR or -1 is returned.
*
* Currently there are only 4 spare fields. SPARE_NUM starts from 1,
* 
* This macro is used by the routine to get the available spare field
* in the TCB. This macro will be used by the taskSpareNumAllot() routine.
* 
* PROTOTYPE: void TASK_SPARE_NUM_ALLOT 
*                (
*                TASK_ID     tid, 
*                SPARE_NUM * numAllotted
*                )
*
* RETURNS: SPARE_NUM, or ERROR if no available field
*
* \NOMANUAL
*/

#define TASK_SPARE_NUM_ALLOT(tid, numAllotted)				      \
    {									      \
    UINT16 num = 0;							      \
    while ((num < NUM_SPARE_FIELDS) &&					      \
           ((tcbSpareBitmap & (1 << (num % NUM_SPARE_FIELDS))) != 0))	      \
	   num++;							      \
    if (num >= NUM_SPARE_FIELDS)					      \
        *numAllotted = (SPARE_NUM) ERROR;				      \
    else								      \
        {								      \
	*numAllotted = ++num;						      \
	tcbSpareBitmap |= (UINT16) (1 << (num-1) % NUM_SPARE_FIELDS);	      \
	}								      \
    }

/******************************************************************************
*
* TASK_SPARE_FIELD_GET - get the value of a spare field
*
* This macro retrieves the value of a spare field. The num parameter,
* gotten from TASK_SPARE_NUM_ALLOT() macro, indicates which spare 
* field to obtain the value from.
*
* PROTOTYPE: long TASK_SPARE_FIELD_GET
*                (
*                TASK_ID   tid, 
*                SPARE_NUM num
*                )
*
* RETURNS: value in the spare field 
*
* \NOMANUAL
*/

#define TASK_SPARE_FIELD_GET(tid, num)					     \
	(								     \
        *(long *)(&(((WIND_TCB *)(tid))->spare1) + (num-1))  		     \
	)

/******************************************************************************
*
* TASK_SPARE_FIELD_SET - set the value of a spare field
*
* This macro sets the value of a spare field. The num parameter,
* gotten from TASK_SPARE_NUM_ALLOT() macro, specifies the spare field 
* to set the value.
*
* PROTOTYPE: void TASK_SPARE_FIELD_SET
*                (
*                TASK_ID   tid, 
*                SPARE_NUM num, 
*                long      value
*                )
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define TASK_SPARE_FIELD_SET(tid, num, value)				     \
	(								     \
        *(long *)(&(((WIND_TCB *)(tid))->spare1) + (num-1)) = value	     \
	)

/******************************************************************************
*
* TASK_CPUTIME_INFO_GET - get the cpuTimeInfo field in the TCB
*
* This macro gets the value of a cpuTimeInfo field, referred to by
* 'index'. Index takes the value of 0 or 1, which indicates the first
* or secode element of the cpuTimeInfo[] array.
*
* INTERNAL: This does not use the allot scheme as in the spare and reserved
* fields because these routines will be used in performance critical code and
* thus the less calculation done, the better.
*
* PROTOTYPE: UINT64 TASK_CPUTIME_INFO_GET
*                (
*                TASK_ID tid,
*                int     index
*                )
*
* RETURNS: value in cpuTimeInfo field
*
* \NOMANUAL
*/

#define TASK_CPUTIME_INFO_GET(tid, index)				\
    (									\
    ((WIND_TCB *)(tid))->cpuTimeInfo[index]				\
    )

/******************************************************************************
*
* TASK_CPUTIME_INFO_SET - set the cpuTimeInfo field in the TCB
*
* This macro sets the value of a the cpuTimeInfo field, specified by 'index'.
* Index takes the value of 0 or 1, which is index into the cpuTimeInfo array.
*
* INTERNAL: This does not use the allot scheme as in the spare and reserved
* fields because these routines will be used in performance critical code and
* thus less calculation the better.
*
* PROTOTYPE: void TASK_CPUTIME_INFO_SET
*                (
*                TASK_ID tid, 
*                int     index, 
*                UINT64  value
*                )
*
* RETURNS: N/A
*
* \NOMANUAL
*/

#define TASK_CPUTIME_INFO_SET(tid, index, value)			\
    (									\
    ((WIND_TCB *)(tid))->cpuTimeInfo[index] = value			\
    )

/* prototypes */

extern void   taskReservedNumAllot (TASK_ID tid, RESERVED_NUM * numAllotted);
extern STATUS taskReservedFieldSet (TASK_ID tid, RESERVED_NUM num, long value);
extern long   taskReservedFieldGet (TASK_ID tid, RESERVED_NUM num);

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskUtilLibPh */
