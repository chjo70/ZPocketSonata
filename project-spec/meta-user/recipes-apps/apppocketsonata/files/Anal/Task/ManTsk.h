// ManTsk.h: interface for the CManTsk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANTSK_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_MANTSK_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32
#include <msgQLib.h>
#endif

#include "Task.h"


#ifdef __cplusplus
extern "C" {
#endif
	
void InitTasks();
void InitClass();
void InitUnits();

// Hook 관련 함수 정의
void HookSoftwareReset();
unsigned int CHookKeyHandler( int i, int ch );

void RequestInit();
void RequestIBit();
void RequestCBit();
void StartMainAnal();
void StartServer();
void RequestToHoldAnal();
void SetupCBit();
void PrintScreenBuffer();

void LogOn();
void LogOff();

void pb();
void cb();
void bp();
void rp();
void bpp();
void debug();
void t();

void test();
void t1();
void t2();
void t3();

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus


class CManTsk : public CTask
{
private:

public:
	void RequestCBit();
	void SoftReset();
	void DownloadUDF();
	void Zerorize();
	void ReqStopAnal();
	inline void Timer() { }
	void SetupCBit();
	void ReqHoldAnal();
	void RequestToHoldAnal();
	void InitTask();
	void MallocBuffer();
	void ReqStartAnal();
	void StartAnal();
	void ReqSwitchControl();
	void RequestUploadChannelData();
	void InitVar();
	void ClearPowerOnInitVar();
	void RequestInit();
	BOOL ParseMessage();
	void RequestIBit();
	void Run();
	CManTsk( char *pTaskName );
	virtual ~CManTsk();

};

#endif


#endif // !defined(AFX_MANTSK_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
