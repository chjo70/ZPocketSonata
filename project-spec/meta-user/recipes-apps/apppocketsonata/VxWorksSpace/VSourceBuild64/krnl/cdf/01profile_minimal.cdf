/* 01profile_minimal.cdf - profile tuned for a small RAM image */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16dec15,lau  removed the INCLUDE_NO_INTRINSICS Component (V7COR-2886)
12may14,wap  Remove INCLUDE_NO_INTRINSICS from standalone profile
             (the shell component depends on intrinsics).
09may14,wap  Switch from BSP_DEFAULTS to BSP_PARAMTER_VALUES and
             remove EXCLUDES.
23apr14,wap  Written per US35788, US35789, US35790, US35791

DESCRIPTION
This file contains definitions for minimal configuration profiles
both with and without user-mode (RTP) support. The 'standalone'
profiles include the target shell. Networking and filesystem
support is excluded.

*/

Profile PROFILE_MINIMAL {
    NAME	Profile is tuned for a small kernel size
    SYNOPSIS	Using this profile will tune the configuration with the goal of producing the smallest possible VxWorks kernel image.
    PROFILES    BSP_PARAMETER_VALUES

    COMPONENTS	INCLUDE_KERNEL		\
                INCLUDE_SYSCLK_INIT	\
                INCLUDE_SIO		\
		INCLUDE_BANNER		
}


Profile PROFILE_MINIMAL_RTP {
    NAME	Profile is tuned for a small kernel size with RTP support
    SYNOPSIS	Using this profile will tune the configuration with the goal of producing the smallest possible VxWorks kernel image with RTP support.
    PROFILES    BSP_PARAMETER_VALUES
    COMPONENTS	INCLUDE_KERNEL		\
                INCLUDE_SYSCLK_INIT	\
		INCLUDE_BANNER		\
		INCLUDE_SIO		\
		INCLUDE_RTP
}


Profile PROFILE_STANDALONE_MINIMAL {
    NAME	Profile is tuned for a small kernel size with target shell
    SYNOPSIS	Using this profile will tune the configuration with the goal of producing the smallest possible VxWorks kernel image that includes the target shell.
    PROFILES    BSP_PARAMETER_VALUES
    COMPONENTS	INCLUDE_KERNEL		\
                INCLUDE_SYSCLK_INIT	\
		INCLUDE_BANNER		\
		INCLUDE_SIO		\
		INCLUDE_SHELL
}


Profile PROFILE_STANDALONE_MINIMAL_RTP {
    NAME	Profile is tuned for a small kernel size with RTP support
    SYNOPSIS	Using this profile will tune the configuration with the goal of producing the smallest possible VxWorks kernel image with RTP support.
    PROFILES    BSP_PARAMETER_VALUES
    COMPONENTS	INCLUDE_KERNEL		\
                INCLUDE_SYSCLK_INIT	\
		INCLUDE_BANNER		\
		INCLUDE_SIO		\
		INCLUDE_RTP		\
		INCLUDE_SHELL
}


