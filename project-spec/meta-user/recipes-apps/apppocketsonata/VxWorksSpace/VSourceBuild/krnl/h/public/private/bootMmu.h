/* bootMmu.h - bootapp mmu handling header file */

/*
 *  Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13mar14,my_  written (US35020, bootapp part)
*/

#ifndef __INCbootmmuh__
#define __INCbootmmuh__

#ifdef __cplusplus
extern "C" {
#endif

STATUS elfLoadMapAddrBlock
	(
	PHYS_ADDR pAddr,
	VIRT_ADDR vAddr,
	ptrdiff_t numBytes,
	char ** load_addr
	);

STATUS elfLoadUnmapAddrBlock
	(
	PHYS_ADDR pAddr,
	VIRT_ADDR vAddr,
	ptrdiff_t numBytes,
	char * load_addr
	);	

void bootAppStub(void *, void *, void *);
void bootAppMmuDisableAndGo(void);
void bootAppMmuInit();

#ifdef __cplusplus
}
#endif

#endif
