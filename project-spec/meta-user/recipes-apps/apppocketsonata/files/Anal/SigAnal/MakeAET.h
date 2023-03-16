// MakeAET.h: interface for the CMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKEAET_H__D3ED692F_6704_4688_B28C_7FEB2AEACEB9__INCLUDED_)
#define AFX_MAKEAET_H__D3ED692F_6704_4688_B28C_7FEB2AEACEB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

//////////////////////////////////////////////////////////////////////////
// 타 장비의 위협 구조체를 정의한다.
#include "../EmitterMerge/ELMsgDefn.h"

#ifdef __cplusplus

//##ModelId=452B0C550390
class CMakeAET
{
private:


public:
    //##ModelId=452B0C55039B
    int m_iCoEmitter;
    //##ModelId=452B0C5503A4
    int m_iCoLOB;

protected:
    DEFINE_ANAL_PVAR_

	UINT m_uiMaxPdw;
	UINT m_uiCoPdw;
	UINT m_uiCoAnalPdw;

    STR_PDWPARAM *m_pPdwParam;
    
    STR_EMITTER *m_pEmitter;
	STR_PULSE_TRAIN_SEG *m_pSeg;
	    
private:
    

public:
    int CalMaxChannel( STR_PDWINDEX *pPdw );
    void PrintAllEmitter();

    inline int GetCoAnalPdw() { return (int) m_uiCoAnalPdw; }
    inline void SetCoAnalPdw(UINT coAnalPdw ) { m_uiCoAnalPdw=coAnalPdw; }
    inline int GetCoLOB() { return m_iCoLOB; }
    inline void SetCoLOB( UINT coLOB ) { m_iCoLOB = (int) coLOB; }

    UINT CalcAoaMean_GSKIMF_200505_6( STR_EMITTER *pEmitter );
    void MakeExtInfoFromSeg( STR_EXT *pExt, STR_EMITTER *pEmitter );
    void MakeAOAInfoFromSeg(STR_MINMAX_SDEV *pAoa, STR_EMITTER *pEmitter);
    void MakePAInfoFromSeg(STR_MINMAX *pPa, STR_EMITTER *pEmitter);
    void MakePWInfoFromSeg(STR_MINMAX *pPw, STR_EMITTER *pEmitter);

    void MakeDefaultPRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter );
    void MakeStaggerPRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter );
    void MakeDwellPRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter );
    void MakeJitterPRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter );
    void MakeStablePRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter );

    void MakeStaggerPRIInfoFromSeg(STR_PRI *pPRI, STR_EMITTER *pEmitter);
    void MakeDwellPRIInfoFromSeg(STR_PRI *pPRI, STR_EMITTER *pEmitter);
    void MakeJitterPRIInfoFromSeg(STR_PRI *pPRI, STR_EMITTER *pEmitter);
    void MakeStablePRIInfoFromSeg(STR_PRI *pPRI, STR_EMITTER *pEmitter);

    
    void MakePRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter );
    void MakePRIInfoFromSeg(STR_PRI *pPRI, STR_EMITTER *pEmitter);
    
    void MakeFrqInfoFromSeg( STR_FRQ *pFrq, STR_EMITTER *pEmitter );
    unsigned int MakeDIInfoFromSeg( STR_EMITTER *pEmitter);
    void MakeLOBDataFromEmitter(int iLOBData, STR_EMITTER *pEmitter, int idxEmitter);
	void MakeFreqLOBDataFromEmitter(SRxLOBData *pLOBData, STR_EMITTER *pEmitter);
	void MakePRILOBDataFromEmitter(SRxLOBData *pLOBData, STR_EMITTER *pEmitter);

    
    void MakeAET();
    
    void Init(void);
    
    CMakeAET( unsigned int uiCoMaxPdw );
    
    virtual ~CMakeAET();

public:
    virtual int CalcAoaMeanByHistAoa(STR_PDWINDEX *pSrcIndex) = 0;
    virtual unsigned int GetColPdw() = 0;
    virtual int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount) = 0;
    virtual int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount) = 0;
    //virtual void MarkToPdwIndex(PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType) = 0;
    virtual void SaveEmitterPDWFile(STR_EMITTER *pEmitter, int index, bool bSaveFile) = 0;
    virtual unsigned int GetCoSeg() = 0;
    virtual unsigned int GetCoEmitter() = 0;
    virtual STR_PULSE_TRAIN_SEG *GetPulseSeg() = 0;
    virtual STR_EMITTER *GetEmitter() = 0;
    virtual UINT CalcFreqMedian(STR_PULSE_TRAIN_SEG *pSeg) = 0;
    virtual STR_PDWPARAM* GetPdwParam() = 0;
    virtual void GetCollectTime(struct timespec *pTimeSpec) = 0;
    virtual void SetKnownIndexEmitter(unsigned int uiIndex, int iIdxEmitter) = 0;
    virtual unsigned int GetOpInitID()=0;
	virtual unsigned int GetPDWID() = 0;
    virtual unsigned int IsStorePDW()=0;
    virtual void DISP_FineLOB( SRxLOBData *pLOBData )=0;
    virtual SRxLOBData *GetLOBData( int index=0 )=0;

#if defined(_ELINT_) || defined(_XBAND_)
    virtual EN_RADARCOLLECTORID GetCollectorID()=0;
    virtual char *GetTaskID()=0;
#endif

};

#endif

#endif // !defined(AFX_MAKEAET_H__D3ED692F_6704_4688_B28C_7FEB2AEACEB9__INCLUDED_)
