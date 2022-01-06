/* Copyright (c) 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
13mar14,wzc  support arm hpc(US17715)
*/

/*
DESCRIPTION
*/
#ifndef INChpc_hpc_ep_test_h
#define INChpc_hpc_ep_test_h
#ifdef __cplusplus
extern "C" {
#endif

extern void hpc_init_arm_tests(void);
extern void hpc_init_e500mc_tests(void);
extern void hpc_init_fsl_p2020_tests(void);
extern void hpc_init_mpc_8540_tests(void);
extern void hpc_init_mpc_8548_tests(void);
extern void hpc_init_core2_tests(void);
extern void hpc_init_corei7_tests(void);

#ifdef __cplusplus
}
#endif
#endif /* INChpc_hpc_ep_test_h */
