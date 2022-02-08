/* netFuncBindP.h - prototypes of network common global functions */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,03dec10,h_x  Add IMPORT FUNCPTR _func_remCurIdGet and
                 IMPORT FUNCPTR _func_remCurIdSet.
01d,10oct07,tkf  Add _ipdhcpc_callback_hook (as part of a fix to
                 WIND00102686).
01c,28feb07,dlk  Replace _gethostbyname, _gethostbyaddr function pointers
                 with reentrant versions _ipcom_gethostbyname_r,
		 _ipcom_gethostbyaddr_r.
01b,24oct06,kch  Removed unsupported fastudp prototypes.
01a,28aug06,tkf  Adopted the obsoleted netFuncBindP.h.
*/

/*
DESCRIPTION

This header file declares prototypes of network common global functions.

*/

#ifndef __INCnetFuncBindPh
#define __INCnetFuncBindPh

/* Global function pointer variables */

/* Function pointers provided by hostLib */

IMPORT FUNCPTR _ipcom_gethostbyname_r;  /* Use IPDNSC for the name query */
IMPORT FUNCPTR _ipcom_gethostbyaddr_r;  /* Use IPDNSC for the pointer query */
IMPORT FUNCPTR _ipdhcpc_callback_hook;  /* Use IPDNSC for the pointer query */

IMPORT FUNCPTR _func_remCurIdGet;
IMPORT FUNCPTR _func_remCurIdSet;

/* protoypes */

#endif /* __INCnetFUNCBindPh */
