// KMakeAET.cpp: implementation of the CKMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../OFP_Main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include "KnownSigAnal.h"
#include "KMakeAET.h"

#include "../../Include/globals.h"

#include "../EmitterMerge/ELStringDefn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * @brief     CKMakeAET
 * @param     void * pParent
 * @param     unsigned int uiCoMaxPdw
 * @return    
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-07-28 14:09:48
 * @warning
 */
CKMakeAET::CKMakeAET( void *pParent, unsigned int uiCoMaxPdw ) : CMakeAET(MAX_AET)
{
	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)
	 
	// 초기에 한번만 초기화한다.
	m_iCoNewAet = 0;

    //m_pAet = NULL;  //GetAet();
    m_pEmitter = CKMakeAET::GetEmitter();

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
	m_iCoNewAet = 0;

    m_pTrkABT = m_pKnownSigAnal->GetTrkAET();

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
    PrintFunction

	// 시작 에미터 번호 위치 백업. 
    //nStartAet = m_CoLOB;

	CMakeAET::MakeAET();

	/*! \bug  Dwell 인 경우에는 추적할 에미터 제원으로 업데이트 하도록 한다.
	    \date 2008-10-29 21:39:09, 조철희
	*/
	// 에미터 추출 개수를 저장
    //m_CoMakeAet = m_CoLOB;

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
    // int idxLOBData;

    //SRxLOBData *pLOBData;
	STR_EMITTER *pEmitter;

	MakeAET();

	/*! \bug  m_IdxUpdAet 초기화
	    \date 2006-06-26 13:43:57, 조철희
	*/
    m_IdxUpdAet = -1;

    CalcAllKnownSucessRatio();

	// 추적 성공인지를 체크한다.
	// 추출된 펄스열로 에미터가 1개 만들어 질떄 추적 성공으로 한다.
    m_IdxUpdAet = SelectKnownSuccessLOB();
    if(GetIdxUpdAet() >= _spZero ) {
        //   UpdateFreq(pLOBData);
        //   UpdatePRI(pLOBData);

		/*! \bug  에미터로 생성된 펄스열들만 마킹을 해서 새로운 에미터 분석시에 분석하지 못하게 한다.
			\date 2006-06-29 13:53:26, 조철희
		*/
		// 추출된 펄스 Marking
        pEmitter = GetEmitterFromKnownIndex( (UINT) GetIdxUpdAet() );
        MarkToEmitterPdwIndex( pEmitter, enEXTRACT_MARK );
	}

    return GetIdxUpdAet() >= _spZero;

}

/**
 * @brief     펄스열에 대해서 마킹 정보를 설정한다.
 * @param     STR_EMITTER * pEmitter
 * @param     PULSE_EXTRACT_MARK usMark
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-16, 10:55
 * @warning
 */
void CKMakeAET::MarkToEmitterPdwIndex( STR_EMITTER *pEmitter, PULSE_MARK enMarkType )
{
    m_pKnownSigAnal->MarkToPDWIndex( pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount, enMarkType);

}

/**
 * @brief     성공한 LOB를 선택한다.
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-04-27, 11:42
 * @warning
 */
int CKMakeAET::SelectKnownSuccessLOB()
{
    int i, iIdxLOB=-1;

    int iNumOfPDW, iMaxNumOfPDW=-1;
    float fKnownSuccessRatio, fMaxKnownSuccessRatio=-1.;

    STR_EMITTER *pEmitter;

    //SRxLOBData *pLOBData;

    for (i = 0; i < m_iCoLOB; ++i) {
        fKnownSuccessRatio = GetKnownSuccessRatio(i);

        pEmitter = GetEmitterFromKnownIndex( (UINT) i);
        iNumOfPDW = (int) pEmitter->stPDW.uiCount;

        // 추적 성공율과 분석한 PDW 개수로 추적 성공 LOB를 선택한다.
        if( (fMaxKnownSuccessRatio < fKnownSuccessRatio) || \
            ( ( is_zero<float>( fMaxKnownSuccessRatio - fKnownSuccessRatio) == true) && ( iMaxNumOfPDW <= iNumOfPDW ) ) ) {
            fMaxKnownSuccessRatio = fKnownSuccessRatio;
            iMaxNumOfPDW = iNumOfPDW;
            iIdxLOB = i;
        }
    }

    return iIdxLOB;
}

/**
 * @brief     주파수 추적 성공율을 계산한다. (추적할 빔 정보로 추적을 한다는 가정하에 )
 * @param     SRxLOBData * pLOBData
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 11:03
 * @warning
 */
float CKMakeAET::CalcFreqSuccessRatio(SRxLOBData *pLOBData)
{
    float fRet=0.;

    if (pLOBData->vFreqType == (unsigned char) m_pTrkABT->vFreqType) {
        fRet = 100.;
    }
    else {
        switch (m_pTrkABT->vFreqType) {
            case E_AET_FRQ_FIXED:
                if(pLOBData->vFreqType == E_AET_FRQ_AGILE ) {
                    fRet = 140.;
                }
                else {
                }
            break;

            case E_AET_FRQ_AGILE:
                if (pLOBData->vFreqType == E_AET_FRQ_FIXED) {
                    fRet = 40.;
                }
                else if (pLOBData->vFreqType == E_AET_FRQ_PATTERN || pLOBData->vFreqType == E_AET_FRQ_HOPPING) {
                    fRet = 140.;
                }
                else {
                }
                break;


            case E_AET_FRQ_HOPPING:
                if (pLOBData->vFreqType == E_AET_FRQ_AGILE) {
                    fRet = 40.;
                }
                break;

            case E_AET_FRQ_PATTERN:
                if (pLOBData->vFreqType == E_AET_FRQ_AGILE) {
                    fRet = 40.;
                }
                break;

            default:
                break;

        }
    }

    return fRet;
}


/**
 * @brief     PRI 추적 성공율을 계산한다. (추적할 빔 정보로 추적을 한다는 가정하에 )
 * @param     SRxLOBData * pLOBData
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 11:03
 * @warning
 */
float CKMakeAET::CalcPRISuccessRatio(SRxLOBData *pLOBData)
{
    float fRet = 0.;

    if (pLOBData->vPRIType == m_pTrkABT->vPRIType) {
        fRet = 100.;
    }
    else {
        switch (m_pTrkABT->vPRIType) {
        case E_AET_PRI_FIXED:
            if (pLOBData->vFreqType == E_AET_PRI_DWELL_SWITCH) {
                fRet = 140.;
            }
            else {
            }
            break;

        case E_AET_PRI_STAGGER:
            if (pLOBData->vFreqType == E_AET_PRI_JITTER) {
                fRet = 40.;
            }
            else {
            }
            break;

        case E_AET_PRI_JITTER:
            if (pLOBData->vFreqType == E_AET_PRI_STAGGER || pLOBData->vFreqType == E_AET_PRI_PATTERN || pLOBData->vFreqType == E_AET_PRI_DWELL_SWITCH) {
                fRet = 140.;
            }
            break;

        case E_AET_PRI_PATTERN:
            if (pLOBData->vFreqType == E_AET_PRI_JITTER) {
                fRet = 40.;
            }
            break;

        case E_AET_PRI_DWELL_SWITCH:
            if (pLOBData->vFreqType == E_AET_PRI_JITTER) {
                fRet = 40.;
            }
            break;

        default:
            break;

        }
    }
    return fRet;

}

/**
 * @brief     추적 성공율을 계산하여 리턴한다.
 * @param     SRxLOBData * pLOBData
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 10:53
 * @warning
 */
void CKMakeAET::CalcAllKnownSucessRatio()
{
    int i;

    float fRatio;

    SRxLOBData *pLOBData;

    for (i = 0; i < m_iCoLOB; ++i) {
        pLOBData = GetLOBData(i);

        // 주파수 추적 성공율 계산
        fRatio = CalcFreqSuccessRatio( pLOBData );

        // PRI 추적 성공율 계산
        fRatio += CalcPRISuccessRatio(pLOBData);

        SetKnownSuccessRatio(i, fRatio);

    }

    return;
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

    switch( pNewPri->vPRIType ) {
		case _STABLE :
            pri_margin = (float)(2. * STABLE_MARGIN);
            bRet = CompMeanDiff<float>(pNewPri->fPRIMean, pTrkPri->fPRIMean, pri_margin);
            break;

        case _JITTER_PATTERN :
        case _DWELL :
			break;

		case _STAGGER :
            if( pTrkPri->vPRIType == _JITTER_RANDOM ) {
            }
            else if( pTrkPri->vPRIType == _STAGGER ) {
                pri_margin = (float) ( 2. * STABLE_MARGIN );  
                if( pNewPri->vPRIElementCount == pTrkPri->vPRIElementCount ) {
                    for( i=0 ; i < pNewPri->vPRIElementCount ; ++i ) {
                        if( CompMeanDiff<float>( pNewPri->fPRISeq[i], pTrkPri->fPRISeq[i], pri_margin ) == FALSE ) {
	  					    bRet = FALSE;
						}
					}
				}
				else {
					bRet = FALSE;
				}
			}
            else {
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
            if( pTrkPri->vPRIType == _STAGGER ) {
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

#if defined(_POCKETSONATA_) || defined(_XBAND_)
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
	int iCount;
	int coUpdAet;
    SRxLOBData *pNewAet;
    SRxLOBData *pUpdAet;
	
    iCount = GetCoLOB();
	pNewAet = GetNewLOB();
	pUpdAet = GetUpdLOB();

	coUpdAet = 0;

	// 추적 성공일때...
	// 새로운 에미터와 추적 에미터와의 하모닉 체크해서 새로운 에미터를 제거하도록 한다.
	//-- 조철희 2005-10-24 11:33:36 --//
	if( pUpdAet != NULL ) {
		// 추적 성공 에미터와 추적할 에미터 제원과 비교해서 하모닉 체크해서 유사 에미터로 판정한다.
		//-- 조철희 2005-12-07 19:16:44 --//
        if( CheckHarmonic<SRxABTData>( m_pTrkABT, pUpdAet ) >= 2 ) {
            pUpdAet->vPRIType = m_pTrkABT->vPRIType;
            pUpdAet->vPRIPatternType = m_pTrkABT->vPRIPatternType;
            pUpdAet->fPRIPatternPeriod = m_pTrkABT->fPRIPatternPeriodMean;
            pUpdAet->fPRIMean = m_pTrkABT->fPRIMean;
            pUpdAet->fPRIMax = m_pTrkABT->fPRIMax;
            pUpdAet->fPRIMin = m_pTrkABT->fPRIMin;
            pUpdAet->fPRIDeviation = m_pTrkABT->fPRIDeviation;
            pUpdAet->fPRIJitterRatio = m_pTrkABT->fPRIJitterRatio;
            pUpdAet->vPRIPositionCount = m_pTrkABT->vPRIPositionCount;
            pUpdAet->vPRIElementCount = m_pTrkABT->vPRIElementCount;

            memcpy( & pUpdAet->fPRISeq, & m_pTrkABT->fPRISeq, sizeof( m_pTrkABT->fPRISeq ) );
		}

		for( int i=0 ; i < iCount; ++i ) {
            if( m_LOBData[i].uiABTID != _spZero ) {
#ifndef _XBAND_
                pUpdAet->iScanType = m_pTrkABT->vScanType;
                pUpdAet->fScanPeriod = m_pTrkABT->fMeanScanPeriod;
				++ coUpdAet;

#endif
			}
		}
	}
	// 추적 에미터가 발견되지 않을 때는 새로운 에미터 제원으로 추적 업데이트한다.
	else if(iCount >= _spOne ) {
        SRxLOBData *pDummyAet;

		// ART 제원을 SWAP 하기 위한 버퍼
        pDummyAet = & m_LOBData[ MAX_AET ];

		for( int i=0 ; i < iCount; ++i ) {
            if( CheckHarmonic<SRxABTData>( m_pTrkABT, pNewAet ) == TRUE ) {
				// 하모닉 관계 에미터 제원 값을 수정한다.
				// 추적 성공임을 표시한다.
                pNewAet->uiABTID = m_pTrkABT->uiABTID;

				// 방위 정보는 최근 정보로 한다.
				// PRI  값은 하모닉 관계로 추적 에미터 제원으로 한다.
                //memcpy( & pNewAet->aet.pri, & stTrkAet.aet.pri, sizeof( STR_PRI ) );
                pNewAet->vPRIType = m_pTrkABT->vPRIType;
                pNewAet->vPRIPatternType = m_pTrkABT->vPRIPatternType;
                pNewAet->fPRIPatternPeriod = m_pTrkABT->fPRIPatternPeriodMean;
                pNewAet->fPRIMean = m_pTrkABT->fPRIMean;
                pNewAet->fPRIMax = m_pTrkABT->fPRIMax;
                pNewAet->fPRIMin = m_pTrkABT->fPRIMin;
                pNewAet->fPRIDeviation = m_pTrkABT->fPRIDeviation;
                pNewAet->fPRIJitterRatio = m_pTrkABT->fPRIJitterRatio;
                pNewAet->vPRIPositionCount = m_pTrkABT->vPRIPositionCount;
                pNewAet->vPRIElementCount = m_pTrkABT->vPRIElementCount;

                memcpy( & pNewAet->fPRISeq, & m_pTrkABT->fPRISeq, sizeof( m_pTrkABT->fPRISeq ) );

				// 유사 에미터를 결정한 에미터를 예비 버퍼에 복사한다.
                memcpy( pDummyAet, pNewAet, sizeof( SRxLOBData ) );

				// 유사 에미터 까지 에미터를 이동한다.
				for( int j=i-1 ; j >= 0 ; --j ) {
                    memcpy( & m_LOBData[j+1], & m_LOBData[j], sizeof( SRxLOBData ) );
				}
                memcpy( & m_LOBData[0], pDummyAet, sizeof( SRxLOBData ) );

				IdxUpdAet(0);

				coUpdAet = 1;

				break;
			}

			++ pNewAet;
		}
	}

	m_iCoNewAet = iCount - coUpdAet;

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
    return m_KwnLOB[_spZero].stLOBData.uiABTID != _spZero;
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
	return m_iCoNewAet;
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
    SRxLOBData *pRetLOBData=NULL;
    SRxLOBData *pLOBData;
    
    for( int i=0 ; i < m_iCoLOB ; ++i ) {
        pLOBData = GetLOBData(i);

        if(pLOBData->uiABTID == _spZero ) {
            pRetLOBData = pLOBData;
        }
	}
	
    return pRetLOBData;
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

    SRxLOBData *pLOBData;

    for( i=0 ; i < m_iCoLOB ; ++i ) {
        pLOBData = GetLOBData(i);

        if(pLOBData->uiABTID == _spZero) {
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

	if( GetIdxUpdAet() >= 0 ) {
        pSRxLOBData = GetLOBData (GetIdxUpdAet() );
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
unsigned int CKMakeAET::GetColPdw()
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
int CKMakeAET::CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount)
{
	return m_pKnownSigAnal->CalcPAMean( pPdwIndex, uiCount);
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
int CKMakeAET::VerifyPW( PDWINDEX *pPdwIndex, unsigned int uiCount)
{
	return (int) m_pKnownSigAnal->VerifyPW( pPdwIndex, uiCount);
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::SaveEmitterPDWFile
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int index
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:37
//
void CKMakeAET::SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )
{
	m_pKnownSigAnal->SaveEmitterPDWFile( pEmitter, iPLOBID, bSaveFile );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetCoSeg
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:39
//
unsigned int CKMakeAET::GetCoSeg()
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
unsigned int CKMakeAET::GetCoEmitter()
{
    return m_pKnownSigAnal->GetCoEmitter();
}

/**
 * @brief     STR_PULSE_TRAIN_SEG 데이터 구조체 포인터를 리턴합니다.
 * @return    STR_PULSE_TRAIN_SEG *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:17:44
 * @warning
 */
STR_PULSE_TRAIN_SEG *CKMakeAET::GetPulseSeg()
{
	return m_pKnownSigAnal->GetPulseSeg();
}

/**
 * @brief     STR_EMITTER 데이터 구조체 포인터를 리턴합니다.
 * @return    STR_EMITTER *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:17:47
 * @warning
 */
STR_EMITTER *CKMakeAET::GetEmitter()
{
    return m_pKnownSigAnal->GetEmitter();
}

/**
 * @brief     주파수 중간값을 계산하여 리턴합니다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-05-09 14:59:01
 * @warning
 */
UINT CKMakeAET::CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg )
{
	return m_pKnownSigAnal->MedianFreq( NULL, pSeg->stPDW.pIndex, pSeg->stPDW.uiCount );
}

/**
 * @brief     LOB 데이터의 주파수 정보를 업데이트 합니다.
 * @param     SRxLOBData * pUpdAetFrq
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-11-03 11:25:01
 * @warning
 */
void CKMakeAET::UpdateFreq( SRxLOBData *pUpdAetFrq )
{
    //STR_FRQ *pTrkAetFrq;

    //pTrkAetFrq = & stTrkAet.aet.frq;
    if( m_pTrkABT->vFreqType != pUpdAetFrq->vFreqType ) {
        switch( m_pTrkABT->vFreqType ) {
            case _HOPPING :
                pUpdAetFrq->vFreqType = m_pTrkABT->vFreqType;
                pUpdAetFrq->vFreqPatternType = m_pTrkABT->vFreqPatternType;
                pUpdAetFrq->fFreqPatternPeriod = m_pTrkABT->fFreqPatternPeriodMean;
                pUpdAetFrq->fFreqMean = m_pTrkABT->fFreqMean;
                pUpdAetFrq->fFreqMax = m_pTrkABT->fFreqMax;
                pUpdAetFrq->fFreqMin = m_pTrkABT->fFreqMin;
                pUpdAetFrq->fFreqDeviation = m_pTrkABT->fFreqDeviation;
                pUpdAetFrq->vFreqPositionCount = (unsigned char) m_pTrkABT->vFreqPositionCount;
                pUpdAetFrq->vFreqElementCount = ( unsigned char ) m_pTrkABT->vFreqElementCount;
                memcpy( pUpdAetFrq->fFreqSeq, m_pTrkABT->fFreqSeq, sizeof( m_pTrkABT->fFreqSeq ) );
				break;

			case _RANDOM_AGILE :
                pUpdAetFrq->vFreqType = m_pTrkABT->vFreqType;
				break;

			case _PATTERN_AGILE :
                pUpdAetFrq->vFreqType = _PATTERN_AGILE;
                pUpdAetFrq->fFreqPatternPeriod = m_pTrkABT->fFreqPatternPeriodMean;
                pUpdAetFrq->vFreqPatternType = m_pTrkABT->vFreqPatternType;
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
    if( m_pTrkABT->vPRIType != (int) pUpdAetPri->vPRIType ) {
        switch( m_pTrkABT->vPRIType ) {
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
 * @brief     LOB 데이터를 출력한다.
 * @param     SRxLOBData * pLOB
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-09, 14:00
 * @warning
 */
void CKMakeAET::DISP_FineLOB( SRxLOBData *pLOB )
{
    return m_pKnownSigAnal->DISP_FineLOB(pLOB);
}

/**
 * @brief CKMakeAET::IsStorePDW
 * @return
 */
unsigned int CKMakeAET::IsStorePDW()
{
    return m_pKnownSigAnal->IsStorePDW();
}


#if defined(_ELINT_) || defined(_XBAND_)
/**
 * @brief     
 * @return    EN_RADARCOLLECTORID
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @author    조철희 (churlhee.jo@lignex1.com)
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
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/22 12:26:33
 * @warning   
 */
// SRxLOBData *CKMakeAET::GetLOBData( int iIndex ) 
// {
// 	return & m_KwnData[iIndex].stLOBData;
// }

/**
 * @brief     
 * @param     struct timespec * pTimeSpec
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 21:45:47
 * @warning   
 */
void CKMakeAET::GetCollectTime( struct timespec *pTimeSpec )
{
	m_pKnownSigAnal->GetCollectTime( pTimeSpec );
}

/**
 * @brief     GetPDWID
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-06, 13:07
 * @warning
 */
unsigned int CKMakeAET::GetPDWID() 
{ 
    return m_pKnownSigAnal->GetPDWID(); 
}

/**
 * @brief     GetOpInitID
 * @return    LONG
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-25, 14:45
 * @warning
 */
UINT CKMakeAET::GetOpInitID()
{
	return m_pKnownSigAnal->GetOpInitID();
}

