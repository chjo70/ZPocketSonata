/* 01comp_erf.cdf - ERF component configuration file */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
17nov14,yjl Provide a VSB or cdf parameter to change the stack size of
            "tErfTask" task (V7STO-205)
01a,04jan14,ghs  create.
*/

Component INCLUDE_ERF
    {
    NAME                Event reporting framework
    SYNOPSIS            Provides support for the event reporting framework for use by other libraries.
    MODULES             erfLib.o
    HDR_FILES           drv/erf/erfLib.h
    INIT_RTN            erfLibInit (ERF_MAX_USR_CATEGORIES, ERF_MAX_USR_TYPES, ERF_TASK_STACK_SIZE);
    CFG_PARAMS          ERF_MAX_USR_CATEGORIES     \
                        ERF_MAX_USR_TYPES     \
                        ERF_TASK_STACK_SIZE
    _CHILDREN           FOLDER_SERVICE
    }

Parameter ERF_MAX_USR_CATEGORIES
    {
    NAME                Maximum number of ERF user categories
	SYNOPSIS			Sets the maximum number of user categories
    TYPE                UINT16
    DEFAULT             16
    }

Parameter ERF_MAX_USR_TYPES
    {
    NAME                Maximum number of ERF user types
	SYNOPSIS			Sets the maximum number of user types.
    TYPE                UINT16
    DEFAULT             16
    }

Parameter ERF_TASK_STACK_SIZE
    {
    NAME                ERF task stack size
	SYNOPSIS			Defines the initial task stack size for the event reporting framework. \
						Its default value is 4096.
    TYPE                size_t
    DEFAULT             4096
    }

