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

    STR_PDWPARAM *m_pPdwParam;

    //##ModelId=452B0C5503CF
    STR_EMITTER *m_pEmitter;

    //##ModelId=452B0C5503A6
    int m_nMaxPdw;
    //##ModelId=452B0C5503AE
    int m_nCoPdw;
    //##ModelId=452B0C5503AF
    UINT m_uiCoAnalPdw;
    //##ModelId=452B0C5503C3
    STR_PULSE_TRAIN_SEG *m_pSeg;

private:
    

public:
    void ConvertRealFreq( STR_FRQ *pFrq );
    int CalMaxChannel( STR_PDWINDEX *pPdw );

    void PrintAllEmitter();

    //##ModelId=452B0C560002
    inline int GetCoAnalPdw() { return m_uiCoAnalPdw; }
    inline void SetCoAnalPdw(UINT coAnalPdw ) { m_uiCoAnalPdw=coAnalPdw; }
    //##ModelId=452B0C560003
    inline int GetCoLOB() { return m_iCoLOB; }
    inline void SetCoLOB( UINT coLOB ) { m_iCoLOB = coLOB; }

    //##ModelId=452B0C56003A
    UINT CalcAoaMean_GSKIMF_200505_6( STR_EMITTER *pEmitter );
    //##ModelId=452B0C56003F
    void MarkToEmitterPdwIndex( STR_EMITTER *pEmitter, int type ) { MarkToPdwIndex( pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount, type ); }
    //##ModelId=452B0C560042
    void MakeExtInfoFromSeg( STR_EXT *pExt, STR_EMITTER *pEmitter );
    //##ModelId=452B0C56004A
    void MakeAOAInfoFromSeg(STR_MINMAX_SDEV *pAoa, STR_EMITTER *pEmitter);
    //##ModelId=452B0C560052
    void MakePAInfoFromSeg(STR_MINMAX *pPa, STR_EMITTER *pEmitter);
    //##ModelId=452B0C560055
    void MakePWInfoFromSeg(STR_MINMAX *pPw, STR_EMITTER *pEmitter);


    void MakeDefaultPRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter );
    void MakeStaggerPRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter );
    void MakeDwellPRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter );
    void MakeJitterPRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter );
    void MakeStablePRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter );

    void MakeStaggerPRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter);
    void MakeDwellPRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter);
    void MakeJitterPRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter);
    void MakeStablePRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter);

    //##ModelId=452B0C56005D
    void MakePRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter );
    void MakePRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter);
    //##ModelId=452B0C560060
    void MakeFrqInfoFromSeg( STR_FRQ *pFrq, STR_EMITTER *pEmitter );
    int MakeDIInfoFromSeg( STR_EMITTER *pEmitter);
    void MakeLOBDataFromEmitter(int iLOBData, STR_EMITTER *pEmitter, int idxEmitter);

    //##ModelId=452B0C560071
    void MakeAET();
    //##ModelId=452B0C560072
    void Init(void);
    //##ModelId=452B0C560074
    CMakeAET( int coMaxPdw );
    //##ModelId=452B0C56007B
    virtual ~CMakeAET();

public:
    //##ModelId=452B0C560004
    virtual int CalcAoaMeanByHistAoa(STR_PDWINDEX *pSrcIndex) = 0;
    //##ModelId=452B0C56000C
    virtual int GetColPdw() = 0;
    //##ModelId=452B0C56000E
    virtual int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount) = 0;
    //##ModelId=452B0C560012
    virtual int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount) = 0;
    //##ModelId=452B0C560019
    virtual void MarkToPdwIndex(PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType) = 0;
    //##ModelId=452B0C560021
    virtual void SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index, bool bSaveFile) = 0;
    //##ModelId=452B0C56002A
    virtual unsigned int GetCoSeg() = 0;
    //##ModelId=452B0C56002C
    virtual int GetCoEmitter() = 0;
    //##ModelId=452B0C56002E
    virtual STR_PULSE_TRAIN_SEG *GetPulseSeg() = 0;
    //##ModelId=452B0C560034
    virtual STR_EMITTER *GetEmitter() = 0;
    //##ModelId=452B0C560036
    virtual UINT CalcFreqMedian(STR_PULSE_TRAIN_SEG *pSeg) = 0;
    virtual STR_PDWPARAM* GetPdwParam() = 0;

    virtual void GetCollectTime(struct timespec *pTimeSpec) = 0;

    virtual void SetKnownIndexEmitter(unsigned int uiIndex, int iIdxEmitter) = 0;

    virtual unsigned int GetOpInitID()=0;
	virtual unsigned int GetPDWID() = 0;
    virtual unsigned int IsStorePDW()=0;
    virtual void DISP_FineAet( SRxLOBData *pLOBData )=0;
    virtual SRxLOBData *GetLOBData( int index=0 )=0;

#if defined(_ELINT_) || defined(_XBAND_)
    virtual EN_RADARCOLLECTORID GetCollectorID()=0;
    virtual char *GetTaskID()=0;
#endif

};

#endif

#endif // !defined(AFX_MAKEAET_H__D3ED692F_6704_4688_B28C_7FEB2AEACEB9__INCLUDED_)
