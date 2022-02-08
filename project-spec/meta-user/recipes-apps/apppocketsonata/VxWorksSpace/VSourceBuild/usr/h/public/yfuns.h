/* yfuns.h functions header */
#ifndef _YFUNS
#define _YFUNS
#include <stddef.h>
#if defined(__RTP__)
#include <sys/types.h>
#endif
_C_STD_BEGIN
 #if _USE_EXISTING_SYSTEM_NAMES

  #if defined(__BORLANDC__)
   #define _Environ	_environ

  #else /* defined(__BORLANDC__) */
   #define _Environ	environ
  #endif /* defined(__BORLANDC__) */

 #if _HAS_C9X

 #else /* _HAS_C9X */
 #define _Exit	_exit
 #endif /* _IS_C9X */

  #define _Close	close
  #define _Lseek	lseek
  #define _Read		read
  #define _Write	write
 #endif /* _USE_EXISTING_SYSTEM_NAMES */

		/* process control */
#define _Envp	(*_Environ)

		/* stdio functions */
#define _Fclose(str)	_Close(_FD_NO(str))
#define _Fread(str, buf, cnt)	_Read(_FD_NO(str), buf, cnt)
#define _Fwrite(str, buf, cnt)	_Write(_FD_NO(str), buf, cnt)

		/* interface declarations */
_EXTERN_C
extern char **_Environ;
_NO_RETURN(_Exit(int));

 #if defined(__APPLE__) || defined(__CYGWIN__)
int _Close(int);
_Longlong _Lseek(int, _Longlong, int);
int _Read(int, void *, size_t);
int _Write(int, const void *, size_t);

 #else /* defined(__APPLE__) */
int _Close(int);
  #if defined(__RTP__)
/*
 * In the RTP environment lseek() uses off_t, per POSIX, and off_t always is a
 * 64-bit type in the RTP environment.
 */
off_t _Lseek(int, off_t, int);
  #else
long _Lseek(int, long, int);
  #endif /* __RTP__ */
int _Read(int, unsigned char *, int);
int _Write(int, const unsigned char *, int);
 #endif /* defined(__APPLE__) */

_END_EXTERN_C
_C_STD_END
#endif /* _YFUNS */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:1278 */
