// Globals.h: interface for the 전역 선언
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_GLOBALS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#pragma once

#ifdef _VXWORKS_
#include <bootLib.h>
#else
#endif




//////////////////////////////////////////////////////////////////////////
// 전역 정의문

#ifdef _MAIN_GLOBALS_

//////////////////////////////////////////////////////////////////////////
// 전역 함수
//

#ifdef __cplusplus

//CManTsk *theManTsk;
//CLogDebug *theLogDebug;
//CSendSerial *theSendSerial;
//CRecvSerial *theRecvSerial;
//CRunBit *theRunBit;

CGetPdw *theGetPdwTask;
CSigAnal *theSigAnalTask;
CLOBMngr *theLOBMngrTask;

//CTcpIpServer *theTcpIpServer;
//CManAet *theManAet;

//CPollKey *thePollKey;
//CAliveMark *theAliveMark;
CIni *theIni;

#endif

// 초기화 관련 결과 정보를 저장한다.
//STR_POWER_ON_INIT stPowerOnInit;

// 전원 인가후의 IBIT 결과가 저장되는 변수
//STR_POWER_ON_IBIT stPowerOnIbit;
//STR_POWER_ON_PBIT stPowerOnPbit;
//STR_POWER_ON_CBIT stPowerOnCbit;

// 초단수신기의 연결 상태를 확인한다.
//STR_VH_RECIVER_CON_STAT stVhReceiverConStat;

// 시리얼 디바이스
//int CComSerial::fdSerial=-1;

//////////////////////////////////////////////////////////////////////////
// 레이더 수집국의 위/경도 좌표
double dRCLatitude[RADARCOL_MAX] = { 0.0, 37.485168456889, 37.454452514694, 37.453517913889 } ;
double dRCLongitude[RADARCOL_MAX] = { 0.0, 126.457916259694, 126.481880188111, 126.423416137778 } ;

double dRCDOA[RADARCOL_MAX] = { 10, 300, 70 } ;

#else

//////////////////////////////////////////////////////////////////////////
// 외부 변수
#ifdef __cplusplus

// IMPORT CManTsk *theManTsk;
//IMPORT CLogDebug *theLogDebug;
// IMPORT CSendSerial *theSendSerial;
// IMPORT CRecvSerial *theRecvSerial;
// IMPORT CRunBit *theRunBit;
// IMPORT CGenPulseInfo *theGenPulseInfo;

IMPORT CGetPdw *theGetPdwTask;
IMPORT CLOBMngr *theLOBMngrTask;
IMPORT CSigAnal *theSigAnalTask;
// IMPORT CTcpIpServer *theTcpIpServer;

IMPORT CIni *theIni;

#endif

#ifdef _VXWORKS_
IMPORT BOOT_PARAMS stBootParams;

#endif

IMPORT double dRCLatitude[RADARCOL_MAX];
IMPORT double dRCLongitude[RADARCOL_MAX];

IMPORT double dRCDOA[RADARCOL_MAX];


#endif

//////////////////////////////////////////////////////////////////////////
//




#endif // !defined(AFX_GLOBALS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
