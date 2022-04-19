// NewSigAnal.h: interface for the CNewSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_)
#define AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../INC/Defines.h"
#include "../Identify/Identify.h"

#include "../../Utils/ccommonutils.h"

#include "../SigAnal/SigAnal.h"
#include "NGroup.h"
#include "NPulExt.h"
#include "NAnalPRI.h"
#include "NMakeAET.h"

#define MAX_MATCH_RADARMODE         (2*MAX_RADARMODE)

#ifdef __cplusplus

class CNewSigAnal : public CSigAnal
{
public:
    CNGroup *m_theGroup;
    CNPulExt *m_thePulExt;
    CNAnalPRI *m_theAnalPRI;
    CNMakeAET *m_theMakeAET;

    DEFINE_ANAL_VAR_

private:
    unsigned int m_uiPDWID;

    enum ANALYSIS_MODE m_AnalMode;

    int m_CoGroup;
    UINT m_uiMaxPdw;
    UINT m_uiCoPdw;
    STR_PDWINDEX *m_pGrPdwIndex;
    STR_PDWDATA *m_pPDWData;            // 수집한 데이터 포인터

    STR_PULSE_TRAIN_SEG *m_pSeg;

    unsigned int m_uiIsStorePDW;

    __time32_t m_tColTime;
    unsigned int m_tColTimeMs;

#if defined(_ELINT_) || defined(_XBAND_)
    unsigned char m_szTaskID[LENGTH_OF_TASK_ID];
    EN_RADARCOLLECTORID m_enCollectorID;
    ENUM_BANDWIDTH m_enBandWidth;

    CELSignalIdentifyAlg *m_pIdentifyAlg;		///< CED/EOb 신호 식별 객체
#elif _POCKETSONATA_
    ENUM_BANDWIDTH m_enBandWidth;

    CELSignalIdentifyAlg *m_pIdentifyAlg;		///< CED/EOb 신호 식별 객체

#endif    

    vector<SRadarMode *> m_VecMatchRadarMode;

private:
    void InitAllVar();
    void InitVar(enum ANALYSIS_MODE analMode);
    void Init(STR_PDWDATA *pPDWData = NULL);

    void LoadCEDLibrary();

    enum FREQ_BAND GetBand(int freq);

public:
    CNewSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName = NULL);
    virtual ~CNewSigAnal();

    // 인라인 외부 연결 함수
    inline ENUM_BANDWIDTH GetBandWidth() { return m_enBandWidth; }
    inline int GetCoPdw() { return m_uiCoPdw; }
    inline int GetBand() { return m_theGroup->GetBand(); }
    inline int GetPulseStat() { return m_theGroup->GetPulseStat(); }

    inline void GetCollectTime(struct timespec *pTimeSpec) {
        CCommonUtils::GetCollectTime(pTimeSpec, GetColTime(), GetColTimeMs());
    }

    inline __time32_t GetColTime() {
        return m_tColTime;
    }
    void SetColTime(__time32_t val) { m_tColTime = val; }

    inline unsigned int GetColTimeMs() {
        return m_tColTimeMs;
    }
    void SetColTimeMs(unsigned int val) { m_tColTimeMs = val; }

    inline unsigned int GetPDWID() {
        return m_uiPDWID;
    }
    void SetPDWID(unsigned int val) { m_uiPDWID = val; }

    inline void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile) {
        return CSigAnal::SaveEmitterPdwFile(pEmitter, m_pPDWData->pstPDW, iPLOBID, bSaveFile);
    }

    // inline void DISP_FineAet( STR_UPDAET *pUpdAet ) { m_theMakeAET->DISP_FineAet( pUpdAet ); }
    //inline void DISP_FineAet( STR_MANAET *pManAet ) { /*m_theMakeAET->DISP_FineAet( pManAet );*/ }
    //inline void DISP_FineAet( STR_NEWAET *pNewAet ) { /*m_theMakeAET->DISP_FineAet( pNewAet );*/ }
    inline void DISP_FineAet( SRxLOBData *pNewAet ) { m_theMakeAET->DISP_FineAet( pNewAet ); }
    
    inline SRxLOBData *GetLOBData(int index=0 ) { return m_theMakeAET->GetLOBData(index); }
    
    inline int GetMakeAet() { return m_theMakeAET->GetMakeAet(); }

    inline STR_EMITTER *GetEmitter() { return m_theAnalPRI->GetEmitter(); }
    inline void DISP_HexFineAet( STR_NEWAET *pNewAet ) { m_theMakeAET->DISP_HexFineAet( pNewAet ); }
    inline unsigned int IsStorePDW() { return m_uiIsStorePDW; }
    inline int GetColPdw() { return m_uiCoPdw; }
#if defined(_ELINT_) || defined(_XBAND_)
    inline EN_RADARCOLLECTORID GetCollectorID() { return m_enCollectorID; }
#endif    
    inline unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( pPdwIndex, framePri, pEmitter ); }
    inline unsigned int GetCoSeg() { return m_thePulExt->m_uiCoSeg; }


    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
    inline STR_PDWPARAM* GetPdwParam() { return m_thePulExt->GetPdwParam(); }

    inline UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold ) { return m_theAnalPRI->CheckHarmonic( priMean1, priMean2, uiThreshold ); }
    inline int GetCoEmitter() { return m_theAnalPRI->GetCoEmitter(); }

    //inline int GetCoAet() { return m_theMakeAET->GetCoAet(); }
    inline SRxLOBData *GetLOB() { return m_theMakeAET->GetLOBData(); }
    inline int GetCoLOB() { return m_theMakeAET->GetCoLOB(); }

    inline void SetCoGroups( UINT coGroup ) { m_theGroup->SetCoGroups( coGroup ); }
    inline UINT GetCoGroups() { return m_theGroup->GetCoGroups(); }
    inline void SetColPdw(UINT coPdw ) { m_uiCoPdw=coPdw; }
    inline int GetCoAnalPdw() { return m_theMakeAET->GetCoAnalPdw(); }
    inline void SetCoAnalPdw( UINT coExtPdw ) { m_theMakeAET->SetCoAnalPdw(coExtPdw); }
    inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return m_theGroup->GetFrqAoaGroupedPdwIndex(); }
    inline void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count ) { m_theAnalPRI->CalPRIRange( pSeg, priMean, dtoa_count ); }
    inline void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange ) { m_theAnalPRI->MakeDtoaHistogram( pPdwIndex, uiCount, pRange ); }
    inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return m_theAnalPRI->GetDtoaHist(); }
    inline BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
    inline void DeleteAllSeg( STR_EMITTER *pEmitter ) { m_thePulExt->DeleteAllSeg( pEmitter ); }
    inline void PrintAllSeg() { m_thePulExt->PrintAllSeg(); }
    inline void ExtractRefStable() { m_thePulExt->ExtractRefStable(); }
    inline BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange ) { return m_thePulExt->ExtractDwellRefPT( pDwlSeg, pExtRange ); }
    inline int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex ) { return m_theGroup->FindPeakInHist(uiCount, pPdwIndex ); }
    inline _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->VerifyPRI( pPdwIndex, uiCount ); }
    inline UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, uiCount ); }
    inline void MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { m_theMakeAET->MakePRIInfoInSeg( pPri, pEmitter ); }
    inline UINT ExtractFramePri(STR_PDWINDEX *pPdwIndex, _TOA framePri) { return m_theAnalPRI->ExtractFramePri( pPdwIndex, framePri ); }
    inline unsigned int GetCoPulseTrains() { return m_thePulExt->m_CoPulseTrains; }
    inline void SetCoPulseTrains( UINT coPulses ) { m_thePulExt->m_CoPulseTrains=coPulses; }
    inline unsigned int GetMaxPdw() { return m_uiMaxPdw; }
    inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }
    inline int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->CalcPAMean( pPdwIndex, uiCount); }
    inline int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->VerifyPW( pPdwIndex, uiCount); }
    inline void SetCoAet( UINT coAet ) { m_theMakeAET->SetCoLOB( coAet ); }
    inline CNMakeAET* GetMakeAET() { return m_theMakeAET; }
    //inline void NextSeqNum() { ++ m_nSeqNum; }
    

    // 기타 함수
    void SaveRemainedPdwFile();    
    void MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType);

    void SaveGroupPdwFile( int index );
    unsigned char *GetTaskID();
    bool CheckValidData( STR_PDWDATA *pPDWData );

    inline STR_PDWDATA *GetPDWData() { return m_pPDWData; }

    // 분석 관련 함수
    void Start(STR_PDWDATA *pPDWData );
    bool CheckKnownByAnalysis();

    // 분석 제어 관련 함수
    //void SetSaveFile( bool bEnable );

    void InitResolution();

};

#endif

#endif // !defined(AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_)
