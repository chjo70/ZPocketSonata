// _SigAnal.h: interface for the 탐지분석 소프트웨어의 헤더파일
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_Type.h"
#include "_Macro.h"

#include "_Define.h"
#include "_Struct.h"

#ifdef _MSC_VER
#include "../../AdvSigAnal/Dummy/Dummy.h"
#endif

#include "../INC/system.h"

#include "../KnownSigAnal/KDefine.h"


#include "../ScanSigAnal/SDefine.h"
#include "../ScanSigAnal/SStruct.h"

#include "../../Anal/Collect/DataFile/DataFile.h"


//////////////////////////////////////////////////////////////////////////
// printf()문을 대체하기 위한 선언.
// Printf() 관련 함수는 타 소스에서 이를 선언해서 장비에 특성에 맞게 구현함.

// #define printf printf

// #ifdef __cplusplus
// extern "C" {
// #endif
// 
// int Printf( char *format, ... );
// 
// #ifdef __cplusplus
// }
// #endif

//////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MAIN_

// 주파수 해상도 계산용

// HARMONIC MARGIN
#ifdef _ELINT_
UINT stSigma1Aoa[5] = { KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR } ;
UINT stSigma1Frq[5] = { KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR } ;

#elif defined(_POCKETSONATA_)
UINT stSigma1Aoa[5] = { KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR, KHARM_AOA_MAR } ;
UINT stSigma1Frq[5] = { KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR, KHARM_FRQ_MAR } ;

#else
UINT stSigma1Aoa[3] = { KHARM_AOA_MAR_LOW, KHARM_AOA_MAR_MID, KHARM_AOA_MAR_HGH } ;
UINT stSigma1Frq[3] = { KHARM_FRQ_MAR_LOW, KHARM_FRQ_MAR_MID, KHARM_FRQ_MAR_HGH } ;

#endif

STR_MANAET stTrkAet;
STR_SCNAET stScnAet;
STR_SCANPT stScanPt;

UINT stOffPdw;

#else

#ifdef _A50_RWR
extern UINT stSigma1Aoa[5];
extern UINT stSigma1Frq[5];

extern STR_MANAET stTrkAet;
extern STR_SCNAET stScnAet;
extern STR_SCANPT stScanPt;

#else
extern UINT stSigma1Aoa[3];
extern UINT stSigma1Frq[3];

#endif




extern UINT stOffPdw;

#endif	// _MAIN_

#ifdef __cplusplus
}
#endif

// int Printf( char *format, ... );


#endif // !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
