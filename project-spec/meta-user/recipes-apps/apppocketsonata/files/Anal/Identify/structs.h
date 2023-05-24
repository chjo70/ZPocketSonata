/*!
  \file     Structs.h
  \brief    interface for the 구조체
	\version  0.0.1
*/
//////////////////////////////////////////////////////////////////////

#pragma once

#include "ELCEDLibDataType2.h"

#include "../INC/system.h"
#include "../INC/AetIPL.h"
#include "../EmitterMerge/ELMsgDefn.h"
#include "../EmitterMerge/ELStringDefn.h"

typedef unsigned int LIBINDEX;

struct STR_LIB_IDRESULT {
	SRadarMode *pIdxRadarMode;
	int uRatio;

} ;

struct STR_CEDEOB_RESULT {
	int iRadarIndex;
	int iRadarModeIndex;
	int iThreatIndex;
	int iDeviceIndex;

	int iRatio;

} ;

// 에미터 식별 방법 구조체 정의
struct STR_HOWTO_IDENTIFY {
	UINT frq[MAX_HOWTO_ID];
	UINT pri[MAX_HOWTO_ID];

} ;

struct STR_FLOWHIGH {
	int ilow;
	int ihgh;
} ;

struct STR_LIB_RANGE {
	UINT uicount;
	SRadarMode **from;

} ;

//
struct STR_FLIB {
	UINT uicount;
	STR_FLOWHIGH frq;

	SRadarMode *pIdxRadarMode[ MAX_RADARMODE ];

	STR_LIB_RANGE pLib[E_AET_MAX_FRQ_TYPE][E_AET_MAX_PRI_TYPE];

} ;

struct STR_EOB_RESULT {
	int nThreatIndex;
	int nDeviceIndex;
	int nRadarIndex;

	int iEOBNo;			// 이전 위협 라이브러리

	double dDistance;

} ;

struct STR_CEDEOB_FINAL_RESULT {
	int nRadarModeIndex[MAX_IDCANDIDATE];
	int nThreatIndex;
	int nDeviceIndex;

	char chELNOT[_MAX_ELNOT_STRING_SIZE_];

} ;




