// NAnalPRI.h: interface for the NAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNANALPRI_H__E2FA3D2C_3913_4551_8449_E3AFB9E151E5__INCLUDED_)
#define AFX_CNANALPRI_H__E2FA3D2C_3913_4551_8449_E3AFB9E151E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/AnalPRI.h"

#ifdef __cplusplus

class CNewSigAnal;

//##ModelId=452B0C550318
class CNAnalPRI : public CAnalPRI
{
protected:
	//##ModelId=452B0C550323
	CNewSigAnal *m_pNewSigAnal;

    static STR_PULSE_TRAIN_SEG *m_pSeg;

public:
	//##ModelId=452B0C550327
	inline void MergeGrouping() { CAnalPRI::MergeGrouping(); }
	//inline void MakeAET() { m_pNewSigAnal->GetCoAet(); }

    void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof );

	//##ModelId=452B0C55032C
	void Init();
	//##ModelId=452B0C55032D
	void Analysis();
	//##ModelId=452B0C55032E
	int FindPeakInHist( int count, PDWINDEX *pPdwIndex );
	//##ModelId=452B0C550331
	int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter );
	//##ModelId=452B0C550339
	BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
	//##ModelId=452B0C550341
	void DeleteAllSeg( STR_EMITTER *pEmitter );
	void PrintAllSeg();
	//##ModelId=452B0C550343
	void ExtractRefStable();
	//##ModelId=452B0C550344
	BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange );
	//##ModelId=452B0C55034B
	UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri );
	//##ModelId=452B0C550355
	int GetCoSeg();
	//##ModelId=452B0C550356
	STR_PULSE_TRAIN_SEG *GetPulseSeg();
	//##ModelId=452B0C55035E
	int GetMaxPdw();
	//##ModelId=452B0C55035F
	void MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter );
	//##ModelId=452B0C550362
	UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, int count );
	//##ModelId=452B0C550375
	_TOA VerifyPRI( PDWINDEX *pPdwIndex, int count );
	int GetBand();
	void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index );

    static int incSegPriMeanCompare( const void *arg1, const void *arg2 );

    CMakeAET *GetMakeAET();

	//##ModelId=452B0C55037C
	CNAnalPRI( void *pParent, int coMaxPdw );
	//##ModelId=452B0C55037F
	virtual ~CNAnalPRI();

};

#endif

#endif // !defined(AFX_CNANALPRI_H__E2FA3D2C_3913_4551_8449_E3AFB9E151E5__INCLUDED_)
