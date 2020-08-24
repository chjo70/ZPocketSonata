// KnownSigAnal.h: interface for the CKnownSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KNOWNSIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_)
#define AFX_KNOWNSIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KColPdw.h"

#include "KVar.h"

#include "KGroup.h"
#include "KPulExt.h"
#include "KAnalPRI.h"
#include "KMakeAET.h"

//##ModelId=452B0C520241
class CKnownSigAnal
{
public:
	//##ModelId=452B0C52024B
	int m_CoNewAet;
	//##ModelId=452B0C52024C
	int m_CoUpdAet;
	//##ModelId=452B0C520256
	STR_PDWINDEX *m_pGrPdwIndex;

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
	int m_CoPdw;
	//##ModelId=452B0C520288
	int m_noSbc;
	//##ModelId=452B0C520291
	int m_noCh;
	//##ModelId=452B0C52029C
	STR_PDWBANK *m_pPdwBank;

public:
	//##ModelId=452B0C5202A5
	inline int GetMaxPdw() { return m_nMaxPdw; }
	//##ModelId=452B0C5202A6
	inline STR_PDWBANK *GetPdwBank() { return m_pPdwBank; }
	//##ModelId=452B0C5202A7
	inline int GetColPdw() { return m_CoPdw; }

	//##ModelId=452B0C5202A8
	inline void MakePDWArray( TNEW_PDW *pdw, int count ) { m_theGroup->MakePDWArray( pdw, count ); }
	//##ModelId=452B0C5202B1
	inline STR_PDWINDEX *GetFrqAoaGroupedPdwIndex() { return m_theGroup->GetFrqAoaGroupedPdwIndex(); }
	//##ModelId=452B0C5202B9
	inline int CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex ) { return m_theGroup->CalcAoaMeanByHistAoa( pSrcIndex ); }
	//##ModelId=452B0C5202BB
	inline int FindPeakInHist( int count, PDWINDEX *pPdwIndex ) { return m_theGroup->FindPeakInHist( count, pPdwIndex ); }
	
	//##ModelId=452B0C5202CE
	inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_thePulExt->GetPulseSeg(); }
	//##ModelId=452B0C5202CF
	inline int CalcPAMean(PDWINDEX *pPdwIndex, int count) { return m_thePulExt->CalcPAMean( pPdwIndex, count); }
	//##ModelId=452B0C5202D8
	inline int VerifyPW(PDWINDEX *pPdwIndex, int count) { return m_thePulExt->VerifyPW( pPdwIndex, count); }
	//##ModelId=452B0C5202E1
	inline int GetCoSeg() { return m_thePulExt->m_CoSeg; }
	//##ModelId=452B0C5202E2
	inline int GetAnalSeg() { return m_thePulExt->m_nAnalSeg; }
	//##ModelId=452B0C5202E3
	inline UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, int count ) { return m_thePulExt->MedianFreq( pMinMax, pPdwIndex, count ); }
	//##ModelId=43D4818F0298
	//inline void SetAnalSeg( int co ) { m_thePulExt->SetAnalSeg( co ); }
	//##ModelId=452B0C5202F8
	inline UINT CheckHarmonic(UINT priMean1, UINT priMean2) { return m_thePulExt->CheckHarmonic( priMean1, priMean2); }
	//##ModelId=452B0C520301
	inline BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) { return m_thePulExt->CheckPriInterval( pSeg1, pSeg2 ); }
	//##ModelId=452B0C52030A
	inline int ExtractStagger(STR_PDWINDEX *pPdwIndex, UINT framePri, STR_EMITTER *pEmitter ) { return m_thePulExt->ExtractStagger( pPdwIndex, framePri, pEmitter ); }
	//##ModelId=452B0C520314
	inline int VerifyPRI( PDWINDEX *pPdwIndex, int count ) { return m_thePulExt->VerifyPRI( pPdwIndex, count ); }
	
	//##ModelId=452B0C52031E
	inline STR_DTOA_HISTOGRAM *GetDtoaHist() { return m_theAnalPRI->GetDtoaHist(); }
	//##ModelId=452B0C52031F
	inline void MakeDtoaHistogram( PDWINDEX *pPdwIndex, int count, STR_MINMAX *pRange ) { m_theAnalPRI->MakeDtoaHistogram( pPdwIndex, count, pRange ); }
	//##ModelId=452B0C520329
	inline void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, UINT priMean, UINT dtoa_count ) { m_theAnalPRI->CalPRIRange( pSeg, priMean, dtoa_count ); }
	//##ModelId=452B0C52033D
	inline void DeleteAllSeg( STR_EMITTER *pEmitter ) { m_theAnalPRI->DeleteAllSeg( pEmitter ); }
	//##ModelId=452B0C520346
	inline void ExtractRefStable() { m_theAnalPRI->ExtractRefStable(); }
	//##ModelId=452B0C52034F
	inline void ExtractDwellRefPT( STR_PRI_RANGE_TABLE *pExtRange ) { m_theAnalPRI->ExtractDwellRefPT( pExtRange ); }
	//##ModelId=452B0C520351
	inline UINT ExtractFramePri(STR_PDWINDEX *pPdwIndex, UINT framePri) { return m_theAnalPRI->ExtractFramePri( pPdwIndex, framePri ); }	
	//##ModelId=452B0C52035A
	inline STR_EMITTER *GetEmitter() { return m_theAnalPRI->GetEmitter(); }
	//##ModelId=452B0C52035B
	inline int GetCoEmitter() { return m_theAnalPRI->GetCoEmitter(); }
	inline void CalDtoaMeanMinMax( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange ) { m_theAnalPRI->CalDtoaMeanMinMax( pSeg, pRange ); }
	
	//##ModelId=452B0C52035C
	inline int GetCoNewAet() { return m_theMakeAET->GetCoNewAet(); }
	//##ModelId=452B0C520363
	inline STR_NEWAET *GetNewAet() { return m_theMakeAET->GetNewAet(); }
	//##ModelId=452B0C520364
	inline void ClearCoAet() { m_theMakeAET->ClearCoAet(); }
	//##ModelId=452B0C520365
	inline void MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) { m_theMakeAET->MakePRIInfoInSeg( pPri, pEmitter ); }

	//##ModelId=452B0C52036E
	void ClearColBuffer();
	//##ModelId=452B0C52036F
	void SendAllAet();
	//##ModelId=452B0C520370
	void SendUpdAet( STR_UPDAET *pUpdAet );
	//##ModelId=452B0C520378
	void SendLostAet();
	//##ModelId=452B0C520379
	void SendNewAet( STR_NEWAET *pNewAet, int inEMT );
	//##ModelId=452B0C520382
	void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index );
	//##ModelId=452B0C52038B
	void MarkToPdwIndex(PDWINDEX *pPdwIndex, int count, int mark_type);
	//##ModelId=452B0C520395
	void SaveAllPdwFile();
	//##ModelId=452B0C520396
	void Init( int noSbc=0, int noCh=0 );
	//##ModelId=452B0C52039F
	void AnalStart( int noSbc, int noCh );
	//##ModelId=452B0C5203B4
	CKnownSigAnal( int coMaxPdw );
	//##ModelId=452B0C5203BE
	virtual ~CKnownSigAnal();

};

extern "C" {
	void CreateKnownSigAnalClass();
	void DeleteKnownSigAnalClass();

	int KnownSigAnal( int noSbc, int noCh );
	void SendKSPNewAet( STR_NEWAET *pAet, UINT inEMT );
	void SendKSPUpdAet( STR_UPDAET *pUpdAet );
	void SendKSPLostAet( STR_TRKAET *pAet, int stat );
	
	extern CKnownSigAnal *theKnownSigAnal;
	extern CKColPdw *theKSPColPdw;

}


#endif // !defined(AFX_KNOWNSIGANAL_H__30606F89_0BF4_4C89_B5CD_4E9700CBE5E4__INCLUDED_)
