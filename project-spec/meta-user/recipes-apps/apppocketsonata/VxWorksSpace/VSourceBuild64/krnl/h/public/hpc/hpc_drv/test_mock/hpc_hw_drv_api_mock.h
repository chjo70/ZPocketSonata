#ifndef INChpc_hw_drv_api_mock_h
#define INChpc_hw_drv_api_mock_h

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {OK = 0, ERROR = -1} STATUS;

extern int vxCpuIndexGet(void);
extern int intCount(void);
extern int intCpuLock(void);
extern void intCpuUnlock(int key);

extern void pentiumMsrGet(int addr, long long int *pData);
extern void pentiumMsrSet(int addr, long long int *pData);
extern STATUS setArmPmuCounterOverflow(int counter);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_hw_drv_api_mock_h */
