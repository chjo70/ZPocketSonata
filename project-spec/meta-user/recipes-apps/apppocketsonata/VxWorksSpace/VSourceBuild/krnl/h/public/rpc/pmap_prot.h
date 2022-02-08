/* pmap_prot.h - Protocol for the local binder service, or pmap. */

/* Copyright 1984-1992 Wind River Systems, Inc. */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 *
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
/*	@(#)pmap_prot.h 1.1 86/02/03 SMI	*/

/* Copyright (C) 1984, Sun Microsystems, Inc. */

/*
modification history
--------------------
01h,23jan10,y_t Add LP64 support.
01g,22sep92,rrr  added support for c++
01f,26may92,rrr  the tree shuffle
01e,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01d,24oct90,shl  deleted redundant function declarations.
01c,05oct90,shl  added ANSI function prototypes.
                 added copyright notice.
01b,27oct89,hjb  added modification history and #ifndef's to avoid multiple
		 inclusion.
*/

#ifndef __INCpmap_proth
#define __INCpmap_proth

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The following procedures are supported by the protocol:
 *
 * PMAPPROC_NULL() returns ()
 * 	takes nothing, returns nothing
 *
 * PMAPPROC_SET(struct pmap) returns (bool_t)
 * 	TRUE is success, FALSE is failure.  Registers the tuple
 *	[prog, vers, prot, port].
 *
 * PMAPPROC_UNSET(struct pmap) returns (bool_t)
 *	TRUE is success, FALSE is failure.  Un-registers pair
 *	[prog, vers].  prot and port are ignored.
 *
 * PMAPPROC_GETPORT(struct pmap) returns (long unsigned).
 *	0 is failure.  Otherwise returns the port number where the pair
 *	[prog, vers] is registered.  It may lie!
 *
 * PMAPPROC_DUMP() RETURNS (struct pmaplist *)
 *
 * PMAPPROC_CALLIT(unsigned, unsigned, unsigned, string<>)
 * 	RETURNS (port, string<>);
 * usage: encapsulatedresults = PMAPPROC_CALLIT(prog, vers, proc, encapsulatedargs);
 * 	Calls the procedure on the local machine.  If it is not registered,
 *	this procedure is quite; ie it does not return error information!!!
 *	This procedure only is supported on rpc/udp and calls via
 *	rpc/udp.  This routine only passes null authentication parameters.
 *	This file has no interface to xdr routines for PMAPPROC_CALLIT.
 *
 * The service supports remote procedure calls on udp/ip or tcp/ip socket 111.
 */

#define PMAPPORT		((u_short)111)
#define PMAPPROG		((u_int)100000)
#define PMAPVERS		((u_int)2)
#define PMAPVERS_PROTO		((u_int)2)
#define PMAPVERS_ORIG		((u_int)1)
#define PMAPPROC_NULL		((u_int)0)
#define PMAPPROC_SET		((u_int)1)
#define PMAPPROC_UNSET		((u_int)2)
#define PMAPPROC_GETPORT	((u_int)3)
#define PMAPPROC_DUMP		((u_int)4)
#define PMAPPROC_CALLIT		((u_int)5)

struct pmap {
	u_int  pm_prog;
	u_int  pm_vers;
	u_int  pm_prot;
	u_int  pm_port;
};

struct pmaplist {
	struct pmap	pml_map;
	struct pmaplist *pml_next;
};

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern	  bool_t       xdr_pmap (XDR *xdrs, struct pmap *regs);
extern	  bool_t       xdr_pmaplist (XDR *xdrs, struct pmaplist **rp);

#else

extern	  bool_t       xdr_pmap ();
extern	  bool_t       xdr_pmaplist ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCpmap_proth */
