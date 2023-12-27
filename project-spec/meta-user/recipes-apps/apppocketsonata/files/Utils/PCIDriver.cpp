/**

    @file      PCIDriver.cpp
    @brief
    @details   ~
    @author    Cool Guy
    @date      14.12.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "pch.h"

#include "PCIDriver.h"

#include "../Anal/OFP_Main.h"

#include "../Include/globals.h"

#include "./ccommonutils.h"

bool CPCIDriver::m_bPCIMemInit = false;

std::string g_strPCIDrverDirection[en_ELEMENT_PCI_DRIVER] = { "LEFT", "RGHT", "UnKnown" };


#ifdef __VXWORKS__
#include "pciDiag.h"
#include <subsys/gpio/vxbGpioLib.h>

/**
 * @brief		ISRPCIeRoutine
 * @param		void * pArg
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/23 10:47:52
 * @warning
 */
void ISRPCIeRoutine( void* pArg )
{
	CPCIDriver* pciDriver = ( CPCIDriver* ) pArg;

	pciDriver->ISRRoutine();

}

#endif

static const std::string g_strPCIRegisterName[50] = { "PARAM_INIT",
                                                      "OP_MODE",
                                                      "PATN_INTERVAL",
                                                      "SEARCH_START",
                                                      "TRACK_START",
                                                      "SCAN_START",
                                                      "DUMMY_START",
                                                      "SEARCH_STOP",
                                                      "TRACK_STOP",
                                                      "SCAN_STOP",
                                                      "DUMMY_STOP",

                                                      "PARAM_IDX_W",
                                                      "PARAM_BYPASS",
                                                      "PARAM_ANZ_COUNT",
                                                      "PARAM_ANZ_TIME_LOW",
                                                      "PARAM_ANZ_TIME_HIGH",
                                                      "PARAM_ANZ_M_OFFSET",
                                                      "PARAM_ANZ_M_SIZE",

                                                      "FILT_ADAPT",
                                                      "FILT_AOA_MAX",
                                                      "FILT_AOA_MIN",
                                                      "FILT_FREQ_MAX",
                                                      "FILT_FREQ_MIN",
                                                      "FILT_PW_MAX",
                                                      "FILT_PW_MIN",
                                                      "FILT_PA_MAX",
                                                      "FILT_PA_MIN",
                                                      "FILT_MOP",
                                                      "FILT_MOP_DIR",
                                                      "FILT_MOP_BW_MIN",
                                                      "FILT_MOP_BW_MAX",

                                                      "ANZ_IRQ_STATUSLOW",
                                                      "ANZ_IRQ_STATUSHIGH",
                                                      "ANZ_ACQ_CNT1",
                                                      "ANZ_ACQ_CNT2",
                                                      "ANZ_ACQ_CNT3",
                                                      "ANZ_ACQ_CNT4",
                                                      "PARAM_TYPE",
                                                      "PARAM_FALSE_PDW",
                                                      "PARAM_IDX_R",
                                                      "IBRDID",
                                                      "ANZ_FILT_TAP1",
                                                      "ANZ_FILT_TAP2",
                                                      "ANZ_FILT_TAP3",
                                                      "ANZ_FILT_TAP4",
                                                      "PARAM_BRAM_WE",
                                                      "PARAM_BRAM_WADDR",
                                                      "PARAM_BRAM_RADDR",
                                                      "ANZ_CNT_IDX" ,
                                                      "CLOCK_RATE" };

/**
 * @brief		필터판 수집 완료 ISR 루틴, 이 루틴에서는 printf() 함수를 넣어도 출력이 안 됩니다. !!
 * @param		ENUM_PCI_DRIVER enPCIDriver
 * @param		unsigned int uiReqStatus
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/21 11:23:39
 * @warning     이 루틴에서는 세마포어나 printf 를 사용하지 말아야 합니다.
 */
void CPCIDriver::ISRRoutine()
{
    unsigned int uiReqStatus, uiValue;

    UNI_MSG_DATA uniMsgData;

    STR_COLLECT_INFO *pStrCollectInfo;

    pStrCollectInfo = & uniMsgData.strCollectInfo;
    //_func_kprintf( "\n pStrCollectInfo[%p]", pStrCollectInfo );

    pStrCollectInfo->enPCIDriver = m_enPCIDriver;

#ifdef __VXWORKS__

    unsigned int uiFilter;
    unsigned int uiGlobalCh = 0, uiFilterCh;

    pStrCollectInfo = & uniMsgData.strCollectInfo;

    memset( pStrCollectInfo->uiCh2TotalPDW, 0, sizeof( pStrCollectInfo->uiCh2TotalPDW ) );

    //! printf() 함수 대신에 _func_kprintf 를 사용해야 정상 출력이 됩니다.
    //_func_kprintf( "\nISR1[%d]...", m_enPCIDriver );

     for( uiFilter = enDetectCollectBank - 1; uiFilter < enScanCollectBank; ++uiFilter ) {
         // 1. 필터 선택
        PCICtrlWrite32( PARAM_IDX_R, uiFilter+1, false );
        //printf( "\n@CtrlWrite32([0x%04X], 0x%08x)", PARAM_IDX_R, uiValue );

        uiReqStatus = PCICtrlRead32( ANZ_IRQ_STATUSLOW, false );
        //printf( "\n@CtrlRead32([0x%04X], 0x%08x)", ANZ_IRQ_STATUSLOW, uiReqStatus );

        pStrCollectInfo->uiReqStatus[uiFilter] = uiReqStatus;

        //_func_kprintf( "\nFilter[%d] : {0x%x}", uiFilter, uiReqStatus );

        if( uiFilter == 0 ) {
            uiGlobalCh = 0;
            uiReqStatus &= APPLIED_DETECT;
        }
        else if( uiFilter == 1 ) {
            uiGlobalCh = CO_DETECT_CHANNEL;
            uiReqStatus &= APPLIED_TRACK;
        }
        else {
            uiGlobalCh = CO_DETECT_CHANNEL + CO_TRACK_CHANNEL;
            uiReqStatus &= APPLIED_SCAN;;
        }

        uiValue = uiReqStatus;

        uiFilterCh = 0;
        while( uiValue ) {
            if( ( unsigned int ) ( uiValue & ( unsigned int ) 1 ) ) {
                // 2. 채널 선택
                PCICtrlWrite32( ANZ_CNT_IDX, uiFilterCh, false );

                // 3. 수집 PDW 개수 읽기
                if( uiFilter == 0 ) {
                    pStrCollectInfo->uiCh2TotalPDW[uiGlobalCh] = PCICtrlRead32( ANZ_ACQ_CNT1, false );
                }
                else if( uiFilter == 1 ) {
                    pStrCollectInfo->uiCh2TotalPDW[uiGlobalCh] = PCICtrlRead32( ANZ_ACQ_CNT2, false );
                }
                else {
                    pStrCollectInfo->uiCh2TotalPDW[uiGlobalCh] = PCICtrlRead32( ANZ_ACQ_CNT3, false );
                }
                //_func_kprintf( " Ch2PDW[%d:%d]", uiGlobalCh, pStrCollectInfo->uiCh2TotalPDW[uiGlobalCh] );

                // 4. 수집 중지 요청
                if( uiFilter == 0 ) {
                    PCICtrlWrite32( SEARCH_STOP, uiFilterCh+1, true );
                }
                else if( uiFilter == 1 ) {
                    PCICtrlWrite32( TRACK_STOP, uiFilterCh+1, false );
                }
                else {
                    PCICtrlWrite32( SCAN_STOP, uiFilterCh+1, false );
                }
             }

             uiValue >>= 1;

             ++ uiFilterCh;
             ++ uiGlobalCh;
        }

    }

    g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_COMPLETECOL, & uniMsgData, sizeof( UNI_MSG_DATA ), PCIISR_NAME, NO_WAIT );

#else
    unsigned int uiFilter;
    unsigned int uiGlobalCh=0, uiFilterCh;

    pStrCollectInfo = & uniMsgData.strCollectInfo;

    memset( pStrCollectInfo->uiCh2TotalPDW, 0, sizeof( pStrCollectInfo->uiCh2TotalPDW ) );
    pStrCollectInfo->uiReqStatus[0] = 0;
    pStrCollectInfo->uiReqStatus[1] = 0;
    pStrCollectInfo->uiReqStatus[2] = 0;

    _func_kprintf( "\nISR[%d]...", m_enPCIDriver );

    for( uiFilter = enDetectCollectBank-1 ; uiFilter < enScanCollectBank ; ++uiFilter )
    {
        // 1. 필터 선택
        PCICtrlWrite32( PARAM_IDX_R, uiFilter, false );

        uiReqStatus = PCICtrlRead32( ANZ_IRQ_STATUSLOW, true );
        if( uiFilter == 0 ) {
            uiReqStatus = 0x01;
        }
        else {
            uiReqStatus = 0x3;
        }

        pStrCollectInfo->uiReqStatus[uiFilter] = uiReqStatus;

        _func_kprintf( "\nFilter[%d] : 0x%x...", uiFilter, uiReqStatus );

        if( uiFilter == 0 ) {
            uiGlobalCh = 0;
            uiReqStatus &= APPLIED_DETECT;
        }
        else if( uiFilter == 1 ) {
            uiGlobalCh = CO_DETECT_CHANNEL;
            uiReqStatus &= APPLIED_TRACK;
        }
        else {
            uiGlobalCh = CO_DETECT_CHANNEL + CO_TRACK_CHANNEL;
            uiReqStatus &= APPLIED_SCAN;;
        }

        uiValue = uiReqStatus;

        uiFilterCh = 1;
        while( uiValue ) {
            if( ( unsigned int ) ( uiValue & ( unsigned int ) 1 ) ) {
                // 2. 채널 선택
                PCICtrlWrite32( ANZ_CNT_IDX, uiFilterCh, true );

                // 3. 수집 PDW 개수 읽기
                pStrCollectInfo->uiCh2TotalPDW[uiGlobalCh] = PCICtrlRead32( ANZ_CNT_IDX, false );
                pStrCollectInfo->uiCh2TotalPDW[uiGlobalCh] = 0;

                // 4. 수집 중지 요청
                if( uiFilter == 0 ) {
                    PCICtrlWrite32( SEARCH_STOP, uiFilterCh+1, true );
                }
                else if( uiFilter == 1 ) {
                    PCICtrlWrite32( TRACK_STOP, uiFilterCh + 1, true );
                }
                else {
                    PCICtrlWrite32( SCAN_STOP, uiFilterCh + 1, true );
                }
            }

            uiValue >>= 1;

            ++ uiFilterCh;
            ++ uiGlobalCh;
        }

    }

    g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_COMPLETECOL, & uniMsgData, sizeof( UNI_MSG_DATA ), PCIISR_NAME, NO_WAIT );

#endif

	return;
}

/**
 * @brief		CPCIDriver
 * @param		ENUM_PCI_DRIVER enPCIDriver
 * @return
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 16:12:38
 * @warning
 */
CPCIDriver::CPCIDriver( ENUM_PCI_DRIVER enPCIDriver, const char *pThreadName ) : m_enPCIDriver( enPCIDriver )
{

    SetThreadName( pThreadName );

    // 메시지 헤더 추가
    //m_strHeader = string_format( (const char *) "[%s]PCI", (char *) g_strPCIDrverDirection[(int)m_enPCIDriver].c_str() );
    m_strHeader = string_format( "[%s]PCI", ( const char * ) g_strPCIDrverDirection[( int ) m_enPCIDriver].c_str() );

    // 메시지 데이터 정의
    m_pstrCollectInfo = m_uniMsgData.GetCollectInfo();

    // PCI를 초기화 합니다.
    PCIConfigSetting();

    // 비트를 수행합니다.
    RunBit();

    // 소프트웨어 초기화를 수행합니다.
    Init();

#if 0
    // ISRRoutine();


    printf( "\n\n\n 10 초 후에 테스트 시작 합니다.... " );
    Sleep( 10 );
    bool bLog = true;
    unsigned int i = 0, uiRead;
    while( true ) {
        for( i=0 ; i < 64 ; ++i ) {
            // 4. 메모리 쓰기
            PCICtrlWrite32( PARAM_ANZ_M_SIZE, i, false );

            PCICtrlWrite32( PARAM_IDX_W, 1, false );

            PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) 0, false );

            // 4. 메모리 쓰기
            PCICtrlWrite32( PARAM_BRAM_WE, 1, false );

            PCICtrlWrite32( PARAM_IDX_R, 1, false );
            PCICtrlWrite32( ANZ_CNT_IDX, 0, false );

            PCICtrlWrite32( PARAM_BRAM_RADDR, 0, false );

            uiRead = PCICtrlRead32( PARAM_ANZ_M_SIZE, true );

            if( uiRead != i ) {
                printf( "\n ========================> [%d] ", i );
                while( true );
            }
        }

    }

#endif

}

/**
 * @brief		PCI 초기화를 수행해서 어드레스를 얻고 ISR 루틴을 설정합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/18 11:01:59
 * @warning
 */
void CPCIDriver::PCIConfigSetting() const
{
    printf( "\n PCIConfigSetting..." );

    if( m_bPCIMemInit == false ) {
#if defined(__VXWORKS__)
        if( PCIeMemInit() == ERROR ) {
            printf( "\n ERROR! PCIe BAR Initialize !" );
        }

        // pciIstDisable();
#elif defined(_MSC_VER)
        TRACE( "\n PCIeMemInit()" );

#endif
        m_bPCIMemInit = true;

    }

    // 클래스 객체 함수로는 안됨... 왜 안 될까 ?
    //pciIsrStart( IRQ_PCI_LEFT, ( VOIDFUNCPTR ) CPCIDriver::LeftISRRoutine );
    //pciIsrStart( IRQ_PCI_RIGHT, ( VOIDFUNCPTR ) CPCIDriver::RightISRRoutine );

#if defined(__VXWORKS__)
    if( m_enPCIDriver == enLEFT_PCI_DRIVER ) {
        Log( enNormal, "좌 ISR 세팅" );

        pciIsrSetting( IRQ_PCI_LEFT, ( VOIDFUNCPTR ) ISRPCIeRoutine, ( void * ) this );
    }
    else if( m_enPCIDriver == enRIGHT_PCI_DRIVER ) {
        Log( enNormal, "우 ISR 세팅" );
        pciIsrSetting( IRQ_PCI_RIGHT, ( VOIDFUNCPTR ) ISRPCIeRoutine, ( void * ) this );
    }
    else {
    }
#endif

}

/**
 * @brief     PCIInterruptEnable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 10:50:35
 * @warning
 */
void CPCIDriver::PCIInterruptEnable() const
{
    if( m_enPCIDriver == enLEFT_PCI_DRIVER ) {
        Log( enDebug, "%s 인터럽트[%d] Enable 을 설정합니다.", m_strHeader.c_str(), IRQ_PCI_LEFT );

#ifdef __VXWORKS__
		vxbGpioIntEnable( IRQ_PCI_LEFT, ( VOIDFUNCPTR ) ISRPCIeRoutine, ( void * ) this );
#endif


    }
    else if( m_enPCIDriver == enRIGHT_PCI_DRIVER ) {
        Log( enDebug, "%s 인터럽트[%d] Enable 을 설정합니다.", m_strHeader.c_str(), IRQ_PCI_RIGHT );

#ifdef __VXWORKS__
		vxbGpioIntEnable( IRQ_PCI_RIGHT, ( VOIDFUNCPTR ) ISRPCIeRoutine, ( void * ) this );
#endif

    }
    else {
        Log( enError, "ISR 인터럽트 Enable 잘못된 설정 입니다 !" );
    }

}

/**
 * @brief     PCIInterruptDisable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 10:50:37
 * @warning
 */
void CPCIDriver::PCIInterruptDisable() const
{
    if( m_enPCIDriver == enLEFT_PCI_DRIVER ) {
        Log( enNormal, "%s 인터럽트[%d] Disable 을 설정합니다.", m_strHeader.c_str(), IRQ_PCI_LEFT );

#ifdef __VXWORKS__
    	vxbGpioIntDisable( IRQ_PCI_LEFT, ( VOIDFUNCPTR ) ISRPCIeRoutine, ( void * ) this );
#endif


    }
    else if( m_enPCIDriver == enRIGHT_PCI_DRIVER ) {
        Log( enNormal, "%s 인터럽트[%d] Disable 을 설정합니다.", m_strHeader.c_str(), IRQ_PCI_RIGHT );

#ifdef __VXWORKS__
    	vxbGpioIntDisable( IRQ_PCI_RIGHT, ( VOIDFUNCPTR ) ISRPCIeRoutine, ( void * ) this );
#endif


    }
    else {
        Log( enError, "ISR 인터럽트 Enable 잘못된 설정 입니다 !" );
    }

}

/**
 * @brief		~CPCIDriver
 * @return
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 16:12:47
 * @warning
 */
CPCIDriver::~CPCIDriver()
{

}

/**
 * @brief		PCI 초기화 작업을 수행합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 17:17:35
 * @warning
 */
void CPCIDriver::Init()
{
    //unsigned int uiCh;

    Log( enNormal, "%s 초기화를 수행합니다.", m_strHeader.c_str() );

    // 멤버 변수 들 초기화
    m_bIsr = false;

    // 인터럽트 Dsiable
    PCIInterruptDisable();

    // PCI를 초기화 합니다.
//     PCICtrlWrite32( PARAM_INIT, 0, bLog );
//
//     // PDW 선택용 제어 비트
//     PCICtrlWrite32( OP_MODE, NOT_APPLY, bLog );
//
//     /*! \debug  설정 후 ISR 이 발생하지 않을 수 있으므로 아래 함수를 실행해 줘야 합니다.
//     	\author 조철희 (churlhee.jo@lignex1.com)
//     	\date 	2023-06-07 18:53:35
//     */
//     for( uiCh=1 ; uiCh <= MAX_CHANNELS; ++uiCh  ) {
//         PCICtrlWrite32( SEARCH_STOP, uiCh, bLog );
//     }
//
//     for( uiCh = 1; uiCh <= MAX_CHANNELS; ++uiCh ) {
//         PCICtrlWrite32( TRACK_STOP, uiCh, bLog );
//     }
//
//     for( uiCh = 1; uiCh <= MAX_CHANNELS; ++uiCh ) {
//         PCICtrlWrite32( SCAN_STOP, uiCh, bLog );
//     }
//
//     for( uiCh = 1; uiCh <= MAX_CHANNELS; ++uiCh ) {
//         PCICtrlWrite32( DUMMY_STOP, uiCh, bLog );
//     }


    // 클럭 초기화
    PCICtrlWrite32( CLOCK_RATE, ( unsigned int ) CLOCK_SEED, true );

    ///////////////////////////////////////////////////////////////////////////////////
    // 탐지 필터 초기화
    InitDetectFilter();

#if CO_SCAN_CHANNEL > 0
    // 스캔 필터 초기화
    InitScanFilter();

#endif

#if CO_TRACK_CHANNEL > 0
    // 추적 필터 초기화
    InitTrackFilter();

#endif

}

/**
 * @brief     InitDetectFilter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-20 22:47:11
 * @warning
 */
void CPCIDriver::InitDetectFilter() const
{
    unsigned int uiCh;

    bool bLog = false;

    Log( enDebug, "탐지 채널 초기화 ==================================" );

    // 1. 필터 수집 영역 설정
    PCICtrlWrite32( PARAM_BYPASS, ( unsigned int ) 0, bLog );

    // 2. PDW 필터 적용
    PCICtrlWrite32( FILT_ADAPT, 0, bLog );

    // 3. 페라미터 초기화
    InitParameter( bLog );

    // 4. 필터 설정
    PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) enDetectCollectBank, bLog );

    for( uiCh = 0; uiCh < LOGIC_TOTAL_CHANNEL; ++uiCh ) {
        // 페라미터 어드레스 설정
        PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) uiCh, bLog );

        // 4. 메모리 쓰기
        PCICtrlWrite32( PARAM_BRAM_WE, 1, bLog );

    }

    PCICtrlWrite32( SEARCH_STOP, ( unsigned int ) 1, bLog );

}

/**
 * @brief     InitScanFilter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-20 22:47:11
 * @warning
 */
void CPCIDriver::InitScanFilter() const
{
    unsigned int uiCh;

    bool bLog = false;

    Log( enDebug, "스캔 채널 초기화 ==================================" );

    // 1. 필터 수집 영역 설정
    PCICtrlWrite32( PARAM_BYPASS, ( unsigned int ) 0, bLog );

    // 2. PDW 필터 적용
    PCICtrlWrite32( FILT_ADAPT, 0, bLog );

    // 3. 페라미터 초기화
    InitParameter( bLog );

    // 4. 필터 설정
    PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) enScanCollectBank, bLog );

    for( uiCh = 0; uiCh < LOGIC_TOTAL_CHANNEL; ++uiCh ) {
        if( bLog == true ) {
            Log( enDebug, "채널[%2d] 초기화", uiCh );
        }

        // 페라미터 어드레스 설정
        PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) uiCh, bLog );

        // 4. 메모리 쓰기
        PCICtrlWrite32( PARAM_BRAM_WE, 1, bLog );

    }

    PCICtrlWrite32( SCAN_STOP, ( unsigned int ) 1, bLog );

}

/**
 * @brief     InitParameter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-22 11:02:39
 * @warning
 */
void CPCIDriver::InitParameter( bool bLog ) const
{

    // 신호 형태
//PCICtrlWrite32( PARAM_TYPE, ( unsigned int ) pWindowCell->uiSignalType, bLog );

// False PDW 제거
//PCICtrlWrite32( PARAM_FALSE_PDW, ( unsigned int ) 0, bLog );

// 방위 설정
    PCICtrlWrite32( FILT_AOA_MAX, ( unsigned int ) 0, bLog );
    PCICtrlWrite32( FILT_AOA_MIN, ( unsigned int ) 0, bLog );

    // 주파수 설정
    PCICtrlWrite32( FILT_FREQ_MAX, ( unsigned int ) 0, bLog );
    PCICtrlWrite32( FILT_FREQ_MIN, ( unsigned int ) 0, bLog );

    // 펄스폭 설정
    PCICtrlWrite32( FILT_PW_MAX, ( unsigned int ) 0, bLog );
    PCICtrlWrite32( FILT_PW_MIN, ( unsigned int ) 0, bLog );

    // 신호 세기 설정
    PCICtrlWrite32( FILT_PA_MAX, ( unsigned int ) 0, bLog );
    PCICtrlWrite32( FILT_PA_MIN, ( unsigned int ) 0, bLog );

    // 신호 변조
    PCICtrlWrite32( FILT_MOP, ( unsigned int ) 0, bLog );
    PCICtrlWrite32( FILT_MOP_DIR, ( unsigned int ) 0, bLog );

    // 신호 변조 대역폭 변화량
    PCICtrlWrite32( FILT_MOP_BW_MAX, ( unsigned int ) 0, bLog );
    PCICtrlWrite32( FILT_MOP_BW_MIN, ( unsigned int ) 0, bLog );

    // 수집 개수
    PCICtrlWrite32( PARAM_ANZ_COUNT, 0x3f, bLog );

    // 수집 시간
    PCICtrlWrite32( PARAM_ANZ_TIME_LOW, ( unsigned int ) 0, bLog );
    PCICtrlWrite32( PARAM_ANZ_TIME_HIGH, ( unsigned int ) 0, bLog );

    // 수집 메모리 설정
    PCICtrlWrite32( PARAM_ANZ_M_OFFSET, 0, bLog );
    PCICtrlWrite32( PARAM_ANZ_M_SIZE, 0x3f, true );

}

/**
 * @brief     InitTrackFilter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-21 09:00:59
 * @warning
 */
void CPCIDriver::InitTrackFilter() const
{
    unsigned int uiCh;

    bool bLog = false;

    Log( enDebug, "추적 채널 초기화 ==================================" );

    // 1. 필터 수집 영역 설정
    PCICtrlWrite32( PARAM_BYPASS, ( unsigned int ) 0, bLog );

    // 2. PDW 필터 적용
    PCICtrlWrite32( FILT_ADAPT, 0, bLog );

    // 3. 페라미터 초기화
    InitParameter( bLog );

    // 필터 설정
    PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) enTrackCollectBank, bLog );

    for( uiCh = 0; uiCh < LOGIC_TOTAL_CHANNEL; ++uiCh ) {
//         if( bLog == true ) {
//             Log( enDebug, "채널[%2d] 초기화", uiCh );
//         }

        // 페라미터 어드레스 설정
        PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) uiCh, bLog );

        // 4. 메모리 쓰기
        PCICtrlWrite32( PARAM_BRAM_WE, 1, bLog );

    }

    PCICtrlWrite32( TRACK_STOP, ( unsigned int ) 1, bLog );

}

/**
 * @brief		비트를 수행합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/16 17:25:07
 * @warning
 */
void CPCIDriver::RunBit()
{
    //unsigned int ui, value32;

    m_bBIT = true;

    // PCI 읽기/쓰기 테스트
//     for (ui = 0; ui <= 0xFF ; ++ui) {
//         PCICtrlWrite32(PATN_INTERVAL, ui, false );
//         value32 = PCICtrlRead32(PATN_INTERVAL, false);
//
//         if (ui != value32) {
//             m_bBIT = false;
//             break;
//         }
//     }

    //LOGMSG3( enNormal, "%s 관련 점검 결과는 %s[%d] 입니다.", m_strHeader.c_str(), g_szBitResult[(unsigned int) m_bBIT], m_bBIT );
    // printf("\n PCI 관련 점검 결과는 %s[%d] 입니다.", g_szBitResult[m_bBIT], m_bBIT );

}

/**
 * @brief     신호 수집을 시작합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-07 11:28:16
 * @warning
 */
void CPCIDriver::StartCollecting()
{

    // 인터럽트 Enable
    PCIInterruptEnable();

}

/**
 * @brief     EndCollecting
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-14 10:25:03
 * @warning
 */
void CPCIDriver::EndCollecting()
{
    // 인터럽트 Disable
    PCIInterruptDisable();

}

/**
 * @brief		탐지 채널을 설정합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 17:03:12
 * @warning
 */
void CPCIDriver::StartCollecting( STR_WINDOWCELL* pWindowCell, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress )
{

    union STR_DOUBLE_WORD {
        unsigned long long int dw;
        unsigned int word[2];
    } tTime;

    Log( enDebug, "%s %s 채널[%3d]을 수집 설정 합니다.", m_strHeader.c_str(), g_szCollectBank[(unsigned int) pstrCollectPCIAddress->enCollectBank], pWindowCell->uiCh );

    bool bLog=true;

    if( pstrCollectPCIAddress->enCollectBank == enDetectCollectBank ) {
        bLog = false;
    }
    else if( pstrCollectPCIAddress->enCollectBank == enScanCollectBank ) {
        bLog = true;
    }
    else {
        bLog = false;
    }

    if( bLog == true ) {
        printf( "\n" );
    }

    //! STOP 설정 합니다.
    switch( pstrCollectPCIAddress->enCollectBank ) {
        case enDetectCollectBank:
            PCICtrlWrite32( SEARCH_STOP, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR + 1, false );
            break;

        case enTrackCollectBank:
            PCICtrlWrite32( TRACK_STOP, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR + 1, false );
            break;

        case enScanCollectBank:
            PCICtrlWrite32( SCAN_STOP, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR + 1, true );
            break;

        default:
            //PCICtrlWrite32( DUMMY_START, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR + 1, bLog );
            break;
    }

#ifdef _SELF_GEN_PDW
    PCICtrlWrite32( PATN_INTERVAL, ( unsigned int ) 2 * PATN_INTERVAL_MS );
#endif

    // 수집 메모리 설정
    PCICtrlWrite32( PARAM_ANZ_M_OFFSET, pstrCollectPCIAddress->uiPCI_ANZ_M_OFFSET, bLog );
    PCICtrlWrite32( PARAM_ANZ_M_SIZE, pstrCollectPCIAddress->uiPCI_ANZ_M_SIZE, bLog );

    // 1. 필터 수집 영역 설정
    // 방위가 역방향이면 방위에 대해서 Reject 를 설정 합니다.
    if( pWindowCell->strAOA.iLow < pWindowCell->strAOA.iHigh ) {
        // 방위 설정
        PCICtrlWrite32( FILT_AOA_MAX, ( unsigned int ) pWindowCell->strAOA.iHigh, bLog );
        PCICtrlWrite32( FILT_AOA_MIN, ( unsigned int ) pWindowCell->strAOA.iLow, bLog );
    }
    else {
        pWindowCell->uiByPass |= FILT_BYPASS_AOA;

        // 방위 설정
        PCICtrlWrite32( FILT_AOA_MAX, ( unsigned int ) pWindowCell->strAOA.iLow, bLog );
        PCICtrlWrite32( FILT_AOA_MIN, ( unsigned int ) pWindowCell->strAOA.iHigh, bLog );
    }
    PCICtrlWrite32( PARAM_BYPASS, ( unsigned int ) pWindowCell->uiByPass, bLog );

    // 2. PDW 필터 적용
    PCICtrlWrite32( FILT_ADAPT, pWindowCell->uiAdapt, bLog );

    // 신호 형태
    //PCICtrlWrite32( PARAM_TYPE, ( unsigned int ) pWindowCell->uiSignalType, bLog );

    // False PDW 제거
    //PCICtrlWrite32( PARAM_FALSE_PDW, ( unsigned int ) 0, bLog );

    // 주파수 설정
    PCICtrlWrite32( FILT_FREQ_MAX, ( unsigned int ) pWindowCell->strFreq.iHigh, bLog );
	PCICtrlWrite32( FILT_FREQ_MIN, (unsigned int) pWindowCell->strFreq.iLow, bLog );

    // 펄스폭 설정
    PCICtrlWrite32( FILT_PW_MAX, ( unsigned int ) pWindowCell->strPW.iHigh, bLog );
	PCICtrlWrite32( FILT_PW_MIN, ( unsigned int ) pWindowCell->strPW.iLow, bLog );

    // 신호 세기 설정
    PCICtrlWrite32( FILT_PA_MAX, ( unsigned int ) pWindowCell->strPA.iHigh, bLog );
	PCICtrlWrite32( FILT_PA_MIN, ( unsigned int ) pWindowCell->strPA.iLow, bLog );

    // 신호 변조
    PCICtrlWrite32( FILT_MOP, ( unsigned int ) pWindowCell->uiMOPType, bLog );
    PCICtrlWrite32( FILT_MOP_DIR, ( unsigned int ) pWindowCell->uiMOPDir, bLog );

    // 신호 변조 대역폭 변화량
    PCICtrlWrite32( FILT_MOP_BW_MAX, ( unsigned int ) 0xFFFF, bLog );
    PCICtrlWrite32( FILT_MOP_BW_MIN, ( unsigned int ) 0, bLog );

    // 수집 개수
    PCICtrlWrite32( PARAM_ANZ_COUNT, pWindowCell->uiCoCollectingPDW, bLog );

    // 수집 시간
    // tTime.dw = ANZ_TIME_MS( pWindowCell->uiMaxCollectTimeMssec );
    float fClockRes;
    //fClockRes = CLOCK_RES;
    //fClockRes = FDIV( 125, CLOCK_SEED ) * (float) 1000000.;
    fClockRes = FMUL( CLOCK_RES, pWindowCell->uiMaxCollectTimeMssec );
    tTime.dw = UDIV( fClockRes, (float) 1000. );

#ifdef __VXWORKS__
    PCICtrlWrite32( PARAM_ANZ_TIME_LOW, tTime.word[1], false );
    PCICtrlWrite32( PARAM_ANZ_TIME_HIGH, tTime.word[0], false );
#else
    PCICtrlWrite32( PARAM_ANZ_TIME_LOW, tTime.word[0], true );
    PCICtrlWrite32( PARAM_ANZ_TIME_HIGH, tTime.word[1], true );
#endif

    // 수집 메모리 설정
    //PCICtrlWrite32( PARAM_ANZ_M_OFFSET, pstrCollectPCIAddress->uiPCI_ANZ_M_OFFSET, bLog );
    //PCICtrlWrite32( PARAM_ANZ_M_SIZE, pstrCollectPCIAddress->uiPCI_ANZ_M_SIZE, true);

    // 필터 설정
    PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) pstrCollectPCIAddress->enCollectBank, bLog );

    // 페라미터 어드레스 설정
    PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) pstrCollectPCIAddress->uiPARAM_BRAM_WADDR, bLog );

#ifdef _SELF_GEN_PDW
    PCICtrlWrite32( PATN_INTERVAL, ( unsigned int ) ( pWindowCell->uiMaxCollectTimeMssec * PATN_INTERVAL_MS ) );
#endif

    // 4. 메모리 쓰기
    PCICtrlWrite32( PARAM_BRAM_WE, 1, bLog );

#if 0
    for( int i = 0; i < 0xFFFFFF; ++i );
#endif

//     // 임시 나머지 채널 쓰기
//     //? 하드웨어 로직 중간 단계로 나중에 삭제 됨?
//     if( pstrCollectPCIAddress->enCollectBank == enDetectCollectBank ) {
//         int i;
//
//         Log( enDebug, "2번 채널부터 64번 채널 까지 수행 합니다." );
//         for( i = 1 ; i < LOGIC_TOTAL_CHANNEL ; ++i ) {
//             PCICtrlWrite32( PARAM_BRAM_WADDR, i, false );
//             PCICtrlWrite32( PARAM_BRAM_WE, 1, false );
//         }
//     }

    // 5. 수집 시작
    switch( pstrCollectPCIAddress->enCollectBank ) {
        case enDetectCollectBank :
            PCICtrlWrite32( SEARCH_START, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR+1, bLog );
            break;

        case enTrackCollectBank:
            PCICtrlWrite32( TRACK_START, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR + 1, bLog );
            break;

        case enScanCollectBank:
            PCICtrlWrite32( SCAN_START, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR + 1, bLog );
            break;

        default:
            //PCICtrlWrite32( DUMMY_START, pstrCollectPCIAddress->uiPARAM_BRAM_WADDR + 1, bLog );
            break;
    }

}

/**
 * @brief     PreFilterSetting
 * @param     STR_WINDOWCELL * pWindowCell
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-05 14:03:38
 * @warning
 */
void CPCIDriver::PreFilterSetting( STR_WINDOWCELL *pWindowCell, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress, STR_COLLECT_PCIADDRESS *i_pPreFilterPCIAddress )
{

    if( pstrCollectPCIAddress->enCollectBank == enTrackCollectBank ) {
        unsigned int uiByPass;

        STR_COLLECT_PCIADDRESS *pPreFilterPCIAddress;

#ifdef __VXWORKS__
        bool bLog = false;
#else
        bool bLog = false;
#endif

        pPreFilterPCIAddress = & i_pPreFilterPCIAddress[pWindowCell->uiCh];

        Log( enDebug, "탐지 채널의 전처러 필터링 [%d] 채널을 설정합니다.", pWindowCell->uiCh );

        // 1. 필터 수집 영역 설정

        // 방위 설정
        if( pWindowCell->strAOA.iLow < pWindowCell->strAOA.iHigh ) {
            uiByPass = FILT_REJECT_ALL;

            // 방위 설정
            PCICtrlWrite32( FILT_AOA_MAX, ( unsigned int ) pWindowCell->strAOA.iHigh, bLog );
            PCICtrlWrite32( FILT_AOA_MIN, ( unsigned int ) pWindowCell->strAOA.iLow, bLog );
        }
        else {
            uiByPass = FILT_REJECT_ALL & (~FILT_BYPASS_AOA);

            // 방위 설정
            PCICtrlWrite32( FILT_AOA_MAX, ( unsigned int ) pWindowCell->strAOA.iLow, bLog );
            PCICtrlWrite32( FILT_AOA_MIN, ( unsigned int ) pWindowCell->strAOA.iHigh, bLog );
        }
        PCICtrlWrite32( PARAM_BYPASS, uiByPass, bLog );

        // 2. PDW 필터 적용
        PCICtrlWrite32( FILT_ADAPT, pWindowCell->uiAdapt, bLog );

        // 신호 형태
        PCICtrlWrite32( PARAM_TYPE, ( unsigned int ) pWindowCell->uiSignalType, bLog );

        // False PDW 제거
        PCICtrlWrite32( PARAM_FALSE_PDW, ( unsigned int ) 0, bLog );


        // 주파수 설정
        PCICtrlWrite32( FILT_FREQ_MAX, ( unsigned int ) pWindowCell->strFreq.iHigh, bLog );
        PCICtrlWrite32( FILT_FREQ_MIN, ( unsigned int ) pWindowCell->strFreq.iLow, bLog );

        // 펄스폭 설정
        PCICtrlWrite32( FILT_PW_MAX, ( unsigned int ) pWindowCell->strPW.iHigh, bLog );
        PCICtrlWrite32( FILT_PW_MIN, ( unsigned int ) pWindowCell->strPW.iLow, bLog );

        // 신호 세기 설정
        PCICtrlWrite32( FILT_PA_MAX, ( unsigned int ) pWindowCell->strPA.iHigh, bLog );
        PCICtrlWrite32( FILT_PA_MIN, ( unsigned int ) pWindowCell->strPA.iLow, bLog );

        // 신호 변조
        PCICtrlWrite32( FILT_MOP, ( unsigned int ) pWindowCell->uiMOPType, bLog );
        PCICtrlWrite32( FILT_MOP_DIR, ( unsigned int ) pWindowCell->uiMOPDir, bLog );

        // 신호 변조 대역폭 변화량
        PCICtrlWrite32( FILT_MOP_BW_MAX, ( unsigned int ) 0xFFFF, bLog );
        PCICtrlWrite32( FILT_MOP_BW_MIN, ( unsigned int ) 0, bLog );

        // 수집 메모리 설정
        PCICtrlWrite32( PARAM_ANZ_M_OFFSET, pPreFilterPCIAddress->uiPCI_ANZ_M_OFFSET, bLog );
        PCICtrlWrite32( PARAM_ANZ_M_SIZE, pPreFilterPCIAddress->uiPCI_ANZ_M_SIZE, bLog );

        // 필터 설정
        PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) pPreFilterPCIAddress->enCollectBank, bLog );

        // 페라미터 어드레스 설정
        PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) pPreFilterPCIAddress->uiPARAM_BRAM_WADDR, bLog );

#ifdef _SELF_GEN_PDW
        PCICtrlWrite32( PATN_INTERVAL, ( unsigned int ) ( pWindowCell->uiMaxCollectTimeMssec * PATN_INTERVAL_MS ) );
#endif

        // 4. 메모리 쓰기
        PCICtrlWrite32( PARAM_BRAM_WE, 1, bLog );

        //     // 임시 나머지 채널 쓰기
        //     //? 하드웨어 로직 중간 단계로 나중에 삭제 됨?
        //     if( pstrCollectPCIAddress->enCollectBank == enDetectCollectBank ) {
        //         int i;
        //
        //         Log( enDebug, "2번 채널부터 64번 채널 까지 수행 합니다." );
        //         for( i = 1 ; i < LOGIC_TOTAL_CHANNEL ; ++i ) {
        //             PCICtrlWrite32( PARAM_BRAM_WADDR, i, false );
        //             PCICtrlWrite32( PARAM_BRAM_WE, 1, false );
        //         }
        //     }

        // 5. 수집 시작
        PCICtrlWrite32( SEARCH_START, 1, bLog );

    }
    else {
    }


}

/**
 * @brief     PreFilterClose
 * @param     STR_WINDOWCELL * pWindowCell
 * @param     STR_COLLECT_PCIADDRESS * pstrCollectPCIAddress
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-14 10:49:22
 * @warning
 */
void CPCIDriver::PreFilterClose( STR_WINDOWCELL *pWindowCell, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress )
{
    Log( enDebug, "탐지 채널의 전처러 필터링 [%d] 채널을 닫습니다.", pWindowCell->uiCh );

    bool bLog = true;

    PCICtrlWrite32( FILT_ADAPT, 0, bLog );

    PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) enDetectCollectBank, bLog );

    PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) pWindowCell->uiCh, bLog );

    // 4. 메모리 쓰기
    PCICtrlWrite32( PARAM_BRAM_WE, 1, bLog );

    //  5. 추적 종료
    PCICtrlWrite32( SEARCH_STOP, ( unsigned int ) 1, bLog );

}

/**
 * @brief		PCICtrlWrite32
 * @param		unsigned int uiOffset
 * @param		unsigned int uiValue
 * @return		bool
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 17:16:43
 * @warning
 */
void CPCIDriver::PCICtrlWrite32( unsigned int uiOffset, unsigned int uiValue, bool bLog ) const
{

    if( bLog == true ) {
        TRACE( "\n@%sCtrlWrite32(%21s[0x%04X], 0x%08x)", m_strHeader.c_str(), GetRegisterName( uiOffset ), uiOffset, uiValue );
        //Log( enDebug, "@%sCtrlWrite32(%-12s[0x%04X], %d(0x%08x))", m_strHeader.c_str(), GetRegisterName( uiOffset ), uiOffset, uiValue, uiValue );
    }

    CCommonUtils::swapByteOrder( uiValue );

#ifdef __VXWORKS__
    switch( m_enPCIDriver ) {
        case enLEFT_PCI_DRIVER :
            PCIeLeftCtrlWrite32( uiOffset, uiValue );
            break;

        case enRIGHT_PCI_DRIVER:
            PCIeRightCtrlWrite32( uiOffset, uiValue );
            break;

        default:
            break;

    }

    // taskDelay( 1L );

#else

#endif

    return;

}

/**
 * @brief		PCICtrlRead32
 * @param		unsigned int uiOffset
 * @return		UINT
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/16 16:21:45
 * @warning
 */
UINT CPCIDriver::PCICtrlRead32(unsigned int uiOffset, bool bLog) const
{
    unsigned int uiValue32=0;

#ifdef __VXWORKS__
    switch( m_enPCIDriver ) {
        case enLEFT_PCI_DRIVER:
            uiValue32 = PCIeLeftCtrlRead32(uiOffset);
            CCommonUtils::swapByteOrder( uiValue32 );
            break;

        case enRIGHT_PCI_DRIVER:
            uiValue32 = PCIeRightCtrlRead32(uiOffset);
            CCommonUtils::swapByteOrder( uiValue32 );
            break;

        default:
            break;
    }

#else

#endif

    if( bLog == true ) {
        TRACE( "\n@[0x%08X] = %sCtrlRead32( %s[0x%04X] )", uiValue32, m_strHeader.c_str(), GetRegisterName( uiOffset ), uiOffset );
        //Log( enNormal, "@[0x%08X] = %sCtrlRead32( %-12s[0x%04X] )", uiValue32, m_strHeader.c_str(), GetRegisterName( uiOffset ), uiOffset );
    }

    return uiValue32;

}

/**
 * @brief		GetRegisterName
 * @param		unsigned int uiOffset
 * @return		const char*
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/16 16:24:31
 * @warning
 */
const char* CPCIDriver::GetRegisterName(unsigned int uiOffset) const
{
    unsigned int i = 0;
    const char* pChar=NULL;

#if defined(__VXWORKS__) || ( defined(_WIN64) && defined(_DEBUG) )
    switch (uiOffset) {
    case PARAM_INIT :
        i = 0;
        break;

    case OP_MODE:
        i = 1;
        break;

    case PATN_INTERVAL:
        i = 2;
        break;

    case SEARCH_START:
        i = 3;
        break;

    case TRACK_START:
        i = 4;
        break;

    case SCAN_START:
        i = 5;
        break;

    case DUMMY_START:
        i = 6;
        break;

    case SEARCH_STOP:
        i = 7;
        break;

    case TRACK_STOP:
        i = 8;
        break;

    case SCAN_STOP:
        i = 9;
        break;

    case DUMMY_STOP:
        i = 10;
        break;

    case PARAM_IDX_W:
        i = 11;
        break;

    case PARAM_BYPASS:
        i = 12;
        break;

    case PARAM_ANZ_COUNT:
        i = 13;
        break;

    case PARAM_ANZ_TIME_LOW:
        i = 14;
        break;

    case PARAM_ANZ_TIME_HIGH:
        i = 15;
        break;

    case PARAM_ANZ_M_OFFSET:
        i = 16;
        break;

	case PARAM_ANZ_M_SIZE:
        i = 17;
		break;

	case FILT_ADAPT:
        i = 18;
		break;

	case FILT_AOA_MAX:
        i = 19;
		break;

	case FILT_AOA_MIN:
        i = 20;
		break;

	case FILT_FREQ_MAX:
        i = 21;
		break;

    case FILT_FREQ_MIN:
        i = 22;
        break;

	case FILT_PW_MAX:
        i = 23;
		break;

	case FILT_PW_MIN:
        i = 24;
		break;

	case FILT_PA_MAX:
        i = 25;
		break;

	case FILT_PA_MIN:
        i = 26;
		break;

	case FILT_MOP:
        i = 27;
		break;

	case FILT_MOP_DIR:
        i = 28;
		break;

	case FILT_MOP_BW_MIN:
        i = 29;
		break;

	case FILT_MOP_BW_MAX:
        i = 30;
		break;

	case ANZ_IRQ_STATUSLOW:
        i = 31;
		break;

	case ANZ_IRQ_STATUSHIGH:
        i = 32;
		break;

	case ANZ_ACQ_CNT1:
        i = 33;
		break;

    case ANZ_ACQ_CNT2:
        i = 34;
        break;

    case ANZ_ACQ_CNT3:
        i = 35;
        break;

    case ANZ_ACQ_CNT4:
        i = 36;
        break;

    case PARAM_TYPE:
        i = 37;
        break;

    case PARAM_FALSE_PDW:
        i = 38;
        break;

    case PARAM_IDX_R:
        i = 39;
        break;

    case IBRDID:
        i = 40;
        break;

    case ANZ_FILT_TAP1:
        i = 41;
        break;

    case ANZ_FILT_TAP2:
        i = 42;
        break;

    case ANZ_FILT_TAP3:
        i = 43;
        break;

    case ANZ_FILT_TAP4:
        i = 44;
        break;

    case PARAM_BRAM_WE:
        i = 45;
        break;

    case PARAM_BRAM_WADDR:
        i = 46;
        break;

    case PARAM_BRAM_RADDR:
        i = 47;
        break;

    case ANZ_CNT_IDX:
        i = 48;
        break;

    case CLOCK_RATE:
        i = 49;
        break;

    default:
        i = 0;
        break;
    }

    pChar = g_strPCIRegisterName[i].c_str();

#endif

    return pChar;
}

/**
 * @brief     CloseChannel
 * @param     unsigned int uiCh
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-14 09:54:00
 * @warning
 */
void CPCIDriver::CloseChannel( unsigned int uiGlobalCh, ENUM_COLLECTBANK enCollectBank, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress )
{
    bool bLog = true;

    Log( enDebug, "%s 채널[%2d]을 닫습니다.", g_szCollectBank[(unsigned int)enCollectBank], uiGlobalCh );

    PCICtrlWrite32( FILT_ADAPT, 0, bLog );

    PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) enCollectBank, bLog );

    PCICtrlWrite32( PARAM_BRAM_WADDR, ( unsigned int ) pstrCollectPCIAddress->uiPARAM_BRAM_WADDR, bLog );

    // 4. 메모리 쓰기
    PCICtrlWrite32( PARAM_BRAM_WE, 1, bLog );

    //  5. 추적 종료
    if( enCollectBank == enTrackCollectBank ) {
        PCICtrlWrite32( TRACK_STOP, ( unsigned int ) 1, bLog );
    }
    else {
        PCICtrlWrite32( SCAN_STOP, ( unsigned int ) 1, bLog );
    }

}

/**
 * @brief     GetPDWData
 * @param     STR_UZPOCKETPDW * pPDWData
 * @param     unsigned int uiCh
 * @param     unsigned int uiTotalPDW
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-11 11:00:26
 * @warning
 */
void CPCIDriver::GetPDWData( STR_UZPOCKETPDW *pPDWData, unsigned int uiGlobalCh, unsigned int uiTotalPDW, unsigned int uiPCIAddressOffset )
{
    unsigned char *pPCIAddress = NULL;

#ifdef __VXWORKS__

    pPCIAddress = PCIeCtrlMemory( (unsigned int) m_enPCIDriver );
    //printf( "\n pPCIAddress[%x]", pPCIAddress );

    pPCIAddress += uiPCIAddressOffset;
    //printf( "\n pPCIAddress[%x]", pPCIAddress );

    Log( enNormal, "%s [%d] 개의 PDW 데이터를 [0x%08x(0x%08x)] 에서부터 복사합니다.", m_strHeader.c_str(), uiTotalPDW, pPCIAddress, uiPCIAddressOffset );

    memcpy( pPDWData->pstPDW, pPCIAddress, sizeof( UZPOCKETPDW ) * uiTotalPDW );
    CCommonUtils::AllSwapData64( pPDWData->pstPDW, sizeof( UZPOCKETPDW ) * uiTotalPDW );

#else
    pPCIAddress = (unsigned char *) 0x10000000;
    pPCIAddress += uiPCIAddressOffset;

    Log( enNormal, "%s [%d] 개의 PDW 데이터를 [0x%08x] 에서부터 복사합니다.", m_strHeader.c_str(), uiTotalPDW, pPCIAddress );

#endif

}

