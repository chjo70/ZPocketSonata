// KPulExt.h: interface for the CKPulExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KPULEXT_H__49C0026D_6532_46C2_8E6A_58BAA5D3CC31__INCLUDED_)
#define AFX_KPULEXT_H__49C0026D_6532_46C2_8E6A_58BAA5D3CC31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/PulExt.h"

#ifdef __cplusplus

class CKnownSigAnal;

//##ModelId=452B0C5201C9
class CKPulExt : public CPulExt
{
private:
    UINT m_CoPulseTrains;

    SRxABTData *m_pTrkAet;

protected:
    //##ModelId=452B0C5201D5
    CKnownSigAnal *m_pKnownSigAnal;

public:
    //##ModelId=452B0C5201DD
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return CPulExt::GetPulseSeg(); }

    unsigned int GetCoPdw();

    void DiscardStablePT();
    void Init();
    void PulseExtract();

    void ExtractPulseTrainByLibrary(vector<SRadarMode *> *pVecMatchRadarMode);
    void PulseExtract(vector<SRadarMode *> *pVecMatchRadarMode);

    STR_DTOA_HISTOGRAM *GetDtoaHist();
    void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange );
    void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );

    STR_PDWINDEX *GetFrqAoaGroupedPdwIndex();
    UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold );
    //void ClearAllMark();

    void KnownPulseExtract();
    CKPulExt( void *pParent, unsigned int uiCoMaxPdw );
    virtual ~CKPulExt();

};

#endif

#endif // !defined(AFX_KPULEXT_H__49C0026D_6532_46C2_8E6A_58BAA5D3CC31__INCLUDED_)
