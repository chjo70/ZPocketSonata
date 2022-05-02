// NMakeAET.cpp: implementation of the NMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _MSC_VER

#elif __linux__
#include <sys/timeb.h>

#elif __VXWORKS__

#else
#include <unistd.h>

#endif


#include "../OFP_Main.h"

#include <stdio.h>

#include "NMakeAET.h"
#include "NewSigAnal.h"

#include "../../Include/globals.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET
// 반환되는 형  : CNMakeAET::CNMakeAET(void *pParent, int coMaxPdw) :
// 함 수 인 자  : void *pParent
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-20 19:04:38
//
CNMakeAET::CNMakeAET( void *pParent, int coMaxPdw ) : CMakeAET( coMaxPdw )
{
    m_pNewSigAnal = ( CNewSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pNewSigAnal)

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::~CNMakeAET
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-20 19:04:41
//
CNMakeAET::~CNMakeAET()
{

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CNMakeAET::Init
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:11:11
//! \warning
//
void CNMakeAET::Init()
{
    /*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
        \date 2008-07-30 13:29:46, 조철희
    */
    //m_CoMakeLOB = 0;

    //m_enBandWidth = m_pNewSigAnal->GetBandWidth();

    CMakeAET::Init();
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    PRI 분석을 통해서 P-AET를 근더로 에미터를 생성한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:10:16
//! \warning
//
void CNMakeAET::MakeAET()
{
    // 초기화
    // Init();
    PrintFunction

    CMakeAET::MakeAET();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : 히스토그램을 이용해서 방위 평균값을 계산한다.
// 반환되는 형  : int
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:23
//
int CNMakeAET::CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex )
{
    return m_pNewSigAnal->CalcAoaMeanByHistAoa( pSrcIndex );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : 신호를 수집한다.
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:27
//
int CNMakeAET::GetColPdw()
{
    return m_pNewSigAnal->GetColPdw();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::CalcPAMean
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:30
//
int CNMakeAET::CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount )
{
    return m_pNewSigAnal->CalcPAMean( pPdwIndex, uiCount );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::VerifyPW
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:32
//
int CNMakeAET::VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount)
{
    return m_pNewSigAnal->VerifyPW( pPdwIndex, uiCount );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:35
//
void CNMakeAET::MarkToPdwIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType)
{
    m_pNewSigAnal->MarkToPdwIndex( pPdwIndex, uiCount, usMarkType);
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
void CNMakeAET::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )
{
    m_pNewSigAnal->SaveEmitterPdwFile( pEmitter, iPLOBID, bSaveFile );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::GetCoSeg
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:39
//
unsigned int CNMakeAET::GetCoSeg()
{
    return m_pNewSigAnal->GetCoSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNMakeAET::GetCoEmitter
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:42
//
int CNMakeAET::GetCoEmitter()
{
    return m_pNewSigAnal->GetCoEmitter();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CNMakeAET::GetPulseSeg
// 반환되는 형  : STR_PULSE_TRAIN_SEG
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:44
//
STR_PULSE_TRAIN_SEG *CNMakeAET::GetPulseSeg()
{
    return m_pNewSigAnal->GetPulseSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CNMakeAET::GetEmitter
// 반환되는 형  : STR_EMITTER
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:17:47
//
STR_EMITTER *CNMakeAET::GetEmitter()
{
    return m_pNewSigAnal->GetEmitter();
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CalcFreqMedian
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-05-09 14:56:34
//! \bug
//! \warning
//
UINT CNMakeAET::CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg )
{
    return m_pNewSigAnal->MedianFreq( NULL, pSeg->pdw.pIndex, pSeg->pdw.uiCount );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNMakeAET::GetPdwParam
        \author   조철희
        \return   STR_PDWPARAM*
        \version  0.0.59
        \date     2008-11-19 12:01:44
        \warning
*/
STR_PDWPARAM* CNMakeAET::GetPdwParam()
{
    return m_pNewSigAnal->GetPdwParam();
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNMakeAET::MarkAllAetToPdwIndex
        \author   조철희
        \return   void
        \version  0.0.1
        \date     2008-01-22 13:13:34
        \warning
*/
void CNMakeAET::MarkAllAetToPdwIndex()
{
    int i;
    //STR_PDWINDEX *pPdwIndex;

    for( i=0 ; i < m_iCoLOB ; ++i ) {
        //pPdwIndex = & m_pEmitter[ m_Aet[i].ext.idxEmitter ].pdw;
        //MarkToPdwIndex( pPdwIndex->pIndex, pPdwIndex->count, EXTRACT_MARK );
    }

}

/**
 * @brief CNMakeAET::DISP_FineAet
 * @param pLOB
*/
void CNMakeAET::DISP_FineAet( SRxLOBData *pLOB )
{
    return m_pNewSigAnal->DISP_FineAet(pLOB);

}

/**
 * @brief CNMakeAET::IsStorePDW
 * @return
 */
unsigned int CNMakeAET::IsStorePDW()
{
    return m_pNewSigAnal->IsStorePDW();
}

/**
 * @brief     
 * @param     struct timespec * pTimeSpec
 * @return    void
 * @author    조철희(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 21:43:36
 * @warning   
 */
void CNMakeAET::GetCollectTime( struct timespec *pTimeSpec )
{
	m_pNewSigAnal->GetCollectTime( pTimeSpec );
}

#if defined(_ELINT_) || defined(_XBAND_)

/**
 * @brief     
 * @return    EN_RADARCOLLECTORID
 * @author    조철희(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 21:43:55
 * @warning   
 */
EN_RADARCOLLECTORID CNMakeAET::GetCollectorID()
{
    return m_pNewSigAnal->GetCollectorID();
}

/**
 * @brief     
 * @return    char *
 * @author    조철희(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 21:44:00
 * @warning   
 */
char *CNMakeAET::GetTaskID()
{
    return m_pNewSigAnal->GetTaskID();
}

#endif

/**
 * @brief     (
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-02, 14:45
 * @warning
 */
unsigned int CNMakeAET::GetPDWID() 
{ 
    return m_pNewSigAnal->GetPDWID(); 
}

LONG CNMakeAET::GetOPInitID() 
{
	return m_pNewSigAnal->GetOPInitID();
}