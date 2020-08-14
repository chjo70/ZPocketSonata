// SStruct.h: interface for the 스캔분석판 소프트웨어의 구조체
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSTRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_SSTRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../INC/PDW.h"

//##ModelId=452B0C44033B
typedef unsigned int HIST;

#ifndef _STR_LOWHIGH
#define _STR_LOWHIGH
typedef struct
{
  int low;
  int hgh;
} STR_LOWHIGH;
#endif

//##ModelId=452B0C440345
struct STR_SCANPT {
	UINT co;
	UINT pa[SCN_COLLECT_PDW+10];				// toa
	UINT toa[SCN_COLLECT_PDW+10];				// amplitude

	STR_LOWHIGH _pa;

}  ;

//##ModelId=452B0C44034F
struct STR_SAMPLE {
	UINT co;
	UINT toa[_spMaxSample+10];
	UINT pa[_spMaxSample+10];	

	float normPa[_spMaxSample];					// normalize of pa

	float	meanY;

	float	sdevY;

	float	kurtosis;
	float	skewness;

	STR_LOWHIGH	_pa;					// Low & High
}  ;

// Auto-Correlation Function 용 변수
//##ModelId=452B0C440359
struct STR_AUTOCOR {
    UINT co;

    float acf[_spMaxSample];

    UINT inPeak;
    UINT idPeak;
    float fThreshold[_spMaxSample];

    float meanAcf;

    float ccf_fix;
    float ccf_con;
    float	ccf_saw;
    float	ccf_ret;
}  ;


#endif // !defined(AFX_SSTRUCT_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
