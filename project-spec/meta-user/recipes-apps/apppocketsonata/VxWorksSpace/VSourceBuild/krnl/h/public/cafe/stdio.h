/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__cafe_stdio_h)
#define __cafe_stdio_h


#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#if defined(HAVE_CAFE_CONFIG_H)
#  include <cafe/config.h>
#endif
#include <cafe/ccdiff.h>  /* for inline */

#if !defined(HAVE_FGETC_UNLOCKED)
#  define fgetc_unlocked(f)    fgetc((f))
#endif

#if !defined(HAVE_FPUTC_UNLOCKED)
#  define fputc_unlocked(c,f)  fputc((c),(f))
#endif

#if !defined(HAVE_FGETS_UNLOCKED)
#  define fgets_unlocked(b,l,f)  fgets((b),(l),(f))
#endif

#if !defined(HAVE_FPUTS_UNLOCKED)
#  define fputs_unlocked(s,f)  fputs((s),(f))
#endif

/* On Linux fread_unlocked is already a macro. */
#if !defined(HAVE_FREAD_UNLOCKED) && !defined(fread_unlocked)
#  define fread_unlocked(p,s,n,f)  fread((p),(s),(n),(f))
#endif

/* On Linux fwrite_unlocked is already a macro. */
#if !defined(HAVE_FWRITE_UNLOCKED) && !defined(fwrite_unlocked)
#  define fwrite_unlocked(p,s,n,f)  fwrite((p),(s),(n),(f))
#endif

#if !defined(HAVE_FFLUSH_UNLOCKED)
#  define fflush_unlocked(f)  fflush((f))
#endif

#if !defined(HAVE_FEOF_UNLOCKED)
#  define feof_unlocked(f)     feof((f))
#endif

#if !defined(HAVE_FERROR_UNLOCKED)
#  define ferror_unlocked(f)    ferror((f))
#endif

#if !defined(HAVE_CLEARERR_UNLOCKED)
#  define clearerr_unlocked(f)  clearerr((f))
#endif


#if defined(__VXWORKS__) && !defined(_C99)
static inline
int fseeko(FILE *stream, off_t offset, int whence)
{
	return fseek(stream, offset, whence);
}

static inline
off_t ftello(FILE *stream)
{
	return ftell(stream);
}
#endif  /* if defined(__VXWORKS__) */


#if defined(_WIN32)
#  include <sys/types.h>  /* for off_t */
#  define vsnprintf  _vsnprintf
#  define snprintf  _snprintf
#  define fseeko  cafe_os_windows_fseeko
#  define ftello  cafe_os_windows_ftello


/* NOTE: _ftelli64() and _fseeki64 don't seem to be available in MSVC++ 2003. */
static inline
int cafe_os_windows_fseeko(FILE *stream, off_t offset, int whence)
{
#if defined(__MINGW32__)
	return fseeko64(stream, offset, whence);
#else
	return _fseeki64(stream, offset, whence);
#endif
}


static inline
off_t cafe_os_windows_ftello(FILE *stream)
{
#if defined(__MINGW32__)
	return ftello64(stream);
#else
	return (off_t) _ftelli64(stream);
#endif	
}

#endif  /* if defined(_WIN32) */


#if defined(__cplusplus)
}
#endif

#endif /* __cafe_stdio_h */
