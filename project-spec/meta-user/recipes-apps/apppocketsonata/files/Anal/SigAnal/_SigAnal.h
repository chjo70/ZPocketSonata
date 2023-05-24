﻿// _SigAnal.h: interface for the 탐지분석 소프트웨어의 헤더파일
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#include "_Type.h"
#include "_Macro.h"

#include "_Define.h"
#include "_Struct.h"

#ifdef _MSC_VER
//#include "../../AdvSigAnal/Dummy/Dummy.h"
#endif

#include "../INC/system.h"

#include "../KnownSigAnal/KDefine.h"


#include "../ScanSigAnal/SDefine.h"
#include "../ScanSigAnal/SStruct.h"

#include "../../Anal/Collect/DataFile/DataFile.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MAIN_

STR_SCANPT stScanPt;

#else

extern STR_MANAET stTrkAet;
extern STR_SCNAET stScnAet;
extern STR_SCANPT stScanPt;


#endif	// _MAIN_

#ifdef __cplusplus
}
#endif



#endif // !defined(AFX_SIGANAL_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
