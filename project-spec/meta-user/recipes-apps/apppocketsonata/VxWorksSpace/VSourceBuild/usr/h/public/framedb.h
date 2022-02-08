/*	Definition module : framedb.h

	Copyright 1998 Diab Data Inc, USA

	Description :
	Frameinfo routines for walking and unwinding the stack.

	History :
	When	Who	What
	000724	fburton	Extracted from Java throw and made generic
*/

#ifndef D_framedb
#define D_framedb

#include <string.h>
#include <assert.h>

#ifdef	__cplusplus
#define	EXTERN_C extern "C"
#else
#define	EXTERN_C extern
#endif

/**************	Exported data, types and macros	*********/

typedef struct _FrameInfoSection {
	unsigned long		*_LowAdr;
	unsigned long		*_HighAdr;
	unsigned long		_LowEntry;
	unsigned long		_Pad;
} _FrameInfoSection, *_FrameInfoSectionP;

/**************	Exported functions **********************/

EXTERN_C void __frameinfo_add(void *, void *);
EXTERN_C void __frameinfo_del(void *, void *);
EXTERN_C _FrameInfoSectionP __frameinfo_find(void *);

#endif
