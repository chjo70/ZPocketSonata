// PulExt.h: interface for the CPulExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PULEXT_H__5C6D2A7D_E233_4E77_ACD5_48D971456B7C__INCLUDED_)
#define AFX_PULEXT_H__5C6D2A7D_E233_4E77_ACD5_48D971456B7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_SigAnal.h"

#ifdef __cplusplus

#include <typeinfo>

using namespace std;

#include "../../Utils/MulDiv64.h"


/**	\brief	클래스명 CPulExt;
                        주파수,방위,펄스폭 그룹화 단계를 거친 후에 입력된 신호를 근거로 펄스열 추출을 한다.
                        펄스열 추출은 크게 기본 규칙성 펄스열단계에서 STABLE PRI를 먼저 찾는다. 이 과정에서
                        STABLE 마킹 작업은 하지 않고 찾는다. 그리고 각 구간별로 규칙성과 불규칙성 펄스열을
                        찾는다. 각 구간에서 찾은 펄스열들은 마킹을 해서 N-배의 PRI를 찾지 않게 한다.

                        다음은 펄스열 추출 알고리즘의 몇가지 기능을 나타낸다.
                        1) 펄스열 추출 시간을 단축하기 위해서 DTOA 히스토그램을 이용해서 펄스열 구간을 알아낸다.
                        2) 마킹하지 않은 기본 펄스열 단계를 추가해서 펄스열을 추출하게 한다.
                        3) 펄스열 추출시에 기본 펄스들의 주파수 정보를 이용해서 펗스열을 추출하게 한다. 그래서
                             만족하지 않지만 어느 정도의 펄스열 분리를 하게 했다.
*/
//##ModelId=452B0C5302F7
class CPulExt
{
protected:
    DEFINE_ANAL_PVAR_

public:
    unsigned int m_uiAnalSeg;

    //! 펄스열 총 개수
    unsigned int m_uiCoSeg;
    unsigned int m_uiCoRefSeg;

    unsigned int m_uiEnd_pri_level;
    unsigned int m_uiStart_pri_level;


private:
    unsigned int m_uiCoPDW;
    unsigned char *m_pRemovePdwIndex;

    STR_PDWINDEX *m_pGrPdwIndex;

    int m_nToaShift;

    unsigned int m_uiRefStartSeg;
    unsigned int m_uiRefEndSeg;
    //! 최대 PDW 개수
    unsigned int m_uiMaxPdw;
    unsigned int m_uiMaxSeg;

    //##ModelId=452B0C53035C
    STR_PDWPARAM m_PdwParam;
    //! 기본 펄스열을 임시 저정하기 위한 저장소.
    //##ModelId=452B0C530366
    STR_PULSE_TRAIN_SEG m_RefSeg;

    //! 펄스열 저장소.
    //##ModelId=452B0C53036B
    STR_PULSE_TRAIN_SEG m_Seg[MAX_SEG];
    //! 규칙성 펄스열 및 불규칙성 펄스열 추출하기 위한 펄스열 밴드 테이블.
    //##ModelId=452B0C530370
    STR_PRI_RANGE_TABLE m_jit_pri_table[MAX_PRI_RANGE];
    //##ModelId=452B0C53037A
    //STR_PRI_RANGE_TABLE m_PRIBand[3];

public:
    void RemoveStablePulseTrain();
    //##ModelId=452B0C530383
    inline STR_PDWPARAM* GetPdwParam() { return & m_PdwParam; }
    //##ModelId=452B0C530384
    inline void SetRefEndSeg() { m_uiRefEndSeg = m_uiCoSeg; }
    //##ModelId=452B0C530385
    inline void CleanPulseTrains() { CleanPulseTrains( m_uiRefStartSeg, m_uiCoSeg ); }
    //##ModelId=452B0C530397
    inline STR_PULSE_TRAIN_SEG *GetPulseSeg() { return m_Seg; }
    //##ModelId=452B0C530398
    inline void GetStartEndPriLevel() { GetStartEndPriLevel( & m_uiStart_pri_level, & m_uiEnd_pri_level ); }
    //##ModelId=452B0C530399
    inline void SetRefStartSeg() { m_uiRefStartSeg = m_uiCoSeg; }
    //##ModelId=452B0C5303A1
    inline void SetGrPdwIndex( STR_PDWINDEX *pPdwIndex ) { m_pGrPdwIndex = pPdwIndex; }

    //!	PRI 클래스에서 정의된 DTOAHIST 멤버 변수를 리턴
    //##ModelId=452B0C5303A3
    virtual STR_DTOA_HISTOGRAM *GetDtoaHist()=0;
    //! DTOA 히스토그램을 작성한다.
    //##ModelId=452B0C5303B6
    virtual void MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange )=0;
    //! DTOA 히스트그램 상에서 추출할 PRI 밴드를 구한다.
    
    virtual void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count )=0;

    virtual STR_PDWINDEX *GetFrqAoaGroupedPdwIndex()=0;
    virtual unsigned int GetCoPdw()=0;
    //virtual void ClearAllMark(bool bClear)=0;

    void MakeCWPulseTrain();
    void ResetJitterSeg();
    BOOL MustDo2ndPulseExtract();
    void MarkStablePulseTrain();
    void CalcEmitterPW( STR_PULSE_TRAIN_SEG *pSeg );
    //int CnvPW( int val );
    void SavePdwParamIndex();
    void ExtractTrackPT( _TOA refPriMean, float refJitRat );
    void DiscardPulseTrain();
    void PrintAllSeg();
    void PrintSeg( int iSeg, STR_PULSE_TRAIN_SEG *pSeg );
    void PrintAllSegPDW( STR_PULSE_TRAIN_SEG *pSeg );
    void ChangeMarkTo( unsigned int uiStartSeg, unsigned int uiEndSeg, SEG_MARK enFromMark, SEG_MARK enTomark);
    void MergePulseTrain( STR_PULSE_TRAIN_SEG *pMrgSeg, STR_PULSE_TRAIN_SEG *pSrcSeg );
    STR_PULSE_TRAIN_SEG *GetMainSeg( unsigned int uiStartSeg, unsigned int uiEndSeg );
    //! 추출하고자할 펄스열의 주파수 범위에 맞는 PDW 인가를 체크한다.
    
    BOOL IsValidPDW( int index, STR_PULSE_TRAIN_SEG *pSeg );
    //! 펄스열을 근거로 주파수 형태 및 주파수 범위를 계산한다.
    
    void CalcEmitterFrq( STR_PULSE_TRAIN_SEG *pSeg );
    void GetStartEndPriLevel( unsigned int *pStart_pri_level, unsigned int *pEnd_pri_level );
    void MergeJitterPulseTrain(unsigned int uiStartSeg, unsigned int uiEndSeg, BOOL bIgnoreJitterP=FALSE );
    void CalPRILevel( STR_LOWHIGH *pPRILevel, STR_DTOA_HISTOGRAM *pDtoaHist );

    void DiscardPulseTrain( unsigned int startseg1, unsigned int endseg, unsigned int startseg2 );
    void MemcpySeg( STR_PULSE_TRAIN_SEG *pDestSeg, STR_PULSE_TRAIN_SEG *pSrcDeg );
    void CleanPulseTrains(unsigned int uiStartSeg, unsigned int uiEndSeg );
    void MarkSegForExt( int nStartSeg, int nEndSeg );
    
    void CompStablesJitters( unsigned int nStartStableSeg, unsigned int nStartJitterSeg );
    bool IsSamePulseTrain( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    
    //unsigned int GetCoExtPulse();
    
    BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    bool CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    bool CheckOmittedPulse( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    
    void DeleteAllSeg( STR_EMITTER *pEmitter );
    BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange );
    void CopyOnePulseTrain( STR_PULSE_TRAIN_SEG *pDstSeg, STR_PULSE_TRAIN_SEG *pSrcSeg );
    void CopyPulseTrains( STR_PULSE_TRAIN_SEG *pDstSeg, STR_PULSE_TRAIN_SEG *pSrcSeg, int coSeg );
    void PulseExtract();
    void ExtractJitter( int type );
    void FindRefStableSeg( STR_PRI_RANGE_TABLE *pExtRange, int nPriBand=-1 );

    _TOA CheckHarmonic( _TOA mean1, float jitter_p1, _TOA mean2, float jitter_p2 );
    
    void ExtractStablePT(STR_PRI_RANGE_TABLE *pExtRange, int nPriBand, BOOL flagMargin=FALSE, PULSE_MARK enMark=enSTABLE_MARK, SEG_MARK enSegMark=NORMAL_SEG );
    void ExtractJitterPT( STR_PRI_RANGE_TABLE *pExtRange, unsigned int uiPriBand, unsigned int coRef=_sp.cm.Rpc, BOOL bFlagMargin=FALSE , PULSE_MARK enMark =enJITTER_MARK, BOOL bIgnoreJitterP=FALSE, SEG_MARK enSegMark = NORMAL_SEG);
    void ExtractPatternPT( STR_PRI_RANGE_TABLE *pExtRange, unsigned int uiCoRef=_sp.cm.Rpc, BOOL flagMargin=FALSE );
    
    inline void MarkToPDWIndex( STR_PULSE_TRAIN_SEG *pSeg, PULSE_MARK enPULSE_MARK, SEG_MARK enSEG_MARK=NORMAL_SEG) {
        pSeg->enSegMark = enSEG_MARK;
        MarkToPDWIndex( pSeg->stPDW.pIndex, pSeg->stPDW.uiCount, (USHORT)enPULSE_MARK );
    }

    void MarkToPDWIndex( PDWINDEX *pPDWIndex, UINT uiCount, USHORT usMarkType );
    
    UINT AnalFreqType(STR_PULSE_TRAIN_SEG *pSeg);
    UINT CheckStaggerLevel( _TOA framePri, STR_EMITTER *pEmitter );
    _TOA CheckHarmonic(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2);
    
    unsigned int ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter );
    
    UINT ExtractFramePri( STR_PDWINDEX *pSrcPdwIndex, _TOA framePri);
    UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );
    void AllExtSegMark();
    int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount);
    
    unsigned int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount);
    
    void CleanRefSeg();
    
    enPRI_TYPE AnalPRIType( STR_PULSE_TRAIN_SEG *pSeg, enPRI_TYPE ext_type=_UNKNOWN_PRI );
    
    void ExtractSimpleStablePT(STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex );
    
    bool FindStableSeg(STR_PULSE_TRAIN_SEG *pRefSeg, UINT uiStart, UINT uiEnd);
    void ExtractRefStable();
    void FindRefStable();
    
    //_TOA RecalcDtoaMargin( int ext_type, STR_PULSE_TRAIN_SEG *pSeg, UINT dtoa );
    bool OverlappedSeg(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2);
    void DiscardStablePulseTrain();
    _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount );
    void VerifyPRI( STR_PULSE_TRAIN_SEG *pSeg );
    UINT CalMaxMiss( int type );
    _TOA CalDtoaMargin( int type, STR_PULSE_TRAIN_SEG *pSeg );
    void UnknownExtract();
    void ExtractJitterPT();
    BOOL CalcSegParam( STR_PULSE_TRAIN_SEG *pSeg, BOOL bIgnoreJitterP=FALSE );
    void ExtractForPT(STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex, _TOA margin=0 );
    
    float CalcRefPRI( PDWINDEX *pPdwIndex, UINT uiCount, STR_MINMAX_TOA *pPRI );
    
    void ChooseTOAMargin(STR_LOWHIGH_TOA *pStrMargin, STR_PRI_RANGE_TABLE *pPriRange, _TOA tDtoa, int ext_type, BOOL bFlagMargin);
    void ExtractBackPT( STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex, BOOL bFlagMargin=FALSE );
    bool ExtractRefPT( STR_PRI_RANGE_TABLE *pPriRange, int ext_type, STR_PULSE_TRAIN_SEG *pSeg, int start_idx, STR_PDWINDEX *pColPdwIndex, unsigned int uiCoRefPulse=_sp.cm.Rpc, BOOL flagMargin=FALSE, BOOL bIgnoreJitterP=FALSE );
    void ExtractStablePT();
    
    void Init();

    CPulExt( unsigned int uiCoMaxPdw );
    virtual ~CPulExt();

};

#endif

#endif // !defined(AFX_PULEXT_H__5C6D2A7D_E233_4E77_ACD5_48D971456B7C__INCLUDED_)

