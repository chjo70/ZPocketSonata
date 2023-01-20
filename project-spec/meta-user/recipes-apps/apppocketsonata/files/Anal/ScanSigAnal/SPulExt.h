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
	unsigned int m_uiMaxPdw;
	unsigned int m_uinoEMT;
	int m_noCh;

	CScanSigAnal *m_pScanSigAnal;
	
public:
	unsigned int GetCoPdw();
	void SaveScanPulse( STR_PDWINDEX *pPdwIndex );
	
	STR_DTOA_HISTOGRAM *GetDtoaHist();
	

    void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange );
    void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );
    void DiscardStablePT();

    void ClearAllMark();

	void SaveScanPulse();
	void Init();
	void KnownPulseExtract();

	STR_PDWINDEX *GetFrqAoaGroupedPdwIndex();

	CSPulExt( void *pParent, unsigned int uiCoMaxPdw );
	virtual ~CSPulExt();

};

#endif

#endif // !defined(AFX_SPULEXT_H__012521F1_308E_44E3_BA97_612DA873B1A3__INCLUDED_)
