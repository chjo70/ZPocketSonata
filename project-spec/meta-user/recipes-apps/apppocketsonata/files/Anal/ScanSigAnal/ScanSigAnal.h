/**

    @file      ScanSigAnal.h
    @brief     interface for the CScanSigAnal class.
    @details   ~
    @author    조철희
    @date      27.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SDefine.h"
#include "SStruct.h"

#include "../../Utils/clog.h"
#include "../../Utils/ccommonutils.h"

#include "../SigAnal/SigAnal.h"
#include "SGroup.h"
#include "SPulExt.h"
#include "SAnalSCN.h"

#ifdef __cplusplus

class CScanSigAnal : public CSigAnal
{
private:
    SRxABTData *m_pScnAet;

public:
    STR_PDWINDEX *m_pGrPdwIndex;

    DEFINE_ANAL_VAR_

protected:
    STR_UPDAET *m_pUpdAet;
    STR_PULSE_TRAIN_SEG *m_pSeg;
    STR_STATIC_PDWDATA *m_pstPDWData;

    unsigned int m_uiNoCh;
    unsigned int m_uiCoPdw;
    unsigned int m_uinoEMT;

    CSGroup *m_theGroup;
    CSPulExt *m_thePulExt;
    CSAnalScan *m_theAnalScan;

    unsigned int m_uiMaxPdw;

    STR_SCANRESULT m_strScnResult;


public:
    CScanSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName = NULL);
    virtual ~CScanSigAnal();

    inline void GetCollectTime(struct timespec *pTimeSpec) {
        CCommonUtils::GetCollectTime(pTimeSpec, GetColTime(), GetColTimeMs());
    }

    void SaveEmitterPDWFile( STR_PDWINDEX *pPdw, int iPLOBID );
    void InitVar();
    void SaveScanInfo( UINT nResult, STR_UPDAET *pUpdAet, bool bOnlyThreat=FALSE );

    inline unsigned int GetMaxPdw() { return m_uiMaxPdw; }
    inline STR_STATIC_PDWDATA *GetPDWData() { return m_pstPDWData; }
    inline unsigned int GetNoEMT() { return m_uinoEMT; }
    inline unsigned int GetScanNoCh() { return m_uiNoCh; }
    inline unsigned int GetColPdw() { return m_uiCoPdw; }

    inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }
    inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return m_theGroup->GetFrqAoaGroupedPdwIndex(); }
    inline UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, uiCount ); }

    inline unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, UINT framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( pPdwIndex, framePri, pEmitter ); }

    inline bool CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
    inline int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->CalcPAMean( pPdwIndex, uiCount); }
    inline unsigned int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->VerifyPW( pPdwIndex, uiCount); }
    inline _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->VerifyPRI( pPdwIndex, uiCount ); }
    inline _TOA CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckStablePT( pnHarmonic, pSeg1, pSeg2 ); }

    inline STR_SCANRESULT *GetScanResult() { return & m_strScnResult; }
    inline SRxLOBData *GetLOBData(int index=0) { return m_theAnalScan->GetLOBData(index); }

    inline int GetBand() { return m_theGroup->GetBand(); }
    inline unsigned int GetCoPdw() { return m_uiCoPdw; }
    inline unsigned int GetCoSeg() { return m_thePulExt->m_uiCoSeg; }
    inline SRxABTData *GetScnAET() { return m_pScnAet; }
    inline STR_PDWPARAM* GetPdwParam() { return m_thePulExt->GetPdwParam(); }

    inline int GetCoGroup() { return 0; }

#if defined(_ELINT_) || defined(_XBAND_)
	inline EN_RADARCOLLECTORID GetCollectorID() { return CSigAnal::GetCollectorID(); }
	// inline unsigned char *GetTaskID() { return & m_pPDWData->x.el.aucTaskID[0]; }
#endif

    void Start( STR_PDWDATA *pPDWData, STR_MANAET *pManAet );
    void Start( STR_PDWDATA *pPDWData, STR_UPDAET *pUpdAet );
    void Start( STR_STATIC_PDWDATA *pPDWData, SRxABTData *pScnAet );
    // void Start( STR_PDWDATA *pPDWData, STR_EMITTER *pEmitter, STR_PULSE_TRAIN_SEG *pSeg, STR_UPDAET *pUpdAet );
    void SendScanResult( UINT nResult );
    STR_SCANPT *GetScanPulseTrain( int noCh );
    void GetScanRes( unsigned int *pScanType, float *pScanPrd );
    UINT GetCoScanPulse();

    void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile );
    void MarkToPdwIndex(PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType);
    void ClearColBuffer();
    UINT AnalStart( int noEMT, int noCh );

    void Init( STR_STATIC_PDWDATA *pstPDWData);
    void ScanExtractPulseInit( unsigned int uinoEMT=0, unsigned int uinoCh=0 );
    void ScanSigAnalInit( unsigned int uinoEMT=0, int noCh=0 );

};

#endif

