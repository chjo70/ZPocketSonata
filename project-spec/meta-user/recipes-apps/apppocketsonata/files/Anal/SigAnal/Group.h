// Group.h: interface for the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUP_H__D4965E30_EC96_4768_8739_4078D42002F1__INCLUDED_)
#define AFX_GROUP_H__D4965E30_EC96_4768_8739_4078D42002F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

#ifdef __cplusplus

//////////////////////////////////////////////////////////////////////
/*!	\brief	클래스명 CGroup
		\author 조철희
		\date   2008-01-15 08:57:55
*/
class CGroup
{
protected:
    DEFINE_ANAL_PVAR_

	char m_szPulseType[MAX_STAT][3];

#if defined(_ELINT_) || defined(_XBAND_)
	UINT m_stSigma1Aoa[5];

#elif _POCKETSONATA_
	UINT m_stSigma1Aoa[enMAXPRC];

#else
	UINT m_stSigma1Aoa[3];

#endif

	UINT *m_pPDWParam;      // PDW의 데이터의 포인터 설정됨.
	unsigned int m_uiClusters;
	STR_CLUSTER *m_pCluster;
	unsigned int m_uiCoPdw;
	unsigned int m_uiMaxPdw;
	int m_nBand;
	int m_nStat;
	unsigned int m_uiCoFrqAoaPwIdx;

	STR_PDWINDEX m_Band[ TOTAL_BAND ];

	STR_PDWINDEX m_GrStat[ MAX_STAT ];				// STAT 그룹화의 펄스열 인덱스
	STR_FRQAOAPWHISTOGRAM m_AoaHist;						// 방위 히스토그램
	STR_FRQAOAPWHISTOGRAM m_FrqHist;						// 주파수 히스토그램
	STR_FRQAOAPWHISTOGRAM	m_PwHist;						// 주파수 히스토그램
	STR_AOA_GROUPS m_AoaGroups;								// 방위 범위 테이블 그룹
	STR_FRQ_GROUPS m_FrqGroups;								// 주파수 범위 테이블 그룹
	STR_PW_GROUPS m_PwGroups;

	STR_PDWINDEX m_FrqAoaPwIdx;									// 방위 및 주파수 필터링된 PDW 인덱스
	STR_FIRST_FRQAOA_PEAK m_FrqAoaPeak;				// 방위 및 주파수 그룹화된 펄스열 중에서 첫번째 인덱스
	STR_PDWINDEX *m_pGrPdwIndex;

public:
	inline int GetBand() { return m_nBand; }
	inline UINT GetCoGroups() { return m_PwGroups.uiCount; }
	inline void SetCoGroups( UINT coGroup ) { m_PwGroups.uiCount=coGroup; }
	inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return & m_FrqAoaPwIdx; }
	inline STR_FIRST_FRQAOA_PEAK *GetFrqAoaPeak() { return & m_FrqAoaPeak; }
	inline int GetPulseStat() { return m_nStat; }
    inline int GetCoFrqAoaPwIdx() { return m_uiCoFrqAoaPwIdx; }

	// 가상 함수 선언
	virtual unsigned int GetColPdw()=0;

	//##ModelId=452B0C560177
	int GetFreqShift( int band, int FREQ_NARR_SHIFT );
	//##ModelId=452B0C56017F
	bool SetHistBinCount( UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	//##ModelId=452B0C560189
	//void FineFreqGroup();
	//##ModelId=452B0C56018A
	void MakePWGroup( bool bForce1Group=false );
	//##ModelId=452B0C560192
	//bool IsSameAoaIdx( int nPwIdx );
	//##ModelId=452B0C560194
	void MakeFreqGroup( bool bForce1Group=false );
	void ReDrawPwHist( STR_PW_GROUP *pPwGroup );
	void GetPwRange( int peak_index, int nShift, STR_PW_GROUP *pPwGroup );
	void MakePWGroup( int frqidx, bool bForce1Group=false );
	bool IsLastGroup();
	bool IsLastGroup( unsigned int uiIndex );
	void ReCluster( STR_CLUSTER *pDstCluster1, STR_CLUSTER *pDstCluster2, STR_CLUSTER *pSrcCluster );
	BOOL SplitCenter( STR_CLUSTER *pCluster, STR_CLUSTER *pDstCluster );
	void CalClusterInfo( STR_CLUSTER *pCluster );
	void ISODATA( STR_PDWINDEX *pSrcIndex, UINT *pPdw );

    bool MakePDWArray( _PDW *pdw, unsigned int uiCount, unsigned int uiBand=0 );

	void MakeFreqAoaPwGroup( STR_PDWINDEX *pStatGrPdwIndex );
	//##ModelId=452B0C560203
	void MakeBandGroup();
	//##ModelId=452B0C560204
	BOOL LastOneAoaGroup( int noGroup );
	//##ModelId=452B0C560216
	void SaveFrqAoaPeak();
	//##ModelId=452B0C560217
	void FilterParam(STR_AOA_GROUP *pAoaGroup, UINT *pParam1, UINT *pParam2, STR_FRQ_GROUP *pFrqGroup, STR_PW_GROUP *pPwGroup, STR_PDWINDEX *pFrqAoaPwIndex );
	//##ModelId=452B0C560234
	BOOL MakeGrIndex();
	//##ModelId=452B0C560235
	void ReDrawFrqHist( STR_FRQ_GROUP *pFrqGroup );
	//##ModelId=452B0C56023D
	BOOL GetFrqRange( int peak_index, int nShift, int freqdiff, STR_FRQ_GROUP *pFrqGroup );
	//##ModelId=452B0C560249
	void MakeHist( STR_AOA_GROUP *pSrcIndex, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	//##ModelId=452B0C560265
	void MakeHist( STR_FRQ_GROUP *pFrqGroup, STR_AOA_GROUP *pAoaGroup, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	//##ModelId=452B0C560271
	void MakeHist( STR_FRQ_GROUP *pFrqGroup, STR_AOA_GROUP *pAoaGroup, UINT *pFreq, UINT *pPW, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	void MakeHist( STR_FRQ_GROUP *pFrqGroup, STR_AOA_GROUP *pAoaGroup, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex );
	void FilterParam( STR_PDWINDEX *pGrPdwIndex, UINT *pParam, STR_AOA_GROUP *pAoaGroup );
	void ReDrawAoaHist( STR_AOA_GROUP *pAoaGroup );
	bool GetAOARange( int peak_index, int nShift, STR_AOA_GROUP *pAoaGroup );
	void MakeHist( STR_PW_GROUP *pPwGroup, STR_AOA_GROUP *pAoaGroup, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	void MakeHist( unsigned int uiCount, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	void MakeHist( STR_PDWINDEX *pSrcIndex, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist  );
	int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
	UINT MakeFreqGroup( int door, int aoaidx, int frqidx=0, bool bForce1Group=false );
	void MakeAOAGroup( STR_PDWINDEX *pGrPdwIndex, bool bForce1Group=false );
	void MakeStatGroup( STR_PDWINDEX *pBand );

	BOOL MakeGroup(void);
	void Init();
	void PrintAllGroup();
	void PrintGroup();

    CGroup( unsigned int uiCoMaxPdw=NEW_COLLECT_PDW );
	virtual ~CGroup();

};

#endif

#endif // !defined(AFX_GROUP_H__D4965E30_EC96_4768_8739_4078D42002F1__INCLUDED_)

