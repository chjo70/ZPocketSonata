/* sysctl.h - sysctl definitions */

/*
 * Copyright (c) 2004-2007, 2009, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Karels at Berkeley Software Design, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)sysctl.h	8.1 (Berkeley) 6/2/93
 * $FreeBSD: src/sys/sys/sysctl.h,v 1.81.2.6 2001/05/17 17:59:53 ru Exp $
 */

/*
modification history
--------------------
02i,07oct13,h_k  removed netVersion.h header inclusion.
02h,27may10,pad  Moved extern C statement after include statements.
02g,16nov09,jpb  Updated SYCTL_ACCESS struct to take 64-bit regs.
02f,24mar09,dlk  Cast CTLFLAG_RD value as an int to avoid signedness warnings.
02e,08jun07,pad  Slightly changed the definition of SYSCTL_ADD_OID so that this
		 public macro and other SYSCTL_ADD_xxx macros can be used by
		 customers. Altered the definition of SYSCTL_OID and 
		 SYSCTLN_OID accordingly.
02d,22may07,pad  Defined _FREE_VERSION for better performances.
02c,05jan07,kch  Removed the obsolete coreip virtual stack references.
02b,06dec06,tkf  Add CTLFLAG_FOREIGN flag for IPNET integration.
02a,26aug05,kk   update prototypes to not use C++ keyword new (SPR# 110779)
01z,11apr05,wap  Reorganize things so that CTL_MAXNAME is visible to RTPs (SPR
                 #106195)
01y,07feb05,vvv  _KERNEL cleanup
01x,31jan05,niq  virtual stack changes for sysctl
01w,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01v,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5-int/1)
01u,24feb04,vvv  updated based on review comments
01t,20feb04,vvv  added support for transparent nodes
01t,23feb04,kkz  added #defines for remlib
01t,12feb04,asr  added new defines for loginLib
01s,24nov03,vvv  added include for logLib.h
01r,20nov03,niq  Remove copyright_wrs.h file inclusion
01q,20nov03,vvv  updated for RTP support
01p,05nov03,cdw  Removal of unnecessary _KERNEL guards.
01o,04nov03,rlm  Ran batch header path update for header re-org.
01n,03nov03,rlm  Removed wrn/coreip/ prefix from #includes for header re-org.
01m,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01l,10jun03,vvv  include netVersion.h
01k,14may03,vvv  made sysctlbyname() available when _KERNEL is not defined
01j,11apr03,syy  Fixed Diab compiler warnings
01i,10mar03,ann  removed the preceding ## from the macros.
01h,09sep02,hsh  add c++ protection
01g,18mar02,ann  adding the prototype for sysctlnametomib
01f,11mar02,ann  fixing compilation warnings
01e,22feb02,ham  changed for tornado build.
01d,21feb02,ann  removed the references to MGMT_LOCK
01c,10jan02,ann  adding the prototype for sysctl
01b,12dec01,ann  corrected the LOG message in SYSCTL_NODE_CHILDREN
01a,05dec01,niq  Created from BSD 4.3
*/

#ifndef _SYS_SYSCTL_H_
#define	_SYS_SYSCTL_H_

#include <sys/queue.h>
#ifdef _WRS_KERNEL
#include <logLib.h>
#endif

/*
 * Definitions for sysctl call.  The sysctl call uses a hierarchical name
 * for objects that can be examined or modified.  The name is expressed as
 * a sequence of integers.  Like a file path name, the meaning of each
 * component depends on its place in the hierarchy.  The top-level and kern
 * identifiers are defined here, and other identifiers are defined in the
 * respective subsystem header files.
 */

#include <sys/sysctlCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Each subsystem defined by sysctl defines a list of variables
 * for that subsystem. Each name is either a node with further
 * levels defined below it, or it is a leaf of some particular
 * type given below. Each sysctl level defines a set of name/type
 * pairs to be used by sysctl(1) in manipulating the subsystem.
 */
struct ctlname {
	char	*ctl_name;	/* subsystem name */
	int	ctl_type;	/* type of name */
};

#define CTLTYPE         0xf     /* Mask for the type */
#define CTLTYPE_NODE    1       /* name is a node */
#define CTLTYPE_INT     2       /* name describes an integer */
#define CTLTYPE_STRING  3       /* name describes a string */
#define CTLTYPE_QUAD    4       /* name describes a 64-bit number */
#define CTLTYPE_OPAQUE  5       /* name describes a structure */
#define CTLTYPE_STRUCT  CTLTYPE_OPAQUE  /* name describes a structure */
#define CTLTYPE_UINT    6       /* name describes an unsigned integer */
#define CTLTYPE_LONG    7       /* name describes a long */
#define CTLTYPE_ULONG   8       /* name describes an unsigned long */

/*
 * The cast indicates to the compiler that we want CTLFLAG_RD
 * to be an int value, even though it is written as a positive
 * constant greater than INT_MAX and would be negative if cast
 * as an int.  That eliminates some warnings.
 * If starting from scratch we would probably use an unsigned integer type
 * for the 'kind' arguments containing these flags, and U on the constants.
 */
#define CTLFLAG_RD	((int)0x80000000) /* Allow reads of variable */
#define CTLFLAG_WR	0x40000000	/* Allow writes to the variable */
#define CTLFLAG_RW	(CTLFLAG_RD|CTLFLAG_WR)
#define CTLFLAG_NOLOCK	0x20000000	/* XXX Don't Lock. Unsupported */
#define CTLFLAG_ANYBODY	0x10000000	/* All users can set this var.
					   Unsupported */
#define CTLFLAG_SECURE	0x08000000	/* Permit set only if securelevel<=0.
					   Unsupported */
#define CTLFLAG_PRISON	0x04000000	/* Prisoned roots can fiddle.
					   Unsupported */
#define CTLFLAG_DYN	0x02000000	/* Dynamic oid - can be freed */
#define CTLFLAG_TRANSP	0x01000000	/* Treat node as transparent although */
#define CTLFLAG_FOREIGN 0x00800000  /* name is a node with a handler and
                                       sits on a foreign sysctl subtree */

/*
 * A node is transparent if it has no handler, or if CTLFLAG_TRANSP is set.
 * The following macro assumes that oidp points to a node. When CTLFLAG_TRANSP
 * is set, the handler is in fact an entry/exit handler. Its arguments are used
 * as follows (see SYSCTL_HANDLER_ARGS):
 *
 *  oidp    points to the struct sysctl_oid as usual. On exit, this is
 *          the same (original) oid pointer as passed on entry.
 *  arg1    points to a transpHandlerData structure which contains two pointers:
 *          - a (struct sysctl_oid_list *) variable where a pointer to the oid's
 *            child list is returned. This variable is initialized to oidp->arg1,
 *            so if there is no child-list swizzling, nothing needs to be done with
 *            this by the entry handler.
 *          - a void pointer (pCtx) which can be used by the handler to store
 *            some status information when invoked as an entry handler which can
 *            be used later when it is called in exit mode.
 *  arg2    TRUE on entry, FALSE on exit. The entry/exit handler is always
 *          called with FALSE after being called with TRUE, as the code
 *          proceeds deeper into and then back out of the sysctl tree.
 *  req     The sysctl_req structure, as usual.
 *
 * The handler is called with arg2 TRUE when code is about to descend
 * past the transparent node to get its child list.
 */

#define NODE_TRANSPARENT(oidp) (((oidp)->oid_handler == 0) || \
                                (((oidp)->oid_kind & CTLFLAG_TRANSP) != 0))


/*
 * USE THIS instead of a hardwired number from the categories below
 * to get dynamically assigned sysctl entries using the linker-set
 * technology. This is the way nearly all new sysctl variables should
 * be implemented.
 * e.g. SYSCTL_INT(_parent, OID_AUTO, name, CTLFLAG_RW, &variable, 0, "");
 */ 
#define OID_AUTO	(-1)

#define SYSCTL_HANDLER_ARGS struct sysctl_oid *oidp, void *arg1, int arg2, \
	struct sysctl_req *req

/*
 * This structure is used to pass data to the transparent node handler (entry/exit).
 * It is passed in arg1. pArg1 contains the child list. pCtx can be used by the
 * handler to store some context on entry which can then be retrieved on exit.
 * For example, the handler for the "net" node (netSysctlHandler) uses pCtx to
 * store the splnet status on entry which is then used by splx when the exit
 * handler is called.
 */

struct transpHandlerData
    {
    struct sysctl_oid_list ** pArg1;
    void * pCtx;
    };

/* supports transparent nodes with entry/exit handlers */

struct sysctlTranspData
    {
    struct sysctl_oid *pStack [CTL_MAXNAME];    /* stores the oid for each */
						/* transparent node. */
    void *pCtx [CTL_MAXNAME];                   /* stores the context, if any, */
						/* for the entry/exit handler  */
    };

/*
 * This describes the access space for a sysctl request.  This is needed
 * so that we can use the interface from the kernel or from user-space.
 */
struct sysctl_req {
	struct proc	*p;
	void		*oldptr;
	size_t		oldlen;
	size_t		oldidx;
	int		(*oldfunc)(struct sysctl_req *, const void *, size_t);
	void		*newptr;
	size_t		newlen;
	size_t		newidx;
	int		(*newfunc)(struct sysctl_req *, void *, size_t);

        /* supports transparent nodes with entry/exit handlers */

        struct sysctlTranspData transpData;
};

/*
 * Let's define the sysctl_oid_list stucture as a single-linked list of
 * sysctl_oid structures.
 */

SLIST_HEAD(sysctl_oid_list, sysctl_oid);

/*
 * This describes one "oid" in the MIB tree.  Potentially more nodes can
 * be hidden behind it, expanded by the handler.
 */
struct sysctl_oid {
	struct sysctl_oid_list *oid_parent;
	SLIST_ENTRY(sysctl_oid) oid_link;
	int		oid_number;
	int		oid_kind;
	void		*oid_arg1;
	int		oid_arg2;
	int		oid_refcnt;
	const char	*oid_name;
	int 		(*oid_handler)(SYSCTL_HANDLER_ARGS);
	const char	*oid_fmt;
};

#define SYSCTL_IN(r, p, l) (r->newfunc)(r, p, l)
#define SYSCTL_OUT(r, p, l) (r->oldfunc)(r, p, l)

int sysctl_handle_int(SYSCTL_HANDLER_ARGS);
int sysctl_handle_long(SYSCTL_HANDLER_ARGS);
int sysctl_handle_intptr(SYSCTL_HANDLER_ARGS);
int sysctl_handle_string(SYSCTL_HANDLER_ARGS);
int sysctl_handle_opaque(SYSCTL_HANDLER_ARGS);

/*
 * These functions are used to add/remove an oid from the mib.
 */
STATUS sysctl_register_oid(struct sysctl_oid *oidp);
void sysctl_unregister_oid(struct sysctl_oid *oidp);

#if FALSE	/* unsupported still */
#define SYSCTL_DECL(name)
#endif

/* Declare the pointer to the oid of a node */
#define SYSCTL_DECL_NODE(name)                                    \
        struct sysctl_oid * name##_node = 0

/* 
 * Declare the pointer to the oid of a node registered in another module 
 * as extern 
 */
#define SYSCTL_DECL_NODE_EXT(name)                                \
        extern struct sysctl_oid * name##_node

/* Hide these in macros */
#define	SYSCTL_CHILDREN(oid_ptr) (struct sysctl_oid_list *)((oid_ptr)->oid_arg1)
#if FALSE	/* unsupported still */
#define	SYSCTL_STATIC_CHILDREN(oid_name)
#endif

#define _FREE_VERSION	/* let's not use the debug version by default */

#ifdef _FREE_VERSION

#define	SYSCTL_NODE_CHILDREN(name) \
    ((struct sysctl_oid_list *) (name##_node)->oid_arg1)

#else  /* ! _FREE_VERSION */

#define	SYSCTL_NODE_CHILDREN(name) \
    _sysctlDbgNodeChildren (name##_node, __FILE__, __LINE__, #name)

#endif /* ! _FREE_VERSION */

/* === Structs and macros related to context handling === */

/* All dynamically created sysctls can be tracked in a context list. */
struct sysctl_ctx_entry {
	struct sysctl_oid *entry; 
	TAILQ_ENTRY(sysctl_ctx_entry) link;
};

TAILQ_HEAD(sysctl_ctx_list, sysctl_ctx_entry);

IMPORT struct sysctl_ctx_list * pNetSysctlCtxList;
IMPORT struct sysctl_ctx_list * pSysctlCtxList;

/* This constructs a "raw" MIB oid. These two macros are not user-callable */

#define SYSCTL_OID(parent, nbr, name, kind, a1, a2, handler, fmt, descr) \
	SYSCTL_ADD_OID(pSysctlCtxList, SYSCTL_NODE_CHILDREN(parent), nbr, \
		       #name, kind, a1, a2, handler, fmt, descr)

#define SYSCTLN_OID(parent, nbr, name, kind, a1, a2, handler, fmt, descr) \
	SYSCTL_ADD_OID(pNetSysctlCtxList, SYSCTL_NODE_CHILDREN(parent), nbr, \
		       #name, kind, a1, a2, handler, fmt, descr)

/*
 * The SYSCTLN_TOP_NODE macro is used to install a top level child
 * node in the 'net' node (parent should always be net). For virtual stacks,
 * the stack specific net_node child list is used as opposed to the one
 * pointed to by net_node->oid_arg1 which points to the child list for the
 * management stack. This is not a user-callable macro.
 */

#define SYSCTLN_TOP_NODE     SYSCTLN_NODE
 
#ifdef _FREE_VERSION

#define SYSCTL_ADD_OID(ctx, parent, nbr, name, kind, a1, a2,		\
		       handler, fmt, descr)				\
	sysctl_add_oid(ctx, parent, nbr, name, kind, a1, a2, handler,	\
		       fmt, descr);

/* The SYSCTL_NODE and SYSCTLN_NODE are not user-calable macros */

#define SYSCTL_NODE(parent, nbr, name, access, handler, descr)		\
    do	{								\
	name##_node = sysctl_add_oid (pSysctlCtxList,			\
				      SYSCTL_NODE_CHILDREN(parent),	\
				      nbr, #name, CTLTYPE_NODE|access,	\
				      0, 0, handler, "N", descr);	\
	} while (FALSE)


#define SYSCTLN_NODE(parent, nbr, name, access, handler, descr)		\
    do	{								\
	name##_node = sysctl_add_oid (pNetSysctlCtxList,		\
				      SYSCTL_NODE_CHILDREN(parent),	\
				      nbr, #name, CTLTYPE_NODE|access,	\
				      0, 0, handler, "N", descr);	\
	} while (FALSE)

#else  /* ! defined _FREE_VERSION */

#define SYSCTL_ADD_OID(ctx, parent, nbr, name, kind, a1, a2,		\
		       handler, fmt, descr)				\
	_sysctlDbgAddOid ((ctx), parent##_node, (nbr), #name, (kind),	\
			  (a1), (a2), (handler), (fmt), (descr),	\
			  __FILE__, __LINE__, #parent);

#define SYSCTL_NODE(parent, nbr, name, access, handler, descr)		\
    do	{								\
	name##_node = _sysctlDbgAddOid (pSysctlCtxList, parent##_node,	\
					(nbr), #name,			\
					CTLTYPE_NODE|(access), 0, 0,	\
					(handler),			\
					"N", (descr),			\
					__FILE__, __LINE__, #parent);	\
	} while (FALSE)

    
#define SYSCTLN_NODE(parent, nbr, name, access, handler, descr)		\
    do	{								\
	name##_node = _sysctlDbgAddOid (pNetSysctlCtxList, parent##_node,\
					(nbr), #name,			\
					CTLTYPE_NODE|(access), 0, 0,	\
					(handler),			\
					"N", (descr),			\
					__FILE__, __LINE__, #parent);	\
	} while (FALSE)
#endif /* ! defined _FREE_VERSION */

/* This constructs a node from which other oids can hang. */

#define SYSCTL_ADD_NODE(ctx, parent, nbr, name, access, handler, descr)	    \
	sysctl_add_oid(ctx, parent, nbr, name,       \
		       CTLTYPE_NODE|access, 0, 0, handler, "N", descr)

/*
 * Oid for a string.  len can be 0 to indicate '\0' termination. The
 * SYSCTL_STRING and SYSCTLN_STRING macros are not user-callable.
 */

#define SYSCTL_STRING(parent, nbr, name, access, arg, len, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_STRING|access, \
		arg, len, sysctl_handle_string, "A", descr)

#define SYSCTLN_STRING(parent, nbr, name, access, arg, len, descr) \
	SYSCTLN_OID(parent, nbr, name, CTLTYPE_STRING|access, \
		arg, len, sysctl_handle_string, "A", descr)

#define SYSCTL_ADD_STRING(ctx, parent, nbr, name, access, arg, len, descr)  \
	SYSCTL_ADD_OID(ctx, parent, nbr, name, CTLTYPE_STRING|access, \
		       arg, len, sysctl_handle_string, "A", descr)

/*
 * Oid for an int.  If ptr is NULL, val is returned. The SYSCTL_INT and
 * SYSCTLN_INT macros are not user-callable.
 */

#define SYSCTL_INT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
		ptr, val, sysctl_handle_int, "I", descr)

#define SYSCTLN_INT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTLN_OID(parent, nbr, name, CTLTYPE_INT|access, \
		ptr, val, sysctl_handle_int, "I", descr)

#define SYSCTL_ADD_INT(ctx, parent, nbr, name, access, ptr, val, descr)	    \
	SYSCTL_ADD_OID(ctx, parent, nbr, name, CTLTYPE_INT|access,	    \
		       ptr, val, sysctl_handle_int, "I", descr)

/*
 * Oid for an unsigned int.  If ptr is NULL, val is returned. The
 * SYSCTL_UINT and SYSCTLN_UINT macros are not user-callable.
 */

#define SYSCTL_UINT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
		   ptr, val, sysctl_handle_int, "IU", descr)

#define SYSCTLN_UINT(parent, nbr, name, access, ptr, val, descr) \
	SYSCTLN_OID(parent, nbr, name, CTLTYPE_INT|access, \
		   ptr, val, sysctl_handle_int, "IU", descr)

#define SYSCTL_ADD_UINT(ctx, parent, nbr, name, access, ptr, val, descr)    \
	SYSCTL_ADD_OID(ctx, parent, nbr, name, CTLTYPE_INT|access,	    \
		       ptr, val, sysctl_handle_int, "IU", descr)

/*
 * Oid for a long.  The pointer must be non NULL. The SYSCTL_LONG and
 * SYSCTLN_LONG macros are not user-callable.
 */

#define SYSCTL_LONG(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
		   ptr, val, sysctl_handle_long, "L", descr)

#define SYSCTLN_LONG(parent, nbr, name, access, ptr, val, descr) \
	SYSCTLN_OID(parent, nbr, name, CTLTYPE_INT|access, \
		   ptr, val, sysctl_handle_long, "L", descr)

#define SYSCTL_ADD_LONG(ctx, parent, nbr, name, access, ptr, descr)	    \
	SYSCTL_ADD_OID(ctx, parent, nbr, name, CTLTYPE_INT|access,	    \
		       ptr, 0, sysctl_handle_long, "L", descr)

/*
 * Oid for an unsigned long.  The pointer must be non NULL. The
 * SYSCTL_ULONG and SYSCTLN_ULONG macros are not user-callable.
 */

#define SYSCTL_ULONG(parent, nbr, name, access, ptr, val, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_INT|access, \
		   ptr, val, sysctl_handle_long, "LU", descr)

#define SYSCTLN_ULONG(parent, nbr, name, access, ptr, val, descr) \
	SYSCTLN_OID(parent, nbr, name, CTLTYPE_INT|access, \
		   ptr, val, sysctl_handle_long, "LU", descr)

#define SYSCTL_ADD_ULONG(ctx, parent, nbr, name, access, ptr, descr)	    \
	SYSCTL_ADD_OID(ctx, parent, nbr, name, CTLTYPE_INT|access,	    \
		       ptr, 0, sysctl_handle_long, "LU", descr)

/*
 * Oid for an opaque object.  Specified by a pointer and a length. The
 * SYSCTL_OPAQUE and SYSCTLN_OPAQUE macros are not user-callable.
 */

#define SYSCTL_OPAQUE(parent, nbr, name, access, ptr, len, fmt, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_OPAQUE|access, \
		   ptr, len, sysctl_handle_opaque, fmt, descr)

#define SYSCTLN_OPAQUE(parent, nbr, name, access, ptr, len, fmt, descr) \
	SYSCTLN_OID(parent, nbr, name, CTLTYPE_OPAQUE|access, \
		   ptr, len, sysctl_handle_opaque, fmt, descr)

#define SYSCTL_ADD_OPAQUE(ctx, parent, nbr, name, access, ptr, len, fmt, descr)\
	SYSCTL_ADD_OID(ctx, parent, nbr, name, CTLTYPE_OPAQUE|access,	    \
		       ptr, len, sysctl_handle_opaque, fmt, descr)

/*
 * Oid for a struct.  Specified by a pointer and a type. The SYSCTL_STRUCT
 * and SYSCTLN_STRUCT macros are not user-callable.
 */

#define SYSCTL_STRUCT(parent, nbr, name, access, ptr, type, descr) \
	SYSCTL_OID(parent, nbr, name, CTLTYPE_OPAQUE|access, \
		   ptr, sizeof(struct type), sysctl_handle_opaque, \
		   "S," #type, descr)

#define SYSCTLN_STRUCT(parent, nbr, name, access, ptr, type, descr) \
	SYSCTLN_OID(parent, nbr, name, CTLTYPE_OPAQUE|access, \
		   ptr, sizeof(struct type), sysctl_handle_opaque, \
		   "S," #type, descr)

#define SYSCTL_ADD_STRUCT(ctx, parent, nbr, name, access, ptr, type, descr) \
	SYSCTL_ADD_OID(ctx, parent, nbr, name, CTLTYPE_OPAQUE|access,	    \
		       ptr, sizeof(struct type), sysctl_handle_opaque, \
		       "S," #type, descr)

/*
 * Oid for a procedure.  Specified by a pointer and an arg. The SYSCTL_PROC
 * and SYSCTLN_PROC macros are not user-callable.
 */

#define SYSCTL_PROC(parent, nbr, name, access, ptr, arg, handler, fmt, descr) \
	SYSCTL_OID(parent, nbr, name, access, ptr, arg, handler, fmt, descr)

#define SYSCTLN_PROC(parent, nbr, name, access, ptr, arg, handler, fmt, descr)\
	SYSCTLN_OID(parent, nbr, name, access, ptr, arg, handler, fmt, descr)

#define SYSCTL_ADD_PROC(ctx, parent, nbr, name, access, ptr, arg, handler, fmt, descr) \
	SYSCTL_ADD_OID(ctx, parent, nbr, name, access,			    \
		       ptr, arg, handler, fmt, descr)


#ifdef _WRS_KERNEL

/*
 * Declare some common oids.
 */
extern struct sysctl_oid_list sysctl__children;

#if FALSE 	/* unsupported still */
SYSCTL_DECL(_kern);
SYSCTL_DECL(_sysctl);
SYSCTL_DECL(_vm);
SYSCTL_DECL(_vfs);
SYSCTL_DECL(_net);
SYSCTL_DECL(_debug);
SYSCTL_DECL(_hw);
SYSCTL_DECL(_machdep);
SYSCTL_DECL(_user);
SYSCTL_DECL(_compat);
#endif

/* init prototypes */

STATUS sysctlInit (void);
STATUS kernSysctlInit (void);
STATUS sysctlLibInit (void);

/*
 * External declaration of the user-extension root node. See sysctl_add_oid()
 * manual for instructions on how to use it.
 */

SYSCTL_DECL_NODE_EXT (usr_ext);

extern char	machine[];
extern char	osrelease[];
extern char	ostype[];

typedef struct
	{
	ULONG		(*readFunc)(void);
	void		(*writeFunc)(ULONG);
	ULONG		shift;
	ULONG		mask;
	} SYSCTL_ACCESS;

int sysctl_handle_reg (SYSCTL_HANDLER_ARGS);

/* Dynamic oid handling */
struct sysctl_oid *sysctl_add_oid(struct sysctl_ctx_list *clist,
		struct sysctl_oid_list *parent, int nbr, const char *name,
		int kind, void *arg1, int arg2,
		int (*handler) (SYSCTL_HANDLER_ARGS),
		const char *fmt, const char *descr);
int	sysctl_remove_oid(struct sysctl_oid *oidp, int del, int recurse);
int	sysctl_ctx_init(struct sysctl_ctx_list *clist);
int	sysctl_ctx_free(struct sysctl_ctx_list *clist);
struct	sysctl_ctx_entry *sysctl_ctx_entry_add(struct sysctl_ctx_list *clist,
		struct sysctl_oid *oidp);
struct	sysctl_ctx_entry *sysctl_ctx_entry_find(struct sysctl_ctx_list *clist,
		struct sysctl_oid *oidp);
int	sysctl_ctx_entry_del(struct sysctl_ctx_list *clist,
		struct sysctl_oid *oidp);

int	kernel_sysctl(struct proc *p, int *name, u_int namelen, void *old,
		      size_t *oldlenp, void *pNew, size_t newlen,
		      size_t *retval);
int	userland_sysctl(struct proc *p, int *name, u_int namelen, void *old,
			size_t *oldlenp, int inkernel, void *pNew, 
			size_t newlen, size_t *retval);
int	sysctl_find_oid(int *name, u_int namelen, struct sysctl_oid **noid,
			int *nindx, struct sysctl_req *req);

int     sysctlnametomib __P((const char *name, int *mibp, size_t *sizep));

int	sysctlbyname __P((char *, void *, size_t *, void *, size_t));

#ifndef _FREE_VERSION

struct sysctl_oid_list *  _sysctlDbgNodeChildren (struct sysctl_oid *parent,
						  char * filename, int lineNo,
						  char * parentName);
struct sysctl_oid * _sysctlDbgAddOid (struct sysctl_ctx_list *clist,
				      struct sysctl_oid *parent,
				      int number, const char *name, int kind,
				      void *arg1, int arg2,
				      int (*handler)(SYSCTL_HANDLER_ARGS),
				      const char *fmt, const char *descr,
				      char * filename, int lineNo,
				      char * parentName);

#endif /* ! defined _FREE_VERSION */

#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif
    
#endif	/* !_SYS_SYSCTL_H_ */
