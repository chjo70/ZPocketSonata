/* stdio.h - stdio header file */

/* Copyright (c) 1992-2004, 2009-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/* Copyright (c) 1990 The Regents of the University of California */

/*
modification history
--------------------
02x,05jul12,mcm  Fix for WIND00328433; ensuring C++ definitions are enclosed
                 in extern "C++" so as to allow inclusion of stdio.h within an
                 extern "C" {} block.
02w,22dec10,s_s  updating kputs() return type (CQ:WIND00247678)
02v,16sep10,mcm  Fixed oprintf prototype to use size_t as second argument
02u,27jul10,pad  Corrected C++ inline wrappers interface.
02t,17may10,jpb  Updated kputs.
02s,30mar10,pad  Moved 'extern "C"' statement and applied C++ inline scheme
		 for oprintf() and voprintf().
02r,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
02q,31mar09,mcm  More updates for LP64, removed non __STDC__ API signatures
02p,24mar09,fan  updated for LP64 data model
02p,17mar09,s_s  Added kprintf() and kputs() declaration
02o,11mar04,md   added oprintf(), voprintf()
02n,16sep02,aeg  added snprintf() and vsnprintf().
02m,25jun03,to   de-classified FILE
02l,17feb99,mrs  Add C++ support for NULL, (SPR #25079).
02k,10dec93,smb  added include  of private/classLibP.h for OBJ_VERIFY
02j,14nov92,jcf  added prototype for stdioShowInit().
02i,13nov92,dnw  changed defns of stdin,out,err to be assignable (SPR #1770)
		 removed include of taskLib.h (SPR #1768)
		 made include of stdarg.h conditional on __STDC__
02h,24sep92,smb  removed POSIX extensions.
02g,22sep92,rrr  added support for c++
02f,10sep92,rfs  removed FAST from stdioShow prototype
02e,08sep92,smb  added #ifndef around EOF definition.
02d,07sep92,smb  added prototypes for stdioShow() and stdioInit().
02c,02aug92,jcf  added _swbuf()/_srget() prototypes.
02b,31jul92,rrr  changed __sclearerr() definition.
02a,29jul92,smb  rewritten based on UCB stdio.
 		 This code is derived from software contributed to Berkeley by
 		 Chris Torek.
01p,04jul92,jcf  cleaned up.
01o,26may92,rrr  the tree shuffle
01n,05dec91,rrr  added missings routines to !__STDC__ section
01m,26nov91,llk  added include of stdarg.h as per Marc Ullman.
01l,07oct91,rrr  fixed fread and fwrite.
01k,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01j,10jun91.del  added pragma for gnu960 alignment.
01i,21may91,kdl  added non-ANSI def's for stdioFillBuf() and stdioFlushBuf().
01h,10jan91,shl  fixed stdioFillBuf() type int, fixed stdioFlushBuf
		 argument type.  changed remove() and rename() to have
		 same type as in ioLib.h
01g,19oct90,shl  added #include of stddef.h and stdarg.h.
01f,05oct90,dnw  added definitions for ANSI compatibility.
01e,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01d,07aug90,shl  added function declarations comment.
01c,18mar90,jcf  made stdin/stdout/stderr macros thru taskIdCurrent.
01b,30jan90,dab  changed declaration of sprintf() from char ptr to int.
01a,28mar88,gae  created.
*/

#ifndef __INCstdioh
#define __INCstdioh

#include <types/vxANSI.h>	/* includes size_t and fpos_t types */
#include <errno.h>
#include <private/handleLibP.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#if defined __GNUG__
#define NULL (__null)
#else
#if !defined(__cplusplus) && 0
#define NULL ((void*)0)
#else
#define NULL (0)
#endif
#endif
#endif

/* types */

struct __sbuf 			/* stdio buffers */
    {
    uchar_t * _base;		/* base address of {std,unget,line} buffer */
    size_t      _size;		/* size of the buffer */
    };

typedef	struct __sFILE
    {
    HANDLE		handle;		/* file pointer handle managemet */
    uchar_t *		_p;		/* current position in (some) buffer */
    long		_r;		/* read space left for getc() */
    long		_w;		/* write space left for putc() */
    short		_flags;		/* flags, below;this FILE is free if 0*/
    short		_file;		/* fileno, if Unix descriptor, else -1*/
    struct __sbuf	_bf;		/* buffer (at least 1 byte,if !NULL) */
    size_t		_lbfsize;	/* 0 or -_bf._size, for inline putc */
    struct __sbuf	_ub;		/* ungetc buffer */
    uchar_t *		_up;		/* old _p if _p is doing ungetc data */
    size_t		_ur;		/* old _r if _r counting ungetc data */
    uchar_t		_ubuf[3];	/* guarantee an ungetc() buffer */
    uchar_t		_nbuf[1];	/* guarantee a getc() buffer */
    struct __sbuf	_lb;		/* buffer for fgetline() */
    size_t		_blksize;	/* stat.st_blksize (may be!=_bf._size)*/
    size_t		_offset;	/* current lseek offset */
    TASK_ID		taskId;		/* task that owns this file pointer */
    } FILE;

/*
 * Fully-qualified function pointer type for oprintf() and voprintf()'s first
 * parameter.
 */

typedef int (*OPRINTF_OUTPUT_FUNCPTR)(char *, size_t, _Vx_usr_arg_t);

/* __SRD and __SWR are never simultaneously asserted */

#define	__SLBF		0x0001		/* line buffered */
#define	__SNBF		0x0002		/* unbuffered */
#define	__SRD		0x0004		/* OK to read */
#define	__SWR		0x0008		/* OK to write */
#define	__SWRNBF	(__SWR|__SNBF)	/* write unbuffered */
#define	__SRW		0x0010		/* open for reading & writing */
#define	__SEOF		0x0020		/* found EOF */
#define	__SERR		0x0040		/* found error */
#define	__SMBF		0x0080		/* _buf is from malloc */
#define	__SAPP		0x0100		/* fdopen()ed in append mode */
#define	__SSTR		0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT		0x0400		/* do fseek() optimisation */
#define	__SNPT		0x0800		/* do not do fseek() optimisation */
#define	__SOFF		0x1000		/* set iff _offset is in fact correct */
#define	__SMOD		0x2000		/* true => fgetline modified _p text */

#define	_IOFBF	0		/* setvbuf should set fully buffered */
#define	_IOLBF	1		/* setvbuf should set line buffered */
#define	_IONBF	2		/* setvbuf should set unbuffered */

#define	BUFSIZ	_PARM_BUFSIZ	/* size of buffer used by setbuf */
#define	BUFSIZE	BUFSIZ

#ifndef EOF
#define	EOF	(-1)
#endif  /* EOF */

#define FOPEN_MAX       _PARM_FOPEN_MAX
#define FILENAME_MAX    _PARM_FILENAME_MAX

#define	L_tmpnam	_PARM_L_tmpnam
#define	TMP_MAX		_PARM_TMP_MAX

#ifndef SEEK_SET
#define	SEEK_SET	0	/* set file offset to offset */
#endif

#ifndef SEEK_CUR
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#endif

#ifndef SEEK_END
#define	SEEK_END	2	/* set file offset to EOF plus offset */
#endif

#if _EXTENSION_POSIX_1003

#define	L_cuserid	_PARM_L_cuserid
#define	L_ctermid	_PARM_L_ctermid
#define STREAM_MAX      FOPEN_MAX

#endif /* _EXTENSION_POSIX_1003 */

extern void	clearerr (FILE *);
extern int	fclose (FILE *);
extern int	feof (FILE *);
extern int	ferror (FILE *);
extern int	fflush (FILE *);
extern int	fgetc (FILE *);
extern int	fgetpos (FILE *, fpos_t *);
extern char *	fgets (char *, int, FILE *);
extern FILE *	fopen (const char *, const char *);
extern int	fprintf (FILE *, const char *, ...);
extern int	fputc (int, FILE *);
extern int	fputs (const char *, FILE *);
extern size_t	fread (void *, size_t, size_t, FILE *);
extern FILE *	freopen (const char *, const char *, FILE *);
extern int	fscanf (FILE *, const char *, ...);
extern int	fseek (FILE *, long, int);
extern int	fsetpos (FILE *, const fpos_t *);
extern long	ftell (FILE *);
extern size_t	fwrite (const void *, size_t, size_t, FILE *);
extern int	getc (FILE *);
extern int	getchar (void);
extern char *	gets (char *);
extern int	oprintf (OPRINTF_OUTPUT_FUNCPTR routine, _Vx_usr_arg_t arg, const char *, ...);
extern void	perror (const char *);
extern int	printf (const char *, ...);
extern int	putc (int, FILE *);
extern int	putchar (int);
extern int	puts (const char *);
extern int	remove (const char *);
extern int	rename  (const char *, const char *);
extern void	rewind (FILE *);
extern int	scanf (const char *, ...);
extern void	setbuf (FILE *, char *);
extern int	setvbuf (FILE *, char *, int, size_t);
extern int	sprintf (char *, const char *, ...);
extern int 	snprintf (char *, size_t, const char *, ...);
extern int	sscanf (const char *, const char *, ...);
extern FILE *	tmpfile (void);
extern char *	tmpnam (char *);
extern int	ungetc (int, FILE *);
extern int	vfprintf (FILE *, const char *, va_list);
extern int	voprintf (OPRINTF_OUTPUT_FUNCPTR routine , _Vx_usr_arg_t arg, const char *, va_list);
extern int	vprintf (const char *, va_list);
extern int	vsprintf (char *, const char *, va_list);
extern int	vsnprintf (char *, size_t, const char *, va_list); 
extern int	__srget (FILE *);		/* for macro definition below */
extern int	__swbuf (int, FILE *);		/* for macro definition below */

/* _EXTENSION_POSIX_1003 */

extern FILE *	fdopen (int, const char *);
extern int	fileno (FILE *);

/* _EXTENSION_POSIX_1003 */

/* WRS stdio functions declarations */

#if _EXTENSION_WRS			/* undef for ANSI */

extern int	fdprintf (int fd, const char *fmt, ...);
extern int	vfdprintf (int fd, const char *fmt, va_list ap);
extern int	printErr (const char *fmt, ...);
extern int	getw (FILE *);
extern int	putw (int, FILE *);
extern void	setbuffer (FILE *, char *, size_t);
extern int	setlinebuf (FILE *);
extern FILE *   stdioFp (int std);
extern STATUS   stdioShow (FILE * fp, int level);
extern STATUS   stdioShowInit (void);
extern STATUS   stdioInit (void);
extern int      kprintf (const char * fmt, ...);
extern ssize_t  kputs (char * buffer);

#endif /* _EXTENSION_WRS */

/* Definition of stdin, stdout, stderr */

extern FILE **	__stdin(void);		/* returns current task's stdin */
extern FILE **	__stdout(void);		/* returns current task's stdout */
extern FILE **	__stderr(void);		/* returns current task's stderr */

#define stdin	(*__stdin())
#define stdout	(*__stdout())
#define stderr	(*__stderr())


/* definition of stdio macros */

#define	__sfileno(p)	((HANDLE_VERIFY(p, handleTypeFile) != OK) ? (-1) : \
			((p)->_file))

#define	__sgetc(p)	((HANDLE_VERIFY(p, handleTypeFile) != OK) ? (EOF) : \
			((--(p)->_r < 0) ? (__srget(p)) : ((int)(*(p)->_p++))))

#define	__sputc(c, p) 	((HANDLE_VERIFY(p, handleTypeFile) != OK) ? (EOF) : \
			 (--(p)->_w < 0 ?				\
			     (p)->_w >= (long)(p)->_lbfsize ?			\
				 (*(p)->_p = (c)), *(p)->_p != '\n' ?	\
				     (int)*(p)->_p++ :			\
				     __swbuf('\n', p) :			\
				 __swbuf((int)(c), p) : 		\
			     (*(p)->_p = (c), (int)*(p)->_p++)))

#define	__sfeof(p)	((HANDLE_VERIFY(p, handleTypeFile) != OK) ? \
			 (FALSE) : (((p)->_flags & __SEOF) != 0))

#define	__sferror(p)	((HANDLE_VERIFY(p, handleTypeFile) != OK) ? \
			 (FALSE) : (((p)->_flags & __SERR) != 0))

#define	__sclearerr(p)	((void)((HANDLE_VERIFY(p, handleTypeFile) != OK) ? \
				(0) : (((p)->_flags &= ~(__SERR|__SEOF)))))


#define	getchar()	__sgetc(stdin)
#define	getc(p)		__sgetc(p)
#define	putchar(c)	(__sputc(c, (stdout)))
#define	putc(c,p)	__sputc(c, p)
#define	feof(p)		__sfeof(p)
#define	ferror(p)	__sferror(p)
#define	clearerr(p)	__sclearerr(p)

#if _EXTENSION_POSIX_1003		/* undef for ANSI */
#define	fileno(p)	__sfileno(p)
#endif

#ifdef __cplusplus
}

extern "C++" {
/*
 * Inlined C++ wrappers for the old-style FUNCPTR based oprintf() and
 * voprintf() function prototypes.
 */

extern int oprintf (FUNCPTR routine, _Vx_usr_arg_t arg, const char *, ...) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline int oprintf
    (
    FUNCPTR routine,
    _Vx_usr_arg_t arg,
    const char * fmt,
    ...
    )
    {
    va_list vaList;	/* traverses argument list */

    va_start (vaList, fmt);

    return voprintf ((OPRINTF_OUTPUT_FUNCPTR)routine, arg, fmt, vaList);
    }

extern int voprintf (FUNCPTR routine, _Vx_usr_arg_t arg, const char *, va_list)\
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline int voprintf
    (
    FUNCPTR routine,
    _Vx_usr_arg_t arg,
    const char * fmt,
    va_list vaList
    )
    {
    return voprintf ((OPRINTF_OUTPUT_FUNCPTR)routine, arg, fmt, vaList);
    }
}
#endif /* __cplusplus */

#endif /* __INCstdioh */
