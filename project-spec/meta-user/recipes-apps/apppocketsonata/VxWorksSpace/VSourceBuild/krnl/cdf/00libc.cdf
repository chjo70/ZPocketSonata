/* 00libc.cdf - libc components */

/*
 * Copyright (c) 2013, 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
26apr17,val  added hypot under INCLUDE_ANSI_MATH (V7COR-4843)
22jan17,jbm  Fixed typo. Removed tabs, minor edits.
17jan17,lau  added scalb, copysign, logb, finite and drem under INCLUDE_ANSI_MATH (V7COR-4642)
07dec16,hcl  added strtoll and strtoull to INCLUDE_ANSI_STDLIB_NUMBERS (V7IOT-1)
29sep16,lau  added strlcat to INCLUDE_ANSI_STRING (V7COR-4599)
27apr16,gls  fixed component INCLUDE_ANSI_STDLIB_NUMBERS CERT dependency
21apr16,emj  CERT: Update to produce partially linked objects (US79607)
07apr15,kk   fixed spaced after "/", causing CDF issues.
11jun15,gls  removed unavailable routines from INCLUDE_ANSI_MATH for CERT  
22jul15,v_r  Removed sinh/cosh/tanh from ANSI_MATH LINK_SYMS since they are not 
             shipped (V7SP-276).
15apr15,v_r  Added back clock(), asctime_r(), localtime_r(), mktime(), time()
             and assert() for CERT. 
             No more hiding component for CERT, instead rely on the project
             facility to mark them unavailable.
24mar15,v_r  CERT adaptation for assert, string, stdlib, time and stdio modules
15sep15,pee  fixed module conflict on stdio.o
01oct13,mcm  created based on content from the common 00vxWorks.cdf 
             in version 6.9
*/

/*
DESCRIPTION
Components that are part of kernel libc 
*/

Folder  FOLDER_ANSI {
        NAME            ANSI C components (libc)
        SYNOPSIS        This folder includes components and parameters to \
                        support the ANSI libraries.
        CHILDREN        INCLUDE_ANSI_ASSERT     \
                        INCLUDE_ANSI_CTYPE      \
                        INCLUDE_ANSI_LOCALE     \
                        INCLUDE_ANSI_MATH       \
                        INCLUDE_ANSI_STDIO      \
                        INCLUDE_ANSI_STDLIB     \
                        INCLUDE_ANSI_STRING     \
                        INCLUDE_ANSI_STRDUP     \
                        INCLUDE_ANSI_STRERROR   \
                        INCLUDE_ANSI_TIME       \
                        INCLUDE_ANSI_STDIO_EXTRA
        DEFAULTS        INCLUDE_ANSI_ASSERT     \
                        INCLUDE_ANSI_CTYPE      \
                        INCLUDE_ANSI_MATH       \
                        INCLUDE_ANSI_STDIO      \
                        INCLUDE_ANSI_STDLIB     \
                        INCLUDE_ANSI_STRING     \
                        INCLUDE_ANSI_TIME       \
                        INCLUDE_ANSI_STRDUP     \
                        INCLUDE_ANSI_STRERROR
}

Component INCLUDE_ANSI_STDIO_EXTRA {
        NAME            ANSI stdio extensions
        SYNOPSIS        This component includes the Wind River routines: \
                        getw( ), putw( ), and setbuffer( ).
        LINK_SYMS       getw putw setbuffer
}

Component INCLUDE_ANSI_ASSERT {
        NAME            ANSI assert
        SYNOPSIS        This component includes the ANSI assert function.
        LINK_SYMS       __assert
        HELP            ansiAssert
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         assert.o
#endif
        REQUIRES        INCLUDE_ANSI_STDIO \
                        INCLUDE_ANSI_ABORT \
                        INCLUDE_FORMATTED_IO
}

Component INCLUDE_ANSI_CTYPE {
        NAME            ANSI ctype
        SYNOPSIS        This component includes the ANSI ctype functions.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         __ctype_tab.o isalnum.o isalpha.o iscntrl.o isdigit.o \
                        isgraph.o islower.o isprint.o ispunct.o isspace.o \
                        isupper.o isxdigit.o tolower.o toupper.o
        LINK_SYMS       __ctype isalnum isalpha iscntrl isdigit isgraph \
                        islower isprint ispunct isspace isupper isxdigit \
                        tolower toupper
#endif
        HELP            ansiCtype
}

Component INCLUDE_ANSI_LOCALE {
        NAME            ANSI locale
        SYNOPSIS        This component includes the ANSI locale functions. 
        MODULES         localeconv.o setlocale.o
        LINK_SYMS       localeconv setlocale
        HELP            ansiLocale
        REQUIRES        INCLUDE_ANSI_STRCMP
}

Component INCLUDE_ANSI_LONGJMP {
        NAME            ANSI longjmp
        SYNOPSIS        ANSI longjmp
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         longjmp.o
        LINK_SYMS       longjmp
#endif
        REQUIRES        INCLUDE_SIGNAL_ARCH
}

Component INCLUDE_ANSI_MATH {
        NAME            ANSI math
        SYNOPSIS        This component includes the ANSI mathematical functions.
#ifndef _WRS_CONFIG_CERT
        LINK_SYMS       acos asin atan atan2 ceil copysign cos cosh drem \
                        exp fabs finite floor fmod frexp hypot ldexp log \
                        log10 logb modf pow scalb sin sinh sqrt tan tanh
#else /* _WRS_CONFIG_CERT */
        LINK_SYMS       acos atan atan2 ceil cos exp fabs floor fmod frexp     \
                        ldexp log log10 modf pow sin sqrt tan
#endif /* _WRS_CONFIG_CERT */
        HELP            ansiMath
}

ObjectFile libc_wr.a::stdio.o 
{
}

Component INCLUDE_ANSI_STDIO {
        NAME            ANSI stdio
        SYNOPSIS        This component provides the ansiStdio library, which \
                        includes most ANSI standard I/O functions except \
                        printf( ), sprintf( ), and sscanf( ).
#ifndef _WRS_CONFIG_CERT
        MODULES         clearerr.o fclose.o feof.o ferror.o fflush.o fgetc.o  \
                        fgetpos.o fgets.o fopen.o fprintf.o fputc.o fputs.o   \
                        fread.o freopen.o fscanf.o fseek.o fsetpos.o ftell.o  \
                        fwrite.o getc.o getchar.o gets.o perror.o putc.o      \
                        putchar.o puts.o rewind.o scanf.o setbuf.o setvbuf.o  \
                        tmpfile.o tmpnam.o ungetc.o vfprintf.o fdopen.o       \
                        fileno.o flags.o makebuf.o rget.o libc_wr.a::stdio.o fvwrite.o   \
                        wbuf.o refill.o wsetup.o
        LINK_SYMS       clearerr fclose feof ferror fflush fgetc fgetpos      \
                        fgets fopen fprintf fputc fputs fread freopen fscanf  \
                        fseek fsetpos ftell fwrite getc getchar gets perror   \
                        putc putchar puts rewind scanf setbuf setvbuf tmpfile \
                        tmpnam ungetc vfprintf fdopen fileno
#else
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         fdopen.o fflush.o fprintf.o vfprintf.o fgets.o fopen.o \
                        fclose.o stdioLib.o stdioFuncBind.o stdio.o flags.o \
                        wbuf.o refill.o wsetup.o makebuf.o
        LINK_SYMS       fdopen fflush fprintf fgets fopen fclose 
#endif
#endif /* _WRS_CONFIG_CERT */
        HELP            ansiStdio
        REQUIRES        INCLUDE_KERNEL          \
                        INCLUDE_IO_BASIC        \
                        INCLUDE_ANSI_STRING     \
                        INCLUDE_ANSI_STRLEN     \
                        INCLUDE_STDIO           \
                        INCLUDE_FORMATTED_IO    \
                        INCLUDE_ANSI_STRERROR   \
                        INCLUDE_ANSI_LONGJMP    \
                        INCLUDE_MEM_MGR_BASIC
}

Component INCLUDE_ANSI_STDLIB {
        NAME            ANSI standard library
        SYNOPSIS        This component provides the ansiStdlib library. This \
                        library includes several standard ANSI routines such as \
                        abort(), abs(), rand(), and strtod(). For a full list of \
                        routines and descriptions, refer to the ansiStdlib entry \
                        in the VxWorks 7 kernel API reference.
#ifdef _WRS_CONFIG_CERT
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         atexit.o
        LINK_SYMS       atexit
#endif
        REQUIRES        INCLUDE_ANSI_ABS            \
                        INCLUDE_ANSI_ABORT          \
                        INCLUDE_ANSI_STRCPY         \
                        INCLUDE_ANSI_ATOF           \
                        INCLUDE_ANSI_STRTOD         \
                        INCLUDE_ANSI_STDLIB_NUMBERS \
                        INCLUDE_TASK_CREATE_DELETE  \
                        INCLUDE_MEM_MGR_BASIC
#else
        MODULES         atexit.o multibyte.o system.o
        LINK_SYMS       atexit mblen system
        REQUIRES        INCLUDE_ANSI_ABS            \
                        INCLUDE_ANSI_ABORT          \
                        INCLUDE_ANSI_BSEARCH        \
                        INCLUDE_ANSI_STRCPY         \
                        INCLUDE_ANSI_ATOF           \
                        INCLUDE_ANSI_STRTOD         \
                        INCLUDE_ANSI_STDLIB_NUMBERS \
                        INCLUDE_TASK_CREATE_DELETE  \
                        INCLUDE_ENV_VARS            \
                        INCLUDE_MEM_MGR_BASIC
#endif /* !_WRS_CONFIG_CERT */
        HELP            ansiStdlib
}

Component INCLUDE_ANSI_ABORT {
        NAME            ANSI abort
        SYNOPSIS        This component includes the ANSI abort function. 
        LINK_SYMS       abort
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         abort.o
#endif
#ifndef _WRS_CONFIG_CERT
        REQUIRES        INCLUDE_TASK_CREATE_DELETE  \
                        INCLUDE_SIGNALS
#else
        REQUIRES        INCLUDE_TASK_CREATE_DELETE
#endif /* !_WRS_CONFIG_CERT */
}

Component INCLUDE_ANSI_BSEARCH {
        NAME            ANSI stdlib bsearch function
        SYNOPSIS        This component includes the ANSI stdlib bsearch function. 
        LINK_SYMS       bsearch
        MODULES         bsearch.o
}

Component INCLUDE_ANSI_STRTOD {
        NAME            ANSI strtod function
        SYNOPSIS        This component includes the ANSI strtod function. 
        LINK_SYMS       strtod
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strtod.o
#endif
}

Component INCLUDE_ANSI_ATOF {
        NAME            ANSI atof function
        SYNOPSIS        This component includes the ANSI atof function.
        LINK_SYMS       atof
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         atof.o
#endif
        REQUIRES        INCLUDE_ANSI_STRTOD
}

Component INCLUDE_ANSI_STDLIB_NUMBERS {
        NAME            ANSI stdlib string-to-number conversion
        SYNOPSIS        This component includes the ANSI stdlib string-to-number \
                        conversion functions.
#ifdef _WRS_CONFIG_CERT
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         atoi.o atol.o strtol.o strtoul.o div.o ldiv.o labs.o \
                        stdrand.o
        LINK_SYMS       atoi atol strtol strtoul div_r ldiv_r labs rand
#endif
#else
        MODULES         atoi.o atol.o strtol.o strtoul.o \
                        div.o ldiv.o labs.o qsort.o stdrand.o \
                        strtoll.o strtoull.o
        LINK_SYMS       atoi atol strtol strtoul div ldiv    \
                        labs qsort rand strtoll strtoull
#endif /* !_WRS_CONFIG_CERT */
}

Component INCLUDE_ANSI_STRING {
        NAME            ANSI string
        SYNOPSIS        This component includes the ANSI string manipulation \
                        functions. 
#ifdef _WRS_CONFIG_CERT
        REQUIRES        INCLUDE_BLIB              \
                        INCLUDE_ANSI_MEMCHR       \
                        INCLUDE_ANSI_MEMCPY       \
                        INCLUDE_ANSI_MEMSET       \
                        INCLUDE_ANSI_MEMCMP       \
                        INCLUDE_ANSI_MEMMOVE      \
                        INCLUDE_ANSI_STRCAT       \
                        INCLUDE_ANSI_STRNCAT      \
                        INCLUDE_ANSI_STRCMP       \
                        INCLUDE_ANSI_STRNCMP      \
                        INCLUDE_ANSI_STRCPY       \
                        INCLUDE_ANSI_STRNCPY      \
                        INCLUDE_ANSI_STRLCPY      \
                        INCLUDE_ANSI_STRLEN
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strstr.o strpbrk.o strrchr.o strspn.o strtok_r.o
        LINK_SYMS       strstr strpbrk strrchr strspn strtok_r
#endif
#else
        REQUIRES        INCLUDE_BLIB              \
                        INCLUDE_ANSI_MEMCHR       \
                        INCLUDE_ANSI_MEMCPY       \
                        INCLUDE_ANSI_MEMSET       \
                        INCLUDE_ANSI_MEMCMP       \
                        INCLUDE_ANSI_MEMMOVE      \
                        INCLUDE_ANSI_STRCAT       \
                        INCLUDE_ANSI_STRNCAT      \
                        INCLUDE_ANSI_STRLCAT      \
                        INCLUDE_ANSI_STRCMP       \
                        INCLUDE_ANSI_STRNCMP      \
                        INCLUDE_ANSI_STRCASECMP   \
                        INCLUDE_ANSI_STRNCASECMP  \
                        INCLUDE_ANSI_STRCPY       \
                        INCLUDE_ANSI_STRNCPY      \
                        INCLUDE_ANSI_STRLCPY      \
                        INCLUDE_ANSI_STRLEN
        MODULES         strchr.o strcoll.o strcspn.o strstr.o strtok.o    \
                        strpbrk.o strrchr.o strspn.o strtok_r.o strxfrm.o \
                        xstate.o
        LINK_SYMS       strchr strcoll strcspn strstr strtok strpbrk strrchr \
                        strspn strtok_r strxfrm
#endif /* !_WRS_CONFIG_CERT */
        HELP            ansiString
}

Component INCLUDE_ANSI_TIME {
        NAME            ANSI time
        SYNOPSIS        This component includes the ANSI time-related functions.
#ifdef _WRS_CONFIG_CERT
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         gmtime.o clock.o asctime.o localtime.o mktime.o time.o \
                        strftime.o locTime.o localtime.o 
        LINK_SYMS       gmtime clock asctime_r localtime_r mktime time 
#endif
#else
        MODULES         asctime.o clock.o ctime.o difftime.o gmtime.o \
                        localtime.o mktime.o strftime.o time.o locTime.o
        LINK_SYMS       asctime clock ctime difftime gmtime localtime \
                        mktime strftime time
#endif /* !_WRS_CONFIG_CERT */
        REQUIRES        INCLUDE_ANSI_STDLIB \
                        INCLUDE_ANSI_STRING \
                        INCLUDE_POSIX_CLOCKS
        HELP            ansiTime
}

Component INCLUDE_ANSI_ABS {
        NAME            ANSI abs function
        SYNOPSIS        This component includes the ANSI abs function. 
        LINK_SYMS       abs
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         abs.o
#endif
}

Component INCLUDE_ANSI_MEMCHR {
        NAME            ANSI memchr function
        SYNOPSIS        This component includes the ANSI memchr function.
        LINK_SYMS       memchr
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memchr.o
#endif
}

Component INCLUDE_ANSI_MEMCPY {
        NAME            ANSI memcpy function
        SYNOPSIS        This component includes the ANSI memcpy function.
        LINK_SYMS       memcpy
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memcpy.o
#endif
        REQUIRES        INCLUDE_BLIB
}

Component INCLUDE_ANSI_MEMSET {
        NAME            ANSI memset function
        SYNOPSIS        This component includes the ANSI memset function.
#ifdef _WRS_CONFIG_CERT
        LINK_SYMS    memset
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memset.o
#endif /* !_WRS_CONFIG_CERT_KERNEL_OBJECT */
#else
        LINK_SYMS       memset memset_s
        MODULES         memset.o memset_s.o
#endif /* _WRS_CONFIG_CERT */
        REQUIRES        INCLUDE_BLIB
}

Component INCLUDE_ANSI_MEMCMP {
        NAME            ANSI memcmp function
        SYNOPSIS        This component includes the ANSI memcmp function.
        LINK_SYMS       memcmp
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memcmp.o
#endif
}

Component INCLUDE_ANSI_MEMMOVE {
        NAME            ANSI memmove function
        SYNOPSIS        This component includes the ANSI memmove function. 
        LINK_SYMS       memmove
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         memmove.o
#endif
}

Component INCLUDE_ANSI_STRCAT {
        NAME            ANSI string cat function
        SYNOPSIS        This component includes the ANSI string cat function.
        LINK_SYMS       strcat
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strcat.o
#endif
}

Component INCLUDE_ANSI_STRNCAT {
        NAME            ANSI strncat function
        SYNOPSIS        This component includes the ANSI strncat function (appends \
                        the first N characters). 
        LINK_SYMS       strncat
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strncat.o
#endif
}

Component INCLUDE_ANSI_STRLCAT {
        NAME            ANSI strlcat function
        SYNOPSIS        This component includes the ANSI strlcat function. 
        LINK_SYMS       strlcat
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strlcat.o
#endif
}

Component INCLUDE_ANSI_STRCMP {
        NAME            ANSI string compare function
        SYNOPSIS        This component includes the ANSI string compare function. 
        LINK_SYMS       strcmp
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strcmp.o
#endif
}

Component INCLUDE_ANSI_STRNCMP {
        NAME            ANSI string compare function
        SYNOPSIS        This component includes the ANSI string compare function \
                        (first N characters).
        LINK_SYMS       strncmp
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strncmp.o
#endif
}

Component INCLUDE_ANSI_STRCASECMP {
        NAME            ANSI extension - case insensitive string compare function
        SYNOPSIS        This component includes an ANSI extension for a case \
                        insensitive string compare function
        LINK_SYMS       strcasecmp
        MODULES         strcasecmp.o
}

Component INCLUDE_ANSI_STRNCASECMP {
        NAME            ANSI extension - case insensitive string compare function
        SYNOPSIS        This component includes an ANSI extension for a case \
                        insensitive string compare function (first N characters).
        LINK_SYMS       strncasecmp
        MODULES         strncasecmp.o
}

Component INCLUDE_ANSI_STRCPY {
        NAME            ANSI string copy function
        SYNOPSIS        This component includes the ANSI string copy function.
        LINK_SYMS       strcpy
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strcpy.o
#endif
}

Component INCLUDE_ANSI_STRNCPY {
        NAME            ANSI string copy function
        SYNOPSIS        This component includes the ANSI string copy function \
                        (first N characters).
        LINK_SYMS       strncpy
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strncpy.o
#endif
}

Component INCLUDE_ANSI_STRLCPY {
        NAME            ANSI strlcpy function
        SYNOPSIS        This component includes the ANSI strlcpy function. 
        LINK_SYMS       strlcpy
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strlcpy.o
#endif
}

Component INCLUDE_ANSI_STRLEN {
        NAME            ANSI string length function
        SYNOPSIS        This component includes the ANSI string length function. 
        LINK_SYMS       strlen
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strlen.o
#endif
}

Component INCLUDE_ANSI_STRDUP {
        NAME            ANSI string duplication function
        SYNOPSIS        This component includes the ANSI string duplication \
                        function.
        LINK_SYMS       strdup
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strdup.o
#endif
        REQUIRES        INCLUDE_MEM_MGR_BASIC
}

Component INCLUDE_ANSI_STRERROR {
        NAME            ANSI errno to error string conversion function
        SYNOPSIS        This component includes the ANSI errno to error string \
                        conversion function
        LINK_SYMS       strerror
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         strerror.o
#endif
        REQUIRES        INCLUDE_ANSI_STRCPY  \
                        INCLUDE_ANSI_STRNCPY \
                        INCLUDE_FORMATTED_OUT_BASIC
}

Component INCLUDE_STDIO_SHOW {
        NAME            stdio show routine
        MODULES         stdioShow.o
        INIT_RTN        stdioShowInit ();
        HDR_FILES       stdio.h
        INCLUDE_WHEN    INCLUDE_STDIO \
                        INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_FP_TYPE {
        NAME            Floating-point type
        SYNOPSIS        This component includes the type of floating point.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         fpType.o
#endif
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_FLOATING_POINT {
        NAME            fpp formatting for printf
        SYNOPSIS        This component allows printf and other routines to \
                        format floats correctly. 
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         floatLib.o
#endif
        INIT_RTN        floatInit ();
        HDR_FILES       math.h
        REQUIRES        INCLUDE_FORMATTED_IO \
                        INCLUDE_ANSI_STRCPY  \
                        INCLUDE_ANSI_MATH    \
                        INCLUDE_FP_TYPE
}

Component INCLUDE_FORMATTED_IO {
        NAME            Formatted IO
        SYNOPSIS        This component includes the formatting for printf, scanf, \
                        and so forth.
        REQUIRES        INCLUDE_FORMATTED_OUT_BASIC \
                        INCLUDE_ANSI_MEMCHR         \
                        INCLUDE_IO_BASIC
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         fioLib.o
#endif
        INIT_RTN        fioLibInit ();
        HDR_FILES       fioLib.h
}

Component INCLUDE_FORMATTED_OUT_BASIC {
        NAME            Formatted IO output routines
        SYNOPSIS        This component includes the formatting for output \
                        routines (scaled down).
        REQUIRES        INCLUDE_KERNEL          \
                        INCLUDE_BLIB            \
                        INCLUDE_ANSI_MEMCHR     \
                        INCLUDE_ANSI_STRLEN
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         fioBaseLib.o
#endif
        INIT_RTN        fioBaseLibInit ();
        HDR_FILES       fioLib.h
}

Component INCLUDE_STDIO {
        NAME            stdio
        SYNOPSIS        This component includes the buffered IO library. 
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
        MODULES         stdioLib.o
#endif
        INIT_RTN        stdioInit ();
        HDR_FILES       stdio.h
        REQUIRES        INCLUDE_ANSI_STDIO      \
                        INCLUDE_MEM_MGR_BASIC   \
                        INCLUDE_TASK_CREATE_HOOKS
}
