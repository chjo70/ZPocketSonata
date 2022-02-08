/* applUtilLib.h - Application utility library */

/*
 * Copyright (c) 2001-2004, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31mar15,h_k  re-arranged category and priority bits for syslog. (F2865)
07aug04,dlk  Substantial changes for scalability and consistency with
             syslog API.
20aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
03aug04,nee  Removing distinction between LOG_* as functions or macros
             depending on whether its GNU or diab
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
             /main/vdt/base6_itn5_networking-int/1)
03feb04,zhr  Added telnet client to logging categories
27jan04,asr  Added rlogin  & remLib to logging categories
06dec03,niq  Fix compile error with GNU
24nov03,asr  added an include for semLib.h
             moved diab version of LOG_XXXX to applUtilLib.c to get rid of
             warnings
20nov03,niq  osdep.h cleanup
01nov03,asr  Changes to port application logger to RTP
22aug03,niq  Merging from Accordion label ACCORDION_BASE6_MERGE_BASELINE
15jul02,rvr  defined inline functions for LOG_INFO,LOG_ERROR,LOG_WARNING
             and LOG_DEBUG for diab compiler
21may02,ppp  adding taskLib.h for T2 build
21Jan02,ism  change logging macros to remove need for array
18Sep01,ism  written
*/

#ifndef __INCapplUtilLibh
#define __INCapplUtilLibh

/* includes */

#include <stdio.h>      /* for FILE */
#include <limits.h>	/* for INT_MAX */
#include <stdarg.h>
#include <semLib.h>
#include <cfgDefs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

#ifdef _WRS_KERNEL
/* nbioLogLib is not presently supported in RTPs.
 * It may or may not be desired in the kernel.
#define SUPPORT_NBIO_LOG
 */
#endif

#ifdef SUPPORT_NBIO_LOG
#define KERN_LOG_FD	LOG_FD_NBIO
#else
#define KERN_LOG_FD	STD_ERR
#endif

#define LOG_OPT_SHIFT	27
#define LOG_OPT_MASK	(0x1f << LOG_OPT_SHIFT)
#define CAT_SHIFT	3
#define CAT_MASK	((UINT)(-(1 << CAT_SHIFT)) & ~LOG_OPT_MASK)

/* Logging categories */

typedef enum _LOG_CAT_NUM
    {
#undef LOG_DB
#undef LOG_DB_LAST
#define LOG_DB(x, y, z)		x##_LOG_NUM,
#define LOG_DB_LAST(x, y, z)	x##_LOG_NUM,
#include <logCategories.h>
    LOG_NUMCATS
    } LOG_CAT_NUM;

typedef enum _LOG_CAT
    {
#undef LOG_DB
#undef LOG_DB_LAST
#define LOG_DB(x, y, z)		x##_LOG = (x##_LOG_NUM << CAT_SHIFT),
#define LOG_DB_LAST(x, y, z)	x##_LOG = (x##_LOG_NUM << CAT_SHIFT)
#include <logCategories.h>
    } LOG_CAT;

typedef struct categoryInfo
    {
    int fd;
    UINT level;
    } CATEGORY_INFO;

typedef struct _APPL_UTIL_CFG
    {
    CFG_DATA_HDR cfgh;	/* header */
    int fd;		/* default logging file descriptor, all facilities
			   except KERN_LOG */
    UINT level;		/* default logging decoration and level, non-KERN */
    int fdKern;		/* default logging file descriptor for KERN_LOG */
    UINT levelKern;	/* default logging decoration and level, KERN_LOG */
    } APPL_UTIL_CFG;

#ifndef _LOG_DEC_DFLT
#define _LOG_DEC_DFLT	(LOG_DECOR|LOG_LOC)
#endif

#ifndef _LOG_LVL_DFLT
#define _LOG_LVL_DFLT	WARNING_LEVEL
#endif

/* Priority levels */


#define LOG_DEBUG	7 /* Messages containing information normally of use */
			  /* only when debugging */
#define LOG_INFO	6 /* Informational messages */
#define LOG_NOTICE	5 /* Non-error conditions, which may require special */
			  /* handling */
#define LOG_WARNING	4 /* Warning messages */
#define LOG_ERR		3 /* Errors */
#define LOG_CRIT	2 /* Critical conditions, such as hard device errors */
#define LOG_ALERT	1 /* A condition which requires immediate corrective */
			  /* action */
#define LOG_EMERG	0 /* Panic condition. The system is unstable. */


#define	LOG_UPTO(pri)	((1 << ((pri)+1)) - 1)	/* all priorities through pri */

/* Logging levels - convenience values for logging all levels
 * up to a specified level.
 */

#define DEBUG_LEVEL	LOG_UPTO (LOG_DEBUG)
#define INFO_LEVEL	LOG_UPTO (LOG_INFO)
#define NOTICE_LEVEL	LOG_UPTO (LOG_NOTICE)
#define WARNING_LEVEL	LOG_UPTO (LOG_WARNING)
#define ERR_LEVEL	LOG_UPTO (LOG_ERR)
#define ERROR_LEVEL	ERR_LEVEL		/* deprecated */
#define CRIT_LEVEL	LOG_UPTO (LOG_CRIT)
#define ALERT_LEVEL	LOG_UPTO (LOG_ALERT)
#define EMERG_LEVEL	LOG_UPTO (LOG_EMERG)
#define DO_NOT_LOG	0x00

/* We share priority levels (although not level names) with syslog() */

#define LOG_DEBUG_BIT		(1 << LOG_DEBUG)
#define LOG_INFO_BIT		(1 << LOG_INFO)
#define LOG_NOTICE_BIT		(1 << LOG_NOTICE)
#define LOG_WARNING_BIT		(1 << LOG_WARNING)
#define LOG_ERR_BIT		(1 << LOG_ERR)
#define LOG_CRIT_BIT		(1 << LOG_CRIT)
#define LOG_ALERT_BIT		(1 << LOG_ALERT)
#define LOG_EMERG_BIT		(1 << LOG_EMERG)

/*
 * Special bit for compile-time enabling of kernel logging (log(), LOG()).
 * Not really a priority bit.
 */

#define LOG_KERNEL_BIT		0x100

/*
 * These bits may be passed to the logging macros as part of the
 * "category" argument to enable or disable various "decorations"
 * on the log output.
 *
 * These bits are exlusive-or'ed with the corresponding bits set on
 * a per-facility basis using logDecorationSet().
 */

#define LOG_DECOR	(16 <<LOG_OPT_SHIFT)	/* log priority level and
						 * facility
						 */
#define LOG_LOC		(8 << LOG_OPT_SHIFT)	/* log file name or function
						 * and line number
						 */

#ifdef ENABLE_LOG_TIME
#define LOG_TIME	(4 << LOG_OPT_SHIFT)	/* log a timestamp */
#endif
#define LOG_ERRNO	(2 << LOG_OPT_SHIFT)	/* log errno */

/* Fake file descriptor value for non-blocking I/O */

#define LOG_FD_NBIO	INT_MAX

/*
 * In the priority/category argument to _applLog(),
 *
 *  Bits 0 - 2 are the priority
 *  Bits 3 - 27 identify the category (Facility)
 *  Bits 27 - 31 are decoration bits.
 *
 *  Bit 0 is the least significant bit here.
 */

#define PRI_CAT(pri, cat) ((cat) | (pri))

#define LOG_CAT(x) ((UINT32)(x) >> CAT_SHIFT)


/* Constants controlling compile-time enabling of logging levels */

/* Define LOG_ENABLE_MASK as 0 to disable at compile time
 * all application logging.  This might be done if a target platform
 * has no available console or other file to which it can log.
 * Define LOG_ENABLE_MASK as a collection of the LOG_*_BIT values above
 * to enable particular logging levels.
 */

#if !defined (LOG_ENABLE_MASK)

#if FALSE  /* change to TRUE if a logging destination is not available */

#define LOG_ENABLE_MASK (0)

#elif FALSE  /* change to TRUE to do full logging */

#define LOG_ENABLE_MASK (DEBUG_LEVEL | LOG_KERNEL_BIT)

#else

/*
 * The _FREE_VERSION macro indicates a well-tested production
 * system. We assume DEBUG and INFO levels are not of interest
 * here (and should be removed to save space).
 *
 * For size reduction, remove these levels in the default (checked)
 * build as well.
 */
#define LOG_ENABLE_MASK (LOG_NOTICE_BIT | \
			 LOG_WARNING_BIT | \
			 LOG_ERR_BIT | \
			 LOG_CRIT_BIT | \
			 LOG_ALERT_BIT | \
			 LOG_EMERG_BIT | \
			 LOG_KERNEL_BIT)


#endif

#endif /* !defined (LOG_ENABLE_MASK) */

#if __DCC__ || (__GNUCC__ >= 3)
#define C99_VARIADIC_MACROS
#endif

#if (LOG_ENABLE_MASK != 0)

#define APPL_LOGGER_INIT(cat, fd)  applLoggerInit ((cat), (fd))
#define APPL_LOGGER_STOP(cat)  applLoggerStop ((cat))
#define LOG_LEVEL_CHANGE(cat, mask)  logLevelChange ((cat), (mask))
#define LOG_DECORATION_CHANGE(cat, disable, enable) \
    logDecorationChange ((cat), (disable), (enable))
#define LOGGER_INFO_SHOW() loggerInfoShow ()

#ifdef C99_VARIADIC_MACROS
#define _APPL_LOG(cat, file, line, ...) \
    _applLog ((cat), (file), (line), __VA_ARGS__);
#else
#define _APPL_LOG(cat, file, line, fmt...) \
    _applLog ((cat), (file), (line), fmt);
#endif /* C99_VARIADIC_MACROS */

#else  /* (LOG_ENABLE_MASK == 0) */

#define APPL_LOGGER_INIT(cat, fd)  (OK)
#define APPL_LOGGER_STOP(cat)  (OK)
#define LOG_LEVEL_CHANGE(cat, mask)  (OK)
#define LOG_DECORATION_CHANGE(cat, disable, enable) (OK)
#define LOGGER_INFO_SHOW() do {} while (FALSE)

#ifdef C99_VARIADIC_MACROS
#define _APPL_LOG(cat, file, line, ...) do {} while (FALSE)
#else
#define _APPL_LOG(cat, file, line, fmt...) do {} while (FALSE)
#endif /* C99_VARIADIC_MACROS */

#endif /* (LOG_ENABLE_MASK == 0) */


/*
 * A modicum of backwards compatibility:
 */
#define USE_PRINTF     STD_OUT

/* typedefs */

/* variables */

/* function declarations */

STATUS applLoggerInit (int category, int fd);
STATUS applLoggerStop (int category);
STATUS logLevelChange (int category, UINT mask);
UINT logDecorationChange (int category, UINT disableMask, UINT enableMask);
void loggerInfoShow ();
void _applLog (int priCat, const char * file, int line, const char * fmt, ...);


/* These functions are deprecated and should not be used */

#define APPL_LOGGER_DEPRECATED_ROUTINES

#ifdef APPL_LOGGER_DEPRECATED_ROUTINES
int initApplLogger (int category, int fd);
int stopApplLogger (int category);
int changeLogLevel (int category, char level);
void showLoggerInfo ();
#endif /* APPL_LOGGER_DEPRECATED_ROUTINES */

#define GCC_VERSION \
	(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

/* XXX verify exact version numbers for _HAVE__FUNCTION__ and _HAVE__func__ */

#if defined (__GNUC__) || (defined (__DCC__) && __VERSION_NUMBER__ >= 5200)
#define _HAVE__FUNCTION__
#endif

#if (GCC_VERSION >= 30200)
#define _HAVE__func__
#endif

#define LOG_LOC_FILE	0      /* The default */
#define LOG_LOC_FUNC	1
#define LOG_LOC_NONE	2

#if LOG_LOCATION == LOG_LOC_NONE
#define _LOG_LOCATION	NULL, 0
#define _LOC_UNIT	NULL
#elif (LOG_LOCATION == LOG_LOC_FUNC) && defined (_HAVE__func__)
#define	_LOG_LOCATION	__func__, __LINE__
#define _LOC_UNIT	__func__
#elif (LOG_LOCATION == LOG_LOC_FUNC) && defined (_HAVE__FUNCTION__)
#define	_LOG_LOCATION	__FUNCTION__, __LINE__
#define _LOC_UNIT	__FUNCTION__
#else
#define	_LOG_LOCATION	__FILE__, __LINE__
#define _LOC_UNIT	__FILE__
#endif

/*
 * If logging is enabled, but LOG_ARGS is not defined, then
 * logging decoration will be shown, but the specified log string
 * and its variable arguments will not.
 * This decreases space requirements while still providing
 * logging information sufficient to locate code logging errors.
 */

#ifndef LOG_ARGS
#define LOG_ARGS	1
#endif


/*
 * These macros provide the logging interface used by the VxWorks
 * applications. Each macro takes a category, which identifies which
 * application has made the call, and also a control string and multiple
 * arguments, which are in exactly the same format as printf().
 *
 * For each macro the current logging level of the specified category is
 * compared to the level that the macro name implies. If the current logging
 * level for the application is greater than or equal to the macro level
 * then the message will be logged, if it is not then the message will
 * be discarded. For example, if the current logging level of an application
 * is INFO_LEVEL then all the logging calls in that application will
 * succeed except the logging calls made using LOG_DEBUG.
 *
 */

#ifdef C99_VARIADIC_MACROS

#if (LOG_ENABLE_MASK & LOG_DEBUG_BIT)
#if LOG_ARGS
#define log_debug(cat, ...)					 \
    do  {							 \
	_applLog (PRI_CAT (LOG_DEBUG, cat), _LOG_LOCATION,     	 \
	      __VA_ARGS__);					 \
	} while (FALSE)
#else
#define log_debug(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_DEBUG, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_debug(cat, ...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_INFO_BIT)
#if LOG_ARGS
#define log_info(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_INFO, cat), _LOG_LOCATION,     	\
	      __VA_ARGS__);					\
	} while (FALSE)
#else
#define log_info(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_INFO, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_info(cat, ...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_NOTICE_BIT)
#if LOG_ARGS
#define log_notice(cat, ...)					  \
    do  {							  \
	_applLog (PRI_CAT (LOG_NOTICE, cat), _LOG_LOCATION,       \
	      __VA_ARGS__);					  \
	} while (FALSE)
#else
#define log_notice(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_NOTICE, cat), _LOG_LOCATION, "");\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_notice(cat, ...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_WARNING_BIT)
#if LOG_ARGS
#define log_warning(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_WARNING, cat), _LOG_LOCATION,	\
	      __VA_ARGS__);					\
	} while (FALSE)
#else
#define log_warning(cat, ...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_WARNING, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_warning(cat, ...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_ERR_BIT)
#if LOG_ARGS
#define log_err(cat, ...)					 \
    do  {							 \
	_applLog (PRI_CAT (LOG_ERR, cat), _LOG_LOCATION,     	 \
	      __VA_ARGS__);					 \
	} while (FALSE)
#else
#define log_err(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_ERR, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_err(cat, ...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_CRIT_BIT)
#if LOG_ARGS
#define log_crit(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_CRIT, cat), _LOG_LOCATION,     	\
	      __VA_ARGS__);					\
	} while (FALSE)
#else
#define log_crit(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_CRIT, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_crit(cat, ...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_ALERT_BIT)
#if LOG_ARGS
#define log_alert(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_ALERT, cat), _LOG_LOCATION,     	\
	      __VA_ARGS__);					\
	} while (FALSE)
#else
#define log_alert(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_ALERT, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_alert(cat, ...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_EMERG_BIT)
#if LOG_ARGS
#define log_emerg(cat, ...)					 \
    do  {							 \
	_applLog (PRI_CAT (LOG_EMERG, cat), _LOG_LOCATION,     	 \
	      __VA_ARGS__);					 \
	} while (FALSE)
#else
#define log_emerg(cat, ...)					\
    do  {							\
	_applLog (PRI_CAT (LOG_EMERG, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_emerg(cat, ...) do {} while (FALSE)
#endif

#else  /* !defined (C99_VARIADIC_MACROS) -> assume old GNU variadic syntax */

#if (LOG_ENABLE_MASK & LOG_DEBUG_BIT)
#if LOG_ARGS
#define log_debug(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_DEBUG, cat), _LOG_LOCATION, fmt);	\
	} while (FALSE)
#else
#define log_debug(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_DEBUG, cat), _LOG_LOCATION, "");		\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_debug(cat, fmt...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_INFO_BIT)
#if LOG_ARGS
#define log_info(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_INFO, cat), _LOG_LOCATION, fmt);		\
	} while (FALSE)
#else
#define log_info(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_INFO, cat), _LOG_LOCATION, "");		\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_info(cat, fmt...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_NOTICE_BIT)
#if LOG_ARGS
#define log_notice(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_NOTICE, cat), _LOG_LOCATION, fmt);	\
	} while (FALSE)
#else
#define log_notice(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_NOTICE, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_notice(cat, fmt...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_WARNING_BIT)
#if LOG_ARGS
#define log_warning(cat, fmt...)					\
    do  {								\
	_applLog (PRI_CAT (LOG_WARNING, cat), _LOG_LOCATION, fmt);	\
	} while (FALSE)
#else
#define log_warning(cat, fmt...)					\
    do  {								\
	_applLog (PRI_CAT (LOG_WARNING, cat), _LOG_LOCATION, "");	\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_warning(cat, fmt...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_ERR_BIT)
#if LOG_ARGS
#define log_err(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_ERR, cat), _LOG_LOCATION, fmt);		\
	} while (FALSE)
#else
#define log_err(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_ERR, cat), _LOG_LOCATION, "");		\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_err(cat, fmt...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_CRIT_BIT)
#if LOG_ARGS
#define log_crit(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_CRIT, cat), _LOG_LOCATION, fmt);		\
	} while (FALSE)
#else
#define log_crit(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_CRIT, cat), _LOG_LOCATION, "");		\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_crit(cat, fmt...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_ALERT_BIT)
#if LOG_ARGS
#define log_alert(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_ALERT, cat), _LOG_LOCATION, fmt);	\
	} while (FALSE)
#else
#define log_alert(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_ALERT, cat), _LOG_LOCATION, "");		\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_alert(cat, fmt...) do {} while (FALSE)
#endif

#if (LOG_ENABLE_MASK & LOG_EMERG_BIT)
#if LOG_ARGS
#define log_emerg(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_EMERG, cat), _LOG_LOCATION, fmt);	\
	} while (FALSE)
#else
#define log_emerg(cat, fmt...)						\
    do  {								\
	_applLog (PRI_CAT (LOG_EMERG, cat), _LOG_LOCATION, "");		\
	} while (FALSE)
#endif /* LOG_ARGS */
#else
#define log_emerg(cat, fmt...) do {} while (FALSE)
#endif

#endif /* !defined (C99_VARIADIC_MACROS) */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCapplUtilLibh */
