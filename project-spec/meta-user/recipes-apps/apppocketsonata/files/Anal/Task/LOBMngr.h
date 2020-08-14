// LOBMngr.h: interface for the CLOBMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOBMngr_H__536AD6D5_B815_4B18_B73A_C2339E4AE028__INCLUDED_)
#define AFX_LOBMngr_H__536AD6D5_B815_4B18_B73A_C2339E4AE028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Task.h"
#include "ELMsgQThread.h"

#include "../EmitterMerge/ELMsgDefn.h"

#include "../EmitterMerge/ELEmitterMergeMngr.h"

#ifdef __cplusplus

class CLOBMngr : public CTask
{
private:
	CELEmitterMergeMngr *m_pclsEmitterMergeMngr;

private:
	void InitVar();

	bool ProcessLOBDataMsg( SQMsg *psqMsg, bool bUserMsg=false );
	bool ShouldProcAirMsg( SQMsg *psqMsg );
	void ProcLOBMsgData( SQMsg *psqMsg, bool bUserMsg=false, bool bCheckDeleteThreat=false );

private:
	static void IsrWrapper( CLOBMngr *pSelf );
	
public:
	inline void Timer() { }

	void MallocBuffer();
	void PrintAllPDW( _PDW *pPdw, UINT count );
	bool Start();
	void ClearInit();
	void SetCollectParameter( int nFilter );
	BOOL ParseMessage( SQMsg *psqMsg );
	void Run();
	void InitTask();

	// 타 타스크 관련 메시지 함수
	//void SendMessageToAnalTask(SQMsg *psqMsg);

	CLOBMngr( char *pTaskName );
	virtual ~CLOBMngr();

};

#endif

#endif // !defined(AFX_LOBMngr_H__536AD6D5_B815_4B18_B73A_C2339E4AE028__INCLUDED_)
