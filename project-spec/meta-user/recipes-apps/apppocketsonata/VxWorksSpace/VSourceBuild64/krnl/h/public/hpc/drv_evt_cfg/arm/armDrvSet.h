/* Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
13mar14,wzc  support arm hpc(US17715)
*/

/*
DESCRIPTION
*/

#ifndef INChpc_armDriverSettings_h
#define INChpc_armDriverSettings_h

#ifdef __cplusplus
extern "C" {
#endif

extern int armEventSettingsGet
    (
    struct cafe_value_type * pType,
    union eventSettings * pDrvSettings,
    struct hpcEventSettings * pHpcSettings,
    const struct hpcEventDescriptor *pEvtDesc
    );

#ifdef __cplusplus
}
#endif
#endif /* INChpc_armDriverSettings_h */
