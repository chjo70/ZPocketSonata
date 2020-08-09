// Globals.h: interface for the ���� ����
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_GLOBALS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#pragma once

#ifndef _WIN32
#include <bootLib.h>
#endif




//////////////////////////////////////////////////////////////////////////
// ���� ���ǹ�

#ifdef _MAIN_GLOBALS_

//////////////////////////////////////////////////////////////////////////
// ���� �Լ�
//

#ifdef __cplusplus

//CManTsk *theManTsk;
CLogDebug *theLogDebug;
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

// �ʱ�ȭ ���� ��� ������ �����Ѵ�.
//STR_POWER_ON_INIT stPowerOnInit;

// ���� �ΰ����� IBIT ����� ����Ǵ� ����
//STR_POWER_ON_IBIT stPowerOnIbit;
//STR_POWER_ON_PBIT stPowerOnPbit;
//STR_POWER_ON_CBIT stPowerOnCbit;

// �ʴܼ��ű��� ���� ���¸� Ȯ���Ѵ�.
//STR_VH_RECIVER_CON_STAT stVhReceiverConStat;

// �ø��� ����̽�
//int CComSerial::fdSerial=-1;

//////////////////////////////////////////////////////////////////////////
// ���̴� �������� ��/�浵 ��ǥ
double dRCLatitude[RADARCOL_MAX] = { 0.0, 37.485168456889, 37.454452514694, 37.453517913889 } ;
double dRCLongitude[RADARCOL_MAX] = { 0.0, 126.457916259694, 126.481880188111, 126.423416137778 } ;

double dRCDOA[RADARCOL_MAX] = { 10, 300, 70 } ;

#else

//////////////////////////////////////////////////////////////////////////
// �ܺ� ����
#ifdef __cplusplus

// IMPORT CManTsk *theManTsk;
IMPORT CLogDebug *theLogDebug;
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

#ifndef _WIN32
IMPORT BOOT_PARAMS stBootParams;

#endif

IMPORT double dRCLatitude[RADARCOL_MAX];
IMPORT double dRCLongitude[RADARCOL_MAX];

IMPORT double dRCDOA[RADARCOL_MAX];


#endif

//////////////////////////////////////////////////////////////////////////
//




#endif // !defined(AFX_GLOBALS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
