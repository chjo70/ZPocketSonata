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
#include "../INC/_aetipl.h"
#include "../EmitterMerge/ELMsgDefn.h"

typedef unsigned int LIBINDEX;

typedef struct {
	SRadarMode *pIdxRadarMode;
	int uRatio;

} STR_LIB_IDRESULT ;

typedef struct {
	int iRadarIndex;
	int iRadarModeIndex;
	int iThreatIndex;
	int iDeviceIndex;

	int iRatio;

} STR_CEDEOB_RESULT ;

// 에미터 식별 방법 구조체 정의
typedef struct {
	UINT frq[MAX_HOWTO_ID];
	UINT pri[MAX_HOWTO_ID];

} STR_HOWTO_IDENTIFY ;

typedef struct
{
	int ilow;
	int ihgh;
} STR_FLOWHIGH;

typedef struct {
	UINT uicount;
	SRadarMode **from;

} STR_LIB_RANGE ;

//
typedef struct {
	UINT uicount;
	STR_FLOWHIGH frq;

	SRadarMode *pIdxRadarMode[ MAX_ELINT_LIBRARY ];

	STR_LIB_RANGE pLib[MAX_FRQTYPE][MAX_PRITYPE];

} STR_FLIB ;

typedef struct {
	int nThreatIndex;
	int nDeviceIndex;
	int nRadarIndex;

	int iEOBNo;			// 이전 위협 라이브러리

	double dDistance;

} STR_EOB_RESULT ;

typedef struct {
	int nRadarModeIndex[MAX_IDCANDIDATE];
	int nThreatIndex;
	int nDeviceIndex;

	char chELNOT[_MAX_ELNOT_STRING_SIZE_];

} STR_CEDEOB_FINAL_RESULT;


#endif // !defined(AFX_STRUCTS_H__F11C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)

