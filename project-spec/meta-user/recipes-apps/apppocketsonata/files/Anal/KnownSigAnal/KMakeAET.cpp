// KMakeAET.cpp: implementation of the CKMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_ELINT_) || defined(_XBAND_)
#include "../OFP_Main.h"
#elif _POCKETSONATA_
#include "../INC/Macros.h"
#include "../Identify/ELUtil.h"

#else
#error "컴파일러에 DEFINE 을 추가해야 합니다."
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "KnownSigAnal.h"
#include "KMakeAET.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET
// 반환되는 형  : CKMakeAET::CKMakeAET() :
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 14:09:48
//
//##ModelId=42E98F300031
CKMakeAET::CKMakeAET( void *pParent, int coMaxPdw ) : CMakeAET( coMaxPdw )
{
	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)
	 
	// 초기에 한번만 초기화한다.
	m_CoNewAet = 0;

    //m_pAet = NULL;  //GetAet();
    m_pEmitter = GetEmitter();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::~CKMakeAET
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 18:14:06
//
//##ModelId=42E98F300032
CKMakeAET::~CKMakeAET()
{

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKMakeAET::Init
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:11:11
//! \warning
//
void CKMakeAET::Init()
{
	m_CoNewAet = 0;

    m_pTrkAet = m_pKnownSigAnal->GetTrkAET();

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
void CKMakeAET::MakeAET()
{
	int i;
	int nStartAet;
    SRxLOBData *pNewAet;

	// 시작 에미터 번호 위치 백업. 
    nStartAet = m_CoLOB;

	CMakeAET::MakeAET();

	/*! \bug  Dwell 인 경우에는 추적할 에미터 제원으로 업데이트 하도록 한다.
	    \date 2008-10-29 21:39:09, 조철희
	*/
	// 에미터 추출 개수를 저장
    m_CoMakeAet = m_CoLOB;

    pNewAet = & m_LOBData[nStartAet];
    for( i=0 ; i < m_CoLOB ; ++i ) {
        if( pNewAet->iPRIType == _DWELL ) {
            //STR_PRI *pNewPri, *pTrkPri;

            //pNewPri = & pNewAet->aet.pri;
            //pTrkPri = & stTrkAet.aet.pri;
			//pNewPri->min = pTrkPri->min;
			//pNewPri->max = pTrkPri->max;
			//pNewPri->swtLev = pTrkPri->swtLev;
			// memcpy( pNewPri->swtVal, pTrkPri->swtVal, sizeof(int)*pNewPri->swtLev );
			// qsort( pNewPri->swtVal, (size_t) pNewPri->swtLev, sizeof( UINT ), intparamCompare );
			
		}
		++ pNewAet;
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::KnownMakeAET
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 18:47:54
//
//##ModelId=42E98F300030
BOOL CKMakeAET::KnownMakeAET()
{
	int i;
	UINT maxPulse;
	//int idxEmitter;
	//STR_EMITTER *pEmitter;

	MakeAET();

	/*! \bug  m_IdxUpdAet 초기화
	    \date 2006-06-26 13:43:57, 조철희
	*/
	m_IdxUpdAet = -1;

	// 추적 성공인지를 체크한다.
	// 추출된 펄스열로 에미터가 1개 만들어 지면 추
    if( m_CoLOB >= 1 ) {
		// 추적에서 2개 이상의 추적 변경에미터 분석될 때는 가장 많은 펄스열로 분석된것만 추적 Update 로 인정하고
		// 나머지 다른 에미터들은 펄스열 마킹만한다.
		maxPulse = 0;
        for( i=0 ; i < m_CoLOB ; ++i ) {
			// 추적할 PRI 값과 추적한 PRI 값이 같아야 추적 성공으로 한다.
			//-- 조철희 2006-01-25 14:00:31 --//
            if( CompPRI( & m_LOBData[i], m_pTrkAet ) == TRUE ) {
                m_LOBData[i].uiABTID = m_pTrkAet->uiABTID;

                //if( maxPulse < m_pAet[i].ext.noExt ) {
                //	maxPulse = m_pAet[i].ext.noExt;
                m_IdxUpdAet = i;
                //}

                UpdateFreq( & m_LOBData[i] );

                UpdatePRI( & m_LOBData[i] );

			}

			/*! \bug  에미터로 생성된 펄스열들만 마킹을 해서 새로운 에미터 분석시에 분석하지 못하게 한다.
			    \date 2006-06-29 13:53:26, 조철희
			*/
			// 추출된 펄스 Marking
            //idxEmitter = m_pAet[i].ext.idxEmitter;
            //pEmitter = & m_pEmitter[idxEmitter];
            //MarkToEmitterPdwIndex( pEmitter, EXTRACT_MARK );
		}

		// 추출한 펄스열들은 EXTRACT_MARK 을 해서 재 분석을 안 하도록 한다.
		//for( i=0 ; i < m_CoSeg ; ++i ) {
			//MarkToPdwIndex( m_pSeg[i].pdw.pIndex, m_pSeg[i].pdw.count, EXTRACT_MARK );
		//}

	}

    return m_IdxUpdAet >= _spZero;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CompPRI
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PRI *pNewPri
// 함 수 인 자  : STR_PRI *pTrkPri
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-25 14:03:44
//
BOOL CKMakeAET::CompPRI( SRxLOBData *pNewPri, SRxABTData *pTrkPri )
{
	int i;
	float pri_margin;
    BOOL bRet=TRUE;

    switch( pNewPri->iPRIType ) {
		case _STABLE :
        case _JITTER_PATTERN :
        case _DWELL :
			break;

		case _STAGGER :
            if( pTrkPri->iPRIType == _JITTER_RANDOM ) {
            }
            else if( pTrkPri->iPRIType == _STAGGER ) {
                pri_margin = (float) ( 2. * STABLE_MARGIN );  
                if( pNewPri->iPRIElementCount == pTrkPri->iPRIElementCount ) {
                    for( i=0 ; i < pNewPri->iPRIElementCount ; ++i ) {
                        if( CompMeanDiff<float>( pNewPri->fPRISeq[i], pTrkPri->fPRISeq[i], pri_margin ) == FALSE ) {
	  					    bRet = FALSE;
						}
					}
				}
				else {
					bRet = FALSE;
				}
			}
			break;

		case _JITTER_RANDOM :
			// 스태거 추적 신호를 추적분석을 해서
			// 지터로 분석하게 되면 범위를 체크해서 새로운 에미터 생성 또는
			// 추적 실패 여부를 결정한다.
			//-- 조철희 2006-05-09 16:19:35 --//
			/*! \bug  변화폭을 5 usdptj 20 us로 수정함. 
			    \date 2006-09-04 10:47:24, 조철희
			*/
            pri_margin = 20 * _spOneMicrosec;
            if( pTrkPri->iPRIType == _STAGGER ) {
                if( _spFalse == CompMeanDiff<float>( pTrkPri->fPRIMin, pNewPri->fPRIMin, pri_margin ) ) {
					bRet = FALSE;
                }
                if( _spFalse == CompMeanDiff<float>( pTrkPri->fPRIMax, pNewPri->fPRIMax, pri_margin ) ) {
					bRet = FALSE;
                }

			}
            break;

        default:
            break;
	}

	return bRet;
	
}

#ifdef _POCKETSONATA_
#else
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::MakeUpAET
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : SONATA, 2005-09-07 15:04:06
//
void CKMakeAET::MakeUpAET()
{
	int count;
	int coUpdAet;
    SRxLOBData *pNewAet;
    SRxLOBData *pUpdAet;
	
	count = GetCoLOB();
	pNewAet = GetNewLOB();
	pUpdAet = GetUpdLOB();

	coUpdAet = 0;

	// 추적 성공일때...
	// 새로운 에미터와 추적 에미터와의 하모닉 체크해서 새로운 에미터를 제거하도록 한다.
	//-- 조철희 2005-10-24 11:33:36 --//
	if( pUpdAet != NULL ) {
		// 추적 성공 에미터와 추적할 에미터 제원과 비교해서 하모닉 체크해서 유사 에미터로 판정한다.
		//-- 조철희 2005-12-07 19:16:44 --//
        if( CheckHarmonic<SRxABTData>( m_pTrkAet, pUpdAet ) >= 2 ) {
            pUpdAet->iPRIType = m_pTrkAet->iPRIType;
            pUpdAet->iPRIPatternType = m_pTrkAet->iPRIPatternType;
            pUpdAet->fPRIPatternPeriod = m_pTrkAet->fPRIPatternPeriodMean;
            pUpdAet->fPRIMean = m_pTrkAet->fPRIMean;
            pUpdAet->fPRIMax = m_pTrkAet->fPRIMax;
            pUpdAet->fPRIMin = m_pTrkAet->fPRIMin;
            pUpdAet->fPRIDeviation = m_pTrkAet->fPRIDeviation;
            pUpdAet->fPRIJitterRatio = m_pTrkAet->fPRIJitterRatio;
            pUpdAet->iPRIPositionCount = m_pTrkAet->iPRIPositionCount;
            pUpdAet->iPRIElementCount = m_pTrkAet->iPRIElementCount;

            memcpy( & pUpdAet->fPRISeq, & m_pTrkAet->fPRISeq, sizeof( m_pTrkAet->fPRISeq ) );
		}

		for( int i=0 ; i < count ; ++i ) {
            if( m_LOBData[i].uiABTID != _spZero ) {
#ifndef _XBAND_
                pUpdAet->iScanType = m_pTrkAet->iScanType;
                pUpdAet->fScanPeriod = m_pTrkAet->fMeanScanPeriod;
				++ coUpdAet;

#endif
			}
		}
	}
	// 추적 에미터가 발견되지 않을 때는 새로운 에미터 제원으로 추적 업데이트한다.
	else if( count >= 1 ) {
        SRxLOBData *pDummyAet;

		// ART 제원을 SWAP 하기 위한 버퍼
        pDummyAet = & m_LOBData[ MAX_AET ];

		for( int i=0 ; i < count ; ++i ) {
            if( CheckHarmonic<SRxABTData>( m_pTrkAet, pNewAet ) == TRUE ) {
				// 하모닉 관계 에미터 제원 값을 수정한다.
				// 추적 성공임을 표시한다.
                pNewAet->uiABTID = m_pTrkAet->uiABTID;

				// 방위 정보는 최근 정보로 한다.
				// PRI  값은 하모닉 관계로 추적 에미터 제원으로 한다.
                //memcpy( & pNewAet->aet.pri, & stTrkAet.aet.pri, sizeof( STR_PRI ) );
                pNewAet->iPRIType = m_pTrkAet->iPRIType;
                pNewAet->iPRIPatternType = m_pTrkAet->iPRIPatternType;
                pNewAet->fPRIPatternPeriod = m_pTrkAet->fPRIPatternPeriodMean;
                pNewAet->fPRIMean = m_pTrkAet->fPRIMean;
                pNewAet->fPRIMax = m_pTrkAet->fPRIMax;
                pNewAet->fPRIMin = m_pTrkAet->fPRIMin;
                pNewAet->fPRIDeviation = m_pTrkAet->fPRIDeviation;
                pNewAet->fPRIJitterRatio = m_pTrkAet->fPRIJitterRatio;
                pNewAet->iPRIPositionCount = m_pTrkAet->iPRIPositionCount;
                pNewAet->iPRIElementCount = m_pTrkAet->iPRIElementCount;

                memcpy( & pNewAet->fPRISeq, & m_pTrkAet->fPRISeq, sizeof( m_pTrkAet->fPRISeq ) );

				// 유사 에미터를 결정한 에미터를 예비 버퍼에 복사한다.
                memcpy( pDummyAet, pNewAet, sizeof( SRxLOBData ) );

				// 유사 에미터 까지 에미터를 이동한다.
				for( int j=i-1 ; j >= 0 ; --j ) {
                    memcpy( & m_LOBData[j+1], & m_LOBData[j], sizeof( SRxLOBData ) );
				}
                memcpy( & m_LOBData[0], pDummyAet, sizeof( SRxLOBData ) );

				m_IdxUpdAet = 0;

				coUpdAet = 1;

				break;
			}

			++ pNewAet;
		}
	}

	m_CoNewAet = count - coUpdAet;

}
#endif

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::IsUpdateAet
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-09-08 10:14:57
//
BOOL CKMakeAET::IsUpdateAet()
{
	// 추적 성공 또는 실패인지를 검사한다.
    return m_LOBData[0].uiABTID != 0;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetCoNewAet
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-10-24 13:57:54
//
int CKMakeAET::GetCoNewAet()
{
	return m_CoNewAet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKMakeAET::GetNewAet
// 반환되는 형  : STR_NEWAET
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-10-24 11:41:29
//
SRxLOBData *CKMakeAET::GetNewLOB()
{
    SRxLOBData *pLOBData=NULL;

    for( int i=0 ; i < m_CoLOB ; ++i ) {
        if( m_LOBData[i].uiABTID == 0 ) {
            pLOBData = & m_LOBData[i];
        }
	}
	
    return pLOBData;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetIndexNewAet
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-26 11:02:51
//
int CKMakeAET::GetIndexNewAet()
{
    int iIndex=-1, i;

    for( i=0 ; i < m_CoLOB ; ++i ) {
        if( m_LOBData[i].uiABTID == 0 ) {
            iIndex = i;
            break;
        }
	}
	
    return iIndex;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *GetUpdAet
// 반환되는 형  : STR_UPDAET
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-10-24 11:42:24
//
SRxLOBData *CKMakeAET::GetUpdLOB()
{
    SRxLOBData *pSRxLOBData=NULL;

	if( m_IdxUpdAet >= 0 ) {
        pSRxLOBData = & m_LOBData[m_IdxUpdAet];
    }

    return pSRxLOBData;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CalcAoaMeanByHistAoa
// 반환되는 형  : int
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:23
//
int CKMakeAET::CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex )
{
	return m_pKnownSigAnal->CalcAoaMeanByHistAoa( pSrcIndex );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetColPdw
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:27
//
int CKMakeAET::GetColPdw()
{
	return m_pKnownSigAnal->GetColPdw();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CalcPAMean
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:30
//
int CKMakeAET::CalcPAMean(PDWINDEX *pPdwIndex, int count )
{
	return m_pKnownSigAnal->CalcPAMean( pPdwIndex, count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::VerifyPW
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:32
//
int CKMakeAET::VerifyPW( PDWINDEX *pPdwIndex, int count )
{
	return m_pKnownSigAnal->VerifyPW( pPdwIndex, count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:35
//
void CKMakeAET::MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type )
{
	m_pKnownSigAnal->MarkToPdwIndex( pPdwIndex, count, mark_type );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::SaveEmitterPdwFile
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int index
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:37
//
void CKMakeAET::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )
{
	m_pKnownSigAnal->SaveEmitterPdwFile( pEmitter, index );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetCoSeg
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:39
//
int CKMakeAET::GetCoSeg()
{
	return m_pKnownSigAnal->GetCoSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetCoEmitter
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:42
//
int CKMakeAET::GetCoEmitter()
{
    return m_pKnownSigAnal->GetCoEmitter();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKMakeAET::GetPulseSeg
// 반환되는 형  : STR_PULSE_TRAIN_SEG
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:44
//
STR_PULSE_TRAIN_SEG *CKMakeAET::GetPulseSeg()
{
	return m_pKnownSigAnal->GetPulseSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKMakeAET::GetEmitter
// 반환되는 형  : STR_EMITTER
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:47
//
STR_EMITTER *CKMakeAET::GetEmitter()
{
    return m_pKnownSigAnal->GetEmitter();
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CKMakeAET::CalcFreqMedian
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-05-09 14:59:01
//! \bug
//! \warning
//
UINT CKMakeAET::CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg )
{
	return m_pKnownSigAnal->MedianFreq( NULL, pSeg->pdw.pIndex, pSeg->pdw.uiCount );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKMakeAET::UpdateFreq
    \author   조철희
    \param    pUpdAetFrq 인자형태 STR_FRQ *
    \return   void
    \version  0.0.53
    \date     2008-11-03 11:25:01
    \warning
*/
void CKMakeAET::UpdateFreq( SRxLOBData *pUpdAetFrq )
{
    //STR_FRQ *pTrkAetFrq;

    //pTrkAetFrq = & stTrkAet.aet.frq;
    if( m_pTrkAet->iFreqType != pUpdAetFrq->iFreqType ) {
        switch( m_pTrkAet->iFreqType ) {
            case _HOPPING :
                pUpdAetFrq->iFreqType = m_pTrkAet->iFreqType;
                pUpdAetFrq->iFreqPatternType = m_pTrkAet->iFreqPatternType;
                pUpdAetFrq->fFreqPatternPeriod = m_pTrkAet->fFreqPatternPeriodMean;
                pUpdAetFrq->fFreqMean = m_pTrkAet->fFreqMean;
                pUpdAetFrq->fFreqMax = m_pTrkAet->fFreqMax;;
                pUpdAetFrq->fFreqMin = m_pTrkAet->fFreqMin;;
                pUpdAetFrq->fFreqDeviation = m_pTrkAet->fFreqDeviation;
                pUpdAetFrq->iFreqPositionCount = m_pTrkAet->iFreqPositionCount;
                pUpdAetFrq->iFreqElementCount = m_pTrkAet->iFreqElementCount;
                memcpy( pUpdAetFrq->fFreqSeq, m_pTrkAet->fFreqSeq, sizeof( m_pTrkAet->fFreqSeq ) );
				break;

			case _RANDOM_AGILE :
                pUpdAetFrq->iFreqType = m_pTrkAet->iFreqType;
				break;

			case _PATTERN_AGILE :
                pUpdAetFrq->iFreqType = _PATTERN_AGILE;
                pUpdAetFrq->fFreqPatternPeriod = m_pTrkAet->fFreqPatternPeriodMean;
                pUpdAetFrq->iFreqPatternType = m_pTrkAet->iFreqPatternType;
				break;

            default:
                break;
		}
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKMakeAET::UpdatePRI
		\author   조철희
		\param    pUpdAetPri 인자형태 STR_PRI *
		\return   void
		\version  0.0.53
		\date     2008-11-03 12:40:25
		\warning
*/
void CKMakeAET::UpdatePRI( SRxLOBData *pUpdAetPri )
{
    //STR_PRI *pTrkAetPri;

    //pTrkAetPri = & m_pTrkAet.aet.pri;
    if( m_pTrkAet->iPRIType != pUpdAetPri->iPRIType ) {
        switch( m_pTrkAet->iPRIType ) {
			case _STAGGER :
                //memcpy( pUpdAetPri, pTrkAetPri, sizeof( STR_PRI ) );
				break;

            default :
                break;
		}
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKMakeAET::GetPdwParam
		\author   조철희
		\return   STR_PDWPARAM*
		\version  0.0.59
		\date     2008-11-19 12:03:58
		\warning
*/
STR_PDWPARAM* CKMakeAET::GetPdwParam()
{
	return m_pKnownSigAnal->GetPdwParam();
}


/**
 * @brief CKMakeAET::DISP_FineAet
 * @param pLOB
 */
void CKMakeAET::DISP_FineAet( SRxLOBData *pLOB )
{


}

/**
 * @brief CKMakeAET::IsStorePDW
 * @return
 */
unsigned int CKMakeAET::IsStorePDW()
{
    return m_pKnownSigAnal->IsStorePDW();
}

/**
 * @brief     CheckHarmonic
 * @param     float mean1
 * @param     float mean2
 * @param     float priThreshold
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-04, 10:21
 * @warning
 */
// UINT CKMakeAET::CheckHarmonic(float mean1, float mean2, float priThreshold ) 
//{
//    return m_pKnownSigAnal->CheckHarmonic( mean1, mean2, priThreshold );
//}

#if defined(_ELINT_) || defined(_XBAND_)
/**
 * @brief     
 * @return    EN_RADARCOLLECTORID
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/22 12:23:55
 * @warning   
 */
EN_RADARCOLLECTORID CKMakeAET::GetCollectorID() 
{
	return m_pKnownSigAnal->GetCollectorID(); 
}

/**
 * @brief     
 * @return    char *
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/22 12:23:51
 * @warning   
 */
char *CKMakeAET::GetTaskID()
{
	return m_pKnownSigAnal->GetTaskID(); 
}
#endif

/**
 * @brief     
 * @param     int index
 * @return    SRxLOBData *
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/22 12:26:33
 * @warning   
 */
SRxLOBData *CKMakeAET::GetLOBData( int index ) 
{
	return & m_LOBData[index]; 
}

/**
 * @brief     
 * @param     struct timespec * pTimeSpec
 * @return    void
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 21:45:47
 * @warning   
 */
void CKMakeAET::GetCollectTime( struct timespec *pTimeSpec )
{
	m_pKnownSigAnal->GetCollectTime( pTimeSpec );
}