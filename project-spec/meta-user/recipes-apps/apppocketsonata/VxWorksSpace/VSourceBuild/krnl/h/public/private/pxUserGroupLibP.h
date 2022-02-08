/* pxUserGroupLibP.h - private header for VxWorks user and group management */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17feb15,ymz  added missing prototypes (flexelint fixes)
17sep14,pad  Added the 'loginUserId' field in WIND_CREDENTIALS (US44416).
26aug14,pad  Added support for effective user and group IDs as well as saved
             set-user and saved set-group IDs (US44512).
04jul14,pad  Added RTP_REAL_USER_ID_OF() and RTP_REAL_GROUP_ID_OF() (US40207).
13jun14,pad  Created (US38499).
*/

#ifndef __INCpxUserGroupLibPh
#define __INCpxUserGroupLibPh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define ROOT_USER_ID            1
#define ROOT_GROUP_ID           1
#define NO_LOGIN_USER_ID	0

#define REAL_USER_ID_OF(tid) \
    ((WIND_CREDENTIALS *)(((WIND_TCB *)(tid))->pCredentials))->realUserId
#define EFFECTIVE_USER_ID_OF(tid) \
    ((WIND_CREDENTIALS *)(((WIND_TCB *)(tid))->pCredentials))->effectiveUserId
#define SAVED_SET_USER_ID_OF(tid) \
    ((WIND_CREDENTIALS *)(((WIND_TCB *)(tid))->pCredentials))->savedSetUserId

#define LOGIN_USER_ID_OF(tid) \
    ((WIND_CREDENTIALS *)(((WIND_TCB *)(tid))->pCredentials))->loginUserId

#define REAL_GROUP_ID_OF(tid) \
    ((WIND_CREDENTIALS *)(((WIND_TCB *)(tid))->pCredentials))->realGroupId
#define EFFECTIVE_GROUP_ID_OF(tid) \
    ((WIND_CREDENTIALS *)(((WIND_TCB *)(tid))->pCredentials))->effectiveGroupId
#define SAVED_SET_GROUP_ID_OF(tid) \
    ((WIND_CREDENTIALS *)(((WIND_TCB *)(tid))->pCredentials))->savedSetGroupId

#ifdef _WRS_CONFIG_RTP
#define RTP_REAL_USER_ID_OF(pid) \
    ((WIND_CREDENTIALS *)(((WIND_RTP *)(pid))->pCredentials))->realUserId
#define RTP_EFFECTIVE_USER_ID_OF(pid) \
    ((WIND_CREDENTIALS *)(((WIND_RTP *)(pid))->pCredentials))->effectiveUserId
#define RTP_SAVED_SET_USER_ID_OF(pid) \
    ((WIND_CREDENTIALS *)(((WIND_RTP *)(pid))->pCredentials))->savedSetUserId

#define RTP_REAL_GROUP_ID_OF(pid) \
    ((WIND_CREDENTIALS *)(((WIND_RTP *)(pid))->pCredentials))->realGroupId
#define RTP_EFFECTIVE_GROUP_ID_OF(pid) \
    ((WIND_CREDENTIALS *)(((WIND_RTP *)(pid))->pCredentials))->effectiveGroupId
#define RTP_SAVED_SET_GROUP_ID_OF(pid) \
    ((WIND_CREDENTIALS *)(((WIND_RTP *)(pid))->pCredentials))->savedSetGroupId

#define RTP_LOGIN_USER_ID_OF(pid) \
    ((WIND_CREDENTIALS *)(((WIND_RTP *)(pid))->pCredentials))->loginUserId
#endif /* _WRS_CONFIG_RTP */

/* Typedefs */

typedef struct wind_credentials
    {
    uid_t realUserId;
    gid_t realGroupId;
    uid_t effectiveUserId;
    gid_t effectiveGroupId;
    uid_t savedSetUserId;
    gid_t savedSetGroupId;
    uid_t loginUserId;      /* user ID of user authenticated through login */
    } WIND_CREDENTIALS;

/* Function declarations */

extern STATUS taskCredentialsInherit
    (
    TASK_ID tid   /* task inheriting caller's credentials */
    );

#ifdef _WRS_CONFIG_RTP
extern STATUS rtpCredentialsInherit
    (
    RTP_ID rtpId   /* RTP inheriting caller's credentials */
    );
#endif /* _WRS_CONFIG_RTP */

extern STATUS taskCredentialsGet
    (
    TASK_ID            tid,            /* task which credentials must be had */
    WIND_CREDENTIALS * pCredentials    /* where to store the credentials */
    );

extern STATUS taskCredentialsSet
    (
    WIND_CREDENTIALS * pCredentials,    /* credentials to use */
    TASK_ID            tid              /* task which credentials must be set */
    );

extern STATUS pxUserGroupLibInit (void);
extern STATUS pxUserGroupScLibInit (void);
extern void loginUserIdSet (uid_t userId);

#ifdef __cplusplus
}
#endif

#endif /* __INCpxUserGroupLibPh */
