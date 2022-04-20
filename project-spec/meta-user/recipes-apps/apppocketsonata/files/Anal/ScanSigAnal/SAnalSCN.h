// SAnalScan.h: interface for the CSAnalScan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SANALSCAN_H__649D0457_9E49_4DE3_ACF7_3D07257B7545__INCLUDED_)
#define AFX_SANALSCAN_H__649D0457_9E49_4DE3_ACF7_3D07257B7545__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SStruct.h"

#include "../SigAnal/AnalPRI.h"
#include "../SigAnal/MakeAET.h"

#include "../SigAnal/_SigAnal.h"

//##ModelId=452B0C450116
enum LowHighThreatType { LOWTHREAT=0, HIGHTHREAT, OBSCURITY } ;
//##ModelId=452B0C45012A
enum PseudoScanType { TrackUnknown=10, DetectUnknown, LowIllustrationTest } ;


#ifdef __cplusplus

class CScanSigAnal;

//##ModelId=452B0C45013E
class CSAnalScan : public CAnalPRI, public CMakeAET
{
private:
    SRxABTData *m_pScnAet;

    int m_uiMaxPdw;

    SRxLOBData m_LOBData[ MAX_AET+1 ];


protected:
    //##ModelId=452B0C5300EF
    CScanSigAnal *m_pScanSigAnal;

protected:
    STR_EMITTER *m_pEmitter;

	//##ModelId=452B0C450148
	UINT m_nCanPeak[_spMaxSample];

	/*! \bug  스캔 주기를 int 에서 unsigned integer로 형 변경함.
	    \date 2009-10-08 12:39:49, 조철희
	*/
	//##ModelId=452B0C450152
    UINT m_uiScnPrd;										//! 스캔 주기값
	//##ModelId=452B0C450153
	UINT m_uiScnTyp;										//! 스캔 형태

	//##ModelId=452B0C45015D
	STR_AUTOCOR m_nAutoCor;
	//##ModelId=452B0C450166
	UINT m_nCoCanPeak;

	//##ModelId=452B0C450167
	UINT m_nSampleTime;
	//##ModelId=452B0C450170
	int m_noCh;
	//##ModelId=452B0C450171
	int m_noEMT;

	//##ModelId=452B0C450185
	STR_SCANPT *m_pScanPt;
	//##ModelId=452B0C45018E
	STR_SAMPLE m_nSample;
	//##ModelId=452B0C450192
    UINT m_nCoModWc[256+1];

    UINT stOffPdw;


    //SRxLOBData m_stLOBData;

public:
    STR_EMITTER *TakeTheScanMainEmitter();

    void SaveScanPulse( STR_PDWINDEX *pPdwIndex );

    STR_PULSE_TRAIN_SEG *GetPulseSeg();

	//BOOL CompMeanDiff(int x, int y, int thresh);
	//float MeanInArray( UINT *series, UINT co );
	//##ModelId=452B0C450198
    inline void GetScanRes( unsigned int *pScanType, UINT *pScanPrd ) { *pScanType = m_uiScnTyp, *pScanPrd= m_uiScnPrd; }
	//##ModelId=452B0C45019B
	// inline STR_SCANPT *GetScanPulseTrain( int noCh ) { return & stScanPt[m_noCh]; }

	//##ModelId=452B0C4501A3
	BOOL CheckControlWc( UINT noEMT );
	//##ModelId=452B0C4501AC
	UINT GetFlagControlWc( UINT noEMT );
	//##ModelId=452B0C4501AE
	UINT DetectNonTrackScanPattern( STR_SAMPLE *pSample, STR_AUTOCOR *pAutocf );
	//##ModelId=452B0C4501B6
    ENUM_AET_SCAN_TYPE HighIllustrationTest2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
	//##ModelId=452B0C4501B9
	UINT PeriodVerify( void );
	//##ModelId=452B0C4501C0
	//float SDevInArray( UINT *series, int co, float mean );
	//##ModelId=452B0C4501C4
	void KurtosisSkewness( STR_SAMPLE *pSample );
	//##ModelId=452B0C4501D5
	UINT ScanTypeDecision( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
    UINT ScanTypeLowDecision(UINT uiPrdVer, STR_SAMPLE *pSample, STR_AUTOCOR *pAcf);
	//##ModelId=452B0C4501DF
	UINT FindPeak( STR_AUTOCOR *pAutoCor );
	//##ModelId=452B0C4501E8
	void AutoCorerelation( STR_SAMPLE *pSample, STR_AUTOCOR *pAutoCor );
	//##ModelId=452B0C4501EB
    bool CheckSteadySignal( STR_SAMPLE *pSample, UINT meanY );
	//##ModelId=452B0C4501F3
	float Normalize( int *series, UINT co, float *norm );
	//##ModelId=452B0C4501FC
	void Interpolation( STR_SAMPLE *pSample, STR_SCANPT *pScanPt );
	//##ModelId=452B0C4501FF
	void ReplaceOffSampling( STR_SAMPLE *pSample, STR_SCANPT *pScanPt );
	//##ModelId=452B0C450208
	void SearchLowHghInArray( int *series, UINT co, STR_LOWHIGH *lh );
	//##ModelId=452B0C450213
	void SamplingProcess();
	//##ModelId=452B0C450214
	UINT CalcSamplingTime( UINT priMean );
	//##ModelId=452B0C45021B
	UINT CalcSamplingTime( UINT noEMT, UINT priMean );
	//##ModelId=452B0C45021E
	void CalcSamplingTime();
	//##ModelId=452B0C450224
    EN_SCANRESULT AnalScan( int preAnalStat=0 );
	//##ModelId=452B0C450226
	void Init( int noEMT=0, int noCh=0 );
    void MakeLOBDatafromEmitter( STR_EMITTER *pEmitter, int idxEmitter );

    BOOL KnownAnalysis();

    int FindPeakInHist(unsigned int uiCount, PDWINDEX *pPdwIndex );
    //##ModelId=452B0C57019E
    BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return 0; }
    //##ModelId=452B0C5701A8
    void DeleteAllSeg( STR_EMITTER *pEmitter )  { }
    //##ModelId=452B0C5701AB
    void ExtractRefStable() { }

    //##ModelId=452B0C5701B4
    BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange ) { return 0; }
    //##ModelId=452B0C5701BC
    UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri ) { return 0; }

    void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof ) { }

    //##ModelId=452B0C5701C8
    void MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { }
    //##ModelId=452B0C5701DA
    unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter) { return 0; }
    //##ModelId=452B0C5701E4
    UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );

    //##ModelId=452B0C5701F8
    _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount );

    int GetBand();
    void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile );

    SRxLOBData *GetLOBData( int index=0 );

    unsigned int GetCoSeg();


    //////////////////////////////////////////////////////////////////////////////////////
    int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
    //##ModelId=452B0C56000C
    int GetColPdw() { return 0; }
    //##ModelId=452B0C56000E
    int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount );
    //##ModelId=452B0C560012
    int VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount);
    //##ModelId=452B0C560019
    void MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType) { }

    //##ModelId=452B0C56002C
    int GetCoEmitter() { return 0; }
    //##ModelId=452B0C560034
    STR_EMITTER *GetEmitter() { return m_pEmitter; }
    //##ModelId=452B0C560036
    UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg );
    STR_PDWPARAM* GetPdwParam();

	void GetCollectTime( struct timespec *pTimeSpec );


    void DISP_FineAet( SRxLOBData *pLOBData ) { }
    unsigned int IsStorePDW();

    CMakeAET* GetMakeAET() { return NULL; }

    inline unsigned int GetPDWID() { return (UINT) -1; }


#if defined(_ELINT_) || defined(_XBAND_)
    EN_RADARCOLLECTORID GetCollectorID();
    char *GetTaskID();
#endif


	//##ModelId=452B0C45022E
    CSAnalScan( void *pParent, int coMaxPdw );
	//##ModelId=452B0C450230
	virtual ~CSAnalScan();

};

#endif

#endif // !defined(AFX_SANALSCAN_H__649D0457_9E49_4DE3_ACF7_3D07257B7545__INCLUDED_)
