/* auxv.h - auxiliary vector header */

/*
 * Copyright (c) 2003-2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,06jul06,pcs  Add AT_WINDHEAPOPT
01b,03dec03,zl   added AT_WINDSTKALN, AT_WINDCACHEALN
01a,03sep03,nrj  written.
*/

#ifndef __INCauxvh
#define __INCauxvh

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ASMLANGUAGE

typedef struct auxiliaryVector
    {
    int	a_type;
    union
	{
        long	a_val;
        void	*a_ptr;
        void	(*a_fcn)();
        } a_un;
    } auxv_t;

#endif /* _ASMLANGUAGE */

#define	AT_NULL		0
#define	AT_IGNORE	1	/* No meaning of entry */
#define	AT_EXECFD	2	/* a_val is fd for lib loader */
#define	AT_PHDR		3	/* runtime memory ptr for phdr */
#define	AT_PHENT	4	/* sizeof(phdr[0]) */
#define	AT_PHNUM	5	/* no. of phdr entries */
#define	AT_PAGESZ	6	/* a_val is page size */
#define	AT_BASE		7	/* a_ptr is  loader base addr */
#define	AT_FLAGS	8	/* flags */
#define	AT_ENTRY	9	/* entry point */
#define	AT_DCACHEBSIZE	10	/* data cache block size */
#define	AT_ICACHEBSIZE	11	/* instruction cache block size */
#define	AT_UCACHEBSIZE	12	/* unified cache block size */

/* Specific to Wind River OS  implementation */

#define	AT_WINDVERSION	3000	/* VxWorks version */

#define	AT_WINDHEAPSZ	3001	/* initial heap size for process */
#define	AT_WINDMEMALN	3002	/* memory alignment in bytes */
#define	AT_WINDCACHEALN	3003	/* cache alignment in bytes */
#define	AT_WINDSTKALN	3004	/* stack alignment in bytes */
#define	AT_WINDMMUSTAT	3005	/* state of  MMU - enabled or not */
#define	AT_WINDLIBMMU	3006	/* mmu info for shared lib */
#define	AT_WINDLIBLD	3007	/* shared lib loader specific */
#define	AT_WINDLIBFD	3008	/* shared lib file desc */
#define	AT_WINDDBG	3009	/* Debugger info */

#define	AT_WINDVXSIM	3010	/* reserved for VXSIM */
#define	AT_WINDHEAPOPT	3011	/* heap partision options for process */

#ifdef __cplusplus
}
#endif

#endif /* __INCauxvh */
