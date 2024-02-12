/**

    @file      SAnalSCN.h
    @brief     interface for the CSAnalScan class.
    @details   ~
    @author    조철희
    @date      2.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SStruct.h"

#include "../SigAnal/AnalPRI.h"
#include "../SigAnal/MakeAET.h"

#include "../SigAnal/_SigAnal.h"

enum LowHighThreatType { LOWTHREAT=0, HIGHTHREAT, OBSCURITY } ;


#ifdef __cplusplus

class CScanSigAnal;

class CSAnalScan : public CAnalPRI
{
private:
    int m_iMinSteadyPAAmplitude;
    unsigned int m_uiMinConicalPeriod;
    unsigned int m_uiMaxConicalPeriod;

    SRxABTData *m_pScnAet;

    unsigned int m_uiMaxPdw;

protected:
    CScanSigAnal *m_pScanSigAnal;

protected:
    STR_EMITTER *m_pEmitter;

	UINT m_uiCanPeak[_spMaxSample];

	/*! \bug  스캔 주기를 int 에서 unsigned integer로 형 변경함.
	    \date 2009-10-08 12:39:49, 조철희
	*/
    STR_SCANRESULT m_stScanResult;

	STR_AUTOCOR m_stAutoCor;
	UINT m_uiCoCanPeak;

	UINT m_nSampleTime;
	int m_noCh;
	unsigned int m_uinoEMT;

	STR_SCANPT *m_pScanPt;
	STR_SAMPLE m_stSample;
    //UINT m_nCoModWc[TOTAL_ITEMS_OF_THREAT_NODE +1];

    UINT m_uiOffCoPDW;

private:
    void CalcSamplingTime();
    void Interpolation();
    void ReplaceOffSampling();
    void SamplingProcess();
    float Normalize();
    bool CheckSteadySignal();
    void AutoCorerelation();
    void KurtosisSkewness( STR_SAMPLE *pSample );
    EN_SCANRESULT ScanTypeDecision();
    EN_SCANRESULT ScanTypeLowDecision( UINT uiPrdVer, STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
    UINT FindPeak();

    void SearchLowHghInArray( int *series, UINT co, STR_LOWHIGH *lh );

    UINT CalcSamplingTime( UINT priMean );
    UINT CalcSamplingTime( UINT noEMT, UINT priMean );

    void SaveScanResult( STR_SCANRESULT *pstScanResul );

public:
    CSAnalScan( void *pParent, unsigned int uicoMaxPdw, const char *pThreadName=NULL );
    virtual ~CSAnalScan();

    STR_EMITTER *WhichTheMainEmitter();

    void SaveScanPulse( STR_PDWINDEX *pPdwIndex );

    STR_PULSE_TRAIN_SEG *GetPulseSeg() override;

	//bool CompMeanDiff(int x, int y, int thresh);
	//float MeanInArray( UINT *series, UINT co );
    //inline void GetScanRes( ENUM_AET_SCAN_TYPE *penScanType, UINT *pScanPrd ) { /* *penScanType = m_enScnType, *pScanPrd= m_uiScnPrd; */}
	// inline STR_SCANPT *GetScanPulseTrain( int noCh ) { return & stScanPt[m_noCh]; }

	//bool CheckControlWc( UINT noEMT );

	UINT GetFlagControlWc( UINT noEMT );
    ENUM_AET_SCAN_TYPE DetectNonTrackScanPattern( STR_SAMPLE *pSample, STR_AUTOCOR *pAutocf );
    ENUM_AET_SCAN_TYPE HighIllustrationTest2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
	UINT PeriodVerify( void );

    EN_SCANRESULT AnalScan( STR_SCANRESULT *pstScanResult );
	void Init( unsigned int uinoEMT=0, int noCh=0 );
    void MakeLOBDataFromEmitter( int iLOBData, STR_EMITTER *pEmitter, int idxEmitter );

    bool KnownAnalysis();

    int FindPeakInHist(unsigned int uiCount, PDWINDEX *pPdwIndex ) override;
    bool CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return 0; }
    //void DeleteAllSeg( STR_EMITTER *pEmitter )  { }
    void ExtractRefStable() { }

    bool ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange ) { return 0; }
    //UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri ) { return 0; }

    //void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof ) { }

    //void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { }
    unsigned int ExtractStagger( _TOA framePri, STR_EMITTER *pEmitter) { return 0; }
    UINT MedianFreq( STR_MINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );
    UINT MedianPA( STR_MINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );

    _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount );

    int GetBand() override;
    //void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile ) override;

    SRxLOBData *GetLOBData( int index=0 );

    unsigned int GetCoSeg() override;

    //////////////////////////////////////////////////////////////////////////////////////
    int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
    unsigned int GetColPdw() { return 0; }
    int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount );
    int VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount);
    void MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType) { }

    unsigned int GetCoEmitter() { return 0; }
    STR_EMITTER *GetEmitter() { return m_pEmitter; }
    UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg );
    STR_PDWPARAM* GetPdwParam() ;

	void GetCollectTime( struct timespec *pTimeSpec );

    ENUM_ANAL_TYPE GetAnalType();

    void DISP_FineLOB( SRxLOBData *pLOBData ) { }
    bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2, int iMaxMiss, bool bForceMerge=false );

    unsigned int IsStorePDW();

    void SaveDebug( const char *pSourcefile, int iLines );

    CMakeAET* GetMakeAET() { return NULL; }

    inline unsigned int GetPDWID() { return (UINT) -1; }
    inline unsigned int GetOpInitID() { return (UINT) -1; }

    void SetKnownIndexEmitter(unsigned int uiIndex, int iIdxEmitter) { }

#if defined(_ELINT_) || defined(_XBAND_)
    EN_RADARCOLLECTORID GetCollectorID();
    char *GetTaskID();
#endif

    inline void *GetParentSigAnal() { return ( void * ) m_pScanSigAnal; }
    inline STR_SCANRESULT *GetScanResult() { return & m_stScanResult; }

};

#endif
