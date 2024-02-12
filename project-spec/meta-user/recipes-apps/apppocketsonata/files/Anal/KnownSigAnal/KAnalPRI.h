/**

    @file      KAnalPRI.h
    @brief      interface for the CKAnalPRI class.
    @details   ~
    @author    조철희
    @date      2.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "../../Utils/clog.h"

#include "../SigAnal/AnalPRI.h"
#include "../SigAnal/MakeAET.h"

#ifdef __cplusplus

class CKnownSigAnal;

class CKAnalPRI : public CAnalPRI
{
private:
    SRxABTData *m_pTrkABT;

protected:
    CKnownSigAnal *m_pKnownSigAnal;

    static STR_PULSE_TRAIN_SEG *m_pSeg;

public:
    CKAnalPRI( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName=NULL );
    virtual ~CKAnalPRI();
    //inline void SetAnalSeg( int coSeg ) { CAnalPRI::SetAnalSeg( coSeg ); }

    int GetBand();

    //void QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof );

    void Init();
    void Analysis();
    int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex );
    unsigned int ExtractStagger( _TOA framePri, STR_EMITTER *pEmitter );
    bool CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );

    //void DeleteAllSeg( STR_EMITTER *pEmitter );

    void ExtractRefStable();

    bool ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange );

    //UINT ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri );

    unsigned int GetCoSeg();
    unsigned int GetAnalSeg();
    STR_PULSE_TRAIN_SEG *GetPulseSeg();

    unsigned int GetMaxPDW();

    //void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter );

    UINT MedianFreq( STR_MINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );

    _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount );

    //void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile );

    void HoppingAnalysis();

    bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2, int iMaxMiss, bool bForceMerge=false );

    bool KnownAnalysis( ENUM_ROBUST_ANAL enRobustAnal );

    CMakeAET* GetMakeAET();

    //static int incSegPriMeanCompare( const void *arg1, const void *arg2 );

    inline void *GetParentSigAnal() { return ( void * ) m_pKnownSigAnal; }

    void SaveDebug( const char *pSourcefile, int iLines );

};

#endif

