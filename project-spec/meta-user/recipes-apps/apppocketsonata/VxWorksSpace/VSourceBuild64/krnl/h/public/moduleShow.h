/* moduleShow.h - object module list management show routine */

/* 
 * Copyright (c) 2004-2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. 
 */

/*
modification history
--------------------
01d,25oct06,v_r  Added option to print full module name and path (as part of
                 defect CQ:WIND00034839 fix).
01c,25jul05,v_r  Updated copyright.
01b,05apr04,jn   Clean up development-related comments
01a,27feb04,jn	 written.  Put moduleShow in a separate component, 
                 INCLUDE_MODULE_SHOW 
*/

#ifndef __INCmoduleShowh
#define __INCmoduleShowh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define MODDISPLAY_LONG	0x1 /* print full module name and path */

/* function declarations */

extern STATUS moduleShow 
    (
    char *	moduleNameOrId, 
    int 	options 
    );

extern void moduleShowInit (void);


#ifdef __cplusplus
}
#endif

#endif /* __INCmoduleShowh */
