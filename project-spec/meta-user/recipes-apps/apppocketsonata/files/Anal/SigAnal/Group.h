// Group.h: interface for the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GROUP_H__D4965E30_EC96_4768_8739_4078D42002F1__INCLUDED_)
#define AFX_GROUP_H__D4965E30_EC96_4768_8739_4078D42002F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

//##ModelId=452B0C560084
enum PDW_MARK { STAT_CW=2, STAT_NORMAL=1, STAT_FMOP=5, STAT_SHORTP=7, MAX_STAT=16 } ;

const int stStat2GrStat[16] = { STAT_NORMAL, STAT_CW, 0, 0, STAT_FMOP, 0, \
																0, STAT_SHORTP, 0, 0, 0, 0, 0, 0, 0, \
																0 };


#ifdef __cplusplus

//////////////////////////////////////////////////////////////////////
/*!	\brief	클래스명 CGroup
		\author 조철희
		\date   2008-01-15 08:57:55
*/
class CGroup
{
protected:
	//##ModelId=452B0C5600B6
	UINT *m_pPdwParam;
	//##ModelId=452B0C5600CA
	int m_nClusters;
	//##ModelId=452B0C5600CC
	STR_CLUSTER *m_pCluster;
	//##ModelId=452B0C5600D4
	int m_nCoPdw;
	//##ModelId=452B0C5600DE
	int m_nMaxPdw;
	//##ModelId=452B0C5600DF
	int m_nBand;
	//##ModelId=452B0C5600E8
	int m_nStat;
	//##ModelId=452B0C5600F2
	int m_CoFrqAoaPwIdx;
	//##ModelId=452B0C5600FD
	STR_PDWINDEX m_Band[ TOTAL_BAND ];
	//##ModelId=452B0C560107
	STR_PDWINDEX m_GrStat[ MAX_STAT ];				// STAT 그룹화의 펄스열 인덱스
	//##ModelId=452B0C560111
	STR_FRQAOAPWHISTOGRAM m_AoaHist;						// 방위 히스토그램
	//##ModelId=452B0C560116
	STR_FRQAOAPWHISTOGRAM m_FrqHist;						// 주파수 히스토그램
	//##ModelId=452B0C56011B
	STR_FRQAOAPWHISTOGRAM	m_PwHist;						// 주파수 히스토그램
	//##ModelId=452B0C560125
	STR_AOA_GROUPS m_AoaGroups;								// 방위 범위 테이블 그룹
	//##ModelId=452B0C560139
	STR_FRQ_GROUPS m_FrqGroups;								// 주파수 범위 테이블 그룹
	//##ModelId=452B0C560143
	STR_PW_GROUPS m_PwGroups;

	//##ModelId=452B0C56014D
	STR_PDWINDEX m_FrqAoaPwIdx;									// 방위 및 주파수 필터링된 PDW 인덱스
	//##ModelId=452B0C560157
	STR_FIRST_FRQAOA_PEAK m_FrqAoaPeak;				// 방위 및 주파수 그룹화된 펄스열 중에서 첫번째 인덱스
	//##ModelId=452B0C560161
	STR_PDWINDEX *m_pGrPdwIndex;

public:
	inline int GetBand() { return m_nBand; }
	BOOL CompMarginDiff( int x, int y1, int y2, int thresh );
	inline UINT GetCoGroups() { return m_PwGroups.count; }
	inline void SetCoGroups( UINT coGroup ) { m_PwGroups.count=coGroup; }
	//##ModelId=452B0C56016A
	//inline int GetGroupedPdw() { return m_FrqAoaPwIdx.count; }
	//##ModelId=452B0C56016B
	//inline int GetCoGroupPdw() { return m_AoaGroups.count; }
	//##ModelId=452B0C56016C
	inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return & m_FrqAoaPwIdx; }
	//##ModelId=452B0C560174
	inline STR_FIRST_FRQAOA_PEAK *GetFrqAoaPeak() { return & m_FrqAoaPeak; }

	inline int GetPulseStat() { return m_nStat; }

	// 가상 함수 선언
	//##ModelId=452B0C560175
	virtual int GetColPdw()=0;

	//##ModelId=452B0C560177
	int GetFreqShift( int band, int FREQ_NARR_SHIFT );
	//##ModelId=452B0C56017F
	void SetHistBinCount( UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	//##ModelId=452B0C560189
	void FineFreqGroup();
	//##ModelId=452B0C56018A
	void MakePWGroup( bool bForce1Group=false );
	//##ModelId=452B0C560192
	BOOL IsSameAoaIdx( int nPwIdx );
	//##ModelId=452B0C560194
	void MakeFreqGroup( bool bForce1Group=false );
	//##ModelId=452B0C560195
	void ReDrawPwHist( STR_PW_GROUP *pPwGroup );
	//##ModelId=452B0C5601A8
	void GetPwRange( int peak_index, int nShift, STR_PW_GROUP *pPwGroup );
	//##ModelId=452B0C5601B2
	void MakePWGroup( int frqidx, bool bForce1Group=false );
	//##ModelId=452B0C5601BB
	BOOL IsLastGroup();
	BOOL IsLastGroup( int index );
	//##ModelId=452B0C5601BC
	BOOL IsSameAoaIdx( int nAoaIdx, UINT narrow_or_wide );
	//##ModelId=452B0C5601C7
	void ReCluster( STR_CLUSTER *pDstCluster1, STR_CLUSTER *pDstCluster2, STR_CLUSTER *pSrcCluster );
	//##ModelId=452B0C5601D9
	BOOL SplitCenter( STR_CLUSTER *pCluster, STR_CLUSTER *pDstCluster );
	//##ModelId=452B0C5601E3
	void CalClusterInfo( STR_CLUSTER *pCluster );
	//##ModelId=452B0C5601E5
	void ISODATA( STR_PDWINDEX *pSrcIndex, UINT *pPdw );
	//##ModelId=452B0C5601F7
    bool MakePDWArray( _PDW *pdw, int count );
	//##ModelId=452B0C560201
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
	//##ModelId=452B0C5602A1
	void MakeHist( STR_FRQ_GROUP *pFrqGroup, STR_AOA_GROUP *pAoaGroup, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	//##ModelId=452B0C5602B5
	int FindPeakInHist( int count, PDWINDEX *pPdwIndex );
	//##ModelId=452B0C5602C0
	void FilterParam( STR_PDWINDEX *pGrPdwIndex, UINT *pParam, STR_AOA_GROUP *pAoaGroup );
	//##ModelId=452B0C5602D3
	void ReDrawAoaHist( STR_AOA_GROUP *pAoaGroup );
	//##ModelId=452B0C5602D5
	BOOL GetAOARange( int peak_index, int nShift, STR_AOA_GROUP *pAoaGroup );
	//##ModelId=452B0C5602E7
	void MakeHist( STR_PW_GROUP *pPwGroup, STR_AOA_GROUP *pAoaGroup, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	//##ModelId=452B0C5602FC
	void MakeHist( int count, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist );
	//##ModelId=452B0C56030F
	void MakeHist( STR_PDWINDEX *pSrcIndex, UINT *pPdw, UINT nShift, STR_FRQAOAPWHISTOGRAM *pHist  );
	//##ModelId=452B0C56031B
	int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
	//##ModelId=452B0C560324
	UINT MakeFreqGroup( int door, int aoaidx, int frqidx=0, bool bForce1Group=false );
	//##ModelId=452B0C56032F
	void MakeAOAGroup( STR_PDWINDEX *pGrPdwIndex, bool bForce1Group=false );
	//##ModelId=452B0C560337
	void MakeStatGroup( STR_PDWINDEX *pBand );
	//##ModelId=452B0C560339
	BOOL MakeGroup(void);
	//##ModelId=452B0C560342
	void Init();
	void PrintAllGroup();
	void PrintGroup();
	//##ModelId=452B0C560343
	CGroup( int coMaxPdw=NSP_MAX_PDW );
	//##ModelId=452B0C560355
	virtual ~CGroup();

};

#endif

#endif // !defined(AFX_GROUP_H__D4965E30_EC96_4768_8739_4078D42002F1__INCLUDED_)

