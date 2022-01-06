/* sdLibP.h - private shared data library header file */

/* 
 * Copyright (c) 2003-2005, 2007-2011, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
05nov14,cww  fix static analysis issues
24aug11,zl   added SD state for SMP, moved reference counting 
             code directly to sdLib.
22feb10,jpb  Updated for LP64 adaptation.
18may09,jmp  Added missing sdClassId and sdShow()
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
11may07,pcs  Remove macro SD_DEFAULT_CACHE_COHERENCY, since SD lib now
             uses VM_DEFAULT_CACHE_COHERENCT_ATTR.
23apr07,pcs  Move SD_LOCK & SD_UNLOCK to sdLib.c
07jul05,zl   embedded semaphore in SD structure.
28mar05,zl   added sdRtpUnmap() prototype.
08feb05,zl   added sdRtpMap() prototype.
02oct04,gls  added sdLibInit() and sdShowInit() declarations
24sep04,gls  removed MMU_ATTR_CACHE_MSK from SD_ATTR_MASK
19jul04,gls  added hook routines (SPR #98361)
04may04,gls  added currentAttr to SD_NODE
29mar04,gls  added include of objLibP.h (SPR #95051)
04mar04,gls  removed sdListNode from WIND_SD struct
17feb04,gls  cleaned up
11dec03,gls  added functionality
04nov03,kk   written
*/

#ifndef __INCsdLibPh
#define __INCsdLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <sdLib.h>
#include <vxAtomicLib.h>
#include <private/objLibP.h>
#include <private/semLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

extern CLASS_ID sdClassId;

extern STATUS   sdLibInit	(const int hookTblSize);
extern void     sdShowInit	(void);
extern BOOL	sdShow		(char * sdNameOrId, int level);

/* defines */

#define SD_DEFAULT_ATTR (MMU_ATTR_SUP_RW | MMU_ATTR_USR_RW | \
                         MMU_ATTR_VALID | MMU_ATTR_CACHE_DEFAULT)

#define SD_ATTR_MASK    (MMU_ATTR_PROT_MSK | MMU_ATTR_VALID_MSK | \
			 MMU_ATTR_SPL_MSK) 

/* private options */

#define	SD_LIB_TEXT	0x00000003	/* SD is used for SL */
#define	SD_HOOK_IGNORE	0x00000004	/* internal call, skip hook routines */


#ifndef	_ASMLANGUAGE

#define SD_LOCK(sdId)           semTake(&(sdId)->sem, WAIT_FOREVER)
#define SD_UNLOCK(sdId)         (void) semGive(&(sdId)->sem)


#define SD_STATE_NORMAL			1
#define SD_STATE_DELETE_PENDING		2

#define SD_DELETER_PENDED		1
#define SD_REFCNT_INCR			2
#define SD_REFCNT_UNPEND		(SD_REFCNT_INCR | SD_DELETER_PENDED)

/* typedef */

typedef struct sdNode		/* Node of a linked list. */
    {
    struct dlnode *next;	/* Points at the next node in the list */
    struct dlnode *previous;	/* Points at the previous node in the list */

    SD_ID    sdId;
    MMU_ATTR currentAttr;	/* Current MMU attributes of SD in the RTP */
    } SD_NODE;

typedef struct wind_sd
    {
    OBJ_CORE	 objCore;		/* object management */
    SEMAPHORE    sem;			/* SD semaphore */
    int		 options;		/* SD options */
    MMU_ATTR	 attr;			/* MMU attributes allowed on this SD */
    size_t	 size;			/* size of the SD */
    PHYS_ADDR	 physAdrs;		/* start physical address of mapping */
    VIRT_ADDR	 virtAdrs;		/* start virtual address of mapping */
    volatile int clientCount;		/* current number of client RTPs */
#ifdef _WRS_CONFIG_SMP
    UINT32	 state;			/* SD state */
    atomic32_t   refCnt;                /* reference count for SMP */
    Q_HEAD       deleterPendQ;          /* deleter pend queue */
#endif /* _WRS_CONFIG_SMP */
    } WIND_SD;

extern CLASS_ID sdClassId;

/* private function declarations */

extern STATUS    sdVerifiedLock (SD_ID sdId);
extern VIRT_ADDR sdRtpMap (SD_ID sdId, MMU_ATTR attr, int options,
			   RTP_ID rtpId);
extern STATUS    sdRtpUnmap (SD_ID sdId, RTP_ID rtpId, int options);
extern BOOL      sdIsMapped (SD_ID sdId, RTP_ID rtpId, SD_NODE ** ppSdIdNode);

extern STATUS    sdLibInit (const int hookTblSize);
extern void      sdShowInit (void);
extern BOOL	 sdShow	(char * sdNameOrId, int level);


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* __INCsdLibPh */

