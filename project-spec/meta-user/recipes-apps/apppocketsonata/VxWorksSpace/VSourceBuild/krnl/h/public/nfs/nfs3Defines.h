/* nfs3Defines.h - Network File System version 3 definitions header */

/*
 * Copyright (c) 1995-2006, 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01f,06aug12,txu  Fix WIND00367917: NFS v3 client does not support READDIRPLUS
01e,29apr10,pad  Moved extern C statement after include statements.
01d,20apr06,pcm  made modifications due to xdr_nfs3.h changes
01c,20jan06,md   Added pathconf support
01b,05dec06,pcm  added PA_FILEID
01a,28jun04,dlk  Added modification history. Removed commented-out
                 S_nfsLib_NFS3ERR_* defines, which interfere with makeStatTbl.
*/

#ifndef __INCnfs3Definesh
#define __INCnfs3Definesh

#include "vwModNum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nfsinfo
    {
    uint32 rtmax;
    uint32 rtpref;
    uint32 rtmult;
    uint32 wtmax;
    uint32 wtpref;
    uint32 wtmult;
    uint32 dtpref;
    size3 maxfilesize;
    nfstime3 time_delta;
    uint32 properties;
    } nfsinfo;

struct nfs_pathconf {
	uint32 name_max;
	uint32 linkmax;
	bool_t no_trunc;
	bool_t chown_restricted;
	bool_t case_insensitive;
	bool_t case_preserving;
};

typedef struct nfs_pathconf nfs_pathconf;

#define NFS3_FHSIZE           64
#define NFS3_COOKIEVERFSIZE   8
#define NFS3_CREATEVERFSIZE   8
#define NFS3_WRITEVERFSIZE    8

#define PA_ATTR     attributes
#define PA_TYPE     attributes.type
#define PA_MODE     attributes.mode
#define PA_SIZE     attributes.size
#define PA_UID      attributes.uid
#define PA_GID      attributes.gid
#define PA_ATIME    attributes.atime
#define PA_MTIME    attributes.mtime
#define PA_CTIME    attributes.ctime
#define PA_FILEID   attributes.fileid

#define RLOK_ATTR   READLINK3res_u.resok.symlink_attributes
#define RLOK_PATH   READLINK3res_u.resok.data
#define RLFL_ATTR   READLINK3res_u.resfail.symlink_attributes

#define LUOK_FH         LOOKUP3res_u.resok.object
#define LUOK_OBJATTR    LOOKUP3res_u.resok.obj_attributes
#define LUOK_DIRATTR    LOOKUP3res_u.resok.dir_attributes
#define LUFL_DIRATTR    LOOKUP3res_u.resfail.dir_attributes

#define CTAR_OBJATTR    how.createhow3_u.obj_attributes
#define CTAR_VERF       how.createhow3_u.verf
#define CTOK_FH         CREATE3res_u.resok.obj
#define CTOK_OBJ        CREATE3res_u.resok.obj
#define CTOK_OBJATTR    CREATE3res_u.resok.obj_attributes
#define CTOK_WCC        CREATE3res_u.resok.dir_wcc
#define CTFL_WCC        CREATE3res_u.resfail.dir_wcc

#define REOK_FILEATTR   READ3res_u.resok.file_attributes
#define REOK_COUNT      READ3res_u.resok.count
#define REOK_EOF        READ3res_u.resok.eof
#define REOK_DATA       READ3res_u.resok.data
#define REFL_FILEATTR   READ3res_u.resfail.file_attributes

#define WROK_FILEWCC    WRITE3res_u.resok.file_wcc
#define WROK_COUNT      WRITE3res_u.resok.count
#define WROK_COMMIT     WRITE3res_u.resok.committed
#define WROK_VERF       WRITE3res_u.resok.verf
#define WRFL_FILEWCC    WRITE3res_u.resfail.file_wcc

#define PE_SIZE         attributes.size
#define PE_MTIME        attributes.mtime
#define PE_CTIME        attributes.ctime

#define GAOK_ATTR       resok.obj_attributes

#define SATT_MODE       mode.mode
#define SATT_UID        uid.uid
#define SATT_GID        gid.gid
#define SATT_SIZE       size.size
#define SATT_ATIME      atime.atime
#define SATT_MTIME      atime.mtime

#define RDOK_DIRATTR     READDIR3res_u.resok.dir_attributes
#define RDOK_COOKIEVERF  READDIR3res_u.resok.cookieverf.cookie
#define RDOK_REPLY       READDIR3res_u.resok.reply

#define RDPOK_DIRATTR     READDIRPLUS3res_u.resok.dir_attributes
#define RDPOK_COOKIEVERF  READDIRPLUS3res_u.resok.cookieverf
#define RDPOK_REPLY       READDIRPLUS3res_u.resok.reply

#define FIOK_INFO_OFF    FSINFO3res_u.resok.rtmax

#define PF_FH            handle

#define FH_BUF           data.data_val

#define COPY_FH(pf1, pf2)                                                \
    bcopy ((char *) (pf1)->data.data_val, (char *) (pf2)->data.data_val, \
            (pf1)->data.data_len);                                       \
    (pf2)->data.data_len = (pf1)->data.data_len;

#define ASSIGN_FH(pf1, pf2)                                              \
    bcopy ((char *) pf1, (char *) pf2, sizeof (nfs_fh3));

#ifdef __cplusplus
}
#endif

#endif /* __INCnfs3Definesh */
