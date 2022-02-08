/* spyLibP.h - private spy library header file */

/*
 * Copyright (c) 2009-2011 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
01c,27sep11,rlp  Added ability to disable symbol lookup & display in spy -
                 CQID: WIND00285819.
01b,29apr10,pad  Moved extern C statement after include statements.
01a,01jul09,jmp  Written
*/

#ifndef __INCspyLibPh
#define __INCspyLibPh

/* includes */

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Hooks for spy library */

extern void (* _func_spy)
    (
    int		freq,		/* reporting freq in sec, 0 = default of 5 */
    int		ticksPerSec,	/* interrupt clock freq, 0 = default of 100 */
    FUNCPTR	printRtn	/* routine to use to display results */
    );

extern void (* _func_spy2)
    (
    int		freq,		/* reporting freq in sec, 0 = default of 5 */
    int		ticksPerSec,	/* interrupt clock freq, 0 = default of 100 */
    BOOL	noSym,		/* Disable symbol lookup & display */
    FUNCPTR	printRtn	/* routine to use to display results */
    );

extern void (* _func_spyStop) (void);

extern STATUS (* _func_spyClkStart)
    (
    int		intsPerSec,	/* timer interrupt freq, 0 = default of 100 */
    FUNCPTR	printRtn	/* routine to display results */
    );

extern void (* _func_spyClkStop) (void);

extern void (* _func_spyReport)
    (
    FUNCPTR	printRtn	/* routine to display results */
    );

extern void (* _func_spyReport2)
    (
    FUNCPTR	printRtn,	/* routine to display results */
    BOOL	noSym		/* Disable symbol lookup & display */
    );

extern void (* _func_spyTask)
    (
    int		freq,		/* reporting frequency, in seconds */
    FUNCPTR	printRtn	/* routine to display results */
    );

/* function declarations */

extern STATUS	spyClkStartCommon	(int intsPerSec, FUNCPTR printRtn);
extern void	spyCommon		(int freq, int ticksPerSec,
					 FUNCPTR printRtn);
extern void	spyCommon2		(int freq, int ticksPerSec,
					 BOOL noSym, FUNCPTR printRtn);
extern void	spyClkStopCommon	(void);
extern void	spyReportCommon		(FUNCPTR printRtn);
extern void	spyReportCommon2	(FUNCPTR printRtn, BOOL noSym);
extern void	spyStopCommon		(void);
extern void	spyComTask		(int freq, FUNCPTR printRtn);

#ifdef __cplusplus
}
#endif

#endif	/* __INCspyLibPh */
