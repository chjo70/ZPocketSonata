﻿// NewSigAnal.h: interface for the CNewSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_)
#define AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "../../ELINTOP/ODBC/mssql.h"
//#include "../../ELINTOP/ODBC/odbccore.h"

#include "../INC/defines.h"
#include "../Identify/Identify.h"

#include "NGroup.h"
#include "NPulExt.h"
#include "NAnalPRI.h"
#include "NMakeAET.h"

#include "../MIDAS/Midas.h"
//#include "../MIDAS/RawFile.h"

#include "../../Utils/clog.h"

#ifdef __cplusplus

class CNewSigAnal
{
public:
    CNGroup *m_theGroup;
    CNPulExt *m_thePulExt;
    CNAnalPRI *m_theAnalPRI;
    CNMakeAET *m_theMakeAET;

    //STR_NEWAET m_theSimulAET[_SIMUL_CO_ANAL_];

    DEFINE_ANAL_VAR_

private:
    enum ANALYSIS_MODE m_AnalMode;
    UINT m_uiStep;
    int m_CoGroup;
    UINT m_nMaxPdw;
    UINT m_CoPdw;
    STR_PDWINDEX *m_pGrPdwIndex;
    STR_PDWDATA *m_pPDWData;
    STR_PULSE_TRAIN_SEG *m_pSeg;

    int m_iIsStorePDW;
#ifdef _ELINT_
    EN_RADARCOLLECTORID m_enCollectorID;
#endif

    ENUM_BANDWIDTH m_enBandWidth;

    bool m_bSaveFile;

    UINT m_uiCoKnownRadarMode;
    SRadarMode *m_pRadarMode[ MAX_ELINT_LIBRARY ];
    //CODBCDatabase m_theMyODBC;
    CELSignalIdentifyAlg *m_pIdentifyAlg;		///< CED/EOb 신호 식별 객체

    CMIDASBlueFileFormat *m_pMidasBlue;

private:


public:
    enum FREQ_BAND GetBand( int freq );
    void Simul();

    void Init();

    // 인라인 외부 연결 함수
    inline ENUM_BANDWIDTH GetBandWidth() { return m_enBandWidth; }
    inline int GetCoPdw() { return m_CoPdw; }
    inline int GetBand() { return m_theGroup->GetBand(); }
    inline int GetPulseStat() { return m_theGroup->GetPulseStat(); }

    // inline void DISP_FineAet( STR_UPDAET *pUpdAet ) { m_theMakeAET->DISP_FineAet( pUpdAet ); }
    inline void DISP_FineAet( STR_MANAET *pManAet ) { /*m_theMakeAET->DISP_FineAet( pManAet );*/ }
    inline void DISP_FineAet( STR_NEWAET *pNewAet ) { /*m_theMakeAET->DISP_FineAet( pNewAet );*/ }
    inline SRxLOBData *GetLOBData(int index=0 ) { return m_theMakeAET->GetLOBData(index); }
    inline int GetCoAet() { return m_theMakeAET->GetCoAet(); }
    inline int GetMakeAet() { return m_theMakeAET->GetMakeAet(); }

    inline STR_EMITTER *GetEmitter() { return m_theAnalPRI->GetEmitter(); }
    inline void DISP_HexFineAet( STR_NEWAET *pNewAet ) { m_theMakeAET->DISP_HexFineAet( pNewAet ); }
    inline int IsStorePDW() { return m_iIsStorePDW; }
    inline int GetColPdw() { return m_CoPdw; }
#ifdef _ELINT_
    inline EN_RADARCOLLECTORID GetCollectorID() { return m_enCollectorID; }
#endif
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
    inline int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( pPdwIndex, framePri, pEmitter ); }
    inline int GetCoSeg() { return m_thePulExt->m_CoSeg; }


    inline UINT CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold ) { return m_theAnalPRI->CheckHarmonic( priMean1, priMean2, uiThreshold ); }
    inline int GetCoLOB() { return m_theAnalPRI->GetCoEmitter(); }
    inline STR_PDWPARAM* GetPdwParam() { return m_thePulExt->GetPdwParam(); }
    inline void SetStep( UINT nStep ) { m_uiStep = nStep; }
    inline void SetCoGroups( UINT coGroup ) { m_theGroup->SetCoGroups( coGroup ); }
    inline UINT GetCoGroups() { return m_theGroup->GetCoGroups(); }
    inline UINT GetCoStep() { return m_uiStep; }
    inline void SetColPdw(UINT coPdw ) { m_CoPdw=coPdw; }
    inline int GetCoAnalPdw() { return m_theMakeAET->GetCoAnalPdw(); }
    inline void SetCoAnalPdw( UINT coExtPdw ) { m_theMakeAET->SetCoAnalPdw(coExtPdw); }
    inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return m_theGroup->GetFrqAoaGroupedPdwIndex(); }
    inline void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count ) { m_theAnalPRI->CalPRIRange( pSeg, priMean, dtoa_count ); }
    inline void MakeDtoaHistogram( PDWINDEX *pPdwIndex, int count, STR_MINMAX_TOA *pRange ) { m_theAnalPRI->MakeDtoaHistogram( pPdwIndex, count, pRange ); }
    inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return m_theAnalPRI->GetDtoaHist(); }
    inline BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
    inline void DeleteAllSeg( STR_EMITTER *pEmitter ) { m_thePulExt->DeleteAllSeg( pEmitter ); }
    inline void PrintAllSeg() { m_thePulExt->PrintAllSeg(); }
    inline void ExtractRefStable() { m_thePulExt->ExtractRefStable(); }
    inline BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange ) { return m_thePulExt->ExtractDwellRefPT( pDwlSeg, pExtRange ); }
    inline int FindPeakInHist( int count, PDWINDEX *pPdwIndex ) { return m_theGroup->FindPeakInHist( count, pPdwIndex ); }
    inline _TOA VerifyPRI( PDWINDEX *pPdwIndex, int count ) { return m_thePulExt->VerifyPRI( pPdwIndex, count ); }
    inline UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, int count ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, count ); }
    inline void MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { m_theMakeAET->MakePRIInfoInSeg( pPri, pEmitter ); }
    inline UINT ExtractFramePri(STR_PDWINDEX *pPdwIndex, _TOA framePri) { return m_theAnalPRI->ExtractFramePri( pPdwIndex, framePri ); }
    inline int GetCoPulseTrains() { return m_thePulExt->m_CoPulseTrains; }
    inline void SetCoPulseTrains( UINT coPulses ) { m_thePulExt->m_CoPulseTrains=coPulses; }
    inline int GetMaxPdw() { return m_nMaxPdw; }
    inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }
    inline int CalcPAMean(PDWINDEX *pPdwIndex, int count) { return m_thePulExt->CalcPAMean( pPdwIndex, count); }
    inline int VerifyPW(PDWINDEX *pPdwIndex, int count) { return m_thePulExt->VerifyPW( pPdwIndex, count); }
    inline void SetCoAet( UINT coAet ) { m_theMakeAET->SetCoAet( coAet ); }

    // 기타 함수
    void SaveRemainedPdwFile();
    void InitAllVar();
    void InitVar( enum ANALYSIS_MODE analMode );
    void SWInit();
    void Init( STR_PDWDATA *pPDWData=NULL );
    void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index );
    void MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type);

    void SaveGroupPdwFile( int index );
    char *GetTaskID();
    bool CheckValidData( STR_PDWDATA *pPDWData );

    inline STR_PDWDATA *GetPDWData() { return m_pPDWData; }

    // 분석 관련 함수
    void Start(STR_PDWDATA *pPDWData );
    bool CheckKnownByAnalysis();

    // 분석 제어 관련 함수
    void SetSaveFile( bool bEnable );

    CNewSigAnal( int coMaxPdw );
    virtual ~CNewSigAnal();

};

#endif

#endif // !defined(AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_)
