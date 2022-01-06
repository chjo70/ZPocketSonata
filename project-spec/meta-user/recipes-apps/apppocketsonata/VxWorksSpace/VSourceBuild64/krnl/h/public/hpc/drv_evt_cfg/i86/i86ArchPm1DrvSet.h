/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_i86ArchPm1DriverSettings_h
#define INChpc_i86ArchPm1DriverSettings_h

#ifdef __cplusplus
extern "C" {
#endif

extern int i86ArchPm1EventSettingsGet
    (
    struct cafe_value_type * pType,
    union eventSettings * pDrvSettings,
    struct hpcEventSettings * pHpcSettings,
    const struct hpcEventDescriptor *pEvtDesc
    );

#ifdef __cplusplus
}
#endif
#endif /* INChpc_i86ArchPm1DriverSettings_h */
