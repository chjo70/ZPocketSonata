/* xdr_nfs2.h - rpcgen generated XDR header file for NFS v2 */

/*
 * Copyright 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,07sep06,mwv  update include paths
01a,07apr06,pcm  modified to work with GNU C++ compiler (SPR 115541)
*/

#ifndef _XDR_NFS2_H_RPCGEN
#define	_XDR_NFS2_H_RPCGEN

#include <rpc/rpc.h>
#include <nfs/xdr_nfs_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	NFS2_FHSIZE 32
#define	NFS_COOKIESIZE 4
#define	NFS_FIFO_DEV -1
#define	NFSMODE_FMT 0170000
#define	NFSMODE_DIR 0040000
#define	NFSMODE_CHR 0020000
#define	NFSMODE_BLK 0060000
#define	NFSMODE_REG 0100000
#define	NFSMODE_LNK 0120000
#define	NFSMODE_SOCK 0140000
#define	NFSMODE_FIFO 0010000

enum ftype {
	NFNON = 0,
	NFREG = 1,
	NFDIR = 2,
	NFBLK = 3,
	NFCHR = 4,
	NFLNK = 5,
	NFSOCK = 6,
	NFBAD = 7,
	NFFIFO = 8
};
typedef enum ftype ftype;

typedef struct
    {
    INT32   volumeId;        /* Volume identifier of the File System */
    UINT32  fsId;            /* Inode of the exported directory */
    UINT32  inode;           /* Inode of the file as returned from stat */
    UINT32  cookie;
    } NFS_FILE_HANDLE; 

union u_nfs_fh2
    {
    char   fh[NFS2_FHSIZE];
    NFS_FILE_HANDLE hdl;
    };

typedef union u_nfs_fh2 nfs_fh2;

union u_nfscookie
    { 
    char  cookie[NFS_COOKIESIZE];
    int   value;
    };
    
typedef union u_nfscookie nfscookie;

struct nfstime {
	u_int seconds;
	u_int useconds;
};
typedef struct nfstime nfstime;

struct fattr {
	ftype type;
	u_int mode;
	u_int nlink;
	u_int uid;
	u_int gid;
	u_int size;
	u_int blocksize;
	u_int rdev;
	u_int blocks;
	u_int fsid;
	u_int fileid;
	nfstime atime;
	nfstime mtime;
	nfstime ctime;
};
typedef struct fattr fattr;

struct sattr {
	u_int mode;
	u_int uid;
	u_int gid;
	u_int size;
	nfstime atime;
	nfstime mtime;
};
typedef struct sattr sattr;

struct attrstat {
	nfsstat status;
	fattr attributes;
};
typedef struct attrstat attrstat;

struct diropargs {
	nfs_fh2 dir;
	filename name;
};
typedef struct diropargs diropargs;

struct diropokres {
	nfs_fh2 file;
	fattr attributes;
};
typedef struct diropokres diropokres;

struct diropres {
	nfsstat status;
	diropokres dirop;
};
typedef struct diropres diropres;

struct sattrargs {
	nfs_fh2 file;
	sattr attributes;
};
typedef struct sattrargs sattrargs;

struct readlinkres {
	nfsstat status;
	nfspath data;
};
typedef struct readlinkres readlinkres;

struct readargs {
	nfs_fh2 file;
	u_int offset;
	u_int count;
	u_int totalcount;
};
typedef struct readargs readargs;

typedef struct {
	u_int data_len;
	char *data_val;
} nfsdata;

struct readokres {
	fattr attributes;
	nfsdata data;
};
typedef struct readokres readokres;

struct readres {
	nfsstat status;
	readokres readop;
};
typedef struct readres readres;

struct writeargs {
	nfs_fh2 file;
	u_int beginoffset;
	u_int offset;
	u_int totalcount;
	nfsdata data;
};
typedef struct writeargs writeargs;

struct createargs {
	diropargs where;
	sattr attributes;
};
typedef struct createargs createargs;

struct renameargs {
	diropargs from;
	diropargs to;
};
typedef struct renameargs renameargs;

struct linkargs {
	nfs_fh2 from;
	diropargs to;
};
typedef struct linkargs linkargs;

struct symlinkargs {
	diropargs from;
	nfspath to;
	sattr attributes;
};
typedef struct symlinkargs symlinkargs;

struct readdirargs {
	nfs_fh2 dir;
	nfscookie cookie;
	u_int count;
};
typedef struct readdirargs readdirargs;

struct entry {
	u_int fileid;
	filename name;
	nfscookie cookie;
	struct entry *nextentry;
};
typedef struct entry entry;

struct dirlist {
	entry *entries;
	bool_t eof;
};
typedef struct dirlist dirlist;

struct readdirres {
	nfsstat status;
	dirlist reply;
};
typedef struct readdirres readdirres;

struct statfsokres {
	u_int tsize;
	u_int bsize;
	u_int blocks;
	u_int bfree;
	u_int bavail;
};
typedef struct statfsokres statfsokres;

struct statfsres {
	nfsstat status;
	statfsokres reply;
};
typedef struct statfsres statfsres;

#define	NFS_V2	2
#define	NFSPROC_NULL	0
#define	NFSPROC_GETATTR	1
#define	NFSPROC_SETATTR	2
#define	NFSPROC_ROOT	3
#define	NFSPROC_LOOKUP	4
#define	NFSPROC_READLINK	5
#define	NFSPROC_READ	6
#define	NFSPROC_WRITECACHE	7
#define	NFSPROC_WRITE	8
#define	NFSPROC_CREATE	9
#define	NFSPROC_REMOVE	10
#define	NFSPROC_RENAME	11
#define	NFSPROC_LINK	12
#define	NFSPROC_SYMLINK	13
#define	NFSPROC_MKDIR	14
#define	NFSPROC_RMDIR	15
#define	NFSPROC_READDIR	16
#define	NFSPROC_STATFS	17

#if defined(__STDC__) || defined(__cplusplus)

extern  void * nfsproc_null_2(void);
extern  attrstat * nfsproc_getattr_2(nfs_fh2 *);
extern  attrstat * nfsproc_setattr_2(sattrargs *);
extern  void * nfsproc_root_2(void);
extern  diropres * nfsproc_lookup_2(diropargs *);
extern  readlinkres * nfsproc_readlink_2(nfs_fh2 *);
extern  readres * nfsproc_read_2(readargs *);
extern  void * nfsproc_writecache_2(void);
extern  attrstat * nfsproc_write_2(writeargs *);
extern  diropres * nfsproc_create_2(createargs *);
extern  nfsstat * nfsproc_remove_2(diropargs *);
extern  nfsstat * nfsproc_rename_2(renameargs *);
extern  nfsstat * nfsproc_link_2(void);
extern  nfsstat * nfsproc_symlink_2(void);
extern  diropres * nfsproc_mkdir_2(createargs *);
extern  nfsstat * nfsproc_rmdir_2(diropargs *);
extern  readdirres * nfsproc_readdir_2(readdirargs *);
extern  statfsres * nfsproc_statfs_2(nfs_fh2 *);
extern int nfs_program_2_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* __STDC__ */

extern  void * nfsproc_null_2();
extern  attrstat * nfsproc_getattr_2();
extern  attrstat * nfsproc_setattr_2();
extern  void * nfsproc_root_2();
extern  diropres * nfsproc_lookup_2();
extern  readlinkres * nfsproc_readlink_2();
extern  readres * nfsproc_read_2();
extern  void * nfsproc_writecache_2();
extern  attrstat * nfsproc_write_2();
extern  diropres * nfsproc_create_2();
extern  nfsstat * nfsproc_remove_2();
extern  nfsstat * nfsproc_rename_2();
extern  nfsstat * nfsproc_link_2();
extern  nfsstat * nfsproc_symlink_2();
extern  diropres * nfsproc_mkdir_2();
extern  nfsstat * nfsproc_rmdir_2();
extern  readdirres * nfsproc_readdir_2();
extern  statfsres * nfsproc_statfs_2();
extern int nfs_program_2_freeresult();

#endif /* __STDC__ */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_ftype (XDR *, ftype*);
extern  bool_t xdr_nfs_fh2 (XDR *, caddr_t);
extern  bool_t xdr_nfscookie (XDR *, caddr_t);
extern  bool_t xdr_nfstime (XDR *, nfstime*);
extern  bool_t xdr_fattr (XDR *, fattr*);
extern  bool_t xdr_sattr (XDR *, sattr*);
extern  bool_t xdr_attrstat (XDR *, attrstat*);
extern  bool_t xdr_diropargs (XDR *, diropargs*);
extern  bool_t xdr_diropokres (XDR *, diropokres*);
extern  bool_t xdr_diropres (XDR *, diropres*);
extern  bool_t xdr_sattrargs (XDR *, sattrargs*);
extern  bool_t xdr_readlinkres (XDR *, readlinkres*);
extern  bool_t xdr_readargs (XDR *, readargs*);
extern  bool_t xdr_data (XDR *, nfsdata*);
extern  bool_t xdr_readokres (XDR *, readokres*);
extern  bool_t xdr_readres (XDR *, readres*);
extern  bool_t xdr_writeargs (XDR *, writeargs*);
extern  bool_t xdr_createargs (XDR *, createargs*);
extern  bool_t xdr_renameargs (XDR *, renameargs*);
extern  bool_t xdr_linkargs (XDR *, linkargs*);
extern  bool_t xdr_symlinkargs (XDR *, symlinkargs*);
extern  bool_t xdr_readdirargs (XDR *, readdirargs*);
extern  bool_t xdr_entry (XDR *, entry*);
extern  bool_t xdr_dirlist (XDR *, dirlist*);
extern  bool_t xdr_readdirres (XDR *, readdirres*);
extern  bool_t xdr_statfsokres (XDR *, statfsokres*);
extern  bool_t xdr_statfsres (XDR *, statfsres*);

#else /* __STDC__ */

/* the xdr functions */
extern bool_t xdr_ftype();
extern bool_t xdr_nfs_fh2();
extern bool_t xdr_nfscookie();
extern bool_t xdr_nfstime();
extern bool_t xdr_fattr();
extern bool_t xdr_sattr();
extern bool_t xdr_attrstat();
extern bool_t xdr_diropargs();
extern bool_t xdr_diropokres();
extern bool_t xdr_diropres();
extern bool_t xdr_sattrargs();
extern bool_t xdr_readlinkres();
extern bool_t xdr_readargs();
extern bool_t xdr_data();
extern bool_t xdr_readokres();
extern bool_t xdr_readres();
extern bool_t xdr_writeargs();
extern bool_t xdr_createargs();
extern bool_t xdr_renameargs();
extern bool_t xdr_linkargs();
extern bool_t xdr_symlinkargs();
extern bool_t xdr_readdirargs();
extern bool_t xdr_entry();
extern bool_t xdr_dirlist();
extern bool_t xdr_readdirres();
extern bool_t xdr_statfsokres();
extern bool_t xdr_statfsres();

#endif /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* !_XDR_NFS2_H_RPCGEN */
