/*	Definition module : unwind-fi.h

	Copyright 2010 Wind River Systems

	Description :
	Unwinder implementation using legacy frameinfo

	History :
	When	Who	What
	100617	salim	initial
*/

/* TODO
 */
#ifndef D_unwind_fi
#define D_unwind_fi

#include "unwind.h"
#include "frameinfo.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _Unwind_Context {
	struct cpu_info cpuinfo;
	int first_frame;

	/* valid if !first_frame */
	unsigned long frame;
	unsigned long fsize;
#ifdef __HAS_ADJUSTED_FSIZE__
	unsigned long afsize;
#endif

	/* valid while calling personality routine for a frame */
	_Unwind_Ptr language_specific_data;
	_Unwind_Ptr region_start;
};

#ifdef __cplusplus
}
#endif

#endif /* D_unwind */
