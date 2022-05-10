// KnownSigAnal.h: interface for the CKnownSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KNOWNSIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_)
#define AFX_KNOWNSIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "KDefine.h"

#include "../../Utils/ccommonutils.h"

#include "../SigAnal/SigAnal.h"
#include "KGroup.h"
#include "KPulExt.h"
#include "KAnalPRI.h"
#include "KMakeAET.h"


#ifdef __cplusplus

//##ModelId=452B0C520241
class CKnownSigAnal : public CSigAnal
{
private:
    SRxABTData *m_pTrkAet;

    int m_CoGroup;

    vector<SRadarMode *> m_VecMatchRadarMode;

public:
    //##ModelId=452B0C52024B
    int m_CoNewAet;
    //##ModelId=452B0C52024C
    int m_CoUpdAet;
    //##ModelId=452B0C520256
    STR_PDWINDEX *m_pGrPdwIndex;

    DEFINE_ANAL_VAR_

protected:
    //##ModelId=452B0C520260
    CKGroup *m_theGroup;
    //##ModelId=452B0C520265
    CKPulExt *m_thePulExt;
    //##ModelId=452B0C52026A
    CKAnalPRI *m_theAnalPRI;
    //##ModelId=452B0C520274
    CKMakeAET *m_theMakeAET;

    //##ModelId=452B0C520279
    STR_PULSE_TRAIN_SEG *m_pSeg;
    //##ModelId=452B0C52027D
    int m_nMaxPdw;
    //##ModelId=452B0C520287
    unsigned int m_uiCoPdw;
    //##ModelId=452B0C520288
    int m_noSbc;
    //##ModelId=452B0C520291
    int m_noCh;
    //##ModelId=452B0C52029C
    //STR_PDWBANK *m_pPdwBank;
    STR_STATIC_PDWDATA *m_pstPDWData;

private:
    bool CheckKnownByAnalysis();

public:
    CKnownSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName = NULL);
    virtual ~CKnownSigAnal();

    inline void GetCollectTime(struct timespec *pTimeSpec) {
        CCommonUtils::GetCollectTime(pTimeSpec, GetColTime(), GetColTimeMs());
    }

    inline void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile) {
        return CSigAnal::SaveEmitterPDWFile(pEmitter, m_pstPDWData->stPDW, iPLOBID, bSaveFile);
    }

    void Init();

    inline unsigned int GetCoPdw() { return m_uiCoPdw; }
    inline unsigned int GetColPdw() { return m_uiCoPdw; }
    inline int GetBand() { return m_theGroup->GetBand(); }
    inline int GetCoUpdAet() { return m_CoUpdAet; }
    //##ModelId=452B0C5202A5
    inline int GetMaxPdw() { return m_nMaxPdw; }
    
    //##ModelId=452B0C5202A8
    inline void MakePDWArray( _PDW *pdw, int iCount ) { m_theGroup->MakePDWArray( pdw, iCount); }
    //##ModelId=452B0C5202B1
    inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return m_theGroup->GetFrqAoaGroupedPdwIndex(); }
    //##ModelId=452B0C5202B9
    inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }
    //##ModelId=452B0C5202BB
    inline int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex ) { return m_theGroup->FindPeakInHist( uiCount, pPdwIndex ); }
	
    //##ModelId=452B0C5202CE
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
    //##ModelId=452B0C5202CF
    inline int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->CalcPAMean( pPdwIndex, uiCount); }
    //##ModelId=452B0C5202D8
    inline int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->VerifyPW( pPdwIndex, uiCount); }
    //##ModelId=452B0C5202E1
    inline int GetCoSeg() { return m_thePulExt->m_uiCoSeg; }
    //##ModelId=452B0C5202E2
    inline int GetAnalSeg() { return m_thePulExt->m_uiAnalSeg; }
    //##ModelId=452B0C5202E3
    inline UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, uiCount ); }
    //##ModelId=43D4818F0298
    //inline void SetAnalSeg( int co ) { m_thePulExt->SetAnalSeg( co ); }


	inline UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold ) { return m_theAnalPRI->CheckHarmonic( priMean1, priMean2, uiThreshold ); }

    //##ModelId=452B0C520301
    inline BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
    //##ModelId=452B0C52030A
    inline unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( pPdwIndex, framePri, pEmitter ); }
    //##ModelId=452B0C520314
    inline _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->VerifyPRI( pPdwIndex, uiCount); }
    inline STR_PDWPARAM* GetPdwParam() { return m_thePulExt->GetPdwParam(); }

    //##ModelId=452B0C52031E
    inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return m_theAnalPRI->GetDtoaHist(); }
    //##ModelId=452B0C52031F
    inline void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange ) { m_theAnalPRI->MakeDtoaHistogram( pPdwIndex, uiCount, pRange ); }
    //##ModelId=452B0C520329
    inline void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count ) { m_theAnalPRI->CalPRIRange( pSeg, priMean, dtoa_count ); }
    //##ModelId=452B0C52033D
    inline void DeleteAllSeg( STR_EMITTER *pEmitter ) { m_thePulExt->DeleteAllSeg( pEmitter ); }
    //##ModelId=452B0C520346
    inline void ExtractRefStable() { m_theAnalPRI->ExtractRefStable(); }
    //##ModelId=452B0C52034F
    inline BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange ) { return m_theAnalPRI->ExtractDwellRefPT( pDwlSewg, pExtRange ); }
    //##ModelId=452B0C520351
    inline UINT ExtractFramePri(STR_PDWINDEX *pPdwIndex, _TOA framePri) { return m_theAnalPRI->ExtractFramePri( pPdwIndex, framePri ); }
    //##ModelId=452B0C52035A
    inline STR_EMITTER *GetEmitter() { return m_theAnalPRI->GetEmitter(); }
    //##ModelId=452B0C52035B
    inline int GetCoEmitter() { return m_theAnalPRI->GetCoEmitter(); }

    inline SRxLOBData *GetLOBData( int index=0 ) { return m_theMakeAET->GetLOBData(index); }
    //##ModelId=452B0C52035B
    inline int GetCoLOB() { return m_theMakeAET->GetCoLOB(); }
    //##ModelId=452B0C52035C
    inline int GetCoNewAet() { return m_CoNewAet; }
    //##ModelId=452B0C520363
    inline SRxLOBData *GetNewAet() { return m_theMakeAET->GetNewLOB(); }
    //##ModelId=452B0C520364
    inline void ClearCoAet() { m_theMakeAET->ClearCoAet(); }
    //##ModelId=452B0C520365
    inline void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { m_theMakeAET->MakePRIInfoFromSeg( pPri, pEmitter ); }
    inline CKMakeAET* GetMakeAET() { return m_theMakeAET; }
    inline SRxLOBData *GetUpdAet() { return m_theMakeAET->GetUpdLOB(); }
    inline SRxABTData *GetTrkAET() { return m_pTrkAet; }

    

    void InitVar();
    //##ModelId=452B0C52036E
    void ClearColBuffer();
    //##ModelId=452B0C52036F
    void SendAllAet();
    //##ModelId=452B0C520370
    void SendUpdAet( SRxLOBData *pUpdAet );
    //##ModelId=452B0C520378
    void SendLostAet();
    //##ModelId=452B0C520379
    void SendNewAet( SRxLOBData *pNewAet, int inEMT );

    //##ModelId=452B0C52038B
    void MarkToPdwIndex(PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType);

    //##ModelId=452B0C520396
    void Init( STR_STATIC_PDWDATA *pstPDWData );
    //##ModelId=452B0C52039F
    void Start( STR_STATIC_PDWDATA *pstPDWData, SRxABTData *pTrkAet );

    void DISP_FineAet(SRxLOBData *pLOB) {
        CSigAnal::DISP_FineAet(pLOB);
    }

};

#endif

/*
extern "C" {
	void CreateKnownSigAnalClass();
	void DeleteKnownSigAnalClass();

	int KnownSigAnal( int noSbc, int noCh );
	void SendKSPNewAet( STR_NEWAET *pAet, UINT inEMT );
	void SendKSPUpdAet( STR_UPDAET *pUpdAet );
	void SendKSPLostAet( STR_TRKAET *pAet, int stat );
	
	extern CKnownSigAnal *theKnownSigAnal;

}
*/

#endif // !defined(AFX_KNOWNSIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_)
