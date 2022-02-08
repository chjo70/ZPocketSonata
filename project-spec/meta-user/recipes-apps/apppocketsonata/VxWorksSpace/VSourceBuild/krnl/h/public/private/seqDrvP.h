/* seqDrvP.h - event buffer library header */

/*
 *  Copyright (c) 1993,2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01b,04feb10,tcr  64bit update
01a,10dec93,smb  written.
*/

#ifndef __INCseqdrvph
#define __INCseqdrvph


#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)

extern UINT32   seqStamp (void);
extern UINT32   seqStampLock (void);
extern STATUS 	seqEnable (void);
extern STATUS 	seqDisable (void);
extern STATUS 	seqConnect (FUNCPTR dummy, _Vx_usr_arg_t dummyArg );
extern UINT32   seqPeriod (void);
extern UINT32   seqFreq (void);

#else   /* __STDC__ */

extern UINT32   seqStamp ();
extern UINT32   seqStampLock ();
extern STATUS 	seqEnable ();
extern STATUS 	seqDisable ();
extern STATUS 	seqConnect ();
extern UINT32   seqPeriod ();
extern UINT32   seqFreq ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCseqdrvph */

