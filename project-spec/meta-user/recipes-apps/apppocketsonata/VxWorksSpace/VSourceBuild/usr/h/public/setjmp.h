#ifndef _Isetjmp
#define _Isetjmp
/* The definitions from xmacros.h is only required when Dinkum C and C++ libraries are not used together. They are not necessary for RTP space. */
#ifndef __RTP__
#include <xmacros.h>
#endif

#if !defined(_C_STD_BEGIN)
#if defined(__cplusplus) && 201103 <= __cplusplus
#define _C_STD_BEGIN     namespace std {
#else
#define _C_STD_BEGIN
#endif
#endif
#if !defined(_C_LIB_DECL)
#if defined(__cplusplus) && 201103 <= __cplusplus
#define _C_LIB_DECL     extern "C" {
#else
#define _C_LIB_DECL
#endif
#endif
#if !defined(_END_C_LIB_DECL)
#if defined(__cplusplus) && 201103 <= __cplusplus
#define _END_C_LIB_DECL }
#else
#define _END_C_LIB_DECL
#endif
#endif
#if !defined(_C_STD_END)
#if defined(__cplusplus) && 201103 <= __cplusplus
#define _C_STD_END     }
#else
#define _C_STD_END
#endif
#endif
#if !defined(_STD_USING) && !defined(_CSETJMP_)
#if defined(__cplusplus) && 201103 <= __cplusplus
#define _STD_USING
#endif
#endif

/* 
 * For the RTP space, three extra words are required in jmp_buf to hold 
 * the signal mask information required for sigsetjmp and siglongjmp support.
 * Here, we update the value of _JBLEN, before it can be used to define
 * jmp_buf.
 * Note that when the type of jmp_buf is long long, we end up with a larger
 * array than we need, but that is ok.
 */
#ifdef __RTP__
#define	_SIGSETJMP_INCREMENT	3
#else
#define	_SIGSETJMP_INCREMENT	0
#endif

_C_STD_BEGIN
_C_LIB_DECL

#if defined(m88k) || defined(__m88k)

#define _JBLEN	40 + _SIGSETJMP_INCREMENT

#elif defined(__ppc)

/* Define ONLY_SOFTWARE_JMPBUF if you are only using software floating point and want
   to save space.  */

#ifdef __EVEC__
#define _JBLEN 25 + _SIGSETJMP_INCREMENT
#else
#ifdef __VEC__
#define _JBLEN 116 + _SIGSETJMP_INCREMENT
#else
#ifdef ONLY_SOFTWARE_JMPBUF
#define _JBLEN 13 + _SIGSETJMP_INCREMENT
#else
#ifdef __LP64__
#define _JBLEN 45 + _SIGSETJMP_INCREMENT
#else
#define _JBLEN 32 + _SIGSETJMP_INCREMENT
#endif
#endif
#endif
#endif

#elif defined(__m68k)

#ifdef ONLY_SOFTWARE_JMPBUF
#define _JBLEN	13 + _SIGSETJMP_INCREMENT
#else
#define _JBLEN	34 + _SIGSETJMP_INCREMENT
#endif

#elif defined(__rce)

#define _JBLEN 9 + _SIGSETJMP_INCREMENT

#elif defined(__nec)

#define _JBLEN 12 + _SIGSETJMP_INCREMENT

#elif defined(__m32r)

#define _JBLEN 8 + _SIGSETJMP_INCREMENT

#elif defined(__mips)

/* Define ONLY_SOFTWARE_JMPBUF if you are only using software floating point and want to save space.  */

/* MIPS RTPs will need to save and restore gp and t9 for shared libraries to work */
#ifndef	__RTP__
#ifdef ONLY_SOFTWARE_JMPBUF
#define _JBLEN 11 + _SIGSETJMP_INCREMENT
#else
#define _JBLEN 23 + _SIGSETJMP_INCREMENT
#endif
#else	/* __RTP__ */
#ifdef ONLY_SOFTWARE_JMPBUF
#define _JBLEN 13 + _SIGSETJMP_INCREMENT
#else
#define _JBLEN 25 + _SIGSETJMP_INCREMENT
#endif
#endif	/* __RTP__ */

#elif defined(sparc) || defined(__sparc)
#define	_JBLEN		5 + _SIGSETJMP_INCREMENT

#elif defined(sh) || defined(__sh) || defined(__sh__)
#define	_JBLEN		9 + _SIGSETJMP_INCREMENT
#elif defined(__arm) || defined(__arm__)
#if defined(__NEON__) || defined(_VFPv3_D32__)
#define	_JBLEN		60 + _SIGSETJMP_INCREMENT
#elif defined(__VFP__) || defined(__VFP_FP__)
#define	_JBLEN		27 + _SIGSETJMP_INCREMENT
#else
#define	_JBLEN		11 + _SIGSETJMP_INCREMENT
#endif

#elif defined(__aarch64) || defined(__aarch64__)

#define _JBLEN		30  + _SIGSETJMP_INCREMENT

#elif defined(__386) || defined(__i386)

#define _JBLEN 32  + _SIGSETJMP_INCREMENT

#elif defined(__sc)
#define _JBLEN 32 + _SIGSETJMP_INCREMENT
#elif defined(__tc)
#define _JBLEN 32 + _SIGSETJMP_INCREMENT

#elif defined(__x86_64) || defined(__x86_64__)

#define _JBLEN 64  + _SIGSETJMP_INCREMENT*2

#else

#error "_JBLEN not set!"

#endif

#ifdef __EVEC__
typedef __ev64_opaque__  jmp_buf[_JBLEN] ;
#elif defined(__VEC__)
typedef __vector signed int jmp_buf[_JBLEN/4] ;

#elif defined(__MIPS64BIT__)
typedef long long jmp_buf[_JBLEN];
#elif defined(__ppc)
typedef long long jmp_buf[_JBLEN];
#elif defined(__x86_64) || defined(__x86_64__)
typedef long long jmp_buf[_JBLEN];
#elif defined(__aarch64__)
typedef long jmp_buf[_JBLEN];
#else
typedef int jmp_buf[_JBLEN];
#endif

extern int setjmp(jmp_buf);
extern void longjmp(jmp_buf, int);

typedef jmp_buf sigjmp_buf;

#ifdef __mot68
#define sigsetjmp(a,b) setjmp(a)
#define siglongjmp(a,b) longjmp(a,b)
#else
extern int sigsetjmp(sigjmp_buf,int);
extern void siglongjmp(sigjmp_buf, int);
#endif

_END_C_LIB_DECL
_C_STD_END

#endif

#ifdef _STD_USING
using	std::longjmp;
using	std::setjmp;
using	std::jmp_buf;
using   std::sigjmp_buf; 
using   std::siglongjmp;
using   std::sigsetjmp;
#endif

