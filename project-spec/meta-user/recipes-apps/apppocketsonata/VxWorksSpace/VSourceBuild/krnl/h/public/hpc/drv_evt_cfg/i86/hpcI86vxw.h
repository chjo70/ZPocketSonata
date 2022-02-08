/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_hpcI86vxw_h
#define INChpc_hpcI86vxw_h

#ifdef __cplusplus
extern "C" {
#endif

extern void hpcVxwI86PerfMonIsrEnable(void);
extern void hpcVxwI86PerfMonIsrDisable(void);
extern void hpcVxwI86PerfMonIsrAck(void);
void hpcVxwI86PerfIsrConnectVec
    (
    void (*pPerfMonVector)(void),
    int (*pPerfMonHandler)(void *)
    );
extern void hpcVxwI86PerfIsrDisconnectVec
    (
    int (*pPerfMonHandler)(void *),
    int force
    );

void hpcI86Init(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_hpcI86vxw_h */

