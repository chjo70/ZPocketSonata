/* shlLibCommon.h - common shared library support library header file */

/*
 * Copyright (c) 2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,27may10,pad  Moved 'extern C' statement to include type definitions.
01c,05nov04,kk   added S_shlLib_SHL_ACCESS_DENIED
01b,20apr04,pad  Added errno S_shlLib_INVALID_PARAMETER.
01a,26mar04,dms  created based on sdLibCommon.h
*/

#ifndef __INCshlLibCommonh
#define	__INCshlLibCommonh

#include <vxWorks.h>
#include <vwModNum.h>

/* errno values */

#define	S_shlLib_ID_SPACE_EXHAUSTED		(M_shlLib | 1)
#define	S_shlLib_INVALID_SH_INITFLG_CHANGE	(M_shlLib | 2)
#define	S_shlLib_INVALID_GOTT_INDEX		(M_shlLib | 3)
#define	S_shlLib_INVALID_SHL_ID			(M_shlLib | 4)
#define	S_shlLib_INVALID_PARAMETER		(M_shlLib | 5)
#define	S_shlLib_SHL_ACCESS_DENIED		(M_shlLib | 6)

/* options */

/* Set in shlFlags to indicate that the library has been initialized.  */
#define	SHL_INITFLG		0x00000001

/* This is a system-wide limit on the number of shared objects.  */
#define	MAX_SHARED_OBJECTS	1023

#ifdef __cplusplus
extern "C" {
#endif

/* data structures */

typedef struct
    {
    UINT32	shlFlags;
    int		shlGOTTINDEX;	/* unique small integer ID */
    VIRT_ADDR	shlTextBase;	/* address of shared library text segment */
    size_t	shlTextSize;	/* size of shared library text segment */
    VIRT_ADDR	shlDataBase;	/* address of shared library data in the RTP */
    size_t	shlDataSize;	/* size of shared library data segment */
    } SHLINFO;

/* functional API to the library */

SHL_ID	_shlOpen	(const char *		name,
			 int			options);

void	_shlUnlock	(SHL_ID			shlId);

STATUS	_shlGet		(SHL_ID			shlId,
			 SHLINFO *		info);

STATUS	_shlPut		(SHL_ID			shlId,
			 const SHLINFO *	info);

STATUS	_shlClose	(SHL_ID			shlId);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __INCshlLibCommonh */
