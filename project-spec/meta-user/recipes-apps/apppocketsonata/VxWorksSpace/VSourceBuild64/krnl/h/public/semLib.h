/* semLib.h - semaphore library header file */

/*
 * Copyright (c) 1990-2005, 2007-2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12apr15,gpa  added CERT apis for semRW*
23oct14,pcs  made semTerminate() public (V7COR-2110)
16jun10,pcs  change the data type of timeout from an int to _Vx_ticks_t
29apr10,pad  Moved extern C statement after include statements.
09mar09,pcs  Updated to add support for the LP64 data model.
02sep08,kk   added semXXXScalable() APIs
06feb07,gls  added VX_READ_WRITE_SEMAPHORE
             added semRWInitialize()
27dec05,yvp  Removed unnecessary semicolon in VX_SEMAPHORE macro.
07oct05,yvp  Used VX_OBJ_ALIGN_SIZE to align statically instantiated
             objects (SPR 113405).
30aug05,yvp  Reworked VX_SEMAPHORE macro to undo struct workaround. 
08aug05,yvp  Added VX_SEMAPHORE macro for static semaphore instantiation.
             Added prototypes for semXInitialize(). Copyright update.
             #include now with angle brackets.
26oct04,fr   added semOpenInit() routine (SPR 101491)
08mar04,aeg  removed Diab _WRS_DEPRECATED C++ workaround.
02mar04,aeg  deprecated semOLib APIs.
25nov03,aeg  added semInfo() function prototype from semLibCommon.h.
21aug03,dcc  moved common definitions with user side to semLibCommon.h.
20jun03,ymz  updated year of copyright.
14mar03,dcc  moved SEM_ID definition to types/vxWind.h.
19oct01,bwa  Added SEM_EVENTSEND_ERR_NOTIFY option.
16feb98,cdp  added #ifndef _ASMLANGUAGE.
10jul96,dbt  added declaration of semMGiveForce (SPR #4352).
	     Updated copyright.
14jul94,dvs  added non-ANSI prototype for semCreate/semOLibInit (SPR# 2648).
22sep92,rrr  added support for c++.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle.
18apr92,jmm  added prototype for semTerminate.
19nov91,rrr  shut up some ansi warnings.
04oct91,rrr  passed through the ansification filter
	     -fixed #else and #endif
	     -changed ASMLANGUAGE to _ASMLANGUAGE
	     -changed copyright notice
10jun91.del  added pragma for gnu960 alignment.
16oct90,shl  made #else ANSI style.
05oct90,dnw  deleted private functions; doc tweaks
05oct90,shl  added ANSI function prototypes.
             made #endif ANSI style.
             added copyright notice.
27jun90,jcf  added defines for optimized version.
26jun90,jcf  rewritten to provide binary/counting/mutex w/ one structure.
	     introduced semaphore options.
     	     removed generic status codes.
02jan90,jcf  written.
*/

#ifndef __INCsemLibh
#define __INCsemLibh

#include <vxWorks.h>
#include <vwModNum.h>
#include <semLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif


/* semaphore options */

#define SEM_Q_MASK		 0x03	/* q-type mask */

#ifndef	_ASMLANGUAGE

/* macro used to statically declare semaphores */

#define VX_SEMAPHORE(name) \
        _WRS_DATA_ALIGN_BYTES(VX_OBJ_ALIGN_SIZE) char name [VX_SEMAPHORE_SIZE]

/*******************************************************************************
*
* VX_BINARY_SEMAPHORE - declare storage for a binary semaphore
*
* This macro declares storage for a binary semaphore having name <name>.
* This macro only generates data declarations for the binary semaphore.
* To fully instantiate the semaphore and make it ready for use, the function 
* semBInitialize() must be called after using this macro. This macro is 
* useful for declaring semaphores statically (i.e. at compile time, without
* using any dynamic memory allocation at runtime).
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <semLib.h>
* 
*      VX_BINARY_SEMAPHORE(mySemB);   /@ declare the semaphore @/
*      SEM_ID mySemBId;               /@ semaphore ID for further operations @/
* 
*      STATUS initializeFunction (void)
*          {
*          if ((mySemBId = semBInitialize (mysemB, options, 0)) == NULL)
*               return (ERROR);      /@ initialization failed @/
*          else
*               return (OK);
*          }
* \ce
* 
* SEE ALSO: semCInitialize(), semMInitialize()
* \NOMANUAL
*/

#define VX_BINARY_SEMAPHORE   VX_SEMAPHORE

/*******************************************************************************
*
* VX_COUNTING_SEMAPHORE - declare storage for a counting semaphore
*
* This macro declares storage for a counting semaphore having name <name>.
* This macro only generates data declarations for the counting semaphore.
* To fully instantiate the semaphore and make it ready for use, the function 
* semCInitialize() must be called after using this macro. This macro is 
* useful for declaring semaphores statically (i.e. at compile time, without
* using any dynamic memory allocation at runtime).
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <semLib.h>
* 
*      VX_COUNTING_SEMAPHORE(mySemC); /@ declare the semaphore @/
*      SEM_ID mySemCId;               /@ semaphore ID for further operations @/
* 
*      STATUS initializeFunction (void)
*          {
*          if ((mySemCId = semCInitialize (mysemC, options, 0)) == NULL)
*               return (ERROR);       /@ initialization failed @/
*          else
*               return (OK);
*          }
* \ce
* 
* SEE ALSO: semBInitialize(), semMInitialize()
* \NOMANUAL
*/

#define VX_COUNTING_SEMAPHORE VX_SEMAPHORE

/*******************************************************************************
*
* VX_MUTEX_SEMAPHORE - declare storage for a mutual exclusion semaphore
*
* This macro declares storage for a mutex semaphore having name <name>.
* This macro only generates data declarations for the mutex semaphore.
* To fully instantiate the semaphore and make it ready for use, the function 
* semMInitialize() must be called after using this macro. This macro is 
* useful for declaring semaphores statically (i.e. at compile time, without
* using any dynamic memory allocation at runtime).
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <semLib.h>
* 
*      VX_MUTEX_SEMAPHORE(mySemM);    /@ declare the semaphore @/
*      SEM_ID mySemMId;               /@ semaphore ID for further operations @/
* 
*      STATUS initializeFunction (void)
*          {
*          if ((mySemMId = semMInitialize (mySemM, options, 0)) == NULL)
*               return (ERROR);       /@ initialization failed @/
*          else
*               return (OK);
*          }
* \ce
* 
* SEE ALSO: semBInitialize(), semCInitialize()
* \NOMANUAL
*/

#define VX_MUTEX_SEMAPHORE    VX_SEMAPHORE

/*******************************************************************************
*
* VX_READ_WRITE_SEMAPHORE - declare storage for a reader/writer semaphore
*
* This macro declares storage for a reader/writer semaphore having name <name>.
* This macro only generates data declarations for the reader/writer semaphore.
* To fully instantiate the semaphore and make it ready for use, the function 
* semRWInitialize() must be called after using this macro. This macro is 
* useful for declaring semaphores statically (i.e. at compile time, without
* using any dynamic memory allocation at runtime).
*
* Sample usage of this macro is as follows:
* \cs
*      #include <vxWorks.h>
*      #include <semLib.h>
* 
*      #define NUM_READERS 0x20
*
*      VX_READ_WRITE_SEMAPHORE(mySemRW, NUM_READERS); /@ declare the semaphore @/
*      SEM_ID mySemRWId;               /@ semaphore ID for further operations @/
* 
*      STATUS initializeFunction (void)
*          {
*          if ((mySemRWId = semRWInitialize (mySemRW, options, NUM_READERS)) == 
*              NULL)
*               return (ERROR);       /@ initialization failed @/
*          else
*               return (OK);
*          }
* \ce
* 
* SEE ALSO: semMInitialize, semBInitialize(), semCInitialize()
* \NOMANUAL
*/

#define VX_READ_WRITE_SEMAPHORE(name, numReaders) \
        _WRS_DATA_ALIGN_BYTES(VX_OBJ_ALIGN_SIZE)  \
          char name [VX_SEMAPHORE_SIZE + SEM_RW_EXT_SIZE + \
                     (SEM_RW_LIST_ENTRY_SIZE * numReaders)]

/* function declarations */

extern void	semOpenInit	(void);
extern STATUS   semMGiveForce 	(SEM_ID semId);
#ifndef _WRS_CONFIG_CERT
extern STATUS   semRWGiveForce 	(SEM_ID semId);
#else
#define semRWGiveForce(semId)    semMGiveForce((semId))
#endif
extern SEM_ID   semBInitialize  (char * pSemMem, int options, 
				 SEM_B_STATE initialState);
extern SEM_ID   semCInitialize  (char * pSemMem, int options, 
				 int initialCount);
extern SEM_ID   semMInitialize  (char * pSemMem, int options);
#ifndef _WRS_CONFIG_CERT
extern SEM_ID   semRWInitialize (char * pSemMem, int options, int maxReaders);
#else
#define semRWInitialize(psemMem, options, maxReaders) \
          semMInitialize ((psemMem), (options)) /* drop maxReaders */
#endif
extern STATUS   semTerminate    (SEM_ID semId);

extern void 	semShowInit 	(void);
extern STATUS 	semShow 	(SEM_ID semId, int level);
extern int      semInfo         (SEM_ID semId, TASK_ID idList[], int maxTasks);

extern STATUS   semMTakeScalable (SEM_ID semId, _Vx_ticks_t timeout, 
                                  int options);
extern STATUS   semMGiveScalable (SEM_ID semId, int options);
extern STATUS   semBTakeScalable (SEM_ID semId, _Vx_ticks_t timeout, 
                                  int options);
extern STATUS   semBGiveScalable (SEM_ID semId, int options);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCsemLibh */
