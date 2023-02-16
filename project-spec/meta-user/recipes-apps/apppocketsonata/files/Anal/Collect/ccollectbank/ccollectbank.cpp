﻿// CCollectBank.cpp: implementation of the CCollectBank class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <string.h>

#include "../../OFP_Main.h"

using namespace std;

#include <algorithm>

#include "ccollectbank.h"
#include "../DataFile/DataFile.h"

#include "../../../Utils/ccommonutils.h"

#include "../../../Thread/csignalcollect.h"

#include "../../../System/csysconfig.h"

#include "../../../Include/globals.h"

/////////////////////////////////////////////////////////////////////////////////

//Queue<unsigned int> CCollectBank::m_theQueueWindowCellID;

/**
 * @brief     객체 초기화를 수행합니다.
 * @param     int iTotalChannels
 * @param     int iChannelNo
 * @return    
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:46:48
 * @warning
 */
CCollectBank::CCollectBank( int iTotalChannels, int iChannelNo )
    :m_iTotalChannels(iChannelNo),
     m_iChannelNo(iChannelNo)
{

    Init();

	// m_strPDW.pstPDW = NULL;
	m_strPDW.pstPDW = (_PDW *) malloc(sizeof(_PDW) * MAX_PDW);
	if (m_strPDW.pstPDW == NULL) {
		Log(enError, "메모리 할당 에러 !");
	}

}

/**
 * @brief     ~CCollectBank
 * @return    
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:03:25
 * @warning
 */
CCollectBank::~CCollectBank()
{
	_SAFE_FREE( m_strPDW.pstPDW )
}

/**
 * @brief     객체 초기화를 수행한다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:03:34
 * @warning
 */
void CCollectBank::Init()
{
    memset( & m_strPDW.x, 0, sizeof(UNION_HEADER) );

	// 탐지는 1서부터 시작하고 추적/스캔은 0 부터 시작한다.
	// 이렇게 해야 PDWID는 1부터 매기게 된다.
    //m_strPDW.SetPDWID( _spOne );

    //m_strPDW.SetBoardID( (unsigned int) g_enBoardId );
    //m_strPDW.SetBand((unsigned int) g_enBoardId );

    InitWindowCell();

}

/**
 * @brief     윈도우셀을 초기화한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-14, 14:21
 * @warning
 */
void CCollectBank::InitWindowCell()
{
    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );

    // 큐가 생성되지 않았으면 한번 수행하여 ID를 저장한다.
//     if( m_theQueueWindowCellID.Count() == 0 && m_iTotalChannels >= 2 ) {
//         m_theQueueWindowCellID.Init( m_iTotalChannels );
//         for( unsigned int i=0 ; i < m_iTotalChannels ; ++i ) {
//             m_theQueueWindowCellID.Push( i );
//         }
//     }
// 
//     m_theQueueWindowCellID.Pop( & m_uiID );

    unsigned int uiBank = (UINT)CCommonUtils::GetEnumCollectBank(m_iChannelNo);
    m_strPDW.SetBank(uiBank );
    

}

/**
 * @brief     윈도우 셀 설정 ＠?설정합니다.
 * @param     STR_WINDOWCELL * pSTR_WINDOWCELL
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:46:27
 * @warning
 */
void CCollectBank::SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL )
{
    LOGENTRY;

    memcpy( & m_strWindowCell, pSTR_WINDOWCELL, sizeof(STR_WINDOWCELL) );
    g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );
}

/**
 * @brief     수집 뱅크를 닫는다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:35
 * @warning
 */
void CCollectBank::CloseCollectBank()
{
    LOGENTRY;

    // 구조체 초기화 한다.
    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );
    m_strWindowCell.bUse = false;
    m_strWindowCell.enCollectMode = enUnused;

    m_strPDW.SetTotalPDW( 0 );

    g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );

}

/**
 * @brief CCollectBank::UpdateWindowCell
 */
void CCollectBank::UpdateWindowCell( STR_WINDOWCELL *pstrWindowCell )
{

    /**
    * @brief 최대 수집 게수 및 수집 시간
    */
    m_strWindowCell.uiMaxCoPDW = pstrWindowCell->uiMaxCoPDW;
    m_strWindowCell.uiMaxCollectTimesec = pstrWindowCell->uiMaxCollectTimesec;
    m_strWindowCell.uiMaxCollectTimems = pstrWindowCell->uiMaxCollectTimems;

    m_strWindowCell.strAoa = pstrWindowCell->strAoa;
    m_strWindowCell.strFreq = pstrWindowCell->strFreq;
    m_strWindowCell.strPA = pstrWindowCell->strPA;
    m_strWindowCell.strPW = pstrWindowCell->strPW;

    m_strWindowCell.tsCollectStart = pstrWindowCell->tsCollectStart;

    m_strWindowCell.uiCollectTime = pstrWindowCell->uiCollectTime;

    m_strWindowCell.uiABTID = pstrWindowCell->uiABTID;

    // memcpy( & m_strWindowCell, pstrWindowCell, sizeof(STR_WINDOWCELL) );

    m_strWindowCell.bUse = true;

//    if( IsValidChannel() == true ) {
//        m_strWindowCell.enCollectMode = enCollecting;

//    }

    UpdateWindowCell();
}

/**
 * @brief     추적 윈도우셀을 닫는다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:21
 * @warning
 */
void CCollectBank::CloseTrackWindowCell()
{
    m_strWindowCell.bUse = false;

    m_strWindowCell.enCollectMode = enUnused;

    g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );
}

/**
 * @brief     유효 채널을 확인한다.
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:47
 * @warning
 */
bool CCollectBank::IsValidChannel()
{
    bool bRet=true;

    switch( m_strWindowCell.enCollectMode ) {
        case enUnused:
            break;
        case enCollecting:
            bRet = false;
            break;
        case enCompleteCollection:
            break;

        default :
            break;
   }

   if( bRet == false ) {
       printf( "IsValidChannle\n" );
   }

   return bRet;

}

/**
 * @brief CCollectBank::PushPDWData
 * @param pstrArrayPDW
 */
// void CCollectBank::PushPDWData( STR_PDWDATA *pPDWData )
// {
//     int iTo;
// 
//     iTo = (int) ( _MAX_COL_PDW - ( m_strWindowCell.uiTotalPDW + pPDWData->uiTotalPDW ) );
//     if( iTo > 0 ) {
//         iTo = pPDWData->uiTotalPDW;
//         m_strPDW.uiTotalPDW = iTo;
//     }
//     else {
//         iTo = (int) ( _MAX_COL_PDW - m_strWindowCell.uiTotalPDW );
//         m_strPDW.uiTotalPDW = _MAX_COL_PDW;
//     }
// 
//     // PDW 정보 복사
//     UINT uiTo;
//     if( iTo > 0 ) {
//         uiTo = (unsigned int) iTo * sizeof(_PDW);
// 
//         memcpy( & m_strPDW.stPDW[m_strPDW.uiTotalPDW], & pPDWData->stPDW[0], uiTo );
//     }    
// 
//     // 추적 윈도우 셀 정보 업데이트
//     UpdateWindowCell();
// 
//     //m_strWindowCell.uiCollectTime = DecodeTOA( m_strPDW.llToa[m_strPDW.uiTotalPDW-1] - m_strPDW.llToa[0] );
// 
//     // 수집 완료 마킹함.
//     m_strWindowCell.enCollectMode = enCompleteCollection;
// 
// }

/**
 * @brief     채널을 모의하기 위한 함수 입니다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:48:01
 * @warning
 */
void CCollectBank::SimCollectMode()
{
    _TOA msDTOA=0;

    unsigned int uiTotalPDW;

    struct timespec tsDiff;

    switch( m_strWindowCell.enCollectMode ) {
        case enUnused:
            break;

        case enCollecting :
            CCommonUtils::DiffTimespec( & tsDiff, & m_strWindowCell.tsCollectStart );

            uiTotalPDW = GetTotalPDW( );


            if( uiTotalPDW >= _spTwo ) {
                msDTOA = m_strPDW.pstPDW[uiTotalPDW-1].ullTOA - m_strPDW.pstPDW[0].ullTOA;
            }

            // 개수 비교
            if( uiTotalPDW >= m_strWindowCell.uiMaxCoPDW ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
            // 시간 비교
            else if( TOAmsCNV( msDTOA ) >= m_strWindowCell.uiMaxCollectTimems + ( m_strWindowCell.uiMaxCollectTimesec * 1000 ) ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
            else if( tsDiff.tv_sec >= 60 ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
			else {

			}

            if( m_strWindowCell.enCollectMode == enCompleteCollection ) {
                m_strWindowCell.uiTotalPDW = uiTotalPDW;
            }

            //round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) >= uiMaxCollectTimeMSec ) {
            //printf( "[%lld]\n" , round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) );

            //m_strWindowCell.enCollectMode = enCompleteCollection;
            break;

        case enCompleteCollection :
            break;

        case enAnalysing :
            break;

        default :
            break;
    }

}

/**
 * @brief     _PDW 구조체 데이터를 수집뱅크 구조체의 데이터에 삽입한다.
 * @param     _PDW * pstPDW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 14:00
 * @warning
 */
void CCollectBank::PushPDWData( _PDW *pstPDW, UNION_HEADER *pHeader )
{
    unsigned int uiTotalPDW;

    if( m_strWindowCell.bUse == true ) {
        uiTotalPDW = m_strPDW.GetTotalPDW();

        if( uiTotalPDW+1 <= m_strWindowCell.uiMaxCoPDW ) {
            memcpy( &m_strPDW.x, pHeader, sizeof( UNION_HEADER ) );

            memcpy( & m_strPDW.pstPDW[uiTotalPDW], pstPDW, sizeof(_PDW) );

            ++ uiTotalPDW;
            m_strPDW.SetTotalPDW( uiTotalPDW );

            ++ m_strWindowCell.uiTotalPDW;
        }
        else {
            //printf( "PDW 데이터가 꽉 참 !!" );
        }
    }

    //SimCollectMode();

}

/**
 * @brief     윈도우셀을 재설정할 때 사용한다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:48:23
 * @warning
 */
void CCollectBank::UpdateWindowCell()
{

    m_strWindowCell.uiAccumulatedTime += m_strWindowCell.uiCollectTime;

    // 누적 수집 PDW 개수 업데이트
    m_strWindowCell.uiAccumulatedCoPDW += m_strWindowCell.uiTotalPDW;

    // 누적 사용 채널 횟수 업데이트
    m_strWindowCell.uiAccumulatedCoUsed += 1;

    m_strWindowCell.enCollectMode = enCollecting;

    // PDW 정보 클리어
    m_strPDW.SetTotalPDW( 0 );

    // 수집한 PDW 개수 업데이트
    m_strWindowCell.uiTotalPDW = 0;

    // 시간 재설정
    clock_gettime( CLOCK_REALTIME, & m_strWindowCell.tsCollectStart );

    g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );

}

/**
 * @brief     수집 완료됨을 체크한다.
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:01
 * @warning
 */
bool CCollectBank::IsCompleteCollect()
{
    bool bRet=false;
    struct timespec tsDiff;

    if( m_strWindowCell.bUse == true && m_strWindowCell.enCollectMode == enCollecting ) {
        CCommonUtils::DiffTimespec( & tsDiff, & m_strWindowCell.tsCollectStart );

        // 수집 시간 확인
        if( tsDiff.tv_sec > (long) m_strWindowCell.uiMaxCollectTimesec ||
#ifdef _MSC_VER
            ( tsDiff.tv_sec == (long) m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_usec >= (long) m_strWindowCell.uiMaxCollectTimems * 1000 ) ) {
#else
            ( tsDiff.tv_sec == m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_nsec >= m_strWindowCell.uiMaxCollectTimems * 1000000 ) ) {
#endif
            bRet = true;
        }

        // 수집 개수 확인
		unsigned int uiTotalPDW= m_strPDW.GetTotalPDW();

        if(uiTotalPDW >= m_strWindowCell.uiMaxCoPDW ) {
            m_strPDW.SetTotalPDW( m_strWindowCell.uiMaxCoPDW );
            bRet = true;
        }
    }

    return bRet;   //m_strWindowCell.enCollectMode == enCompleteCollection;

}

/**
 * @brief     입력한 PDW 데이터가 윈도우 셀 통과 여부를 문의한다.
 * @param     _PDW * pstPDW
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:48:40
 * @warning
 */
bool CCollectBank::IsFiltered( _PDW *pstPDW )
{
    bool bRet=false;

    if( m_strWindowCell.bUse == true ) {
        bRet = CompMarginDiff<int>( (int)pstPDW->uiFreq, m_strWindowCell.strFreq.iLow, m_strWindowCell.strFreq.iHgh, 10 ) && \
               CompMarginDiff<int>( (int)pstPDW->uiPW, m_strWindowCell.strPW.iLow, m_strWindowCell.strPW.iHgh, 10 );
    }

    return bRet;
}


/**
 * @brief     윈도우셀에 시간 정보를 업데이트 한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-25, 10:46
 * @warning
 */
void CCollectBank::SetCollectUpdateTime()
{
    time_t tNow;
    tNow = time( NULL );

    m_strPDW.SetColTime( tNow, 0 );

}