/* utime.h - POSIX file time modification */

/*
modification history
--------------------
01e,28apr10,pad  Moved extern C statement after include statements.
01d,05mar06,mil  Removed function argument identifiers.
01c,01mar06,pes  Use base type file for time_t instead of including time.h,
                 per POSIX requirements.
01b,01feb06,mil  Added include of time.h for time_t. 
01a,07nov03,dat  started history, added const to utime args, removed
		old style declaration.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef	__INCutimeh
#define	__INCutimeh

#include <base/b_time_t.h>

#ifdef __cplusplus
extern "C" {
#endif

struct utimbuf
    {
    time_t	actime;		/* set the access time */
    time_t	modtime;	/* set the modification time */
    };

extern int utime (const char *, const struct utimbuf *);

#ifdef __cplusplus
}
#endif

#endif /* __INCdosFsLibh */
