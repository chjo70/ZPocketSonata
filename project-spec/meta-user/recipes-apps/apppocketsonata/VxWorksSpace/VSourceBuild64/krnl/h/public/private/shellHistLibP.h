/* shellHistLibP.h - shell history management routines private header */

/*
 * Copyright (c) 2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,26jul07,v_r  Added histSave() and histLoad() prototypes to be able to
                 reference them from usrExtra.c
01a,19jul07,v_r  Created. Contains the prototypes for the shell history
		 saving/loading private routines (req CQ:WIND00005098).
*/

#ifndef __INCshellHistLibPh
#define __INCshellHistLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* Typedefs */

typedef enum shellHistOp
    {
    SHELL_HIST_SAVE = 1,
    SHELL_HIST_LOAD
    } SHELL_HIST_OP;

/* Function declarations */

extern void	histSave	    (char * saveFile, BOOL allInterp);
extern void	histLoad	    (char * loadFile, BOOL allInterp);
extern STATUS	shellHistLibInit    (void);
extern STATUS	shellHistSaveOrLoad (BOOL allInterp, char * histFile, 
				       SHELL_HIST_OP operation);
#ifdef __cplusplus
}
#endif
#endif /* __INCshellHistLibPh */

