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
enum PseudoScanType { TrackUnknown=10, DetectUnknown, LowIllustrationTest } ;


#ifdef __cplusplus

class CScanSigAnal;

class CSAnalScan : public CAnalPRI, public CMakeAET
{
private:
    SRxABTData *m_pScnAet;

    unsigned int m_uiMaxPdw;

    SRxLOBData m_LOBData[ MAX_AET+1 ];


protected:
    //##ModelId=452B0C5300EF
    CScanSigAnal *m_pScanSigAnal;

protected:
    STR_EMITTER *m_pEmitter;

	//##ModelId=452B0C450148
	UINT m_uiCanPeak[_spMaxSample];

	/*! \bug  스캔 주기를 int 에서 unsigned integer로 형 변경함.
	    \date 2009-10-08 12:39:49, 조철희
	*/
    UINT m_uiScnPrd;										//! 스캔 주기값
	unsigned char m_ucScnTyp;										//! 스캔 형태

	STR_AUTOCOR m_nAutoCor;
	UINT m_uiCoCanPeak;

	UINT m_nSampleTime;
	int m_noCh;
	unsigned int m_uinoEMT;

	STR_SCANPT *m_pScanPt;
	STR_SAMPLE m_nSample;
    UINT m_nCoModWc[256+1];

    UINT stOffPdw;

public:
    CSAnalScan( void *pParent, unsigned int uicoMaxPdw );
    virtual ~CSAnalScan();

    STR_EMITTER *WhichTheMainEmitter();

    void SaveScanPulse( STR_PDWINDEX *pPdwIndex );

    STR_PULSE_TRAIN_SEG *GetPulseSeg();

	//bool CompMeanDiff(int x, int y, int thresh);
	//float MeanInArray( UINT *series, UINT co );
    inline void GetScanRes( unsigned int *pScanType, UINT *pScanPrd ) { *pScanType = m_ucScnTyp, *pScanPrd= m_uiScnPrd; }
	// inline STR_SCANPT *GetScanPulseTrain( int noCh ) { return & stScanPt[m_noCh]; }

	//bool CheckControlWc( UINT noEMT );

	UINT GetFlagControlWc( UINT noEMT );
	UINT DetectNonTrackScanPattern( STR_SAMPLE *pSample, STR_AUTOCOR *pAutocf );
    ENUM_AET_SCAN_TYPE HighIllustrationTest2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
	UINT PeriodVerify( void );

	//float SDevInArray( UINT *series, int co, float mean );

	void KurtosisSkewness( STR_SAMPLE *pSample );
	UINT ScanTypeDecision( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
    UINT ScanTypeLowDecision(UINT uiPrdVer, STR_SAMPLE *pSample, STR_AUTOCOR *pAcf);
	UINT FindPeak( STR_AUTOCOR *pAutoCor );
	void AutoCorerelation( STR_SAMPLE *pSample, STR_AUTOCOR *pAutoCor );
    bool CheckSteadySignal( STR_SAMPLE *pSample, UINT meanY );
	float Normalize( int *series, UINT co, float *norm );
	void Interpolation( STR_SAMPLE *pSample, STR_SCANPT *pScanPt );
	void ReplaceOffSampling( STR_SAMPLE *pSample, STR_SCANPT *pScanPt );
	void SearchLowHghInArray( int *series, UINT co, STR_LOWHIGH *lh );
	void SamplingProcess();
	UINT CalcSamplingTime( UINT priMean );
	UINT CalcSamplingTime( UINT noEMT, UINT priMean );
	void CalcSamplingTime();
    EN_SCANRESULT AnalScan( int preAnalStat=0 );
	void Init( unsigned int uinoEMT=0, int noCh=0 );
    void MakeLOBDataFromEmitter( int iLOBData, STR_EMITTER *pEmitter, int idxEmitter );

    bool KnownAnalysis();

    int FindPeakInHist(unsigned int uiCount, PDWINDEX *pPdwIndex );
    bool CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return 0; }
    void DeleteAllSeg( STR_EMITTER *pEmitter )  { }
    void ExtractRefStable() { }

    bool ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange ) { return 0; }
    UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri ) { return 0; }

    void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof ) { }

    void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { }
    unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter) { return 0; }
    UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );

    _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount );

    int GetBand();
    void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile );

    SRxLOBData *GetLOBData( int index=0 );

    unsigned int GetCoSeg();

    //////////////////////////////////////////////////////////////////////////////////////
    int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
    unsigned int GetColPdw() { return 0; }
    int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount );
    int VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount);
    void MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType) { }

    unsigned int GetCoEmitter() { return 0; }
    STR_EMITTER *GetEmitter() { return m_pEmitter; }
    UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg );
    STR_PDWPARAM* GetPdwParam();

	void GetCollectTime( struct timespec *pTimeSpec );


    void DISP_FineLOB( SRxLOBData *pLOBData ) { }
    bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );

    unsigned int IsStorePDW();

    CMakeAET* GetMakeAET() { return NULL; }

    inline unsigned int GetPDWID() { return (UINT) -1; }
    inline unsigned int GetOpInitID() { return (UINT) -1; }

    void SetKnownIndexEmitter(unsigned int uiIndex, int iIdxEmitter) { }


#if defined(_ELINT_) || defined(_XBAND_)
    EN_RADARCOLLECTORID GetCollectorID();
    char *GetTaskID();
#endif

};

#endif
