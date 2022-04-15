// CCollectBank.cpp: implementation of the CCollectBank class.
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
 * @brief CCollectBank::CCollectBank
 */
CCollectBank::CCollectBank( int iTotalChannels, int iChannelNo )
    :m_iTotalChannels(iChannelNo),
     m_iChannelNo(iChannelNo)
{

    Init();

	m_strPDW.pstPDW = NULL;
	_SAFE_MALLOC( m_strPDW.pstPDW, _PDW, sizeof(_PDW) * MAX_PDW );
    //m_strPDW.pstPDW = ( _PDW * ) malloc( sizeof(_PDW) * MAX_PDW );

}

/**
 * @brief CCollectBank::~CCollectBank
 */
CCollectBank::~CCollectBank()
{
	_SAFE_FREE( m_strPDW.pstPDW )
}

/**
 * @brief 媛앹껜 珥덇린?붾? ?섑뻾?쒕떎.
 */
void CCollectBank::Init()
{
    memset( & m_strPDW, 0, sizeof(UNION_HEADER) );

	// ?먯???1?쒕????쒖옉?섍퀬 異붿쟻/?ㅼ틪? 0 遺???쒖옉?쒕떎.
	// ?대젃寃??댁빞 PDWID??1遺??留ㅺ린寃??쒕떎.
    //m_strPDW.SetPDWID( _spOne );

    m_strPDW.SetBoardID( (unsigned int) g_enBoardId );
    m_strPDW.SetBand((unsigned int) g_enBoardId );
    //m_strPDW.x.ps.uiBand = g_enBoardId;

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

    // ?먭? ?앹꽦?섏? ?딆븯?쇰㈃ ?쒕쾲 ?섑뻾?섏뿬 ID瑜???ν븳??
//     if( m_theQueueWindowCellID.Count() == 0 && m_iTotalChannels >= 2 ) {
//         m_theQueueWindowCellID.Init( m_iTotalChannels );
//         for( unsigned int i=0 ; i < m_iTotalChannels ; ++i ) {
//             m_theQueueWindowCellID.Push( i );
//         }
//     }
// 
//     m_theQueueWindowCellID.Pop( & m_uiID );

    m_strPDW.x.ps.iBank = CCommonUtils::GetEnumCollectBank( m_iChannelNo );

}

/**
 * @brief CCollectBank::SetWindowCell
 * @param pSTR_WINDOWCELL
 */
void CCollectBank::SetWindowCell( STR_WINDOWCELL *pSTR_WINDOWCELL )
{
    LOGENTRY;

    memcpy( & m_strWindowCell, pSTR_WINDOWCELL, sizeof(STR_WINDOWCELL) );
    g_pTheSysConfig->SetWindowCell( m_iChannelNo, & m_strWindowCell );
}

/**
 * @brief 수집 뱅크를 닫는다.
 */
void CCollectBank::CloseCollectBank()
{
    LOGENTRY;

    // 援ъ“泥?珥덇린???쒕떎.
    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );
    m_strWindowCell.bUse = false;
    m_strWindowCell.enCollectMode = enUnused;

    m_strPDW.SetTotalPDW( 0 );

    g_pTheSysConfig->SetWindowCell( m_iChannelNo, & m_strWindowCell );

}

/**
 * @brief CCollectBank::UpdateWindowCell
 */
void CCollectBank::UpdateWindowCell( STR_WINDOWCELL *pstrWindowCell )
{

    /**
    * @brief 理쒕? ?섏쭛 寃뚯닔 諛??섏쭛 ?쒓컙
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
 * @brief CCollectBank::CloseTrackWindowCell
 * @param pstrWindowCell
 */
void CCollectBank::CloseTrackWindowCell()
{
    m_strWindowCell.bUse = false;

    m_strWindowCell.enCollectMode = enUnused;

    g_pTheSysConfig->SetWindowCell( m_iChannelNo, & m_strWindowCell );
}

/**
 * @brief CSignalCollect::IsValidChannle
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
//     // PDW ?뺣낫 蹂듭궗
//     UINT uiTo;
//     if( iTo > 0 ) {
//         uiTo = (unsigned int) iTo * sizeof(_PDW);
// 
//         memcpy( & m_strPDW.stPDW[m_strPDW.uiTotalPDW], & pPDWData->stPDW[0], uiTo );
//     }    
// 
//     // 異붿쟻 ?덈룄??? ?뺣낫 ?낅뜲?댄듃
//     UpdateWindowCell();
// 
//     //m_strWindowCell.uiCollectTime = DecodeTOA( m_strPDW.llToa[m_strPDW.uiTotalPDW-1] - m_strPDW.llToa[0] );
// 
//     // ?섏쭛 ?꾨즺 留덊궧??
//     m_strWindowCell.enCollectMode = enCompleteCollection;
// 
// }

/**
 * @brief CCollectBank::SimCollectMode
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

            // 媛쒖닔 鍮꾧탳
            if( uiTotalPDW >= m_strWindowCell.uiMaxCoPDW ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
      
            // ?쒓컙 鍮꾧탳
            else if( TOAmsCNV( msDTOA ) >= m_strWindowCell.uiMaxCollectTimems + ( m_strWindowCell.uiMaxCollectTimesec * 1000 ) ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
            else if( tsDiff.tv_sec >= 60 ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
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
 * @brief CCollectBank::PushPDWData
 * @param pstPDW
 */
void CCollectBank::PushPDWData( _PDW *pstPDW )
{
    unsigned int uiTotalPDW;

    if( m_strWindowCell.bUse == true ) {
        uiTotalPDW = m_strPDW.GetTotalPDW();

        if( uiTotalPDW+1 <= m_strWindowCell.uiMaxCoPDW ) {
            memcpy( & m_strPDW.pstPDW[uiTotalPDW], pstPDW, sizeof(_PDW) );

            ++ uiTotalPDW;
            m_strPDW.SetTotalPDW( uiTotalPDW );

            ++ m_strWindowCell.uiTotalPDW;
        }
        else {
            //printf( "PDW ?곗씠?곌? 苑?李?!!" );
        }
    }

    //SimCollectMode();

}

/**
 * @brief ?덈룄?곗????섏쭛 醫낅즺 ?꾩뿉 ?낅뜲?댄듃 ?쒕떎.
 */
void CCollectBank::UpdateWindowCell()
{

    m_strWindowCell.uiAccumulatedTime += m_strWindowCell.uiCollectTime;

    // ?꾩쟻 ?섏쭛 PDW 媛쒖닔 ?낅뜲?댄듃
    m_strWindowCell.uiAccumulatedCoPDW += m_strWindowCell.uiTotalPDW;

    // ?꾩쟻 ?ъ슜 梨꾨꼸 ?잛닔 ?낅뜲?댄듃
    m_strWindowCell.uiAccumulatedCoUsed += 1;

    m_strWindowCell.enCollectMode = enCollecting;

    // PDW ?뺣낫 ?대━??
    m_strPDW.SetTotalPDW( 0 );

    //m_strPDW.IncPDWID();

    // ?섏쭛??PDW 媛쒖닔 ?낅뜲?댄듃
    m_strWindowCell.uiTotalPDW = 0;

    // ?쒓컙 ?ъ꽕??
    clock_gettime( CLOCK_REALTIME, & m_strWindowCell.tsCollectStart );

    g_pTheSysConfig->SetWindowCell( m_iChannelNo, & m_strWindowCell );

}

/**
 * @brief CCollectBank::IsCompleteCollect
 * @return
 */
bool CCollectBank::IsCompleteCollect()
{
    bool bRet=false;
    struct timespec tsDiff;

    if( m_strWindowCell.bUse == true && m_strWindowCell.enCollectMode == enCollecting ) {
        CCommonUtils::DiffTimespec( & tsDiff, & m_strWindowCell.tsCollectStart );

        // ?섏쭛 ?쒓컙 ?뺤씤
        if( tsDiff.tv_sec > (long) m_strWindowCell.uiMaxCollectTimesec ||
#ifdef _MSC_VER
            ( tsDiff.tv_sec == (long) m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_usec >= (long) m_strWindowCell.uiMaxCollectTimems * 1000 ) ) {
#else
            ( tsDiff.tv_sec == m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_nsec >= m_strWindowCell.uiMaxCollectTimems * 1000000 ) ) {
#endif
            bRet = true;
        }

        // ?섏쭛 媛쒖닔 ?뺤씤
        if( m_strPDW.GetTotalPDW() >= m_strWindowCell.uiMaxCoPDW ) {
            m_strPDW.SetTotalPDW( m_strWindowCell.uiMaxCoPDW );
            bRet = true;
        }
    }

    return bRet;   //m_strWindowCell.enCollectMode == enCompleteCollection;

}

/**
 * @brief CSignalCollect::IsFiltered
 * @param pstPDW
 * @param pWindowCell
 * @return
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
 * @brief     SetCollectUpdateTime
 * @return    void
 * @exception
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-25, 10:46
 * @warning
 */
void CCollectBank::SetCollectUpdateTime()
{
    __time32_t tNow;
    tNow = time( NULL );

    m_strPDW.SetColTime( tNow, 0 );

}