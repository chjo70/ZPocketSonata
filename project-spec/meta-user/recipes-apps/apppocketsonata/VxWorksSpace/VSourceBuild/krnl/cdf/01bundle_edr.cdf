/* 01bundle_edr.cdf - VxWorks ED&R component bundles */

/* Copyright 2003-2006, 2017 Wind River Systems, Inc. */

/*
modification history
--------------------
17apr17,own  Updated SYNOPSIS (F8862).
01e,10may06,tfo  removed FOLDER_BUNDLES
01d,29sep04,tam  removed INCLUDE_EDR_KH
01c,29jul04,md   removed INCLUDE_EDR_POLICIES, BUNDLE_EDR_RTP
01b,21jun04,md   removed old components
01a,14apr04,md   written
*/

Bundle BUNDLE_EDR {
    NAME	Error Detection and Reporting
    SYNOPSIS	This bundle contains the Kernel components required for error \
                detection and reporting (ED&R).
    COMPONENTS	INCLUDE_EDR_PM \
		INCLUDE_EDR_ERRLOG \
		INCLUDE_EDR_SHOW \
		INCLUDE_EDR_SYSDBG_FLAG
}
