/**

    @file      PCIDriver.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      14.12.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include <string>

#include "cthread.h"
#include "../Include/struct.h"


#include "clogname.h"

// 수집 필터 총 채널 개수
#define TOTAL_FLT_CHANNEL           (32)        // 총 필터 채널 개수


// PCI 메모리 옵셋 정의
#define PARAM_INIT                  (0x0000)    // 신호 분석용 파라미터 초기화 요청 비트
#define OP_MODE                     (0x0004)    // 메모리(PL-BRAM) 제어 여부 확인용 동작모드.
#define PATN_INTERVAL               (0x0008)    // 메모리(PL-BRAM) 제어 여부 확인용 Pattern(PDW) 생성 주기.
#define SEARCH_START                (0x0010)    // 탐지채널 신호분석 시작 요청. 1번 부터 시작.
#define TRACK_START                 (0x0014)    // 추적채널 신호분석 시작 요청. 1번 부터 시작.
#define SCAN_START                  (0x0018)    // 스캔채널 신호분석 시작 요청., 1번 부터 시작.
#define DUMMY_START                 (0x001C)    // 더미채널 신호분석 시작 요청. 1번 부터 시작.
#define SEARCH_STOP                 (0x0020)    // 탐지채널 신호분석 종료. 1번 부터 시작.
#define TRACK_STOP                  (0x0024)    // 추적채널 신호분석 종료. 1번 부터 시작.
#define SCAN_STOP                   (0x0028)    // 스캔채널 신호분석 종료. 1번 부터 시작.
#define DUMMY_STOP                  (0x002C)    // 더미채널 신호분석 종료. 1번 부터 시작.

#define PARAM_IDX_W                 (0x0100)    // 신호 분석용 PDW Filter 파라미터 쓰기 인덱스(채널) 설정값.
#define PARAM_BYPASS                (0x0104)    // PDW Filter 통과/제거 설정. (필터 모드)
//#define ANZ_START           (0x0108)    // 신호분석 시작 요청.
//#define ANZ_STOP                    (0x010C)    // 탐색/추적/스캔/Unknown 신호분석 종료
//#define ANZ_ID                      (0x0110)    // 신호분석 제원에 대한 Lost/Delete 판단 적용 비트.
//#define ANZ_LOST_DEL_ON             (0x0114)    // 신호분석 제원에 대한 Lost/Delete 판단 적용 비트.
//#define ANZ_LOST_TIME               (0x0118)    // 신호분석 제원에 대한 Lost 판단 설정시간
//#define ANZ_DEL_TIME                (0x011C)    // 신호분석 제원에 대한 Delete 판단 설정시간
#define PARAM_ANZ_COUNT             (0x0120)    // 신호분석 요청에 따른 PDW 저장 설정개수
#define PARAM_ANZ_TIME_LOW          (0x0124)    // 신호분석 요청에 따른 PDW 저장 설정시간(하위), 18 bit
//#define PARAM_ANZ_TIME_HIGH         (0x0128)    // 신호분석 요청에 따른 PDW 저장 설정시간(상위)
#define PARAM_ANZ_M_OFFSET          (0x012C)    // PDW Filter 인덱스(채널)별 메모리 시작 주소
#define PARAM_ANZ_M_SIZE            (0x0130)    // PDW Filter 인덱스(채널)별 메모리 용량

#define FILT_ADAPT                  (0x0134)    // PDW Filter 적용 유/무
#define FILT_AOA_MAX                (0x0138)    // PDW Filter AOA 최대값
#define FILT_AOA_MIN                (0x013C)    // PDW Filter AOA 최소값
#define FILT_FREQ_MAX               (0x0140)    // PDW Filter FREQ 최대값
#define FILT_FREQ_MIN               (0x0144)    // PDW Filter FREQ 최소값
#define FILT_PW_MAX                 (0x0148)    // PDW Filter PW 최대값
#define FILT_PW_MIN                 (0x014C)    // PDW Filter PW 최소값
#define FILT_PA_MAX                 (0x0150)    // PDW Filter PA 최대값
#define FILT_PA_MIN                 (0x0154)    // PDW Filter PA 최소값
#define FILT_MOP                    (0x0158)    // PDW Filter MOP 정보
#define FILT_MOP_DIR                (0x015C)    // PDW Filter MOP 방향
#define FILT_MOP_BW_MAX             (0x0160)    // PDW Filter MOP 대역폭 최대
#define FILT_MOP_BW_MIN             (0x0164)    // PDW Filter MOP 대역폭 최소



#ifdef _OLD_VERSION_
#define ANZ_IRQ_STATUS              (0x015C)    // 신호 분석 요청에 의한 필터별 인터럽트 발생 유/무
#define ANZ_ACQ_UPDATE              (0x0160)    // 신호 분석 요청에 의한 수집된 PDW 갱신 여부
#define ANZ_ACQ_CNT                 (0x0164)    // 신호 분석 요청에 의한 수집된 완료시, PDW 저장개수
#define ANZ_LAST_ADDR               (0x0168)    // 신호 분석 요청에 의한 수집된 완료시, 마지막 PDW 저장 메모리 주소값
#define ANZ_LOST_STATUS             (0x016C)    //
#define ANZ_DELETE_STATUS           (0x0170)    //

#else
#define ANZ_IRQ_STATUSLOW           (0x0168)    // 신호 분석 요청에 의한 필터별 인터럽트 발생 유/무
#define ANZ_IRQ_STATUSHIGH          (0x016C)    //

#define ANZ_ACQ_CNT1                (0x0170)    // 탐지채널 신호 분석 요청에 의한 수집된 PDW 저장개수.
#define ANZ_ACQ_CNT2                (0x0174)    // 추적채널 신호 분석 요청에 의한 수집된 PDW 저장개수.
#define ANZ_ACQ_CNT3                (0x0178)    // 스캔채널 신호 분석 요청에 의한 수집된 PDW 저장개수.
#define ANZ_ACQ_CNT4                (0x017C)    // 더미채널 신호 분석 요청에 의한 수집된 PDW 저장개수.

#endif

#define PARAM_TYPE                  (0x0188)    // 신호 분석용 PDW Filter 파라미터 읽기 인덱스(채널) 설정값.
#define PARAM_FALSE_PDW             (0x018C)    // PDW Filter False PDW 식별자.
#define PARAM_IDX_R                 (0x0200)    // 읽기-분석채널 선택 설정값., 탐지는 1번 부터
#define IBRDID                      (0x0208)    // Board ID 대역 정보.
#define ANZ_FILT_TAP1               (0x0214)    // 탐지채널 필터 운용개수 설정값.
#define ANZ_FILT_TAP2               (0x0218)    // 추적채널 필터 운용개수 설정값.
#define ANZ_FILT_TAP3               (0x021C)    // 스캔채널 필터 운용개수 설정값.
#define ANZ_FILT_TAP4               (0x0220)    // 더미채널 필터 운용개수 설정값.
#define PARAM_BRAM_WE               (0x0300)    // PDW Filter 파라미터 메모리 쓰기 인에이블.
#define PARAM_BRAM_WADDR            (0x0304)    // PDW Filter 메모리 파라미터 쓰기 어드레스. 0번 부터 시작
#define PARAM_BRAM_RADDR            (0x0308)    // PDW Filter 메모리 파라미터 쓰기 어드레스. 0번 부터 시작
#define ANZ_CNT_IDX                 (0x0400)    // 수집카운트 읽기 인덱스(채널) 설정값.

#define CLOCK_RATE                  (0x0404)    // 클럭 레이트 설정값


///////////////////////////////////////////////////////////////////////////////////

#define LOGIC_TOTAL_CHANNEL         (64)

#define PARAM_ANZ_TIME_MAXBIT       (0x3FFFF)


//////////////////////////////////////////////////////////////////////////
// 값 정의
#define APPLY                               (1)
#define NOT_APPLY                           (0)

#define BYPASS                      (0)
#define REJECT                      (1)

#define FILTER_SIGNALTYPE_CW        (0)
#define FILTER_SIGNALTYPE_NORMAL    (1)
#define FILTER_SIGNALTYPE_ALL       (0)

#define FILTER_NO_MOP               (0)
#define FILTER_PMOP                 (1)
#define FILTER_FMOP                 (2)
#define FILTER_ALL_MOP              (3)

#define FILTER_FMOP_TRI             (0)
#define FILTER_FMOP_UP              (1)
#define FILTER_FMOP_DOWN            (2)
#define FILTER_FMOP_UNKNOWN         (3)

#define FILT_ADAPT_AOA             (0x01)
#define FILT_ADAPT_FRQ             (0x02)
#define FILT_ADAPT_PW              (0x04)
#define FILT_ADAPT_PA              (0x08)
#define FILT_ADAPT_MOP             (0x10)
#define FILT_ADAPT_TYPE            (0x20)
#define FILT_ADAPT_FALSE_PDW       (0x40)

#define FILT_ADAPT_ALL             (0x00)

#define FILT_BYPASS_AOA            (0x01)
#define FILT_BYPASS_FRQ            (0x02)
#define FILT_BYPASS_PW             (0x04)
#define FILT_BYPASS_PA             (0x08)
#define FILT_BYPASS_MOP            (0x10)
#define FILT_BYPASS_TYPE           (0x20)
#define FILT_BYPASS_FALSE_PDW      (0x40)

#define FILT_BYPASS_ALL            (0x00)
#define FILT_REJECT_ALL            (FILT_BYPASS_AOA | FILT_BYPASS_FRQ | FILT_BYPASS_PW | FILT_BYPASS_PA | FILT_BYPASS_MOP | FILT_BYPASS_TYPE | FILT_BYPASS_FALSE_PDW )


#define FILTER_REQ_STOP         (0)
#define FILTER_REQ_START        (1)

#define PATN_INTERVAL_MS        (unsigned int) ( (1000000./ 22. / 6.4) + 0.5)
#define PATN_INTERVAL_US        (unsigned int) ( (1000./ 22. / 6.4) + 0.5)



#define CLOCK_SEED              (1024*60)
#define CLOCK_RES               ( FDIV( 125, CLOCK_SEED ) * ( float ) 1000000. )

//#define ANZ_TIME_MS(A)      (unsigned long long int) ( (unsigned long long int) 250000 * (A) + 0.5 ) // ( (1000000./ 6.4)*(A) + 0.5)
#define ANZ_TIME_MS(A)          (unsigned long long int) ( (unsigned long long int) 125000 * (A) + 0.5 ) // ( (1000000./ 8.0)*(A) + 0.5)


#ifdef _MSC_VER
#define IRQ_PCI_LEFT            (25)
#define IRQ_PCI_RIGHT           (30)
#endif

/**

    @class   CPCIDriver
    @brief   수집 모듈 클래스
    @details ~
    @author  조철희
    @date    14.12.2023

**/
class CPCIDriver : public CLogName
{
private:
    ENUM_PCI_DRIVER m_enPCIDriver;

    bool m_bBIT;

    bool m_bIsr;

    std::string m_strHeader;

    // 메시지 데이터
    UNI_MSG_DATA m_uniMsgData;
    STR_COLLECT_INFO *m_pstrCollectInfo;

public:
    static bool m_bPCIMemInit;

private:
    void InitDetectFilter() const;
    void InitScanFilter() const;
    void InitTrackFilter() const;
    void InitParameter( bool bLog ) const;

public:
	void PCIConfigSetting() const;
    void PCIInterruptEnable() const;
    void PCIInterruptDisable() const;

public:
	void PCICtrlWrite32( unsigned int uiOffset, unsigned int uiValue, bool bLog = true, bool bLogMsg = false ) const;

public:
	UINT PCICtrlRead32( unsigned int uiOffset, bool bLog = true, bool bLogMsg = false ) const;

	const char* GetRegisterName( unsigned int uiOffset ) const;

public:
    CPCIDriver( ENUM_PCI_DRIVER enPCIDriver, const char *pThreadName=NULL );
    ~CPCIDriver();

    void Init();
    void RunBit();

    void StartCollecting();
    void EndCollecting();
    void PreFilterSetting( STR_WINDOWCELL *pstWindowCell, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress, STR_COLLECT_PCIADDRESS *pstrPreFilterPCIAddress );
    void PreFilterClose( STR_WINDOWCELL *pstWindowCell, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress );
    void CloseChannel( unsigned int uiCh, ENUM_COLLECTBANK enCollectBank, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress );

    void ISRRoutine();

    void StartCollecting(STR_WINDOWCELL* pWindowCell, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress );

    void GetPDWData( STR_UZPOCKETPDW *pPDWData, unsigned int uiCh, unsigned int uiTotalPDW, unsigned int uiPCIAddressOffset );

    unsigned char *GetAddress( unsigned int uiOffset );

};
