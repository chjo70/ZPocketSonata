// AnalPRI.h: interface for the CAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALPRI_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_ANALPRI_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

// CompFreqLevel 함수에서 리턴되는 정의
//##ModelId=452B0C56035F
enum ANAL_FREQ_TYPE { FIXED_TYPE=0, AGILE_TYPE, FORCED_FIXED, NOT_MATCH } ;

// 병합 방법 정의
enum { MERGE=0, NO_MERGE } ;

#ifdef __cplusplus

//##ModelId=452B0C5603CD
class CAnalPRI
{
public:
	//##ModelId=452B0C5603D7
	int m_nAnalEmitter;
	//##ModelId=452B0C5603E1
	int m_CoEmitter;
	//##ModelId=452B0C570003
	int m_CoSeg;
	//##ModelId=452B0C570004
	int m_nAnalSeg;

private:
	//##ModelId=452B0C57000D
	PDWINDEX *m_pMergePdwIndex;
	//##ModelId=452B0C570018
	PDWINDEX *m_pBinSearchIndex;
	//##ModelId=452B0C570021
	int m_nMaxPdw;
	//##ModelId=452B0C57002C
	static STR_PULSE_TRAIN_SEG *m_pSeg;

	STR_PULSE_TRAIN_SEG m_DwlSeg;

	//##ModelId=452B0C570036
	STR_EMITTER m_Emitter[MAX_AET];

	// 패턴 형태 분석을 분석하기 위한 데이터
	//##ModelId=452B0C570049
	int m_1PrimeData[ MAX_SAMPLING_DATA ];
	//##ModelId=452B0C570053
	int m_2PrimeData[ MAX_SAMPLING_DATA ];
	//##ModelId=452B0C570054
	int m_nPatternType;

	// 주파수 패턴 및 PRI 패턴 정보를 분석하기 위한 내부 변수들
	//##ModelId=452B0C57005D
	UINT m_SamplingTime;
	//##ModelId=452B0C570067
	int m_CoSample;
	//##ModelId=452B0C570071
	_TOA m_SampleToa[MAX_SAMPLING_DATA];
	//##ModelId=452B0C57007C
	int m_SampleData[MAX_SAMPLING_DATA];
	//##ModelId=452B0C570086
	int m_NormData[MAX_SAMPLING_DATA];
	//##ModelId=452B0C570090
	float m_skewness;
	//##ModelId=452B0C5700A4
	float m_kurtosis;

	//##ModelId=452B0C5700B8
	int m_CoData;
	//##ModelId=452B0C5700C2
	_TOA m_DataX[MAX_SAMPLING_DATA];
	//##ModelId=452B0C5700C3
	_TOA m_DataY[MAX_SAMPLING_DATA];

	//##ModelId=452B0C5700CC
	float m_Acf[MAX_SAMPLING_DATA];
	//##ModelId=452B0C5700D6
	int m_CoAcf;

	//##ModelId=452B0C5700E0
	_TOA m_CanPeak[MAX_SAMPLING_DATA];

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
	int m_coCanPeak;
	//##ModelId=452B0C570130
	_TOA m_nMaxPeak;

	//
	//##ModelId=452B0C57013A
	int m_nRefFramePri;
	//##ModelId=452B0C57013B
	_TOA *m_pRefFramePri;
	//##ModelId=452B0C570144
	UINT m_nTmpStaggerLevel[_spMaxSwtLev];
	//##ModelId=452B0C57014E
	UINT m_nStaggerLevel[_spMaxSwtLev];

	//##ModelId=452B0C570163
	STR_DTOA_HISTOGRAM m_DtoaHist;

	int m_iCoDwellLevel;
	STR_DWELL_LEVEL m_stDwellLevel[_MAX_DWELL_LEVEL];

public:
	void CalHopLevel( STR_EMITTER *pEmitter );
	BOOL IsFreqHopping( STR_EMITTER *pEmitter );
	BOOL CompAoaDiff( int x, int y, int thresh );
	UINT CalOverlapSpace( int hgh1, int low1, int hgh2, int low2 );
	_TOA CalOverlapSpace64( _TOA hgh1, _TOA low1, _TOA hgh2, _TOA low2 );
	float MeanInArray( UINT *series, UINT co );
	float IMeanInArray( int *series, UINT co );
	//##ModelId=452B0C57016C
	inline void SetAnalSeg( int nSeg ) { m_nAnalSeg=nSeg; }
	//##ModelId=452B0C57016E
	inline void MergeGrouping() { MergeGrouping( m_nAnalEmitter ); }
	//##ModelId=452B0C570176
	inline void SetCoSeg( int nSeg ) { m_CoSeg = nSeg; }
	//##ModelId=452B0C570178
	inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return & m_DtoaHist; }
	//##ModelId=452B0C570180
	inline void SetPulseSeg( STR_PULSE_TRAIN_SEG *pSeg ) { m_pSeg = pSeg; }
	//##ModelId=452B0C570182
	inline int GetCoEmitter() { return m_CoEmitter; }
	inline void SetCoEmitter( UINT coEmitter ) { m_CoEmitter=coEmitter; }
	//##ModelId=452B0C57018A
	inline void SetAnalEmitter( int nEmitter ) { m_nAnalEmitter = nEmitter; }
	//##ModelId=452B0C57018C
	inline STR_EMITTER *GetEmitter() { return m_Emitter; }

	//////////////////////////////////////////////////////////////////////////
	// 가상 함수 선언...
	//##ModelId=452B0C570194
	virtual int FindPeakInHist( int count, PDWINDEX *pPdwIndex )=0;
	//##ModelId=452B0C57019E
	virtual BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )=0;
	//##ModelId=452B0C5701A8
	virtual void DeleteAllSeg( STR_EMITTER *pEmitter )=0;
	virtual void PrintAllSeg()=0;
	//##ModelId=452B0C5701AB
	virtual void ExtractRefStable()=0;
	//##ModelId=452B0C5701B2
	virtual int GetCoSeg()=0;
	//##ModelId=452B0C5701B4
	virtual BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange )=0;
	//##ModelId=452B0C5701BC
	virtual UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri )=0;
	//##ModelId=452B0C5701C6
	virtual STR_PULSE_TRAIN_SEG *GetPulseSeg()=0;
	//##ModelId=452B0C5701C8
	virtual void MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter )=0;
	//##ModelId=452B0C5701DA
	virtual int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter)=0;
	//##ModelId=452B0C5701E4
	virtual UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, int count )=0;
	//##ModelId=452B0C5701F8
	virtual _TOA VerifyPRI( PDWINDEX *pPdwIndex, int count )=0;
	virtual int GetBand()=0;
	virtual void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )=0;

	BOOL CompAoa( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
	//##ModelId=452B0C57020C
	BOOL CheckPW( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
	//##ModelId=452B0C57020F
	void CalcEmitterPW( STR_EMITTER *pEmitter );
	//##ModelId=452B0C570216
	UINT CheckHarmonicPW( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
	//##ModelId=452B0C570221
	//void GroupingDwell();
	//##ModelId=452B0C57022A
	void PrintAllEmitter();
	//##ModelId=452B0C57022B
	BOOL CheckSawPattern( int *pSawPatternType );
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
	//##ModelId=452B0C570253
	BOOL GetDtoaRange( int peak_index, STR_LOWHIGH *pRange );
	//##ModelId=452B0C570266
	void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );
	//##ModelId=452B0C570272
	void MakeStaggerLevel( _TOA *pStaggerLevel, int CoStagger );
	//##ModelId=452B0C57027C
	BOOL CheckFreqHopping( STR_EMITTER *pEmitter );
	//##ModelId=452B0C570285
	BOOL VerifyStaggerLevel( STR_EMITTER *pStaggerEmitter, STR_EMITTER *pEmitter=NULL );
	//##ModelId=452B0C57028F
	float ISDevInArray( int *series, int co, UINT mean );
	//##ModelId=452B0C5702A2
	void KurtosisSkewness();
	//##ModelId=452B0C5702AC
	BOOL CompareAllStaggerLevel( STR_EMITTER *pEmitter, STR_PULSE_TRAIN_SEG *pSeg );
	//##ModelId=452B0C5702B8
	int GetMaxPdw();
	//##ModelId=452B0C5702B9
	BOOL DwellAnalysis( STR_EMITTER *pEmitter );
	//##ModelId=452B0C5702C1
	BOOL ExtractDwellPT();
	//##ModelId=452B0C5702C2
	BOOL FindBin( UINT bin );
	BOOL FindDtoa( _TOA priMean );
	//##ModelId=452B0C5702D5
	BOOL FindDwellLevel();
	BOOL FindDwellLevel( STR_EMITTER *pEmitter );
	//##ModelId=452B0C5702D6
	void MakeDtoaHistogram( PDWINDEX *pPdwIndex, int count, STR_MINMAX_TOA *pRange=NULL );
	//##ModelId=452B0C5702E8
	void DwellAnalysis();
	BOOL CheckContiStable( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
	void MergePdwIndexInSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
	//##ModelId=452B0C5702E9
	void CheckHarmonicStaggerLevel( STR_EMITTER *pStaggerEmitter );
	//##ModelId=452B0C5702F2
	BOOL StaggerLevelAnalysis( STR_EMITTER *pEmitter );
	//##ModelId=452B0C5702FC
	UINT HighIllustrationTest( STR_EMITTER *pEmitter );
	//##ModelId=452B0C5702FD
	void FindPeriod();
	//##ModelId=452B0C5702FE
	void AutoCorerelation();
	//##ModelId=452B0C570306
	void Normalize();
	//##ModelId=452B0C570307
	void ReplaceOffSampling();
	//##ModelId=452B0C570308
	void Interpolation();
	//##ModelId=452B0C570309
	void SamplingProcess( STR_EMITTER *pEmitter );
	//##ModelId=452B0C570311
	void CalcSamplingTime( STR_EMITTER *pEmitter );
	//##ModelId=452B0C570313
	float PatternAnalysis( STR_EMITTER *pEmitter );
	//##ModelId=452B0C57031B
	void FindPeak();
	//##ModelId=452B0C57031C
	int GetContiThreshold( int count );
	//##ModelId=452B0C570325
	BOOL CheckStaggerLevel( STR_EMITTER *pOrgEmitter, STR_EMITTER *pStaggerEmitter, int match_index );
	//##ModelId=452B0C570343
	UINT CheckHarmonic(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2);
	//##ModelId=452B0C57034E
	UINT CheckHarmonic(_TOA priMean1, _TOA priMean2 ,_TOA uiThreshold=(3*_spOneMicrosec) );
	//##ModelId=452B0C570362
	BOOL CompFreq( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
	//##ModelId=452B0C57036C
	void CalcEmitterFrq( STR_EMITTER *pEmitter );
	//##ModelId=452B0C570375
	void CalcEmitterPri( STR_EMITTER *pEmitter );
	//##ModelId=452B0C57037F
	UINT CompFreqLevel( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 );
	//##ModelId=452B0C57038A
	BOOL BinSearchInPdwIndex( int from, int to, int search_value );
	//##ModelId=452B0C57039E
	BOOL IncludePulseTrain(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
	//##ModelId=452B0C5703B1
	int ExtractStagger( STR_EMITTER *pEmitter, UINT framePri );
	//##ModelId=452B0C5703C7
	BOOL FindRefFramePri( UINT dtoa );
	//##ModelId=452B0C5703D9
	_TOA CheckFramePRI( STR_EMITTER *pEmitter );
	//##ModelId=452B0C5703DB
	UINT CheckHarmonic(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2);
	//##ModelId=452B0C5703E4
	BOOL SelectMainEmitter( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, UINT *pMrgOption );
	//##ModelId=452B0C580007
	void MergeEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter, UINT nOption );
	//##ModelId=452B0C580011
	BOOL OverlappedSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
	//##ModelId=452B0C58001B
	void MergeGrouping( int nAnalEmitter );
	//##ModelId=452B0C580023
	BOOL StaggerAnalysis( STR_EMITTER *pEmitter );
	//##ModelId=452B0C580025
	void SelectMainSeg(STR_EMITTER *pEmitter);
	//##ModelId=452B0C580038
	BOOL DecisionEmitter( STR_EMITTER *pEmitter );
	//##ModelId=452B0C580041
	BOOL AnalLobe( STR_EMITTER *pEmitter );
	//##ModelId=452B0C580043
	void MergePdwIndexInSeg( STR_EMITTER *pEmitter );
	//##ModelId=452B0C58004B
	UINT AnalPriType( STR_EMITTER *pEmitter );
	//##ModelId=452B0C58004D
	FREQ_TYPE AnalFreqType( STR_EMITTER *pEmitter );
	//##ModelId=452B0C580056
	SIGNAL_TYPE AnalSignalType( STR_EMITTER *pEmitter );
	//##ModelId=452B0C580058
	void PatternAnalysis();
	//##ModelId=452B0C58005F
	void StaggerAnalysis();
	//##ModelId=452B0C580060
	void GroupingUnknown();
	//##ModelId=452B0C580061
	void GroupingJitter( BOOL fDecisionEmitter=FALSE );
	//##ModelId=452B0C58006A
	void GroupingStagger( BOOL fDecisionEmitter=FALSE );
	//##ModelId=452B0C58006C
	void GroupingStable( BOOL fDecisionEmitter=FALSE );
	void GroupingDwell( BOOL fDecisionEmitter=TRUE );

	BOOL CalcPRILevel( STR_EMITTER *pEmitter );
	void AddDwellLevel( STR_DWELL_LEVEL *pSTR_DWELL_LEVEL );
	bool MakeDwellLevel( STR_EMITTER *pEmitter );

	int (CAnalPRI::*qsort_memberfunc)( const void *arg1, const void *arg2 );
	static int incSegPriMeanCompare( const void *arg1, const void *arg2 );
	void SortEmitter();
	void SwapEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter );
	_TOA GetMinPulseTrainMean( STR_EMITTER *pEmitter );

	//##ModelId=452B0C580074
	void Analysis();
	//##ModelId=452B0C580075
	void Init();
	//##ModelId=452B0C580076
	CAnalPRI( int coMaxPdw=NSP_MAX_PDW );
	//##ModelId=452B0C58007E
	virtual ~CAnalPRI();

};

#endif

#endif // !defined(AFX_ANALPRI_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)

