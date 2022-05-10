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
	_SAFE_MALLOC( m_strPDW.pstPDW, _PDW, sizeof(_PDW) * MAX_PDW )

}

/**
 * @brief CCollectBank::~CCollectBank
 */
CCollectBank::~CCollectBank()
{
	_SAFE_FREE( m_strPDW.pstPDW )
}

/**
 * @brief ��ü �ʱ�ȭ�� �����Ѵ�.
 */
void CCollectBank::Init()
{
    memset( & m_strPDW.x, 0, sizeof(UNION_HEADER) );

	// Ž���� 1������ �����ϰ� ����/��ĵ�� 0 ���� �����Ѵ�.
	// �̷��� �ؾ� PDWID�� 1���� �ű�� �ȴ�.
    //m_strPDW.SetPDWID( _spOne );

    m_strPDW.SetBoardID( (unsigned int) g_enBoardId );
    m_strPDW.SetBand((unsigned int) g_enBoardId );

    InitWindowCell();

}

/**
 * @brief     �����켿�� �ʱ�ȭ�Ѵ�.
 * @return    void
 * @exception
 * @author    ��ö�� (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-14, 14:21
 * @warning
 */
void CCollectBank::InitWindowCell()
{
    memset( & m_strWindowCell, 0, sizeof(STR_WINDOWCELL) );

    // ť�� �������� �ʾ����� �ѹ� �����Ͽ� ID�� �����Ѵ�.
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
 * @brief ���� ��ũ�� �ݴ´�.
 */
void CCollectBank::CloseCollectBank()
{
    LOGENTRY;

    // ����ü �ʱ�ȭ �Ѵ�.
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
    * @brief �ִ� ���� �Լ� �� ���� �ð�
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
//     // PDW ���� ����
//     UINT uiTo;
//     if( iTo > 0 ) {
//         uiTo = (unsigned int) iTo * sizeof(_PDW);
// 
//         memcpy( & m_strPDW.stPDW[m_strPDW.uiTotalPDW], & pPDWData->stPDW[0], uiTo );
//     }    
// 
//     // ���� ������ �� ���� ������Ʈ
//     UpdateWindowCell();
// 
//     //m_strWindowCell.uiCollectTime = DecodeTOA( m_strPDW.llToa[m_strPDW.uiTotalPDW-1] - m_strPDW.llToa[0] );
// 
//     // ���� �Ϸ� ��ŷ��.
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

            // ���� ��
            if( uiTotalPDW >= m_strWindowCell.uiMaxCoPDW ) {
                m_strWindowCell.enCollectMode = enCompleteCollection;
            }
      
            // �ð� ��
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
            //printf( "PDW �����Ͱ� �� �� !!" );
        }
    }

    //SimCollectMode();

}

/**
 * @brief �����켿�� ���� ���� �Ŀ� ������Ʈ �Ѵ�.
 */
void CCollectBank::UpdateWindowCell()
{

    m_strWindowCell.uiAccumulatedTime += m_strWindowCell.uiCollectTime;

    // ���� ���� PDW ���� ������Ʈ
    m_strWindowCell.uiAccumulatedCoPDW += m_strWindowCell.uiTotalPDW;

    // ���� ��� ä�� Ƚ�� ������Ʈ
    m_strWindowCell.uiAccumulatedCoUsed += 1;

    m_strWindowCell.enCollectMode = enCollecting;

    // PDW ���� Ŭ����
    m_strPDW.SetTotalPDW( 0 );

    // ������ PDW ���� ������Ʈ
    m_strWindowCell.uiTotalPDW = 0;

    // �ð� �缳��
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

        // ���� �ð� Ȯ��
        if( tsDiff.tv_sec > (long) m_strWindowCell.uiMaxCollectTimesec ||
#ifdef _MSC_VER
            ( tsDiff.tv_sec == (long) m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_usec >= (long) m_strWindowCell.uiMaxCollectTimems * 1000 ) ) {
#else
            ( tsDiff.tv_sec == m_strWindowCell.uiMaxCollectTimesec && tsDiff.tv_nsec >= m_strWindowCell.uiMaxCollectTimems * 1000000 ) ) {
#endif
            bRet = true;
        }

        // ���� ���� Ȯ��
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
 * @author    ��ö�� (churlhee.jo@lignex1.com)
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