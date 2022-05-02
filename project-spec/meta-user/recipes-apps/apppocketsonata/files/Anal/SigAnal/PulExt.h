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
    //##ModelId=452B0C530301
    unsigned int m_uiAnalSeg;
    //! 펄스열 총 개수
    //##ModelId=452B0C53030B
    unsigned int m_uiCoSeg;
    unsigned int m_uiCoRefSeg;

    //##ModelId=452B0C53030C
    unsigned int m_uiEnd_pri_level;
    //##ModelId=452B0C530315
    unsigned int m_uiStart_pri_level;


private:
    int m_CoPdw;
    unsigned char *m_pRemovePdwIndex;

    //##ModelId=452B0C53032A
    STR_PDWINDEX *m_pGrPdwIndex;

    //##ModelId=452B0C53032E
    int m_nToaShift;

    //##ModelId=452B0C530333
    unsigned int m_uiRefStartSeg;
    //##ModelId=452B0C53033D
    unsigned int m_uiRefEndSeg;
    //! 최대 PDW 개수
    //##ModelId=452B0C530347
    unsigned int m_uiMaxPdw;
    //##ModelId=452B0C530348
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
    //##ModelId=452B0C5303C1
    virtual void CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count )=0;
    //! 펄스열에 마킹을 한다.
    //##ModelId=452B0C5303D3
    virtual void MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType )=0;
    //##ModelId=452B0C5303DD
    virtual STR_PDWINDEX *GetFrqAoaGroupedPdwIndex()=0;
    virtual int GetCoPdw()=0;
    virtual void ClearAllMark()=0;


    template <typename T>
    UINT CheckHarmonic(T priMean1, T priMean2, T tThreshold ) {
        UINT ret=0;
		T r;
        T harmonic;
        T max_mean, min_mean;

        if( priMean1 > priMean2 ) {
            max_mean = priMean1;
            min_mean = priMean2;
        }
        else {
            max_mean = priMean2;
            min_mean = priMean1;
        }

        if( strcmp( typeid(T).name(), "float" ) == 0 ) {
            harmonic = (unsigned int) ( fmod( (float) max_mean, (float) min_mean ) + 0.5 );
        }
        else {
            harmonic = max_mean % min_mean;
        }

        // 10배수 이상이면 STABLE 마진 값을 두배로 해서 harmonic 체크한다.
        T margin_th = tThreshold; // UDIV( max_mean, STB_MARGIN*1000 );

        // 하모닉 체크에서 배수만큼 더한 마진으로 체크한다.
        if( harmonic <= tThreshold+margin_th || min_mean-harmonic <= tThreshold+margin_th ) {
            r = MulDiv64( 1, max_mean, min_mean );
			if( r > UINT_MAX ) {
				ret = UINT_MAX;
			}
			else {
				ret = (UINT) r;
			}
        }

        return ret;
    }

    void MakeCWPulseTrain();
    void ResetJitterSeg();
    BOOL MustDo2ndPulseExtract();
    void MarkStablePulseTrain();
    void CalcEmitterPW( STR_PULSE_TRAIN_SEG *pSeg );
    //##ModelId=452B0C5303DF
    //int CnvPW( int val );
    //##ModelId=452B0C5303E8
    void SavePdwParamIndex();
    //##ModelId=452B0C540009
    void ExtractTrackPT( _TOA refPriMean, float refJitRat );
    //##ModelId=452B0C54001D
    void DiscardPulseTrain();
    //##ModelId=452B0C54001E
    void PrintAllSeg();
    void PrintSeg( int iSeg, STR_PULSE_TRAIN_SEG *pSeg );
    void PrintAllSegPDW( STR_PULSE_TRAIN_SEG *pSeg );
    //##ModelId=452B0C54001F
    void ChangeMarkTo( int startSeg, int endSeg, UINT from_mark, SEG_MARK to_mark );
    //##ModelId=452B0C54003B
    void MergePulseTrain( STR_PULSE_TRAIN_SEG *pMrgSeg, STR_PULSE_TRAIN_SEG *pSrcSeg );
    //##ModelId=452B0C540046
    STR_PULSE_TRAIN_SEG *GetMainSeg( int startSeg, int endSeg );
    //! 추출하고자할 펄스열의 주파수 범위에 맞는 PDW 인가를 체크한다.
    //##ModelId=452B0C540059
    BOOL IsValidPDW( int index, STR_PULSE_TRAIN_SEG *pSeg );
    //! 펄스열을 근거로 주파수 형태 및 주파수 범위를 계산한다.
    //##ModelId=452B0C540063
    void CalcEmitterFrq( STR_PULSE_TRAIN_SEG *pSeg );
    //##ModelId=452B0C54006D
    void GetStartEndPriLevel( unsigned int *pStart_pri_level, unsigned int *pEnd_pri_level );
    //##ModelId=452B0C540077
    void MergeJitterPulseTrain( int startSeg, int endSeg, BOOL bIgnoreJitterP=FALSE );
    //##ModelId=452B0C54008C
    void CalPRILevel( STR_LOWHIGH *pPRILevel, STR_DTOA_HISTOGRAM *pDtoaHist );
    //##ModelId=452B0C54009F
    void DePulseExtract();
    //##ModelId=452B0C5400A0
    void DiscardPulseTrain( unsigned int startseg1, unsigned int endseg, unsigned int startseg2 );
    //##ModelId=452B0C5400AA
    void MemcpySeg( STR_PULSE_TRAIN_SEG *pDestSeg, STR_PULSE_TRAIN_SEG *pSrcDeg );
    //##ModelId=452B0C5400BD
    void CleanPulseTrains( int startseg, int endseg );
    //##ModelId=452B0C5400C7
    void MarkSegForExt( int nStartSeg, int nEndSeg );
    //##ModelId=452B0C5400D2
    void CompStablesJitters( unsigned int nStartStableSeg, unsigned int nStartJitterSeg );
    //##ModelId=452B0C5400DC
    int GetCoExtPulse();
    //##ModelId=452B0C5400DD
    BOOL CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    BOOL CheckToaInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    BOOL CheckOmittedPulse( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 );
    //##ModelId=452B0C5400F9
    void DeleteAllSeg( STR_EMITTER *pEmitter );
    //##ModelId=452B0C540103
    BOOL ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange );
    //##ModelId=452B0C54010D
    void CopyOnePulseTrain( STR_PULSE_TRAIN_SEG *pDstSeg, STR_PULSE_TRAIN_SEG *pSrcSeg );
    //##ModelId=452B0C540117
    void CopyPulseTrains( STR_PULSE_TRAIN_SEG *pDstSeg, STR_PULSE_TRAIN_SEG *pSrcSeg, int coSeg );
    //##ModelId=452B0C540121
    void PulseExtract();
    //##ModelId=452B0C540122
    void ExtractJitter( int type );
    //##ModelId=452B0C54012B
    void FindRefStableSeg( STR_PRI_RANGE_TABLE *pExtRange, int nPriBand=-1 );



    //##ModelId=452B0C540135
    _TOA CheckHarmonic( _TOA mean1, float jitter_p1, _TOA mean2, float jitter_p2 );



    //##ModelId=452B0C540141
    void ExtractStablePT(STR_PRI_RANGE_TABLE *pExtRange, int nPriBand, BOOL flagMargin=FALSE, int iMark=STABLE_MARK );
    //##ModelId=452B0C540168
    void ExtractJitterPT( STR_PRI_RANGE_TABLE *pExtRange, unsigned int uiPriBand, unsigned int coRef=_sp.cm.Rpc, BOOL flagMargin=FALSE ,int iMark=JITTER_MARK, BOOL bIgnoreJitterP=FALSE );
    //##ModelId=452B0C54017E
    void ExtractPatternPT( STR_PRI_RANGE_TABLE *pExtRange, unsigned int uiCoRef=_sp.cm.Rpc, BOOL flagMargin=FALSE );
    //##ModelId=452B0C540191
    void MarkToPdwIndex( STR_PULSE_TRAIN_SEG *pSeg, int mark_type);
    //##ModelId=452B0C54019B
    UINT AnalFreqType(STR_PULSE_TRAIN_SEG *pSeg);
    //##ModelId=452B0C5401A5
    UINT CheckStaggerLevel( _TOA framePri, STR_EMITTER *pEmitter );
    //##ModelId=452B0C5401B8

    //##ModelId=452B0C5401C3
    _TOA CheckHarmonic(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2);
    //##ModelId=452B0C5401D6
    unsigned int ExtractStagger( STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter );
    //##ModelId=452B0C5401EB
    UINT ExtractFramePri( STR_PDWINDEX *pSrcPdwIndex, _TOA framePri);
    //##ModelId=452B0C5401F5
    UINT MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount );
    //##ModelId=452B0C540201
    void AllExtSegMark();
    //##ModelId=452B0C540208
    int CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount);
    //##ModelId=452B0C540212
    int VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount);
    //##ModelId=452B0C540215
    void CleanRefSeg();
    //##ModelId=452B0C54021C
    enPRI_TYPE AnalPRIType( STR_PULSE_TRAIN_SEG *pSeg, enPRI_TYPE ext_type=_UNKNOWN_PRI );
    //##ModelId=452B0C540226
    void ExtractSimpleStablePT(STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex );
    //##ModelId=452B0C540230
    bool FindSeg(STR_PULSE_TRAIN_SEG *pRefSeg, int start, int end);
    //##ModelId=452B0C540244
    void ExtractRefStable();
    //##ModelId=452B0C540245
    void FindRefStable();
    //##ModelId=452B0C540246
    _TOA RecalcDtoaMargin( int ext_type, STR_PULSE_TRAIN_SEG *pSeg, UINT dtoa );
    //##ModelId=452B0C540250
    bool OverlappedSeg(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2);
    //##ModelId=452B0C540259
    void DiscardStablePulseTrain();
    //##ModelId=452B0C54025A
    _TOA VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount );
    //##ModelId=452B0C540263
    void VerifyPRI( STR_PULSE_TRAIN_SEG *pSeg );
    //##ModelId=452B0C540265
    int CalMaxMiss( int type );
    //##ModelId=452B0C54026D
    _TOA CalDtoaMargin( int type, STR_PULSE_TRAIN_SEG *pSeg );
    //##ModelId=452B0C540270
    void UnknownExtract();
    //##ModelId=452B0C540276
    void ExtractJitterPT();
    //##ModelId=452B0C540277
    BOOL CalcSegParam( STR_PULSE_TRAIN_SEG *pSeg, BOOL bIgnoreJitterP=FALSE );
    //##ModelId=452B0C540279
    void ExtractForPT(STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex, _TOA margin=0 );
    //##ModelId=452B0C540282
    float CalcRefPRI( PDWINDEX *pPdwIndex, UINT count, STR_MINMAX_TOA *pPRI );
    //##ModelId=452B0C54028D


    void ChooseTOAMargin(STR_LOWHIGH_TOA *pStrMargin, STR_PRI_RANGE_TABLE *pPriRange, _TOA tDtoa, int ext_type, BOOL bFlagMargin);


    void ExtractBackPT( STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex, _TOA margin=0 );
    //##ModelId=452B0C540297
    BOOL ExtractRefPT( STR_PRI_RANGE_TABLE *pPriRange, int ext_type, STR_PULSE_TRAIN_SEG *pSeg, int start_idx, STR_PDWINDEX *pColPdwIndex, unsigned int uiCoRefPulse=_sp.cm.Rpc, BOOL flagMargin=FALSE, BOOL bIgnoreJitterP=FALSE );
    //##ModelId=452B0C5402AB
    void ExtractStablePT();
    //! 멤버 변수 초기화
    //##ModelId=452B0C5402AC
    void Init();

    //##ModelId=452B0C5402B2
    CPulExt( int coMaxPdw );
    //##ModelId=452B0C5402B4
    virtual ~CPulExt();

};

#endif

#endif // !defined(AFX_PULEXT_H__5C6D2A7D_E233_4E77_ACD5_48D971456B7C__INCLUDED_)

