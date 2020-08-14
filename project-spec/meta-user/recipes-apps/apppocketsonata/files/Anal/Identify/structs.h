/*!
  \file     Structs.h
  \brief    interface for the 구조체
	\version  0.0.1
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRUCTS_H__F11C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_STRUCTS_H__F11C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ELCEDLibDataType2.h"
#include "../INC/system.h"
#include "../INC/AetIPL.h"
#include "../EmitterMerge/ELMsgDefn.h"

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

	SRadarMode *pIdxRadarMode[ MAX_ELINT_LIBRARY ];

	STR_LIB_RANGE pLib[MAX_FRQTYPE][MAX_PRITYPE];

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


#endif // !defined(AFX_STRUCTS_H__F11C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)

