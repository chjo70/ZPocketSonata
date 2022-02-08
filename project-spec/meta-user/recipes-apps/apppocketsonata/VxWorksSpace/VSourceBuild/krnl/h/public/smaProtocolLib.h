/* smaProtocolLib.h - stop mode agent protocol header file */

/*
 * Copyright (c) 2014,2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24mar15,elp  Added hardware breakpoint support (US41503)
19nov14,sdt  Added exceptions support (US44279)
07jul14,jmp  created from Hypervisor 2.1 gdb serial code.
*/

#ifndef __INCsmaProtocolLibh
#define __INCsmaProtocolLibh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* define */

#define SMA_STOP_CHAR   0x3             /* GDB RSP default value */
#define SMA_BUF_SIZE    600             /* Default SMA buffer size */

#ifndef _ASMLANGUAGE

/* typedef */

/* SMA protocol breakpoint type */

typedef enum sma_bp_type
    {
    SMA_SOFT_BP,		/* software breakpoint */
    SMA_HW_INST_BP,		/* hardware instruction breakpoint */
    SMA_HW_DATA_WRITE_BP,	/* write watchpoint */
    SMA_HW_DATA_READ_BP,	/* read watchpoint */
    SMA_HW_DATA_ACCESS_BP,	/* access watchpoint */
    SMA_UNKNOWN_BP_TYPE	= -1	/* unknown breakpoint type */
    } SMA_BP_TYPE;

typedef enum sma_error_code
    {
    SMA_ERROR_BP_LIST_FULL = 1,		/* Reach max number of Hard&Soft BPs */
    SMA_ERROR_INVALID_BP,		/* No such BP in breakpoints list */
    SMA_ERROR_HW_BP_NOT_SUP,            /* No HW bp support */
    SMA_ERROR_HW_BP_DBG_REGS_FULL,	/* Debug register set full */
    SMA_ERROR_HW_BP_INVALID_ACCESS_TYPE,/* Unsupported type/len combination */
    SMA_ERROR_HW_BP_INVALID_ACCESS_SIZE /* Unsupported type/len combination */
    } SMA_ERROR_CODE; 

enum sma_signal
    {
    SMA_SIG_NULL = -1,
    SMA_SIG_INT = 2,
    SMA_SIG_TRAP = 5,
    SMA_SIG_STOP = 17
    };

/* function declaration */

extern int              smaProtocolParse (unsigned char * ptr);
extern void             smaProtocolPostEvent (void);
extern unsigned char *  smaProtocolGetPacket (unsigned char * buffer,
                                              size_t size);
extern char             smaProtocolBreakCharGet (void);
extern BOOL             smaProtocolHook (char ch);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __INCsmaProtocolLibh */
