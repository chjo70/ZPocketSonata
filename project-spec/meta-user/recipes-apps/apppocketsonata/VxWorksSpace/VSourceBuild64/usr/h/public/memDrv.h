/* memDrv.h - header file for memDrv.c */

/* Copyright 1984-1992, 2009 Wind River Systems, Inc. */

/*
modification history
--------------------
01g,13jul09,lyc  LP64 support
01f,13aug98,rlp  added memDevDelete function.
01e,22sep92,rrr  added support for c++
01d,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCmemDrvh
#define __INCmemDrvh

#ifdef __cplusplus
extern "C" {
#endif


typedef struct mem_drv_direntry
    {
    char * name;	    /* Name of this entry: relative to
			       containing directory, or mount point */
    char * base;	    /* Start address, if a file */
    struct mem_drv_direntry *pDir;
			    /* files contained within, if a directory */
    size_t length;		    /* Length in bytes, if a file;
			       number of files, if a directory */
    } MEM_DRV_DIRENTRY;


/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	memDrv (void);
extern STATUS 	memDevCreate (char *name, char *base, size_t length);
extern STATUS	memDevCreateDir (char * name, MEM_DRV_DIRENTRY * files, size_t numFiles);
extern STATUS 	memDevDelete (char *name);

#else

extern STATUS 	memDrv ();
extern STATUS 	memDevCreate ();
extern STATUS	memDevCreateDir ();
extern STATUS 	memDevDelete ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCmemDrvh */
