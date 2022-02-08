/* nfs3HashP.h - private nfs hash  header file */

/*
 * Copyright (c) 1998, 2003, 2006-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
-------------------- 
01f,28may10,zly  fix WIND00204302 - Add fhDelete() function to delete entry 
                 from hash table while remove a file. 
01e,29apr10,pad  Moved extern C statement after include statements.
01d,01mar10,y_t    update for LP64
01c,07mwv06,mwv  update include paths
01b,28aug03,snd  Modifications for NFSv3
01a,15nov98,rjc  created.
*/

#ifndef __INCnfsHashPh
#define __INCnfsHashPh

#include <nfs/nfsdCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)

extern void nfsHashTableShow(int, int);
extern void nfsdHashTableParamsSet(int, int, char *);
extern void nfsHashTblSet (char *, int, int );
extern void nfsHashTblUnset (char *, int);
extern STATUS nfsFhLkup (NFS_FILE_HANDLE * ,  char *);
extern int nfsNmLkupIns (int, char *);
extern STATUS nfsStatusGet(void *, int);
extern int fhDelete (NFS_FILE_HANDLE *dir, char *pName); /*Deletes entry from hashtable*/
\

#else	/* __STDC__ */

extern void nfsHashTblSet ();
extern void nfsHashTblUnset ();
extern STATUS nfsFhLkup ();
extern int nfsNmLkupIns ();
extern int fhDelete (); /*Deletes entry from hashtable*/

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnfsHashPh */
