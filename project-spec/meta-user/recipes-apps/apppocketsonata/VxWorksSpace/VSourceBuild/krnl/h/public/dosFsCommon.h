/* dosFsCommon.h - DOS file system header file (common elements) */

/* Copyright 1999-2004, 2009, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
29aug14,txu  modify to remove compile warning (US43884)
08jul14,yjl  fix printErrno() not return POSIX error (V7STO-26)
11mar14,ghs  put back error number for compatible
13jan14,ghs  replace error number by POSIX error number (US29308)
18jun09,zly  added macro PRINT_MSG
17aug06,kuo  added macro DOS_CHK_VERB_MASK
02may04,jkf  fixed SPR#83487, DOS_MAX_DIR_LEVELS to 124
09apr04,dat  written (from dosFsLib.h ver 01q)
*/

/*
These are the common DOS file system macros needed for both
kernel and RTP space.  (This file is referenced as usrFsLib.h from
RTP space).
*/

#ifndef __INCdosFsCommonh
#define __INCdosFsCommonh

#ifdef __cplusplus
extern "C" {
#endif


/* defines */
#define	DOS_FS_COMPAT	/* enable definition for backwards compatibility */

/* dosDevCreateOptions - check disk levels */

#define	DOS_CHK_FLAGS_MASK	0x000000ff /* all "control" flags in here */
#define DOS_CHK_ONLY		0x00000001
#define DOS_CHK_REPAIR		0x00000002
#define DOS_CHK_NONE		0x00000004
#define	DOS_CHK_FORCE		0x00000008 /* force chkdsk even if clean */
#define DOS_CHK_VERB_0		0x0000ff00 /* verbosity level/flags */
#define DOS_CHK_VERB_SILENT	DOS_CHK_VERB_0
#define DOS_CHK_VERB_1		0x00000100
#define DOS_CHK_VERB_2		0x00000200
#define DOS_CHK_VERB_MASK       0x0000ff00

/* misc max definitions */
#define DOS_MAX_DIR_LEVELS      124     /* max expected directory levels */
#define DOS_VOL_LABEL_LEN 	11	/* length of volume label */

/* ioctl FIOCHKDSK - check disk levels */

#define CHK_ONLY	1
#define CHK_REPAIR	2

/* additional open() flags */

#define DOS_O_CONTIG_CHK	0x10000	/* check file for contiguity */
#define DOS_O_CASENS		0x20000	/* case-sensitive file lookup */

/* File attribute byte values */

#define DOS_ATTR_RDONLY         0x01            /* read-only file */
#define DOS_ATTR_HIDDEN         0x02            /* hidden file */
#define DOS_ATTR_SYSTEM         0x04            /* system file */
#define DOS_ATTR_VOL_LABEL      0x08            /* volume label (not a file) */
#define DOS_ATTR_DIRECTORY      0x10            /* entry is a sub-directory */
#define DOS_ATTR_ARCHIVE        0x20            /* file subject to archiving */

/* error codes */

#ifdef _WRS_CONFIG_COMPAT69
#define S_dosFsLib_32BIT_OVERFLOW           (EOVERFLOW)       /* NOSTATTBL */
#define S_dosFsLib_DISK_FULL                (ENOSPC)          /* NOSTATTBL */
#define S_dosFsLib_FILE_NOT_FOUND           (ENOENT)          /* NOSTATTBL */
#define S_dosFsLib_NO_FREE_FILE_DESCRIPTORS (ENFILE)          /* NOSTATTBL */
#define S_dosFsLib_NOT_FILE                 (EISDIR)          /* NOSTATTBL */
#define S_dosFsLib_NOT_SAME_VOLUME          (ENXIO)           /* NOSTATTBL */
#define S_dosFsLib_NOT_DIRECTORY            (ENOTDIR)         /* NOSTATTBL */
#define S_dosFsLib_DIR_NOT_EMPTY            (ENOTEMPTY)       /* NOSTATTBL */
#define S_dosFsLib_FILE_EXISTS              (EEXIST)          /* NOSTATTBL */
#define S_dosFsLib_INVALID_PARAMETER        (EINVAL)          /* NOSTATTBL */
#define S_dosFsLib_NAME_TOO_LONG            (ENAMETOOLONG)    /* NOSTATTBL */
#define S_dosFsLib_UNSUPPORTED              (ENOTSUP)         /* NOSTATTBL */
#define S_dosFsLib_VOLUME_NOT_AVAILABLE     (ENXIO)           /* NOSTATTBL */
#define S_dosFsLib_INVALID_NUMBER_OF_BYTES  (ENOTSUP)         /* NOSTATTBL */
#define S_dosFsLib_ILLEGAL_NAME             (EINVAL)          /* NOSTATTBL */
#define S_dosFsLib_CANT_DEL_ROOT            (ENOTSUP)         /* NOSTATTBL */
#define S_dosFsLib_READ_ONLY                (EROFS)           /* NOSTATTBL */
#define S_dosFsLib_ROOT_DIR_FULL            (ENOSPC)          /* NOSTATTBL */
#define S_dosFsLib_NO_LABEL                 (ENOENT)          /* NOSTATTBL */
#define S_dosFsLib_NO_CONTIG_SPACE          (ENOSPC)          /* NOSTATTBL */
#define S_dosFsLib_FD_OBSOLETE              (ENOENT)          /* NOSTATTBL */
#define S_dosFsLib_DELETED                  (ENOENT)          /* NOSTATTBL */
#define S_dosFsLib_INTERNAL_ERROR           (EIO)             /* NOSTATTBL */
#define S_dosFsLib_WRITE_ONLY               (EACCES)          /* NOSTATTBL */
#define S_dosFsLib_ILLEGAL_PATH             (ENOENT)          /* NOSTATTBL */
#define S_dosFsLib_ACCESS_BEYOND_EOF        (EINVAL)          /* NOSTATTBL */
#define S_dosFsLib_DIR_READ_ONLY            (EROFS)           /* NOSTATTBL */
#define S_dosFsLib_UNKNOWN_VOLUME_FORMAT    (EIO)             /* NOSTATTBL */
#define S_dosFsLib_ILLEGAL_CLUSTER_NUMBER   (EINVAL)          /* NOSTATTBL */
#endif /* _WRS_CONFIG_COMPAT69 */

/*
 * user`s printing message level :
 * 0  - print nothing
 * 1  - print message at level-1
 * >1 - for future extension
 */

IMPORT int dosFsMsgLevel;

/*
 *Classification of message
 *By default all message at level-1
 */

#define CLSMSG_NORMAL 1


/*
 * print message according to dosFsMsgLevel (DOSFS_PRTMSG_LEVEL)
 * class : default value is CLSMSG_NORMAL
 */

#define PRINT_MSG(class, fmt, ...)                  \
    do {                                            \
        if ((dosFsMsgLevel) != 0) {                   \
            if ((dosFsMsgLevel) <= (class)) {         \
                    (void)printf((fmt),##__VA_ARGS__);    \
            }                                       \
        }                                           \
    } while (0)

/* macros */

/* typedefs */

/* interface functions prototypes */

#ifdef __cplusplus
    }
#endif

#endif /* __INCdosFsCommonh */
