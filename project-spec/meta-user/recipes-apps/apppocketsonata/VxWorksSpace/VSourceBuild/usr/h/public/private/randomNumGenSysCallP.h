/* randomNumGenSysCallP.h - Random number generator system call definitions */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14aug14,jpb  US34996: implement a random number generator
*/

#ifndef __INCrandomNumGenSysCallPh
#define __INCrandomNumGenSysCallPh

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
    {
    VX_RANDOM_BYTES,
    VX_RANDOM_PSEUDO_BYTES,
    VX_RANDOM_ADD,
    VX_RANDOM_STATUS
    } VX_RANDOM_NUM_GEN_CTL_CMD;

typedef struct vx_random_num_gen_ctl_bytes
    {
    unsigned char * buf;
    int num;
    } VX_RANDOM_NUM_GEN_CTL_BYTES_CMD;
    
typedef struct vx_random_num_gen_ctl_add
    {
    unsigned char * buf;
    int num;
    int entropy;
    } VX_RANDOM_NUM_GEN_CTL_ADD_CMD;

extern STATUS randNumGenCtl (VX_RANDOM_NUM_GEN_CTL_CMD command,
                             void * pArg,
                             size_t pArgSize);
    
#ifdef __cplusplus
}
#endif

#endif /* __INCrandomNumGenSysCallPh */    
