// NAnalPRI.h: interface for the NAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNANALPRI_H__E2FA3D2C_3913_4551_8449_E3AFB9E151E5__INCLUDED_)
#define AFX_CNANALPRI_H__E2FA3D2C_3913_4551_8449_E3AFB9E151E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../../Utils/clog.h"
#include "../SigAnal/AnalPRI.h"

#ifdef __cplusplus

class CNewSigAnal;

class CNAnalPRI : public CAnalPRI
{
protected:
	CNewSigAnal *m_pNewSigAnal;

    static STR_PULSE_TRAIN_SEG *m_pSeg;

public:
    CNAnalPRI( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName=NULL );
    virtual ~CNAnalPRI();

	//inline void MergeGrouping() { CAnalPRI::MergeGrouping(); }
	//inline void MakeAET() { m_pNewSigAnal->GetCoAet(); }

    //void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof );
	void Init();

	void Analysis();
	int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex );
	unsigned int ExtractStagger(_TOA framePri, STR_EMITTER *pEmitter );
	bool CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
	//void DeleteAllSeg( STR_EMITTER *pEmitter );
	void PrintAllSeg();
	void ExtractRefStable();
	bool ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange );
	unsigned int GetCoSeg();
	STR_PULSE_TRAIN_SEG *GetPulseSeg();
	unsigned int GetMaxPdw();
	//void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter );
	UINT MedianFreq( STR_MINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );
	_TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount);
	int GetBand();
	//void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile );

    bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2, int iMaxMiss, bool bForceMerge );

    //static int incSegPriMeanCompare( const void *arg1, const void *arg2 );

    CMakeAET *GetMakeAET();

    void *GetParentSigAnal();

    void SaveDebug( const char *pSourcefile, int iLines );

#ifdef _LOG_ANALTYPE_
    bool IsLogAnalType();
#endif

};

#endif

#endif // !defined(AFX_CNANALPRI_H__E2FA3D2C_3913_4551_8449_E3AFB9E151E5__INCLUDED_)
