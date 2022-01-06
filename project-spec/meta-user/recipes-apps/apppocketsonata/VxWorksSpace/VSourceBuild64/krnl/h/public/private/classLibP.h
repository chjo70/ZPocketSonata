/* classLibP.h - private object class management library header file */

/*
 * Copyright (c) 2004-2005, 2007-2010, 2012-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
28jan15,gls  added WIND_CLASS_ADD_TO_CLASS_LIST class option
09mar15,jpb  removed classListTblInitialize (V7COR-2522)
21feb14,cww  updated CLASS_LIST_TBL_INIT_FUNC to return STATUS
21feb14,wzc  remove building warnings.(WB4-2765)
03jun13,wzc  Add WIND_CLASS_STACKTRACE
09jul12,wzc  WIND00361531 - Remove building warnings.
13oct10,jpb  Fixed wrong offset listed in comments of OBJ_CLASS struct
16aug10,cww  Use dynamically generated offsets in offset macros
29apr10,pad  Moved extern C statement after include statements.
23jan10,gls  modified handle size
17feb09,zl   changed to fully qualified function pointers. LP64 updates.
20oct08,jpb  Defect 139482.  Renamed VX_CLASS_TASK_LIST_LOCK 
             and VX_TASK_CLASS_LIST_UNLOCK to 
	     VX_CLASS_LIST_LOCK and VX_CLASS_LIST_UNLOCK.
27aug08,jpb  Renamed VSB header file
30jul08,jpb  Added macros for common code and support when class list 
             configuration is removed.
26jan07,zl   added class list management function pointer types
29aug05,kk   added classCreateConnect() (SPR# 106196)
26oct04,fr   added classOpenConnect() routine (SPR 101491)
28sep04,fr   added createRtn & openRtn and removed nameSetRtn & nameGetRtn
             from wind_class and classInit() (SPR 101349)
14may04,dcc  added CLASSID_INVALIDATE() and CLASSID_RESTORE() macros.
12apr04,dcc  enabled use of the per-class mutex.
11sep03,tcr  add WindView class instrumentation.
26aug03,tcr  remove WindView functions no longer needed
22oct03,dcc  added offsets in the OBJ_CLASS comments.
21aug03,dcc  added support for public objects
02jul03,to   added offset for objClassType.
23jun03,dcc  removed classCreate() and classDestroy() prototypes.
14mar03,dcc  ported from AE1.1 
19may97,jpd  added _ASMLANGUAGE for offsets into OBJ_CLASS.
10dec93,smb  added windview documentation
	     changed helpRtn to instRtn
22sep92,rrr  added support for c++
04jul92,jcf  created.
*/

#ifndef __INCclassLibPh
#define __INCclassLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <semLib.h>
#include <memLib.h>
#include <classLib.h>
#include <dllLib.h>
#include <private/handleLibP.h>
#include <private/objLibP.h>

#ifndef _ASMLANGUAGE
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#endif

/* class options */

#define WIND_CLASS_ALLOW_DUPLICATE_NAMES	0x01
#define WIND_CLASS_RENAME_NOT_ALLOWED		0x02
#define WIND_CLASS_INSTRUMENTED		        0x04 
#define WIND_CLASS_STACKTRACE		        0x08 
#define WIND_CLASS_ADD_TO_CLASS_LIST	        0x10

#ifndef _ASMLANGUAGE

/*
 * These macros take a CLASS_ID and test/get/set the instrumentation state for
 * the class. Then any subsequent object creations will inherit the
 * instrumented state from the class.
 */
    
#define WV_OBJ_CLASS_IS_INSTRUMENTED(classId)				\
            ((classId)->handle.attributes & WIND_CLASS_INSTRUMENTED)

#define WV_OBJ_CLASS_INSTRUMENTATION_ENABLE(classId)			\
            ((classId)->handle.attributes |= WIND_CLASS_INSTRUMENTED)

#define WV_OBJ_CLASS_INSTRUMENTATION_DISABLE(classId)			\
            ((classId)->handle.attributes = \
                (UINT16)((classId)->handle.attributes & \
                (~WIND_CLASS_INSTRUMENTED)))

#define WV_OBJ_CLASS_IS_STACKTRACE(classId)				\
            ((classId)->handle.attributes & WIND_CLASS_STACKTRACE)

#define WV_OBJ_CLASS_STACKTRACE_ENABLE(classId)			\
            ((classId)->handle.attributes |= WIND_CLASS_STACKTRACE)

#define WV_OBJ_CLASS_STACKTRACE_DISABLE(classId)			\
            ((classId)->handle.attributes = \
                (UINT16)((classId)->handle.attributes & \
                (~WIND_CLASS_STACKTRACE)))

/* Class list semaphore options */

#define CLASS_LIST_SEM_INIT_OPTIONS  (SEM_Q_PRIORITY |			\
                                      SEM_DELETE_SAFE |			\
                                      SEM_INVERSION_SAFE)

#define CLASS_LIST_SEM_INLINE_OPTIONS (CLASS_LIST_SEM_INIT_OPTIONS |	\
                                       SEM_NO_ID_VALIDATE |		\
                                       SEM_NO_ERROR_CHECK |		\
                                       SEM_NO_EVENT_SEND)

/* Locking of class list */

#define VX_CLASS_LIST_LOCK(lock)					\
	semMTakeScalable (lock, WAIT_FOREVER, CLASS_LIST_SEM_INLINE_OPTIONS)
#define VX_CLASS_LIST_UNLOCK(lock)					\
	semMGiveScalable (lock, CLASS_LIST_SEM_INLINE_OPTIONS)

/* Initialize list maintaining tasks when class list configuration disabled */

#ifndef _WRS_CONFIG_OBJECT_CLASS_LIST
#define VX_TASK_CLASS_LIST_INIT(classId, lock)				\
	dllInit (&(classId)->objPrivList);				\
	semMInit (lock, CLASS_LIST_SEM_INIT_OPTIONS); 
#endif /* _WRS_CONFIG_OBJECT_CLASS_LIST */

/* Add/remove objects to class list */

#define CLASS_LIST_ADD(list, node) 	dllAdd (list, node)
#define CLASS_LIST_REMOVE(list, node)	dllRemove (list, node)

/* 
 * CLASS_LIST_INFO is used to traverse object list storing the info in the 
 * element array.
 */

#define CLASS_NODE_TO_OBJ_ID(pNode)					\
	(OBJ_ID)((long)(pNode) - OFFSET (OBJ_CORE, classNode))

#define CLASS_LIST_INFO(list, max, element)				\
	{								\
	DL_NODE * pNode;						\
	pNode = DLL_FIRST (&list);					\
	while ((pNode != NULL) && (--max >= 0))				\
	    {								\
	    *(element++) = CLASS_NODE_TO_OBJ_ID(pNode);			\
	    pNode = DLL_NEXT (pNode);					\
	    }								\
	}

typedef struct wind_class	/* OBJ_CLASS */
    {
    HANDLE		  handle;	  /* 0x00/0x00: handle management     */
    enum windObjClassType objClassType;	  /* 0x10/0x18: class type	      */
    int			  options;	  /* 0x14/0x1c: object class options  */
    size_t		  objSize;	  /* 0x18/0x20: size of object	      */
    OBJ_CREATE_FUNC	  createRtn;  	  /* 0x1c/0x28: object create routine */
    OBJ_DESTROY_FUNC	  destroyRtn;	  /* 0x20/0x30: object destroy	      */
					  /*		routine		      */
    OBJ_SHOW_FUNC	  showRtn;	  /* 0x24/0x38: object show routine   */
    OBJ_ALLOC_FUNC	  objMemAllocRtn; /* 0x28/0x40: object memory alloc   */
					  /*		routine		      */
    OBJ_FREE_FUNC	  objMemFreeRtn;  /* 0x2c/0x48: object memory free    */
					  /*		routine		      */
    void *		  objPartId;      /* 0x30/0x50: object memory pool ID */
    DL_LIST		  objPrivList;    /* 0x34/0x58: list of private	      */
					  /*		objects		      */
    DL_LIST	          objPubList;     /* 0x3c/0x68: list of public	      */
					  /*		objects		      */
    SEM_ID		  pClassSem;      /* 0x44/0x78: lists' mutual	      */
					  /*		exclusion	      */
    } OBJ_CLASS;			  /* 0x48/0x80  sizeof OBJ_CLASS      */

typedef void	(*CLASS_LIST_INIT_FUNC)		(OBJ_CLASS * pObjClass, 
				       enum windObjClassType objClassType);
typedef void	(*CLASS_LIST_ADD_FUNC)		(OBJ_CORE * pObjCore,
						 CLASS_ID classId);
typedef void	(*CLASS_LIST_REMOVE_FUNC)	(OBJ_CORE * pObjCore,
						 CLASS_ID classId);
typedef STATUS	(*CLASS_LIST_TBL_INIT_FUNC)	(void);
typedef STATUS	(*CLASS_LIST_LOCK_FUNC)		(CLASS_ID classId);
typedef STATUS	(*CLASS_LIST_UNLOCK_FUNC)	(CLASS_ID classId);

/* variable declarations */

extern CLASS_ID	classIdTable [];	/* array of class IDs */
extern CLASS_LIST_LOCK_FUNC	_func_classListLock;
extern CLASS_LIST_UNLOCK_FUNC	_func_classListUnlock;
extern CLASS_LIST_INIT_FUNC     _func_classListInit;
extern CLASS_LIST_ADD_FUNC      _func_classListAdd;
extern CLASS_LIST_REMOVE_FUNC   _func_classListRemove;

/* function declarations */

extern STATUS classInit			(OBJ_CLASS * pObjClass,
					 size_t objectSize,
					 OBJ_CREATE_FUNC createRtn,
					 OBJ_DESTROY_FUNC destroyRtn,
					 OBJ_ALLOC_FUNC objMemAllocRtn,
					 OBJ_FREE_FUNC objMemFreeRtn,
					 void * objMemPoolId,
			 		 enum windObjClassType objClassType,
					 int options);
extern STATUS classCreateConnect	(CLASS_ID classId,
					 OBJ_CREATE_FUNC createRtn);
extern STATUS classDestroyConnect	(CLASS_ID classId,
					 OBJ_DESTROY_FUNC destRtn);
extern STATUS classShowConnect		(CLASS_ID classId,
					 OBJ_SHOW_FUNC showRtn);
extern STATUS classListLibInit		(void);

#ifdef __cplusplus
}
#endif

#else  /* _ASMLANGUAGE */

/*
 * offsets in the OBJ_CLASS structure - these must be in an ASM section due to
 * a circular dependency when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#include <private/offsetMacrosP.h>

#define WIND_CLASS_TYPE		OBJ_CLASS_objClassType_OFFSET

#endif  /* _ASMLANGUAGE */

#endif /* __INCclassLibPh */

