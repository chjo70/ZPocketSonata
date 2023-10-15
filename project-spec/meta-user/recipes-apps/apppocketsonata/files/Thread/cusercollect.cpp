﻿/****************************************************************************************
 파 일 명 : cusercollect.cpp
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 사용자 수집
 가    정 :
 저 자 명 : 조철희
 변 경 자 : 
 변경내용 : (목적)
 변경일시 : 
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#include "stdafx.h"

#define _USE_MATH_DEFINES

#include "cusercollect.h"

#include "csignalcollect.h"

//#include "../Utils/chwio.h"
//#include "../Utils/DMA/dma.h"
#include "../Utils/ccommonutils.h"


#include "../Include/globals.h"

#ifndef __ZYNQ_BOARD__
#define _SIM_USER_COLLECT_
#endif

/**
 * @brief     CUserCollect
 * @param     int iKeyId
 * @param     const char * pClassName
 * @param     bool bArrayLanData
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:29
 * @warning
 */
CUserCollect::CUserCollect( int iKeyId, const char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;

    AllocMemory();
    InitVar();

#ifdef _POCKETSONATA_
    bool bRet = true;

    int j, k, iBoardID;
    int iFreq, iCh;
    int iEFreq, iECh;
    int iDFreq, iDCh;
    float fFreq;

    float fMinFreq, fMaxFreq;

    fMinFreq = 999999999;
    fMaxFreq = 0;

    for( iBoardID = (int) enPRC1 ; iBoardID <= (int) enPRC5 ; ++iBoardID ) {
        for( k = 0 ; k <= 1 ; ++k ) {
            fMinFreq = 999999999;
            fMaxFreq = 0;

            for( iDCh = 0 ; iDCh < 15 ; ++iDCh ) {
                for( j = 0 ; j < 0xFFFF ; ++j ) {
                    iDFreq = j;
                    fFreq = CPOCKETSONATAPDW::DecodeRealFREQMHz( iDFreq, iDCh, iBoardID, k );
                    CPOCKETSONATAPDW::EncodeRealFREQMHz( &iEFreq, &iECh, iBoardID, fFreq );

                    fMinFreq = min( fMinFreq, fFreq );
                    fMaxFreq = max( fMaxFreq, fFreq );
                }
            }

            TRACE( "\niBoardId/No(%d/%d) [%f - %f]", iBoardID, k, fMinFreq, fMaxFreq );
        }
    }

    TRACE( "\n\n" );
#endif

}

/**
 * @brief CPulseTrk::~CJamTech
 */
CUserCollect::~CUserCollect(void)
{
    FreeMemory();
}

/**
 * @brief CUserCollect::InitVar
 */
void CUserCollect::InitVar()
{

    // 모의 SIM 데이터 초기화
    m_uiIndex = 0;
    m_ullTOA = 0;

    m_uiCoSim = 0;

    m_uiColStart = 0;

    m_iColHistoTime = 0;

    // 하드웨어
    //xuio_t *s_uio = (xuio_t*) CHWIO::uio_get_uio((uint8_t)REG_UIO_DMA_1);
#ifdef __ZYNQ_BOARD__
    CHWIO::uio_re_enable_Interrupt(REG_UIO_DMA_1);
#endif

    m_pUniHeader = ( UNION_HEADER * ) & m_pstrPDWWithFileHeader[0];
    m_pSIGAPDW = ( SIGAPDW *) & m_pstrPDWWithFileHeader[sizeof(UNION_HEADER)];

}

/**
 * @brief     멤버변수들의 메모리를 할당한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 10:12
 * @warning
 */
void CUserCollect::AllocMemory()
{

    m_pstrPDWWithFileHeader = ( char * ) malloc( sizeof( SIGAPDW )*NUM_OF_SIM_PDW+sizeof(UNION_HEADER) );

    m_pTheGenPDW = new CGenPDW( MAX_PDW );

}

/**
 * @brief     메모리를 해지합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:14
 * @warning
 */
void CUserCollect::FreeMemory()
{
    free( m_pstrPDWWithFileHeader );

    delete m_pTheGenPDW;
}

/**
 * @brief     Run
 * @param     key_t key
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:14
 * @warning
 */
void CUserCollect::Run(key_t key)
{
    LOGENTRY;

    CThread::Run( );

}

/**
 * @brief     _routine
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:14
 * @warning
 */
void CUserCollect::_routine()
{
    LOGENTRY;
    //bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetRecvDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while(m_bThreadLoop) {
        if( QMsgRcv() == -1 ) {
            //perror( "QMsgRcv" );
            break;
        }
        else {
        switch( m_pMsg->uiOpCode ) {
            case enTHREAD_REQ_SETCONFIG :
                SetConfig();
                break;

//             case enTHREAD_REQ_STOP :
//                 Stop();
//                 break;


            case enTHREAD_REQ_COLSTART :
                ColStart();
                break;

            case enTHREAD_REQ_COLEND :
                TRACE( "\nenTHREAD_REQ_COLEND.........................");
                StopThread();
                break;

            case enTHREAD_REQ_RAWDATA :
                SendRawData();
                break;

            case enCGI_REQ_SPECTRUM :
                MakeSharedSpectrumData();
                break;

            default:
                //Log( enError, "AAA" );
                break;
            }
        }
    }

}

/**
 * @brief     SetConfig
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:14
 * @warning
 */
void CUserCollect::SetConfig()
{
    char szBuffer[2904];
    unsigned int uiResult;

    UNI_LAN_DATA *pLanData;

    memset( & m_strResColStart, 0 , sizeof(STR_RES_COL_START) );

    pLanData = ( UNI_LAN_DATA * ) GetRecvData();

    if( pLanData != NULL ) {
        sprintf( szBuffer, "개수/시간[ms](%d/%.1f), 방위[도](%.1f,%.1f), 주파수[MHz](%.3f,%.3f), 세기[dBm](%.1f,%.1f), 펄스폭[ns](%.1f,%.1f)" , \
                 pLanData->strReqSetMode.coPulseNum, pLanData->strReqSetMode.fColTime, \
                 pLanData->strReqSetMode.fAOALow, pLanData->strReqSetMode.fAOAHgh, \
                 pLanData->strReqSetMode.fFreqLow, pLanData->strReqSetMode.fFreqHgh, \
                 pLanData->strReqSetMode.fPALow, pLanData->strReqSetMode.fPAHgh, \
                 pLanData->strReqSetMode.fPWLow, pLanData->strReqSetMode.fPWHgh );
        LOGMSG1( enDebug, " 수집 설정 %s 을 기반으로 윈도우 셀을 설정합니다." , szBuffer );

        // 하드웨어를 설정 합니다.
        uiResult = 0;

        CCommonUtils::SendLan( esRES_SETCONFIG, & uiResult, sizeof(uiResult) );
    }
    else {
        // LOGMSG( enDebug, " 수집 설정 값이 잘못 됐습니다." );
    }

}

/**
 * @brief     Stop
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-09 10:18:21
 * @warning
 */
void CUserCollect::StopThread()
{
    LOGMSG( enDebug, " 수집 설정을 종료합니다." );

#ifdef __ZYNQ_BOARD__
    CHWIO::StopCollecting( REG_UIO_DMA_1 );
#endif

}

/**
 * @brief     PDW 수집을 시작합니다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-04, 10:14
 * @warning
 */
void CUserCollect::ColStart()
{
#ifdef __ZYNQ_BOARD__
    xuio_t *pUIO;

    pdw_reg_t s_pdw_reg_t;

    uint32_t DataCount = (UINT) PDW_GATHER_SIZE;
    
    pUIO = CHWIO::uio_get_uio((uint8_t)REG_UIO_DMA_1);

    memset( &s_pdw_reg_t, 0, sizeof( s_pdw_reg_t ) );

#endif

    UINT uiSize;

    //DumpLen = sizeof(uint8_t) * DataCount;

    LOGMSG1( enDebug, " Starting of the Collecting Signal [%d]... " , m_uiColStart );
	
    // 인터럽트 재설정 
#ifdef __ZYNQ_BOARD__
    CHWIO::uio_re_enable_Interrupt( REG_UIO_DMA_1 );

    // 하드웨어로 부터 PDW 데이터를 수집합니다.
    xmem_t *pMem = CHWIO::mem_get_mem(DMA_1_MEM);

    dma_s2mm_reset(dma_dev_1);
    dma_s2mm_start(dma_dev_1, pMem, PDW_GATHER_SIZE, false );
#endif

    memset( & m_strResColStart, 0, sizeof(m_strResColStart) );

    NextCollectHistogram();

#ifdef __ZYNQ_BOARD__
    if( true == CHWIO::PendingFromInterrupt(pUIO) ) {
#endif
    		
#ifdef _SIM_USER_COLLECT_
        CThread::msSleep( 1000 );

#endif

        //pUIO->ullPhysical = UIO_DMA_1_ADDR;
        //pUIO->size = 0x1000;

#ifdef _MFC_VER
        //TRACE( " *********************************pUIO->physical = %I64u\n", pUIO->ullPhysical );
#else
        //printf( " *********************************pUIO[0x%p], iFd[%d], uLLPhysical[%llu], Dev[%s], Size[%d]\n", pUIO, pUIO->iFd, pUIO->ullPhysical, pUIO->pszDev, sizeof(xuio_t) );
#endif

#ifdef __ZYNQ_BOARD__
        switch( pUIO->ullPhysical ) {
            case UIO_DMA_1_ADDR :

                CHWIO::ClearInterrupt(pUIO);

                m_strResColStart.uiBoardID = (unsigned int) g_pTheSysConfig->GetBoardID();

                // 실제 PDW 수집한 개수는 현재는 그냥 100 으로 한다.
                m_strResColStart.uiCoPulseNum = NUM_OF_SIM_PDW; // PDW_GATHER_SIZE / sizeof(DMAPDW);

                if( pUIO->iFd > 0 ) {
                    memcpy( m_pSIGAPDW, (void *)(pMem->ullogical), PDW_GATHER_SIZE );

                    //m_uiCoPDW = NUM_OF_PDW;
                }
                else {
                    MakeSIMPDWData();
                }

                MakeCollectHistogram();

                // ES 모드일때만 모의 데이터를 수집 관리에 밀어 넣는다.
                if( g_pTheTaskMngr->GetMode() == enOP_Mode ) {
                    // printf( "\n Send enTHREAD_REQ_SIM_PDWDATA..." );

                    uiSize = sizeof( SIGAPDW ) * m_pUniHeader->GetTotalPDW(en_ZPOCKETSONATA);
                    g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SIM_PDWDATA, m_pstrPDWWithFileHeader, sizeof(UNION_HEADER)+uiSize, NULL, 0, GetThreadName() );
                }
                break;

            default :
                CHWIO::ClearInterrupt(pUIO);
                //ClearInterrupt(s_uio);
                //printf( "\n AAAA" );
                break;
        }
#else


#endif

#ifdef __ZYNQ_BOARD__
        CHWIO::uio_re_enable_Interrupt( REG_UIO_DMA_1 );
#endif

#ifdef __ZYNQ_BOARD__
    }
#endif

    if( ( (unsigned int) g_pTheTaskMngr->GetMode() & (unsigned int) enOP_Mode ) > 0 ) {
        g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLSTART, GetThreadName() );
    }
    else {
        WhereIs;
        //CCommonUtils::SendLan( Mres_ColStart, & m_strResColStart, sizeof(STR_RES_COL_START) );        
    }

    ++ m_uiColStart;

}

/**
 * @brief     SendRawData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-10, 17:05
 * @warning
 */
void CUserCollect::SendRawData()
{
    unsigned int ui;
    SIGAPDW *pDMAPDW;

    LOGMSG1( enDebug, " 수집한 PDW [%d] 개를 전송합니다." , m_strResColStart.uiCoPulseNum );

    //pDMAPDW = m_pstrDMAPDW;
    for( ui=0 ; ui < m_strResColStart.uiCoPulseNum ; ui += PDW_BLOCK ) {
        pDMAPDW = & m_pSIGAPDW[ui];
        if( m_strResColStart.uiCoPulseNum - ui >= PDW_BLOCK ) {
            CCommonUtils::SendLan( enRES_RAWDATA, pDMAPDW, sizeof(UDRCPDW)*PDW_BLOCK );
        }
        else {
            CCommonUtils::SendLan( enRES_RAWDATA, pDMAPDW, sizeof(UDRCPDW)*(m_strResColStart.uiCoPulseNum-ui) );
        }
        //pDMAPDW += PDW_BLOCK;
    }

}

/**
 * @brief     시나리오 파일을 로드하여 PDW 파일을 생성한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-02, 11:07
 * @warning
 */
void CUserCollect::MakeSIMPDWData()
{
    unsigned int i, uiCoPDW;

    float fRandomDOA;

    int iDOA;
    int iRandomDOA;
    unsigned int uiRandomDOA, uiRandomPA, uiRandomPW, randomFreq, randomCh;

    STR_PDWDATA *pPDWData;
    _PDW *pstPDW;

    SIGAPDW *pSIGAPDW = m_pSIGAPDW;

    memset( m_pUniHeader, 0, sizeof( UNION_HEADER ) );

    m_pUniHeader->SetBoardID( g_enUnitType, ( UINT ) g_enBoardId );

    m_pUniHeader->SetColTime( time( NULL ), 0 );
    //m_pUniHeader->SetTotalPDW( NUM_OF_PDW );
    m_pUniHeader->SetIsStorePDW( 1 );
    m_pUniHeader->SetBandWidth( 1 );
    m_pUniHeader->SetCollectorID( RADARCOL_1 );

    m_pUniHeader->SetBoardID( (unsigned int) g_enBoardId );
    m_pUniHeader->SetBand((unsigned int) g_enBoardId );

    char *pTaskID=m_pUniHeader->GetTaskID( g_enUnitType );
    if( pTaskID != NULL ) {
        strcpy( pTaskID, "MSIGA" );
    }

	//if ((m_uiCoSim % 20) <= 5) {
	if ((m_uiCoSim % 10) <= 3) {
		uiCoPDW = 0;
	}
	else {
		uiCoPDW = m_strResColStart.uiCoPulseNum;
	}

#ifdef __VXWORKS__
    uiCoPDW = 0;

#endif

	m_pUniHeader->SetTotalPDW( uiCoPDW );


    int iBandWidth = m_pUniHeader->GetBandWidth();

#ifdef _SIM_PDW_
#if defined(_POCKETSONATA_)
#define MANUALTOA   (35)

    _TOA manualTOA[MANUALTOA] = { CPOCKETSONATAPDW::EncodeTOAus( (float) 1598.41),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 2986.972 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 4359.585 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 5746.258 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 7022.91 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 8270.053 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 9516.386 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 10763.56 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 12010.74 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 13362.59 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 16424.9 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 17956.39 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 21018.86 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 22410.07 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 23801.04 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 25192.14 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 26582.81 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 29115.85 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 30362.69 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 31609.92 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 32857.43 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 37344.84 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 38874.19 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 40402.47 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 41951.62 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 43256.66 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 44647.55 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 46038.38 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 47429.53 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 48715.07 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 49961.97 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 51209.08 ),
    } ;

    iDOA = (int) m_uiCoSim * (int) CPOCKETSONATAPDW::EncodeDOA( 50 );
    
    for( i=0 ; i < uiCoPDW; ++i ) {
        uiRandomDOA = (unsigned int) ( iDOA + ( ( rand() % 4 ) - 20 ) );
        //uiRandomDOA = ( unsigned int ) iDOA;
		uiRandomPA =  (unsigned int) ( ( rand() % 140 ) + 20 );
		uiRandomPW =  (unsigned int) ( ( rand() % 1000 ) + 20000 );

        if( m_uiCoSim % 20 == 0 || true ) {
            CPOCKETSONATAPDW::EncodeRealFREQMHz( (int *) & randomFreq, (int * ) & randomCh, (int) g_enBoardId, 9800.0 );
        }
        else {
            CPOCKETSONATAPDW::EncodeRealFREQMHz( (int *) & randomFreq, (int * ) & randomCh, (int) g_enBoardId, 3985.0 );
        }

        m_ullTOA += ( CPOCKETSONATAPDW::EncodeTOAus( (float) 100 ) + (_TOA) ( ( rand() % 10000 ) - 5000 ) );

        memset( pSIGAPDW, 0, sizeof(DMAPDW) );

        //
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.cw_pulse = 0;        // ;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.pmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.false_pdw = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir = 1;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_bw = 8000;

        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa = uiRandomDOA;
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.di = 0;
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa = uiRandomPA;

        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width = uiRandomPW;
        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L = randomFreq & (unsigned int) 0xFF;

        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H = ( randomFreq >> 8 ) & (unsigned int) 0xFF;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch = randomCh;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = m_ullTOA & (_TOA) 0xFFFF;

        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = ( m_ullTOA >> 16 );
        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.edge = 1;

        pSIGAPDW->uPDW.x.uniPdw_index.stPdw_index.index = m_uiIndex;

        //printf( "m_ullTOA[%llx], [%0X:%0X]\n" , m_ullTOA, pDMAPDW->uPDW.uniPdw_toa_edge.stPdw_toa_edge.toa_H, pDMAPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.toa_L );

        ++ m_uiIndex;

        ++ pSIGAPDW;
    }


#else
    uiCoPDW = m_strResColStart.uiCoPulseNum;

    iDOA = m_uiCoSim * 20;

    for (i = 0; i < uiCoPDW; ++i) {
        int iCh;

        fRandomDOA = (float) iDOA + ( (float) CCommonUtils::Rand( 100 ) / (float) 10. );

        m_ullTOA += 0x100; // CEncode::EncodeTOAus(100, 0);

        memset( pSIGAPDW, 0, sizeof( SIGAPDW ) );

        // 
        pSIGAPDW->ullTOA = m_ullTOA;

        pSIGAPDW->iPulseType = CEncode::EncodePulseType( 0 );

        pSIGAPDW->uiAOA = CEncode::EncodeDOA( fRandomDOA );
        pSIGAPDW->uiFreq = CEncode::EncodeRealFREQMHz(&iCh, 9000.);
        pSIGAPDW->uiPA = CEncode::EncodePA(-100);
        pSIGAPDW->uiPW = CEncode::EncodePWns( 100, iBandWidth );

        ++m_uiIndex;

        ++pSIGAPDW;
    }

#endif


#else
    m_pTheGenPDW->OpenMakefile( g_szPDWScinarioFile );
    m_pTheGenPDW->ParseAndMakeMemory();

    pstPDW = m_pTheGenPDW->GetMergedPDWData();

    for( i = 0 ; i < uiCoPDW; ++i ) {
        memset( pSIGAPDW, 0, sizeof( DMAPDW ) );

        randomFreq = pstPDW->GetFrequency();
        randomCh = pstPDW->GetChannel();

        m_ullTOA = pstPDW->GetTOA();

#if defined(_POCKETSONATA_)
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.cw_pulse = CEncode::EncodePulseType( pstPDW->GetPulsetype() );        // uiPDW_CW;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.pmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_flag = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.false_pdw = 0;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir = 1;
        pSIGAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_bw = 8000;

        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa = pstPDW->GetAOA();
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.di = 0;
        pSIGAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa = pstPDW->GetPulseamplitude();

        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width = pstPDW->GetPulsewidth();
        pSIGAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L = randomFreq & 0xFF;

        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H = (randomFreq >> 8) & 0xFF;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch = randomCh;
        pSIGAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = m_ullTOA & 0xFFFF;

        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = (m_ullTOA >> 16);
        pSIGAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.edge = 1;

        pSIGAPDW->uPDW.x.uniPdw_index.stPdw_index.index = m_uiIndex;
#else
        int iCh;

        pSIGAPDW->iPulseType = pstPDW->GetPulsetype();

        pSIGAPDW->ullTOA = pstPDW->GetTOA();
        pSIGAPDW->uiAOA = pstPDW->GetAOA();
        pSIGAPDW->uiFreq = pstPDW->GetFrequency();
        pSIGAPDW->uiPA = pstPDW->GetPulseamplitude();
        pSIGAPDW->uiPW = pstPDW->GetPulsewidth();

#endif

        ++pstPDW;

        ++m_uiIndex;

        ++pSIGAPDW;
    }

#if defined(_POCKETSONATA_)


#else

#endif



#endif

    ++ m_uiCoSim;

}

/**
 * @brief     히스토그램을 도시한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-09, 18:10
 * @warning
 */
void CUserCollect::MakeCollectHistogram()
{
    float fFreq;
	int iIndex, iCh;
	unsigned char ucMax=0;
    unsigned int ui, uiFreq;
    //unsigned char (*pColHisto)[COLHISTO_CELLS] = GP_SYSCFG->GetColHisto();

    unsigned char *pColHisto;

    SIGAPDW *pSIGAPDW;

    // 주파수 변환하여 기록
    pColHisto = & m_ucColHisto[m_iColHistoTime][0];

    pSIGAPDW = m_pSIGAPDW;
    for( ui=0; ui < m_strResColStart.uiCoPulseNum ; ++ui ) {
#ifdef _POCKETSONATA_
        iCh = pSIGAPDW->GetChannel();
        uiFreq = pSIGAPDW->GetFrequency( iCh );

        fFreq = FRQMhzCNV( g_enBoardId, uiFreq );
#else
        fFreq = 0;
#endif
        iIndex = (int) ( ( fFreq - MIN_FREQ_MHZ ) / COLHISTO_WIDTH_MHZ );

        iIndex = min( iIndex, COLHISTO_CELLS-1 );
        iIndex = max( iIndex, 0 );
        if( pColHisto[iIndex] >= 0xFF ) {
        }
        else {
            ++ pColHisto[iIndex];

			ucMax = _max(ucMax, pColHisto[iIndex] );
        }

        ++ pSIGAPDW;
    }

    pColHisto[COLHISTO_CELLS] = ucMax;

}

/**
 * @brief CUserCollect::NextCollectHistogram
 */
void CUserCollect::NextCollectHistogram()
{
    //unsigned char (*pColHisto)[COLHISTO_CELLS] = g_pTheSysConfig->GetColHisto();
    m_iColHistoTime = m_iColHistoTime >= (COLHISTO_TIME-1) ? 0 : m_iColHistoTime+1;
    memset( & m_ucColHisto[m_iColHistoTime][0], 0, sizeof(char)*COLHISTO_CELLS );


}

/**
 * @brief     MakeSharedSpectrumData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-12 15:00:27
 * @warning
 */
void CUserCollect::MakeSharedSpectrumData()
{
    int i, iMax;
    unsigned char *pColHisto;

    unsigned char (*pSharedColHisto)[COLHISTO_CELLS] = g_pTheSysConfig->GetColHisto();

    pColHisto = & m_ucColHisto[m_iColHistoTime][0];

    // 정형화하여 SharedMemory 에 저장한다.
    iMax = pColHisto[COLHISTO_CELLS];
    for( i=0; i < COLHISTO_CELLS ; ++i ) {
        pSharedColHisto[0][i] = (unsigned char ) IDIV( pColHisto[i] * 100, iMax );
    }

    g_pTheSysConfig->SetColHisto();

}
