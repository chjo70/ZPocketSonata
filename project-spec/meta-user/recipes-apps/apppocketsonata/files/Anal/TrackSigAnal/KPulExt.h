// KPulExt.h: interface for the CKPulExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KPULEXT_H__49C0026D_6532_46C2_8E6A_58BAA5D3CC31__INCLUDED_)
#define AFX_KPULEXT_H__49C0026D_6532_46C2_8E6A_58BAA5D3CC31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../RSA/NSP/PulExt.h"

class CKnownSigAnal;

//##ModelId=452B0C5201C9
class CKPulExt : public CPulExt
{
protected:
	//##ModelId=452B0C5201D5
	CKnownSigAnal *m_pKnownSigAnal;
	
public:
	//##ModelId=452B0C5201DD
	inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return CPulExt::GetPulseSeg(); }

	//##ModelId=452B0C5201DE
	void DiscardStablePT();
	//##ModelId=452B0C5201DF
	void Init();
	//##ModelId=452B0C5201E7
	void PulseExtract();
	//##ModelId=452B0C5201E8
	STR_DTOA_HISTOGRAM *GetDtoaHist();
	//##ModelId=452B0C5201E9
	void MakeDtoaHistogram( PDWINDEX *pPdwIndex, int count, STR_MINMAX *pRange );
	//##ModelId=452B0C5201FE
	void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, UINT priMean, UINT dtoa_count );
	//##ModelId=452B0C520207
	void MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type );
	//##ModelId=452B0C520211
	STR_PDWINDEX *GetFrqAoaGroupedPdwIndex();

	//##ModelId=452B0C520212
	void KnownPulseExtract();
	//##ModelId=452B0C520213
	CKPulExt( void *pParent, int coMaxPdw=KSP_MAX_PDW );
	//##ModelId=452B0C520223
	virtual ~CKPulExt();

};

#endif // !defined(AFX_KPULEXT_H__49C0026D_6532_46C2_8E6A_58BAA5D3CC31__INCLUDED_)
