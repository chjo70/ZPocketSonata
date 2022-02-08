/* 01profile_small_footprint.cdf - profile tuned for a small RAM image */

/*
 * Copyright 2014-2015 (c) Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16dec15,lau  removed the INCLUDE_NO_INTRINSICS Component (V7COR-2886)
06oct14,jmz  V7PRO-1054 - Prevent VSB's that do not support 
             PROFILE_SMALL_FOOTPRINT from advertising that they do
*/

#if (defined PROFILE_SMALL_FOOTPRINT)
Profile PROFILE_SMALL_FOOTPRINT {
    NAME	Profile is tuned for a small RAM image
    SYNOPSIS	Using this profile will tune the configuration with the goal of producing the smallest possible VxWorks RAM footprint image.
    COMPONENTS	INCLUDE_KERNEL		\
                INCLUDE_SYSCLK_INIT
    PROFILES    BSP_PARAMETER_VALUES
}
#endif
