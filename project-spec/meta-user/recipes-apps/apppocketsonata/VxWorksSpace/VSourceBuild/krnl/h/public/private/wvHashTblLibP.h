/* wvHashTblLibP.h - header for System Viewer hash table */


/*
 * Copyright (c) 2005-2006,2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,09feb10,tcr  64bit adaptation
01b,19dec06,tcr  make hash table SMP-safe
01a,22nov05,tcr  created
*/

#ifndef __INCwvHashTableLibP_h
#define __INCwvHashTableLibP_h

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
 
#define WV_HASH_TBL_SIZE                64

/* types */

typedef struct wvHashNode
    {
    char *              pEvent;         /* event data */
    size_t              eventSize;      /* size of event data */
    _Vx_usr_arg_t       key;            /* hash key */
    struct wvHashNode * next;           /* next node */
    } WV_HASH_NODE;
    

typedef struct tnHashTable
    {
    int                 size;
    WV_HASH_NODE **     tbl;		/* *tbl[] */
    SEM_ID              mutex;
    } WV_HASH_TBL;

typedef struct wvIterKey
    {
    int 	   index;
    WV_HASH_NODE * pCur;
    } WV_ITER_KEY;


/* function declarations */

extern WV_HASH_TBL * wvHashTblCreate
    (
    PART_ID             memPart,
    int                 tblSize
    );
    
extern STATUS wvHashTblDestroy
    (
    WV_HASH_TBL *       pTbl,
    PART_ID             memPart
    );
    
extern STATUS wvHashTblInsert
    (
    WV_HASH_TBL *       pTbl,
    PART_ID             memPart,
    char *              pEvent,
    size_t             	eventSize,
    _Vx_usr_arg_t       key
    );

extern void wvHashTblIterDone
    (
    WV_ITER_KEY *       pIterKey,
    WV_HASH_TBL *       pTbl
    );

extern WV_ITER_KEY * wvHashTblIterInit 
    (
    WV_HASH_TBL *       pTbl
    );

extern WV_HASH_NODE * wvHashTblIterNext
    (
    WV_HASH_TBL *       pTbl,
    WV_ITER_KEY *       pIterKey
    );


    
#ifdef __cplusplus
}
#endif


#endif /* __INCwvHashTableLibP_h */
