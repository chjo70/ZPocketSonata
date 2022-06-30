// NAnalPRI.cpp: implementation of the NAnalPRI class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"



#if defined(_ELINT_) || defined(_XBAND_)

#include "../OFP_Main.h"
#endif

#include <stdio.h>

#include "../INC/PDW.h"

#include "../SigAnal/_Macro.h"

#include "NAnalPRI.h"
#include "NewSigAnal.h"

#include "../../Include/globals.h"

STR_PULSE_TRAIN_SEG *CNAnalPRI::m_pSeg=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * @brief CAnalPRI::incSegPriMeanCompare
 * @param arg1
 * @param arg2
 * @return
 */
int CNAnalPRI::incSegPriMeanCompare( const void *arg1, const void *arg2 )
{
    int iRet;
    const UINT *p1, *p2;
    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    p1 = (const UINT *) arg1;
    p2 = (const UINT *) arg2;

    pSeg1 = & m_pSeg[ *p1 ];
    pSeg2 = & m_pSeg[ *p2 ];

    if( pSeg1->stPRI.tMean > pSeg2->stPRI.tMean ) {
        iRet = 1;
    }
    else if( pSeg1->stPRI.tMean < pSeg2->stPRI.tMean ) {
        iRet = (-1);
    }
    else {
        iRet = 0;
    }

    return iRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI
// 반환되는 형  : CNAnalPRI::CNAnalPRI(void *pParent, int coMaxPdw) :
// 함 수 인 자  : void *pParent
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:10:00
//
CNAnalPRI::CNAnalPRI( void *pParent, unsigned int uiCoMaxPdw) : CAnalPRI(uiCoMaxPdw)
{
    m_pNewSigAnal = ( CNewSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pNewSigAnal)

    m_pSeg = CNAnalPRI::GetPulseSeg();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNAnalPRI::~CNAnalPRI
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:10:03
//
CNAnalPRI::~CNAnalPRI()
{

}

/**
 * @brief     객체에서 초기화를 수행한다. PRI 분석시 초기화를 호출해야 한다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-07-10 12:01:31
 * @warning
 */
void CNAnalPRI::Init()
{

    CAnalPRI::m_uiAnalSeg = _spZero;
    CAnalPRI::m_uiCoSeg = GetCoSeg();

    CAnalPRI::m_uiAnalEmitter = _spZero; // m_uiCoEmitter;

    /*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
        \date 2008-07-30 13:35:08, 조철희
    */
    CAnalPRI::Init();

}

/**
 * @brief     PRI 분석을 처리한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-08-24 08:13:46
 * @warning
 */
void CNAnalPRI::Analysis()
{
    PrintFunction

    // 초기화
    Init();

    // 고정펄스열들에 대하여 스태거 그룹핑 수행하여 스태거 신호인지 분석한다.
    GroupingStagger();
    StaggerAnalysis();
    PrintAllEmitter( m_uiStepEmitter, "[1/8] Stable PRI 기반 스태거 분석" );

    // 고정펄스열 그룹핑은 스태거 그룹핑 후 검증하여 해제된 펄스열들에 대해 한다.
    GroupingStable();
    PrintAllEmitter( m_uiStepEmitter, "[2/8] 스테이블 PRI 분석" );

    GroupingJitter();
    PrintAllEmitter( m_uiStepEmitter, "[3/8] 지터 PRI 분석" );

    // 지터 그룹핑된 이후 스태거 분석을 한번 더 수행한다.(Jitter 펄스열들에 대해 Auto-Correlation Function으로 스태거 분석 수행)
    StaggerAnalysis();
    PrintAllEmitter( 0, "[4/8] 스태거 PRI 분석", _JITTER_STAGGER );

    // PRI 고정으로 분석된 에미터들에 대해 D&S 분석을 수행한다.
    //DNSAnalysis();
    //PrintAllEmitter( 0, "[5/8] 드웰 PRI 분석", _DWELL );

    // Agile 형태 에미터를 대상으로 Hopping 여부를 분석한다.
    //HoppingAnalysis();
    //PrintAllEmitter( 0, "[6/8] 호핑 PRI 분석" );

    // 패턴 분석을 수행한다.
    //PatternAnalysis();
    //PrintAllEmitter( 0, "[6/8] 패턴 PRI 분석" );

    // 에미터 그룹핑
    // PRI 타입이 다르더라도 PRI 평균이 같은 에미터 단위는 하나로 형성한다.
    MergeGrouping();

    CAnalPRI::Analysis();

}

/**
 * @brief     스태거 펄스열을 추출한다.
 * @param     STR_PDWINDEX * pPdwIndex
 * @param     _TOA framePri
 * @param     STR_EMITTER * pEmitter
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 16:57:14
 * @warning
 */
unsigned int CNAnalPRI::ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter )
{
    return m_pNewSigAnal->ExtractStagger( pPdwIndex, framePri, pEmitter );
}

/**
 * @brief     CheckPriInterval
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:06
 * @warning
 */
BOOL CNAnalPRI::CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    return m_pNewSigAnal->CheckPriInterval( pSeg1, pSeg2 );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNAnalPRI::DeleteAllSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:10:12
//
void CNAnalPRI::DeleteAllSeg( STR_EMITTER *pEmitter )
{
    m_pNewSigAnal->DeleteAllSeg( pEmitter );
}

/**
 * @brief     추출한 모든 펄스열 정보를 출력한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-15, 10:26
 * @warning
 */
void CNAnalPRI::PrintAllSeg()
{
    m_pNewSigAnal->PrintAllSeg();
}

/**
 * @brief     기준 펄스열을 추출한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:15
 * @warning
 */
void CNAnalPRI::ExtractRefStable()
{
    m_pNewSigAnal->ExtractRefStable();
}

/**
 * @brief     드웰 펄스열을 추출한다.
 * @param     STR_PULSE_TRAIN_SEG * pDwlSeg
 * @param     STR_PRI_RANGE_TABLE * pExtRange
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:18
 * @warning
 */
BOOL CNAnalPRI::ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange )
{
    return m_pNewSigAnal->ExtractDwellRefPT( pDwlSeg, pExtRange );
}

/**
 * @brief     기준 펄스열을 추출한다.
 * @param     STR_PDWINDEX * pSrcPdwIndex
 * @param     _TOA framePri
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:21
 * @warning
 */
UINT CNAnalPRI::ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri )
{
    return m_pNewSigAnal->ExtractFramePri( pSrcPdwIndex, framePri );
}

/**
 * @brief     펄스열 개수를 리턴한다.
 * @return    unsigned int
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:23
 * @warning
 */
unsigned int CNAnalPRI::GetCoSeg()
{
    return m_pNewSigAnal->GetCoSeg();
}

/**
 * @brief     펄스열 추출 시작 포인터를 리턴한다.
 * @return    STR_PULSE_TRAIN_SEG *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:32
 * @warning
 */
STR_PULSE_TRAIN_SEG *CNAnalPRI::GetPulseSeg()
{
    return m_pNewSigAnal->GetPulseSeg();
}

/**
 * @brief     최대 수집 개수를 리턴한다.
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:34
 * @warning
 */
int CNAnalPRI::GetMaxPdw()
{
    return m_pNewSigAnal->GetMaxPdw();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNAnalPRI::MakePRIInfoFromSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI *pPri
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:10:37
//
void CNAnalPRI::MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter )
{
    m_pNewSigAnal->MakePRIInfoFromSeg( pPri, pEmitter );
}

/**
 * @brief     주파수 메디안을 계산한다.
 * @param     STR_TYPEMINMAX * pMinMax
 * @param     PDWINDEX * pPdwIndex
 * @param     unsigned int uiCount
 * @return    UINT
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:10:40
 * @warning
 */
UINT CNAnalPRI::MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount )
{
    return m_pNewSigAnal->MedianFreq( pMinMax, pPdwIndex, uiCount );
}

/**
 * @brief     PRI 검증을 수행한다.
 * @param     PDWINDEX * pPdwIndex
 * @param     unsigned int uiCount
 * @return    _TOA
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-02-06 14:43:48
 * @warning
 */
_TOA CNAnalPRI::VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount )
{
    return m_pNewSigAnal->VerifyPRI( pPdwIndex, uiCount );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNAnalPRI::GetBand
        \author   조철희
        \return   int
        \version  0.0.57
        \date     2008-11-11 19:13:03
        \warning
*/
int CNAnalPRI::GetBand()
{
    return m_pNewSigAnal->GetBand();
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 FindPeakInHist
//!	\author  조철희
//!	\param	 count	인자형태 int
//!	\param	 pPdwIndex	인자형태 PDWINDEX *
//!	\return	 int
//! \version 1.0
//! \date		 2006-07-06 17:21:27
//! \warning
//
int CNAnalPRI::FindPeakInHist( unsigned int uiCount, PDWINDEX *pPdwIndex )
{
    return m_pNewSigAnal->FindPeakInHist(uiCount, pPdwIndex );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::SaveEmitterPdwFile
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int index
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:37
//
void CNAnalPRI::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )
{
    m_pNewSigAnal->SaveEmitterPdwFile( pEmitter, iPLOBID, bSaveFile );

}

/**
 * @brief CNAnalPRI::QSort
 * @param pIdx
 * @param uiCount
 * @param uiSizeof
 */
void CNAnalPRI::QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof )
{
    qsort( pIdx, uiCount, uiSizeof, incSegPriMeanCompare );
    return;
}




/**
 * @brief		가상 에미터 포인터를 리턴한다.
 * @return		CMakeAET*
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 16:49:18
 * @warning		
 */
CMakeAET* CNAnalPRI::GetMakeAET()
{
    return m_pNewSigAnal->GetMakeAET();
}


/**
 * @brief		가상 에미터 포인터를 리턴한다.
 * @return		CMakeAET*
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 16:49:18
 * @warning
 */
bool CNAnalPRI::CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    return m_pNewSigAnal->CheckStablePT( pnHarmonic, pSeg1, pSeg2 );
}
