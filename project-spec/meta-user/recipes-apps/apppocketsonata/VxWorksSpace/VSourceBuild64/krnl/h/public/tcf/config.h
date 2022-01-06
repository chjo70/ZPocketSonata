/*******************************************************************************
 * Copyright (c) 2007, 2013-2016 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 * You may elect to redistribute this code under either of these licenses.
 *
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

/*
 * This file contains "define" statements that control agent configuration.
 * SERVICE_* definitions control which service implementations are included into the agent.
 */

#ifndef D_config
#define D_config
#include <tcf/wr-renameconfig.h>
#include <tcf/framework/mdep.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#  define TARGET_WINDOWS    1
#  define TARGET_VXWORKS    0
#  define TARGET_UNIX       0
#  if defined(_MSC_VER)
#    define TARGET_MSVC     1
#  else
#    define TARGET_MSVC     0
#  endif
#  define TARGET_BSD        0
#  define TARGET_SYMBIAN    0
#elif defined(_WRS_KERNEL)
#  define TARGET_WINDOWS    0
#  define TARGET_VXWORKS    1
#  define TARGET_UNIX       0
#  define TARGET_MSVC       0
#  define TARGET_BSD        0
#  define TARGET_SYMBIAN    0
#elif defined(__SYMBIAN32__)
#  define TARGET_WINDOWS    0
#  define TARGET_VXWORKS    0
#  define TARGET_UNIX       0
#  define TARGET_MSVC       0
#  define TARGET_BSD        0
#  define TARGET_SYMBIAN    1
#else
#  define TARGET_WINDOWS    0
#  define TARGET_VXWORKS    0
#  define TARGET_UNIX       1
#  define TARGET_MSVC       0
#  if defined(__FreeBSD__) || defined(__NetBSD__)
#    define TARGET_BSD      1
#  else
#    define TARGET_BSD      0
#  endif
#  define TARGET_SYMBIAN    0
#endif

#if !defined(SERVICE_Locator)
#define SERVICE_Locator         (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS || TARGET_SYMBIAN)
#endif
#if !defined(SERVICE_RunControl)
#define SERVICE_RunControl      (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_Breakpoints)
#define SERVICE_Breakpoints     (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_Memory)
#define SERVICE_Memory          (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_Registers)
#define SERVICE_Registers       (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_Processes)
#define SERVICE_Processes       (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_MemoryMap)
#define SERVICE_MemoryMap       (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_StackTrace)
#define SERVICE_StackTrace      (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_Symbols)
#define SERVICE_Symbols         (TARGET_UNIX || TARGET_MSVC)
#endif
#if !defined(SERVICE_LineNumbers)
#define SERVICE_LineNumbers     (TARGET_UNIX || TARGET_MSVC)
#endif
#if !defined(SERVICE_FileSystem)
#define SERVICE_FileSystem      (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_SysMonitor)
#define SERVICE_SysMonitor      ((TARGET_UNIX && !TARGET_BSD) || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_Expressions)
#define SERVICE_Expressions     (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_Streams)
#define SERVICE_Streams         (TARGET_UNIX || TARGET_VXWORKS || TARGET_WINDOWS || TARGET_SYMBIAN)
#endif
#if !defined(SERVICE_PathMap)
#define SERVICE_PathMap         1
#endif
#if !defined(SERVICE_ContextQuery)
#define SERVICE_ContextQuery    1
#endif
#if !defined(SERVICE_Terminals)
#define SERVICE_Terminals       (TARGET_UNIX || TARGET_WINDOWS)
#endif
#if !defined(SERVICE_DPrintf)
#define SERVICE_DPrintf         (SERVICE_Expressions && SERVICE_Streams)
#endif
#if !defined(SERVICE_Disassembly)
#define SERVICE_Disassembly     (SERVICE_Memory)
#endif
#if !defined(SERVICE_Profiler)
#define SERVICE_Profiler        (SERVICE_RunControl)
#endif

#if !defined(ENABLE_Plugins)
#  if TARGET_UNIX && defined(PATH_Plugins)
#    define ENABLE_Plugins      1
#  else
#    define ENABLE_Plugins      0
#  endif
#endif

#if !defined(ENABLE_ZeroCopy)
#define ENABLE_ZeroCopy         1
#endif

#if !defined(ENABLE_Splice)
#  if ENABLE_ZeroCopy
#    include <fcntl.h>
#    if defined(SPLICE_F_MOVE)
#      define ENABLE_Splice       1
#    else
#      define ENABLE_Splice       0
#    endif
#  else
#    define ENABLE_Splice       0
#  endif
#endif

#if !defined(ENABLE_Trace)
#  define ENABLE_Trace          1
#endif

#if defined(_WRS_CONFIG_TCF_DISABLE_DISCOVERY)
#   if !defined(ENABLE_Discovery)
#     define ENABLE_Discovery      0
#   endif
#else
#   if !defined(ENABLE_Discovery)
#     define ENABLE_Discovery      1
#   endif
#endif

#if !defined(ENABLE_Cmdline)
#  define ENABLE_Cmdline        1
#endif

#if !defined(ENABLE_ContextProxy)
#  define ENABLE_ContextProxy   0
#endif

#if !defined(ENABLE_ContextMux)
#  define ENABLE_ContextMux     0
#endif

#if !defined(ENABLE_DebugContext)
#  define ENABLE_DebugContext   (ENABLE_ContextProxy || ENABLE_ContextMux || SERVICE_RunControl || SERVICE_Breakpoints || \
        SERVICE_Memory || SERVICE_Registers || SERVICE_StackTrace || SERVICE_Disassembly)
#endif

#if !defined(ENABLE_SymbolsProxy)
#  define ENABLE_SymbolsProxy   (ENABLE_DebugContext && TARGET_VXWORKS)
#endif

#if !defined(ENABLE_LineNumbersProxy)
#  define ENABLE_LineNumbersProxy (ENABLE_DebugContext && TARGET_VXWORKS)
#endif

#if !defined(ENABLE_MemoryMap)
#  define ENABLE_MemoryMap      ((ENABLE_DebugContext && ENABLE_ContextProxy) || SERVICE_MemoryMap)
#endif

#if ENABLE_SymbolsProxy || !ENABLE_DebugContext
#  undef SERVICE_Symbols
#  define SERVICE_Symbols       0
#endif

#if ENABLE_LineNumbersProxy || !ENABLE_DebugContext
#  undef SERVICE_LineNumbers
#  define SERVICE_LineNumbers    0
#endif

#if !defined(ENABLE_Symbols)
#  define ENABLE_Symbols        (ENABLE_SymbolsProxy || SERVICE_Symbols)
#endif

#if !defined(ENABLE_LineNumbers)
#  define ENABLE_LineNumbers    (ENABLE_LineNumbersProxy || SERVICE_LineNumbers)
#endif

#if !defined(ENABLE_ELF)
#  define ENABLE_ELF            (TARGET_UNIX && (SERVICE_Symbols || SERVICE_LineNumbers))
#endif

#if !defined(ENABLE_PE)
#  define ENABLE_PE             (TARGET_MSVC && (SERVICE_Symbols || SERVICE_LineNumbers))
#endif

#if !defined(ENABLE_SymbolsMux)
#define ENABLE_SymbolsMux   0
#endif

#if !defined(ENABLE_LineNumbersMux)
#define ENABLE_LineNumbersMux   0
#endif

#if !defined(ENABLE_SSL)
#  if defined(PATH_OpenSSL)
#    define ENABLE_SSL          1
#  elif (TARGET_UNIX) && !defined(__APPLE__)
#    define ENABLE_SSL          1
#  else
#    define ENABLE_SSL          0
#  endif
#endif

#if !defined(ENABLE_RCBP_TEST)
#  if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__APPLE__)
/* TODO: debug services are not fully implemented on BSD */
#    define ENABLE_RCBP_TEST    0
#  else
#    define ENABLE_RCBP_TEST    (!ENABLE_ContextProxy && (SERVICE_RunControl && SERVICE_Breakpoints))
#  endif
#endif

#if !defined(ENABLE_AIO)
#  if !defined(_POSIX_ASYNCHRONOUS_IO)
#    define ENABLE_AIO          0
#  elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__APPLE__)
/* On BSD AIO sends signal SIGSYS - bad system call */
#    define ENABLE_AIO          0
#  elif defined(__linux__)
/* Linux implementation of POSIX AIO found to be inefficient */
#    define ENABLE_AIO          0
#  elif TARGET_SYMBIAN
/* Symbian impl (OpenC) not desired either */
#    define ENABLE_AIO          0
#  else
#    define ENABLE_AIO          1
#  endif
#endif

#if !defined(ENABLE_STREAM_MACROS)
/* Enabling stream macros increases code size about 5%, and increases speed about 7% */
#  define ENABLE_STREAM_MACROS  0
#endif

#if !defined(ENABLE_LUA)
#  if defined(PATH_LUA)
#    define ENABLE_LUA          1
#  else
#    define ENABLE_LUA          0
#  endif
#endif

#if !defined(ENABLE_Unix_Domain)
/* Using UNIX:/path/to/socket for local TCP communication */
#  define ENABLE_Unix_Domain    (TARGET_UNIX || TARGET_SYMBIAN)
#endif

#if !defined(ENABLE_ContextExtraProperties)
#  define ENABLE_ContextExtraProperties 0
#endif

#if !defined(ENABLE_ContextStateProperties)
#  define ENABLE_ContextStateProperties 0
#endif

#if !defined(ENABLE_ContextBreakpointCapabilities)
#  define ENABLE_ContextBreakpointCapabilities (TARGET_WINDOWS && ENABLE_DebugContext && !ENABLE_ContextProxy)
#endif

#if !defined(ENABLE_ExtendedBreakpointStatus)
#  define ENABLE_ExtendedBreakpointStatus (TARGET_WINDOWS && ENABLE_DebugContext && !ENABLE_ContextProxy)
#endif

#if !defined(ENABLE_ExtendedMemoryErrorReports)
#  define ENABLE_ExtendedMemoryErrorReports 1
#endif

#if !defined(ENABLE_MemoryAccessModes)
#  define ENABLE_MemoryAccessModes 1
#endif

#if !defined(ENABLE_ExternalStackcrawl)
#  define ENABLE_ExternalStackcrawl 0
#endif

#if !defined(ENABLE_StackCrawlMux)
#  define ENABLE_StackCrawlMux 0
#endif

#if !defined(ENABLE_WR_SymbolsListProxy)
#  define ENABLE_WR_SymbolsListProxy 1
#endif

#if !defined(ENABLE_WR_LivePatchProxy)
#  define ENABLE_WR_LivePatchProxy 0
#endif

#if !defined(ENABLE_ContextISA)
#  define ENABLE_ContextISA SERVICE_Disassembly
#endif

#if !defined(ENABLE_ProfilerSST)
#  define ENABLE_ProfilerSST (SERVICE_Profiler && SERVICE_RunControl && SERVICE_StackTrace && \
      ENABLE_DebugContext && !ENABLE_ContextProxy)
#endif

#if !defined(ENABLE_SkipPrologueWhenPlanting)
#define ENABLE_SkipPrologueWhenPlanting         1
#endif

#if !defined(ENABLE_WR_LivePatch)
#if (_WRS_VXWORKS_MAJOR < 7)
#define ENABLE_WR_LivePatch     0
#else
#define ENABLE_WR_LivePatch     1
#endif
#endif

#ifdef _WRS_CONFIG_HAC_AGENT
#if defined(SERVICE_Profiler)
#undef SERVICE_Profiler
#endif
#define SERVICE_Profiler         1

#if !defined(ENABLE_ProfilerSPY)
#define ENABLE_ProfilerSPY         1
#endif

#if !defined(ENABLE_AllStopMode)
#  define ENABLE_AllStopMode 1
#endif
#endif

#endif /* D_config */
