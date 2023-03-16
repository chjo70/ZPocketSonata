// AnalPRI.h: interface for the CAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALPRI_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_ANALPRI_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

#include "../SigAnal/MakeAET.h"

// 병합 방법 정의
enum enEMITTER_MERGE_OPTION { 
    enMERGE_LEFT=0,		// pEmitter1 과 pEmitter2 에서 pEmitter1 으로 합한다.
	enMERGE_RIGHT,		// pEmitter1 과 pEmitter2 에서 pEmitter2 으로 합한다.
    enNO_MERGE 
} ;

#ifdef __cplusplus

//##ModelId=452B0C5603CD
class CAnalPRI
{
protected:
    DEFINE_ANAL_PVAR_

public:
    unsigned int m_uiAnalEmitter;
    
    unsigned int m_uiCoEmitter;
    unsigned int m_uiStepEmitter;
    
    unsigned int m_uiCoSeg;    
    unsigned int m_uiAnalSeg;

private:
	UINT m_spdiffaoa[ 6 ];

    PDWINDEX *m_pMergePdwIndex;
    PDWINDEX *m_pBinSearchIndex;

    unsigned int m_uiMaxPdw;

    STR_PULSE_TRAIN_SEG *m_pSeg;
    STR_PULSE_TRAIN_SEG m_DwlSeg;

    STR_EMITTER m_Emitter[MAX_AET];
    STR_EMITTER m_StaggerEmitter;           // 스태거 분석하기 위한 임시 가상 에미터 저장소

    // 패턴 형태 분석을 분석하기 위한 데이터
    int *m_p1PrimeData;
    int *m_p2PrimeData;
	PATTERN_TYPE m_enPatternType;

    // 주파수 패턴 및 PRI 패턴 정보를 분석하기 위한 내부 변수들
    UINT m_SamplingTime;
    unsigned int m_CoSample;
    _TOA *m_pSampleToa;
    int *m_pSampleData;
    int *m_pNormData;
    float m_skewness;
    float m_kurtosis;

    //##ModelId=452B0C5700B8
    unsigned int m_uiCoData;
    //##ModelId=452B0C5700C2
    _TOA *m_pDataX;
    //##ModelId=452B0C5700C3
    _TOA *m_pDataY;

    //##ModelId=452B0C5700CC
    float *m_pAcf;
    //##ModelId=452B0C5700D6
    unsigned int m_CoAcf;

    //##ModelId=452B0C5700E0
    _TOA *m_pCanPeak;

    //##ModelId=452B0C5700EA
    _TOA *m_pPulseDtoa;

    //##ModelId=452B0C5700F4
    float m_Period;

    // 스태거 분석하기 위한 내부 변수들
    //
    //##ModelId=452B0C5700FE
    int m_CoPulseDtoa;
    // ACF 연산을 사용하여 스태거 분석하기 위한 변수들...
    //-- 조철희 2005-05-26 08:04:33 --//
    //##ModelId=452B0C570108
    _TOA *m_pPulseToa;
    //##ModelId=452B0C570112
    _TOA *m_pToaAcf;
    //##ModelId=452B0C570126
    unsigned int m_coCanPeak;
    //##ModelId=452B0C570130
    _TOA m_nMaxPeak;

    //
    //##ModelId=452B0C57013A
    int m_nRefFramePri;
    //##ModelId=452B0C57013B
    _TOA *m_pRefFramePri;
    //##ModelId=452B0C570144
    UINT m_nTmpStaggerLevel[MAX_FREQ_PRI_STEP];
    //##ModelId=452B0C57014E
    UINT m_nStaggerLevel[MAX_FREQ_PRI_STEP];

    //##ModelId=452B0C570163
    STR_DTOA_HISTOGRAM m_DtoaHist;
    STR_HOPPING_DATA m_HoppingData;

    int m_iCoDwellLevel;
    STR_DWELL_LEVEL m_stDwellLevel[_MAX_DWELL_LEVEL];    

private:
    void NormalizeTOA(STR_EMITTER *pEmitter);
    void AnalyzeACF(STR_EMITTER *pEmitter);

    BOOL CheckStaggerLevel( STR_EMITTER *pStaggerEmitter, int iMatch, int iLevelCount );

	// 에미터 병합 및 비교 관련 함수 모음
	enEMITTER_MERGE_OPTION WhichMerge(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
	bool CheckMergeEmitter(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, enEMITTER_MERGE_OPTION *pMrgOption);
	void MergeEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter, enEMITTER_MERGE_OPTION enMergeOption);

public:
    void CalHopLevel( STR_EMITTER *pEmitter );
    BOOL IsFreqHopping( STR_EMITTER *pEmitter );
    float IMeanInArray( int *series, UINT co );

    //void MakeSegOfEmitter(STR_EMITTER *pEmitter);

    void DNSAnalysis();
    bool CheckDNSPossibility(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
    void MergePdwIndexInEmitter(STR_EMITTER *pEmitter);
    int CalcDiffAOA(int iAOA1, int iAOA2);
    bool CheckOverlapSeg(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
    bool CheckFreqType(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
    void HoppingAnalysis();
    void MakeFreqHistogram(STR_EMITTER *pEmitter);
    void ExtractHoppingLevel(STR_EMITTER *pEmitter);
    BOOL HoppingDecision(STR_EMITTER *pEmitter);
    void SetHoppingInfo(STR_EMITTER *pEmitter);

    inline void PrintAllSeg() { }

    //##ModelId=452B0C57016C
    inline void SetAnalSeg( unsigned int uiSeg ) { m_uiAnalSeg=uiSeg; }
    //##ModelId=452B0C57016E
    //inline void MergeGrouping() { MergeGrouping(); }

    //##ModelId=452B0C570178
    inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return & m_DtoaHist; }
    //##ModelId=452B0C570180
    inline void SetPulseSeg( STR_PULSE_TRAIN_SEG *pSeg ) { m_pSeg = pSeg; }
    //##ModelId=452B0C570182
    inline unsigned int GetCoEmitter() { return m_uiCoEmitter; }
    inline void SetCoEmitter( UINT coEmitter ) { m_uiCoEmitter=coEmitter; }
    //##ModelId=452B0C57018A
    inline void SetAnalEmitter( unsigned int uiEmitter) { m_uiAnalEmitter = uiEmitter; }
    //##ModelId=452B0C57018C
    inline STR_EMITTER *GetEmitter() { return m_Emitter; }

    //////////////////////////////////////////////////////////////////////////
    // 가상 함수 선언...
    //##ModelId=452B0C570194
    virtual int FindPeakInHist(unsigned int uiCount, PDWINDEX *pPdwIndex )=0;
    //##ModelId=452B0C57019E
    virtual BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )=0;
    //##ModelId=452B0C5701A8
    virtual void DeleteAllSeg( STR_EMITTER *pEmitter )=0;
    //##ModelId=452B0C5701AB
    virtual void ExtractRefStable()=0;
    //##ModelId=452B0C5701B2
    virtual unsigned int GetCoSeg()=0;
    //##ModelId=452B0C5701B4
    virtual BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange )=0;
    //##ModelId=452B0C5701BC
    virtual UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri )=0;
    //##ModelId=452B0C5701C6
    virtual STR_PULSE_TRAIN_SEG *GetPulseSeg()=0;
    virtual void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof )=0;
    virtual void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter )=0;
    virtual unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter)=0;    
    virtual UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount )=0;    
    virtual _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount )=0;
    virtual int GetBand()=0;
    virtual void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )=0;
    virtual CMakeAET* GetMakeAET()=0;
    virtual bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )=0;

    bool CompAOA( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    
    void CalcEmitterPW( STR_EMITTER *pEmitter );
    
    void PrintAllEmitter( unsigned int iEmitter=0, const char *pszString=NULL, enPRI_TYPE enPRITYpe= _UNKNOWN_PRI );
    //##ModelId=452B0C57022B
    BOOL CheckSawPattern(PATTERN_TYPE *pSawPatternType );
    //##ModelId=452B0C570235
    UINT CheckSinePattern();
    //##ModelId=452B0C570236
    UINT CalPrimeDifference();
    //##ModelId=452B0C570237
    void CalTwoPrime();
    //##ModelId=452B0C57023E
    BOOL GetDtoaRange( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange );
    //##ModelId=452B0C570248
    void RemoveNoiseDtoa( UINT count );
    //##ModelId=452B0C57024A
    void CalDtoaMeanMinMax( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange );
    
    BOOL GetDtoaRange( int peak_index, STR_LOWHIGH *pRange );    
    void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );
    
    void MakeStaggerLevel( _TOA *pStaggerLevel, int CoStagger );
    //##ModelId=452B0C57027C
    BOOL CheckFreqHopping( STR_EMITTER *pEmitter );
    //##ModelId=452B0C570285
    BOOL VerifyStaggerLevel( STR_EMITTER *pStaggerEmitter, STR_EMITTER *pEmitter=NULL );
    //##ModelId=452B0C57028F
    //float ISDevInArray( int *series, UINT co, UINT mean );
    //##ModelId=452B0C5702A2
    void KurtosisSkewness();
    //##ModelId=452B0C5702AC
    BOOL CompareAllStaggerLevel( STR_EMITTER *pEmitter, STR_PULSE_TRAIN_SEG *pSeg );
    int GetMaxPdw();

    BOOL DwellAnalysis( STR_EMITTER *pEmitter );
    BOOL ExtractDwellPT();
    BOOL FindBin( UINT bin );
    BOOL FindDtoa( _TOA priMean );
    BOOL FindDwellLevel();
    BOOL FindDwellLevel( STR_EMITTER *pEmitter );    
    void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange=NULL );
    
    void DwellAnalysis();
    BOOL CheckContiStable( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    void MergePDWIndexInSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    
    void CheckHarmonicStaggerLevel( STR_EMITTER *pStaggerEmitter );
    
    BOOL StaggerLevelAnalysis( STR_EMITTER *pEmitter );
    void MakeStaggerPRI( STR_EMITTER *pEmitter );

    PATTERN_TYPE HighIllustrationTest( STR_EMITTER *pEmitter );

    void FindPeriod();
    void AutoCorerelation();
    void Normalize();
    void ReplaceOffSampling();
    void Interpolation();
    //##ModelId=452B0C570309
    void SamplingProcess( STR_EMITTER *pEmitter );
    //##ModelId=452B0C570311
    void CalcSamplingTime( STR_EMITTER *pEmitter );
    //##ModelId=452B0C570313
    float PatternAnalysis( STR_EMITTER *pEmitter );
    bool FindPeak();
    
    //int GetContiThreshold( int iCount );
    //##ModelId=452B0C570325
    BOOL CheckStaggerLevel( STR_EMITTER *pOrgEmitter, STR_EMITTER *pStaggerEmitter, int match_index );
    
    UINT CheckHarmonic(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2);    
    UINT CheckHarmonic(_TOA priMean1, _TOA priMean2 ,_TOA uiThreshold=(3*_spOneMicrosec) );
	UINT CheckHarmonic(STR_MINMAX_TOA *pstPRI1, STR_MINMAX_TOA *pstPRI2);
    
    bool CompFreq( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    
    void CalcEmitterFrq( STR_EMITTER *pEmitter );
    //##ModelId=452B0C570375
    void CalcEmitterPri( STR_EMITTER *pEmitter );
    //##ModelId=452B0C57037F
    bool CompFreq( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    //##ModelId=452B0C57038A
    BOOL BinSearchInPdwIndex( int from, int to, int search_value );

    BOOL IncludePulseTrain(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
    int ExtractStagger( STR_EMITTER *pEmitter, UINT framePri );
    BOOL FindRefFramePri( UINT dtoa );
    _TOA CheckFramePRI( STR_EMITTER *pEmitter );
    UINT CheckHarmonic(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
    
    
    bool OverlappedStableSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    bool OverlappedSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    
    void MergeGrouping();

    bool StaggerAnalysis( STR_EMITTER *pEmitter );
    bool FindFramePRI( STR_EMITTER *pEmitter );


    //##ModelId=452B0C580025
    void SelectMainSeg(STR_EMITTER *pEmitter);
    
    BOOL DecisionEmitter( STR_EMITTER *pEmitter );
    
    BOOL AnalLobe( STR_EMITTER *pEmitter );
    //##ModelId=452B0C580043
    void MergePDWIndexInSeg( STR_EMITTER *pEmitter );

    //##ModelId=452B0C58004D
    enFREQ_TYPE AnalFreqType( STR_EMITTER *pEmitter );
    //##ModelId=452B0C580056
    enSIGNAL_TYPE AnalSignalType( STR_EMITTER *pEmitter );
    //##ModelId=452B0C580058
    void PatternAnalysis();
    //##ModelId=452B0C58005F
    void StaggerAnalysis();
    //##ModelId=452B0C580060
    void GroupingUnknown();
    //##ModelId=452B0C580061
    void GroupingJitter( BOOL bDecisionEmitter=FALSE );
    void GroupingJitterWithJitter( STR_PULSE_TRAIN_SEG *pRefSeg, unsigned int uiLoop, BOOL bDecisionEmitter );
    void GroupingJitterWithStable( STR_PULSE_TRAIN_SEG *pRefSeg, unsigned int uiLoop, BOOL bDecisionEmitter );
    //##ModelId=452B0C58006A
    void GroupingStagger( BOOL bDecisionEmitter=FALSE );
    //##ModelId=452B0C58006C
    void GroupingStable( BOOL bDecisionEmitter=FALSE );
    void GroupingDwell( BOOL bDecisionEmitter=TRUE );

    BOOL CalcPRILevel( STR_EMITTER *pEmitter );
    void AddDwellLevel( STR_DWELL_LEVEL *pSTR_DWELL_LEVEL );
    bool MakeDwellLevel( STR_EMITTER *pEmitter );

    int (CAnalPRI::*qsort_memberfunc)( const void *arg1, const void *arg2 );
    
    void SortEmitter();
    void SwapEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter );
    _TOA GetMinPulseTrainMean( STR_EMITTER *pEmitter );

    //##ModelId=452B0C580074
    void Analysis();
    //##ModelId=452B0C580075
    void Init();

    void InitSeg(STR_EMITTER *pEmitter);

    //##ModelId=452B0C580076
    CAnalPRI( unsigned int uiCoMaxPdw=NEW_COLLECT_PDW );
    //##ModelId=452B0C58007E
    virtual ~CAnalPRI();


};

#endif

#endif // !defined(AFX_ANALPRI_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)

