// ScanSigAnal.h: interface for the CScanSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANSIGANAL_H__A2FFC458_5A2A_41E8_8D9D_C80FD0441511__INCLUDED_)
#define AFX_SCANSIGANAL_H__A2FFC458_5A2A_41E8_8D9D_C80FD0441511__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SDefine.h"
#include "SStruct.h"

#include "../../Utils/ccommonutils.h"

#include "../SigAnal/SigAnal.h"
#include "SGroup.h"
#include "SPulExt.h"
#include "SAnalSCN.h"

#ifdef __cplusplus

//##ModelId=452B0C450011
class CScanSigAnal : public CSigAnal
{
private:
    SRxABTData *m_pScnAet;

private:
    

public:
    //##ModelId=452B0C450027
    STR_PDWINDEX *m_pGrPdwIndex;

    DEFINE_ANAL_VAR_
	
protected:
    STR_UPDAET *m_pUpdAet;
    //##ModelId=452B0C45002C
    STR_PULSE_TRAIN_SEG *m_pSeg;
    //##ModelId=452B0C450031
    STR_STATIC_PDWDATA *m_pstPDWData;
    //##ModelId=452B0C450035
    int m_noCh;
    //##ModelId=452B0C45003A
    unsigned int m_uiCoPdw;
    //##ModelId=452B0C45003B
    int m_noEMT;
    //##ModelId=452B0C450045
    CSGroup *m_theGroup;
    //##ModelId=452B0C45004A
    CSPulExt *m_thePulExt;
    //##ModelId=452B0C450052
    CSAnalScan *m_theAnalScan;
    //##ModelId=452B0C450058
    int m_nMaxPdw;

    SRxScanData m_strScnResult;


public:
    CScanSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName = NULL);
    virtual ~CScanSigAnal();
    
    inline void GetCollectTime(struct timespec *pTimeSpec) {
        CCommonUtils::GetCollectTime(pTimeSpec, GetColTime(), GetColTimeMs());
    }

    void SaveEmitterPdwFile( STR_PDWINDEX *pPdw, int iPLOBID );
    void InitVar();
    //BOOL IsAnalScan();
    void SaveScanInfo( UINT nResult, STR_UPDAET *pUpdAet, BOOL bOnlyThreat=FALSE );

    //##ModelId=452B0C450059
    inline int GetMaxPdw() { return m_nMaxPdw; }
    //##ModelId=452B0C45005A
    inline STR_STATIC_PDWDATA *GetPDWData() { return m_pstPDWData; }
    //##ModelId=452B0C450062
    inline int GetNoEMT() { return m_noEMT; }
    //##ModelId=452B0C450063
    inline UINT GetScanNoCh() {	return m_noCh; }
    //##ModelId=452B0C450064
    inline int GetColPdw() { return m_uiCoPdw; }
    //##ModelId=452B0C450065
    inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }
    //##ModelId=452B0C45006D
    inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return m_theGroup->GetFrqAoaGroupedPdwIndex(); }
    //##ModelId=452B0C45006E
    inline UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, uiCount ); }
    //##ModelId=452B0C450078
    inline unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, UINT framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( pPdwIndex, framePri, pEmitter ); }
    //##ModelId=452B0C450082
    inline BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
    //##ModelId=452B0C450095
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
    //##ModelId=452B0C450096
    inline int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->CalcPAMean( pPdwIndex, uiCount); }
    //##ModelId=452B0C45009F
    inline int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount) { return m_thePulExt->VerifyPW( pPdwIndex, uiCount); }
    //##ModelId=452B0C4500A8
    inline _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount ) { return m_thePulExt->VerifyPRI( pPdwIndex, uiCount ); }
    //inline STR_UPDAET *GetUpdAet() { return & stScnAet; }
    inline SRxScanData *GetScanResult() { return & m_strScnResult; }
    inline SRxLOBData *GetLOBData(int index=0) { return m_theAnalScan->GetLOBData(index); }

    inline int GetBand() { return m_theGroup->GetBand(); }
    inline int GetCoPdw() { return m_uiCoPdw; }
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
    //##ModelId=452B0C4500AB
    void SendScanResult( UINT nResult );
    //##ModelId=452B0C4500B3
    STR_SCANPT *GetScanPulseTrain( int noCh );
    //##ModelId=452B0C4500B5
    void GetScanRes( unsigned int *pScanType, float *pScanPrd );
    //##ModelId=452B0C4500BD
    UINT GetCoScanPulse();

    //##ModelId=452B0C4500C6
    void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile );
    //##ModelId=452B0C4500C9
    void MarkToPdwIndex(PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType);
    //##ModelId=452B0C4500D2
    void ClearColBuffer();
    //##ModelId=452B0C4500D3
    UINT AnalStart( int noEMT, int noCh );

    //##ModelId=452B0C4500E5
    void Init( STR_STATIC_PDWDATA *pstPDWData);
    //##ModelId=452B0C4500E6
    void ScanExtractPulseInit( int noEMT=0, int noCh=0 );
    //##ModelId=452B0C4500EF
    void ScanSigAnalInit( int noEMT=0, int noCh=0 );

};

#endif

/*

extern "C" {
	void CreateScanSigAnalClass();
	void DeleteScanSigAnalClass();
	
	//int ScanSigAnal( int noEMT, int noCh );

	UINT ExtPul( int noEMT, UINT noCh );
	void InitScanSigAnal();
	void InitSAPColPdw();
	STR_SCANPT *GetScanPulseTrain( int noCh );
	void GetScanRes( int *pScanType, int *pScanPrd );
	
	extern CScanSigAnal *theScanSigAnal;
	extern CSColPdw *theSAPColPdw;

}

	*/

#endif // !defined(AFX_SCANSIGANAL_H__A2FFC458_5A2A_41E8_8D9D_C80FD0441511__INCLUDED_)
