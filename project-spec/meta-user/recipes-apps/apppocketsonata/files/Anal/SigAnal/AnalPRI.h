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

#include "../../Utils/clog.h"
#include "../../Utils/ccommonutils.h"

#include "Hopping.h"

// 병합 방법 정의
enum enEMITTER_MERGE_OPTION {
    enMERGE_LEFT=0,		// pEmitter1 과 pEmitter2 에서 pEmitter1 으로 합한다.
	enMERGE_RIGHT,		// pEmitter1 과 pEmitter2 에서 pEmitter2 으로 합한다.
    enNO_MERGE
} ;

#ifdef __cplusplus

/**

    @class   CAnalPRI
    @brief   PRI 분석 관련 클래스 입니다.
    @details ~

**/
class CAnalPRI : public CLogName
{
protected:
    DEFINE_ANAL_PVAR_

private:


public:
    unsigned int m_uiCoEmitter;

    unsigned int m_uiCoSeg;
    unsigned int m_uiAnalSeg;

private:
	UINT m_spdiffaoa[enMAXPRC];

    PDWINDEX *m_pMergePdwIndex;
    PDWINDEX *m_pBinSearchIndex;

    unsigned int m_uiMaxPdw;

    STR_PULSE_TRAIN_SEG *m_pSeg;
    STR_PULSE_TRAIN_SEG m_DwlSeg;

    STR_EMITTER m_Emitter[MAX_LOB];
    STR_EMITTER m_StaggerEmitter;           // 스태거 분석하기 위한 임시 가상 에미터 저장소

    // 패턴 형태 분석을 분석하기 위한 데이터
    float *m_p1PrimeData;
    float *m_p2PrimeData;
    ENUM_AET_FREQ_PRI_PATTERN_TYPE m_enPatternType;

    // 주파수 패턴 및 PRI 패턴 정보를 분석하기 위한 내부 변수들
    UINT m_SamplingTime;
    unsigned int m_uiCoSample;
    _TOA *m_pSampleToa;
    int *m_pSampleData;
    int *m_pNormData;
    float m_skewness;
    float m_kurtosis;

    unsigned int m_uiCoData;
    _TOA *m_ptDataX;
    _TOA *m_ptDataY;

    float *m_pAcf;
    unsigned int m_CoAcf;

    _TOA *m_pCanPeak;
    _TOA *m_pPulseDtoa;

    float m_fPeriod;

    // 스태거 분석하기 위한 내부 변수들
    //
    int m_CoPulseDtoa;
    // ACF 연산을 사용하여 스태거 분석하기 위한 변수들...
    //-- 조철희 2005-05-26 08:04:33 --//
    _TOA *m_pPulseToa;
    _TOA *m_pToaAcf;
    unsigned int m_coCanPeak;
    _TOA m_nMaxPeak;

    int m_nRefFramePri;
    _TOA *m_pRefFramePri;
    UINT m_nTmpStaggerLevel[MAX_FREQ_PRI_STEP];
    UINT m_nStaggerLevel[MAX_FREQ_PRI_STEP];

    STR_DTOA_HISTOGRAM m_DtoaHist;

    int m_iCoDwellLevel;
    STR_DWELL_LEVEL m_stDwellLevel[_MAX_DWELL_LEVEL];

    // 주파수 호핑 분석
    CHopping *m_pTheHopping;

protected:
    _TOA m_tStableMargin;
    unsigned int m_uiFixedFreqMargin;

    unsigned int m_uiZeroMargin;
    unsigned int m_thSawPattern;

    STR_STAGGER_SEG m_stStaggerSeg[MAX_STAGGER_LEVEL_POSITION];

private:
    void NormalizeTOA(STR_EMITTER *pEmitter);
    void AnalyzeACF(STR_EMITTER *pEmitter);

    bool CheckStaggerLevel( STR_EMITTER *pStaggerEmitter, int iMatch, int iLevelCount );

	// 에미터 병합 및 비교 관련 함수 모음
	enEMITTER_MERGE_OPTION WhichMerge(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
	bool CheckMergeEmitter(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, enEMITTER_MERGE_OPTION *pMrgOption);
    void CheckStablePRIMergeEmitter( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, enEMITTER_MERGE_OPTION *pMrgOption, bool *pBret );
    void CheckStaggerPRIMergeEmitter( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, enEMITTER_MERGE_OPTION *pMrgOption, bool *pBret );
    void CheckJitterPRIMergeEmitter( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, enEMITTER_MERGE_OPTION *pMrgOption, bool *pBret );

	void MergeEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter, enEMITTER_MERGE_OPTION enMergeOption);

    void CheckStablePRIHarmonic( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, UINT *puiRet );
    void CheckStaggerPRIHarmonic( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, UINT *puiRet );
    void CheckJitterPRIHarmonic( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, UINT *puiRet );
    void CheckPatternPRIHarmonic( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, UINT *puiRet );

    bool CheckMergeOfPRIType( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool CheckMergeOfStablePRIType( STR_EMITTER *pEmitter );
    bool CheckMergeOfStaggerPRIType( STR_EMITTER *pEmitter );
    bool CheckMergeOfJitterPRIType( STR_EMITTER *pEmitter );
    bool CheckMergeOfDwellPRIType( STR_EMITTER *pEmitter );
    bool CheckMergeOfPatternPRIType( STR_EMITTER *pEmitter );

    unsigned int CountOfEmitter( unsigned int uiStartEmitter, enANL_FREQ_TYPE enFREQ_TYPE, enANL_PRI_TYPE enPRI_TYPE );

    bool CheckIncludePulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    // bool CheckDwellPulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool CheckMergeOfPulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool CheckMergeOfStablePulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool CheckMergeOfStaggerPulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool CheckMergeOfJitterPulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool CheckMergeOfDwellPulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool CheckMergeOfPatternPulseTrain( enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION, STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );

public:
    CAnalPRI( void *pParent, unsigned int uiCoMaxPdw = NEW_COLLECT_PDW, const char *pThreadName=NULL );
    virtual ~CAnalPRI();


    //void CalHopLevel( STR_EMITTER *pEmitter );
    //bool IsHopping( STR_EMITTER *pEmitter );
    float IMeanInArray( int *series, UINT co );

    void DNSAnalysis();
    bool CheckDNSPossibility(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
    void MergePdwIndexInEmitter(STR_EMITTER *pEmitter);
    int CalcDiffAOA(int iAOA1, int iAOA2);
    bool CheckOverlapSeg(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
    bool CheckFreqType(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);

    // 호핑 분석
    void MakeFREQ( STR_EMITTER *pEmitter );
    void HoppingAnalysis();
    void MakeFreqHistogram(STR_EMITTER *pEmitter);
    void ExtractHoppingLevel(STR_EMITTER *pEmitter);
    bool HoppingDecision(STR_EMITTER *pEmitter);
    void SetHoppingInfo(STR_EMITTER *pEmitter);

    // 드웰 분석
    void MakeDTOA( STR_EMITTER *pEmitter );
    void DwellNSwitchAnalysis();


    inline void PrintAllSeg() { }
    inline void SetAnalSeg( unsigned int uiSeg ) { m_uiAnalSeg=uiSeg; }
    inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return & m_DtoaHist; }
    inline void SetPulseSeg( STR_PULSE_TRAIN_SEG *pSeg ) { m_pSeg = pSeg; }
    inline unsigned int GetCoEmitter() { return m_uiCoEmitter; }
    inline void SetCoEmitter( UINT coEmitter ) { m_uiCoEmitter=coEmitter; }
    //inline void SetAnalEmitter( unsigned int uiEmitter) { m_uiAnalEmitter = uiEmitter; }
    inline STR_EMITTER *GetEmitter() { return m_Emitter; }

    bool CompAOA( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );

    void CalcEmitterPW( STR_EMITTER *pEmitter );
    void CalcEmitterMOP( STR_EMITTER *pEmitter );

    void PrintAllEmitter( unsigned int uiStartEmitter=0, const char *pszString=NULL, enANL_FREQ_TYPE enFREQ_TYPE= _UNKNOWN_FREQ, enANL_PRI_TYPE enPRITYpe= _UNKNOWN_PRI );
    bool CheckSawPattern( ENUM_AET_FREQ_PRI_PATTERN_TYPE *pSawPatternType );
    ENUM_AET_FREQ_PRI_PATTERN_TYPE CheckSinePattern();
    UINT CalPrimeDifference();
    void CalTwoPrime( STR_EMITTER *pEmitter );
    bool GetDTOARange( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange );
    void RemoveNoiseDtoa( UINT count );
    void CalDtoaMeanMinMax( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange );

    bool GetDTOARange( int peak_index, STR_LOWHIGH *pRange );
    void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );

    void MakeStaggerLevel( _TOA *pStaggerLevel, int CoStagger );
    bool CheckFreqHopping( STR_EMITTER *pEmitter );
    bool VerifyStaggerLevel( STR_EMITTER *pStaggerEmitter, STR_EMITTER *pEmitter=NULL );
    void KurtosisSkewness();
    bool CompareAllStaggerLevel( STR_EMITTER *pEmitter, STR_PULSE_TRAIN_SEG *pSeg );
    //int GetMaxPdw();

    bool DwellAnalysis( STR_EMITTER *pEmitter );
    bool ExtractDwellPT();
    bool FindBin( UINT bin );
    bool FindDtoa( _TOA priMean );
    bool FindDwellLevel();
    bool FindDwellLevel( STR_EMITTER *pEmitter );
    void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange=NULL );

    void DwellAnalysis();
    bool CheckContiStable( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    void MergePDWIndexInSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );

    void CheckHarmonicStaggerLevel( STR_EMITTER *pStaggerEmitter );

    bool StaggerLevelAnalysis( STR_EMITTER *pEmitter );
    void MakeStaggerPRI( STR_EMITTER *pEmitter );

    ENUM_AET_FREQ_PRI_PATTERN_TYPE HighIllustrationTest( STR_EMITTER *pEmitter );

    void FindPeriod( bool bCheckPeak=false );
    void AutoCorerelation();
    void Normalize();
    void ReplaceOffSampling();
    void Interpolation();
    void SamplingProcess( STR_EMITTER *pEmitter, ENUM_SAMPLING_OPTION enSamplingOption=enAVERAGE );


    void CalcSamplingTime( STR_EMITTER *pEmitter );
    float PatternAnalysis( STR_EMITTER *pEmitter );
    bool FindPeak();

    bool CheckStaggerLevel( STR_EMITTER *pOrgEmitter, STR_EMITTER *pStaggerEmitter, int match_index );

    UINT CheckHarmonic(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2);
    UINT CheckHarmonic(_TOA priMean1, _TOA priMean2 ,_TOA uiThreshold=(3*_spOneMicrosec) );
	UINT CheckHarmonic(STR_MINMAX_TOA *pstPRI1, STR_MINMAX_TOA *pstPRI2);
    UINT CheckHarmonic( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );

    bool CompFreq( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );

    void CalcEmitterFrq( STR_EMITTER *pEmitter );
    void CalcEmitterPRI( STR_EMITTER *pEmitter );
    bool CompFreq( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
    bool BinSearchInPdwIndex( int from, int to, int search_value );

    void SelectMainEmitter( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, enEMITTER_MERGE_OPTION *penEMITTER_MERGE_OPTION );
    int ExtractStagger( STR_EMITTER *pEmitter, UINT framePri );
    bool FindRefFramePri( UINT dtoa );
    //_TOA CheckFramePRI( STR_EMITTER *pEmitter );

    bool OverlappedSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );

    void MergeGrouping();

    bool StaggerAnalysis( STR_EMITTER *pEmitter );
    bool SortSegOfFramePRI( STR_EMITTER *pEmitter );
    bool CheckStaggerPRI( STR_EMITTER *pEmitter );
    bool FindFramePRI( STR_EMITTER *pEmitter );
    bool AdjustStaggerLevel( STR_EMITTER *pEmitter, unsigned int uiStep );

    void SelectMainSeg(STR_EMITTER *pEmitter);
    bool DecisionEmitter( STR_EMITTER *pEmitter );
    bool AnalLobe( STR_EMITTER *pEmitter );
    void MergePDWIndexInSeg( STR_EMITTER *pEmitter );


    enANL_FREQ_TYPE AnalFreqType( STR_EMITTER *pEmitter );
    ENUM_SIGNAL_TYPE AnalSignalType( STR_EMITTER *pEmitter );

    void PatternAnalysis( bool bFreqPattern=true, bool bPRIPattern=true );
    void StaggerAnalysis();
    void GroupingUnknown();

    void GroupingJitter( bool bDecisionEmitter=false, bool bForceMerge=false );
    void GroupingJitterWithJitter( STR_PULSE_TRAIN_SEG *pRefSeg, unsigned int uiLoop, bool bDecisionEmitter );
    void GroupingJitterWithStable( STR_PULSE_TRAIN_SEG *pRefSeg, unsigned int uiLoop, bool bDecisionEmitter );
    void GroupingStagger( bool bDecisionEmitter=false );
    void GroupingStable( bool bDecisionEmitter=false, bool bForceMerge=false );
    void GroupingDwell( bool bDecisionEmitter=true );

    bool CalcPRILevel( STR_EMITTER *pEmitter );
    void AddDwellLevel( STR_DWELL_LEVEL *pSTR_DWELL_LEVEL );
    bool MakeDwellLevel( STR_EMITTER *pEmitter );

    int (CAnalPRI::*qsort_memberfunc)( const void *arg1, const void *arg2 );

    void SortEmitter();
    void SwapEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter );
    _TOA GetMinPulseTrainMean( STR_EMITTER *pEmitter );

    void Analysis();
    void Init();

    void InitSeg(STR_EMITTER *pEmitter);


    float DifferencePAdBm( int iMax, int iMin );


    //////////////////////////////////////////////////////////////////////////
    // 가상 함수 선언...
    virtual int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex ) = 0;
    virtual bool CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) = 0;
    virtual void DeleteAllSeg( STR_EMITTER *pEmitter ) = 0;
    virtual void ExtractRefStable() = 0;
    virtual unsigned int GetCoSeg() = 0;
    virtual bool ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange ) = 0;
    //virtual UINT ExtractFramePri( STR_PDWINDEX *pSrcPdwIndex, _TOA framePri ) = 0;
    virtual STR_PULSE_TRAIN_SEG *GetPulseSeg() = 0;
    virtual void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof ) = 0;
    virtual void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) = 0;
    virtual unsigned int ExtractStagger( _TOA framePri, STR_EMITTER *pEmitter ) = 0;
    virtual UINT MedianFreq( STR_MINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount ) = 0;
    virtual _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount ) = 0;
    virtual int GetBand() = 0;
    virtual void SaveEmitterPDWFile( STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile ) = 0;
    virtual CMakeAET *GetMakeAET() = 0;
    virtual bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2, int iMaxMiss, bool bForceMerge ) = 0;

    virtual void SaveDebug( const char *pSourcefile, int iLines ) = 0;

    virtual void *GetParentSigAnal() = 0;

};

#endif

#endif // !defined(AFX_ANALPRI_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)

