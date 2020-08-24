// KVar.h: interface for the 추적분석판 소프트웨어의 헤더파일
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KVAR_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_KVAR_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../RSA/INC/_define.h"
#include "../../RSA/INC/_common.h"

#include "../../RSA/BSP/hw_def.h"
#include "KDefine.h"

#include "KStruct.h"

#include "../NSP/NVar.h"

#ifdef _WIN32
#include "../../AdvSigAnal/Dummy/Dummy.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MAIN_
STR_TRKAET stTrkAet;

UINT stNoCh;

#ifdef _WIN32
STR_PDWBANK stKPDW[_spCoKSP][KSF_noCell];
word32 gKDMFifoFull;
#else
STR_PDWBANK stKPDW[KSF_noCell];
#endif

#else
extern STR_TRKAET stTrkAet;

extern UINT stNoCh;

#ifdef _WIN32
extern STR_PDWBANK stKPDW[_spCoKSP][KSF_noCell];
#else
extern STR_PDWBANK stKPDW[KSF_noCell];
#endif

extern word32 gKDMFifoFull;
extern word32 gKDMHalfFull;

#endif	// _MAIN_

// 함수 선언
int KSPCollectPDW();
void KSPCollectInit();

#ifdef __cplusplus
}
#endif


#endif // !defined(AFX_KVAR_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
