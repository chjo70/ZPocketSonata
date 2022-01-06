/* coreDumpLib.h - core dump interface header */

/*
 * Copyright (c) 2005-2010,2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
 
/*
modification history
--------------------
13apr16,jmp  Added core dump module hook support (US76633).
31mar16,jmp  Added core dump copy hook facility (US76630).
07jul15,jmp  Added Minimal Kernel Core Dump support (US61148).
20may15,jmp  Added SysModel string to kernel core dump information (US58770).
30apr15,rlp  Added Kernel image signature support (US57214).
31mar15,jmp  Added binaryDesc field to CORE_DUMP_INFO to provide information
             on running VxWorks image (Version - Creation date).
24dec14,jmp  Added posix signal information to core dump facility (V7COR-2400).
23dec14,jmp  Added numCores to CORE_DUMP_INFO.
29apr10,pad  Moved extern C statement after include statements.
19nov09,jmp  LP64 code adaptation.
18jun08,jmp  added coreDumpLibCommon.h inclusion.
             moved errnos to coreDumpLibCommon.h.
14apr08,jmp  added CORE_DUMP_API_VERSION.
21feb08,jmp  added Core Dump Progress Hook facility (REQ CQ:WIND00105547).
30jan08,jmp  added coreDumpOptions[Set|Get]() (REQ CQ:WIND00105548).
20sep07,jmp  added EDR string to CORE_DUMP_INFO (CQ:WIND00104805).
13dec06,jmp  added new errnos.
             added coreDumpDevInfoGet() prototype, and CORE_DUMP_DEV_INFO
             structure.
11jul06,dbt  Fixed CORE_DUMP_INFO fields description.
08dec05,jmp  added core dump checksum status to CORE_DUMP_INFO structure.
             fixed macro conflict (SPR #115895).
09sep05,jmp  updated core dump types.
02sep05,jmp  renamed coreDumpFormat() into coreDumpDevFormat().
             added S_coreDumpLib_CORE_DUMP_FILTER_NOT_FOUND.
22aug05,dbt  Added coreDumpOpen() & coreDumpClose() prototypes. Updated
             coreDumpRead() prototype.
11aug05,dbt  Added valid & errnoVal fields in CORE_DUMP_INFO structure.
             Added device size in CORE_DUMP_RAW_DEV_DESC structure.
             Added coreDumpDevShow() prototype.
11aug05,dbt  Added coreDumpUsrGenerate() & coreDumpMemDump() prototypes;
             removed coreDumpGenerate().
05aug05,jmp  added CORE_DUMP_RAW_DEV, moved some definitions to 
             private/coreDumpLibP.h.
04aug05,jmp  added more errnos.
03aug05,dbt  Added errnos & additional APIs.
29jul05,jmp  added core dump memory filtering.
18jul05,jmp  updated CORE_DUMP_INFO structure.
29jun05,jmp  splited & cleanup.
22mar05,jmp  written.
*/

#ifndef __INCcoreDumpLibh
#define __INCcoreDumpLibh

/* includes */

#include <time.h>
#ifndef HOST
#include <taskLib.h>
#include <rtpLib.h>
#include <regs.h>
#include <excLib.h>
#include <vwModNum.h>
#include <coreDumpLibCommon.h>
#endif	/* !HOST */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* core dump info macros */

#define MAX_CORE_DUMP_LEN	100	/* max len for core dump basename */
#define MAX_CORE_DUMP_TASK_LEN	256	/* max length for task name */
#define MAX_CORE_DUMP_RTP_LEN	256	/* max length for RTP name */
#define CORE_DUMP_TYPE_LEN	30	/* max length for core dump type name */
#define MAX_CORE_DUMP_INFO_LEN	160	/* max length for core dump info str */
#define MAX_CORE_DUMP_DESC_LEN  256     /* max len for description string */
#define MAX_CORE_DUMP_VXVER_LEN 64	/* max len for VxWorksVersion string */
#define MAX_CORE_DUMP_DATE_LEN 64	/* max len for creationDate string */
#define MAX_CORE_DUMP_SYS_MODEL_LEN 160 /* max len for sysModel string */
                                           

/*
 * The following Core Dump API version allow to identify which set of core
 * Dump APIs must be used. It can be used to write conditional code that could
 * work on different VxWorks versions.
 */

#define CORE_DUMP_API_VERSION 2		/* Version 2 of Core Dump APIs */

/* typedefs */

/* core dump types */

typedef enum                    /* Core Dump Type */
    {
    CORE_DUMP_USER,             /* 0: user coredump (on-demand) */
    CORE_DUMP_KERNEL_INIT,      /* 1: fatal error during kernel intialization */
    CORE_DUMP_INTERRUPT,        /* 2: Obsolete / Kept for backward compat */
    CORE_DUMP_KERNEL_PANIC,     /* 3: Obsolete / Kept for backward compat */
    CORE_DUMP_KERNEL_TASK,      /* 4: kernel task error */
    CORE_DUMP_RTP,              /* 5: process coredump */
    CORE_DUMP_KERNEL            /* 6: VxWorks kernel error */
    } CORE_DUMP_TYPE;

/* core dump status */

typedef enum                    /* Core Dump Checksum Status */
    {
    CORE_DUMP_NO_CKSUM,         /* 0: No cksum available (N/A) */
    CORE_DUMP_CKSUM_OK,         /* 1: Core dump checksum status OK */
    CORE_DUMP_CKSUM_ERROR       /* 2: Core dump checksum status ERROR */
    } CORE_DUMP_CKSUM_STATUS;

/* core dump options */

typedef enum                    /* Core Dump Options */
    {
    CORE_DUMP_AUTO_REBOOT = 0x0001	/* Automatic reboot after core dump */
					/* generation */
    } CORE_DUMP_OPTIONS;

typedef enum
    {
    CORE_DUMP_PROGRESS_START,		/* 0: Start progress report */
    CORE_DUMP_PROGRESS_RUN,		/* 1: Run progress report */
    CORE_DUMP_PROGRESS_END		/* 2: End progress report */
    } CORE_DUMP_PROGRESS_HOOK_TYPE;

typedef void (*CORE_DUMP_PROGRESS_HOOK_RTN) (CORE_DUMP_PROGRESS_HOOK_TYPE type);

typedef struct core_dump_desc *	CORE_DUMP_ID;	/* core dump descriptor */

typedef struct core_dump_info            /* core dump information */
    {
    UINT32                 coreDumpIndex;/* core dump index */
    BOOL                   valid;        /* core dump validity */
    UINT32                 errnoVal;     /* core dump errno */
    char                   name[MAX_CORE_DUMP_LEN];
                                         /* name of the core dump */
    size_t                 size;         /* size of the core dump */
    CORE_DUMP_TYPE         type;         /* origin of the core dump */
    TASK_ID                taskId;       /* task Id (kernel core dump) */
    char                   taskName[MAX_CORE_DUMP_TASK_LEN];
                                         /* name of task */
    RTP_ID                 rtpId;        /* process Id (process core  dump) */
    char                   rtpName[MAX_CORE_DUMP_RTP_LEN];
                                         /* path to RTP */
    int                    excNum;       /* exception number (Not valid for */
                                         /* on-demand &  Panic core dumps) */
    ULONG		   pc;           /* exception program counter */
    ULONG		   sp;           /* exception stack pointer */
    ULONG		   fp;           /* exception frame pointer */
    time_t                 time;         /* generation calendar time */
    ULONG		   ticks;        /* VxWorks time stamp */
    CORE_DUMP_CKSUM_STATUS cksumStatus;  /* core dump checksum status */
    char		   infoString[MAX_CORE_DUMP_INFO_LEN];
					 /* information string */
    BOOL		   excIsValid;	 /* Indicate validity of exception */
					 /* information (excNum, pc, sp, fp) */
    int                    numCores;     /* Number of configured cores */
    int                    signalNum;    /* POSIX signal number */
    int                    signalSubcode;/* POSIX "si_code" */
    char                   binaryDesc[MAX_CORE_DUMP_DESC_LEN];
                                         /* Binary description string. Used */
                                         /* for kernel core dump to report */
                                         /* VxWorks image information */
    char                   vxVersion[MAX_CORE_DUMP_VXVER_LEN];
					 /* VxWorks version string */
    char                   creationDate[MAX_CORE_DUMP_DATE_LEN];
					 /* Kernel image creation date */
    char                   sysModel[MAX_CORE_DUMP_SYS_MODEL_LEN];
    } CORE_DUMP_INFO;

typedef struct core_dump_task_dump_info   /* information for task dump */
    {
    ssize_t maxStackSize;       /* Maximum size of stack to dump: */
                                /* 0 = dump nothing */
                                /* -1 = dump everything from sp to stack top */
                                /* <n> = dump <n> bytes from sp */
    } CORE_DUMP_TASK_DUMP_INFO;

typedef struct core_dump_raw_dev_desc   /* coredump raw device descriptor */
    {
    UINT32	devWrtBlkSize;		/* device write block size */
    void *	deviceId;		/* device ID used for various rtns */
    size_t	size;			/* device size */
    char *	pDevWrtBlkCache;	/* device write cache buffer */
    FUNCPTR	pDevEraseRtn;		/* device erase() routine */
    FUNCPTR	pDevWriteRtn;		/* device write() routine */
    FUNCPTR	pDevReadRtn;		/* device read() routine */
    FUNCPTR	pDevFlushRtn;		/* device flush() routine */
    } CORE_DUMP_RAW_DEV_DESC;

typedef struct core_dump_dev_info	/* coredump device information */
    {
    BOOL	initialized;		/* Is core dump device initialized ? */
    BOOL	formatted;		/* Is device formatted ? */
    size_t	size;			/* total device size */
    size_t	free;			/* remaining device size */
    UINT32	coreDumpMax;		/* maximun core dump on device */
    } CORE_DUMP_DEVICE_INFO;

/* externals */

#ifndef HOST
extern STATUS	coreDumpDevFormat	(UINT32 coreDumpMax);
extern BOOL	coreDumpIsAvailable	(void);
extern STATUS	coreDumpNextGet		(UINT32 currentIx,
					 UINT32 * pNextIx);
extern CORE_DUMP_INFO * coreDumpInfoGet (UINT32 coreDumpIndex);
extern CORE_DUMP_DEVICE_INFO * coreDumpDevInfoGet (void);
extern CORE_DUMP_ID	coreDumpOpen	(UINT32 coreDumpIx);
extern STATUS	coreDumpClose		(CORE_DUMP_ID coreDumpId);
extern ssize_t	coreDumpRead		(CORE_DUMP_ID coreDumpId,
					 void * buffer, size_t size);
extern STATUS   coreDumpCopy            (UINT32 coreDumpIndex, char * destPath);
extern STATUS   coreDumpCopyHookAdd     (FUNCPTR copyHook);
extern STATUS   coreDumpCopyHookDelete  (FUNCPTR copyHook);
extern STATUS   coreDumpShowInit        (void);
extern STATUS   coreDumpShow            (UINT32 coreDumpIndex, UINT32 level);
extern STATUS   coreDumpDevShow		(void);
extern STATUS	coreDumpMemFilterAdd	(void * addr, size_t size);
extern STATUS	coreDumpMemFilterDelete	(void * addr, size_t size);
extern STATUS	coreDumpCreateHookAdd	(FUNCPTR createHook);
extern STATUS	coreDumpCreateHookDelete(FUNCPTR createHook);
extern STATUS	coreDumpUsrGenerate	(void);
extern STATUS	coreDumpMemDump		(void * src, size_t size, void * dest);
extern char *	coreDumpTypeStrGet	(char typeStr[CORE_DUMP_TYPE_LEN],
					 CORE_DUMP_TYPE coreDumpType);
extern STATUS	coreDumpOptionsSet	(CORE_DUMP_OPTIONS unsetMask,
					 CORE_DUMP_OPTIONS setMask);
extern STATUS	coreDumpOptionsGet	(CORE_DUMP_OPTIONS * pOptions);
extern STATUS	coreDumpProgressHookAdd	(CORE_DUMP_PROGRESS_HOOK_RTN
					 progressHook, size_t callFreq);
extern STATUS	coreDumpProgressHookDelete (CORE_DUMP_PROGRESS_HOOK_RTN
					 progressHook);
extern STATUS   coreDumpTaskDumpHookAdd (BOOL (*routine)(
                                            TASK_ID taskId,
                                            void *  pArg,
                                            CORE_DUMP_TASK_DUMP_INFO * pInfo),
                                         void * pArg);
extern STATUS   coreDumpTaskDumpHookDelete (BOOL (*routine)(
                                            TASK_ID taskId,
                                            void *  pArg,
                                            CORE_DUMP_TASK_DUMP_INFO * pInfo));
extern STATUS   coreDumpModuleDumpHookAdd (BOOL (*routine)(
                                                void * moduleId,
                                                char * moduleName,
                                                void * pArg),
                                           void * pArg);
extern STATUS   coreDumpModuleDumpHookDelete (BOOL (*routine)(
                                                void * moduleId,
                                                char * moduleName,
                                                void * pArg));
#endif	/* !HOST */

#ifdef __cplusplus
}
#endif

#endif /* __INCcoreDumpLibh */
