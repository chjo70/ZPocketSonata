/* vxworks_polling.h - header for vxworks polling event processor */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13jan15,tle  Add vxworks_polling event processor (US11628)
*/

#ifndef __vxworks_pollingh
#define __vxworks_pollingh

#ifdef __cplusplus
extern "C" {
#endif

extern int cafe_vxworks_polling_register(void);
extern void cafe_vxworks_polling_unregister(void);

#ifdef __cplusplus
}
#endif


#endif /* __vxworks_pollingh */
