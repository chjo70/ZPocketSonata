﻿//////////////////////////////////////////////////////////////////////////
// CPCIDriver.cpp 소스 파일

#include "pch.h"

#include "PCIDriver.h"

#include "../Anal/OFP_Main.h"

#include "../Include/globals.h"

#include "./ccommonutils.h"

bool CPCIDriver::m_bPCIMemInit = false;

std::string g_strPCIDrverDirection[en_ELEMENT_PCI_DRIVER] = { "LEFT", "RGHT" };


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

static const std::string g_strPCIRegisterName[35] = { "PARAM_INIT",
                                                      "OP_MODE",
                                                      "PATN_INTERVAL",
                                                      "PARAM_IDX_W",
                                                      "FILT_BYPASS",
                                                      "ANZ_START",
                                                      "ANZ_STOP",
                                                      "ANZ_ID",
                                                      "ANZ_LOST_DEL_ON",
                                                      "ANZ_LOST_TIME",
                                                      "ANZ_DEL_TIME",
                                                      "ANZ_CNT",
                                                      "ANZ_TIME_L",
                                                      "ANZ_TIME_H",
                                                      "ANZ_M_OFFSET",
                                                      "ANZ_M_SIZE",
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
                                                      "ANZ_IRQ_STATUS",
                                                      "ANZ_ACQ_UPDATE",
                                                      "ANZ_ACQ_CNT",
                                                      "ANZ_LAST_ADDR",
                                                      "ANZ_LOST_STATUS",
                                                      "ANZ_DELETE_STATUS",
                                                      "PARAM_IDX_R",
                                                      "ANZ_REQ" ,
                                                      "IBRDID" };

/**
 * @brief		필터판 수집 완료 ISR 루틴
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
#ifdef __VXWORKS__
	unsigned int uiReqStatus, uiReqStatusBit, uiCh=0;

    UNI_MSG_DATA uniMsgData;

    STR_COLLECT_INFO *pStrCollectInfo;

    pStrCollectInfo = &uniMsgData.strCollectInfo;

	uiReqStatus = PCICtrlRead32( ANZ_IRQ_STATUS, false );

    _func_kprintf( "\nISR[%d/0x%x]...", m_enPCIDriver, uiReqStatus );

    m_bIsr = true;

    // 1. 채널별로 수집 중지 요청 설정하기
    uiReqStatusBit = uiReqStatus;

    // unsigned int inputParams = PCICtrlRead32( PARAM_IDX_R, false );


    while( uiReqStatusBit && uiCh < TOTAL_CHANNELS ) {
        if( ( unsigned int ) ( uiReqStatusBit & ( unsigned int ) 1 ) ) {
            // 1. 채널 번호 설정
            PCICtrlWrite32( PARAM_IDX_R, uiCh + 1, false );

            // 2. 수집 개수 읽기
            pStrCollectInfo->uiCh2TotalPDW[uiCh] = PCICtrlRead32( ANZ_ACQ_CNT, false );
            if( pStrCollectInfo->uiCh2TotalPDW[uiCh] != 0 ) {
                _func_kprintf( "\nuiReqStatusBit[0x%x], #uiCh[%d], uiTodalPDW[%d]", uiReqStatusBit, uiCh, pStrCollectInfo->uiCh2TotalPDW[uiCh] );
            }
            else {
                //_func_kprintf( "\n#채널[%d]에 수집 개수가 없습니다." , uiCh );
            }

            // 3. 중지 요청
            PCICtrlWrite32( ANZ_STOP, uiCh + 1, false );

        }
        uiReqStatusBit >>= 1;
        ++uiCh;
    }

    // 2. 수집 관련 타스크에 메시지 전송합니다.
    if( CCommonUtils::CountSetBits( uiReqStatus ) >= _spOne ) {
        pStrCollectInfo->Set( uiReqStatus, 0, 0, 0, m_enPCIDriver, enDetectCollectBank, 0);

        if( pStrCollectInfo->uiReqStatus < ( 1 << TOTAL_CHANNELS ) ) {
            //_func_kprintf( "\n[%s]에서 iCh[0x%x], TotalPDW[%d]...[%d]", m_strHeader.c_str(), pStrCollectInfo->uiReqStatus, pStrCollectInfo->uiTotalPDW, uiReqStatus );
            if( g_pTheTaskMngr->GetMode() == enOP_Mode ) {
                g_pTheSignalCollect->QMsgSnd( enTHREAD_REQ_COMPLETECOL, & uniMsgData, sizeof( union UNI_MSG_DATA ), PCIISR_NAME, NO_WAIT );
            }
        }
        else {
            _func_kprintf( "\n채널 값[%d]이 잘못 됐습니다 !", pStrCollectInfo->uiReqStatus );
        }

    }
    else {
        //?     #에러 메시지 확인
        //date 	2023-03-22 11:03:17
        _func_kprintf( "\n[W] [%s]에서 IRQ_STATUS 값[%d]이 잘못 되었거나 2번 이상 ISR이 발생했습니다. 수집 중지로 이런 상태일 수도 있숩니다.", m_strHeader.c_str(), uiReqStatus );

    }
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
CPCIDriver::CPCIDriver( ENUM_PCI_DRIVER enPCIDriver ) : m_enPCIDriver( enPCIDriver )
{

    // 메시지 헤더 추가
    //m_strHeader = string_format( (const char *) "[%s]PCI", (char *) g_strPCIDrverDirection[(int)m_enPCIDriver].c_str() );
    m_strHeader = string_format( ( const char * ) "[%s]PCI", ( const char * ) g_strPCIDrverDirection[( int ) m_enPCIDriver].c_str() );

    // 메시지 데이터 정의
    m_pstrCollectInfo = m_uniMsgData.GetCollectInfo();

    // PCI를 초기화 합니다.
    PCIConfigSetting();

    // 비트를 수행합니다.
    RunBit();

    // 소프트웨어 초기화를 수행합니다.
    Init();

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
        pciIsrSetting( IRQ_PCI_LEFT, ( VOIDFUNCPTR ) ISRPCIeRoutine, ( void * ) this );
    }
    else if( m_enPCIDriver == enRIGHT_PCI_DRIVER ) {
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
    unsigned int uiCh;
    //LOGMSG1( enNormal, "%s 초기화를 수행합니다.", m_strHeader.c_str() );

    // 멤버 변수 들 초기화
    m_bIsr = false;

    // 인터럽트 Dsiable
    PCIInterruptDisable();

    // PCI를 초기화 합니다.
    //PCICtrlWrite32( ANZ_REQ, 0, false );
    PCICtrlWrite32( PARAM_INIT, 0, false );

    // PDW 선택용 제어 비트
    PCICtrlWrite32( OP_MODE, NOT_APPLY, false );

    /*! \debug  설정 후 ISR 이 발생하지 않을 수 있으므로 아래 함수를 실행해 줘야 합니다.
    	\author 조철희 (churlhee.jo@lignex1.com)
    	\date 	2023-06-07 18:53:35
    */
    for( uiCh=1 ; uiCh <= MAX_CHANNELS; ++uiCh  ) {
        PCICtrlWrite32( ANZ_STOP, uiCh, false );
    }

#ifdef _SELF_GEN_PDW
    // PDW 선택용 제어 비트
    PCICtrlWrite32( OP_MODE, NOT_APPLY );

    // Test PDW 패턴 주기
    // PCICtrlWrite32( PATN_INTERVAL, 0x605f41 /* 156249 */ );
    PCICtrlWrite32( PATN_INTERVAL, ( unsigned int ) 2 * PATN_INTERVAL_MS );

    // PDW 선택용 제어 비트
    PCICtrlWrite32( OP_MODE, NOT_APPLY );
#else

#endif

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

    Log( enDebug, "%s 채널[%d]을 수집 설정 합니다.", m_strHeader.c_str(), pWindowCell->uiCh );

#ifdef _SELF_GEN_PDW
    PCICtrlWrite32( PATN_INTERVAL, ( unsigned int ) 2 * PATN_INTERVAL_MS );
#endif

    // 1. 필터 수집 영역 설정
    PCICtrlWrite32( FILT_BYPASS, BYPASS, false );

    // 주파수 설정
	PCICtrlWrite32( FILT_FREQ_MIN, (unsigned int) pWindowCell->strFreq.iLow, false );
	PCICtrlWrite32( FILT_FREQ_MAX, ( unsigned int ) pWindowCell->strFreq.iHigh, false );

    // 방위 설정
    PCICtrlWrite32( FILT_AOA_MIN, ( unsigned int ) pWindowCell->strAOA.iLow, false );
    PCICtrlWrite32( FILT_AOA_MAX, ( unsigned int ) pWindowCell->strAOA.iHigh, false );

    // 펄스폭 설정
	PCICtrlWrite32( FILT_PW_MIN, ( unsigned int ) pWindowCell->strPW.iLow, false );
	PCICtrlWrite32( FILT_PW_MAX, ( unsigned int ) pWindowCell->strPW.iHigh, false );

    // 신호 세기 설정
	PCICtrlWrite32( FILT_PA_MIN, ( unsigned int ) pWindowCell->strPA.iLow, false );
	PCICtrlWrite32( FILT_PA_MAX, ( unsigned int ) pWindowCell->strPA.iHigh, false );

    // 수집 메모리 설정
    PCICtrlWrite32( ANZ_M_OFFSET, pstrCollectPCIAddress->uiPCIAddressOffset, false );
    PCICtrlWrite32( ANZ_M_SIZE, pstrCollectPCIAddress->uiPCIAddressSize, false );

    //PCICtrlWrite32( FILT_MOP, pWindowCell->uiStat, false );
    PCICtrlWrite32( FILT_MOP, FILTER_NO_MOP, false );

	// 2. PDW 필터 적용
	PCICtrlWrite32( FILT_ADAPT, NOT_APPLY, false );
    PCICtrlWrite32( ANZ_CNT, pWindowCell->uiCoCollectingPDW, false );

    tTime.dw = ANZ_TIME_MS( pWindowCell->uiMaxCollectTimeMssec );
#ifdef __VXWORKS__
    PCICtrlWrite32( ANZ_TIME_L, tTime.word[1], false );
    PCICtrlWrite32( ANZ_TIME_H, tTime.word[0], false );
#else
    PCICtrlWrite32( ANZ_TIME_L, tTime.word[0], false );
    PCICtrlWrite32( ANZ_TIME_H, tTime.word[1], false );
#endif

#ifdef _SELF_GEN_PDW
    PCICtrlWrite32( PATN_INTERVAL, ( unsigned int ) ( pWindowCell->uiMaxCollectTimeMssec * PATN_INTERVAL_MS ) );
#endif

	// 3. 채널 번호 설정
    PCICtrlWrite32( PARAM_IDX_W, ( unsigned int ) ( pWindowCell->uiCh + 1 ), false );

    // 4. 수집 시작
    PCICtrlWrite32( ANZ_START, ( unsigned int ) ( pWindowCell->uiCh + 1 ), false );

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
        _func_kprintf( "\n@%sCtrlWrite32(%s[0x %04X], 0x%08x)", m_strHeader.c_str(), GetRegisterName( uiOffset ), uiOffset, uiValue );
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
        _func_kprintf( "\n@[0x%08X] = %sCtrlRead32( %s[0x%04X] )", uiValue32, m_strHeader.c_str(), GetRegisterName( uiOffset ), uiOffset );
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
    const char* pChar=NULL;

#ifdef __VXWORKS__
    switch (uiOffset) {
    case PARAM_INIT :
        pChar = g_strPCIRegisterName[0].c_str();
        break;

    case OP_MODE:
        pChar = g_strPCIRegisterName[1].c_str();
        break;

    case PATN_INTERVAL:
        pChar = g_strPCIRegisterName[2].c_str();
        break;

    case PARAM_IDX_W:
        pChar = g_strPCIRegisterName[3].c_str();
        break;

    case FILT_BYPASS:
        pChar = g_strPCIRegisterName[4].c_str();
        break;

    case ANZ_START :
		pChar = g_strPCIRegisterName[5].c_str();
		break;

    case ANZ_STOP:
        pChar = g_strPCIRegisterName[6].c_str();
        break;

    case ANZ_ID:
        pChar = g_strPCIRegisterName[7].c_str();
        break;

	case ANZ_LOST_DEL_ON:
		pChar = g_strPCIRegisterName[8].c_str();
		break;

	case ANZ_LOST_TIME:
		pChar = g_strPCIRegisterName[9].c_str();
		break;

	case ANZ_DEL_TIME:
		pChar = g_strPCIRegisterName[10].c_str();
		break;

	case ANZ_CNT:
		pChar = g_strPCIRegisterName[11].c_str();
		break;

	case ANZ_TIME_L:
		pChar = g_strPCIRegisterName[12].c_str();
		break;

    case ANZ_TIME_H:
        pChar = g_strPCIRegisterName[13].c_str();
        break;

	case ANZ_M_OFFSET:
		pChar = g_strPCIRegisterName[14].c_str();
		break;

	case ANZ_M_SIZE:
		pChar = g_strPCIRegisterName[15].c_str();
		break;

	case FILT_ADAPT:
		pChar = g_strPCIRegisterName[16].c_str();
		break;

	case FILT_AOA_MAX:
		pChar = g_strPCIRegisterName[17].c_str();
		break;

	case FILT_AOA_MIN:
		pChar = g_strPCIRegisterName[18].c_str();
		break;

	case FILT_FREQ_MAX:
		pChar = g_strPCIRegisterName[19].c_str();
		break;

	case FILT_FREQ_MIN:
		pChar = g_strPCIRegisterName[20].c_str();
		break;

	case FILT_PW_MAX:
		pChar = g_strPCIRegisterName[21].c_str();
		break;

	case FILT_PW_MIN:
		pChar = g_strPCIRegisterName[22].c_str();
		break;

	case FILT_PA_MAX:
		pChar = g_strPCIRegisterName[23].c_str();
		break;

	case FILT_PA_MIN:
		pChar = g_strPCIRegisterName[24].c_str();
		break;

    case FILT_MOP:
        pChar = g_strPCIRegisterName[25].c_str();
        break;

    case ANZ_IRQ_STATUS:
        pChar = g_strPCIRegisterName[26].c_str();
        break;

    case ANZ_ACQ_UPDATE:
        pChar = g_strPCIRegisterName[27].c_str();
        break;

    case ANZ_ACQ_CNT:
        pChar = g_strPCIRegisterName[28].c_str();
        break;

    case ANZ_LAST_ADDR:
        pChar = g_strPCIRegisterName[29].c_str();
        break;

    case ANZ_LOST_STATUS:
        pChar = g_strPCIRegisterName[30].c_str();
        break;

    case ANZ_DELETE_STATUS:
        pChar = g_strPCIRegisterName[31].c_str();
        break;

    case PARAM_IDX_R:
        pChar = g_strPCIRegisterName[32].c_str();
        break;

//     case ANZ_REQ:
//         pChar = g_strPCIRegisterName[33].c_str();
//         break;

    case IBRDID:
        pChar = g_strPCIRegisterName[34].c_str();
        break;

    default:
        break;
    }
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
void CPCIDriver::CloseChannel( unsigned int uiCh )
{

    _func_kprintf( "\n 채널[%d] 닫기", uiCh );

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
void CPCIDriver::GetPDWData( STR_UZPOCKETPDW *pPDWData, unsigned int uiCh, unsigned int uiTotalPDW, unsigned int uiPCIAddressOffset )
{

#ifdef __VXWORKS__
    unsigned char *pPCIAddress = 0;

    pPCIAddress = PCIeCtrlMemory( (unsigned int) m_enPCIDriver );

    pPCIAddress += uiPCIAddressOffset;

    Log( enNormal, "%s [%d] 개의 PDW 데이터를 [0x%08x(0x%08x)] 에서부터 복사합니다.", m_strHeader.c_str(), uiTotalPDW, pPCIAddress, uiPCIAddressOffset );

    memcpy( pPDWData->pstPDW, pPCIAddress, sizeof( union UZPOCKETPDW ) * uiTotalPDW );
    CCommonUtils::AllSwapData64( pPDWData->pstPDW, sizeof( union UZPOCKETPDW ) * uiTotalPDW );

#else
    //LOGMSG3( enNormal, "%s [%d] 개의 PDW 데이터를 [0x%08x] 에서부터 복사합니다.", m_strHeader.c_str(), uiTotalPDW, pPCIAddress );

#endif

}
