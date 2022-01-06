/*
 
 */

#ifndef __ntp_vxworks
#define __ntp_vxworks


#ifdef NTP_VXWORKS_6
#undef IPCRYPTO_USE_TYPE_MAPPING
#endif

#ifndef NTP_VXWORKS_7
#define IPCOM_USE_CLIB_PROTO
#endif
#include <ipcom_clib.h>
#include <ipcom_err.h>

#include <time.h>

#ifdef SYS_VXWORKS
#define NO_MAIN_ALLOWED 	1
#endif /* SYS_VXWORKS */

#ifdef IPNTP_USE_TEST
#define NTP_SYSCLKRATEGET    60
#else
extern  int sysClkRateGet(void);
#define NTP_SYSCLKRATEGET    (sysClkRateGet())
#endif

#endif /* __ntp_vxworks */
