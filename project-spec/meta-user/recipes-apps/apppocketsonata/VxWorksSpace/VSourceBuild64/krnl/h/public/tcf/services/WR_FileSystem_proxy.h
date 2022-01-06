/*
 * Copyright (c) 2013-2014,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * TCF service filesystem - proxy version.
 *
 */

#ifndef WR_FILESYSTEM_PROXY_H
#define WR_FILESYSTEM_PROXY_H

#include <tcf/framework/channel.h>
#include <semLib.h>

typedef struct WrFsProxyStat {
    int64_t size;	/* file size in bytes */
    int uid;		/* file owner user ID */
    int gid;		/* file owner group ID */
    int permissions;	/* file access permissions */
    uint64_t atime;	/* file last access time */
    uint64_t mtime;	/* file last modification time */
}WrFsProxyStat;
    
typedef struct FileNode {
    char * file_name;                   /* a directory or file name */
    struct FileNode * next;             /* pointer to next file */
}FileNode;

extern void ini_wr_fsproxy_lib(void);
extern int wr_fsproxy_open(Channel * c, SEM_ID semid, int * posixerrno, const char * file_name, int mode, int perm, char ** fd);
extern int wr_fsproxy_close(Channel * c, SEM_ID semid, int * posixerrno, const char * fd);
extern int wr_fsproxy_read(Channel * c, SEM_ID semid, int * posixerrno, const char * fd, off_t offset, size_t size, char *buf, ssize_t * read_bytes);
extern int wr_fsproxy_write(Channel * c, SEM_ID semid, int * posixerrno, const char * fd, off_t offset, size_t size, char *buf);
extern int wr_fsproxy_remove(Channel * c, SEM_ID semid, int * posixerrno, const char * file_name);
extern int wr_fsproxy_fstat(Channel * c, SEM_ID semid, int * posixerrno, const char * fd, WrFsProxyStat * proxy_stat);
extern int wr_fsproxy_opendir(Channel * c, SEM_ID semid, int * posixerrno, const char * path, char **fd);
extern int wr_fsproxy_readdir(Channel * c, SEM_ID semid, int * posixerrno, char *fd, FileNode ** file_list, FileNode ** last_node, int *oef);
extern int wr_fsproxy_stat(Channel * c, SEM_ID semid, int * posixerrno, const char * path, WrFsProxyStat * proxy_stat);
extern void wr_fsproxy_roots (Channel * chnl, char * token, char * devid, BOOL connect, int version);
extern int wr_fsproxy_mkdir(Channel * c, SEM_ID semid, int * posixerrno, const char * dir_name, int perm);
extern int wr_fsproxy_rmdir(Channel * c, SEM_ID semid, int * posixerrno, const char * dir_name);
extern int wr_fsproxy_rename(Channel * c, SEM_ID semid, int * posixerrno, const char * old_name, const char * new_name);
#endif /* WR_FILESYSTEM_PROXY_H */
