/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INChpc_e500vxw_h
#define INChpc_e500vxw_h
#ifdef __cplusplus
extern "C" {
#endif

typedef int (*E500_PERF_HANDLER)(void *);

extern E500_PERF_HANDLER vxwE500PerfIsrEnable(int (*pHandler)(void *));
extern STATUS vxwE500PerfIsrDisable(int (*pHandler)(void *));
#ifndef HIDE
extern unsigned int readPMC0(void);
extern unsigned int readPMC1(void);
extern unsigned int readPMC2(void);
extern unsigned int readPMC3(void);
extern unsigned int readPMGC0(void);
extern unsigned int readPMLCa0(void);
extern unsigned int readPMLCa1(void);
extern unsigned int readPMLCa2(void);
extern unsigned int readPMLCa3(void);
extern unsigned int readPMLCb0(void);
extern unsigned int readPMLCb1(void);
extern unsigned int readPMLCb2(void);
extern unsigned int readPMLCb3(void);
extern void writePMC0(unsigned int);
extern void writePMC1(unsigned int);
extern void writePMC2(unsigned int);
extern void writePMC3(unsigned int);
extern void writePMGC0(unsigned int);
extern void writePMLCa0(unsigned int);
extern void writePMLCa1(unsigned int);
extern void writePMLCa2(unsigned int);
extern void writePMLCa3(unsigned int);
extern void writePMLCb0(unsigned int);
extern void writePMLCb1(unsigned int);
extern void writePMLCb2(unsigned int);
extern void writePMLCb3(unsigned int);
#endif

extern STATUS hpcVxwDevicePerfIsrEnable(int (*pHandler)(void *));
extern STATUS hpcVxwDevicePerfIsrDisable(int (*pHandler)(void *));

extern STATUS vxwMpc8540PerfIsrEnable(int (*pHandler)(void *));
extern STATUS vxwMpc8540PerfIsrDisable(int (*pHandler)(void *));

extern STATUS vxwFslP2020PerfIsrEnable(int (*pHandler)(void *));
extern STATUS vxwFslP2020PerfIsrDisable(int (*pHandler)(void *));

extern void devPmcRegSet(int counter, unsigned long long value);
extern unsigned long long devPmcRegGet(int counter);
extern void devPmlcaRegSet(int counter, unsigned int value);
extern unsigned int devPmlcaRegGet(int counter);
extern void devPmlcbRegSet(int counter, unsigned int value);
extern unsigned int devPmlcbRegGet(int counter);
extern void devPmgc0RegSet(unsigned int value);
extern unsigned int devPmgc0RegGet(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_e500vxw_h */
