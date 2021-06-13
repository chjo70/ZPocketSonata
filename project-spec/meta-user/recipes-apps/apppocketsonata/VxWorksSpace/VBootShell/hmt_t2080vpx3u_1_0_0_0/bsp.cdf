/* bsp.cdf - Board definition description file */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27jun16,l_z  add BUILD_TARGETS. (V7PRO-3159)
15dec15,syt  added BUILD_SPECS as default. (V7PRO-1405)
11nov14,syt  added LP64 support. (US15027)
18jul14,x_z  moved BSP REQUIRES to 20bsp.cdf. (US40507)
29may14,syt  Added component DRV_QORIQ_CLK (V7PRO-885).
10apr14,ylu  added support for SMP.(US34480)
09mar14,ylu  Created.
*/

Bsp hmt_t2080vpx3u {
    NAME          board support package
    CPU           PPCE6500
    MP_OPTIONS    UP SMP
    BUILD_SPECS   default
    BUILD_TARGETS uVxWorks vxWorks
    ENDIAN        big
    FP            hard soft
    DATA_MODEL    ILP32 LP64
}

