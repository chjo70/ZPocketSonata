// GetPdw.h: interface for the CGetPdw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETPDW_H__536AD6D5_B815_4B18_B73A_C2339E4AE028__INCLUDED_)
#define AFX_GETPDW_H__536AD6D5_B815_4B18_B73A_C2339E4AE028__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Task.h"
#include "ELMsgQThread.h"

#include "../PdwFilter.h"

#ifdef __cplusplus

class CGetPdw : public CTask
{
public:
	
private:
	CFile m_PDWFile;
	CFile m_StorePDWFile;
	bool m_bStartFlag;

	bool m_bOpen;
	bool m_bEndOfFile;

	SQMsg m_SendQMsg;

	STR_LOWHIGH m_FilterFrq[2];
	CString m_strPDWFilename;

	USHORT m_nBitMode;
	STR_CHANNEL_SELECTION m_nMaxChannel[ALL_BAND];
	STR_CW_CONTROL m_nCWControl[ALL_BAND];
	STR_PDWDATA m_stPDWData;

	int m_PdwFile[ALL_BAND+1];

	enum COLLECT_MODE m_mode;

	int m_nMemoryBank;
	int m_nFilter;
	BOOL **m_pbSendAnal;
	
	UINT m_nTotalCountOfPDW;
	UINT m_nCountOfPDW;
	_PDW *m_pCollectPdw;
	_PDW *m_pBitCollectPdw;

	SCollectingList m_stCollectingList;

public:
	virtual void intHandlerCollect();

private:
	static void IsrWrapper( CGetPdw *pSelf );
	
public:
	bool Init(CString strFilename);
	void ClosePDWFile();
	int GetIniThreshold( enum BAND_INFO band );
	void SetScanFilter( STR_PDWFILTER_INFO *pFilterInfo );
	void SetFilterFreq( STR_LOWHIGH *pFilterFreq );
	void InitCWThreshold( float *pThreshold );
	//void RunBITAllPDW( UNI_PP_BIT *pPPBit );
	void RunRFPathBit();
	int GetInitCWThreshold( enum BAND_INFO band );
	void ControlCWThreshold( enum BAND_INFO band );
	void ClearCWMark( STR_AET *pAet );
	//void SetCWThreshold( STR_AET *pAet );
	BOOL IsUseCWControl( enum BAND_INFO band );
	void ClearMaxChannel( STR_AET *pAet );
	BOOL CouldUseMaxChannel( enum BAND_INFO band );
	void SetMaxChannel( STR_AET *pAet, enum CHANNEL_SELECTION channel_selection );

	// 메시지 처리
	void ReqSendCollectingList(SCollectingList *pstCollectingList);

	// Opcode 별 메시지 처리
	void ReqSendCollectingList(SQMsg *psqMsg);

	//inline void UpdateScanMode( enum BAND_INFO nBand ) { m_thePdwFilter->UpdateScanMode( nBand ); };
	//inline void RequestPowerOnIBit1() { theGenPulseInfo->RequestPowerOnIBit(); }
	//inline enum BAND_INFO GetFilterBand() { return m_ci.nBand; }
	//inline void RequestPowerOnInit() { theGenPulseInfo->RequestPowerOnInit(); }
	//inline void UpdateChannelData( UINT nReceiver ) { theGenPulseInfo->UpdateChannelData(nReceiver); }
	//inline void GetChannelVersion() { theGenPulseInfo->GetChannelVersion(); }
	//inline void ClearTemperature() { theGenPulseInfo->ClearTemperature(); }
	inline BOOL IsSendAnal( enum ANAL Anal, int noFilter ) { return m_pbSendAnal[Anal][noFilter]; }
	inline COLLECT_MODE GetMode() { return m_mode; }
	inline void SetMode( COLLECT_MODE mode ) { m_mode=mode; }
	//inline int GetCoScan() { return m_thePdwFilter->GetCoScan(); }
	//inline STR_FILTER_INFO *GetFilterInfo() { return & m_fi; }
	//inline int GetCoTrack() { return m_thePdwFilter->GetCoTrack(); }
	//inline void SetBand( enum BAND_INFO nBand ) { m_nBand = nBand; }
	//inline enum BAND_INFO GetBand( enum ANAL Anal, int index ) { return m_thePdwFilter->GetBand( Anal, index ); }


	BOOL CompMeanDiff( int x, int y, int thresh );
	BOOL VerifyBITPDW();
	void ClosePDWFiles();
	void CreatePDWFiles();
	void ClearCBit();
	void RequestPowerOnIBit();
	void RequestPowerOnCBit();
	void RequestUserPBit();
	void RemovePDWFiles();
	void ClearIBit();
 	void ClearPBit();
	void SendPdwData();
	void SetCollect();
	void StopAnal();
	void SendSwitchControl( int offset=0 );
	inline void Timer() { }
	void SetColStat( enum ANAL Anal, int noFilter, enum FILTER_STAT stat );
	// inline void SetColStat( enum ANAL Anal, int noFilter, enum FILTER_STAT stat ) { m_thePdwFilter->SetColStat( Anal, noFilter, stat ); }
	//void SetColStat( enum ANAL Anal, enum FILTER_STAT stat ) { m_thePdwFilter->SetColStat( Anal, stat ); }
	BOOL BackupPDWFiles();
	void SavePDW();
	//inline BOOL IsFullNewCol() { return m_thePdwFilter->IsFullNewCol(); }
	inline void SetSendAnal( enum ANAL Anal, int noFilter ) { m_pbSendAnal[Anal][noFilter]=TRUE; }
	inline void ClearSendAnal( enum ANAL Anal, int noFilter ) { m_pbSendAnal[Anal][noFilter]=FALSE; }
	//inline enum FILTER_STAT GetNewColStat() { return m_thePdwFilter->GetNewColStat(); };
	//inline CPdwFilter *GetPdwFilter() { return m_thePdwFilter; }
	void SendSigAnal( enum ANAL Anal, int noFilter );
	//void SendAllSigAnal( );
	//void CollectByFilter();
	//void SetCountTime();
	void SetFreqAoaPwSa();
	//void NextBand();
	int GetFilterChannel();
	void MallocBuffer();
	void PrintAllPDW( _PDW *pPdw, UINT count );
	void WideFreqAoaPwSa();
	void ReadPDWFileBlock();
	void CollectingPDW(BOOL bBitMode, STR_PDWDATA *pstPDWData);
	void StorePDWFile();
	bool Start();
	void ScheduleCollect();
	void ClearInit();
	void SetCollectParameter( int nFilter );
	BOOL ParseMessage( SQMsg *psqMsg );
	void Run();
	void InitTask();
	void InitVar();

	// 타 타스크 관련 메시지 함수
	void SendMessageToAnalTask(SQMsg *psqMsg, int iIndexOfCollectingList=0 );

	CGetPdw( char *pTaskName );
	virtual ~CGetPdw();

};

#endif

#endif // !defined(AFX_GETPDW_H__536AD6D5_B815_4B18_B73A_C2339E4AE028__INCLUDED_)
