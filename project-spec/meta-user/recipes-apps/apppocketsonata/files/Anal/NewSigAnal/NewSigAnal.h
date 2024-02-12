// NewSigAnal.h: interface for the CNewSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_)
#define AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../include/Defines.h"
#include "../Identify/Identify.h"

#include "../../Utils/clog.h"
#include "../../Utils/ccommonutils.h"

#include "../SigAnal/SigAnal.h"
#include "NGroup.h"
#include "NPulExt.h"
#include "NAnalPRI.h"
#include "NMakeAET.h"

#include "../IntraSigAnal/IntraSigAnal.h"

#define MAX_MATCH_RADARMODE         (2*MAX_RADARMODE)

#ifdef __cplusplus

class CNewSigAnal : public CSigAnal
{
private:
    unsigned int m_uiPDWID;

    int m_CoGroup;                          //< 그룹화 총 개수
    UINT m_uiMaxPDW;                        //< 수집 분석할 최대 PDW 개수
    UINT m_uiColPDW;                        //< 수집한  분석할 최대 PDW 개수
    UINT m_uiCoPDW;
    STR_PDWINDEX *m_pGrPdwIndex;
    STR_PDWDATA m_theLOB2PDWData;           //< 해당 LOB의 PDW 데이터
    STR_PDWDATA *m_pPDWData;                //< 수집한 데이터 포인터

    STR_PULSE_TRAIN_SEG *m_pSeg;

    CELSignalIdentifyAlg *m_pIdentifyAlg;		//< CED/EOb 신호 식별 객체

    vector<SRadarMode *> m_VecMatchRadarMode;

public:
    CNGroup *m_theGroup;
    CNPulExt *m_thePulExt;
    CNAnalPRI *m_theAnalPRI;
    CNMakeAET *m_theMakeAET;

    DEFINE_ANAL_VAR_

private:
	void AllocMemory();
    void InitAllVar();
	void StartOfSignalAnalysis( bool bDBInsert );

    void Init(STR_PDWDATA *pPDWData = NULL);
	void InitOfNewSigAnal();

    enum FREQ_BAND GetBand(int freq);

    int GetPLOBIndex();

public:
    CNewSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName = NULL, const char *pThreadName=NULL );
    virtual ~CNewSigAnal();

#ifdef _USRDLL
    bool LoadCEDLibrary();
    bool LoadEOBLibrary();

#endif

    STR_PDWDATA *GetLOB2PDWData( unsigned int uiLOBIndex );

    inline void DeleteAllFiles() {
        CSigAnal::DeleteAllFiles();
    }

    // 인라인 외부 연결 함수
    /**
     * @brief     GetCoPdw
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:28
     * @warning
     */
    inline unsigned int GetCoPdw() {
        return m_uiCoPDW;
    }
    /**
     * @brief     GetBand
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:28
     * @warning
     */
    inline int GetBand() {
        return m_theGroup->GetBand();
    }
    /**
     * @brief     펄스 정보의 상태 값을 리턴한다.
     * @return    int
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:28
     * @warning
     */
    inline int GetPulseStat() {
        return m_theGroup->GetPulseStat();
    }

    /**
     * @brief     시간 정보를 리턴한다.
     * @param     struct timespec * pTimeSpec
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-04-21, 10:28
     * @warning
     */
    inline void GetCollectTime(struct timespec *pTimeSpec) {
        CCommonUtils::GetCollectTime(pTimeSpec, GetColTime(), GetColTimeMs());
    }

    /**
     * @brief     수집 데이터를 특정 폴더에 PDW 파일로 저장한다.
     * @param     STR_EMITTER * pEmitter
     * @param     int iPLOBID
     * @param     bool bSaveFile
     * @return    void
     * @exception
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   0.0.1
     * @date      2022-05-10, 11:53
     * @warning
     */
//     inline void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile) {
//         return CSigAnal::SaveEmitterPDWFile( pEmitter, m_pPDWData->pstPDW, iPLOBID, bSaveFile);
//     }

    inline void DISP_FineLOB( SRxLOBData *pNewAet ) { CSigAnal::DISP_FineLOB( pNewAet ); }

    inline SRxLOBData *GetLOBData(unsigned int index=0 ) { return m_theMakeAET->GetLOBData(index); }
    //inline STR_PDWINDEX *GetLOB2PDWData( unsigned int uiLOBIndex ) { return m_theMakeAET->GetLOB2PDWData( uiLOBIndex ); }

    inline STR_EMITTER *GetEmitter() { return m_theAnalPRI->GetEmitter(); }
    inline unsigned int GetColPdw() { return m_uiCoPDW; }


    ///////////////////////////////////////////////////////////////////////////////////
    // 그룹화 관련 함수 모음.
    inline void SetCoGroups( UINT coGroup ) { m_theGroup->SetCoGroups( coGroup ); }
    inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return m_theGroup->GetFrqAoaGroupedPdwIndex(); }
    inline UINT GetCoFrqAoaPwIdx() { return m_theGroup->GetCoFrqAoaPwIdx(); }
    inline UINT GetCoGroups() { return m_theGroup->GetCoGroups(); }
    inline int FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex ) { return m_theGroup->FindPeakInHist( uiCount, pPdwIndex ); }
    inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }

    ///////////////////////////////////////////////////////////////////////////////////
    // 펄스열 추출 관련 함수 모음.
    inline STR_PDWPARAM *GetPdwParam() { return m_thePulExt->GetPdwParam(); }
    inline unsigned int GetCoSeg() { return m_thePulExt->m_uiCoSeg; }
    inline unsigned int ExtractStagger( _TOA framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( framePri, pEmitter ); }
    inline void MarkToPDWIndex( PDWINDEX *pPDWIndex, unsigned int uiCount, PULSE_MARK enMarkType ) { m_thePulExt->MarkToPDWIndex( pPDWIndex, uiCount, enMarkType ); }
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
    inline bool CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
    inline void PrintAllSeg() { m_thePulExt->PrintAllSeg(); }
    inline _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->VerifyPRI( pPdwIndex, uiCount ); }
    inline bool ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange ) { return m_thePulExt->ExtractDwellRefPT( pDwlSeg, pExtRange ); }
    inline UINT MedianFreq( STR_MINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, uiCount ); }
    inline void ExtractRefStable() { m_thePulExt->ExtractRefStable(); }
    inline int CalcPAMean( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->CalcPAMean( pPdwIndex, uiCount ); }
    inline unsigned int VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->VerifyPW( pPdwIndex, uiCount ); }
    inline bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2, int iMaxMiss, bool bForceMerge ) { return m_thePulExt->CheckStablePT( pnHarmonic, pSeg1, pSeg2, iMaxMiss, bForceMerge ); }


    ///////////////////////////////////////////////////////////////////////////////////
    // PRI 분석 관련 함수 모음.
    inline UINT CheckHarmonic( _TOA priMean1, _TOA priMean2, _TOA uiThreshold ) { return m_theAnalPRI->CheckHarmonic( priMean1, priMean2, uiThreshold ); }
    inline unsigned int GetCoEmitter() { return m_theAnalPRI->GetCoEmitter(); }
    inline void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count ) { m_theAnalPRI->CalPRIRange( pSeg, priMean, dtoa_count ); }
    inline void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange ) { m_theAnalPRI->MakeDtoaHistogram( pPdwIndex, uiCount, pRange ); }
    inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return m_theAnalPRI->GetDtoaHist(); }
    //inline UINT ExtractFramePri( STR_PDWINDEX *pPdwIndex, _TOA framePri ) { return m_theAnalPRI->ExtractFramePri( pPdwIndex, framePri ); }

    ///////////////////////////////////////////////////////////////////////////////////
    // 에미터 생성 관련 함수 모음.
    inline int GetCoLOB() { return m_theMakeAET->GetCoLOB(); }
    inline int GetCoAnalPdw() { return m_theMakeAET->GetCoAnalPdw(); }
    inline void SetCoAnalPdw( UINT coExtPdw ) { m_theMakeAET->SetCoAnalPdw( coExtPdw ); }
    //inline void MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { m_theMakeAET->MakePRIInfoFromSeg( pPri, pEmitter ); }
    inline void SetCoAet( UINT coAet ) { m_theMakeAET->SetCoLOB( coAet ); }
    inline CNMakeAET *GetMakeAET() { return m_theMakeAET; }

    //inline ENUM_ANAL_TYPE GetAnalType() { return m_enAnalType; }

    inline void SetColPdw(UINT coPdw ) { m_uiCoPDW=coPdw; }

    //inline unsigned int GetCoPulseTrains() { return m_thePulExt->m_CoPulseTrains; }
    //inline void SetCoPulseTrains( UINT coPulses ) { m_thePulExt->m_CoPulseTrains=coPulses; }
    inline unsigned int GetMaxPdw() { return m_uiMaxPDW; }


    inline int GetCoGroup() { return m_CoGroup; }

    inline void SetGlobalBoardID( ENUM_BoardID enBoardID ) { g_enBoardId = enBoardID; }

    //inline void NextSeqNum() { ++ m_nSeqNum; }

    // 기타 함수
    bool CheckValidData( STR_PDWDATA *pPDWData );

    inline STR_PDWDATA *GetPDWData() { return m_pPDWData; }

    // 분석 관련 함수
    void Start(STR_PDWDATA *pPDWData, bool bDBInsert=false );
    bool CheckKnownByAnalysis();

    void SaveDebug( const char *pSourcefile, int iLines );

    void MakeDirectory( time_t ti, ENUM_COLLECTBANK enCollectBank )
    {
        CSigAnal::MakeDirectory( ti, enCollectBank );
    }

};

#endif

#endif // !defined(AFX_NEWSIGANAL_H__9A66BC5E_1BC5_41A1_86AC_4C0DC4414610__INCLUDED_)
