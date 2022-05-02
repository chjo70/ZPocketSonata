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

    int GetCoPdw();

    //##ModelId=452B0C5201DE
    void DiscardStablePT();
    //##ModelId=452B0C5201DF
    void Init();
    //##ModelId=452B0C5201E7
    void PulseExtract();

    void ExtractPulseTrainByLibrary(vector<SRadarMode *> *pVecMatchRadarMode);
    void PulseExtract(vector<SRadarMode *> *pVecMatchRadarMode);


    //##ModelId=452B0C5201E8
    STR_DTOA_HISTOGRAM *GetDtoaHist();
    //##ModelId=452B0C5201E9
    void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange );
    //##ModelId=452B0C5201FE
    void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count );
    //##ModelId=452B0C520207
    void MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType);
    //##ModelId=452B0C520211
    STR_PDWINDEX *GetFrqAoaGroupedPdwIndex();
    UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold );
    void ClearAllMark();

    //##ModelId=452B0C520212
    void KnownPulseExtract();
    //##ModelId=452B0C520213
    CKPulExt( void *pParent, int coMaxPdw );
    //##ModelId=452B0C520223
    virtual ~CKPulExt();

};

#endif

#endif // !defined(AFX_KPULEXT_H__49C0026D_6532_46C2_8E6A_58BAA5D3CC31__INCLUDED_)
