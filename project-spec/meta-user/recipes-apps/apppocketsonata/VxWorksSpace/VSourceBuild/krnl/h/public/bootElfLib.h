/* bootElfLib.h - ELF object module boot loader library header */

/* Copyright 1984-1992, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,15jul10,kab  Add binding decls for map/unmap routines
01a,25oct93,cd   created from bootEcoffLib.h v01b
*/

#ifndef __INCbootElfLibh
#define __INCbootElfLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS bootElfInit (void);

extern STATUS (* _func_elfLoadMapAddrBlock)
    (
    PHYS_ADDR   pAddr,      /* requested physical start address */
    VIRT_ADDR   vAddr,      /* ELF header virtual start address  */
    size_t      numBytes,   /* size in bytes to map */
    char **     load_addr  /* where the above is mapped */
    );

extern STATUS (* _func_elfLoadUnmapAddrBlock)
    (
    PHYS_ADDR   pAddr,      /* requested physical start address */
    VIRT_ADDR   vAddr,      /* ELF header virtual address base */
    size_t      numBytes,   /* size in bytes to map */
    char *      load_addr   /* where the above is mapped */
    );

#else	/* __STDC__ */

extern STATUS bootElfInit ();

extern STATUS (* _func_elfLoadMapAddrBlock) ();

extern STATUS (* _func_elfLoadUnmapAddrBlock) ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCbootElfLibh */
