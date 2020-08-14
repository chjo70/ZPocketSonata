// SigAnal.h: interface for the CSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGANAL_H__B1861C90_58D2_419C_B285_F44D27936048__INCLUDED_)
#define AFX_SIGANAL_H__B1861C90_58D2_419C_B285_F44D27936048__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "../SigAnal/SysPara.h"

#include "../NewSigAnal/NewSigAnal.h"
#include "../KnownSigAnal/KnownSigAnal.h"
#include "../ScanSigAnal/ScanSigAnal.h"

#ifdef __cplusplus

extern bool gstbSimulator;

class CSigAnal : public CTask
{
private:
	enum BAND_INFO m_nBand;
	STR_QUEUE_LOG_MESSAGE m_logMsg;
	enum ANALYSIS_MODE m_eAnalMode;

	SQMsg m_SendQMsg;
	
public:
	//CPdwFilter *m_thePdwFilter;
	CSysPara *m_theSysPara;
	CNewSigAnal *m_theNewSigAnal;
	//CKnownSigAnal *m_theKnownSigAnal;
	//CScanSigAnal *m_theScanSigAnal;
	STR_PDWDATA m_stPDWData;

private:
	void SendMessageToLOBMngrTask();

public:
	enum ANALYSIS_MODE GetAnalMode();
	void ScanSigAnal();
	void StopAnal();
	void DISP_HexFineAet( STR_NEWAET *pNewAet );
	inline void Timer() { }
	inline void DISP_FineAet( STR_NEWAET *pNewAet ) { m_theNewSigAnal->DISP_FineAet( pNewAet ); }
	void DISP_FineAet( STR_MANAET *pManAet );
	void MallocBuffer();
	void SendAetMessage( enum ANAL Anal );
	void StartAnal( enum ANAL Anal, int noFilter, enum BAND_INFO nBand );
	BOOL ParseMessage();
	BOOL ParseMessage(SQMsg *psqMsg);
	void Run();
	void InitTask();
	void InitVar();
	void Start(SQMsg *psqMsg);
	

	CSigAnal( char *pTaskName );
	virtual ~CSigAnal();

public:
	void SendSystemLog( int opData, SRxLOBData *pLOB, STR_EMITTER *pEmitter );

};

#endif

#endif // !defined(AFX_SIGANAL_H__B1861C90_58D2_419C_B285_F44D27936048__INCLUDED_)
