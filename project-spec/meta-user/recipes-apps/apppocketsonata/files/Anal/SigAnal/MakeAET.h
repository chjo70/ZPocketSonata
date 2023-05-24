/**

    @file      MakeAET.h
    @brief     interface for the CMakeAET class.
    @details   ~
    @author    조철희
    @date      2.05.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

//////////////////////////////////////////////////////////////////////////
// 타 장비의 위협 구조체를 정의한다.
#include "../EmitterMerge/ELMsgDefn.h"

#include "../../Utils/clog.h"
#include "../../Utils/ccommonutils.h"

#ifdef __cplusplus

/**

    @class   CMakeAET
    @brief   시본 에미터 생성 관련 클래스 입니다.
    @details ~

**/
class CMakeAET
{
private:
    SRxLOBData *m_pLOBData;

public:
    int m_iCoEmitter;
    int m_iCoLOB;

protected:
    DEFINE_ANAL_PVAR_

    _TOA m_tStableMargin;

	UINT m_uiCoMaxLOB;
	UINT m_uiCoPdw;
	UINT m_uiCoAnalPdw;

    STR_PDWPARAM *m_pPdwParam;

    STR_EMITTER *m_pEmitter;
	STR_PULSE_TRAIN_SEG *m_pSeg;

private:
    int SortLevel( int iSwtLev, _TOA *pSwtLev );

public:
    CMakeAET( unsigned int uiCoMaxLOB );
    virtual ~CMakeAET();

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
    void PrintAllAET();
	void MakeFreqLOBDataFromEmitter(SRxLOBData *pLOBData, STR_EMITTER *pEmitter);
	void MakePRILOBDataFromEmitter(SRxLOBData *pLOBData, STR_EMITTER *pEmitter);

    void MakeAET( bool bDBInsert );

    void Init(void);

    inline SRxLOBData *GetLOBData( int index = 0 ) { return & m_pLOBData[index]; }

protected:


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
    //virtual SRxLOBData *GetLOBData( int index=0 )=0;

#if defined(_ELINT_) || defined(_XBAND_)
    virtual EN_RADARCOLLECTORID GetCollectorID()=0;
    virtual char *GetTaskID()=0;
#endif


};

#endif

