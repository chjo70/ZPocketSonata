/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_i86NehalemUncoreEventConfig_h
#define INChpc_i86NehalemUncoreEventConfig_h

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS hpcI86NehalemUncFinit (void);
extern STATUS hpcI86NehalemUncInit
    (
    unsigned int intCore
    );
extern struct hpcDriverConfig * hpcI86NehalemUncDrvCfgGet(void);
extern struct hpcDriverConfig * hpcI86NehalemUncFixedDrvCfgGet(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_i86NehalemUncoreEventConfig_h */
