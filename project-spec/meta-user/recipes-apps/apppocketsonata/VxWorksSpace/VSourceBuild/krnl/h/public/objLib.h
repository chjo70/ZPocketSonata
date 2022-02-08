/* objLib.h - object management library header */

/*
 * Copyright (c) 1989-2005, 2009-2010, 2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02jan18,dlk  Add objNameSpaceToId() (V7COR-5445)
20oct10,kk   updated object routine prototypes based on review.
28jul10,kk   added additional object routine prototypes
29apr10,pad  Moved extern C statement after include statements.
24feb09,zl   changed bufSize argument to size_t
26jan05,kk   remove OBJ_DETECT_NAME_CLASH references (SPR# 105824)
             added missing public APIs, removed objNameShow APIs.
14sep04,lei  moved back objOwnerGet() prototype from objLibP.h
28apr04,dcc  added objContextGet() and objContextSet() prototypes.
26mar04,dcc  updated objNameToId() API. moved objOwnerGet(), objOwnerSet(),
             and objNameSet() protoypes to objLibP.h
31oct03,dat  adding const to objNameSet name argument.
29oct03,dat  objNameToId uses a const char *
12sep03,aeg  added include of objLibCommon.h
21aug03,dcc  updated objNameToId() signature. Added open flags.
14mar03,dcc  ported from AE1.1
20jun96,kkk	 undid 01p change.
09feb96,mem  test for NULL pointer in OBJ_VERIFY.
31aug94,rdc  beefed up OBJ_VERIFY.
15oct93,cd   added #ifndef _ASMLANGUAGE.
10dec93,smb  modified OBJ_VERIFY for windview level 1 instrumentation
22sep92,rrr  added support for c++
29jul92,jcf  added errno.h include.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04dec91,rrr  some ansi cleanup.
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed VOID to void
             -changed copyright notice
10jun91.del  added pragma for gnu960 alignment.
05apr91,gae  added NOMANUAL to avoid fooling mangen.
05oct90,shl  added ANSI function prototypes.
             made #endif ANSI style.
             added copyright notice.
15jul90,dnw  changed objAlloc() from (char*) to (void*)
             added objAllocExtra()
26jun90,jcf  added objAlloc()/objFree().
             added standard object status codes.
10dec89,jcf  written.
*/

#ifndef __INCobjLibh
#define __INCobjLibh

#include "vxWorks.h"
#include "objLibCommon.h"	/* errnos for objLib located here */
#include "errno.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* Note that OBJ_ID is declared in types/vxWind.h */

/* function declarations */

extern enum windObjClassType objClassTypeGet (OBJ_ID objId);

extern STATUS 	objContextGet	(OBJ_ID objId, void ** pContext);
extern STATUS 	objContextSet	(OBJ_ID objId, void * context);
extern STATUS   objHandleShow   (OBJ_HANDLE objHandle, RTP_ID rtpId);
extern void     objHandleTblShow(RTP_ID rtpId, int disp);
extern STATUS	objNameGet 	(OBJ_ID objId, char * nameBuf, size_t bufSize);
extern ssize_t	objNameLenGet 	(OBJ_ID objId);
extern OBJ_ID	objNameToId 	(enum windObjClassType classType,
			         const char * name);
extern OBJ_ID   objNameSpaceToId(enum windObjClassType classType,
                                 const char * name,
                                 BOOL  nsPublic);
extern OBJ_ID	objOwnerGet 	(OBJ_ID objId);
extern STATUS	objOwnerSet 	(OBJ_ID objId, OBJ_ID ownerId);
extern STATUS 	objShow 	(OBJ_ID objId, int showType);
extern STATUS 	objShowAll 	(OBJ_ID objId, int showType);

extern OBJ_HANDLE objRtpHandleAlloc (OBJ_ID objId);
extern STATUS   objRtpHandleFree    (OBJ_HANDLE handle);
extern OBJ_ID   objRtpAccess        (OBJ_HANDLE handle);
extern STATUS   objRtpRelease       (OBJ_ID objId);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCobjLibh */
