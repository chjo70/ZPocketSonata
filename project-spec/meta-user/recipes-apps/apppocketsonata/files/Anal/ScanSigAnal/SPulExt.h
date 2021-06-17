// SPulExt.h: interface for the CSPulExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPULEXT_H__012521F1_308E_44E3_BA97_612DA873B1A3__INCLUDED_)
#define AFX_SPULEXT_H__012521F1_308E_44E3_BA97_612DA873B1A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/PulExt.h"

#ifdef __cplusplus

class CScanSigAnal;

//##ModelId=452B0C440363
class CSPulExt : public CPulExt  
{
private:
    SRxABTData *m_pScnAet;

protected:
	//##ModelId=452B0C440365
	int m_uiMaxPdw;
	//##ModelId=452B0C44036D
	int m_noEMT;
	//##ModelId=452B0C44036E
	int m_noCh;
	//##ModelId=452B0C440378
	CScanSigAnal *m_pScanSigAnal;
	
public:
	int GetCoPdw();
	void SaveScanPulse( STR_PDWINDEX *pPdwIndex );
	//##ModelId=452B0C44037C
	STR_DTOA_HISTOGRAM *GetDtoaHist();
	//##ModelId=452B0C44037D

    void MakeDtoaHistogram( PDWINDEX *pPdwIndex, int count, STR_MINMAX_TOA *pRange );
	//##ModelId=452B0C440382
    void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );
	//##ModelId=452B0C440386
    void DiscardStablePT();

    void ClearAllMark() { };

	void SaveScanPulse();
	//##ModelId=452B0C44038B
	void Init();
	//##ModelId=452B0C44038C
	void KnownPulseExtract();
	//##ModelId=452B0C44038D
	void MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type );
	//##ModelId=452B0C440396
	STR_PDWINDEX *GetFrqAoaGroupedPdwIndex();
	//##ModelId=452B0C44039F
	CSPulExt( void *pParent, int coMaxPdw );
	//##ModelId=452B0C4403AA
	virtual ~CSPulExt();

};

#endif

#endif // !defined(AFX_SPULEXT_H__012521F1_308E_44E3_BA97_612DA873B1A3__INCLUDED_)
