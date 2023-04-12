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
    CKGroup *m_theGroup;
    CKPulExt *m_thePulExt;
    CKAnalPRI *m_theAnalPRI;
    CKMakeAET *m_theMakeAET;

    STR_PULSE_TRAIN_SEG *m_pSeg;

    unsigned int m_uiMaxPdw;

    unsigned int m_uiCoPdw;
    int m_noSbc;
    int m_noCh;

    //STR_PDWBANK *m_pPdwBank;
    STR_STATIC_PDWDATA *m_pstPDWData;

private:
    bool CheckKnownByAnalysis();
	void StartOfTrackSignalAnalysis();
	void StartOfNewSignalAnalysis();

    int GetPLOBIndex();

public:
    CKnownSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName = NULL);
    virtual ~CKnownSigAnal();

    inline void GetCollectTime(struct timespec *pTimeSpec) {
        CCommonUtils::GetCollectTime(pTimeSpec, GetColTime(), GetColTimeMs());
    }

    inline void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile) {
        return CSigAnal::SaveEmitterPDWFile(pEmitter, m_pstPDWData->stPDW, iPLOBID, bSaveFile);
    }

    void Init();

    inline unsigned int GetCoPdw() { return m_uiCoPdw; }
    inline unsigned int GetColPdw() { return m_uiCoPdw; }
    inline int GetBand() { return m_theGroup->GetBand(); }
    inline int GetCoUpdAet() { return m_CoUpdAet; }

    /**
     * @brief     GetMaxPdw
     * @return    unsigned int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-10 13:09:22
     * @warning
     */
    inline unsigned int GetMaxPdw() {
		return m_uiMaxPdw;
	}


    /**
     * @brief     MakePDWArray
     * @param     _PDW * pdw
     * @param     int iCount
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-10 13:09:15
     * @warning
     */
    inline void MakePDWArray( _PDW *pdw, int iCount ) {
		m_theGroup->MakePDWArray( pdw, (UINT) iCount);
	}

    /**
     * @brief     GetFrqAoaGroupedPdwIndex
     * @return    STR_PDWINDEX *
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-10 13:09:30
     * @warning
     */
    inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() {
		return m_theGroup->GetFrqAoaGroupedPdwIndex();
	}

    inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }
    inline int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex ) { return m_theGroup->FindPeakInHist( uiCount, pPdwIndex ); }
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
    inline int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->CalcPAMean( pPdwIndex, uiCount); }
    inline unsigned int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->VerifyPW( pPdwIndex, uiCount); }
    inline unsigned int GetCoSeg() { return m_thePulExt->m_uiCoSeg; }
    inline unsigned int GetAnalSeg() { return m_thePulExt->m_uiAnalSeg; }
    inline UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, uiCount ); }
    inline bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckStablePT( pnHarmonic, pSeg1, pSeg2 ); }
    inline void MarkToPDWIndex( PDWINDEX *pPDWIndex, UINT uiCount, PULSE_MARK enMarkType ) { m_thePulExt->MarkToPDWIndex( pPDWIndex, uiCount, (UINT) enMarkType); }
	inline UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold ) { return m_theAnalPRI->CheckHarmonic( priMean1, priMean2, uiThreshold ); }
    inline BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
    inline unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( pPdwIndex, framePri, pEmitter ); }
    inline _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->VerifyPRI( pPdwIndex, uiCount); }
    inline STR_PDWPARAM* GetPdwParam() { return m_thePulExt->GetPdwParam(); }

    inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return m_theAnalPRI->GetDtoaHist(); }
    inline void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange ) { m_theAnalPRI->MakeDtoaHistogram( pPdwIndex, uiCount, pRange ); }
    inline void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count ) { m_theAnalPRI->CalPRIRange( pSeg, priMean, dtoa_count ); }
    inline void DeleteAllSeg( STR_EMITTER *pEmitter ) { m_thePulExt->DeleteAllSeg( pEmitter ); }
    inline void ExtractRefStable() { m_theAnalPRI->ExtractRefStable(); }
    inline BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange ) { return m_theAnalPRI->ExtractDwellRefPT( pDwlSewg, pExtRange ); }
    inline UINT ExtractFramePri(STR_PDWINDEX *pPdwIndex, _TOA framePri) { return m_theAnalPRI->ExtractFramePri( pPdwIndex, framePri ); }
    inline STR_EMITTER *GetEmitter() { return m_theAnalPRI->GetEmitter(); }
    inline unsigned int GetCoEmitter() { return m_theAnalPRI->GetCoEmitter(); }

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

    /**
     * @brief     GetTrkAET
     * @return    SRxABTData *
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-10 13:09:44
     * @warning
     */
    inline SRxABTData *GetTrkAET() {
		return m_pTrkAet;
	}

    /**
     * @brief     GetCoGroup
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2022-07-10 13:09:38
     * @warning
     */
    inline int GetCoGroup() {
		return m_CoGroup;
	}



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

    //##ModelId=452B0C520396
    void Init( STR_STATIC_PDWDATA *pstPDWData );
    //##ModelId=452B0C52039F
    void Start( STR_STATIC_PDWDATA *pstPDWData, SRxABTData *pTrkAet );

    void DISP_FineLOB(SRxLOBData *pLOB) {
        CSigAnal::DISP_FineLOB(pLOB);
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
