/*	BSDI $Id: dlfcn.h,v 2.6 1999/08/09 15:05:08 donn Exp $	*/

#ifndef _DLFCN_H_
#define	_DLFCN_H_

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#ifndef RTLD_INTERNAL
/* Map the external names to our internal libdl names.  */
#  define	dladdr		_rtld_dladdr
#  define	dlclose		_rtld_dlclose
#  define	dlerror		_rtld_dlerror
#  define	dlopen		_rtld_dlopen
#  define	dlsym		_rtld_dlsym
#endif
#endif  /* _POSIX_xxx_SOURCE */

#define	RTLD_LAZY	1
#define	RTLD_NOW	2

/* Linux extensions which we currently support.  */
#define	RTLD_GLOBAL	0x100

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#define	RTLD_NEXT	((void *)-1)

/* Support for dladdr(), a Solaris extension.  */
typedef struct {
        const char      *dli_fname;     /* pointer to filename of object */
        void            *dli_fbase;     /* base address of object */
        const char      *dli_sname;     /* name of symbol nearest to address */
        void            *dli_saddr;     /* address of that symbol */
} Dl_info;

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
int dladdr(void *, Dl_info *);
#endif  /* _POSIX_xxx_SOURCE */

int dlclose(void *);
char *dlerror(void);
void *dlopen(const char *, int);
void *dlsym(void *, const char *);

#ifdef __cplusplus
};
#endif

#endif  /* _DLFCN_H_ */
