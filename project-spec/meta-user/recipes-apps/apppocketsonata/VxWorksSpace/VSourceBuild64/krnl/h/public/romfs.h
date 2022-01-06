/* 
 * Copyright (c) 2015 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*-
 * Copyright (c) 1997 Berkeley Software Design, Inc.
 *
 * The Berkeley Software Design Inc. software License Agreement specifies
 * the terms and conditions for redistribution.
 *
 *	BSDI $Id: romfs.h,v 2.5 2001/10/30 17:09:27 polk Exp $
 */

/*
modification history
--------------------
13may15,txu  fix V7STO-358 : wrong include after extern "C"
*/

#ifndef __INCromfsh
#define __INCromfsh


#ifdef    __cplusplus
extern "C" {
#endif

#define	RF_MAGIC	"RFS1"
/*
 * Round x to a 4 byte boundry
 */
#define	LWROUND(x)	(((x) + 3) & ~3)

/*
 * The rftime_t structure is a fixed size timespec structure
 * Since it is used in an on-disk layout we cannot allow it to change
 * size if a time_t or long have a size other than 32 bits.
 */
typedef struct {
	u_int32_t	tv_sec;		/* Seconds since 00:00 1/1/1970 */
	u_int32_t	tv_nsec;	/* nanoseconds */
} rftime_t;

/*
 * Each file is preceeded by an rfnode_t structure.
 * The next rfnode_t structure is located at RFNEXTNODE(&rfn)
 * Nodes are always stored on 4 byte boundries
 * All meta data on disk is stored in network byte order (big endian)
 */
typedef struct rfnode_t {
	u_int32_t	rf_size;	/* size of file */
	u_int16_t	rf_mode;
	int16_t		rf_nlink;
	rftime_t	rf_ctime;
	u_int32_t	rf_flags;
	u_int32_t	rf_uid;
	u_int32_t	rf_gid;
	u_int32_t	rf_rdev;
	u_int32_t	rf_space;	/* space allocated for file */

	/*
	 * The entries below are not stored in the filesystem.
	 * but are computed when the rfnode_t block is read
	 */
	u_int32_t	rf_offset;	/* Offset into device */
	u_int32_t	rf_seekp;	/* Our current seek pointer */
#if	defined(KERNEL) && !defined(STANDALONE)
        struct lock	rf_lock;	/* node lock */
	dev_t		rf_dev;		/* Device where inode resides */
	struct vnode	*rf_vnode;	/* Back pointer to the vnode */
	struct vnode	*rf_devvp;	/* Back pointer to the device vnode */
	struct rfnode_t	*rf_next;
	struct rfnode_t	**rf_prev;
#endif
} rfnode_t;

#define VTOI(vp) ((struct rfnode_t *)(vp)->v_data)
#define ITOV(ip) ((ip)->rf_vnode)

#if _BYTE_ORDER == _BIG_ENDIAN

#define ntohl(x)        (x)
#define ntohs(x)        (x)
#define htonl(x)        (x)
#define htons(x)        (x)

#else

#define ntohl(x)        ((((x) & 0x000000ff) << 24) |   \
                         (((x) & 0x0000ff00) <<  8) |   \
                         (((x) & 0x00ff0000) >>  8) |   \
                         (((x) & 0xff000000) >> 24))

#define htonl(x)        ((((x) & 0x000000ff) << 24) |   \
                         (((x) & 0x0000ff00) <<  8) |   \
                         (((x) & 0x00ff0000) >>  8) |   \
                         (((x) & 0xff000000) >> 24))

#define ntohs(x)        ((((x) & 0x00ff) << 8) |    \
                         (((x) & 0xff00) >> 8))

#define htons(x)        ((((x) & 0x00ff) << 8) |    \
                         (((x) & 0xff00) >> 8))

#endif /* _BYTE_ORDER */

#define	RFNODESZ ((char *)(&(((rfnode_t *)0)->rf_offset)) - (char *)0)

/*
 * Given a pointer to an rfnode_t read from the filesystem, return a pointer
 * to the next file
 */
#define RFNEXTNODE(rfp)	((rfp)->rf_offset + RFNODESZ + (rfp)->rf_space)

/*
 * Names are up to 255 bytes long
 * The actual structure is truncated to the lowest long word boundry which
 * allows the entire name to be stored.
 * rd_offset is stored in network byte order (big endian)
 */
typedef struct {
	u_int32_t	rd_offset;	/* "inode" number of entry */
	u_char		rd_type;	/* file type from <sys/dirent.h> */
	u_char		rd_namelen;	/* length of string in rd_name */
	char		rd_name[255];	/* name of entry */
} rfdir_t;

#define	RFDIRHDR	(((rfdir_t *)0)->rd_name - (char *)0)

/*
 * Given a pointer to an rfdir_t entry return the offset of the next rfdir_t
 * entry.  In the current director.  Note that an offset of 0 implies the
 * end of the directory and all other fields are invalid.
 */
#define	RFDIRSZ(n) LWROUND(((char *)(&(((rfdir_t *)0)->rd_name[strlen(n)])) - (char *)0))
#define	RFNDIRSZ(n) LWROUND(((char *)(&(((rfdir_t *)0)->rd_name[n])) - (char *)0))
#define RFNEXTDIR(rfp, rdp)	LWROUND((rfp)->rf_offset + (rdp)->rd_offset)

struct open_file {
        void            *f_devdata;     /* device specific data */
        void            *f_fsdata;      /* file system specific data */
};

#if defined(STANDALONE) || defined(ROMFS_PROTOTYPES)
int rfs_open __P((char *, struct open_file *));
int rfs_read __P((struct open_file *, char *, u_int, u_int *));
off_t rfs_seek __P((struct open_file *, off_t, int));
#ifndef SMALL
int rfs_close __P((struct open_file *));
int rfs_write __P((struct open_file *, char *, u_int, u_int *));
int rfs_stat __P((struct open_file *, struct stat *));
int rfs_ls __P((struct open_file *));
#endif
int rfsread __P((struct open_file *, u_int, char *, u_int *));
#endif
void romfs_ntoh __P((rfnode_t *));


#ifdef __cplusplus
}
#endif

#endif /*  __INCromfsh   */
