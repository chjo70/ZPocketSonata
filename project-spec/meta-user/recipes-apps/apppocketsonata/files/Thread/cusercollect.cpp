/****************************************************************************************
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

#include "../Utils/chwio.h"
#include "../Utils/DMA/dma.h"
#include "../Utils/ccommonutils.h"

//#include "../System/csysconfig.h"

#include "../Include/globals.h"

#ifndef __ZYNQ_BOARD__
#define _SIM_USER_COLLECT_
#endif

CUserCollect::CUserCollect( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData )
{
    LOGENTRY;

    InitVar();
    AllocMemory();
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
    m_ullTOA = 0xFFFFFF00000;

    m_uiCoSim = 0;

    m_uiColStart = 0;

    m_iColHistoTime = 0;

    // 하드웨어
    //xuio_t *s_uio = (xuio_t*) CHWIO::uio_get_uio((uint8_t)REG_UIO_DMA_1);
#ifdef __ZYNQ_BOARD__
    CHWIO::uio_re_enable_Interrupt(REG_UIO_DMA_1);
#endif

}

/**
 * @brief CUserCollect::AllocMemory
 */
void CUserCollect::AllocMemory()
{
    m_pstrDMAPDWWithFileHeader = ( char * ) malloc( sizeof(DMAPDW)*NUM_OF_PDW+sizeof(STR_PDWFILE_HEADER) );
    m_pstrDMAPDW = (DMAPDW *) & m_pstrDMAPDWWithFileHeader[sizeof(STR_PDWFILE_HEADER)];
}

/**
 * @brief CUserCollect::FreeMemory
 */
void CUserCollect::FreeMemory()
{
    free( m_pstrDMAPDWWithFileHeader );
}

/**
 * @brief CUserCollect::Run
 * @param key
 */
void CUserCollect::Run(key_t key)
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CUserCollect::_routine
 */
void CUserCollect::_routine()
{
    LOGENTRY;
    bool bWhile=true;
    UNI_LAN_DATA *pLanData;

    m_pMsg = GetDataMessage();

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    while( bWhile ) {
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
                Stop();
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
 * @brief CUserCollect::SetConfig
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
 * @brief CUserCollect::Stop
 */
void CUserCollect::Stop()
{
    LOGMSG( enDebug, " 수집 설정을 종료합니다." );

#ifdef __ZYNQ_BOARD__
    CHWIO::StopCollecting( REG_UIO_DMA_1 );
#endif

}

/**
 * @brief CUserCollect::ColStart
 */
void CUserCollect::ColStart()
{
    xuio_t *pUIO;

    pdw_reg_t s_pdw_reg_t;

    uint32_t DataCount = PDW_GATHER_SIZE;
    uint32_t DumpLen;

    pUIO = CHWIO::uio_get_uio((uint8_t)REG_UIO_DMA_1);

    DumpLen = sizeof(uint8_t) * DataCount;

    memset(&s_pdw_reg_t, 0, sizeof(s_pdw_reg_t));

    LOGMSG1( enDebug, " Starting of the Collecting Signal [%d]... " , m_uiColStart );
	
    // 인터럽트 재설정 
#ifdef __ZYNQ_BOARD__
    CHWIO::uio_re_enable_Interrupt( REG_UIO_DMA_1 );
#endif

    // 하드웨어로 부터 PDW 데이터를 수집합니다.
    xmem_t *pMem = CHWIO::mem_get_mem(DMA_1_MEM);

#ifdef __ZYNQ_BOARD__
    dma_s2mm_reset(dma_dev_1);
    dma_s2mm_start(dma_dev_1, pMem, PDW_GATHER_SIZE, false );
#endif

    memset( & m_strResColStart, 0, sizeof(m_strResColStart) );

    NextCollectHistogram();
    
    if( true == CHWIO::PendingFromInterrupt(pUIO) ) {
    		
#ifdef _SIM_USER_COLLECT_
        CThread::Sleep( 1000 );

#endif

        //pUIO->ullPhysical = UIO_DMA_1_ADDR;
        //pUIO->size = 0x1000;

#ifdef _MFC_VER
        //TRACE( " *********************************pUIO->physical = %I64u\n", pUIO->ullPhysical );
#else
        //printf( " *********************************pUIO[0x%p], iFd[%d], uLLPhysical[%llu], Dev[%s], Size[%d]\n", pUIO, pUIO->iFd, pUIO->ullPhysical, pUIO->pszDev, sizeof(xuio_t) );
#endif
      
        switch( pUIO->ullPhysical ) {
            case UIO_DMA_1_ADDR :
#ifdef __ZYNQ_BOARD__
                CHWIO::ClearInterrupt(pUIO);
#endif

                m_strResColStart.uiBoardID = g_pTheSysConfig->GetBoardID();

                // 실제 PDW 수집한 개수는 현재는 그냥 100 으로 한다.
                m_strResColStart.uiCoPulseNum = PDW_GATHER_SIZE / sizeof(DMAPDW);

                if( pUIO->iFd > 0 ) {
                    memcpy( m_pstrDMAPDW, (void *)(pMem->ullogical), PDW_GATHER_SIZE );
                    //m_uiCoPDW = NUM_OF_PDW;
                }
                else {
                    MakeSIMPDWData();
                }

                MakeCollectHistogram();

                // ES 모드일때만 모의 데이터를 수집 관리에 밀어 넣는다.
                if( g_pTheSysConfig->GetMode() == enANAL_ES_MODE ) {
                    STR_PDWFILE_HEADER *pPDWFileHeader;

                    // printf( "\n Send enTHREAD_REQ_SIM_PDWDATA..." );

                    pPDWFileHeader = ( STR_PDWFILE_HEADER * ) m_pstrDMAPDWWithFileHeader;
                    memset( pPDWFileHeader, 0, sizeof(STR_PDWFILE_HEADER) );
                    pPDWFileHeader->uiBoardID = (UINT) g_enBoardId;
                    pPDWFileHeader->uiSignalCount = NUM_OF_PDW;
                    g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_SIM_PDWDATA, m_pstrDMAPDWWithFileHeader, PDW_GATHER_SIZE+sizeof(STR_PDWFILE_HEADER), NULL, 0, GetThreadName() );
                }
                break;

            default :
#ifdef __ZYNQ_BOARD__
                CHWIO::ClearInterrupt(pUIO);
#endif
                //ClearInterrupt(s_uio);
                //printf( "\n AAAA" );
                break;
        }

#ifdef __ZYNQ_BOARD__
        CHWIO::uio_re_enable_Interrupt( REG_UIO_DMA_1 );
#endif
    }

    if( g_pTheSysConfig->GetMode() & enANAL_Mode ) {
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
    DMAPDW *pDMAPDW;

    LOGMSG1( enDebug, " 수집한 PDW [%d] 개를 전송합니다." , m_strResColStart.uiCoPulseNum );

    //pDMAPDW = m_pstrDMAPDW;
    for( ui=0 ; ui < m_strResColStart.uiCoPulseNum ; ui += PDW_BLOCK ) {
        pDMAPDW = & m_pstrDMAPDW[ui];
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
 * @brief     MakeSIMPDWData
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

    unsigned int randomDOA, randomPA, randomPW, randomFreq, randomCh;

    DMAPDW *pDMAPDW;

    pDMAPDW = m_pstrDMAPDW;

    int iDOA;

#define MANUALTOA   (30)
    _TOA manualTOA[MANUALTOA] = { CPOCKETSONATAPDW::EncodeTOAus( (float) 1598.41),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 2986.972 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 4359.585 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 5746.258 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 7022.91 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 8270.053 ),
                                  CPOCKETSONATAPDW::EncodeTOAus( (float) 9516.386 ),
    } ;

    TRACE( "\nMakeSIMPDWData.." );

    uiCoPDW = m_strResColStart.uiCoPulseNum;

    iDOA = m_uiCoSim * CPOCKETSONATAPDW::EncodeDOA( 50 );

    for( i=0 ; i < uiCoPDW; ++i ) {
        randomDOA = iDOA + ( rand() % 40 ) - 20;
        randomPA =  ( rand() % 140 ) + 20;
        randomPW =  ( rand() % 1000 ) + 20000;

        if( m_uiCoSim % 20 == 0 || true ) {
            CPOCKETSONATAPDW::EncodeRealFREQMHz( (int *) & randomFreq, (int * ) & randomCh, (int) g_enBoardId, 3585.0 );
            //randomFreq = CPOCKETSONATAPDW::EncodeFREQMHzFloor( 4500 );     // ( rand() % 50 ) + 2000;
            //randomCh = 1;
        }
        else {
            CPOCKETSONATAPDW::EncodeRealFREQMHz( (int *) & randomFreq, (int * ) & randomCh, (int) g_enBoardId, 3985.0 );
        }

        //m_ullTOA += ( ( rand() % 10 ) - 5 ) + 0x2000;
        if( i % 2 )
            m_ullTOA += 0x2000;
        else
            m_ullTOA += 0x1500;

        if( i < MANUALTOA ) {
            m_ullTOA = manualTOA[i];
        }

        memset( pDMAPDW, 0, sizeof(DMAPDW) );

        //
        pDMAPDW->uPDW.x.uniPdw_status.stPdw_status.cw_pulse = 0;        // uiPDW_CW;
        pDMAPDW->uPDW.x.uniPdw_status.stPdw_status.pmop_flag = 0;
        pDMAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_flag = 0;
        pDMAPDW->uPDW.x.uniPdw_status.stPdw_status.false_pdw = 0;
        pDMAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_dir = 1;
        pDMAPDW->uPDW.x.uniPdw_status.stPdw_status.fmop_bw = 8000;

        pDMAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.doa = randomDOA;
        pDMAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.di = 0;
        pDMAPDW->uPDW.x.uniPdw_dir_pa.stPdw_dir_pa.pa = randomPA;

        pDMAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.pulse_width = randomPW;
        pDMAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L = randomFreq & 0xFF;

        pDMAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H = ( randomFreq >> 8 ) & 0xFF;
        pDMAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch = randomCh;
        pDMAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.toa_L = m_ullTOA & 0xFFFF;

        pDMAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.toa_H = ( m_ullTOA >> 16 );
        pDMAPDW->uPDW.x.uniPdw_toa_edge.stPdw_toa_edge.edge = 1;

        pDMAPDW->uPDW.x.uniPdw_index.stPdw_index.index = m_uiIndex;

        //printf( "m_ullTOA[%llx], [%0X:%0X]\n" , m_ullTOA, pDMAPDW->uPDW.uniPdw_toa_edge.stPdw_toa_edge.toa_H, pDMAPDW->uPDW.uniPdw_freq_toa.stPdw_freq_toa.toa_L );

        ++ m_uiIndex;

        ++ pDMAPDW;
    }

    ++ m_uiCoSim;

}

/**
 * @brief CUserCollect::MakeCollectHistogram
 */
void CUserCollect::MakeCollectHistogram()
{
    float fFreq;
    int iIndex, iCh, iMax=0;
    unsigned int ui, uiFreq;
    //unsigned char (*pColHisto)[COLHISTO_CELLS] = GP_SYSCFG->GetColHisto();

    unsigned char *pColHisto;

    DMAPDW *pDMAPDW;

    // 주파수 변환하여 기록
    pColHisto = & m_ucColHisto[m_iColHistoTime][0];

    pDMAPDW = m_pstrDMAPDW;
    for( ui=0; ui < m_strResColStart.uiCoPulseNum ; ++ui ) {
        uiFreq = ( pDMAPDW->uPDW.x.uniPdw_pw_freq.stPdw_pw_freq.frequency_L ) | ( pDMAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.frequency_H << 8 );
        iCh = pDMAPDW->uPDW.x.uniPdw_freq_toa.stPdw_freq_toa.pdw_phch;
        fFreq = CPOCKETSONATAPDW::DecodeRealFREQMHz( uiFreq, iCh, (int) g_enBoardId );
        iIndex = (int) ( ( fFreq - MIN_FREQ_MHZ ) / COLHISTO_WIDTH_MHZ );

        iIndex = _min( iIndex, COLHISTO_CELLS-1 );
        iIndex = _max( iIndex, 0 );
        if( pColHisto[iIndex] >= 0xFF ) {
        }
        else {
            ++ pColHisto[iIndex];

            iMax = _max( iMax, pColHisto[iIndex] );
        }

        ++ pDMAPDW;
    }

    pColHisto[COLHISTO_CELLS] = iMax;

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
 * @brief CUserCollect::MakeSharedSpectrumData
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
        pSharedColHisto[0][i] = IDIV( pColHisto[i] * 100, iMax );
    }

    g_pTheSysConfig->SetColHisto();

}
