/* ostimer - pure timer event generator */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef OStimer_h
#define OStimer_h

#ifdef __cplusplus
extern "C" {
#endif

#define OSTIMER_DEF	"S[cafe_ostimer.ostimer]"
#define OSTIMER_REF	"t[cafe_ostimer.ostimer]"

extern int  cafe_ostimer_cfg_register(void);
extern void cafe_ostimer_cfg_unregister(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* OStimer_h */
