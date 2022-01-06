/* 01bundle_runtime_analysis.cdf - Runtime Analysis components bundles */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
20jan14,sdt  Added history.

DESCRIPTION
This file contains component bundle descriptions for the Analysis Agent.

*/

Bundle BUNDLE_RUNTIME_ANALYSIS_DEVELOP {
	NAME        	Component bundle for Runtime Analysis development
	SYNOPSIS	Runtime Analysis components useful for development
	COMPONENTS	INCLUDE_ANALYSIS_AGENT \
			INCLUDE_ANALYSIS_SCRIPT \
			INCLUDE_ANALYSIS_DEBUG_SUPPORT \
			INCLUDE_ANALYSIS_TEST

}

