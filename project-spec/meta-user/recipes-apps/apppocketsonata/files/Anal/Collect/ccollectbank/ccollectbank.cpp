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

extern std::string g_strPCIDrverDirection[en_ELEMENT_PCI_DRIVER];

STR_COLLECT_PCIADDRESS *CCollectBank::m_pstrCollectPCIAddress=NULL;
STR_COLLECT_PCIADDRESS *CCollectBank::m_pstrPreFilterPCIAddress = NULL;

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
CCollectBank::CCollectBank( unsigned int uiDetectChannel, unsigned int uiPreFilterChannel, unsigned int uiTracnChannel, unsigned int uiScanChannel, ENUM_PCI_DRIVER enPCIDriver, const char *pThreadName )
    :m_uiDetectChannel( uiDetectChannel ),
     m_uiPreFilterChannel( uiPreFilterChannel ),
     m_uiTrackChannel( uiTracnChannel ),
     m_uiScanChannel( uiScanChannel ),
     m_uiTotalChannels( uiDetectChannel + uiTracnChannel + uiScanChannel ),
     m_enPCIDriver( enPCIDriver )
{
    SetThreadName( pThreadName );

    // 메모리를 할당 합니다.
    Alloc();

    // 구조체 및 변수를 초기화 합니다.
    Init();

#if 0
    STR_WINDOWCELL strWindowCell;

    strWindowCell.strAOA.iLow = IAOACNVLOW( 100.0 );
    strWindowCell.strAOA.iHigh = IAOACNVHGH( 20.1 );

    strWindowCell.strFreq.iLow = IFRQCNVLOW( 1096.12399 );
    strWindowCell.strFreq.iHigh = IFRQCNVHGH( 1096.39914 );

    strWindowCell.strPA.iLow = IPACNVLOW( -91 );
    strWindowCell.strPA.iLow = IPACNVLOW( -89 );
    strWindowCell.strPA.iLow = IPACNVLOW( 7.32 );
    strWindowCell.strPA.iLow = IPACNVLOW( 7.35 );
    strWindowCell.strPA.iHigh = IPACNVHGH( 7.32 );
    strWindowCell.strPA.iHigh = IPACNVHGH( 7.5 );

    strWindowCell.strPW.iLow = IPWCNVLOW( 3 );
    strWindowCell.strPW.iHigh = IPWCNVHGH( 4 );

#endif

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

    Free();
}

/**
 * @brief     메모리를 할당 합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 11:19:44
 * @warning
 */
void CCollectBank::Alloc()
{
    unsigned int i;
    unsigned int uiStart = 0;

    unsigned int uiDetMemSize=0, uiTrkMemSize = 0, uiScnMemSize = 0;

    STR_WINDOWCELL* pstWindowCell;

    if( m_pstrCollectPCIAddress == NULL ) {
        if( m_uiTotalChannels <= MAX_CHANNELS ) {
            m_pstrCollectPCIAddress = ( STR_COLLECT_PCIADDRESS * ) malloc( sizeof( struct STR_COLLECT_PCIADDRESS ) * m_uiTotalChannels );
            m_pstrPreFilterPCIAddress = ( STR_COLLECT_PCIADDRESS * ) malloc( sizeof( struct STR_COLLECT_PCIADDRESS ) * ( m_uiPreFilterChannel+m_uiDetectChannel ) );
        }
        else {
            Log( enError, "채널 수[%d]를 너무 많게 설정했습니다." , m_uiTotalChannels );
        }

        if( m_pstrCollectPCIAddress != NULL && m_pstrPreFilterPCIAddress != NULL ) {
            // 탐지
            uiStart = 0;
            for( i = 0; i < m_uiDetectChannel; ++ i ) {
                m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_OFFSET = 0x000000 + ( uiStart * sizeof( struct UZPOCKETPDW_PDWWORD ) );
                m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE = DETECT_COLLECTION_MEMORY_SIZE;
                m_pstrCollectPCIAddress[i].enCollectBank = enDetectCollectBank;
                m_pstrCollectPCIAddress[i].uiPARAM_BRAM_WADDR = i;

                uiStart += ( m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE );

                uiDetMemSize += DETECT_COLLECTION_MEMORY_SIZE * sizeof( struct UZPOCKETPDW_PDWWORD );
            }

            // 전처리 필터
            for( i = m_uiDetectChannel; i < m_uiDetectChannel + m_uiPreFilterChannel; ++ i ) {
                m_pstrPreFilterPCIAddress[i].uiPCI_ANZ_M_OFFSET = 0x000000 + ( uiStart * sizeof( struct UZPOCKETPDW_PDWWORD ) );
                m_pstrPreFilterPCIAddress[i].uiPCI_ANZ_M_SIZE = TRACK_COLLECTION_MEMORY_SIZE;
                m_pstrPreFilterPCIAddress[i].enCollectBank = enDetectCollectBank;
                m_pstrPreFilterPCIAddress[i].uiPARAM_BRAM_WADDR = i;

                uiStart += ( m_pstrPreFilterPCIAddress[i].uiPCI_ANZ_M_SIZE );

                uiDetMemSize += TRACK_COLLECTION_MEMORY_SIZE * sizeof( struct UZPOCKETPDW_PDWWORD );
            }

            // 추적
            uiStart = 0;
            for( i = m_uiDetectChannel ; i < m_uiDetectChannel + m_uiTrackChannel; ++ i ) {
                m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_OFFSET = 0x020000 + ( uiStart * sizeof( struct UZPOCKETPDW_PDWWORD ) );
                m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE = TRACK_COLLECTION_MEMORY_SIZE;
                m_pstrCollectPCIAddress[i].enCollectBank = enTrackCollectBank;
                m_pstrCollectPCIAddress[i].uiPARAM_BRAM_WADDR = i - m_uiDetectChannel;

                uiStart += ( m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE );

                uiTrkMemSize += TRACK_COLLECTION_MEMORY_SIZE * sizeof( struct UZPOCKETPDW_PDWWORD );
            }

            // 스캔
            uiStart = 0;
            for( i = m_uiDetectChannel+ m_uiTrackChannel ; i < m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel; ++ i ) {
                m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_OFFSET = 0x040000 + ( uiStart * sizeof( struct UZPOCKETPDW_PDWWORD ) );
                m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE = SCAN_COLLECTION_MEMORY_SIZE;
                m_pstrCollectPCIAddress[i].enCollectBank = enScanCollectBank;
                m_pstrCollectPCIAddress[i].uiPARAM_BRAM_WADDR = i - ( m_uiDetectChannel + m_uiTrackChannel );

                uiStart += ( m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE );

                uiScnMemSize += SCAN_COLLECTION_MEMORY_SIZE * sizeof( struct UZPOCKETPDW_PDWWORD );

            }

            // 사용자 필터
//             uiStart = 0;
//             for( i = m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel; i < m_uiTotalChannels ; ++ i ) {
//                 m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_OFFSET = uiStart * sizeof( struct UZPOCKETPDW_PDWWORD );
//                 m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE = USER_COLLECTION_MEMORY_SIZE;
//                 m_pstrCollectPCIAddress[i].enCollectBank = enUserCollectBank;
//                 m_pstrCollectPCIAddress[i].uiPARAM_BRAM_WADDR = i;
//
//                 uiStart += ( m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE );
//
//                 uiUsrMemSize += USER_COLLECTION_MEMORY_SIZE * sizeof( struct UZPOCKETPDW_PDWWORD );
//             }

            if( uiDetMemSize > MAX_LOGIC_MEMORY_SIZE || uiTrkMemSize > MAX_LOGIC_MEMORY_SIZE || uiScnMemSize > MAX_LOGIC_MEMORY_SIZE ) {
                Log( enError, "탐지[%d], 추적[%d], 스캔[%d] 에서 로직 메모리를 초과했습니다 ! 담당자에게 문의하세요...", uiDetMemSize / 1024, uiTrkMemSize / 1024, uiScnMemSize / 1024 );
                while( true ) { }
            }


            DisplayPCIAddress();

        }

    }

    if( m_uiTotalChannels <= MAX_CHANNELS ) {
        size_t szSize = CCommonUtils::CheckMultiplyOverflow( ( int ) sizeof( STR_WINDOWCELL * ), (int) m_uiTotalChannels );
        //m_pstrWindowCell = ( STR_WINDOWCELL** ) malloc( sizeof( STR_WINDOWCELL* ) * m_uiTotalChannels );
        m_pstrWindowCell = ( STR_WINDOWCELL ** ) malloc( szSize );
        if( m_pstrWindowCell == NULL ) {
            TRACE( "\n메모리 할당 에러[CCollectBank::m_pstrWindowCell] !" );
            while( true ) {
            }
        }
        else {
            for( i = 0; i < m_uiTotalChannels; ++i ) {
                m_pstrWindowCell[i] = ( STR_WINDOWCELL* ) malloc( sizeof( STR_WINDOWCELL ) );
                if( m_pstrWindowCell[i] == NULL ) {
                    TRACE( "\n메모리 할당 에러[CCollectBank::m_pstrWindowCell] !" );
                    while( true ) {
                    }
                }
                else {
                    pstWindowCell = m_pstrWindowCell[i];

                    // m_strPDW.pstPDW = NULL;
                    pstWindowCell->strPDW.pstPDW = ( UZPOCKETPDW * ) malloc( sizeof( UZPOCKETPDW ) * MAX_PDW );
                    if( pstWindowCell->strPDW.pstPDW == NULL ) {
                        TRACE( "\n메모리 할당 에러[CCollectBank::pstWindowCell->strPDW.pstPDW] !" );
                    }
                    else {
                        // Log( enDebug, "메모리 할당 : WindowCell[%p], PDW[%p], 크기[%d]", m_pstrWindowCell[i], pstWindowCell->strPDW.pstPDW, sizeof( UZPOCKETPDW ) * MAX_PDW );
                    }
                }

            }
        }
    }
    else {
        Log( enError, "채널 수[%d]를 너무 많게 설정했습니다.", m_uiTotalChannels );
    }

    ///////////////////////////////////////////////////////////////////////////////////
    // 채널 번호 초기화

    // 스캔 채널 번호 초기화
    m_theQueueScanChannel.Init( m_uiScanChannel );

    // PCI 핸들러 생성
    m_pThePCI = new CPCIDriver( m_enPCIDriver, GetThreadName() );

}

/**
 * @brief     DisplayPCIAddress
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-12 11:20:07
 * @warning
 */
void CCollectBank::DisplayPCIAddress()
{
    unsigned int i;

    Log( enNormal, "탐지 [%2d 채널/%3d 개]:전처리 [%2d 채널], 추적 [%2d 채널/%3d 개], 스캔 [%2d 채널/%3d 개] 를 할당 했습니다.", m_uiDetectChannel, DETECT_COLLECTION_MEMORY_SIZE, m_uiPreFilterChannel, m_uiTrackChannel, TRACK_COLLECTION_MEMORY_SIZE, m_uiScanChannel, SCAN_COLLECTION_MEMORY_SIZE );
    for( i = 0; i < m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel ; ++i ) {
        Log( enNormal, "[%s/%3u] 시작 베이스 어드레스 [0x%08X], 크기 [0x%08X]", g_szCollectBank[( int ) m_pstrCollectPCIAddress[i].enCollectBank], m_pstrCollectPCIAddress[i].uiPARAM_BRAM_WADDR, m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_OFFSET, m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE );
    }

    for( i = 0; i < m_uiPreFilterChannel; ++i ) {
        // Log( enNormal, "[%s/%3u] 시작 베이스 어드레스 [0x%08X], 크기 [0x%08X]", g_szCollectBank[( int ) m_pstrPreFilterPCIAddress[i].enCollectBank], m_pstrCollectPCIAddress[i].uiPARAM_BRAM_WADDR, m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_OFFSET, m_pstrCollectPCIAddress[i].uiPCI_ANZ_M_SIZE );
    }

}

/**
 * @brief     Free
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 12:07:13
 * @warning
 */
void CCollectBank::Free()
{
    if( m_pstrCollectPCIAddress != NULL ) {
        free( m_pstrCollectPCIAddress );
    }

    if( m_pstrPreFilterPCIAddress != NULL ) {
        free( m_pstrPreFilterPCIAddress );
    }

    free( m_pstrWindowCell );

    delete m_pThePCI;
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
    unsigned int uiCh;

    m_theQueueScanChannel.Reset();

    //for( uiCh = m_uiDetectChannel + m_uiTrackChannel ; uiCh < m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel; ++uiCh ) {
    for( uiCh = m_uiDetectChannel + m_uiTrackChannel ; uiCh <= m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel - 1 ; ++uiCh ) {
        m_theQueueScanChannel.Push( ( int ) uiCh );
    }


    // 객체 관련 멤버 변수 초기화를 수행합니다.
    for( uiCh = 0; uiCh < (unsigned int) m_uiTotalChannels; ++uiCh ) {
        InitWindowCell( uiCh );

    }

    // PCI 핸들 관련 초기화를 수행합니다.
    m_pThePCI->Init();

	// 탐지는 1서부터 시작하고 추적/스캔은 0 부터 시작한다.
	// 이렇게 해야 PDWID는 1부터 매기게 된다.
    //m_strPDW.SetPDWID( _spOne );

    //m_strPDW.SetBoardID( (unsigned int) g_enBoardId );
    //m_strPDW.SetBand((unsigned int) g_enBoardId );

    // InitWindowCell();

}

/**
 * @brief     InitWindowCell
 * @param     unsigned int uiCh
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 14:08:37
 * @warning
 */
void CCollectBank::InitWindowCell( unsigned int uiCh )
{
    STR_WINDOWCELL* pstWindowCell;

    pstWindowCell = GetWindowCell( uiCh );

    pstWindowCell->Init( uiCh );

    ENUM_COLLECTBANK enCollectBank = GetEnumCollectBank( uiCh );

    pstWindowCell->strPDW.SetCollectBank( enCollectBank );
    pstWindowCell->strPDW.SetBoardID( g_enBoardId );
    pstWindowCell->strPDW.SetBand( (unsigned int) g_enBoardId );        // 대역과 보드 ID는 동일한 것으로 합니다.

}

/**
 * @brief     신호 수집을 시작합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 11:26:50
 * @warning
 */
void CCollectBank::StartCollecting()
{
    m_pThePCI->StartCollecting();

}

/**
 * @brief		EndCollecting
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/04 16:33:51
 * @warning
 */
void CCollectBank::EndCollecting()
{
    m_pThePCI->EndCollecting();

}

/**
 * @brief     수집 뱅크를 리턴합니다.
 * @param     unsigned int uiCh
 * @return    ENUM_COLLECTBANK
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 14:02:41
 * @warning
 */
ENUM_COLLECTBANK CCollectBank::GetEnumCollectBank( unsigned int uiGlobalCh ) const
{
    ENUM_COLLECTBANK enCollectBank = enUnknownCollectBank;

    if( uiGlobalCh < m_uiDetectChannel ) {
        enCollectBank = enDetectCollectBank;
    }
    else if( uiGlobalCh < m_uiDetectChannel + m_uiTrackChannel ) {
        enCollectBank = enTrackCollectBank;
    }
    else if( uiGlobalCh < m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel ) {
        enCollectBank = enScanCollectBank;
    }
    else {
        enCollectBank = enUserCollectBank;
    }

    return enCollectBank;
}

/**
 * @brief     윈도우 셀 설정 값을 시작합니다.
 * @param     STR_WINDOWCELL * pSTR_WINDOWCELL
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:46:27
 * @warning
 */
void CCollectBank::StartWindowCell( STR_WINDOWCELL *pstWindowCell )
{
    STR_COLLECT_PCIADDRESS *pSTR_COLLECT_PCIADDRESS;

    // 수집 시간 업데이트
    CCommonUtils::GetCollectTime( & pstWindowCell->tsCollectStart );

    pSTR_COLLECT_PCIADDRESS = & m_pstrCollectPCIAddress[pstWindowCell->uiCh];
    // 적용 플레그
    if( pstWindowCell->enCollectMode == enUnused || pstWindowCell->enCollectMode == enCloseCollection || pstWindowCell->enCollectMode == enUpdateCollecting ) {
        pstWindowCell->bUse = true;
    }
    else {
        Log( enError, "%s 채널[%3d] 관리가 잘못 됐습니다 !" , g_szCollectBank[(unsigned int) pSTR_COLLECT_PCIADDRESS->enCollectBank], pstWindowCell->uiCh );
    }

    // 개수 초기화
    pstWindowCell->uiColPDW = 0;
    pstWindowCell->strPDW.SetTotalPDW( 0 );

    pstWindowCell->SetCollectMode( enCollecting );

    // 전처리 필터 세팅
    m_pThePCI->PreFilterSetting( pstWindowCell, pSTR_COLLECT_PCIADDRESS, m_pstrPreFilterPCIAddress );

    // 전처리 필터 세팅
    m_pThePCI->StartCollecting( pstWindowCell, pSTR_COLLECT_PCIADDRESS );

    //memcpy( & m_strWindowCell, pSTR_WINDOWCELL, sizeof(struct STR_WINDOWCELL) );
    //g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );
}

/**
 * @brief     CloseCollectBanks
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 10:30:00
 * @warning
 */
void CCollectBank::CloseCollectBanks()
{

    Init();

}

/**
 * @brief     CloseCollectingInterrupt
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-20 17:28:11
 * @warning
 */
void CCollectBank::CloseCollectingInterrupt()
{
    EndCollecting();

}

/**
 * @brief     UpdateCollectBank
 * @param     unsigned int uiCh
 * @param     unsigned int uiTotalPDW
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-25 10:55:35
 * @warning
 */
void CCollectBank::UpdateCollectBank( unsigned int uiGlobalCh, unsigned int uiColPDW )
{
    struct timespec tsDiff;

    STR_WINDOWCELL *pstWindowCell = GetWindowCell( uiGlobalCh );

    ENUM_COLLECTBANK enCollectBank = GetEnumCollectBank( uiGlobalCh );

    ///////////////////////////////////////////////////////////////////////////////////
    // 윈도우 셀 개수 저장하기
    pstWindowCell->uiColPDW = uiColPDW;

    ///////////////////////////////////////////////////////////////////////////////////
    // pstWindowCell->bUse = false;

    // 누적 수집 PDW 개수 업데이트
    pstWindowCell->uiAccumulatedCoPDW += uiColPDW;

    // 누적 필터판 사용
    ++pstWindowCell->uiAccumulatedCoUsed;

    // 수집 시간 차 계산
    CCommonUtils::DiffTimespec( & tsDiff, &pstWindowCell->tsCollectStart );

#ifdef _MSC_VER
    Log( enNormal, "[%s] 수집 소요 시간 [%d.%d ms]", g_szCollectBank[( unsigned int ) enCollectBank], tsDiff.tv_sec, tsDiff.tv_usec / 1000 );
#else
    Log( enNormal, "[%s] 수집 소요 시간 [%d.%d ms]", g_szCollectBank[( unsigned int ) enCollectBank], tsDiff.tv_sec, tsDiff.tv_nsec / 1000000 );
#endif

#ifdef _MSC_VER
    pstWindowCell->uiAccumulatedTime += ( unsigned int ) ( ( tsDiff.tv_sec * 1000 ) + ( tsDiff.tv_usec / 1000 ) );
#else
    //printf( "\n [%d.%d]" , tsDiff.tv_sec, tsDiff.tv_nsec );
    pstWindowCell->uiAccumulatedTime = 0;
#endif

    pstWindowCell->SetCollectMode( enUpdateCollecting );

    g_pTheSysConfig->SetWindowCell( ( UINT ) uiGlobalCh, pstWindowCell );

}

/**
 * @brief     탐지/수집/스캔 수집 뱅크를 닫는다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:35
 * @warning
 */
void CCollectBank::CloseCollectBank( unsigned int uiGlobalCh, unsigned int uiColPDW )
{
    struct timespec tsDiff;

    STR_WINDOWCELL *pstWindowCell = GetWindowCell( uiGlobalCh );

    ENUM_COLLECTBANK enCollectBank = GetEnumCollectBank( uiGlobalCh );

    ///////////////////////////////////////////////////////////////////////////////////
    // 윈도우 셀 개수 저장하기
    pstWindowCell->uiColPDW = uiColPDW;

    ///////////////////////////////////////////////////////////////////////////////////
    pstWindowCell->bUse = false;

    // 누적 수집 PDW 개수 업데이트
    pstWindowCell->uiAccumulatedCoPDW += uiColPDW;

    // 수집 시간 차 계산
    CCommonUtils::DiffTimespec( & tsDiff, &pstWindowCell->tsCollectStart, NULL );

#ifdef _MSC_VER
    Log( enNormal, "[%s] 수집 소요 시간 [%d.%d ms]", g_szCollectBank[( unsigned int ) enCollectBank], tsDiff.tv_sec, tsDiff.tv_usec / 1000 );
#else
    Log( enNormal, "[%s] 수집 소요 시간 [%d.%d ms]", g_szCollectBank[(unsigned int)enCollectBank], tsDiff.tv_sec, tsDiff.tv_nsec / 1000000 );
#endif

#ifdef _MSC_VER
    pstWindowCell->uiAccumulatedTime += (unsigned int) ( ( tsDiff.tv_sec * 1000 ) + ( tsDiff.tv_usec / 1000 ) );
#else
    pstWindowCell->uiAccumulatedTime += ( unsigned int ) ( ( tsDiff.tv_sec * 1000 ) + ( tsDiff.tv_nsec / 1000 ) );
#endif

    pstWindowCell->SetCollectMode( enCloseCollection );

    // 추적 채널일 때만 전처리 설정과 문을 닫습니다.
    if( enCollectBank == enTrackCollectBank ) {
        // 전처리 필터를 닫습니다.
        m_pThePCI->PreFilterClose( pstWindowCell, & m_pstrPreFilterPCIAddress[pstWindowCell->uiCh] );
        WhereIs;

        // 전처리 필터를 닫습니다.
        m_pThePCI->CloseChannel( uiGlobalCh, enCollectBank, & m_pstrCollectPCIAddress[uiGlobalCh] );
    }

    // 스캔 채널을 닫습니다.
    else if( enCollectBank == enScanCollectBank ) {
        // 채널을 재사용하도록 큐에 삽입한다.
        m_theQueueScanChannel.Push( (int) uiGlobalCh );

        m_pThePCI->CloseChannel( uiGlobalCh, enCollectBank, & m_pstrCollectPCIAddress[uiGlobalCh] );
    }
    else {

    }

    g_pTheSysConfig->SetWindowCell( (UINT) uiGlobalCh, pstWindowCell );

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
//     m_strWindowCell.bUse = false;
//
//     m_strWindowCell.enCollectMode = enUnused;
//
//     g_pTheSysConfig->SetWindowCell( (UINT) m_iChannelNo, & m_strWindowCell );
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

//     switch( m_strWindowCell.enCollectMode ) {
//         case enUnused:
//             break;
//         case enCollecting:
//             bRet = false;
//             break;
//         case enCompleteCollection:
//             break;
//
//         default :
//             break;
//    }
//
//    if( bRet == false ) {
//        printf( "IsValidChannle\n" );
//    }

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
//         uiTo = (unsigned int) iTo * sizeof(struct _PDW);
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
 * @brief     수집 완료됨을 체크한다.
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:47:01
 * @warning
 */
bool CCollectBank::IsCompleteCollect( unsigned int uiCh )
{
    // bool bRet;// = false;
    //struct timespec tsDiff;

    STR_WINDOWCELL *pWindowCell = GetWindowCell( uiCh );

//     if( pWindowCell->bUse == true && pWindowCell->enCollectMode == enCollecting ) {
//         CCommonUtils::DiffTimespec( & tsDiff, &pWindowCell->tsCollectStart );
//
//         // 수집 시간 확인
//         if( tsDiff.tv_sec > (long) pWindowCell->uiMaxCollectTimesec ||
// #ifdef _MSC_VER
//         ( tsDiff.tv_sec == (long) pWindowCell->uiMaxCollectTimesec && tsDiff.tv_usec >= (long) pWindowCell->uiMaxCollectTimems * 1000 ) ) {
// #else
//         ( tsDiff.tv_sec == pWindowCell->uiMaxCollectTimesec && tsDiff.tv_nsec >= pWindowCell->uiMaxCollectTimems * 1000000 ) ) {
// #endif
//             bRet = true;
//         }
//
//         // 수집 개수 확인
//         unsigned int uiTotalPDW= GetPDWData(uiCh)->GetTotalPDW();
//
//         if(uiTotalPDW >= pWindowCell->uiCoCollectingPDW ) {
//             GetPDWData(uiCh)->SetTotalPDW( pWindowCell->uiCoCollectingPDW );
//             bRet = true;
//         }
//     }

    return pWindowCell->enCollectMode == enCompleteCollection;

}

/**
 * @brief     탐지 채널 수집 정보를 계산하고 수집을 설정합니다.
 * @param     unsigned int uiCh
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-14 10:08:56
 * @warning
 */
void CCollectBank::StartDetectChannel( unsigned int uiCh )
{
    STR_WINDOWCELL *pWindowCell;

    // 윈도우 정보 얻기
    pWindowCell = GetWindowCell( uiCh );

    // 계산하기
    CalDetectWindowCell( pWindowCell );

    // 세팅하기
    StartWindowCell( pWindowCell );

#ifdef _MSC_VER
    // m_pThePCI->ISRRoutine();

#endif

}

/**
 * @brief     탐지 윈도우 셀 정보를 계산합니다.
 * @param     STR_WINDOWCELL * pstWindowCell
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-06 15:31:15
 * @warning
 */
void CCollectBank::CalDetectWindowCell( STR_WINDOWCELL *pstWindowCell )
{
    // pstWindowCell->enCollectMode = enCollecting;

    pstWindowCell->uiCoCollectingPDW = NEW_COLLECT_PDW;

    pstWindowCell->uiMaxCollectTimeMssec = 250;

    pstWindowCell->uiSignalType = FILTER_SIGNALTYPE_ALL;
    pstWindowCell->uiMOPType = FILTER_NO_MOP; // FILTER_ALL_MOP;
    pstWindowCell->uiMOPDir = 0; // FILTER_FMOP_UNKNOWN;

    pstWindowCell->uiAdapt = FILT_ADAPT_ALL; // FILT_ADAPT_FALSE_PDW;
    pstWindowCell->uiByPass = FILT_BYPASS_ALL; //  FILT_BYPASS_FALSE_PDW;

    pstWindowCell->strAOA.iLow = 0;
    pstWindowCell->strAOA.iHigh = MAX_AOA_BIT-1;

    pstWindowCell->strFreq.iLow = 0; // IFRQMhzCNV( 0, MIN_FREQ_MHZ );
    pstWindowCell->strFreq.iHigh = MAX_FREQ_BIT-1; // IFRQMhzCNV( 0, MAX_FREQ_MHZ );

    pstWindowCell->strPA.iLow = 0;
    pstWindowCell->strPA.iHigh = MAX_PA_BIT;

    pstWindowCell->strPW.iLow = 0;
    pstWindowCell->strPW.iHigh = MAX_PW_BIT-1;

    pstWindowCell->uiABTIndex = _spZero;

}

/**
 * @brief     StartTrackChennel
 * @param     SRxABTData * pABTData
 * @param     SRadarMode * pRadarMode
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-19 13:51:53
 * @warning
 */
void CCollectBank::StartTrackChannel( unsigned int uiCh, SRxABTData *pABTData, SRadarMode *pRadarMode, STR_WINDOWCELL_INFO *pstTrackWindowCellInfo )
{
    STR_WINDOWCELL *pWindowCell;

    pWindowCell = GetWindowCell( uiCh );

    CalTrackWindowCell( pWindowCell, pABTData, pRadarMode, pstTrackWindowCellInfo );

    // 세팅하기
    StartWindowCell( pWindowCell );

    Log( enNormal, "추적 : 위협[%d/%d]을 채널[%3d], 방위[%.1f~%.1f 도], 주파수[%d~%d MHz], 시간[%.2f 초]를 설정", \
        pABTData->uiAETID, pABTData->uiABTID, uiCh, FAOACNV( pWindowCell->strAOA.iLow), FAOACNV( pWindowCell->strAOA.iHigh ), \
        UDIV( pWindowCell->strFreq.iLow, 1000 ), UDIV( pWindowCell->strFreq.iHigh, 1000 ), \
        FDIV( pWindowCell->uiMaxCollectTimeMssec, 1000. ) );
    //         Log( enDebug, "\t\t필터 설정 수집 개수\t\t%d [개]", pstrWindowCell->uiCoCollectingPDW );
    //         Log( enDebug, "\t\t필터 설정 수집 시간\t\t%3.2f [초]", FDIV( pstrWindowCell->uiMaxCollectTimeMssec, 1000. ) );
    //         Log( enDebug, "\t\t필터 설정 방위\t\t\t%.1f~%.1f [도]", CPOCKETSONATAPDW::DecodeDOA( pstrWindowCell->strAOA.iLow ), CPOCKETSONATAPDW::DecodeDOA( pstrWindowCell->strAOA.iHigh ) );
    //         Log( enDebug, "\t\t필터 설정 주파수\t\t%d~%d [MHz]", pstrWindowCell->strFreq.iLow, pstrWindowCell->strFreq.iHigh );

}

/**
 * @brief     빔 정보를 보고 추적 윈도우 셀을 계산한다.
              초기에는 빔 관리를 수집에서 했지만 필터 정보는 위협 관리를 확인해야 해서 이를 위협 관리로 이동함.
              나머지 수집개수 및 시간은 기존대로 신호 수집에서 결정함. 데이터 충돌 방지를 위해서 나눔.
              횃갈리려나... ?
 * @param     STR_WINDOWCELL * pstrWindowCell
 * @param     SRxABTData * pABTData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-24, 17:40
 * @warning
 */
void CCollectBank::CalTrackWindowCell( STR_WINDOWCELL *pstWindowCell, SRxABTData *pABTData, SRadarMode *pRadarMode, STR_WINDOWCELL_INFO *pstTrackWindowCellInfo )
{
    UINT uiCollectTime;

    float fMinCollectTime = 0;

    if( pstWindowCell != NULL ) {
#if 0
        pstrWindowCell->uiABTID = pABTData->uiABTID;

        pstrWindowCell->strAOA.iLow = ( int ) ( ( IAOACNV( pABTData->fDOAMin - 10 ) + MAX_AOA_BIT ) % MAX_AOA_BIT );
        pstrWindowCell->strAOA.iHigh = ( int ) ( ( IAOACNV( pABTData->fDOAMax + 10 ) + MAX_AOA_BIT ) % MAX_AOA_BIT );


        // 레이더모드 식별 경우에 식별 정보를 이용하여 주파수 및 펄스폭을 설정
        if( pRadarMode != NULL ) {
            pstrWindowCell->strFreq.iLow = ( int ) CPOCKETSONATAPDW::EncodeFREQMHz( pRadarMode->fRF_TypicalMin );
            pstrWindowCell->strFreq.iHigh = ( int ) CPOCKETSONATAPDW::EncodeFREQMHz( pRadarMode->fRF_TypicalMax );

            pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
            pstrWindowCell->strPW.iHigh = IPWCNVHGH( pABTData->fPWMax );

            fMinCollectTime = max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {
            pstrWindowCell->strFreq.iLow = ( int ) CPOCKETSONATAPDW::EncodeFREQMHz( pABTData->fFreqMin - 5 );
            pstrWindowCell->strFreq.iHigh = ( int ) CPOCKETSONATAPDW::EncodeFREQMHz( pABTData->fFreqMax + 5 );

#ifdef _XBAND_
            fMinCollectTime = ( float ) 10.0;
#else
            fMinCollectTime = pABTData->fMaxScanPeriod;
#endif
        }

        pstrWindowCell->strPA.iLow = 0;
        pstrWindowCell->strPA.iHigh = PDW_PA_MAX;

        pstrWindowCell->strPW.iLow = IPWCNVLOW( pABTData->fPWMin );
        pstrWindowCell->strPW.iHigh = IPWCNVHGH( pABTData->fPWMax );


        pstrWindowCell->uiCoCollectingPDW = KWN_COLLECT_PDW;

        uiCollectTime = max( 5000, UDIV( fMinCollectTime, 1000 ) );
        //pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
        pstrWindowCell->uiMaxCollectTimeMssec = uiCollectTime;

#else
        // 빔 정보 설정
        pstWindowCell->uiABTID = pABTData->uiABTID;

        ///////////////////////////////////////////////////////////////////////////////////
        //
        pstWindowCell->uiByPass = FILT_BYPASS_ALL;
        pstWindowCell->uiAdapt = FILT_ADAPT_AOA | FILT_ADAPT_FRQ; //  FILT_ADAPT_AOA | FILT_ADAPT_FRQ | FILT_ADAPT_PW | FILT_ADAPT_PA | FILT_ADAPT_MOP | FILT_ADAPT_FALSE_PDW;

        pstWindowCell->uiMOPType = 0;
        pstWindowCell->uiMOPDir = 0;

        // 펄스 상태 설정
        pstWindowCell->uiSignalType = pstTrackWindowCellInfo->uiSignalType;

        // 수집 필터 범위 설정
        pstWindowCell->strAOA.iLow = (int) IAOACNVLOW( pstTrackWindowCellInfo->strAOA.fLow );
        pstWindowCell->strAOA.iHigh = ( int ) IAOACNVHGH( pstTrackWindowCellInfo->strAOA.fHigh );

        pstWindowCell->strFreq.iLow = IFRQCNVLOW( pstTrackWindowCellInfo->strFreq.fLow );
        pstWindowCell->strFreq.iHigh = IFRQCNVHGH( pstTrackWindowCellInfo->strFreq.fHigh );

        pstWindowCell->strPA.iLow = ( int ) IPACNVLOW( pstTrackWindowCellInfo->strPA.fLow );
        pstWindowCell->strPA.iHigh = ( int ) IPACNVHGH( pstTrackWindowCellInfo->strPA.fHigh );

        pstWindowCell->strPW.iLow = IPWCNVLOW( pstTrackWindowCellInfo->strPW.fLow );
        pstWindowCell->strPW.iHigh = IPWCNVHGH( pstTrackWindowCellInfo->strPW.fHigh );

        // 수집 시간 설정
        if( pRadarMode != NULL ) {
            fMinCollectTime = max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax );
        }
        else {

#ifdef _XBAND_
            fMinCollectTime = ( float ) 10.0;
#else
            fMinCollectTime = pABTData->fMaxScanPeriod;
#endif
        }


        // 1. 수집 개수 계산합니다.
        pstWindowCell->uiCoCollectingPDW = CalTrackCollecingPDW( pABTData );

        // 2. 수집 시간 계산합니다.
        uiCollectTime = max( (unsigned int) 5000, UDIV( fMinCollectTime, 1000 ) );
        //pstrWindowCell->uiMaxCollectTimesec = UDIV( uiCollectTime, 1000 );
        pstWindowCell->uiMaxCollectTimeMssec = uiCollectTime;
#endif

    }
    else {

    }
}

/**
 * @brief     CalTrackCollecingPDW
 * @param     SRxABTData * pABTData
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-13 13:52:37
 * @warning
 */
unsigned int CCollectBank::CalTrackCollecingPDW( SRxABTData *pABTData )
{
    unsigned int uiCoCollectingPDW = KWN_COLLECT_PDW;

    // TODO : 위협 레이더 특성에 따라서 펄스 개수를 조정 해야 함.

/*
    switch( pABTData->vPRIType ) {
        case ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED:
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH:
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER:
            if( pABTData->vPRIPositionCount > 20 ) {
                uiCoCollectingPDW = KWN_COLLECT_PDW;
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN:
            break;

        default:
            break;
    }       */

    return uiCoCollectingPDW;

}

/**
 * @brief     스캔 윈도우 셀 정보를 계산합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 11:54:25
 * @warning
 */
int CCollectBank::StartScanChennel( SRxABTData *pABTData, SRadarMode *pRadarMode, unsigned int uiReqScanPeriod, unsigned int uiScanStep, STR_SCANRESULT *pstScanResult )
{
    int iCh=0;

    STR_WINDOWCELL *pWindowCell;

    bool bRet = m_theQueueScanChannel.Pop( & iCh );

    if( bRet == true ) {
        // 윈도우 정보 얻기
        pWindowCell = GetWindowCell( (unsigned int) iCh );

        // 계산하기
        CalScanWindowCell( pWindowCell, pABTData, pRadarMode, uiReqScanPeriod, uiScanStep, pstScanResult );

        // 세팅하기
        StartWindowCell( pWindowCell );

        Log( enNormal, "스캔 : 위협[%d/%d]을 채널[%3d], 방위[%d~%d 도], 주파수[%d~%d MHz], 세기[%.1f~%.1f dBm], 시간[%.2f 초]를 스캔 설정", \
            pABTData->uiAETID, pABTData->uiABTID, iCh, UDIV( pWindowCell->strAOA.iLow, 10 ), UDIV( pWindowCell->strAOA.iHigh, 10 ), \
            UDIV(pWindowCell->strFreq.iLow, 1000), UDIV(pWindowCell->strFreq.iHigh, 1000), \
            CPOCKETSONATAPDW::DecodePA( pWindowCell->strPA.iLow), CPOCKETSONATAPDW::DecodePA( pWindowCell->strPA.iHigh), \
            FDIV( pWindowCell->uiMaxCollectTimeMssec, 1000. ) );

//         Log( enDebug, "\t\t필터 설정 수집 개수\t\t%d [개]", pstrWindowCell->uiCoCollectingPDW );
//         Log( enDebug, "\t\t필터 설정 수집 시간\t\t%3.2f [초]", FDIV( pstrWindowCell->uiMaxCollectTimeMssec, 1000. ) );
//         Log( enDebug, "\t\t필터 설정 방위\t\t\t%.1f~%.1f [도]", CPOCKETSONATAPDW::DecodeDOA( pstrWindowCell->strAOA.iLow ), CPOCKETSONATAPDW::DecodeDOA( pstrWindowCell->strAOA.iHigh ) );
//         Log( enDebug, "\t\t필터 설정 주파수\t\t%d~%d [MHz]", pstrWindowCell->strFreq.iLow, pstrWindowCell->strFreq.iHigh );


    }
    else {
        Log( enDebug, "스캔 수집할 채널이 없습니다 ! 스캔 대기 큐에 [%d]개가 대기하고 있습니다.", m_theQueueScanChannel.Count() );

        // 현재 점유 중인 스캔 채널 정보를 보여줍니다.
        ShowAllScanCahennelInfo();

        iCh = -1;

    }

    return iCh;

}

/**
 * @brief     ShowScanCahennelInfo
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 12:10:23
 * @warning
 */
void CCollectBank::ShowAllScanCahennelInfo()
{
    unsigned int uiCh;
    STR_WINDOWCELL *pstrWindowCell;

    Log( enDebug, "[%s]의 스캔 수집 정보를 보여줍니다." , g_strPCIDrverDirection[(int)m_enPCIDriver].c_str() );

    for( uiCh = m_uiDetectChannel + m_uiTrackChannel ; uiCh < m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel ; ++uiCh ) {
        pstrWindowCell = GetWindowCell( uiCh );

        ShowScanCahennelInfo( pstrWindowCell );

    }

}

/**
 * @brief     ShowScanCahennelInfo
 * @param     STR_WINDOWCELL * pstrWindowCell
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-17 14:43:49
 * @warning
 */
void CCollectBank::ShowScanCahennelInfo( STR_WINDOWCELL *pstrWindowCell )
{
#ifdef __VXWORKS__
    char szApply[2][10] = { "미적용", "적용" };
    char g_szCollectMode[enAnalysing + 1][20] = { "미사용", "수집중", "수집완료", "수집닫기", "분석중" };

    Log( enDebug, "[%d] 스캔 채널 ------------------------------------", pstrWindowCell->uiCh-m_uiDetectChannel-m_uiTrackChannel );
    Log( enDebug, "\t\t사용 여부\t\t\t\t%s", szApply[(unsigned int) pstrWindowCell->bUse] );
    Log( enDebug, "\t\t수집 상태\t\t\t\t%s", g_szCollectMode[( unsigned int ) pstrWindowCell->enCollectMode] );

#ifdef _MSC_VER
    Log( enDebug, "\t\t수집중인 개수\t\t\t%d [개]", pstrWindowCell->uiColPDW );
#endif

    Log( enDebug, "\t\t필터 설정 수집 개수\t\t%d [개]", pstrWindowCell->uiCoCollectingPDW );
    Log( enDebug, "\t\t필터 설정 수집 시간\t\t%3.2f [초]", FDIV( pstrWindowCell->uiMaxCollectTimeMssec, 1000. ) );
    Log( enDebug, "\t\t필터 설정 방위\t\t\t%.1f~%.1f [도]", CPOCKETSONATAPDW::DecodeDOA(pstrWindowCell->strAOA.iLow), CPOCKETSONATAPDW::DecodeDOA( pstrWindowCell->strAOA.iHigh ) );
    Log( enDebug, "\t\t필터 설정 주파수\t\t%d~%d [MHz]", pstrWindowCell->strFreq.iLow, pstrWindowCell->strFreq.iHigh );
    Log( enDebug, "\t\t누적 수집 개수\t\t\t%d [개]", pstrWindowCell->uiAccumulatedCoPDW );
    Log( enDebug, "\t\t연관 빔 번호\t\t\t%d", pstrWindowCell->uiABTID );
    //Log( enDebug, "\t\t스캔 수집 단계\t\t\t%d [단계]", pstrWindowCell->uiScanStep );

    Log( enLineFeed, "" );
#endif

}

/**
 * @brief		빔 정보를 참조하여 윈도우 셀 정보를 계산합니다.
 * @param		STR_WINDOWCELL * pstrWindowCell
 * @param		SRxABTData * pABTData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/23 10:23:43
 * @warning
 */
void CCollectBank::CalScanWindowCell( STR_WINDOWCELL *pstWindowCell, SRxABTData *pABTData, SRadarMode *pRadarMode, unsigned int uiReqScanPeriod, unsigned int uiScanStep, STR_SCANRESULT *pstScanResult )
{

    if( pstWindowCell != NULL ) {
        pstWindowCell->uiABTID = pABTData->uiABTID;

        pstWindowCell->uiSignalType = MakeSignalTypeOfWindowCell( pABTData );
        pstWindowCell->uiSignalType = FILTER_SIGNALTYPE_ALL;
        pstWindowCell->uiMOPType = FILTER_NO_MOP; // FILTER_ALL_MOP;
        pstWindowCell->uiMOPDir = 0; // FILTER_FMOP_UNKNOWN;

        pstWindowCell->uiByPass = FILT_BYPASS_ALL; //  FILT_BYPASS_FALSE_PDW;
        pstWindowCell->uiAdapt = FILT_ADAPT_AOA | FILT_ADAPT_FRQ; // FILT_ADAPT_FALSE_PDW;

        // 레이더모드 식별 경우에 식별 정보를 이용하여 주파수 및 펄스폭을 설정
        if( pRadarMode != NULL ) {
            if( CCommonUtils::IsValidMinMax( pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax ) ) {
                pstWindowCell->strFreq.iLow = ( int ) IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMin );
                pstWindowCell->strFreq.iHigh = ( int ) IFRQMhzCNV( 0, pRadarMode->fRF_TypicalMax );
            }
            else {
                pstWindowCell->strFreq.iLow = ( int ) IFRQMhzCNV( 0, pABTData->fFreqMin );
                pstWindowCell->strFreq.iHigh = ( int ) IFRQMhzCNV( 0, pABTData->fFreqMax );
            }

            if( CCommonUtils::IsValidMinMax( pRadarMode->fPD_TypicalMin, pRadarMode->fPD_TypicalMax ) ) {
                pstWindowCell->strPW.iLow = IPWCNVLOW( pRadarMode->fPD_TypicalMin );
                pstWindowCell->strPW.iHigh = IPWCNVHGH( pRadarMode->fPD_TypicalMax );
            }
            else {
                pstWindowCell->strPW.iLow = 0; // IPWCNVLOW( pABTData->fPWMin );
                pstWindowCell->strPW.iHigh = IPWCNVHGH( pABTData->fPWMax );
            }

            //?     2차 후보 스캔을 고려해서 이 부분을 위협관리로 옮겨야 함.
            //date 	2023-04-14 09:29:39
//             if( is_zero<float>( pRadarMode->fScanPrimaryTypicalMax ) != true ) {
//                 uiCollectTimems = UMUL( max( pRadarMode->fScanPrimaryTypicalMax, pRadarMode->fScanSecondaryTypicalMax ), 1000 );
//             }
        }
        else {
            if( pABTData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED ) {
                pstWindowCell->strFreq.iLow = ( int) IFRQMhzCNV( 0, pABTData->fFreqMin - (float) 1.0 );
                pstWindowCell->strFreq.iHigh = ( int ) IFRQMhzCNV( 0, pABTData->fFreqMax + (float) 1.0 );
            }
            else {
                pstWindowCell->strFreq.iLow = ( int ) IFRQMhzCNV( 0, pABTData->fFreqMin - ( float ) 5.0 );
                pstWindowCell->strFreq.iHigh = ( int ) IFRQMhzCNV( 0, pABTData->fFreqMax + ( float ) 5.0 );
            }

            pstWindowCell->strPW.iLow = 0; //  IPWCNVLOW( pABTData->fPWMin );
            pstWindowCell->strPW.iHigh = IPWCNVHGH( pABTData->fPWMax );

#ifdef _XBAND_

#else
//             if( is_zero<float>(pABTData->fMeanScanPeriod ) != true ) {
//                 uiCollectTimems = UMUL( pABTData->fMeanScanPeriod, 1000. );
//             }

#endif
        }

        // 시간 정보가 0 일때, 일반적인 스캔 수집 시간으로 설정합니다.
//         if( uiCollectTimems == 0 ) {
//             uiCollectTimems = UMUL( uiReqScanPeriod, 2.5 ); // m_uiScanCollectionTimems[uiScanStep];
//         }

        // 펄스폭 설정
        pstWindowCell->strPW.iLow = 0;
        pstWindowCell->strPW.iHigh = MAX_PW_BIT - 1;

        // 방위 설정
        pstWindowCell->strAOA.iLow = ( int ) ( ( IAOACNV( ( float ) ( pABTData->fDOAMin - 10. ) ) + PDW_DOA_MAX ) % PDW_DOA_MAX );
        pstWindowCell->strAOA.iHigh = ( int ) ( ( IAOACNV( ( float ) ( pABTData->fDOAMax + 10. ) ) + PDW_DOA_MAX ) % PDW_DOA_MAX );

        CheckScanPAFilter( & pstWindowCell->strPA, pABTData, uiReqScanPeriod, uiScanStep, pstScanResult );

        pstWindowCell->uiCoCollectingPDW = SCN_COLLECT_PDW;

        pstWindowCell->uiMaxCollectTimeMssec = UMUL( uiReqScanPeriod, 2.5 );

        pstWindowCell->uiReqScanPeriod = uiReqScanPeriod;
        pstWindowCell->uiScanStep = uiScanStep;

    }
    else {

    }
}

/**
 * @brief     CheckScanPAFilter
 * @param     STR_LOWHIGH * pstrPA
 * @param     unsigned int uiScanStep
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-18 10:33:41
 * @warning
 */
void CCollectBank::CheckScanPAFilter( STR_LOWHIGH *pstrPA, SRxABTData *pABTData, unsigned int uiReqScanPeriod, unsigned int uiScanStep, STR_SCANRESULT *pstScanResult )
{
    // 신호세기 최소값 설정
    // 첫번째 스캔 신호 수집은 PA 최소값을 0 으로 해서 수집합니다.
    if( uiScanStep == 0 ) {
        pstrPA->iLow = 0;              // ( int ) IPACNV( PDW_PA_DB_MIN );

    }
    // 두 번째 이상 부터는, PA 최소값을 잡음 이상의 신호에서 설정하도록 한다.
    else {

        if( IsFullOfCollecting( pstScanResult->fCoScanCollectingPDW ) && !IsFullOfDuration( pstScanResult->fScanDurationms ) ) {
            pstrPA->iLow = (int) pstScanResult->uiMedianPA;
        }
        else {
            pstrPA->iLow = ( int ) IPACNV( ( float ) pABTData->fPAMin );
        }
        pstrPA->iLow = pstrPA->iLow + 5;
    }

    Log( enNormal, "스캔 신호 세기 최소값[%.1f]으로 설정합니다.", CPOCKETSONATAPDW::DecodePA( pstrPA->iLow ) );

    // 신호세기 최대값 설정
    pstrPA->iHigh = MAX_PA_BIT - 1;

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
void CCollectBank::SetCollectUpdateTime( unsigned int uiCh )
{
    time_t tNow;
    tNow = time( NULL );

    if( tNow > 0 ) {
        GetPDWData(uiCh)->SetColTime( (unsigned int) tNow, 0 );
    }
    else {
        GetPDWData( uiCh )->SetColTime( 0, 0 );
    }

}


// CCollectBank* CCollectBank::GetCollectBank( unsigned int uiCh )
// {
//     CCollectBank* pCCollectBank = NULL;
//
//     if( iCh >= 0 ) {
//         if( iCh < CO_DETECT_CHANNEL )
//             pCCollectBank = m_pTheDetectCollectBank[iCh];
//         else if( iCh < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL )
//             pCCollectBank = m_pTheTrackCollectBank[iCh - CO_DETECT_CHANNEL];
//         else if( iCh < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL + CO_SCAN_CHANNEL )
//             pCCollectBank = m_pTheScanCollectBank[iCh - CO_DETECT_CHANNEL - CO_TRACK_CHANNEL];
//         else
//             pCCollectBank = m_pTheUserCollectBank[iCh - CO_DETECT_CHANNEL - CO_TRACK_CHANNEL - CO_SCAN_CHANNEL];
//     }
//     else {
//         TRACE( "잘못된 채널 번호 입니다." );
//     }
//
//     return pCCollectBank;
//
// }

/**
 * @brief     SaveCollectCahnnelInfo
 * @param     unsigned int uiCh
 * @param     SRxABTData * pABTData
 * @param     unsigned int uiABTINdex
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-23 12:27:17
 * @warning
 */
void CCollectBank::SaveCollectCahnnelInfo( unsigned int uiCh, SRxABTData *pABTData, unsigned int uiABTINdex, unsigned int uiReqScanPeriod, ENUM_ROBUST_ANAL enRobustAnal )
{
    STR_WINDOWCELL *pstrWindowCell;

    pstrWindowCell = GetWindowCell( uiCh );

    ///////////////////////////////////////////////////////////////////////////////////
    // 빔 정보 저장
    //
    // 빔 정보
    memcpy( & pstrWindowCell->stABTData, pABTData, sizeof( struct SRxABTData ) );

    // 1. 위협 인덱스 저장 합니다.
    pstrWindowCell->uiABTIndex = uiABTINdex;

    // 2. 스캔 주기 설정 값을 저장 합니다.
    pstrWindowCell->uiReqScanPeriod = uiReqScanPeriod;

    // 3. 주파수 및 PRI 정밀 분석 플레그를 저장 합니다.
    pstrWindowCell->enRobustAnal = enRobustAnal;

//     // 3. 주파수 정밀 분석 플레그를 저장 합니다.
//     if( enRobustAnal == enFREQ_ROBUST_ANALYSIS || enRobustAnal == enFREQ_PRI_ROBUST_ANALYSIS ) {
//         pstrWindowCell->bFreqDepthAnal = true;
//     }
//     else {
//         pstrWindowCell->bFreqDepthAnal = false;
//     }
//
//     // 4. PRI 정밀 분석 플레그를 저장 합니다.
//     if( enRobustAnal == enPRI_ROBUST_ANALYSIS || enRobustAnal == enFREQ_PRI_ROBUST_ANALYSIS ) {
//         pstrWindowCell->bPRIDepthAnal = true;
//     }
//     else {
//         pstrWindowCell->bPRIDepthAnal = false;
//     }

}

/**
 * @brief     GetPDWData
 * @param     STR_UZPOCKETPDW * pPDWData
 * @param     unsigned int uiCh
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-11 10:53:16
 * @warning
 */
void CCollectBank::GetPDWData( STR_UZPOCKETPDW *pPDWData, unsigned int uiGlobalCh, unsigned int uiTotalPDW )
{
    unsigned int tColTime;
    UINT uiColTimeMs;

    // Log( enDebug, "PDW 데이터 [%d] 개를 갖고 옵니다." , uiTotalPDW );

    //////////////////////////////////////////////////////////////////////////
    // 헤더 정보 저장
    memset( & pPDWData->x, 0, sizeof( UNION_HEADER ) );

    pPDWData->SetTotalPDW( uiTotalPDW );
    pPDWData->SetBoardID( g_enBoardId );
    pPDWData->SetBand( (unsigned int) g_enBoardId );
    pPDWData->SetCollectBank( GetEnumCollectBank( uiGlobalCh ) );

    m_pThePCI->GetPDWData( pPDWData, uiGlobalCh, uiTotalPDW, m_pstrCollectPCIAddress[uiGlobalCh].uiPCI_ANZ_M_OFFSET );

    // 신호 수집 시간 설정
    CCommonUtils::GetCollectTime( & tColTime, & uiColTimeMs );
    pPDWData->SetColTime( tColTime, uiColTimeMs );

}

#ifdef _SIM_PDW_

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
bool CCollectBank::IsFiltered( unsigned int uiCh, _PDW *pstPDW )
{
    bool bRet = false;

    STR_WINDOWCELL *pstrWindowCell;

    pstrWindowCell = m_pstrWindowCell[uiCh];

    ENUM_COLLECTBANK enCollectBank = GetEnumCollectBank( uiCh );

    if( enCollectBank == enTrackCollectBank ) {
        if( pstrWindowCell->bUse == true || ( ( pstrWindowCell->enCollectMode == enCollecting ) || ( pstrWindowCell->enCollectMode == enCompleteCollection ) ) ) {
            bRet = TCompMarginDiff<int>( ( int ) pstPDW->uiFreq, pstrWindowCell->strFreq.iLow, pstrWindowCell->strFreq.iHigh, 0 ) && \
                TCompEncodeDOAMarginDiff<int>( ( int ) pstPDW->uiAOA, pstrWindowCell->strAOA.iLow, pstrWindowCell->strAOA.iHigh ) && \
                TCompMarginDiff<int>( ( int ) pstPDW->uiPA, pstrWindowCell->strPA.iLow, pstrWindowCell->strPA.iHigh, 0 ) && \
                TCompMarginDiff<int>( ( int ) pstPDW->uiPW, pstrWindowCell->strPW.iLow, pstrWindowCell->strPW.iHigh, 0 );
        }
    }
    else {
        if( pstrWindowCell->bUse == true && pstrWindowCell->enCollectMode == enCollecting ) {
            bRet = TCompMarginDiff<int>( ( int ) pstPDW->uiFreq, pstrWindowCell->strFreq.iLow, pstrWindowCell->strFreq.iHigh, 0 ) && \
                   TCompEncodeDOAMarginDiff<int>( ( int ) pstPDW->uiAOA, pstrWindowCell->strAOA.iLow, pstrWindowCell->strAOA.iHigh ) && \
                   TCompMarginDiff<int>( ( int ) pstPDW->uiPA, pstrWindowCell->strPA.iLow, pstrWindowCell->strPA.iHigh, 0 ) && \
                   TCompMarginDiff<int>( ( int ) pstPDW->uiPW, pstrWindowCell->strPW.iLow, pstrWindowCell->strPW.iHigh, 0 );
        }
    }

    return bRet;
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
void CCollectBank::PushPDWData( unsigned int uiCh, _PDW *pstPDW, UNION_HEADER *pHeader )
{
    STR_WINDOWCELL *pWindowCell;

    unsigned int uiTotalPDW;

    pWindowCell = GetWindowCell( uiCh );

    if( pWindowCell->bUse == true ) {
        uiTotalPDW = pWindowCell->strPDW.GetTotalPDW();

        if( uiTotalPDW + 1 <= pWindowCell->uiCoCollectingPDW ) {
            // memcpy( &pWindowCell->strPDW.x, pHeader, sizeof( union UNION_HEADER ) );

#if defined(_POCKETSONATA_) || defined(_712_)
            pWindowCell->strPDW.SavePDWData( uiTotalPDW, pstPDW );

#else
            memcpy( &pWindowCell->strPDW.pstPDW[uiTotalPDW], pstPDW, sizeof( union UZPOCKETPDW ) );

#endif

            ++uiTotalPDW;
            pWindowCell->strPDW.SetTotalPDW( uiTotalPDW );

            ++pWindowCell->uiColPDW;
        }
        else {
            //printf( "PDW 데이터가 꽉 참 !!" );
        }
    }

}

/**
 * @brief     채널을 모의하기 위한 함수 입니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-07-10 12:48:01
 * @warning
 */
void CCollectBank::SimCollectMode( unsigned int uiCh )
{
    _TOA msDTOA = 0;

    unsigned int uiTotalPDW;

    struct timespec tsDiff;

    STR_UZPOCKETPDW *pPocketPDW;

    STR_WINDOWCELL *pWindowCell = GetWindowCell( uiCh );

    switch( pWindowCell->enCollectMode ) {
        case enUnused:
            break;

        case enCollecting:
            uiTotalPDW = GetTotalPDW( uiCh );

            if( uiTotalPDW >= _spTwo ) {
                pPocketPDW = GetPDWData( uiCh );
                msDTOA = pPocketPDW->pstPDW[uiTotalPDW - 1].stHwPdwDataRf.ullTOA - pPocketPDW->pstPDW[0].stHwPdwDataRf.ullTOA;

                // 개수 비교
                if( uiTotalPDW >= pWindowCell->uiCoCollectingPDW ) {
                    pWindowCell->enCollectMode = enCompleteCollection;
                }
                // 시간 비교
                else if( TOAmsCNV( msDTOA ) >= ( double ) pWindowCell->uiMaxCollectTimeMssec ) {
                    pWindowCell->enCollectMode = enCompleteCollection;
                    SetTotalPDW( uiCh, uiTotalPDW - 1 );

                }
                else {
                }

            }
            // PDW 개수가 1개 미만일 때는 시간으로 체크 함.
            else {
                CCommonUtils::DiffTimespec( &tsDiff, &pWindowCell->tsCollectStart );

                if( tsDiff.tv_sec > 10 ) {
                    pWindowCell->enCollectMode = enCompleteCollection;
                }

            }

            if( pWindowCell->enCollectMode == enCompleteCollection ) {
                pWindowCell->uiColPDW = uiTotalPDW;
            }

            //round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) >= uiMaxCollectTimeMSec ) {
            //printf( "[%lld]\n" , round( ( tsNow.tv_nsec - m_strWindowCell.tsCollectStart.tv_nsec ) / 1.0e06 ) );
            //m_strWindowCell.enCollectMode = enCompleteCollection;
            break;

        case enCompleteCollection:
            break;

        case enAnalysing:
            break;

        default:
            break;
    }

}

/**
 * @brief     CheckCollectBank
 * @param     ENUM_COLLECTBANK enCollectBank
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-14 11:56:16
 * @warning
 */
int CCollectBank::CheckCollectBank( ENUM_COLLECTBANK enCollectBank )
{
    int iCh = -1;
    unsigned int uiCh;

    STR_WINDOWCELL *pstWindowCell;

    // 채널을 랜덤 또는 증가/감소 교대로 번갈아 가며 체크한다.
    switch( enCollectBank ) {
        case enDetectCollectBank:
            for( uiCh = 0 ; uiCh < m_uiDetectChannel ; ++uiCh ) {
                if( true == IsCompleteCollect( uiCh ) ) {
                    pstWindowCell = GetWindowCell( uiCh );

                    Log( enDebug, "[%s]에서 탐지 채널[%3d] [%d]개 수집 완료", g_strPCIDrverDirection[(int)m_enPCIDriver].c_str(), uiCh, pstWindowCell->uiColPDW );

                    //pCollectBank->SetCollectMode( ui, enCompleteCollection );
                    SetCollectUpdateTime( uiCh );
                    iCh = ( int ) uiCh;
                    break;
                }
                else {
                    // 아래는 탐지 윈도우셀을 자동 재설정하도록 한다.
    //                     pWindowCell = pCollectBank->GetWindowCell();
                        //pCollectBank->UpdateWindowCell();
                        //SendEndCollect();

                }

            }
            break;

        case enTrackCollectBank :
            for( uiCh = m_uiDetectChannel ; uiCh < m_uiDetectChannel + m_uiTrackChannel ; ++uiCh ) {
                if( true == IsCompleteCollect( uiCh ) ) {
                    pstWindowCell = GetWindowCell( uiCh );

                    // 자동으로 수집 모드를 변경 합니다.
                    // pstWindowCell->SetCollectMode( enUpdateCollecting );

                    Log( enDebug, "[%s]에서 위협[%d/%d] 추적 채널[%3d]에서 [%d]개 수집 완료", g_strPCIDrverDirection[( int ) m_enPCIDriver].c_str(), pstWindowCell->stABTData.uiAETID, pstWindowCell->stABTData.uiABTID, uiCh-m_uiDetectChannel, pstWindowCell->uiColPDW );
                    SetCollectUpdateTime( uiCh );
                    iCh = ( int ) uiCh;
                    break;
                }
            }
            break;

        case enScanCollectBank :
            for( uiCh = m_uiDetectChannel + m_uiTrackChannel ; uiCh < m_uiDetectChannel + m_uiTrackChannel + m_uiScanChannel ; ++uiCh ) {
                if( true == IsCompleteCollect( uiCh ) ) {
                    pstWindowCell = GetWindowCell( uiCh );

                    Log( enDebug, "[%s]에서 위협[%d/%d] 스캔 채널[%3d]에서 [%d]개 수집 완료", g_strPCIDrverDirection[(int)m_enPCIDriver].c_str(), pstWindowCell->stABTData.uiAETID, pstWindowCell->stABTData.uiABTID, uiCh-m_uiDetectChannel-m_uiTrackChannel, pstWindowCell->uiColPDW );
                    SetCollectUpdateTime( uiCh );
                    iCh = ( int ) uiCh;
                    break;
                }
            }
            break;

            //         case enUserCollectBank :
            //             for( i=0 ; i < CO_USER_CHANNEL ; ++i ) {
            //                 if( true == m_pTheUserCollectBank[i]->IsCompleteCollect() ) {
            //                     iCh = m_pTheUserCollectBank[i]->GetChannelNo();
            //
            //                     Log( enDebug, "\n 사용자 뱅크[%d]에서 [%d] 채널에서 수집 완료되었습니다." , i, iCh );
            //                     break;
            //                 }
            //             }
            //             break;

        default:
            break;
    }

    return iCh;

}

/**
 * @brief     SimFilter
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-27 12:57:19
 * @warning
 */
void CCollectBank::SimFilter( STR_PDWDATA *pstPDWData, bool bOnly )
{
    unsigned int ui, uj, uiTotalPDW=0;
    unsigned int uiTrackCh = 0, uiScanCh = 0, uiDetectCh = ( unsigned int ) -1;

    _PDW *pstPDW;

    if( pstPDWData != NULL ) {
        uiTotalPDW = pstPDWData->GetTotalPDW();
    }

    if( uiTotalPDW != 0 ) {
        pstPDW = & pstPDWData->pstPDW[0];

        for( ui = 0; ui < uiTotalPDW; ++ui ) {
#if CO_TRACK_CHANNEL != 0
            uiTrackCh = 0;

            // 추적 채널 설정
            for( uj = CO_DETECT_CHANNEL; uj < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL; ++uj ) {
                if( IsFiltered( uj, pstPDW ) == true ) {
                    if( IsSave( uj ) == true ) {
                        PushPDWData( uj, pstPDW, &pstPDWData->x );
                    }
                    uiTrackCh = uj;

                }
            }

            // 탐지 채널에 저장한다.
            if( uiTrackCh == 0 ) {
#endif

                if( bOnly == true ) {
                    for( uj = 0 ; uj < CO_DETECT_CHANNEL; ++uj ) {
                        if( IsFiltered( uj, pstPDW ) == true ) {
                            PushPDWData( uj, pstPDW, &pstPDWData->x );
                            uiDetectCh = uj;
                        }
                    }
                }
#if CO_TRACK_CHANNEL != 0
            }
#endif

#if CO_SCAN_CHANNEL != 0
            // 스캔 채널 설정
            for( uj = CO_DETECT_CHANNEL + CO_TRACK_CHANNEL; uj < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL + CO_SCAN_CHANNEL; ++uj ) {
                if( IsFiltered( uj, pstPDW ) == true ) {
                    if( IsSave( uj ) == true ) {
                        PushPDWData( uj, pstPDW, &pstPDWData->x );
                    }
                    uiScanCh = uj;

                }

            }
#endif

            // 사용자 채널 설정

            ++pstPDW;

            for( uj = 0; uj < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL + CO_SCAN_CHANNEL; ++uj ) {
                SimCollectMode( uj );
            }

        }


    }
    else {
        for( uj = 0; uj < CO_DETECT_CHANNEL + CO_TRACK_CHANNEL + CO_SCAN_CHANNEL; ++uj ) {
            SimCollectMode( uj );
        }


        //STR_COLLECT_INFO stCollectInfo;

        //         memset( &stCollectInfo, 0, sizeof( STR_COLLECTINFO ) );
        //         stCollectInfo.iCh = 0;
        //         stCollectInfo.uiTotalPDW = 0;
        //         g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_DETECT_COLSTOP, &stCollectInfo, sizeof( struct STR_COLLECTINFO ) );
    }

}


#endif
