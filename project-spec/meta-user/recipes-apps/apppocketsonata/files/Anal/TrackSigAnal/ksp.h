/****************************************************************************************
 파 일 명 : ksp.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 제어 헤더 파일
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 3:01오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#ifndef _KSP_H_
#define _KSP_H_

#include "../../RSA/INC/_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MAIN_
UINT stOverToaFlag;	// over TOA flag

#else
extern UINT stOverToaFlag;	// over TOA flag

#endif

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기용 공용 선언 (ktsys.c)
//
void InitOpAnalVar(void);

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기용 공용 선언 (ktmng.c)
//
TASK TSK_MngTsk( void );

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기용 공용 선언 (kgsig.c)
//
TASK TSK_GthSig( void );
UINT CollectPdw( void );
void InitColVar( void );
BOOL ReadFifo( UINT *phase );
BOOL GetFifo( UINT *phase );
UINT GetOnePdw( TNEW_PDW *pNewPdw );
UINT ReadOnePdw( TNEW_PDW *pNewPdw );
void SendPulExt( UINT noCh );

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기용 공용 선언 (kasig.c)
//
TASK TSK_AnlSig( void );
UINT AnalSig( STR_TRKAET *pTrkAet );
void GetTrkAetInCommon( STR_TRKAET *pTrkAet, UINT noEMT );
void SendStatAet( STR_UPDAET *pAet, UINT stat );

void SendKSPNewAet( STR_NEWAET *pAet, UINT inEMT );
void SendKSPUpdAet( STR_UPDAET *pUpdAet );
void SendKSPLostAet( STR_TRKAET *pAet, int stat );

int KnownSigAnal( int noSbc, int noCh );

void LoadSystemParameter(void);
void CompileRevision( void );

#ifdef __cplusplus
}
#endif

#endif

