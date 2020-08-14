// SAnalScan.h: interface for the CSAnalScan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SANALSCAN_H__649D0457_9E49_4DE3_ACF7_3D07257B7545__INCLUDED_)
#define AFX_SANALSCAN_H__649D0457_9E49_4DE3_ACF7_3D07257B7545__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=452B0C450116
enum LowHighThreatType { LOWTHREAT=0, HIGHTHREAT, OBSCURITY } ;
//##ModelId=452B0C45012A
enum PseudoScanType { TrackUnknown=10, DetectUnknown, LowIllustrationTest } ;


#ifdef __cplusplus

class CScanSigAnal;

//##ModelId=452B0C45013E
class CSAnalScan  
{
protected:
	//##ModelId=452B0C450148
	UINT m_nCanPeak[_spMaxSample];

	/*! \bug  스캔 주기를 int 에서 unsigned integer로 형 변경함.
	    \date 2009-10-08 12:39:49, 조철희
	*/
	//##ModelId=452B0C450152
	UINT m_nScnPrd;										//! 스캔 주기값
	//##ModelId=452B0C450153
	UINT m_nScnTyp;										//! 스캔 형태

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
	//##ModelId=452B0C45017B
	CScanSigAnal *m_pScanSigAnal;
	//##ModelId=452B0C450185
	STR_SCANPT *m_pScanPt;
	//##ModelId=452B0C45018E
	STR_SAMPLE m_nSample;
	//##ModelId=452B0C450192
	UINT m_nCoModWc[_spMaxEMTNum+1];

public:
	BOOL CompMeanDiff(int x, int y, int thresh);
	float MeanInArray( UINT *series, UINT co );
	//##ModelId=452B0C450198
	inline void GetScanRes( int *pScanType, int *pScanPrd ) { *pScanType = m_nScnTyp, *pScanPrd= m_nScnPrd; }
	//##ModelId=452B0C45019B
	// inline STR_SCANPT *GetScanPulseTrain( int noCh ) { return & stScanPt[m_noCh]; }

	//##ModelId=452B0C4501A3
	BOOL CheckControlWc( UINT noEMT );
	//##ModelId=452B0C4501AC
	UINT GetFlagControlWc( UINT noEMT );
	//##ModelId=452B0C4501AE
	UINT DetectNonTrackScanPattern( STR_SAMPLE *pSample, STR_AUTOCOR *pAutocf );
	//##ModelId=452B0C4501B6
	UINT HighIllustrationTest2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
	//##ModelId=452B0C4501B9
	UINT PeriodVerify( void );
	//##ModelId=452B0C4501C0
	float SDevInArray( UINT *series, int co, float mean );
	//##ModelId=452B0C4501C4
	void KurtosisSkewness( STR_SAMPLE *pSample );
	//##ModelId=452B0C4501D5
	UINT ScanTypeDecision2( STR_SAMPLE *pSample, STR_AUTOCOR *pAcf );
	//##ModelId=452B0C4501DF
	UINT FindPeak( STR_AUTOCOR *pAutoCor );
	//##ModelId=452B0C4501E8
	void AutoCorerelation( STR_SAMPLE *pSample, STR_AUTOCOR *pAutoCor );
	//##ModelId=452B0C4501EB
	UINT CheckSteadySignal( STR_SAMPLE *pSample, UINT meanY );
	//##ModelId=452B0C4501F3
	float Normalize( UINT *series, UINT co, float *norm );
	//##ModelId=452B0C4501FC
	void Interpolation( STR_SAMPLE *pSample, STR_SCANPT *pScanPt );
	//##ModelId=452B0C4501FF
	void ReplaceOffSampling( STR_SAMPLE *pSample, STR_SCANPT *pScanPt );
	//##ModelId=452B0C450208
	void SearchLowHghInArray( UINT *series, UINT co, STR_LOWHIGH *lh );
	//##ModelId=452B0C450213
	void SamplingProcess();
	//##ModelId=452B0C450214
	UINT CalcSamplingTime( UINT priMean );
	//##ModelId=452B0C45021B
	UINT CalcSamplingTime2( UINT noEMT, UINT priMean );
	//##ModelId=452B0C45021E
	void CalcSamplingTime();
	//##ModelId=452B0C450224
	UINT AnalScan( int preAnalStat=0 );
	//##ModelId=452B0C450226
	void Init( int noEMT=0, int noCh=0 );
	//##ModelId=452B0C45022E
	CSAnalScan( void *pParent );
	//##ModelId=452B0C450230
	virtual ~CSAnalScan();

};

#endif

#endif // !defined(AFX_SANALSCAN_H__649D0457_9E49_4DE3_ACF7_3D07257B7545__INCLUDED_)
