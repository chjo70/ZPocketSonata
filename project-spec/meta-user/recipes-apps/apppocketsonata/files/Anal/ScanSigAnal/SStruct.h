// SStruct.h: interface for the 스캔분석판 소프트웨어의 구조체
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSTRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_SSTRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../INC/PDW.h"
#include "SDefine.h"

typedef unsigned int HIST;

#ifndef _STR_LOWHIGH
#define _STR_LOWHIGH
struct STR_LOWHIGH
{
    int iLow;
    int iHigh;

} ;
#endif

/**
    @struct STR_SCANPT
    @brief
**/
#ifdef SCN_COLLECT_PDW
struct STR_SCANPT {
    UINT uiCount;
    int iPA[SCN_COLLECT_PDW];				// 신호세기
    _TOA tTOA[SCN_COLLECT_PDW];				// 시간

    STR_LOWHIGH _pa;

} ;
#endif

/**
    @struct STR_SAMPLE
    @brief
**/
struct STR_SAMPLE {
	UINT uiCount;
	_TOA tTOA[SCN_COLLECT_PDW];
	int iPA[SCN_COLLECT_PDW];

	float fNormPa[SCN_COLLECT_PDW];					// normalize of pa

	float fMeanY;

	float fSdevY;

	float fKurtosis;
	float fSkewness;

	STR_LOWHIGH	_pa;					// Low & High
} ;

// Auto-Correlation Function 용 변수
struct STR_AUTOCOR {
    UINT uiCount;

    float fACF[SCN_COLLECT_PDW];

    UINT inPeak;
    UINT idPeak;
    float fThreshold[SCN_COLLECT_PDW];

    float fMeanACF;

    float fCCF_Fix;
    float fCCF_Con;
}  ;



#endif // !defined(AFX_SSTRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
