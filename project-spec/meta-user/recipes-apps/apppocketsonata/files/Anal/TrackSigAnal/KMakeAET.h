// KMakeAET.h: interface for the CKMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KMAKEAET_H__0B6C1D4B_0545_4DD1_9E8C_1FDB63EDF929__INCLUDED_)
#define AFX_KMAKEAET_H__0B6C1D4B_0545_4DD1_9E8C_1FDB63EDF929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../RSA/NSP/MakeAET.h"

class CKnownSigAnal;

//##ModelId=452B0C5203C8
class CKMakeAET : public CMakeAET  
{
protected :
	//##ModelId=452B0C5203D4
	CKnownSigAnal *m_pKnownSigAnal;
	
	//##ModelId=452B0C5203DC
	int m_CoNewAet;
	//##ModelId=452B0C5203DD
	int m_IdxUpdAet;

	//##ModelId=452B0C5203E7
	STR_NEWAET *m_pAet;
	//##ModelId=452B0C530009
	STR_EMITTER *m_pEmitter;
	
public:
	//##ModelId=452B0C53000D
	inline void SetCoNewAet( int count ) { m_CoNewAet=count; }
	//##ModelId=452B0C53000F
	inline void ClearCoAet() { m_CoAet=0; }
	//##ModelId=452B0C530012
	inline STR_NEWAET *GetAet() { return CMakeAET::GetAet(); }
	// inline STR_EMITTER *GetEmitter() { return CMakeAET::GetEmitter(); }

	void CalDtoaMeanMinMax( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange );

	//##ModelId=452B0C530013
	void Init();
	//##ModelId=452B0C530014
	void MakeAET();
	//##ModelId=452B0C530015
	UINT CheckStaggerHarmonic( STR_PRI *pPri1, STR_PRI *pPri2 );
	//##ModelId=452B0C53001D
	UINT CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg );
	//##ModelId=452B0C53001F
	int GetIndexNewAet();
	//##ModelId=452B0C530030
	BOOL CompPRI( STR_PRI *pNewPri, STR_PRI *pTrkPri );
	//##ModelId=452B0C530033
	STR_PULSE_TRAIN_SEG *GetPulseSeg();
	//##ModelId=452B0C530034
	int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex );
	//##ModelId=452B0C53003B
	int GetColPdw();
	//##ModelId=452B0C53003C
	int CalcPAMean(PDWINDEX *pPdwIndex, int count );
	//##ModelId=452B0C530044
	int VerifyPW( PDWINDEX *pPdwIndex, int count );
	//##ModelId=452B0C530047
	void MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type );
	//##ModelId=452B0C530050
	void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index );
	//##ModelId=452B0C530058
	int GetCoSeg();
	//##ModelId=452B0C530059
	int GetCoEmitter();
	//##ModelId=452B0C53005A
	STR_EMITTER *GetEmitter();
	//##ModelId=452B0C53005B
	STR_NEWAET *GetNewAet();
	//##ModelId=452B0C53005C
	STR_UPDAET *GetUpdAet();
	//##ModelId=452B0C53005D
	UINT CheckHarmonic( STR_PRI *pPri1, STR_PRI *pPri2 );
	//##ModelId=452B0C530064
	int GetCoNewAet();
	//##ModelId=452B0C530065
	UINT CheckHarmonic(UINT mean1, float jitter_p1, UINT mean2, float jitter_p2);
	//##ModelId=452B0C53006E
	UINT CheckHarmonic(UINT mean1, UINT mean2 );
	//##ModelId=452B0C530071
	UINT CheckHarmonic(STR_AET *pAet1, STR_AET *pAet2 );
	//##ModelId=452B0C530078
	BOOL IsUpdateAet();
	//##ModelId=452B0C530079
	void MakeUpAET();
	//##ModelId=452B0C530080
	BOOL KnownMakeAET();
	//##ModelId=452B0C530081
	CKMakeAET( void *pParent, int coMaxPdw=KSP_MAX_PDW );
	//##ModelId=452B0C530084
	virtual ~CKMakeAET();

};

#endif // !defined(AFX_KMAKEAET_H__0B6C1D4B_0545_4DD1_9E8C_1FDB63EDF929__INCLUDED_)
