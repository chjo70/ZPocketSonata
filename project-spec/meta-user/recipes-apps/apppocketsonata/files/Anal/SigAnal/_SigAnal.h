// _SigAnal.h: interface for the 탐지분석 소프트웨어의 헤더파일
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_type.h"
#include "_macro.h"

#include "_Define.h"
#include "_Struct.h"

#ifdef _WIN32
// #include "../../AdvSigAnal/Dummy/Dummy.h"
#endif

#include "../INC/System.h"
#include "../ScanSigAnal/SDefine.h"
#include "../ScanSigAnal/SStruct.h"


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

_TOA TOA[MAX_PDW];					// PDW TOA 파라메터
UINT AOA[MAX_PDW];					// PDW AOA 파라메터
UINT FREQ[MAX_PDW];					// PDW FREQUENCY 파라메터
UINT PW[MAX_PDW];						// PDW PULSE WIDTH 파라메터
int PA[MAX_PDW];						// PDW PULSE AMPLITUDE 파라메터
UCHAR PMOP[MAX_PDW];				// PDW PMOP 파라메터
UCHAR FMOP[MAX_PDW];				// PDW FMOP 파라메터
USHORT MARK[MAX_PDW];				// PDW MARK ; selected pdw
UCHAR BAND[MAX_PDW];				// 주파수 밴드
UCHAR STAT[MAX_PDW];				// PDW STATUS(Notmal, CW, PMOP, Chirp Up/Dn)
USHORT BKMK[MAX_PDW];				// MARK 백업용, 스태거 분석시에 사용함.
USHORT RSMK[MAX_PDW];				// MARK 백업용, 스태거 분석시에 사용함.
UCHAR MAXCHANNEL[MAX_PDW];	// PDW의 MaxChannel

// 주파수 해상도 계산용

// HARMONIC MARGIN
#ifdef _ELINT_
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

extern _TOA TOA[MAX_PDW];			// PDW TOA 파라메터
extern UINT AOA[MAX_PDW];			// PDW AOA 파라메터
extern UINT FREQ[MAX_PDW];		// PDW FREQUENCY 파라메터
extern UINT PW[MAX_PDW];			// PDW PULSE WIDTH 파라메터
extern int PA[MAX_PDW];			// PDW PULSE AMPLITUDE 파라메터
extern UCHAR PMOP[MAX_PDW];		// PDW PMOP 파라메터
extern UCHAR FMOP[MAX_PDW];		// PDW FMOP 파라메터
extern USHORT MARK[MAX_PDW];	// PDW MARK ; selected pdw
extern UCHAR BAND[MAX_PDW];		// 주파수 밴드
extern UCHAR STAT[MAX_PDW];		// 주파수 밴드
extern USHORT BKMK[MAX_PDW];		// Mark 펄스열의 백업용
extern USHORT RSMK[MAX_PDW];	// MARK 백업용, 스태거 분석시에 사용함.
extern UCHAR MAXCHANNEL[MAX_PDW];	// PDW의 MaxChannel

#ifdef _A50_RWR
extern UINT stSigma1Aoa[5];
extern UINT stSigma1Frq[5];

#else
extern UINT stSigma1Aoa[3];
extern UINT stSigma1Frq[3];

#endif


extern STR_MANAET stTrkAet;
extern STR_SCNAET stScnAet;
extern STR_SCANPT stScanPt;

extern UINT stOffPdw;

#endif	// _MAIN_

#ifdef __cplusplus
}
#endif

// int Printf( char *format, ... );


#endif // !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
