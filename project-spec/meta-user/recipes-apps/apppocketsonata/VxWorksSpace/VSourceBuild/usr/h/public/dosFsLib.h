/* dosFsCommon.h - DOS file system header file (common elements) */

/* Copyright 1999-2004, 2009, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,13jan14,ghs  replace error number by POSIX (US29308)
01e,09jan14,ghs  clean up reference (US29308)
01d,18jun09,zly  added macro PRINT_MSG
01c,17aug06,kuo  added macro DOS_CHK_VERB_MASK
01b,02may04,jkf  fixed SPR#83487, DOS_MAX_DIR_LEVELS to 124
01a,09apr04,dat  written (from dosFsLib.h ver 01q)
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
#define DOS_FS_COMPAT       /* enable definition for backwards compatibility */

/* dosDevCreateOptions - check disk levels */

#define DOS_CHK_FLAGS_MASK  0x000000ff /* all "control" flags in here */
#define DOS_CHK_ONLY        0x00000001
#define DOS_CHK_REPAIR      0x00000002
#define DOS_CHK_NONE        0x00000004
#define DOS_CHK_FORCE       0x00000008 /* force chkdsk even if clean */
#define DOS_CHK_VERB_0      0x0000ff00 /* verbosity level/flags */
#define DOS_CHK_VERB_SILENT DOS_CHK_VERB_0
#define DOS_CHK_VERB_1      0x00000100
#define DOS_CHK_VERB_2      0x00000200
#define DOS_CHK_VERB_MASK   0x0000ff00

/* misc max definitions */
#define DOS_MAX_DIR_LEVELS  124     /* max expected directory levels */
#define DOS_VOL_LABEL_LEN   11      /* length of volume label */

/* ioctl FIOCHKDSK - check disk levels */

#define CHK_ONLY    1
#define CHK_REPAIR  2

/* additional open() flags */

#define DOS_O_CONTIG_CHK    0x10000 /* check file for contiguity */
#define DOS_O_CASENS        0x20000 /* case-sensitive file lookup */

/* File attribute byte values */

#define DOS_ATTR_RDONLY         0x01            /* read-only file */
#define DOS_ATTR_HIDDEN         0x02            /* hidden file */
#define DOS_ATTR_SYSTEM         0x04            /* system file */
#define DOS_ATTR_VOL_LABEL      0x08            /* volume label (not a file) */
#define DOS_ATTR_DIRECTORY      0x10            /* entry is a sub-directory */
#define DOS_ATTR_ARCHIVE        0x20            /* file subject to archiving */

/* error codes */

#define S_dosFsLib_32BIT_OVERFLOW           (EOVERFLOW)
#define S_dosFsLib_DISK_FULL                (ENOSPC)
#define S_dosFsLib_FILE_NOT_FOUND           (ENOENT)
#define S_dosFsLib_NO_FREE_FILE_DESCRIPTORS (ENFILE)
#define S_dosFsLib_NOT_FILE                 (EISDIR)
#define S_dosFsLib_NOT_SAME_VOLUME          (ENXIO)
#define S_dosFsLib_NOT_DIRECTORY            (ENOTDIR)
#define S_dosFsLib_DIR_NOT_EMPTY            (ENOTEMPTY)
#define S_dosFsLib_FILE_EXISTS              (EEXIST)
#define S_dosFsLib_INVALID_PARAMETER        (EINVAL)
#define S_dosFsLib_NAME_TOO_LONG            (ENAMETOOLONG)
#define S_dosFsLib_UNSUPPORTED              (ENOTSUP)
#define S_dosFsLib_VOLUME_NOT_AVAILABLE     (ENXIO)
#define S_dosFsLib_INVALID_NUMBER_OF_BYTES  (ENOTSUP)
#define S_dosFsLib_ILLEGAL_NAME             (EINVAL)
#define S_dosFsLib_CANT_DEL_ROOT            (ENOTSUP)
#define S_dosFsLib_READ_ONLY                (EROFS)
#define S_dosFsLib_ROOT_DIR_FULL            (ENOSPC)
#define S_dosFsLib_NO_LABEL                 (ENOENT)
#define S_dosFsLib_NO_CONTIG_SPACE          (ENOSPC)
#define S_dosFsLib_FD_OBSOLETE              (ENOENT)
#define S_dosFsLib_DELETED                  (ENOENT)
#define S_dosFsLib_INTERNAL_ERROR           (EIO)
#define S_dosFsLib_WRITE_ONLY               (EACCES)
#define S_dosFsLib_ILLEGAL_PATH             (ENOENT)
#define S_dosFsLib_ACCESS_BEYOND_EOF        (EINVAL)
#define S_dosFsLib_DIR_READ_ONLY            (EROFS)
#define S_dosFsLib_UNKNOWN_VOLUME_FORMAT    (EIO)
#define S_dosFsLib_ILLEGAL_CLUSTER_NUMBER   (EINVAL)

/* macros */

/* typedefs */

/* interface functions prototypes */

#ifdef __cplusplus
    }
#endif

#endif /* __INCdosFsCommonh */
