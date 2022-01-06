/* stdcomp.h - True Flash File System */

/*
 * Copyright (c) 1984-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/* FAT-FTL Lite Software Development Kit
 * Copyright (C) M-Systems Ltd. 1995-1997	*/

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,29jul04,alr  modified file header, restarted history
*/

#ifndef STDCOMP_H
#define STDCOMP_H

#include "flbase.h"
#include "fltl.h"
#include "flflash.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MTD Identify Routines */

FLStatus amdMTDIdentify (FLFlash vol);
FLStatus i28f008Identify (FLFlash vol);
FLStatus i28f008BajaIdentify (FLFlash vol);
FLStatus i28f016Identify (FLFlash vol);
FLStatus cdsnIdentify (FLFlash vol);
FLStatus doc2Identify (FLFlash vol);
FLStatus cfiscsIdentify (FLFlash vol);
FLStatus cfiAmdIdentify (FLFlash vol);
FLStatus flwAmdMTDIdentify (FLFlash vol);

/* TL Mount and Format Routines */

FLStatus mountFTL (FLFlash *flash, TL *tl, FLFlash **volForCallback);
FLStatus formatFTL (FLFlash *flash, FormatParams FAR1 *formatParams);
FLStatus mountNFTL (FLFlash *flash, TL *tl, FLFlash **volForCallback);
FLStatus formatNFTL (FLFlash *flash, FormatParams FAR1 *formatParams);
FLStatus mountSSFDC (FLFlash *flash, TL *tl, FLFlash **volForCallback);
FLStatus formatSSFDC (FLFlash *flash, FormatParams FAR1 *formatParams);


/*----------------------------------------------------------------------*/
/*    	    Component registration routine in CUSTOM.C			*/
/*----------------------------------------------------------------------*/

void	flRegisterComponents(void);

#ifdef __cplusplus
}
#endif

#endif /* STDCOMP_H */
