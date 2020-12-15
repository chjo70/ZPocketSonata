// KAnalPRI.h: interface for the CKAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KANALPRI_H__E067780C_6672_47DC_89CB_69F320B7FD52__INCLUDED_)
#define AFX_KANALPRI_H__E067780C_6672_47DC_89CB_69F320B7FD52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/AnalPRI.h"

#ifdef __cplusplus

class CKnownSigAnal;

//##ModelId=452B0C5300E4
class CKAnalPRI : public CAnalPRI
{
private:
    SRxABTData *m_pTrkAet;

protected:
    //##ModelId=452B0C5300EF
    CKnownSigAnal *m_pKnownSigAnal;

public:
    //##ModelId=452B0C5300F8
    inline void SetAnalSeg( int coSeg ) { CAnalPRI::SetAnalSeg( coSeg ); }
    //##ModelId=452B0C5300FA
    inline void SetCoSeg( int nSeg ) { CAnalPRI::SetCoSeg( nSeg ); }

    int GetBand();


    //##ModelId=452B0C5300FC
    void Init();
    //##ModelId=452B0C530102
    void Analysis();
    //##ModelId=452B0C530103
    int FindPeakInHist( int count, PDWINDEX *pPdwIndex );
    //##ModelId=452B0C530106
    int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter );
    //##ModelId=452B0C53010F
    BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    //##ModelId=452B0C530116
    void DeleteAllSeg( STR_EMITTER *pEmitter );
    //##ModelId=452B0C530118
    void ExtractRefStable();
    //##ModelId=452B0C530119
    BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange );
    //##ModelId=452B0C530120
    UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri );
    //##ModelId=452B0C530123
    int GetCoSeg();
    //##ModelId=452B0C530124
    int GetAnalSeg();
    //##ModelId=452B0C530125
    STR_PULSE_TRAIN_SEG *GetPulseSeg();
    //##ModelId=452B0C53012A
    int GetMaxPdw();
    //##ModelId=452B0C53012B
    void MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter );
    //##ModelId=452B0C53012E
    UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, int count );
    //##ModelId=452B0C530137
    _TOA VerifyPRI( PDWINDEX *pPdwIndex, int count );

    void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index );

    //##ModelId=452B0C53013E
    void GroupingKnownPri();
    //##ModelId=452B0C53013F
    BOOL KnownAnalysis();
    //##ModelId=452B0C530140
    CKAnalPRI( void *pParent, int coMaxPdw=KSP_MAX_PDW );
    //##ModelId=452B0C530143
    virtual ~CKAnalPRI();

};

#endif

#endif // !defined(AFX_KANALPRI_H__E067780C_6672_47DC_89CB_69F320B7FD52__INCLUDED_)
