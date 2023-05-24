//////////////////////////////////////////////////////////////////////////
// CPCIDriver.h 헤더 파일

#pragma once

#include <string>

#include "cthread.h"
#include "../Include/struct.h"




// 수집 필터 총 채널 개수
#define TOTAL_FLT_CHANNEL   (32)        // 총 필터 채널 개수


// PCI 메모리 옵셋 정의
#define PARAM_INIT          (0x0000)    // 신호 분석용 파라미터 초기화 요청 비트
#define OP_MODE             (0x0004)    // 메모리(PL-BRAM) 제어 여부 확인용 동작모드.
#define PATN_INTERVAL       (0x0008)    // 메모리(PL-BRAM) 제어 여부 확인용 Pattern(PDW) 생성 주기.
#define PARAM_IDX_W         (0x0100)    // 신호 분석용 PDW Filter 파라미터 쓰기 인덱스(채널) 설정값.
#define FILT_BYPASS         (0x0104)    // PDW Filter 통과/제거 설정. (필터 모드)
#define ANZ_START           (0x0108)    // 신호분석 시작 요청.
#define ANZ_STOP            (0x010C)    // 탐색/추적/스캔/Unknown 신호분석 종료
#define ANZ_ID              (0x0110)    // 신호분석 제원에 대한 Lost/Delete 판단 적용 비트.
#define ANZ_LOST_DEL_ON     (0x0114)    // 신호분석 제원에 대한 Lost/Delete 판단 적용 비트.
#define ANZ_LOST_TIME       (0x0118)    // 신호분석 제원에 대한 Lost 판단 설정시간
#define ANZ_DEL_TIME        (0x011C)    // 신호분석 제원에 대한 Delete 판단 설정시간
#define ANZ_CNT             (0x0120)    // 신호분석 요청에 따른 PDW 저장 설정개수
#define ANZ_TIME_L          (0x0124)    // 신호분석 요청에 따른 PDW 저장 설정시간(하위)
#define ANZ_TIME_H          (0x0128)    // 신호분석 요청에 따른 PDW 저장 설정시간(상위)

#define ANZ_M_OFFSET        (0x012C)    // PDW Filter 인덱스(채널)별 메모리 시작 주소
#define ANZ_M_SIZE          (0x0130)    // PDW Filter 인덱스(채널)별 메모리 용량
#define FILT_ADAPT          (0x0134)    // PDW Filter 적용 유/무
#define FILT_AOA_MAX        (0x0138)    // PDW Filter AOA 최대값
#define FILT_AOA_MIN        (0x013C)    // PDW Filter AOA 최소값
#define FILT_FREQ_MAX       (0x0140)    // PDW Filter FREQ 최대값
#define FILT_FREQ_MIN       (0x0144)    // PDW Filter FREQ 최소값
#define FILT_PW_MAX         (0x0148)    // PDW Filter PW 최대값
#define FILT_PW_MIN         (0x014C)    // PDW Filter PW 최소값
#define FILT_PA_MAX         (0x0150)    // PDW Filter PA 최대값
#define FILT_PA_MIN         (0x0154)    // PDW Filter PA 최소값
#define FILT_MOP            (0x0158)    // PDW Filter MOP 정보
#define ANZ_IRQ_STATUS      (0x015C)    // 신호 분석 요청에 의한 필터별 인터럽트 발생 유/무
#define ANZ_ACQ_UPDATE      (0x0160)    // 신호 분석 요청에 의한 수집된 PDW 갱신 여부
#define ANZ_ACQ_CNT         (0x0164)    // 신호 분석 요청에 의한 수집된 완료시, PDW 저장개수
#define ANZ_LAST_ADDR       (0x0168)    // 신호 분석 요청에 의한 수집된 완료시, 마지막 PDW 저장 메모리 주소값
#define ANZ_LOST_STATUS     (0x016C)    //
#define ANZ_DELETE_STATUS   (0x0170)    //

#define PARAM_IDX_R         (0x0200)    // 신호 분석용 PDW Filter 파라미터 읽기 인덱스(채널) 설정값.
//#define ANZ_REQ             (0x0204)    //

#define IBRDID              (0x0208)    // 신호 분석용 PDW Filter 파라미터 읽기 인덱스(채널) 설정값.


//////////////////////////////////////////////////////////////////////////
// 값 정의
#define APPLY               (1)
#define NOT_APPLY           (0)

#define BYPASS              (0)
#define REJECT              (1)

#define FILTER_NO_MOP       (0)
#define FILTER_PMOP         (1)
#define FILTER_FMOP         (2)
#define FILTER_ALL_PMOP     (3)


#define FILTER_REQ_STOP     (0)
#define FILTER_REQ_START    (1)

#define PATN_INTERVAL_MS    (unsigned int) ( (1000000./ 22. / 6.4) + 0.5)
#define PATN_INTERVAL_US    (unsigned int) ( (1000./ 22. / 6.4) + 0.5)

//#define ANZ_TIME_MS(A)      (unsigned long long int) ( (unsigned long long int) 250000 * (A) + 0.5 ) // ( (1000000./ 6.4)*(A) + 0.5)
#define ANZ_TIME_MS(A)      (unsigned long long int) ( (unsigned long long int) 125000 * (A) + 0.5 ) // ( (1000000./ 8.0)*(A) + 0.5)


#ifdef _MFC_VER
#define IRQ_PCI_LEFT            (25)
#define IRQ_PCI_RIGHT           (30)
#endif


// 수집 모듈 PCI 클래스
class CPCIDriver {

private:
    bool m_bBIT;

    bool m_bIsr;

    ENUM_PCI_DRIVER m_enPCIDriver;

    std::string m_strHeader;

    // 메시지 데이터
    UNI_MSG_DATA m_uniMsgData;
    STR_COLLECT_INFO *m_pstrCollectInfo;

public:
    static bool m_bPCIMemInit;

private:
	void PCIConfigSetting() const;
    void PCIInterruptEnable() const;
    void PCIInterruptDisable() const;

public:
	void PCICtrlWrite32( unsigned int uiOffset, unsigned int uiValue, bool bLog = true ) const;

public:
	UINT PCICtrlRead32( unsigned int uiOffset, bool bLog = true ) const;

	const char* GetRegisterName( unsigned int uiOffset ) const;

public:
    CPCIDriver( ENUM_PCI_DRIVER enPCIDriver );
    ~CPCIDriver();

    void Init();
    void RunBit();

    void StartCollecting();
    void EndCollecting();
    void CloseChannel( unsigned int uiCh );

    void ISRRoutine();

    void StartCollecting(STR_WINDOWCELL* pWindowCell, STR_COLLECT_PCIADDRESS *pstrCollectPCIAddress );

    void GetPDWData( STR_UZPOCKETPDW *pPDWData, unsigned int uiCh, unsigned int uiTotalPDW, unsigned int uiPCIAddressOffset );

    unsigned char *GetAddress( unsigned int uiOffset );


};
