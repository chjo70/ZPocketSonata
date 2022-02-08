/* dataSegPad.c - padding for beginning of data segment */

/* Copyright (c) 1992, 2004, 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12oct17,sub  Removed SPR96639_FIXED macro related code
30sep04,jpb  V7COR-1690: removed comment
27sep04,tam  replaced INCLUDE_EDR_KH by INCLUDE_KERNEL_HARDENING
02sep04,pes  Conditionalize the alignment of dataSegPad
08jun04,tam  added EDR_KH handling
03may04,tam  updated data segment alignment code
19oct92,jcf  change to include when INCLUDE_MMU_FULL defined.
28jul92,rdc  changed PAGE_SIZE to VM_PAGE_SIZE.
21jul92,rdc  written.
*/

/*
DESCRIPTION

This module conditionally defined the variable dataSegPad which is aligned
on a MMU page size boundary by default; it is explicitly listed as the first
module on the load line when VxWorks is linked to insure that this data
structure is the first item in the data segment. This mechanism is needed
to insure that the data segment does not overlap a page that is occupied
by the text segment;  when text segment protection is turned on, all pages
that contain text are write protected. This insures that the data segment
does not lie in a page that has been write protected. If text segment
protection has not been included, this module compiles into a null object
module. Note that if the data segment needs to be aligned on a boundary
larger than an MMU page size, then KERNEL_DATA_SEG_ALIGN should be defined
to that alignment, otherwise it defaults to a MMU page size (VM_PAGE_SIZE).

In an embedded system, this mechanism may not be needed if the loader
explicitly places the data segment in a section of memory separate from
the text segment.
*/

#include <vxWorks.h>
#ifdef _WRS_CONFIG_COMPAT69
#   include <config.h>
#else /* !_WRS_CONFIG_COMPAT69 */
#   include <prjParams.h>
#endif /* _WRS_CONFIG_COMPAT69 */

#if !defined (_WRS_LINKER_DATA_SEG_ALIGN)

#ifndef	KERNEL_DATA_SEG_ALIGN
#define	KERNEL_DATA_SEG_ALIGN	VM_PAGE_SIZE
#endif	/* KERNEL_DATA_SEG_ALIGN */

#if	(defined(INCLUDE_PROTECT_TEXT) || defined(INCLUDE_KERNEL_HARDENING))
/* bootroms will not ref dataSegPad.o */

char  	_WRS_DATA_ALIGN_BYTES(KERNEL_DATA_SEG_ALIGN) dataSegPad = 1;

#endif /* INCLUDE_PROTECT_TEXT */
#else /* _WRS_LINKER_DATA_SEG_ALIGN */
/*
 * declaration for architectures that use the linker to ensure proper data
 * segment alignment.
 */
char  	dataSegPad = 1;
#endif /* _WRS_LINKER_DATA_SEG_ALIGN */
