/*	Definition module : unwind.h

	Copyright 2010 Wind River Systems

	Description :
	C++ ABI compatible interface to frame unwinder

	History :
	When	Who	What
	100617	salim	initial
*/

/* TODO
 + Move uint64 definition elsewhere [TODO]
 */
#ifndef D_unwind
#define D_unwind

#ifdef __cplusplus
extern "C" {
#endif

#if __UNWIND_API_HIDE
/* Until we have a GCC compatible unwinding library, compile with
   -Xunwind-api-hide to use non-standard names for the _Unwind functions */

/* This prefix must agree with the one in
   comp/src/common/cxa_eh.cc:unwind_resume_routine */
#define __hide(x) __diab##x

#define _Unwind_GetIP __hide(_Unwind_GetIP)
#define _Unwind_SetIP __hide(_Unwind_SetIP)
#define _Unwind_GetLanguageSpecificData __hide(_Unwind_GetLanguageSpecificData)
#define _Unwind_GetRegionStart __hide(_Unwind_GetRegionStart)
#define _Unwind_GetGR __hide(_Unwind_GetGR)
#define _Unwind_SetGR __hide(_Unwind_SetGR)
#define _Unwind_RaiseException __hide(_Unwind_RaiseException)
#define _Unwind_Resume __hide(_Unwind_Resume)

/* The following are not part of the Standard _Unwind API so there is no
  danger of conflicts, but we use the same naming convention for
  consistency */
#define _Unwind_SetArg1 __hide(_Unwind_SetArg1)
#define _Unwind_SetArg2 __hide(_Unwind_SetArg2)
#define _Unwind_ExtendAddress __hide(_Unwind_ExtendAddress)
#endif

typedef int                int32;
typedef unsigned int       uint32;
typedef long long          int64;
typedef unsigned long long uint64;

/* _Unwind_Ptr is not defined by the C++ ABI. Values that are conceptually
   pointers returned by GetIP, GetLanguageSpecificData and GetRegionStart
   are uint64 in that ABI, presumably because it is target to IA64. 

   In this implementation we use _Unwind_Ptr instead of uint64 in such cases.

   I don't think this is an ABI violation because all linked code is suppose
   to use one set of unwind routines and is not supposed to peek into the
   data structures.
*/
typedef const char * _Unwind_Ptr;
	
/* _Unwind_Reg is not defined by the C++ ABI. We use it for _Unwind_GetGR
   and _Unwind_SetGR instead of uint64. See _Unwind_Ptr discussion
   above. */
#if defined(__MIPS64BIT__) /* TODO && ILP64 */
typedef unsigned long long _Unwind_Reg;
#else
typedef unsigned long _Unwind_Reg;
#endif

typedef enum {
	_URC_NO_REASON = 0,
	_URC_FOREIGN_EXCEPTION_CAUGHT = 1,
	_URC_FATAL_PHASE2_ERROR = 2,
	_URC_FATAL_PHASE1_ERROR = 3,
	_URC_NORMAL_STOP = 4,
	_URC_END_OF_STACK = 5,
	_URC_HANDLER_FOUND = 6,
	_URC_INSTALL_CONTEXT = 7,
	_URC_CONTINUE_UNWIND = 8
} _Unwind_Reason_Code;

struct _Unwind_Exception;
struct _Unwind_Context;

typedef void (*_Unwind_Exception_Cleanup_Fn)
	(_Unwind_Reason_Code reason,
	 struct _Unwind_Exception *exc);
	
/*
  Alignment:
  The user exception object follows the _Unwind_Exception header (which for
  C++ is wrapped in a __cxa_exception header). The header is allocated with
  malloc; in order for the object to be properly aligned the header must be
  maximally aligned.

  In addition to simplify pointer adjustments between either header and the
  object itself, there should be no tail padding between the end of the
  _Unwind_Exception and the end of the enclosing language specific
  header. 

  We solve both problems by giving the _Unwind_Exception struct an
  alignment of 16. Maximal alignment varies across targets but fixing the
  alignment to 16 produces a layout that is compatible with GCC (verified
  on 32 bit X86) and will work for all current and projected supported
  targets.

  The X86_64_ABI only says that an _Unwind_Exception should be 8 byte
  aligned. In fact if it is 8 byte aligned then (on both IP32 and LP64
  targets) both the C++ language header and _Unwind_Exception will actually
  be 16 byte aligned (assuming the memory returned from malloc is 16 byte
  aligned). We explicitly use 16 below to make it clear that it will work
  on targets that have 16 byte aligned native types (Altivec).

  [TODO - What happens if a user defines a class with
  __attribute__((aligned)) to have an alignment > 16?]
 */
struct _Unwind_Exception {
	uint64			     exception_class;
	_Unwind_Exception_Cleanup_Fn exception_cleanup;
	uint64		     private_1;
	uint64		     private_2;
} __attribute__((aligned(16)));


_Unwind_Reason_Code _Unwind_RaiseException(struct _Unwind_Exception *exception_object);
void _Unwind_Resume(struct _Unwind_Exception * exception_object);

/* TODO: ABI example code uses static const, but does static const work as efficiently as enum in C too?
 */
typedef int _Unwind_Action;
enum {
	_UA_SEARCH_PHASE = 1,
	_UA_CLEANUP_PHASE = 2,
	_UA_HANDLER_FRAME = 4,
	_UA_FORCE_UNWIND = 8
};

typedef _Unwind_Reason_Code
(*_Unwind_Personality_Routine)(int version,
				_Unwind_Action actions,
				uint64 exceptionClass,
				struct _Unwind_Exception *exceptionObject,
				struct _Unwind_Context *context);

_Unwind_Ptr _Unwind_GetIP(struct _Unwind_Context * context);
void _Unwind_SetIP(struct _Unwind_Context * context, _Unwind_Ptr value);
_Unwind_Ptr _Unwind_GetLanguageSpecificData(struct _Unwind_Context * context);
_Unwind_Ptr _Unwind_GetRegionStart(struct _Unwind_Context * context);

_Unwind_Reg _Unwind_GetGR(struct _Unwind_Context *context, int index);
void _Unwind_SetGR(struct _Unwind_Context *context, int index, _Unwind_Reg value);

/* These are Diab extensions which are useful for passing args to landing
   pads */
void _Unwind_SetArg1(struct _Unwind_Context * context, _Unwind_Reg value);

/* Note that this is not implemented for all architectures; in those cases
   it is a no-op. The exception handling runtime provides an alternative
   way to get arg2 by calling a function. */
void _Unwind_SetArg2(struct _Unwind_Context * context, _Unwind_Reg value);

/* Use this to get the value to pass to _Unwind_SetGR/Arg1/Arg2 when the
   value is an address */
 _Unwind_Reg _Unwind_ExtendAddress(_Unwind_Ptr address);

#ifdef __cplusplus
}
#endif

#endif /* D_unwind */
