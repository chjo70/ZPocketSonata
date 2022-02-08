/* 05runtime_analysis_hpc.cdf - Runtime Analysis HPC components */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
16jun15,mob  Remove "Experimental" tag from HPC components (V7COR-3066)
05jun15,gxu  Release HPC component for intel arch (V7COR-3019)
26feb14,sdt  Dissociate HPC folder definition
20jan14,sdt  Written.

DESCRIPTION

This file contains component descriptions for HPC common part of the Runtime
Analysis.

*/

Folder FOLDER_ANALYSIS_HPC {
        NAME            Hardware Performance Counter (HPC) driver
        SYNOPSIS        Hardware performance counter driver components

#ifdef _WRS_CONFIG_ARCH_i86        
        _CHILDREN	FOLDER_RUNTIME_ANALYSIS
#else        
       _CHILDREN	FOLDER_NOT_VISIBLE        
#endif
        CHILDREN	INCLUDE_CAFE_EP_HPC
        DEFAULTS	INCLUDE_CAFE_EP_HPC
}

/* Overwrite defaults field to add HPC tests */
Folder FOLDER_ANALYSIS_TEST {
	DEFAULTS	INCLUDE_ANALYSIS_HPC_TEST_HW \
			INCLUDE_ANALYSIS_TEST \
			INCLUDE_ANALYSIS_HPC_API_TEST_HW
}

Component INCLUDE_CAFE_EP_HPC {
	NAME		Cafe event source for HPC
	SYNOPSIS	Cafe event source for Hardware Performance Counters
	INIT_RTN	hpcCfgInit();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	CONFIGLETTES	hpcInit.c
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE \
			INCLUDE_CAFE_VX_TIMESTAMP
}

Component INCLUDE_ANALYSIS_HPC_TEST_HW {
        NAME            HPC Tests
        SYNOPSIS        Unit tests for Hardware Performance Counters part of Runtime Analysis. Execute hpc_unit_test_hw from target shell to run tests.
	INIT_RTN	hpcCfgTestInit();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_ANALYSIS_TEST
}

Component INCLUDE_ANALYSIS_HPC_API_TEST_HW {
        NAME            HPC API Tests
        SYNOPSIS        Tests for HPC driver API of Runtime Analysis. Execute hpcHwDrvUnitTestSuiteHw from target shell to run tests.
	INIT_RTN	hpcCfgHpcHwApiTestInit();
        MODULES         hpc_test_drv_main_vx.o
        LINK_SYMS       hpcHwDrvUnitTestSuiteHw
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_ANALYSIS_TEST
}
